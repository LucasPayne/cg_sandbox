/*--------------------------------------------------------------------------------
This header file contains information about the GLSL language.
Global GLSL type information is defined in glsl.cpp.
--------------------------------------------------------------------------------*/
#ifndef GL_GLSL_H
#define GL_GLSL_H
#include <string>
#include <string.h>

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
    static GLSLType glsl_types[8]; //!-IMPORTANT-! Make this the correct length.
    static GLSLType from_name(const std::string &name);
    static GLSLType from_ID(GLSLTypeID id);
};

#endif // GL_GLSL_H
