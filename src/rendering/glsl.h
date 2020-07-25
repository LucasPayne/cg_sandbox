/*--------------------------------------------------------------------------------
This header file contains information about the GLSL language.
Global GLSL type information is defined in glsl.cpp.
--------------------------------------------------------------------------------*/
#ifndef RENDERING_GLSL_H
#define RENDERING_GLSL_H
#include "core.h"

//todo: Figure out a better way to declare global GLSL type information.
#define MAX_GLSL_TYPE_NAME_LENGTH 31
typedef uint8_t GLSLTypeID;
struct GLSLType {
    GLSLTypeID id;
    char name[MAX_GLSL_TYPE_NAME_LENGTH + 1];
    size_t size;
    size_t alignment; //std140 alignment

    // All glsl types are defined in a global array. This holds information the application might need
    // about a glsl type.
    static GLSLType glsl_types[6]; //!-IMPORTANT-! Make this the correct length.
    static inline GLSLType from_name(const std::string &name) {
        for (GLSLType type : glsl_types) {
            if (strncmp(type.name, name.c_str(), MAX_GLSL_TYPE_NAME_LENGTH) == 0) return type;
        }
        fprintf(stderr, "ERROR: GLSL type \"%s\" doesn't exist or is not accounted for.\n", name.c_str());
        exit(EXIT_FAILURE);
    };
    static inline GLSLType from_ID(GLSLTypeID id) {
        for (GLSLType type : glsl_types) {
            if (type.id == id) return type;
        }
        fprintf(stderr, "ERROR: GLSL type with ID \"%u\" doesn't exist.\n", id);
        exit(EXIT_FAILURE);
    };
};

#endif // RENDERING_GLSL_H
