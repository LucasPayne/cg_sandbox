#ifndef HEADER_DEFINED_GL_H
#define HEADER_DEFINED_GL_H

#include <string>
#include <iostream>

#include "glad/glad.h"
// Debugging
std::string gl_error_string(GLenum err);
void gl_check_error(const char *file, int line);
#include "glad_debug_wrappers.h"
#include "gl_shader_program.h"
#include "glsl.h"


//----------todo: Move these. These are more specifically to do with cg_sandbox.
struct Framebuffer {
    GLuint id;
    int resolution_x;
    int resolution_y;
    GLuint texture;
    GLuint depth_texture; // if applicable

    // // Logical framebuffer extents.
    // GLint x;
    // GLint y;
    // GLsizei w;
    // GLsizei h;
};
std::ostream &operator<<(std::ostream &os, Framebuffer framebuffer);

// Macro for expanding a viewport into glViewport and glScissor parameters.
#define VIEWPORT_EXPAND(VIEWPORT) ( VIEWPORT ).x, ( VIEWPORT ).y, ( VIEWPORT ).w, ( VIEWPORT ).h
struct Viewport {
    Framebuffer *framebuffer;
    GLint x;
    GLint y;
    GLsizei w;
    GLsizei h;
    Viewport(Framebuffer &_framebuffer, int _x, int _y, int _w, int _h) :
        framebuffer{&_framebuffer}, x{(GLint) _x}, y{(GLint) _y}, w{(GLsizei) _w}, h{(GLsizei) _h}
    {}
    Viewport(int _x, int _y, int _w, int _h) :
        framebuffer{nullptr}, x{(GLint) _x}, y{(GLint) _y}, w{(GLsizei) _w}, h{(GLsizei) _h}
    {}
    Viewport() {}
};
std::ostream &operator<<(std::ostream &os, Viewport viewport);

#endif // HEADER_DEFINED_GL_H
