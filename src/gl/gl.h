#ifndef GL_CORE_H
#define GL_CORE_H
// Everything using the OpenGL/GLFW classes should include this.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core.h"
#include "input/input.h"

// The active OpenGLContext updates these global values.
// This is for convenience, so that having things with time-dependence doesn't require
// passing the context around everywhere.
extern float total_time;
extern float dt;

// typedef void (*KeyCallback)(int key, int action);
// typedef void (*CursorPositionCallback)(double x, double y);
// typedef void (*MouseButtonCallback)(int button, int action);

typedef void (*ReshapeCallback)(int width, int height);
typedef void (*KeyboardHandler)(KeyboardEvent);
typedef void (*MouseHandler)(MouseEvent);

class InputListener {
private:
public:
    bool listening;
    virtual void keyboard_handler(KeyboardEvent e) {}
    virtual void mouse_handler(MouseEvent e) {}

    // virtual void key_callback(int key, int action) {}
    // virtual void cursor_position_callback(double x, double y) {}
    // virtual void cursor_move_callback(double x, double y) {}
    // virtual void mouse_button_callback(int button, int action) {}
};

// A Looper can encapsulate its own data, so is a sort of parameterized function.
// The OpenGLContext holds a list of these.
struct Looper {
    Looper () {}
    virtual void loop() = 0;
    virtual void init() {};
    virtual void close() {};
};

class OpenGLContext {
private:
    // It would not make sense to give glfw a pointer to a member function of a class.
    // glfw will instead have these as callbacks, which pass the events to the callbacks of the active context.
    static void glfw_reshape(GLFWwindow *window, int width, int height);
    static void glfw_key_callback(GLFWwindow *window, int key,
                           int scancode, int action,
                           int mods);
    static void glfw_cursor_position_callback(GLFWwindow *window, double x, double y);
    static void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    // These callbacks are just function pointers, so cannot be associated to objects with data.
    std::vector<KeyboardHandler> m_keyboard_handlers;
    std::vector<MouseHandler> m_mouse_handlers;
    // A class derived from InputListener implements callback functions, so can have data, etc.
    std::vector<InputListener *> m_input_listeners;

    std::vector<ReshapeCallback> m_reshape_callbacks;
    std::vector<Looper *> m_loopers;

    int m_initial_resolution_x;
    int m_initial_resolution_y;
    int m_window_width;
    int m_window_height;
    float bg_color[4]; // Overall window clear color.
    float fg_color[4]; // Subrectangle clear color.

    // GLFW state.
    GLFWwindow *m_glfw_window;
    std::string m_glfw_window_name;
    float m_time;
    float m_dt;
    float m_last_time; // Used to compute m_dt.
public:
    OpenGLContext() {}
    OpenGLContext(std::string const &window_name, int res_x = 512, int res_y = 512) :
        m_glfw_window_name(window_name)
    {
        set_bg_color(0,0,0,1);
        set_fg_color(1,1,1,1);
        m_initial_resolution_x = res_x;
        m_initial_resolution_y = res_y;
        m_window_width = res_x;
        m_window_height = res_x;
        m_time = 0;
        m_dt = 0;
        m_last_time = 0;
    }

    void open();
    void close();
    void enter_loop();

    InputListener *add_input_listener(InputListener *input_listener) {
        m_input_listeners.push_back(input_listener);
        return input_listener;
    }

    ReshapeCallback add_reshape_callback(ReshapeCallback callback) {
        m_reshape_callbacks.push_back(callback);
        return callback;
    }

    Looper *add_looper(Looper *looper) {
        m_loopers.push_back(looper);
        looper->init();
        return looper;
    }
    inline int window_width() const { return m_window_width; }
    inline int window_height() const { return m_window_height; }
    void set_bg_color(float r, float g, float b, float a) {
        bg_color[0] = r;
        bg_color[1] = g;
        bg_color[2] = b;
        bg_color[3] = a;
    }
    void set_fg_color(float r, float g, float b, float a) {
        fg_color[0] = r;
        fg_color[1] = g;
        fg_color[2] = b;
        fg_color[3] = a;
    }
};

// There can only be one.
extern bool g_context_active;
extern OpenGLContext *g_opengl_context;

#include "gl/gl_shader_program.h"
#include "gl/gl_input.h"

#endif // GL_CORE_H
