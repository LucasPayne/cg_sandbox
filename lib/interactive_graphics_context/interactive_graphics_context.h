#ifndef INTERACTIVE_GRAPHICS_CONTEXT_H
#define INTERACTIVE_GRAPHICS_CONTEXT_H
#include <string>
#include <vector>

#include "input.h"
enum WindowEventTypes {
    WINDOW_EVENT_FRAMEBUFFER_SIZE,
};
struct WindowEvent {
    uint8_t type;
    struct {
        uint16_t width;
        uint16_t height;
    } framebuffer;
};

// Global time information.
// It is very convenient to be able to access these from anywhere.
extern float total_time;
extern float dt;

namespace IGC {

namespace Platform {
    typedef void *WindowReference;
    WindowReference create_window(const std::string &name);
    bool poll(WindowReference window); // Returns false if the platform is terminating.
    void present(WindowReference window);
    void close(WindowReference window);
    float time();
} // end namespace Platform


class Callbacks
{
public:
    virtual void close() {}
    virtual void loop() {}
    virtual void keyboard_handler(KeyboardEvent e) {}
    virtual void mouse_handler(MouseEvent e) {}
    virtual void window_handler(WindowEvent e) {}
};

class Context
{
public:
    Context(const std::string &name);

    void add_callbacks(Callbacks &callbacks);
    void enter_loop();
    void close();

    static void keyboard_event(KeyboardEvent e);
    static void mouse_event(MouseEvent e);
    static void window_event(WindowEvent e);
    std::vector<Callbacks *> m_callbacks;

    inline float time() { return m_time; }
    inline float delta_time() { return m_delta_time; }
private:
    float m_time;
    float m_delta_time;
    Platform::WindowReference window;
};


} // end namespace IGC
#endif // INTERACTIVE_GRAPHICS_CONTEXT_H
