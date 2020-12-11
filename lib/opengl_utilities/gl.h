#ifndef HEADER_DEFINED_GL_H
#define HEADER_DEFINED_GL_H

#include <string>
#include <iostream>

#include "the_glad/glad.h"
// Debugging
std::string gl_error_string(GLenum err);
void gl_check_error(const char *file, int line);
#include "glad_debug_wrappers.h"

#include "gl_shader_program.h"
#include "glsl.h"


#endif // HEADER_DEFINED_GL_H
