/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.

BUGS:
PROBLEMS:
IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"


define_aspect(Transform)
    float position[3];
    float orientation[3];
    uint32_t flags;
end_define_aspect(Transform)

define_aspect(Camera)
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    float projection_matrix[16];
end_define_aspect(Camera)

define_aspect(Drawable)
    // GeometryInstance geometry_instance;
    // MaterialInstance material_instance;
end_define_aspect(Drawable)

void create_dude(EntityModel &em)
{
    Entity e = em.new_entity();
    Transform *t = em.add_aspect<Transform>(e);
    t->position[0] = 1;
    t->position[1] = 2;
    t->position[2] = 3;
    Drawable *d = em.add_aspect<Drawable>(e);
}

void CGSandbox::init()
{
    // parse_shading_file("resources/triangle_mesh.gmat");
    parse_shading_file("resources/test.gmat");
    getchar();

    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;

    Entity cameraman = em.new_entity();
    Camera *camera = em.add_aspect<Camera>(cameraman);
    camera->bottom_left[0] = 0;
    camera->bottom_left[1] = 0;
    camera->top_right[0] = 1;
    camera->top_right[1] = 1;
    Transform *camera_transform = em.add_aspect<Transform>(cameraman);
    camera_transform->position[0] = 0;
    camera_transform->position[1] = 0;
    camera_transform->position[2] = 0;

    for (int i = 0; i < 8; i++) create_dude(em);

}
void CGSandbox::close()
{
}


void CGSandbox::loop()
{
    // test_shading_dataflow();
    test_new_shading_program();
    getchar();

    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");
    EntityModel &em = entity_model;

    for (auto [camera, camera_transform] : em.aspects<Camera, Transform>()) {
        printf("Camera\n");
        printf("bottom left: %.2f %.2f\n", camera.bottom_left[0], camera.bottom_left[1]);
        printf("top right: %.2f %.2f\n", camera.top_right[0], camera.top_right[1]);

#if 0
        ShadingModelInstance sm_instance = new_sm_instance("color_shading");
        sm_instance.properties.set("vp_matrix", camera.vp_matrix);

        // Render with this camera.
        for (auto [drawable, transform] : em.aspects<Drawable, Transform>()) {
            printf("Drawable\n");

            // Constructor looks up precompiled shading program in cache, if its not there, it is created and cached.
            //-renamed Draw, rather than ShadingProgram, since that will be the instance-independent thing.
            Draw draw(drawable.geometry_instance,
                      drawable.material_instance,
                      sm_instance);
            // Binding the draw prepares the GPU pipeline for rendering with the G+M+SM.
            draw.bind();

            // Synchronize pipeline state with the properties.
            draw.upload_properties();

            // Draw. The Draw encapsulates one drawable geometry vertex array (in whatever format), pipelined through
            // the ShadingProgram associated to the Geometry, Material, and ShadingModel.
            draw.draw();
        }
#endif
    }
}

void CGSandbox::key_callback(int key, int action)
{
    EntityModel &em = entity_model;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
        }

        if (key == GLFW_KEY_K) {
            for (auto &t : em.aspects<Transform>()) {
                t.position[1] += 2.3;
            }
        }
        if (key == GLFW_KEY_C) {
            create_dude(em);
        }
        if (key == GLFW_KEY_M) {
            for (auto &t : em.aspects<Transform>()) {
                // if (frand() > 0.8) em.destroy_entity(t.entity);
                em.destroy_entity(t.entity);
                break;
            }
        }
        // This is broken!
        // if (key == GLFW_KEY_V) {
        //     for (auto &v : em.aspects<Velocity>()) {
        //         em.destroy_aspect(&v);
        //         break;
        //     }
        // }
    }
}
void CGSandbox::cursor_position_callback(double x, double y)
{
}
void CGSandbox::cursor_move_callback(double x, double y)
{
}
void CGSandbox::mouse_button_callback(int button, int action)
{
}
