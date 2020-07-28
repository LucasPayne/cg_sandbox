#include "gl.h"
#include "input/input.h"

float total_time;
float dt;

bool g_context_active = false;
OpenGLContext *g_opengl_context = NULL;

void OpenGLContext::open()
{
    if (g_context_active) {
        std::cerr <<  "ERROR: Only one OpenGL context can be open at a time!\n";
        exit(EXIT_FAILURE);
    }
    if (!glfwInit()) {
        std::cerr <<  "GLFW error: Something went wrong initializing GLFW.\n";
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfw_window = glfwCreateWindow(m_initial_resolution_x, m_initial_resolution_y, m_glfw_window_name.c_str(), NULL, NULL);
    if (m_glfw_window == NULL) {
        std::cerr << "GLFW error: Failed to create a window properly.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_glfw_window);
    gladLoadGL(); //------
    glfwSwapInterval(1);

    // Input and event callbacks.
    glfwSetKeyCallback(m_glfw_window, glfw_key_callback);
    glfwSetMouseButtonCallback(m_glfw_window, glfw_mouse_button_callback);
    glfwSetCursorPosCallback(m_glfw_window, glfw_cursor_position_callback);
    glfwSetFramebufferSizeCallback(m_glfw_window, glfw_reshape);

    g_context_active = true;
    g_opengl_context = this;
}
void OpenGLContext::close()
{
    if (!g_context_active) {
        //- This check does not guarantee that the closed context is the currently open context.
        std::cerr <<  "ERROR: Tried to close OpenGLContext, none is open!\n";
        exit(EXIT_FAILURE);
    }
    for (Looper *looper : m_loopers) {
        looper->close();
    }
    glfwTerminate();
    glfwDestroyWindow(m_glfw_window);
    g_context_active = false;
}
void OpenGLContext::enter_loop()
{
    while (!glfwWindowShouldClose(m_glfw_window))
    {
        glfwPollEvents();

        m_last_time = m_time;
        m_time = glfwGetTime();
        m_dt = m_time - m_last_time;

        // Set the globals for convenience (there is only ever one context anyway).
        dt = m_dt;
        total_time = m_time;

        // Clearing: window clear to background color, viewport clear to the foreground color.
        glClearColor(bg_color[0],bg_color[1],bg_color[2],bg_color[3]);
        glDisable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glEnable(GL_SCISSOR_TEST);
        glScissor(viewport[0], viewport[1], viewport[2], viewport[3]);
        glClearColor(fg_color[0],fg_color[1],fg_color[2],fg_color[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);


        for (Looper *looper : m_loopers) {
            looper->loop();
        }

        glFlush();
        glfwSwapBuffers(m_glfw_window);
    }
}

void OpenGLContext::glfw_reshape(GLFWwindow *window, int width, int height)
{
    g_opengl_context->m_window_width = width;
    g_opengl_context->m_window_height = height;
    for (const ReshapeCallback &cb : g_opengl_context->m_reshape_callbacks) {
        cb(width, height);
    }
}

static int glfw_keycode_to_keycode(int key)
{
    switch (key) {
        // todo: Possibly GLFW has these correspond to keycodes anyway, and could just check some ranges.
        case GLFW_KEY_Q: return KEY_Q;
        case GLFW_KEY_W: return KEY_W;
        case GLFW_KEY_E: return KEY_E;
        case GLFW_KEY_R: return KEY_R;
        case GLFW_KEY_T: return KEY_T;
        case GLFW_KEY_Y: return KEY_Y;
        case GLFW_KEY_U: return KEY_U;
        case GLFW_KEY_I: return KEY_I;
        case GLFW_KEY_O: return KEY_O;
        case GLFW_KEY_P: return KEY_P;
        case GLFW_KEY_A: return KEY_A;
        case GLFW_KEY_S: return KEY_S;
        case GLFW_KEY_D: return KEY_D;
        case GLFW_KEY_F: return KEY_F;
        case GLFW_KEY_G: return KEY_G;
        case GLFW_KEY_H: return KEY_H;
        case GLFW_KEY_J: return KEY_J;
        case GLFW_KEY_K: return KEY_K;
        case GLFW_KEY_L: return KEY_L;
        case GLFW_KEY_Z: return KEY_Z;
        case GLFW_KEY_X: return KEY_X;
        case GLFW_KEY_C: return KEY_C;
        case GLFW_KEY_V: return KEY_V;
        case GLFW_KEY_B: return KEY_B;
        case GLFW_KEY_N: return KEY_N;
        case GLFW_KEY_M: return KEY_M;
        case GLFW_KEY_UP: return KEY_UP_ARROW;
        case GLFW_KEY_DOWN: return KEY_DOWN_ARROW;
        case GLFW_KEY_LEFT: return KEY_LEFT_ARROW;
        case GLFW_KEY_RIGHT: return KEY_RIGHT_ARROW;
        case GLFW_KEY_LEFT_SHIFT: return KEY_LEFT_SHIFT;
        case GLFW_KEY_RIGHT_SHIFT: return KEY_RIGHT_SHIFT;
        case GLFW_KEY_SPACE: return KEY_SPACE;
    }
    return EOF;
}

void OpenGLContext::glfw_key_callback(GLFWwindow *window, int key,
                       int scancode, int action,
                       int mods)
{
    KeyboardEvent e;
    int c;
    if ((c = glfw_keycode_to_keycode(key)) == EOF) return;
    e.key.code = (KeyboardKeyCode) c;
    
    if (action == GLFW_PRESS) {
        e.action = KEYBOARD_PRESS;
    } else if (action == GLFW_RELEASE) {
        e.action = KEYBOARD_RELEASE;
    } else {
        return; // Action not handled, no-op.
    }
    for (InputListener *il : g_opengl_context->m_input_listeners) {
        il->keyboard_handler(e);
    }
}

static CursorState g_cursor = { 0 };
static bool g_cursor_initialized = false;
void OpenGLContext::glfw_cursor_position_callback(GLFWwindow *window, double window_x, double window_y)
{
    // Convert to more meaningful coordinates, (0,0) bottom left corner of viewport, (1,1) top right.
    GLint viewport[4]; //x,y,width,height
    glGetIntegerv(GL_VIEWPORT, viewport);
    float x = (window_x - viewport[0]) / (1.0 * viewport[2]);
    float y = 1 - (window_y - viewport[1]) / (1.0 * viewport[3]);

    if (!g_cursor_initialized) {
        g_cursor.x = x;
        g_cursor.x = y;
        g_cursor_initialized = true;
    }
    g_cursor.dx = x - g_cursor.x;
    g_cursor.dy = y - g_cursor.y;
    g_cursor.x = x;
    g_cursor.y = y;

    MouseEvent e;
    e.action = MOUSE_MOVE;
    e.cursor = g_cursor;

    for (InputListener *il : g_opengl_context->m_input_listeners) {
        il->mouse_handler(e);
    }
}
void OpenGLContext::glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    MouseEvent e;
    switch (action) {
        case GLFW_PRESS: e.action = MOUSE_BUTTON_PRESS; break;
        case GLFW_RELEASE: e.action = MOUSE_BUTTON_RELEASE; break;
        default:
            return; // Action not accounted for, no-op.
    }
    if (action == GLFW_PRESS) e.action = MOUSE_BUTTON_PRESS;
    else if (action == GLFW_PRESS) e.action = MOUSE_BUTTON_PRESS;
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: e.button.code = MOUSE_LEFT; break;
        case GLFW_MOUSE_BUTTON_RIGHT: e.button.code = MOUSE_RIGHT; break;
        case GLFW_MOUSE_BUTTON_MIDDLE: e.button.code = MOUSE_MIDDLE; break;
        default:
            return; // Button not accounted for, no-op.
    }
    e.cursor = g_cursor;

    for (InputListener *il : g_opengl_context->m_input_listeners) {
        il->mouse_handler(e);
    }
}
