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

#include "world/standard_aspects/standard_aspects.h"

ShadingModelInstance *shading_model_model_test;

static void log_render(const char *format, ...)
{
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
    rm = ResourceModel();
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) {\
        rm.register_resource_type<NAME>(#NAME);\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering resource types...\n");
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);
    printf("[world] Resource model initialized.\n");

    // Initialize the entity model, with no entities.
    printf("[world] Initializing entity model...\n");
    em = EntityModel();
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) {\
        em.register_aspect_type<NAME>(#NAME);\
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
    assets.rm = &rm;
    assets.models.rm = &rm;
    assets.shading.rm = &rm;
    printf("[world] Assets initialized.\n");

    // Initialize the Graphics component, which holds graphics state, such as compiled shader programs.
    printf("[world] Initializing Graphics...\n");
    graphics = Graphics(&rm); // The Graphics component relies on the resource model.
    printf("[world] Graphics initialized.\n");

    glDisable(GL_CULL_FACE); //
    glEnable(GL_DEPTH_TEST); // todo: Remove this.
    glDepthFunc(GL_LESS);    //

    // Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/model_test/model_test.sm");
    Resource<ShadingModel> sm = rm.new_resource<ShadingModel>();
    std::fstream sm_file;
    sm_file.open("resources/model_test/model_test.sm");
    sm->load(sm_file);
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
    // EntityModel em;    Saved.
    // ResourceModel rm;  
    // Graphics graphics; 
    // InputState input;  Thrown out.
    // Assets assets;

    // EntityModel
    pack(em.entity_table, file);
    pack(em.aspect_tables, file);
}


World World::load_world(std::string &path)
{
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
    for (auto b : em.aspects<Behaviour>()) {
        if (b->object->updating) {
            b->object->update();
        }
    }
    // Render.
    for (auto camera : em.aspects<Camera>()) {
        log_render("Getting camera transform...");
        auto camera_transform = camera.sibling<Transform>();
        log_render("Calculating view-projection matrix...");
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        log_render("Uploading view-projection matrix...");
        shading_model_model_test->properties.set_mat4x4("vp_matrix", vp_matrix);

        log_render("Rendering Drawables:");
        for (auto drawable : em.aspects<Drawable>()) {
            log_render("  Rendering drawable with ID %u.", drawable.ID());
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
}

void World::keyboard_handler(KeyboardEvent e)
{
    for (auto b : em.aspects<Behaviour>()) {
        if (b->object->handling_keyboard) {
            b->object->keyboard_handler(e);
        }
    }
}
void World::mouse_handler(MouseEvent e)
{
    for (auto b : em.aspects<Behaviour>()) {
        if (b->object->handling_mouse) {
            b->object->mouse_handler(e);
        }
    }
}

