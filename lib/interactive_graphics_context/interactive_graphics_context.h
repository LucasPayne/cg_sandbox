#ifndef INTERACTIVE_GRAPHICS_CONTEXT_H
#define INTERACTIVE_GRAPHICS_CONTEXT_H
#include <string>
#include <vector>
#include "input.h"
namespace IGC {

namespace Platform {
    typedef void *WindowReference;
    WindowReference create_window(const std::string &name);
    
    void close_window(WindowReference window);
} // end namespace Platform


class Callbacks
{
public:
    virtual void close() {}
    virtual void loop() {}
    virtual void keyboard_handler(KeyboardEvent e) {}
    virtual void mouse_handler(MouseEvent e) {}
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
    std::vector<Callbacks *> m_callbacks;
private:
};


} // end namespace IGC
#endif // INTERACTIVE_GRAPHICS_CONTEXT_H
