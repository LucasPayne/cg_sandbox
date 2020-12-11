/*--------------------------------------------------------------------------------
    GLFW platform code. This routes GLFW events into the *_event functions,
    and implements the interface in namespace IGC::Platform.
--------------------------------------------------------------------------------*/
#include "interactive_graphics_context.h"
#include <iostream>
#include "opengl_utilities/gl.h"
#include "glfw/include/GLFW/glfw3.h"
namespace IGC {
namespace Platform {


void enable_raw_mouse(WindowReference window)
{
    glfwSetInputMode((GLFWwindow *) window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void disable_raw_mouse(WindowReference window)
{
    glfwSetInputMode((GLFWwindow *) window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void get_screen_size(WindowReference window, int *width, int *height)
{
    glfwGetWindowSize((GLFWwindow *) window, width, height);
}


void close(WindowReference window)
{
    glfwTerminate();
    glfwDestroyWindow((GLFWwindow *) window);
}


bool poll(WindowReference window)
{
    if (glfwWindowShouldClose((GLFWwindow *) window)) return false;
    glfwPollEvents();
    return true;
}


void present(WindowReference window)
{
    glFlush();
    glfwSwapBuffers((GLFWwindow *) window);
}


float time()
{
    return (float) glfwGetTime();
}



static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    WindowEvent e;
    e.type = WINDOW_EVENT_FRAMEBUFFER_SIZE;
    e.framebuffer.width = width;
    e.framebuffer.height = height;
    Context::window_event(e);
}


static int glfw_keycode_to_keycode(int key)
{
    switch (key) {
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


void glfw_key_callback(GLFWwindow *window, int key,
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
    Context::keyboard_event(e);
}

static CursorState g_cursor = { 0 };
static bool g_cursor_initialized = false;

void glfw_cursor_position_callback(GLFWwindow *window, double window_x, double window_y)
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

    Context::mouse_event(e);
}


void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
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
    Context::mouse_event(e);
}


void glfw_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    MouseEvent e;
    e.action = MOUSE_SCROLL;
    e.scroll_y = y_offset;
    Context::mouse_event(e);
}



WindowReference create_window(const std::string &name)
{
    if (!glfwInit()) {
        std::cerr <<  "GLFW error: Something went wrong initializing GLFW.\n";
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *glfw_window = glfwCreateWindow(800, 600, name.c_str(), NULL, NULL);
    if (glfw_window == nullptr) {
        std::cerr << "GLFW error: Failed to create a window properly.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(glfw_window);
    gladLoadGL();
    glfwSwapInterval(1);

    // Input and event callbacks.
    glfwSetKeyCallback(glfw_window, glfw_key_callback);
    glfwSetMouseButtonCallback(glfw_window, glfw_mouse_button_callback);
    glfwSetCursorPosCallback(glfw_window, glfw_cursor_position_callback);
    glfwSetScrollCallback(glfw_window, glfw_scroll_callback);
    glfwSetFramebufferSizeCallback(glfw_window, glfw_framebuffer_size_callback);

    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    // int flags;
    // glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    // if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
    //     printf("Failed to create debug context.\n");
    //     exit(EXIT_FAILURE);
    // }

    return (WindowReference) glfw_window;
}

} // end namespace Platform
} // end namespace IGC
