/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.

BUGS:
PROBLEMS:
IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "world/world.h"
#include "spatial_algebra/spatial_algebra.h"
#include <math.h>
#include <stdarg.h>
#include <sstream>

#include <assert.h>
#include "utils/string_utils.h"


#include "world/standard_aspects/standard_aspects.h"


ShadingModelInstance *shading_model_model_test;


static const bool logging_rendering = true;
static void log_render(const char *format, ...)
{
    if (!logging_rendering) return;
    va_list args;
    va_start(args, format);
    printf("[render] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


World::World()
{
    printf("[world] Creating world...\n");

    // Initialize the resource model.
    printf("[world] Initializing resource model...\n");
    resources = Resources();
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) {\
        resources.register_resource_type<NAME>();\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering resource types...\n");
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingBlock); //Data layout description for material properties.
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);
    printf("[world] Resource model initialized.\n");

    // Initialize the entity model, with no entities.
    printf("[world] Initializing entity model...\n");
    entities = Entities();
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) {\
        entities.register_aspect_type<NAME>();\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering aspect types...\n");
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);
    REGISTER_ASPECT_TYPE(Behaviour);
    printf("[world] Entity model initialized.\n");

    // Initialize an instance of Assets, through which hard-coded specific assets can be loaded and shared using the resource model.
    printf("[world] Initializing Assets...\n");
    assets = Assets();
    assets.resources = &resources;
    assets.models.resources = &resources;
    assets.shading.resources = &resources;
    printf("[world] Assets initialized.\n");

    // Initialize the Graphics component, which holds graphics state, such as compiled shader programs.
    printf("[world] Initializing Graphics...\n");
    graphics = Graphics(&resources); // The Graphics component relies on the resource model.
    printf("[world] Graphics initialized.\n");

    glDisable(GL_CULL_FACE); //
    glEnable(GL_DEPTH_TEST); // todo: Remove this.
    glDepthFunc(GL_LESS);    //

    // Resource<ShadingModel> sm = resources.load_from_file<ShadingModel>("resources/model_test/model_test.sm");
    Resource<ShadingModel> sm = resources.add<ShadingModel>();
    std::fstream sm_file;
    sm_file.open("resources/model_test/model_test.sm");
    sm->load(resources, sm_file);
    shading_model_model_test = new ShadingModelInstance(sm); // create a global shading model instance for testing.

    // Input.
    printf("[world] Initializing InputState...\n");
    input = InputState();
    printf("[world] InputState initialized.\n");
}


void World::save(std::string &path)
{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file.is_open()) {
        printf("[world] Failed to open file \"%s\" when saving world.\n", path.c_str());
        exit(EXIT_FAILURE);
    }
    // Component subsystems.
    // Entities entities;    Saved.
    // Resources resources;  
    // Graphics graphics; 
    // InputState input;  Thrown out.
    // Assets assets;

    // Entities
    // pack(em.entity_table, file);
    // pack(em.aspect_tables, file);
}


World World::load_world(std::string &path)
{
    //todo
    return World();
}


void World::close()
{
}


void World::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

    float bg_color[4] = {0,0,0,0};
    float fg_color[4] = {1,1,1,1};

    // Clearing: window clear to background color, viewport clear to the foreground color.
    glClearColor(bg_color[0],bg_color[1],bg_color[2],bg_color[3]);
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glEnable(GL_SCISSOR_TEST);
    glScissor(viewport[0], viewport[1], viewport[2], viewport[3]);
    glClearColor(fg_color[0],fg_color[1],fg_color[2],fg_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Update entity behaviours.
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->update();
    }
    // Render.
    bool any_camera = false;
    for (auto camera : entities.aspects<Camera>()) {
        any_camera = true;
        printf("[render] Camera rendering...\n");
        print_entity(camera.entity());

        log_render("Getting camera transform...");
        auto camera_transform = camera.sibling<Transform>();
        log_render("Calculating view-projection matrix...");
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        log_render("Uploading view-projection matrix...");
        shading_model_model_test->properties.set_mat4x4("vp_matrix", vp_matrix);

        log_render("Rendering Drawables:");
        for (auto drawable : entities.aspects<Drawable>()) {
            log_render("  Rendering drawable.");
            log_render("    Getting transform...");
            auto t = drawable.sibling<Transform>();
            log_render("    Calculating model matrix...");
            mat4x4 model_matrix = t->matrix();
            log_render("    Uploading model matrix...");
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);

            log_render("    Draw.");
            graphics.draw(drawable->geometric_material, drawable->material, *shading_model_model_test);
        }
    }
    if (!any_camera) printf("[world] No camera.\n"); // Make it easier to tell when the camera is not working.
}


void World::keyboard_handler(KeyboardEvent e)
{
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->keyboard_handler(e);
    }
}


void World::mouse_handler(MouseEvent e)
{
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->mouse_handler(e);
    }
}



/*--------------------------------------------------------------------------------
    Entity serialization.
--------------------------------------------------------------------------------*/


void World::print_entity(Entity entity, int indent_level)
{
    std::cout << "entity {\n";
    for (auto &aspect : entity) {
        // Now pack the actual aspect data.
        print_aspect(aspect, std::cout, indent_level+1);
    }
    std::cout << indents(indent_level) << "}\n";
}

void World::pack_entity(Entity entity, std::ostream &out)
{
    int num_aspects = entity.num_aspects();
    Reflector::pack(num_aspects, out);

    for (auto &aspect : entity) {
        Reflector::pack(aspect.type(), out);
        export_aspect(aspect, out);
    }
}

Entity World::unpack_entity(std::istream &in)
{
    auto entity = entities.add();
    int num_aspects;
    Reflector::unpack(in, num_aspects);
    for (int i = 0; i < num_aspects; i++) {
        TypeHandle type;
        Reflector::unpack(in, type);
        auto aspect = entity.add(type);
        import_aspect(in, aspect);
    }
    return entity;
}

Entity World::copy_entity(Entity entity)
{
    std::stringstream buffer;
    pack_entity(entity, buffer);
    return unpack_entity(buffer);
}


void World::export_entity(Entity entity, const std::string &path)
{
    std::cout << "Exporting entity...\n";
    std::ofstream file;
    file.open(path, std::ios::trunc | std::ios::out | std::ios::binary);
    assert(file.is_open());
    pack_entity(entity, file);
    file.close();
}


Entity World::import_entity(const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    assert(file.is_open());
    Entity entity = unpack_entity(file);
    file.close();
    return entity;
}

void World::export_aspect(GenericAspect aspect, std::ostream &out)
{
    auto type_name = aspect.type()->name();
    std::cout << "    Exporting " << type_name << " aspect...\n";

    aspect.type()->pack(*aspect.get_data(), out);

    aspect.type()->apply([&](const TypeHandle &type, uint8_t &obj) {
        if (type->name() == "Resource<T>" || type->name() == "GenericResource") {
            auto &resource = reinterpret_cast<GenericResource &>(obj);
            printf("Exporting resource!\n");
            Reflector::printl(resource.type());
            getchar();
        }
    }, *aspect.get_data());

    std::cout << "    Export success:\n        ";
    aspect.type()->print(*aspect.get_data(), std::cout, 2);
    std::cout << "\n";
}

void World::import_aspect(std::istream &in, GenericAspect aspect)
{
    auto type_name = aspect.type()->name();
    std::cout << "    Importing " << type_name << " aspect...\n";
    Reflector::printl(aspect.entity());

    // The aspect metadata, including the parent entity and the next aspect,
    // is stored as data members _in the aspect type_, which derives from IAspectType (the metadata class).
    // This means it must be saved and restored, since the aspect unpacker
    // doesn't know this context.
    IAspectType metadata = *aspect.metadata();

    aspect.type()->unpack(in, *aspect.get_data());

    // Restore the metadata.
    *aspect.metadata() = metadata;

    // Pointer and reference fix-ups specific to aspects.
    aspect.type()->apply([&](const TypeHandle &type, uint8_t &obj) {
        std::cout << "Fixing up " << type->name() << "\n";
        if (type == TypeHandle::from_type<World *>()) {
            // Fix-up World pointers.
            (World * &) obj = this;
        } else if (type == TypeHandle::from_type<Resources *>()) {
            // Fix-up Resources pointers.
            (Resources * &) obj = &resources;
        } else if (type == TypeHandle::from_type<Entities *>()) {
            // Fix-up Entities pointers.
            (Entities * &) obj = &entities;
        } else if (type == TypeHandle::from_type<Entity>()) {
            // Fix-up parent entity references.
            //(todo): Make this search for a separate type, ParentEntity.
            (Entity &) obj = aspect.entity();
        }
    }, *aspect.get_data());

    std::cout << "    Import success:\n        ";
    aspect.type()->print(*aspect.get_data(), std::cout, 2);
    std::cout << "\n";
}


void World::print_aspect(GenericAspect aspect, std::ostream &out, int indent_level)
{
    auto type_name = aspect.type()->name();
    out << indents(indent_level);

    aspect.type()->print(*aspect.get_data(), out, indent_level);
    printf("\n");
}


// Non-virtual Behaviour interface.
// It may be useful to wrap all behaviour callbacks for debugging.
void Behaviour::update()
{
    object()->update();
}
void Behaviour::mouse_handler(MouseEvent e)
{
    object()->mouse_handler(e);
}
void Behaviour::keyboard_handler(KeyboardEvent e)
{
    object()->keyboard_handler(e);
}


DESCRIPTOR_INSTANCE(IBehaviour);
BEGIN_ENTRIES(IBehaviour)
    ENTRY(world)
    ENTRY(entity)
END_ENTRIES()


DESCRIPTOR_INSTANCE(Behaviour);
BEGIN_ENTRIES(Behaviour)
    ENTRY(data)
END_ENTRIES()



DESCRIPTOR_INSTANCE(World);
BEGIN_ENTRIES(World)
    //...unfinished
END_ENTRIES()


