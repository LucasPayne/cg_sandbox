/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"
#include "entity_model/entity_model.h"

#define TESTING 1
#if TESTING == 1
#include "cg_sandbox_testing.cpp"
#endif

void CGSandbox::init()
{
    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 

    // Run initialization testing/debugging code, if there is any.
    #if TESTING == 1
    test_init();
    #endif
}
void CGSandbox::close()
{
}
void CGSandbox::loop()
{
    #if TESTING == 1
    test_loop();
    #endif
}

void CGSandbox::key_callback(int key, int action)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
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
