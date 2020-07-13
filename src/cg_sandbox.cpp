/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"
#include "entity_model/entity_model.h"

define_aspect(Velocity)
    float velocity[3];
end_define_aspect(Velocity)

define_aspect(Transform)
    float position[3];
    float orientation[3];
    uint32_t flags;
end_define_aspect(Transform)

void CGSandbox::init()
{
    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;

    for (int i = 0; i < 10; i++) {
        Entity e = em.new_entity();
        Transform *t = em.add_aspect<Transform>(e);
        t->position[0] = 1;
        t->position[1] = 2;
        t->position[2] = 3;
        if (frand() > 0.5) {
            Velocity *v = em.add_aspect<Velocity>(e);
            v->velocity[0] = 1;
            v->velocity[1] = -1;
            v->velocity[2] = 0.5;
        }
    }
}
void CGSandbox::close()
{
}
void CGSandbox::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");
    EntityModel &em = entity_model;

    for (auto &t : em.aspects<Transform>()) {
        printf("position: %.2f, %.2f, %.2f\n", t.position[0], t.position[1], t.position[2]);
    }
    for (auto &v : em.aspects<Velocity>()) {
        Transform *t = em.try_get_sibling_aspect<Transform>(&v);
        if (t != nullptr) {
            for (int i = 0; i < 3; i++) {
                t->position[i] += v.velocity[i] * dt;
            }
        }
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
        if (key == GLFW_KEY_M) {
            for (auto &t : em.aspects<Transform>()) {
                if (frand() > 0.8) em.destroy_entity(t.entity);
            }
        }
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
