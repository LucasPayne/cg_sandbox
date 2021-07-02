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
    void enable_raw_mouse(WindowReference window);
    void disable_raw_mouse(WindowReference window);
    void get_screen_size(WindowReference window, int *width, int *height);
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

    void add_callbacks(Callbacks *callbacks);
    void enter_loop();
    void enable_raw_mouse();
    void disable_raw_mouse();
    void close();
    void get_screen_size(int *width, int *height);

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

/*--------------------------------------------------------------------------------
Callbacks for input state tracking. Add these to the active Context to track
--------------------------------------------------------------------------------*/
struct KeyboardState {
    // Each key has bit-flags to signify its state.
    // Starting with the least significant bit:
    //    Bit 0:  0:down    1:up
    // todo:
    //    Bit 1:  1 signifies the key became pressed one "input-cycle" ago (whatever manages the InputState handles this).
    //    Bit 2:  Same as above but for when the key is released.
    uint8_t key_flags[KEYBOARD_NUM_KEYS];
    bool down(KeyboardKeyCode code) const;
};
struct MouseState {
    uint8_t button_flags[MOUSE_NUM_BUTTONS];
    bool down(MouseButtonCode code) const;
};

// InputState listens to input events and tracks state, such as keys that are held down.
struct InputState : public IGC::Callbacks {
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    KeyboardState keyboard;
    MouseState mouse;
};

#endif // INTERACTIVE_GRAPHICS_CONTEXT_H
