interactive_graphics_context
----------------------------

This library allows the easy creation of a window with an OpenGL context.
Usage example:
    IGC::Context context("Window name");
Callbacks can be added to the context:
    context.add_callbacks(&obj);
where obj is of a class which derives from IGC::Callbacks, optionally overriding these methods:
    virtual void close() {}
    virtual void loop() {}
    virtual void keyboard_handler(KeyboardEvent e) {}
    virtual void mouse_handler(MouseEvent e) {}
    virtual void window_handler(WindowEvent e) {}
and finally, the loop can be entered:
    context.enter_loop();
and the context closed:
    context.close();

Input events:
Input events are routed from the selected back end into event structs, passed to the Callbacks objects added to the IGC::Context.
These structs contain input information, such as cursor position in a MouseEvent. See the input header for details.

Only one context can be active at a time, but another one can be started after closing the last one.

Supported back ends:
    glfw3
