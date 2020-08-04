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
#include "rendering/rendering.h"
#include "world/standard_aspects/standard_aspects.h"
#include "interactive_graphics_context/interactive_graphics_context.h"
#include <math.h>

Table<GenericTable> g_table_registry(Table<GenericTable>(1)); // Static initialization, prepare global table registry.

static TableHandle init_world_table() {
    TableHandle world_table_handle = g_table_registry.add();
    GenericTable *world_table = g_table_registry.lookup(world_table_handle);
    *world_table = GenericTable(sizeof(World), 1);
    return world_table_handle;
}
TableHandle World::table(init_world_table()); // Statically initialize the global World table in the global table registry.

ShadingModelInstance *shading_model_model_test;

Reference<World> World::new_world()
{
    TableHandle table_handle = g_table_registry.lookup(table).add();
    World &world = *reinterpret_cast<World *>(g_table_registry.lookup(table).lookup(table_handle));
    world.ref = Reference<World>(table, table_handle, 

    WorldHandle world_handle = table.add();
    World &world = *table.lookup(world_handle);
    world.handle = world_handle;

    // Initialize the resource model.
    world.rm = ResourceModel();
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) world.rm.register_resource_type<NAME>(#NAME)
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);

    // Initialize the entity model, with no entities.
    world.em = EntityModel(); 
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) world.em.register_aspect_type<NAME>(#NAME)
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);
    REGISTER_ASPECT_TYPE(Behaviour);

    // Initialize an instance of Assets, through which hard-coded specific assets can be loaded and shared using the resource model.
    world.assets = Assets();
    world.assets.rm = &world.rm;
    world.assets.models.rm = &world.rm;
    world.assets.shading.rm = &world.rm;

    // Initialize the Graphics component, which holds graphics state, such as compiled shader programs.
    world.graphics = Graphics();
    world.graphics.rm = &world.rm; // The Graphics component relies on the resource model.

    glDisable(GL_CULL_FACE); //
    glEnable(GL_DEPTH_TEST); // todo: Remove this.
    glDepthFunc(GL_LESS);    //

    // Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/model_test/model_test.sm");
    Resource<ShadingModel> sm = world.rm.new_resource<ShadingModel>();
    std::fstream sm_file;
    sm_file.open("resources/model_test/model_test.sm");
    sm->load(sm_file);
    shading_model_model_test = new ShadingModelInstance(sm); // create a global shading model instance for testing.

    // Input.
    world.input = InputState();
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
    for (Behaviour *b : em.aspects<Behaviour>()) {
        if (b->object->updating) {
            b->object->update();
        }
    }
    // Render.
    for (Camera *camera : em.aspects<Camera>()) {
        Transform *camera_transform = em.get_sibling<Transform>(camera);
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        shading_model_model_test->properties.set_mat4x4("vp_matrix", vp_matrix);

        for (Drawable *drawable : em.aspects<Drawable>()) {
            Transform *t = em.get_sibling<Transform>(drawable);
            mat4x4 model_matrix = t->matrix();
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);

            graphics.draw(drawable->geometric_material, drawable->material, *shading_model_model_test);
        }
    }
}

void World::keyboard_handler(KeyboardEvent e)
{
    for (Behaviour *b : em.aspects<Behaviour>()) {
        if (b->object->handling_keyboard) {
            b->object->keyboard_handler(e);
        }
    }
}
void World::mouse_handler(MouseEvent e)
{
    for (Behaviour *b : em.aspects<Behaviour>()) {
        if (b->object->handling_mouse) {
            b->object->mouse_handler(e);
        }
    }
}
