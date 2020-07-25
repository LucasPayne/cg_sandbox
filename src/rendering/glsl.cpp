/*--------------------------------------------------------------------------------
Global GLSL type information.
--------------------------------------------------------------------------------*/
#include "rendering/glsl.h"

#define TYPE
GLSLType GLSLType::glsl_types[] = {
    // The glsl type ID is the index into this array.
    // !-IMPORTANT-! Make sure the ID written here is correct.
    {0, "float", 4, 4},
    {1, "vec2", 8, 8},
    {2, "vec3", 12, 16},
    {3, "vec4", 16, 16},
    {4, "bool", 1, 1},
    {5, "int", 4, 4},
    {6, "mat4x4", 64, 16},
};
#undef TYPE
