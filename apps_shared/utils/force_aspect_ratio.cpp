
void force_aspect_ratio(WindowEvent e)
{
    float wanted_aspect_ratio = 0.566;
    if (e.type == WINDOW_EVENT_FRAMEBUFFER_SIZE) {
        float width = e.framebuffer.width;
        float height = e.framebuffer.height;
        double aspect_ratio = ((double) height) / width;
        if (aspect_ratio > wanted_aspect_ratio) {
            glViewport(0, (height - wanted_aspect_ratio * width)/2.0, width, wanted_aspect_ratio * width);
        }
        else {
            glViewport((width - height / wanted_aspect_ratio)/2.0, 0, height / wanted_aspect_ratio,  height);
        }
    }
}
