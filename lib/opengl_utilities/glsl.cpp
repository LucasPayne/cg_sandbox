/*--------------------------------------------------------------------------------
Global GLSL type information.
--------------------------------------------------------------------------------*/
#include "glsl.h"

#define TYPE
GLSLType GLSLType::glsl_types[] = {
    // The glsl type ID is the index into this array.
    // !-IMPORTANT-! Make sure the ID written here is correct.
    {0, "float", 4, 4},
    {1, "vec2", 8, 8},
    {2, "vec3", 16, 16},
    {3, "vec4", 16, 16},
    {4, "bool", 1, 1},
    {5, "int", 4, 4},
    {6, "mat4x4", 64, 16},
    {7, "mat3x3", 48, 16},
};
#undef TYPE


GLSLType GLSLType::from_name(const std::string &name) {
    for (GLSLType type : glsl_types) {
        if (strncmp(type.name, name.c_str(), MAX_GLSL_TYPE_NAME_LENGTH) == 0) return type;
    }
    fprintf(stderr, "ERROR: GLSL type \"%s\" doesn't exist or is not accounted for.\n", name.c_str());
    exit(EXIT_FAILURE);
}

GLSLType GLSLType::from_ID(GLSLTypeID id) {
    for (GLSLType type : glsl_types) {
        if (type.id == id) return type;
    }
    fprintf(stderr, "ERROR: GLSL type with ID \"%u\" doesn't exist.\n", id);
    exit(EXIT_FAILURE);
}
