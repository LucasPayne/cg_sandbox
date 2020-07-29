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
#include "input/input.h"
#include <math.h>

ShadingModelInstance *shading_model_model_test;

World::World()
{
    // Initialize the resource model.
    rm = ResourceModel();
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) rm.register_resource_type<NAME>(#NAME)
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);

    // Initialize the entity model, with no entities.
    em = EntityModel(); 
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) em.register_aspect_type<NAME>(#NAME)
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);
    REGISTER_ASPECT_TYPE(Behaviour);

    // Initialize an instance of Assets, through which hard-coded specific assets can be loaded and shared using the resource model.
    assets = Assets();
    assets.rm = &rm;

    // Initialize the Graphics component, which holds graphics state, such as compiled shader programs.
    graphics = Graphics();
    graphics.rm = &rm; // The Graphics component relies on the resource model.

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/model_test/model_test.sm");
    // shading_model_model_test = new ShadingModelInstance(sm); // create a global shading model instance for testing.
}
void World::close()
{
}

void World::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

    for (Behaviour *b : em.aspects<Behaviour>()) {
        if (b->object->updating) {
            b->object->update();
        }
    }

    for (Camera *camera : em.aspects<Camera>()) {
        Transform *camera_transform = em.get_sibling<Transform>(camera);
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        // printf("vp_matrix\n");
        // std::cout << vp_matrix << "\n";
        shading_model_model_test->properties.set_mat4x4("vp_matrix", vp_matrix);

        for (Drawable *drawable : em.aspects<Drawable>()) {
            Transform *t = em.get_sibling<Transform>(drawable);
            mat4x4 model_matrix = t->matrix();
            // printf("model_matrix\n");
            // std::cout << model_matrix << "\n";
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);

            graphics.draw(drawable->geometric_material, drawable->material, *shading_model_model_test);
        }
    }
}

void World::keyboard_handler(KeyboardEvent e)
{
    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
        }
    }
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
