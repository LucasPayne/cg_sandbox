#include "core.h"
#include "gl.h"

class CGSLooper : public Looper, public InputListener {
    void loop();
    void key_callback(int key, int action);
    void cursor_position_callback(double x, double y);
    void cursor_move_callback(double x, double y);
    void mouse_button_callback(int button, int action);
};
void CGSLooper::loop()
{
}
void CGSLooper::key_callback(int key, int action)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
        }
    }
}
void CGSLooper::cursor_position_callback(double x, double y)
{

}
void CGSLooper::cursor_move_callback(double x, double y)
{

}
void CGSLooper::mouse_button_callback(int button, int action)
{

}

// Force the application to its constant-aspect-ratio subrectangle of the actual viewport.
void force_aspect_ratio(int width, int height, double wanted_aspect_ratio)
{
    double aspect_ratio = ((double) height) / width;
    if (aspect_ratio > wanted_aspect_ratio) {
        glViewport(0, (height - wanted_aspect_ratio * width)/2.0, width, wanted_aspect_ratio * width);
    }
    else {
        glViewport((width - height / wanted_aspect_ratio)/2.0, 0, height / wanted_aspect_ratio,  height);
    }
}
void reshape(int width, int height)
{
    float aspect_ratio = 0.566;
    force_aspect_ratio(width, height, aspect_ratio);
}

int main(int argc, char *argv[])
{
    int window_width = 512;
    int window_height = 512;
    OpenGLContext context("cg_sandbox", window_width, window_height);
    context.set_bg_color(0,0,0.3,1);
    context.set_fg_color(1,0.9,0.96,1);
    context.open();

    // The CGSLooper (CGS standing for computer graphics sandbox) is the main entry point
    // for application behaviour. It derives from two classes, providing a per-frame loop function
    // and event callbacks.
    CGSLooper *loop = new CGSLooper();
    loop->listening = true;
    context.add_looper(loop);
    context.add_input_listener(loop);
    context.add_reshape_callback(reshape);

    context.enter_loop();
    context.close();
}
