#include "core.h"
#include "gl.h"

class CGSLooper : public Looper {
    void loop();
};
void CGSLooper::loop() {
    printf("duuude\n");
}

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
    context.open();

    CGSLooper *loop = new CGSLooper();
    context.add_looper(loop);
    // context.add_input_listener(viewer_loop);
    context.add_reshape_callback(reshape);

    // rendering_thread = std::thread(rendering_thread_function, renderer);

    context.enter_loop();
    context.close();
}

