/*--------------------------------------------------------------------------------
    Program entry point. This initializes the context, starts a sandbox
    (with loop and input event entry points), and does some other things.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"

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

    // The CGSandbox is the main entry point for application behaviour.
    // It derives from two classes, providing a per-frame loop function and event callbacks.
    CGSandbox cgs = CGSandbox();
    cgs.listening = true;
    context.add_looper(&cgs);
    context.add_input_listener(&cgs);
    context.add_reshape_callback(reshape);

    context.enter_loop();
    context.close();
}
