/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"

void CGSandbox::loop()
{

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
