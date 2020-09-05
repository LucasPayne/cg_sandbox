/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.

BUGS:
PROBLEMS:
IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "opengl_utilities/gl.h"
#include "world/world.h"
#include "spatial_algebra/spatial_algebra.h"
#include <math.h>
#include <stdarg.h>
#include <sstream>

#include <assert.h>
#include "utils/string_utils.h"


#include "world/standard_aspects/standard_aspects.h"


World::World() : graphics{Graphics(*this)}, assets{Assets(*this)}
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

    // // Initialize the Graphics component, which holds graphics state, such as compiled shader programs.
    // printf("[world] Initializing Graphics...\n");
    // graphics = Graphics(&resources); // The Graphics component relies on the resource model.
    // printf("[world] Graphics initialized.\n");

    glDisable(GL_CULL_FACE); //
    glEnable(GL_DEPTH_TEST); // todo: Remove this.
    glDepthFunc(GL_LESS);    //

    // Input.
    printf("[world] Initializing InputState...\n");
    input = InputState();
    printf("[world] InputState initialized.\n");

    
    // TODO: Give every subsystem an init().
    graphics.init();
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



// Utilities.
bool World::screen_to_ray(float screen_x, float screen_y, Ray *ray)
{
    // Get the highest-priority (lowest layer) camera which has its viewport overlapping this screen position.
    bool any = false;
    Aspect<Camera> used_camera;
    for (auto &camera : entities.aspects<Camera>()) {
        if (camera->in_viewport(screen_x, screen_y)) {
            if (!any) {
                any = true;
                used_camera = camera;
            } else {
                if (camera->layer < used_camera->layer) used_camera = camera;
            }
        }
    }
    if (!any) return false;

    float camera_x, camera_y;
    used_camera->to_viewport(screen_x, screen_y, &camera_x, &camera_y);
    *ray = used_camera->ray(camera_x, camera_y);
    // printf("screen_x: %.2f, screen_y: %.2f\n", screen_x, screen_y);
    // printf("camera_x: %.2f, camera_y: %.2f\n", camera_x, camera_y);
    // getchar();
    return true;
}



void World::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

    graphics.clear();
    graphics.paint.clear();
    // Update entity behaviours.
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->update();
    }
    graphics.render_drawables();
    // for (int i = 0; i < 10; i++) graphics.paint.sphere(vec3(frand(), 0,0), 1, vec4(0,1,1,1));
    // graphics.paint.render();
}
