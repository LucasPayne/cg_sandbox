// References:
//    http://amesgames.net/2017/06/27/c-rendering-engine-i-abstracting-the-render-device/3/
#include "interactive_graphics_context.h"

float total_time = 0;
float dt = 0;

namespace IGC {

// Input events generated by the platform code need to be dispatched to the active Context,
// which is made globally available. These *_event functions are the entry point for input, and are
// called by platform code.
Context *active_context = nullptr;

void Context::keyboard_event(KeyboardEvent e)
{
   for (Callbacks *callbacks : active_context->m_callbacks) {
       callbacks->keyboard_handler(e);
   }
}
void Context::mouse_event(MouseEvent e)
{
    for (Callbacks *callbacks : active_context->m_callbacks) {
        callbacks->mouse_handler(e);
    }
}
void Context::window_event(WindowEvent e)
{
    for (Callbacks *callbacks : active_context->m_callbacks) {
        callbacks->window_handler(e);
    }
}

Context::Context(const std::string &name)
{
    if (active_context != nullptr) {
        fprintf(stderr, "interactive_graphics_context error: Only one Context can be active at a time.\n");
        exit(EXIT_FAILURE);
    }
    active_context = this;
    window = Platform::create_window(name);
}

void Context::add_callbacks(Callbacks &callbacks)
{
    m_callbacks.push_back(&callbacks);
}

void Context::enter_loop()
{
    m_delta_time = 0;
    m_time = Platform::time();

    while (Platform::poll(window)) {
        float time_now = Platform::time();
        m_delta_time = time_now - m_time;
        m_time = time_now;
        // Make time information globally available.
        total_time = time();
        dt = delta_time();
        for (Callbacks *callbacks : m_callbacks) {
            callbacks->loop();
        }
        Platform::present(window);
    }
    close();
}

void Context::close()
{
    active_context = nullptr;
}


} // end namespace IGC

