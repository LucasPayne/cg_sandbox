/*--------------------------------------------------------------------------------
Global GLSL type information.
--------------------------------------------------------------------------------*/
#include "gl.h"

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


//--------
std::string gl_error_string(GLenum err)
{
    switch(err) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
    }
    return "UNKNOWN";
}

void gl_check_error(const char *file, int line)
{
    GLenum err;
    bool fatal = false;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << gl_error_string(err) << " OpenGL error in file\n";
        printf("    %s\n", file);
        std::cout << "at line " << std::to_string(line) << ".\n";
        fatal = true;
    }
    if (fatal) {
        exit(EXIT_FAILURE);
    }
}


// glad debug wrappers
void _glCullFace(GLenum mode, const char * _file, int _line) {
    glad_glCullFace(mode);
    gl_check_error(_file, _line);
}


void _glFrontFace(GLenum mode, const char * _file, int _line) {
    glad_glFrontFace(mode);
    gl_check_error(_file, _line);
}


void _glHint(GLenum target, GLenum mode, const char * _file, int _line) {
    glad_glHint(target, mode);
    gl_check_error(_file, _line);
}


void _glLineWidth(GLfloat width, const char * _file, int _line) {
    glad_glLineWidth(width);
    gl_check_error(_file, _line);
}


void _glPointSize(GLfloat size, const char * _file, int _line) {
    glad_glPointSize(size);
    gl_check_error(_file, _line);
}


void _glPolygonMode(GLenum face, GLenum mode, const char * _file, int _line) {
    glad_glPolygonMode(face, mode);
    gl_check_error(_file, _line);
}


void _glScissor(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glScissor(x, y, width, height);
    gl_check_error(_file, _line);
}


void _glTexParameterf(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glTexParameterf(target, pname, param);
    gl_check_error(_file, _line);
}


void _glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glTexParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTexParameteri(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glTexParameteri(target, pname, param);
    gl_check_error(_file, _line);
}


void _glTexParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTexParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glDrawBuffer(GLenum buf, const char * _file, int _line) {
    glad_glDrawBuffer(buf);
    gl_check_error(_file, _line);
}


void _glClear(GLbitfield mask, const char * _file, int _line) {
    glad_glClear(mask);
    gl_check_error(_file, _line);
}


void _glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line) {
    glad_glClearColor(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glClearStencil(GLint s, const char * _file, int _line) {
    glad_glClearStencil(s);
    gl_check_error(_file, _line);
}


void _glClearDepth(GLdouble depth, const char * _file, int _line) {
    glad_glClearDepth(depth);
    gl_check_error(_file, _line);
}


void _glStencilMask(GLuint mask, const char * _file, int _line) {
    glad_glStencilMask(mask);
    gl_check_error(_file, _line);
}


void _glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, const char * _file, int _line) {
    glad_glColorMask(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glDepthMask(GLboolean flag, const char * _file, int _line) {
    glad_glDepthMask(flag);
    gl_check_error(_file, _line);
}


void _glDisable(GLenum cap, const char * _file, int _line) {
    glad_glDisable(cap);
    gl_check_error(_file, _line);
}


void _glEnable(GLenum cap, const char * _file, int _line) {
    glad_glEnable(cap);
    gl_check_error(_file, _line);
}


void _glFinish(const char * _file, int _line) {
    glad_glFinish();
    gl_check_error(_file, _line);
}


void _glFlush(const char * _file, int _line) {
    glad_glFlush();
    gl_check_error(_file, _line);
}


void _glBlendFunc(GLenum sfactor, GLenum dfactor, const char * _file, int _line) {
    glad_glBlendFunc(sfactor, dfactor);
    gl_check_error(_file, _line);
}


void _glLogicOp(GLenum opcode, const char * _file, int _line) {
    glad_glLogicOp(opcode);
    gl_check_error(_file, _line);
}


void _glStencilFunc(GLenum func, GLint ref, GLuint mask, const char * _file, int _line) {
    glad_glStencilFunc(func, ref, mask);
    gl_check_error(_file, _line);
}


void _glStencilOp(GLenum fail, GLenum zfail, GLenum zpass, const char * _file, int _line) {
    glad_glStencilOp(fail, zfail, zpass);
    gl_check_error(_file, _line);
}


void _glDepthFunc(GLenum func, const char * _file, int _line) {
    glad_glDepthFunc(func);
    gl_check_error(_file, _line);
}


void _glPixelStoref(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPixelStoref(pname, param);
    gl_check_error(_file, _line);
}


void _glPixelStorei(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPixelStorei(pname, param);
    gl_check_error(_file, _line);
}


void _glReadBuffer(GLenum src, const char * _file, int _line) {
    glad_glReadBuffer(src);
    gl_check_error(_file, _line);
}


void _glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels, const char * _file, int _line) {
    glad_glReadPixels(x, y, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glGetBooleanv(GLenum pname, GLboolean *data, const char * _file, int _line) {
    glad_glGetBooleanv(pname, data);
    gl_check_error(_file, _line);
}


void _glGetDoublev(GLenum pname, GLdouble *data, const char * _file, int _line) {
    glad_glGetDoublev(pname, data);
    gl_check_error(_file, _line);
}


// GLenum glGetError() {
//     auto val = glad_glGetError();
//     gl_check_error();
//     return val;
// }


void _glGetFloatv(GLenum pname, GLfloat *data, const char * _file, int _line) {
    glad_glGetFloatv(pname, data);
    gl_check_error(_file, _line);
}


void _glGetIntegerv(GLenum pname, GLint *data, const char * _file, int _line) {
    glad_glGetIntegerv(pname, data);
    gl_check_error(_file, _line);
}


const GLubyte * _glGetString(GLenum name, const char * _file, int _line) {
    auto val = glad_glGetString(name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line) {
    glad_glGetTexImage(target, level, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTexParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTexParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTexLevelParameterfv(target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTexLevelParameteriv(target, level, pname, params);
    gl_check_error(_file, _line);
}


GLboolean _glIsEnabled(GLenum cap, const char * _file, int _line) {
    auto val = glad_glIsEnabled(cap);
    gl_check_error(_file, _line);
    return val;
}


void _glDepthRange(GLdouble n, GLdouble f, const char * _file, int _line) {
    glad_glDepthRange(n, f);
    gl_check_error(_file, _line);
}


void _glViewport(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glViewport(x, y, width, height);
    gl_check_error(_file, _line);
}


void _glDrawArrays(GLenum mode, GLint first, GLsizei count, const char * _file, int _line) {
    glad_glDrawArrays(mode, first, count);
    gl_check_error(_file, _line);
}


void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices, const char * _file, int _line) {
    glad_glDrawElements(mode, count, type, indices);
    gl_check_error(_file, _line);
}


void _glPolygonOffset(GLfloat factor, GLfloat units, const char * _file, int _line) {
    glad_glPolygonOffset(factor, units);
    gl_check_error(_file, _line);
}


void _glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line) {
    glad_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
    gl_check_error(_file, _line);
}


void _glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line) {
    glad_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glBindTexture(GLenum target, GLuint texture, const char * _file, int _line) {
    glad_glBindTexture(target, texture);
    gl_check_error(_file, _line);
}


void _glDeleteTextures(GLsizei n, const GLuint *textures, const char * _file, int _line) {
    glad_glDeleteTextures(n, textures);
    gl_check_error(_file, _line);
}


void _glGenTextures(GLsizei n, GLuint *textures, const char * _file, int _line) {
    glad_glGenTextures(n, textures);
    gl_check_error(_file, _line);
}


GLboolean _glIsTexture(GLuint texture, const char * _file, int _line) {
    auto val = glad_glIsTexture(texture);
    gl_check_error(_file, _line);
    return val;
}


void _glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, const char * _file, int _line) {
    glad_glDrawRangeElements(mode, start, end, count, type, indices);
    gl_check_error(_file, _line);
}


void _glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glActiveTexture(GLenum texture, const char * _file, int _line) {
    glad_glActiveTexture(texture);
    gl_check_error(_file, _line);
}


void _glSampleCoverage(GLfloat value, GLboolean invert, const char * _file, int _line) {
    glad_glSampleCoverage(value, invert);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glGetCompressedTexImage(GLenum target, GLint level, void *img, const char * _file, int _line) {
    glad_glGetCompressedTexImage(target, level, img);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    gl_check_error(_file, _line);
}


void _glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount, const char * _file, int _line) {
    glad_glMultiDrawArrays(mode, first, count, drawcount);
    gl_check_error(_file, _line);
}


void _glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const char * _file, int _line) {
    glad_glMultiDrawElements(mode, count, type, indices, drawcount);
    gl_check_error(_file, _line);
}


void _glPointParameterf(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPointParameterf(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameterfv(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPointParameterfv(pname, params);
    gl_check_error(_file, _line);
}


void _glPointParameteri(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPointParameteri(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameteriv(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glPointParameteriv(pname, params);
    gl_check_error(_file, _line);
}


void _glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line) {
    glad_glBlendColor(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glBlendEquation(GLenum mode, const char * _file, int _line) {
    glad_glBlendEquation(mode);
    gl_check_error(_file, _line);
}


void _glGenQueries(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glGenQueries(n, ids);
    gl_check_error(_file, _line);
}


void _glDeleteQueries(GLsizei n, const GLuint *ids, const char * _file, int _line) {
    glad_glDeleteQueries(n, ids);
    gl_check_error(_file, _line);
}


GLboolean _glIsQuery(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsQuery(id);
    gl_check_error(_file, _line);
    return val;
}


void _glBeginQuery(GLenum target, GLuint id, const char * _file, int _line) {
    glad_glBeginQuery(target, id);
    gl_check_error(_file, _line);
}


void _glEndQuery(GLenum target, const char * _file, int _line) {
    glad_glEndQuery(target);
    gl_check_error(_file, _line);
}


void _glGetQueryiv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetQueryiv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetQueryObjectiv(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetQueryObjectuiv(id, pname, params);
    gl_check_error(_file, _line);
}


void _glBindBuffer(GLenum target, GLuint buffer, const char * _file, int _line) {
    glad_glBindBuffer(target, buffer);
    gl_check_error(_file, _line);
}


void _glDeleteBuffers(GLsizei n, const GLuint *buffers, const char * _file, int _line) {
    glad_glDeleteBuffers(n, buffers);
    gl_check_error(_file, _line);
}


void _glGenBuffers(GLsizei n, GLuint *buffers, const char * _file, int _line) {
    glad_glGenBuffers(n, buffers);
    gl_check_error(_file, _line);
}


GLboolean _glIsBuffer(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glIsBuffer(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line) {
    glad_glBufferData(target, size, data, usage);
    gl_check_error(_file, _line);
}


void _glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line) {
    glad_glBufferSubData(target, offset, size, data);
    gl_check_error(_file, _line);
}


void _glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line) {
    glad_glGetBufferSubData(target, offset, size, data);
    gl_check_error(_file, _line);
}


void * _glMapBuffer(GLenum target, GLenum access, const char * _file, int _line) {
    auto val = glad_glMapBuffer(target, access);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glUnmapBuffer(GLenum target, const char * _file, int _line) {
    auto val = glad_glUnmapBuffer(target);
    gl_check_error(_file, _line);
    return val;
}


void _glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetBufferParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetBufferPointerv(GLenum target, GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetBufferPointerv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line) {
    glad_glBlendEquationSeparate(modeRGB, modeAlpha);
    gl_check_error(_file, _line);
}


void _glDrawBuffers(GLsizei n, const GLenum *bufs, const char * _file, int _line) {
    glad_glDrawBuffers(n, bufs);
    gl_check_error(_file, _line);
}


void _glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, const char * _file, int _line) {
    glad_glStencilOpSeparate(face, sfail, dpfail, dppass);
    gl_check_error(_file, _line);
}


void _glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask, const char * _file, int _line) {
    glad_glStencilFuncSeparate(face, func, ref, mask);
    gl_check_error(_file, _line);
}


void _glStencilMaskSeparate(GLenum face, GLuint mask, const char * _file, int _line) {
    glad_glStencilMaskSeparate(face, mask);
    gl_check_error(_file, _line);
}


void _glAttachShader(GLuint program, GLuint shader, const char * _file, int _line) {
    glad_glAttachShader(program, shader);
    gl_check_error(_file, _line);
}


void _glBindAttribLocation(GLuint program, GLuint index, const GLchar *name, const char * _file, int _line) {
    glad_glBindAttribLocation(program, index, name);
    gl_check_error(_file, _line);
}


void _glCompileShader(GLuint shader, const char * _file, int _line) {
    glad_glCompileShader(shader);
    gl_check_error(_file, _line);
}


GLuint _glCreateProgram(const char * _file, int _line) {
    auto val = glad_glCreateProgram();
    gl_check_error(_file, _line);
    return val;
}


GLuint _glCreateShader(GLenum type, const char * _file, int _line) {
    auto val = glad_glCreateShader(type);
    gl_check_error(_file, _line);
    return val;
}


void _glDeleteProgram(GLuint program, const char * _file, int _line) {
    glad_glDeleteProgram(program);
    gl_check_error(_file, _line);
}


void _glDeleteShader(GLuint shader, const char * _file, int _line) {
    glad_glDeleteShader(shader);
    gl_check_error(_file, _line);
}


void _glDetachShader(GLuint program, GLuint shader, const char * _file, int _line) {
    glad_glDetachShader(program, shader);
    gl_check_error(_file, _line);
}


void _glDisableVertexAttribArray(GLuint index, const char * _file, int _line) {
    glad_glDisableVertexAttribArray(index);
    gl_check_error(_file, _line);
}


void _glEnableVertexAttribArray(GLuint index, const char * _file, int _line) {
    glad_glEnableVertexAttribArray(index);
    gl_check_error(_file, _line);
}


void _glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name, const char * _file, int _line) {
    glad_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name, const char * _file, int _line) {
    glad_glGetActiveUniform(program, index, bufSize, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders, const char * _file, int _line) {
    glad_glGetAttachedShaders(program, maxCount, count, shaders);
    gl_check_error(_file, _line);
}


GLint _glGetAttribLocation(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetAttribLocation(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetProgramiv(GLuint program, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramiv(program, pname, params);
    gl_check_error(_file, _line);
}


void _glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line) {
    glad_glGetProgramInfoLog(program, bufSize, length, infoLog);
    gl_check_error(_file, _line);
}


void _glGetShaderiv(GLuint shader, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetShaderiv(shader, pname, params);
    gl_check_error(_file, _line);
}


void _glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line) {
    glad_glGetShaderInfoLog(shader, bufSize, length, infoLog);
    gl_check_error(_file, _line);
}


void _glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source, const char * _file, int _line) {
    glad_glGetShaderSource(shader, bufSize, length, source);
    gl_check_error(_file, _line);
}


GLint _glGetUniformLocation(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetUniformLocation(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetUniformfv(GLuint program, GLint location, GLfloat *params, const char * _file, int _line) {
    glad_glGetUniformfv(program, location, params);
    gl_check_error(_file, _line);
}


void _glGetUniformiv(GLuint program, GLint location, GLint *params, const char * _file, int _line) {
    glad_glGetUniformiv(program, location, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVertexAttribdv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVertexAttribfv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribiv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer, const char * _file, int _line) {
    glad_glGetVertexAttribPointerv(index, pname, pointer);
    gl_check_error(_file, _line);
}


GLboolean _glIsProgram(GLuint program, const char * _file, int _line) {
    auto val = glad_glIsProgram(program);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsShader(GLuint shader, const char * _file, int _line) {
    auto val = glad_glIsShader(shader);
    gl_check_error(_file, _line);
    return val;
}


void _glLinkProgram(GLuint program, const char * _file, int _line) {
    glad_glLinkProgram(program);
    gl_check_error(_file, _line);
}


void _glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length, const char * _file, int _line) {
    glad_glShaderSource(shader, count, string, length);
    gl_check_error(_file, _line);
}


void _glUseProgram(GLuint program, const char * _file, int _line) {
    glad_glUseProgram(program);
    gl_check_error(_file, _line);
}


void _glUniform1f(GLint location, GLfloat v0, const char * _file, int _line) {
    glad_glUniform1f(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2f(GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line) {
    glad_glUniform2f(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line) {
    glad_glUniform3f(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line) {
    glad_glUniform4f(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1i(GLint location, GLint v0, const char * _file, int _line) {
    glad_glUniform1i(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2i(GLint location, GLint v0, GLint v1, const char * _file, int _line) {
    glad_glUniform2i(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3i(GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line) {
    glad_glUniform3i(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line) {
    glad_glUniform4i(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform1fv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform2fv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform3fv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform4fv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform1iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform1iv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform2iv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform3iv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform4iv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix2fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix3fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix4fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glValidateProgram(GLuint program, const char * _file, int _line) {
    glad_glValidateProgram(program);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1d(GLuint index, GLdouble x, const char * _file, int _line) {
    glad_glVertexAttrib1d(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib1dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1f(GLuint index, GLfloat x, const char * _file, int _line) {
    glad_glVertexAttrib1f(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1fv(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib1fv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1s(GLuint index, GLshort x, const char * _file, int _line) {
    glad_glVertexAttrib1s(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1sv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib1sv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexAttrib2d(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib2dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glVertexAttrib2f(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2fv(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib2fv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2s(GLuint index, GLshort x, GLshort y, const char * _file, int _line) {
    glad_glVertexAttrib2s(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2sv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib2sv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexAttrib3d(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib3dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glVertexAttrib3f(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3fv(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib3fv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glVertexAttrib3s(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3sv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib3sv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nbv(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4Nbv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Niv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttrib4Niv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nsv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib4Nsv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line) {
    glad_glVertexAttrib4Nub(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nubv(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4Nubv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nuiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttrib4Nuiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4Nusv(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttrib4Nusv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4bv(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4bv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexAttrib4d(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib4dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glVertexAttrib4f(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4fv(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib4fv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4iv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttrib4iv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line) {
    glad_glVertexAttrib4s(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4sv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib4sv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4ubv(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4ubv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4uiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttrib4uiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4usv(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttrib4usv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix2x3fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix3x2fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix2x4fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix4x2fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix3x4fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix4x3fv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, const char * _file, int _line) {
    glad_glColorMaski(index, r, g, b, a);
    gl_check_error(_file, _line);
}


void _glGetBooleani_v(GLenum target, GLuint index, GLboolean *data, const char * _file, int _line) {
    glad_glGetBooleani_v(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetIntegeri_v(GLenum target, GLuint index, GLint *data, const char * _file, int _line) {
    glad_glGetIntegeri_v(target, index, data);
    gl_check_error(_file, _line);
}


void _glEnablei(GLenum target, GLuint index, const char * _file, int _line) {
    glad_glEnablei(target, index);
    gl_check_error(_file, _line);
}


void _glDisablei(GLenum target, GLuint index, const char * _file, int _line) {
    glad_glDisablei(target, index);
    gl_check_error(_file, _line);
}


GLboolean _glIsEnabledi(GLenum target, GLuint index, const char * _file, int _line) {
    auto val = glad_glIsEnabledi(target, index);
    gl_check_error(_file, _line);
    return val;
}


void _glBeginTransformFeedback(GLenum primitiveMode, const char * _file, int _line) {
    glad_glBeginTransformFeedback(primitiveMode);
    gl_check_error(_file, _line);
}


void _glEndTransformFeedback(const char * _file, int _line) {
    glad_glEndTransformFeedback();
    gl_check_error(_file, _line);
}


void _glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glBindBufferRange(target, index, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glBindBufferBase(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line) {
    glad_glBindBufferBase(target, index, buffer);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode, const char * _file, int _line) {
    glad_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line) {
    glad_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glClampColor(GLenum target, GLenum clamp, const char * _file, int _line) {
    glad_glClampColor(target, clamp);
    gl_check_error(_file, _line);
}


void _glBeginConditionalRender(GLuint id, GLenum mode, const char * _file, int _line) {
    glad_glBeginConditionalRender(id, mode);
    gl_check_error(_file, _line);
}


void _glEndConditionalRender(const char * _file, int _line) {
    glad_glEndConditionalRender();
    gl_check_error(_file, _line);
}


void _glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribIPointer(index, size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribIiv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetVertexAttribIuiv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1i(GLuint index, GLint x, const char * _file, int _line) {
    glad_glVertexAttribI1i(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2i(GLuint index, GLint x, GLint y, const char * _file, int _line) {
    glad_glVertexAttribI2i(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z, const char * _file, int _line) {
    glad_glVertexAttribI3i(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glVertexAttribI4i(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1ui(GLuint index, GLuint x, const char * _file, int _line) {
    glad_glVertexAttribI1ui(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2ui(GLuint index, GLuint x, GLuint y, const char * _file, int _line) {
    glad_glVertexAttribI2ui(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z, const char * _file, int _line) {
    glad_glVertexAttribI3ui(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line) {
    glad_glVertexAttribI4ui(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1iv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI1iv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2iv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI2iv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3iv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI3iv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4iv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI4iv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1uiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI1uiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2uiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI2uiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3uiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI3uiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4uiv(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI4uiv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4bv(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttribI4bv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4sv(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribI4sv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4ubv(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttribI4ubv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4usv(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttribI4usv(index, v);
    gl_check_error(_file, _line);
}


void _glGetUniformuiv(GLuint program, GLint location, GLuint *params, const char * _file, int _line) {
    glad_glGetUniformuiv(program, location, params);
    gl_check_error(_file, _line);
}


void _glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name, const char * _file, int _line) {
    glad_glBindFragDataLocation(program, color, name);
    gl_check_error(_file, _line);
}


GLint _glGetFragDataLocation(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetFragDataLocation(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glUniform1ui(GLint location, GLuint v0, const char * _file, int _line) {
    glad_glUniform1ui(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2ui(GLint location, GLuint v0, GLuint v1, const char * _file, int _line) {
    glad_glUniform2ui(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line) {
    glad_glUniform3ui(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line) {
    glad_glUniform4ui(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform1uiv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform2uiv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform3uiv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform4uiv(location, count, value);
    gl_check_error(_file, _line);
}


void _glTexParameterIiv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTexParameterIiv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line) {
    glad_glTexParameterIuiv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTexParameterIiv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetTexParameterIuiv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value, const char * _file, int _line) {
    glad_glClearBufferiv(buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value, const char * _file, int _line) {
    glad_glClearBufferuiv(buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value, const char * _file, int _line) {
    glad_glClearBufferfv(buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, const char * _file, int _line) {
    glad_glClearBufferfi(buffer, drawbuffer, depth, stencil);
    gl_check_error(_file, _line);
}


const GLubyte * _glGetStringi(GLenum name, GLuint index, const char * _file, int _line) {
    auto val = glad_glGetStringi(name, index);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsRenderbuffer(GLuint renderbuffer, const char * _file, int _line) {
    auto val = glad_glIsRenderbuffer(renderbuffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBindRenderbuffer(GLenum target, GLuint renderbuffer, const char * _file, int _line) {
    glad_glBindRenderbuffer(target, renderbuffer);
    gl_check_error(_file, _line);
}


void _glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers, const char * _file, int _line) {
    glad_glDeleteRenderbuffers(n, renderbuffers);
    gl_check_error(_file, _line);
}


void _glGenRenderbuffers(GLsizei n, GLuint *renderbuffers, const char * _file, int _line) {
    glad_glGenRenderbuffers(n, renderbuffers);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorage(target, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetRenderbufferParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


GLboolean _glIsFramebuffer(GLuint framebuffer, const char * _file, int _line) {
    auto val = glad_glIsFramebuffer(framebuffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBindFramebuffer(GLenum target, GLuint framebuffer, const char * _file, int _line) {
    glad_glBindFramebuffer(target, framebuffer);
    gl_check_error(_file, _line);
}


void _glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers, const char * _file, int _line) {
    glad_glDeleteFramebuffers(n, framebuffers);
    gl_check_error(_file, _line);
}


void _glGenFramebuffers(GLsizei n, GLuint *framebuffers, const char * _file, int _line) {
    glad_glGenFramebuffers(n, framebuffers);
    gl_check_error(_file, _line);
}


GLenum _glCheckFramebufferStatus(GLenum target, const char * _file, int _line) {
    auto val = glad_glCheckFramebufferStatus(target);
    gl_check_error(_file, _line);
    return val;
}


void _glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTexture1D(target, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTexture2D(target, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line) {
    glad_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
    gl_check_error(_file, _line);
}


void _glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line) {
    glad_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    gl_check_error(_file, _line);
}


void _glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
    gl_check_error(_file, _line);
}


void _glGenerateMipmap(GLenum target, const char * _file, int _line) {
    glad_glGenerateMipmap(target);
    gl_check_error(_file, _line);
}


void _glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line) {
    glad_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line) {
    glad_glFramebufferTextureLayer(target, attachment, texture, level, layer);
    gl_check_error(_file, _line);
}


void * _glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line) {
    auto val = glad_glMapBufferRange(target, offset, length, access);
    gl_check_error(_file, _line);
    return val;
}


void _glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, const char * _file, int _line) {
    glad_glFlushMappedBufferRange(target, offset, length);
    gl_check_error(_file, _line);
}


void _glBindVertexArray(GLuint array, const char * _file, int _line) {
    glad_glBindVertexArray(array);
    gl_check_error(_file, _line);
}


void _glDeleteVertexArrays(GLsizei n, const GLuint *arrays, const char * _file, int _line) {
    glad_glDeleteVertexArrays(n, arrays);
    gl_check_error(_file, _line);
}


void _glGenVertexArrays(GLsizei n, GLuint *arrays, const char * _file, int _line) {
    glad_glGenVertexArrays(n, arrays);
    gl_check_error(_file, _line);
}


GLboolean _glIsVertexArray(GLuint array, const char * _file, int _line) {
    auto val = glad_glIsVertexArray(array);
    gl_check_error(_file, _line);
    return val;
}


void _glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, const char * _file, int _line) {
    glad_glDrawArraysInstanced(mode, first, count, instancecount);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, const char * _file, int _line) {
    glad_glDrawElementsInstanced(mode, count, type, indices, instancecount);
    gl_check_error(_file, _line);
}


void _glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glTexBuffer(target, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glPrimitiveRestartIndex(GLuint index, const char * _file, int _line) {
    glad_glPrimitiveRestartIndex(index);
    gl_check_error(_file, _line);
}


void _glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line) {
    glad_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
    gl_check_error(_file, _line);
}


void _glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices, const char * _file, int _line) {
    glad_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
    gl_check_error(_file, _line);
}


void _glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
    gl_check_error(_file, _line);
}


void _glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName, const char * _file, int _line) {
    glad_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
    gl_check_error(_file, _line);
}


GLuint _glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName, const char * _file, int _line) {
    auto val = glad_glGetUniformBlockIndex(program, uniformBlockName);
    gl_check_error(_file, _line);
    return val;
}


void _glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
    gl_check_error(_file, _line);
}


void _glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName, const char * _file, int _line) {
    glad_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
    gl_check_error(_file, _line);
}


void _glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding, const char * _file, int _line) {
    glad_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
    gl_check_error(_file, _line);
}


void _glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex, const char * _file, int _line) {
    glad_glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
    gl_check_error(_file, _line);
}


void _glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex, const char * _file, int _line) {
    glad_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, const char * _file, int _line) {
    glad_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex, const char * _file, int _line) {
    glad_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
    gl_check_error(_file, _line);
}


void _glProvokingVertex(GLenum mode, const char * _file, int _line) {
    glad_glProvokingVertex(mode);
    gl_check_error(_file, _line);
}


GLsync _glFenceSync(GLenum condition, GLbitfield flags, const char * _file, int _line) {
    auto val = glad_glFenceSync(condition, flags);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsSync(GLsync sync, const char * _file, int _line) {
    auto val = glad_glIsSync(sync);
    gl_check_error(_file, _line);
    return val;
}


void _glDeleteSync(GLsync sync, const char * _file, int _line) {
    glad_glDeleteSync(sync);
    gl_check_error(_file, _line);
}


GLenum _glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char * _file, int _line) {
    auto val = glad_glClientWaitSync(sync, flags, timeout);
    gl_check_error(_file, _line);
    return val;
}


void _glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char * _file, int _line) {
    glad_glWaitSync(sync, flags, timeout);
    gl_check_error(_file, _line);
}


void _glGetInteger64v(GLenum pname, GLint64 *data, const char * _file, int _line) {
    glad_glGetInteger64v(pname, data);
    gl_check_error(_file, _line);
}


void _glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values, const char * _file, int _line) {
    glad_glGetSynciv(sync, pname, count, length, values);
    gl_check_error(_file, _line);
}


void _glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data, const char * _file, int _line) {
    glad_glGetInteger64i_v(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params, const char * _file, int _line) {
    glad_glGetBufferParameteri64v(target, pname, params);
    gl_check_error(_file, _line);
}


void _glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTexture(target, attachment, texture, level);
    gl_check_error(_file, _line);
}


void _glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val, const char * _file, int _line) {
    glad_glGetMultisamplefv(pname, index, val);
    gl_check_error(_file, _line);
}


void _glSampleMaski(GLuint maskNumber, GLbitfield mask, const char * _file, int _line) {
    glad_glSampleMaski(maskNumber, mask);
    gl_check_error(_file, _line);
}


void _glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name, const char * _file, int _line) {
    glad_glBindFragDataLocationIndexed(program, colorNumber, index, name);
    gl_check_error(_file, _line);
}


GLint _glGetFragDataIndex(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetFragDataIndex(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGenSamplers(GLsizei count, GLuint *samplers, const char * _file, int _line) {
    glad_glGenSamplers(count, samplers);
    gl_check_error(_file, _line);
}


void _glDeleteSamplers(GLsizei count, const GLuint *samplers, const char * _file, int _line) {
    glad_glDeleteSamplers(count, samplers);
    gl_check_error(_file, _line);
}


GLboolean _glIsSampler(GLuint sampler, const char * _file, int _line) {
    auto val = glad_glIsSampler(sampler);
    gl_check_error(_file, _line);
    return val;
}


void _glBindSampler(GLuint unit, GLuint sampler, const char * _file, int _line) {
    glad_glBindSampler(unit, sampler);
    gl_check_error(_file, _line);
}


void _glSamplerParameteri(GLuint sampler, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glSamplerParameteri(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param, const char * _file, int _line) {
    glad_glSamplerParameteriv(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glSamplerParameterf(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param, const char * _file, int _line) {
    glad_glSamplerParameterfv(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param, const char * _file, int _line) {
    glad_glSamplerParameterIiv(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param, const char * _file, int _line) {
    glad_glSamplerParameterIuiv(sampler, pname, param);
    gl_check_error(_file, _line);
}


void _glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetSamplerParameteriv(sampler, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetSamplerParameterIiv(sampler, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetSamplerParameterfv(sampler, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetSamplerParameterIuiv(sampler, pname, params);
    gl_check_error(_file, _line);
}


void _glQueryCounter(GLuint id, GLenum target, const char * _file, int _line) {
    glad_glQueryCounter(id, target);
    gl_check_error(_file, _line);
}


void _glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line) {
    glad_glGetQueryObjecti64v(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line) {
    glad_glGetQueryObjectui64v(id, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexAttribDivisor(GLuint index, GLuint divisor, const char * _file, int _line) {
    glad_glVertexAttribDivisor(index, divisor);
    gl_check_error(_file, _line);
}


void _glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line) {
    glad_glVertexAttribP1ui(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line) {
    glad_glVertexAttribP1uiv(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line) {
    glad_glVertexAttribP2ui(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line) {
    glad_glVertexAttribP2uiv(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line) {
    glad_glVertexAttribP3ui(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line) {
    glad_glVertexAttribP3uiv(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line) {
    glad_glVertexAttribP4ui(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line) {
    glad_glVertexAttribP4uiv(index, type, normalized, value);
    gl_check_error(_file, _line);
}


void _glVertexP2ui(GLenum type, GLuint value, const char * _file, int _line) {
    glad_glVertexP2ui(type, value);
    gl_check_error(_file, _line);
}


void _glVertexP2uiv(GLenum type, const GLuint *value, const char * _file, int _line) {
    glad_glVertexP2uiv(type, value);
    gl_check_error(_file, _line);
}


void _glVertexP3ui(GLenum type, GLuint value, const char * _file, int _line) {
    glad_glVertexP3ui(type, value);
    gl_check_error(_file, _line);
}


void _glVertexP3uiv(GLenum type, const GLuint *value, const char * _file, int _line) {
    glad_glVertexP3uiv(type, value);
    gl_check_error(_file, _line);
}


void _glVertexP4ui(GLenum type, GLuint value, const char * _file, int _line) {
    glad_glVertexP4ui(type, value);
    gl_check_error(_file, _line);
}


void _glVertexP4uiv(GLenum type, const GLuint *value, const char * _file, int _line) {
    glad_glVertexP4uiv(type, value);
    gl_check_error(_file, _line);
}


void _glTexCoordP1ui(GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glTexCoordP1ui(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP1uiv(GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glTexCoordP1uiv(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP2ui(GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glTexCoordP2ui(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP2uiv(GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glTexCoordP2uiv(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP3ui(GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glTexCoordP3ui(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP3uiv(GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glTexCoordP3uiv(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP4ui(GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glTexCoordP4ui(type, coords);
    gl_check_error(_file, _line);
}


void _glTexCoordP4uiv(GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glTexCoordP4uiv(type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glMultiTexCoordP1ui(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glMultiTexCoordP1uiv(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glMultiTexCoordP2ui(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glMultiTexCoordP2uiv(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glMultiTexCoordP3ui(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glMultiTexCoordP3uiv(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glMultiTexCoordP4ui(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glMultiTexCoordP4uiv(texture, type, coords);
    gl_check_error(_file, _line);
}


void _glNormalP3ui(GLenum type, GLuint coords, const char * _file, int _line) {
    glad_glNormalP3ui(type, coords);
    gl_check_error(_file, _line);
}


void _glNormalP3uiv(GLenum type, const GLuint *coords, const char * _file, int _line) {
    glad_glNormalP3uiv(type, coords);
    gl_check_error(_file, _line);
}


void _glColorP3ui(GLenum type, GLuint color, const char * _file, int _line) {
    glad_glColorP3ui(type, color);
    gl_check_error(_file, _line);
}


void _glColorP3uiv(GLenum type, const GLuint *color, const char * _file, int _line) {
    glad_glColorP3uiv(type, color);
    gl_check_error(_file, _line);
}


void _glColorP4ui(GLenum type, GLuint color, const char * _file, int _line) {
    glad_glColorP4ui(type, color);
    gl_check_error(_file, _line);
}


void _glColorP4uiv(GLenum type, const GLuint *color, const char * _file, int _line) {
    glad_glColorP4uiv(type, color);
    gl_check_error(_file, _line);
}


void _glSecondaryColorP3ui(GLenum type, GLuint color, const char * _file, int _line) {
    glad_glSecondaryColorP3ui(type, color);
    gl_check_error(_file, _line);
}


void _glSecondaryColorP3uiv(GLenum type, const GLuint *color, const char * _file, int _line) {
    glad_glSecondaryColorP3uiv(type, color);
    gl_check_error(_file, _line);
}


void _glMinSampleShading(GLfloat value, const char * _file, int _line) {
    glad_glMinSampleShading(value);
    gl_check_error(_file, _line);
}


void _glBlendEquationi(GLuint buf, GLenum mode, const char * _file, int _line) {
    glad_glBlendEquationi(buf, mode);
    gl_check_error(_file, _line);
}


void _glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line) {
    glad_glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
    gl_check_error(_file, _line);
}


void _glBlendFunci(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line) {
    glad_glBlendFunci(buf, src, dst);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
    gl_check_error(_file, _line);
}


void _glDrawArraysIndirect(GLenum mode, const void *indirect, const char * _file, int _line) {
    glad_glDrawArraysIndirect(mode, indirect);
    gl_check_error(_file, _line);
}


void _glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, const char * _file, int _line) {
    glad_glDrawElementsIndirect(mode, type, indirect);
    gl_check_error(_file, _line);
}


void _glUniform1d(GLint location, GLdouble x, const char * _file, int _line) {
    glad_glUniform1d(location, x);
    gl_check_error(_file, _line);
}


void _glUniform2d(GLint location, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glUniform2d(location, x, y);
    gl_check_error(_file, _line);
}


void _glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glUniform3d(location, x, y, z);
    gl_check_error(_file, _line);
}


void _glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glUniform4d(location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glUniform1dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glUniform1dv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glUniform2dv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glUniform3dv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glUniform4dv(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix2dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix3dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix4dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix2x3dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix2x4dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix3x2dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix3x4dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix4x2dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glUniformMatrix4x3dv(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glGetUniformdv(GLuint program, GLint location, GLdouble *params, const char * _file, int _line) {
    glad_glGetUniformdv(program, location, params);
    gl_check_error(_file, _line);
}


GLint _glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetSubroutineUniformLocation(program, shadertype, name);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetSubroutineIndex(program, shadertype, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values, const char * _file, int _line) {
    glad_glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
    gl_check_error(_file, _line);
}


void _glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line) {
    glad_glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name);
    gl_check_error(_file, _line);
}


void _glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line) {
    glad_glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name);
    gl_check_error(_file, _line);
}


void _glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices, const char * _file, int _line) {
    glad_glUniformSubroutinesuiv(shadertype, count, indices);
    gl_check_error(_file, _line);
}


void _glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params, const char * _file, int _line) {
    glad_glGetUniformSubroutineuiv(shadertype, location, params);
    gl_check_error(_file, _line);
}


void _glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values, const char * _file, int _line) {
    glad_glGetProgramStageiv(program, shadertype, pname, values);
    gl_check_error(_file, _line);
}


void _glPatchParameteri(GLenum pname, GLint value, const char * _file, int _line) {
    glad_glPatchParameteri(pname, value);
    gl_check_error(_file, _line);
}


void _glPatchParameterfv(GLenum pname, const GLfloat *values, const char * _file, int _line) {
    glad_glPatchParameterfv(pname, values);
    gl_check_error(_file, _line);
}


void _glBindTransformFeedback(GLenum target, GLuint id, const char * _file, int _line) {
    glad_glBindTransformFeedback(target, id);
    gl_check_error(_file, _line);
}


void _glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids, const char * _file, int _line) {
    glad_glDeleteTransformFeedbacks(n, ids);
    gl_check_error(_file, _line);
}


void _glGenTransformFeedbacks(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glGenTransformFeedbacks(n, ids);
    gl_check_error(_file, _line);
}


GLboolean _glIsTransformFeedback(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsTransformFeedback(id);
    gl_check_error(_file, _line);
    return val;
}


void _glPauseTransformFeedback(const char * _file, int _line) {
    glad_glPauseTransformFeedback();
    gl_check_error(_file, _line);
}


void _glResumeTransformFeedback(const char * _file, int _line) {
    glad_glResumeTransformFeedback();
    gl_check_error(_file, _line);
}


void _glDrawTransformFeedback(GLenum mode, GLuint id, const char * _file, int _line) {
    glad_glDrawTransformFeedback(mode, id);
    gl_check_error(_file, _line);
}


void _glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream, const char * _file, int _line) {
    glad_glDrawTransformFeedbackStream(mode, id, stream);
    gl_check_error(_file, _line);
}


void _glBeginQueryIndexed(GLenum target, GLuint index, GLuint id, const char * _file, int _line) {
    glad_glBeginQueryIndexed(target, index, id);
    gl_check_error(_file, _line);
}


void _glEndQueryIndexed(GLenum target, GLuint index, const char * _file, int _line) {
    glad_glEndQueryIndexed(target, index);
    gl_check_error(_file, _line);
}


void _glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetQueryIndexediv(target, index, pname, params);
    gl_check_error(_file, _line);
}


void _glReleaseShaderCompiler(const char * _file, int _line) {
    glad_glReleaseShaderCompiler();
    gl_check_error(_file, _line);
}


void _glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length, const char * _file, int _line) {
    glad_glShaderBinary(count, shaders, binaryFormat, binary, length);
    gl_check_error(_file, _line);
}


void _glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision, const char * _file, int _line) {
    glad_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
    gl_check_error(_file, _line);
}


void _glDepthRangef(GLfloat n, GLfloat f, const char * _file, int _line) {
    glad_glDepthRangef(n, f);
    gl_check_error(_file, _line);
}


void _glClearDepthf(GLfloat d, const char * _file, int _line) {
    glad_glClearDepthf(d);
    gl_check_error(_file, _line);
}


void _glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary, const char * _file, int _line) {
    glad_glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
    gl_check_error(_file, _line);
}


void _glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length, const char * _file, int _line) {
    glad_glProgramBinary(program, binaryFormat, binary, length);
    gl_check_error(_file, _line);
}


void _glProgramParameteri(GLuint program, GLenum pname, GLint value, const char * _file, int _line) {
    glad_glProgramParameteri(program, pname, value);
    gl_check_error(_file, _line);
}


void _glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program, const char * _file, int _line) {
    glad_glUseProgramStages(pipeline, stages, program);
    gl_check_error(_file, _line);
}


void _glActiveShaderProgram(GLuint pipeline, GLuint program, const char * _file, int _line) {
    glad_glActiveShaderProgram(pipeline, program);
    gl_check_error(_file, _line);
}


GLuint _glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings, const char * _file, int _line) {
    auto val = glad_glCreateShaderProgramv(type, count, strings);
    gl_check_error(_file, _line);
    return val;
}


void _glBindProgramPipeline(GLuint pipeline, const char * _file, int _line) {
    glad_glBindProgramPipeline(pipeline);
    gl_check_error(_file, _line);
}


void _glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines, const char * _file, int _line) {
    glad_glDeleteProgramPipelines(n, pipelines);
    gl_check_error(_file, _line);
}


void _glGenProgramPipelines(GLsizei n, GLuint *pipelines, const char * _file, int _line) {
    glad_glGenProgramPipelines(n, pipelines);
    gl_check_error(_file, _line);
}


GLboolean _glIsProgramPipeline(GLuint pipeline, const char * _file, int _line) {
    auto val = glad_glIsProgramPipeline(pipeline);
    gl_check_error(_file, _line);
    return val;
}


void _glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramPipelineiv(pipeline, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramUniform1i(GLuint program, GLint location, GLint v0, const char * _file, int _line) {
    glad_glProgramUniform1i(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform1iv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1f(GLuint program, GLint location, GLfloat v0, const char * _file, int _line) {
    glad_glProgramUniform1f(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform1fv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1d(GLuint program, GLint location, GLdouble v0, const char * _file, int _line) {
    glad_glProgramUniform1d(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform1dv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ui(GLuint program, GLint location, GLuint v0, const char * _file, int _line) {
    glad_glProgramUniform1ui(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform1uiv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1, const char * _file, int _line) {
    glad_glProgramUniform2i(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform2iv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line) {
    glad_glProgramUniform2f(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform2fv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1, const char * _file, int _line) {
    glad_glProgramUniform2d(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform2dv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1, const char * _file, int _line) {
    glad_glProgramUniform2ui(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform2uiv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line) {
    glad_glProgramUniform3i(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform3iv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line) {
    glad_glProgramUniform3f(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform3fv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, const char * _file, int _line) {
    glad_glProgramUniform3d(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform3dv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line) {
    glad_glProgramUniform3ui(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform3uiv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line) {
    glad_glProgramUniform4i(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform4iv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line) {
    glad_glProgramUniform4f(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform4fv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3, const char * _file, int _line) {
    glad_glProgramUniform4d(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform4dv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line) {
    glad_glProgramUniform4ui(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform4uiv(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glValidateProgramPipeline(GLuint pipeline, const char * _file, int _line) {
    glad_glValidateProgramPipeline(pipeline);
    gl_check_error(_file, _line);
}


void _glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line) {
    glad_glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1d(GLuint index, GLdouble x, const char * _file, int _line) {
    glad_glVertexAttribL1d(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexAttribL2d(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexAttribL3d(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexAttribL4d(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL1dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL2dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL3dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4dv(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL4dv(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribLPointer(index, size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVertexAttribLdv(index, pname, params);
    gl_check_error(_file, _line);
}


void _glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glViewportArrayv(first, count, v);
    gl_check_error(_file, _line);
}


void _glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const char * _file, int _line) {
    glad_glViewportIndexedf(index, x, y, w, h);
    gl_check_error(_file, _line);
}


void _glViewportIndexedfv(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glViewportIndexedfv(index, v);
    gl_check_error(_file, _line);
}


void _glScissorArrayv(GLuint first, GLsizei count, const GLint *v, const char * _file, int _line) {
    glad_glScissorArrayv(first, count, v);
    gl_check_error(_file, _line);
}


void _glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glScissorIndexed(index, left, bottom, width, height);
    gl_check_error(_file, _line);
}


void _glScissorIndexedv(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glScissorIndexedv(index, v);
    gl_check_error(_file, _line);
}


void _glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glDepthRangeArrayv(first, count, v);
    gl_check_error(_file, _line);
}


void _glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f, const char * _file, int _line) {
    glad_glDepthRangeIndexed(index, n, f);
    gl_check_error(_file, _line);
}


void _glGetFloati_v(GLenum target, GLuint index, GLfloat *data, const char * _file, int _line) {
    glad_glGetFloati_v(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetDoublei_v(GLenum target, GLuint index, GLdouble *data, const char * _file, int _line) {
    glad_glGetDoublei_v(target, index, data);
    gl_check_error(_file, _line);
}


void _glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance, const char * _file, int _line) {
    glad_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance, const char * _file, int _line) {
    glad_glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance, const char * _file, int _line) {
    glad_glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
    gl_check_error(_file, _line);
}


void _glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params, const char * _file, int _line) {
    glad_glGetInternalformativ(target, internalformat, pname, count, params);
    gl_check_error(_file, _line);
}


void _glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
    gl_check_error(_file, _line);
}


void _glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format, const char * _file, int _line) {
    glad_glBindImageTexture(unit, texture, level, layered, layer, access, format);
    gl_check_error(_file, _line);
}


void _glMemoryBarrier(GLbitfield barriers, const char * _file, int _line) {
    glad_glMemoryBarrier(barriers);
    gl_check_error(_file, _line);
}


void _glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line) {
    glad_glTexStorage1D(target, levels, internalformat, width);
    gl_check_error(_file, _line);
}


void _glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glTexStorage2D(target, levels, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glTexStorage3D(target, levels, internalformat, width, height, depth);
    gl_check_error(_file, _line);
}


void _glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount, const char * _file, int _line) {
    glad_glDrawTransformFeedbackInstanced(mode, id, instancecount);
    gl_check_error(_file, _line);
}


void _glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount, const char * _file, int _line) {
    glad_glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
    gl_check_error(_file, _line);
}


void _glTbufferMask3DFX(GLuint mask, const char * _file, int _line) {
    glad_glTbufferMask3DFX(mask);
    gl_check_error(_file, _line);
}


void _glDebugMessageEnableAMD(GLenum category, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line) {
    glad_glDebugMessageEnableAMD(category, severity, count, ids, enabled);
    gl_check_error(_file, _line);
}


void _glDebugMessageInsertAMD(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar *buf, const char * _file, int _line) {
    glad_glDebugMessageInsertAMD(category, severity, id, length, buf);
    gl_check_error(_file, _line);
}


void _glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void *userParam, const char * _file, int _line) {
    glad_glDebugMessageCallbackAMD(callback, userParam);
    gl_check_error(_file, _line);
}


GLuint _glGetDebugMessageLogAMD(GLuint count, GLsizei bufSize, GLenum *categories, GLuint *severities, GLuint *ids, GLsizei *lengths, GLchar *message, const char * _file, int _line) {
    auto val = glad_glGetDebugMessageLogAMD(count, bufSize, categories, severities, ids, lengths, message);
    gl_check_error(_file, _line);
    return val;
}


void _glBlendFuncIndexedAMD(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line) {
    glad_glBlendFuncIndexedAMD(buf, src, dst);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparateIndexedAMD(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparateIndexedAMD(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
    gl_check_error(_file, _line);
}


void _glBlendEquationIndexedAMD(GLuint buf, GLenum mode, const char * _file, int _line) {
    glad_glBlendEquationIndexedAMD(buf, mode);
    gl_check_error(_file, _line);
}


void _glBlendEquationSeparateIndexedAMD(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line) {
    glad_glBlendEquationSeparateIndexedAMD(buf, modeRGB, modeAlpha);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorageMultisampleAdvancedAMD(GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorageMultisampleAdvancedAMD(target, samples, storageSamples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorageMultisampleAdvancedAMD(GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorageMultisampleAdvancedAMD(renderbuffer, samples, storageSamples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glFramebufferSamplePositionsfvAMD(GLenum target, GLuint numsamples, GLuint pixelindex, const GLfloat *values, const char * _file, int _line) {
    glad_glFramebufferSamplePositionsfvAMD(target, numsamples, pixelindex, values);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferSamplePositionsfvAMD(GLuint framebuffer, GLuint numsamples, GLuint pixelindex, const GLfloat *values, const char * _file, int _line) {
    glad_glNamedFramebufferSamplePositionsfvAMD(framebuffer, numsamples, pixelindex, values);
    gl_check_error(_file, _line);
}


void _glGetFramebufferParameterfvAMD(GLenum target, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat *values, const char * _file, int _line) {
    glad_glGetFramebufferParameterfvAMD(target, pname, numsamples, pixelindex, size, values);
    gl_check_error(_file, _line);
}


void _glGetNamedFramebufferParameterfvAMD(GLuint framebuffer, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat *values, const char * _file, int _line) {
    glad_glGetNamedFramebufferParameterfvAMD(framebuffer, pname, numsamples, pixelindex, size, values);
    gl_check_error(_file, _line);
}


void _glUniform1i64NV(GLint location, GLint64EXT x, const char * _file, int _line) {
    glad_glUniform1i64NV(location, x);
    gl_check_error(_file, _line);
}


void _glUniform2i64NV(GLint location, GLint64EXT x, GLint64EXT y, const char * _file, int _line) {
    glad_glUniform2i64NV(location, x, y);
    gl_check_error(_file, _line);
}


void _glUniform3i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line) {
    glad_glUniform3i64NV(location, x, y, z);
    gl_check_error(_file, _line);
}


void _glUniform4i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line) {
    glad_glUniform4i64NV(location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glUniform1i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glUniform1i64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glUniform2i64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glUniform3i64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glUniform4i64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform1ui64NV(GLint location, GLuint64EXT x, const char * _file, int _line) {
    glad_glUniform1ui64NV(location, x);
    gl_check_error(_file, _line);
}


void _glUniform2ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line) {
    glad_glUniform2ui64NV(location, x, y);
    gl_check_error(_file, _line);
}


void _glUniform3ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line) {
    glad_glUniform3ui64NV(location, x, y, z);
    gl_check_error(_file, _line);
}


void _glUniform4ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line) {
    glad_glUniform4ui64NV(location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glUniform1ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glUniform1ui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glUniform2ui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glUniform3ui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glUniform4ui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glGetUniformi64vNV(GLuint program, GLint location, GLint64EXT *params, const char * _file, int _line) {
    glad_glGetUniformi64vNV(program, location, params);
    gl_check_error(_file, _line);
}


void _glGetUniformui64vNV(GLuint program, GLint location, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetUniformui64vNV(program, location, params);
    gl_check_error(_file, _line);
}


void _glProgramUniform1i64NV(GLuint program, GLint location, GLint64EXT x, const char * _file, int _line) {
    glad_glProgramUniform1i64NV(program, location, x);
    gl_check_error(_file, _line);
}


void _glProgramUniform2i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, const char * _file, int _line) {
    glad_glProgramUniform2i64NV(program, location, x, y);
    gl_check_error(_file, _line);
}


void _glProgramUniform3i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line) {
    glad_glProgramUniform3i64NV(program, location, x, y, z);
    gl_check_error(_file, _line);
}


void _glProgramUniform4i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line) {
    glad_glProgramUniform4i64NV(program, location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramUniform1i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform1i64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform2i64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform3i64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform4i64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ui64NV(GLuint program, GLint location, GLuint64EXT x, const char * _file, int _line) {
    glad_glProgramUniform1ui64NV(program, location, x);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line) {
    glad_glProgramUniform2ui64NV(program, location, x, y);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line) {
    glad_glProgramUniform3ui64NV(program, location, x, y, z);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line) {
    glad_glProgramUniform4ui64NV(program, location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform1ui64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform2ui64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform3ui64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniform4ui64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glVertexAttribParameteriAMD(GLuint index, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glVertexAttribParameteriAMD(index, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysIndirectAMD(GLenum mode, const void *indirect, GLsizei primcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawArraysIndirectAMD(mode, indirect, primcount, stride);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsIndirectAMD(GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawElementsIndirectAMD(mode, type, indirect, primcount, stride);
    gl_check_error(_file, _line);
}


void _glGenNamesAMD(GLenum identifier, GLuint num, GLuint *names, const char * _file, int _line) {
    glad_glGenNamesAMD(identifier, num, names);
    gl_check_error(_file, _line);
}


void _glDeleteNamesAMD(GLenum identifier, GLuint num, const GLuint *names, const char * _file, int _line) {
    glad_glDeleteNamesAMD(identifier, num, names);
    gl_check_error(_file, _line);
}


GLboolean _glIsNameAMD(GLenum identifier, GLuint name, const char * _file, int _line) {
    auto val = glad_glIsNameAMD(identifier, name);
    gl_check_error(_file, _line);
    return val;
}


void _glQueryObjectParameteruiAMD(GLenum target, GLuint id, GLenum pname, GLuint param, const char * _file, int _line) {
    glad_glQueryObjectParameteruiAMD(target, id, pname, param);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorGroupsAMD(GLint *numGroups, GLsizei groupsSize, GLuint *groups, const char * _file, int _line) {
    glad_glGetPerfMonitorGroupsAMD(numGroups, groupsSize, groups);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorCountersAMD(GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters, const char * _file, int _line) {
    glad_glGetPerfMonitorCountersAMD(group, numCounters, maxActiveCounters, counterSize, counters);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorGroupStringAMD(GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString, const char * _file, int _line) {
    glad_glGetPerfMonitorGroupStringAMD(group, bufSize, length, groupString);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorCounterStringAMD(GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString, const char * _file, int _line) {
    glad_glGetPerfMonitorCounterStringAMD(group, counter, bufSize, length, counterString);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorCounterInfoAMD(GLuint group, GLuint counter, GLenum pname, void *data, const char * _file, int _line) {
    glad_glGetPerfMonitorCounterInfoAMD(group, counter, pname, data);
    gl_check_error(_file, _line);
}


void _glGenPerfMonitorsAMD(GLsizei n, GLuint *monitors, const char * _file, int _line) {
    glad_glGenPerfMonitorsAMD(n, monitors);
    gl_check_error(_file, _line);
}


void _glDeletePerfMonitorsAMD(GLsizei n, GLuint *monitors, const char * _file, int _line) {
    glad_glDeletePerfMonitorsAMD(n, monitors);
    gl_check_error(_file, _line);
}


void _glSelectPerfMonitorCountersAMD(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList, const char * _file, int _line) {
    glad_glSelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList);
    gl_check_error(_file, _line);
}


void _glBeginPerfMonitorAMD(GLuint monitor, const char * _file, int _line) {
    glad_glBeginPerfMonitorAMD(monitor);
    gl_check_error(_file, _line);
}


void _glEndPerfMonitorAMD(GLuint monitor, const char * _file, int _line) {
    glad_glEndPerfMonitorAMD(monitor);
    gl_check_error(_file, _line);
}


void _glGetPerfMonitorCounterDataAMD(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten, const char * _file, int _line) {
    glad_glGetPerfMonitorCounterDataAMD(monitor, pname, dataSize, data, bytesWritten);
    gl_check_error(_file, _line);
}


void _glSetMultisamplefvAMD(GLenum pname, GLuint index, const GLfloat *val, const char * _file, int _line) {
    glad_glSetMultisamplefvAMD(pname, index, val);
    gl_check_error(_file, _line);
}


void _glTexStorageSparseAMD(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags, const char * _file, int _line) {
    glad_glTexStorageSparseAMD(target, internalFormat, width, height, depth, layers, flags);
    gl_check_error(_file, _line);
}


void _glTextureStorageSparseAMD(GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags, const char * _file, int _line) {
    glad_glTextureStorageSparseAMD(texture, target, internalFormat, width, height, depth, layers, flags);
    gl_check_error(_file, _line);
}


void _glStencilOpValueAMD(GLenum face, GLuint value, const char * _file, int _line) {
    glad_glStencilOpValueAMD(face, value);
    gl_check_error(_file, _line);
}


void _glTessellationFactorAMD(GLfloat factor, const char * _file, int _line) {
    glad_glTessellationFactorAMD(factor);
    gl_check_error(_file, _line);
}


void _glTessellationModeAMD(GLenum mode, const char * _file, int _line) {
    glad_glTessellationModeAMD(mode);
    gl_check_error(_file, _line);
}


void _glElementPointerAPPLE(GLenum type, const void *pointer, const char * _file, int _line) {
    glad_glElementPointerAPPLE(type, pointer);
    gl_check_error(_file, _line);
}


void _glDrawElementArrayAPPLE(GLenum mode, GLint first, GLsizei count, const char * _file, int _line) {
    glad_glDrawElementArrayAPPLE(mode, first, count);
    gl_check_error(_file, _line);
}


void _glDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count, const char * _file, int _line) {
    glad_glDrawRangeElementArrayAPPLE(mode, start, end, first, count);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementArrayAPPLE(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line) {
    glad_glMultiDrawElementArrayAPPLE(mode, first, count, primcount);
    gl_check_error(_file, _line);
}


void _glMultiDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line) {
    glad_glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount);
    gl_check_error(_file, _line);
}


void _glGenFencesAPPLE(GLsizei n, GLuint *fences, const char * _file, int _line) {
    glad_glGenFencesAPPLE(n, fences);
    gl_check_error(_file, _line);
}


void _glDeleteFencesAPPLE(GLsizei n, const GLuint *fences, const char * _file, int _line) {
    glad_glDeleteFencesAPPLE(n, fences);
    gl_check_error(_file, _line);
}


void _glSetFenceAPPLE(GLuint fence, const char * _file, int _line) {
    glad_glSetFenceAPPLE(fence);
    gl_check_error(_file, _line);
}


GLboolean _glIsFenceAPPLE(GLuint fence, const char * _file, int _line) {
    auto val = glad_glIsFenceAPPLE(fence);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glTestFenceAPPLE(GLuint fence, const char * _file, int _line) {
    auto val = glad_glTestFenceAPPLE(fence);
    gl_check_error(_file, _line);
    return val;
}


void _glFinishFenceAPPLE(GLuint fence, const char * _file, int _line) {
    glad_glFinishFenceAPPLE(fence);
    gl_check_error(_file, _line);
}


GLboolean _glTestObjectAPPLE(GLenum object, GLuint name, const char * _file, int _line) {
    auto val = glad_glTestObjectAPPLE(object, name);
    gl_check_error(_file, _line);
    return val;
}


void _glFinishObjectAPPLE(GLenum object, GLint name, const char * _file, int _line) {
    glad_glFinishObjectAPPLE(object, name);
    gl_check_error(_file, _line);
}


void _glBufferParameteriAPPLE(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glBufferParameteriAPPLE(target, pname, param);
    gl_check_error(_file, _line);
}


void _glFlushMappedBufferRangeAPPLE(GLenum target, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glFlushMappedBufferRangeAPPLE(target, offset, size);
    gl_check_error(_file, _line);
}


GLenum _glObjectPurgeableAPPLE(GLenum objectType, GLuint name, GLenum option, const char * _file, int _line) {
    auto val = glad_glObjectPurgeableAPPLE(objectType, name, option);
    gl_check_error(_file, _line);
    return val;
}


GLenum _glObjectUnpurgeableAPPLE(GLenum objectType, GLuint name, GLenum option, const char * _file, int _line) {
    auto val = glad_glObjectUnpurgeableAPPLE(objectType, name, option);
    gl_check_error(_file, _line);
    return val;
}


void _glGetObjectParameterivAPPLE(GLenum objectType, GLuint name, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetObjectParameterivAPPLE(objectType, name, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureRangeAPPLE(GLenum target, GLsizei length, const void *pointer, const char * _file, int _line) {
    glad_glTextureRangeAPPLE(target, length, pointer);
    gl_check_error(_file, _line);
}


void _glGetTexParameterPointervAPPLE(GLenum target, GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetTexParameterPointervAPPLE(target, pname, params);
    gl_check_error(_file, _line);
}


void _glBindVertexArrayAPPLE(GLuint array, const char * _file, int _line) {
    glad_glBindVertexArrayAPPLE(array);
    gl_check_error(_file, _line);
}


void _glDeleteVertexArraysAPPLE(GLsizei n, const GLuint *arrays, const char * _file, int _line) {
    glad_glDeleteVertexArraysAPPLE(n, arrays);
    gl_check_error(_file, _line);
}


void _glGenVertexArraysAPPLE(GLsizei n, GLuint *arrays, const char * _file, int _line) {
    glad_glGenVertexArraysAPPLE(n, arrays);
    gl_check_error(_file, _line);
}


GLboolean _glIsVertexArrayAPPLE(GLuint array, const char * _file, int _line) {
    auto val = glad_glIsVertexArrayAPPLE(array);
    gl_check_error(_file, _line);
    return val;
}


void _glVertexArrayRangeAPPLE(GLsizei length, void *pointer, const char * _file, int _line) {
    glad_glVertexArrayRangeAPPLE(length, pointer);
    gl_check_error(_file, _line);
}


void _glFlushVertexArrayRangeAPPLE(GLsizei length, void *pointer, const char * _file, int _line) {
    glad_glFlushVertexArrayRangeAPPLE(length, pointer);
    gl_check_error(_file, _line);
}


void _glVertexArrayParameteriAPPLE(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glVertexArrayParameteriAPPLE(pname, param);
    gl_check_error(_file, _line);
}


void _glEnableVertexAttribAPPLE(GLuint index, GLenum pname, const char * _file, int _line) {
    glad_glEnableVertexAttribAPPLE(index, pname);
    gl_check_error(_file, _line);
}


void _glDisableVertexAttribAPPLE(GLuint index, GLenum pname, const char * _file, int _line) {
    glad_glDisableVertexAttribAPPLE(index, pname);
    gl_check_error(_file, _line);
}


GLboolean _glIsVertexAttribEnabledAPPLE(GLuint index, GLenum pname, const char * _file, int _line) {
    auto val = glad_glIsVertexAttribEnabledAPPLE(index, pname);
    gl_check_error(_file, _line);
    return val;
}


void _glMapVertexAttrib1dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points, const char * _file, int _line) {
    glad_glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points);
    gl_check_error(_file, _line);
}


void _glMapVertexAttrib1fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points, const char * _file, int _line) {
    glad_glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points);
    gl_check_error(_file, _line);
}


void _glMapVertexAttrib2dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points, const char * _file, int _line) {
    glad_glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
    gl_check_error(_file, _line);
}


void _glMapVertexAttrib2fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points, const char * _file, int _line) {
    glad_glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
    gl_check_error(_file, _line);
}


void _glMemoryBarrierByRegion(GLbitfield barriers, const char * _file, int _line) {
    glad_glMemoryBarrierByRegion(barriers);
    gl_check_error(_file, _line);
}


void _glPrimitiveBoundingBoxARB(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW, const char * _file, int _line) {
    glad_glPrimitiveBoundingBoxARB(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
    gl_check_error(_file, _line);
}


GLuint64 _glGetTextureHandleARB(GLuint texture, const char * _file, int _line) {
    auto val = glad_glGetTextureHandleARB(texture);
    gl_check_error(_file, _line);
    return val;
}


GLuint64 _glGetTextureSamplerHandleARB(GLuint texture, GLuint sampler, const char * _file, int _line) {
    auto val = glad_glGetTextureSamplerHandleARB(texture, sampler);
    gl_check_error(_file, _line);
    return val;
}


void _glMakeTextureHandleResidentARB(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeTextureHandleResidentARB(handle);
    gl_check_error(_file, _line);
}


void _glMakeTextureHandleNonResidentARB(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeTextureHandleNonResidentARB(handle);
    gl_check_error(_file, _line);
}


GLuint64 _glGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format, const char * _file, int _line) {
    auto val = glad_glGetImageHandleARB(texture, level, layered, layer, format);
    gl_check_error(_file, _line);
    return val;
}


void _glMakeImageHandleResidentARB(GLuint64 handle, GLenum access, const char * _file, int _line) {
    glad_glMakeImageHandleResidentARB(handle, access);
    gl_check_error(_file, _line);
}


void _glMakeImageHandleNonResidentARB(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeImageHandleNonResidentARB(handle);
    gl_check_error(_file, _line);
}


void _glUniformHandleui64ARB(GLint location, GLuint64 value, const char * _file, int _line) {
    glad_glUniformHandleui64ARB(location, value);
    gl_check_error(_file, _line);
}


void _glUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniformHandleui64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value, const char * _file, int _line) {
    glad_glProgramUniformHandleui64ARB(program, location, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *values, const char * _file, int _line) {
    glad_glProgramUniformHandleui64vARB(program, location, count, values);
    gl_check_error(_file, _line);
}


GLboolean _glIsTextureHandleResidentARB(GLuint64 handle, const char * _file, int _line) {
    auto val = glad_glIsTextureHandleResidentARB(handle);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsImageHandleResidentARB(GLuint64 handle, const char * _file, int _line) {
    auto val = glad_glIsImageHandleResidentARB(handle);
    gl_check_error(_file, _line);
    return val;
}


void _glVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x, const char * _file, int _line) {
    glad_glVertexAttribL1ui64ARB(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL1ui64vARB(index, v);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetVertexAttribLui64vARB(index, pname, params);
    gl_check_error(_file, _line);
}


void _glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line) {
    glad_glBufferStorage(target, size, data, flags);
    gl_check_error(_file, _line);
}


GLsync _glCreateSyncFromCLeventARB(struct _cl_context *context, struct _cl_event *event, GLbitfield flags, const char * _file, int _line) {
    auto val = glad_glCreateSyncFromCLeventARB(context, event, flags);
    gl_check_error(_file, _line);
    return val;
}


void _glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearBufferData(target, internalformat, format, type, data);
    gl_check_error(_file, _line);
}


void _glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearBufferSubData(target, internalformat, offset, size, format, type, data);
    gl_check_error(_file, _line);
}


void _glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearTexImage(texture, level, format, type, data);
    gl_check_error(_file, _line);
}


void _glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
    gl_check_error(_file, _line);
}


void _glClipControl(GLenum origin, GLenum depth, const char * _file, int _line) {
    glad_glClipControl(origin, depth);
    gl_check_error(_file, _line);
}


void _glClampColorARB(GLenum target, GLenum clamp, const char * _file, int _line) {
    glad_glClampColorARB(target, clamp);
    gl_check_error(_file, _line);
}


void _glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, const char * _file, int _line) {
    glad_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    gl_check_error(_file, _line);
}


void _glDispatchComputeIndirect(GLintptr indirect, const char * _file, int _line) {
    glad_glDispatchComputeIndirect(indirect);
    gl_check_error(_file, _line);
}


void _glDispatchComputeGroupSizeARB(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z, const char * _file, int _line) {
    glad_glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z);
    gl_check_error(_file, _line);
}


void _glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, const char * _file, int _line) {
    glad_glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    gl_check_error(_file, _line);
}


void _glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line) {
    glad_glDebugMessageControlARB(source, type, severity, count, ids, enabled);
    gl_check_error(_file, _line);
}


void _glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line) {
    glad_glDebugMessageInsertARB(source, type, id, severity, length, buf);
    gl_check_error(_file, _line);
}


void _glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void *userParam, const char * _file, int _line) {
    glad_glDebugMessageCallbackARB(callback, userParam);
    gl_check_error(_file, _line);
}


GLuint _glGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line) {
    auto val = glad_glGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog);
    gl_check_error(_file, _line);
    return val;
}


void _glCreateTransformFeedbacks(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glCreateTransformFeedbacks(n, ids);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer, const char * _file, int _line) {
    glad_glTransformFeedbackBufferBase(xfb, index, buffer);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetTransformFeedbackiv(xfb, pname, param);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint *param, const char * _file, int _line) {
    glad_glGetTransformFeedbacki_v(xfb, pname, index, param);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 *param, const char * _file, int _line) {
    glad_glGetTransformFeedbacki64_v(xfb, pname, index, param);
    gl_check_error(_file, _line);
}


void _glCreateBuffers(GLsizei n, GLuint *buffers, const char * _file, int _line) {
    glad_glCreateBuffers(n, buffers);
    gl_check_error(_file, _line);
}


void _glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line) {
    glad_glNamedBufferStorage(buffer, size, data, flags);
    gl_check_error(_file, _line);
}


void _glNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line) {
    glad_glNamedBufferData(buffer, size, data, usage);
    gl_check_error(_file, _line);
}


void _glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line) {
    glad_glNamedBufferSubData(buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void _glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line) {
    glad_glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
    gl_check_error(_file, _line);
}


void _glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearNamedBufferData(buffer, internalformat, format, type, data);
    gl_check_error(_file, _line);
}


void _glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
    gl_check_error(_file, _line);
}


void * _glMapNamedBuffer(GLuint buffer, GLenum access, const char * _file, int _line) {
    auto val = glad_glMapNamedBuffer(buffer, access);
    gl_check_error(_file, _line);
    return val;
}


void * _glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line) {
    auto val = glad_glMapNamedBufferRange(buffer, offset, length, access);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glUnmapNamedBuffer(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glUnmapNamedBuffer(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line) {
    glad_glFlushMappedNamedBufferRange(buffer, offset, length);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedBufferParameteriv(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 *params, const char * _file, int _line) {
    glad_glGetNamedBufferParameteri64v(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetNamedBufferPointerv(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line) {
    glad_glGetNamedBufferSubData(buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void _glCreateFramebuffers(GLsizei n, GLuint *framebuffers, const char * _file, int _line) {
    glad_glCreateFramebuffers(n, framebuffers);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line) {
    glad_glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glNamedFramebufferParameteri(framebuffer, pname, param);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glNamedFramebufferTexture(framebuffer, attachment, texture, level);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line) {
    glad_glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf, const char * _file, int _line) {
    glad_glNamedFramebufferDrawBuffer(framebuffer, buf);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs, const char * _file, int _line) {
    glad_glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src, const char * _file, int _line) {
    glad_glNamedFramebufferReadBuffer(framebuffer, src);
    gl_check_error(_file, _line);
}


void _glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, const char * _file, int _line) {
    glad_glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
    gl_check_error(_file, _line);
}


void _glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value, const char * _file, int _line) {
    glad_glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value, const char * _file, int _line) {
    glad_glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value, const char * _file, int _line) {
    glad_glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
    gl_check_error(_file, _line);
}


void _glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, const char * _file, int _line) {
    glad_glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
    gl_check_error(_file, _line);
}


void _glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line) {
    glad_glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    gl_check_error(_file, _line);
}


GLenum _glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target, const char * _file, int _line) {
    auto val = glad_glCheckNamedFramebufferStatus(framebuffer, target);
    gl_check_error(_file, _line);
    return val;
}


void _glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetNamedFramebufferParameteriv(framebuffer, pname, param);
    gl_check_error(_file, _line);
}


void _glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
    gl_check_error(_file, _line);
}


void _glCreateRenderbuffers(GLsizei n, GLuint *renderbuffers, const char * _file, int _line) {
    glad_glCreateRenderbuffers(n, renderbuffers);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
    gl_check_error(_file, _line);
}


void _glCreateTextures(GLenum target, GLsizei n, GLuint *textures, const char * _file, int _line) {
    glad_glCreateTextures(target, n, textures);
    gl_check_error(_file, _line);
}


void _glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glTextureBuffer(texture, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glTextureBufferRange(texture, internalformat, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line) {
    glad_glTextureStorage1D(texture, levels, internalformat, width);
    gl_check_error(_file, _line);
}


void _glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glTextureStorage2D(texture, levels, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glTextureStorage3D(texture, levels, internalformat, width, height, depth);
    gl_check_error(_file, _line);
}


void _glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glTextureParameterf(GLuint texture, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glTextureParameterf(texture, pname, param);
    gl_check_error(_file, _line);
}


void _glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat *param, const char * _file, int _line) {
    glad_glTextureParameterfv(texture, pname, param);
    gl_check_error(_file, _line);
}


void _glTextureParameteri(GLuint texture, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glTextureParameteri(texture, pname, param);
    gl_check_error(_file, _line);
}


void _glTextureParameterIiv(GLuint texture, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTextureParameterIiv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint *params, const char * _file, int _line) {
    glad_glTextureParameterIuiv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureParameteriv(GLuint texture, GLenum pname, const GLint *param, const char * _file, int _line) {
    glad_glTextureParameteriv(texture, pname, param);
    gl_check_error(_file, _line);
}


void _glGenerateTextureMipmap(GLuint texture, const char * _file, int _line) {
    glad_glGenerateTextureMipmap(texture);
    gl_check_error(_file, _line);
}


void _glBindTextureUnit(GLuint unit, GLuint texture, const char * _file, int _line) {
    glad_glBindTextureUnit(unit, texture);
    gl_check_error(_file, _line);
}


void _glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels, const char * _file, int _line) {
    glad_glGetTextureImage(texture, level, format, type, bufSize, pixels);
    gl_check_error(_file, _line);
}


void _glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void *pixels, const char * _file, int _line) {
    glad_glGetCompressedTextureImage(texture, level, bufSize, pixels);
    gl_check_error(_file, _line);
}


void _glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTextureLevelParameterfv(texture, level, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureLevelParameteriv(texture, level, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTextureParameterfv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureParameterIiv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetTextureParameterIuiv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameteriv(GLuint texture, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureParameteriv(texture, pname, params);
    gl_check_error(_file, _line);
}


void _glCreateVertexArrays(GLsizei n, GLuint *arrays, const char * _file, int _line) {
    glad_glCreateVertexArrays(n, arrays);
    gl_check_error(_file, _line);
}


void _glDisableVertexArrayAttrib(GLuint vaobj, GLuint index, const char * _file, int _line) {
    glad_glDisableVertexArrayAttrib(vaobj, index);
    gl_check_error(_file, _line);
}


void _glEnableVertexArrayAttrib(GLuint vaobj, GLuint index, const char * _file, int _line) {
    glad_glEnableVertexArrayAttrib(vaobj, index);
    gl_check_error(_file, _line);
}


void _glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer, const char * _file, int _line) {
    glad_glVertexArrayElementBuffer(vaobj, buffer);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line) {
    glad_glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides, const char * _file, int _line) {
    glad_glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
    gl_check_error(_file, _line);
}


void _glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex, const char * _file, int _line) {
    glad_glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
    gl_check_error(_file, _line);
}


void _glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor, const char * _file, int _line) {
    glad_glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetVertexArrayiv(vaobj, pname, param);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetVertexArrayIndexediv(vaobj, index, pname, param);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param, const char * _file, int _line) {
    glad_glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
    gl_check_error(_file, _line);
}


void _glCreateSamplers(GLsizei n, GLuint *samplers, const char * _file, int _line) {
    glad_glCreateSamplers(n, samplers);
    gl_check_error(_file, _line);
}


void _glCreateProgramPipelines(GLsizei n, GLuint *pipelines, const char * _file, int _line) {
    glad_glCreateProgramPipelines(n, pipelines);
    gl_check_error(_file, _line);
}


void _glCreateQueries(GLenum target, GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glCreateQueries(target, n, ids);
    gl_check_error(_file, _line);
}


void _glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line) {
    glad_glGetQueryBufferObjecti64v(id, buffer, pname, offset);
    gl_check_error(_file, _line);
}


void _glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line) {
    glad_glGetQueryBufferObjectiv(id, buffer, pname, offset);
    gl_check_error(_file, _line);
}


void _glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line) {
    glad_glGetQueryBufferObjectui64v(id, buffer, pname, offset);
    gl_check_error(_file, _line);
}


void _glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line) {
    glad_glGetQueryBufferObjectuiv(id, buffer, pname, offset);
    gl_check_error(_file, _line);
}


void _glDrawBuffersARB(GLsizei n, const GLenum *bufs, const char * _file, int _line) {
    glad_glDrawBuffersARB(n, bufs);
    gl_check_error(_file, _line);
}


void _glBlendEquationiARB(GLuint buf, GLenum mode, const char * _file, int _line) {
    glad_glBlendEquationiARB(buf, mode);
    gl_check_error(_file, _line);
}


void _glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line) {
    glad_glBlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
    gl_check_error(_file, _line);
}


void _glBlendFunciARB(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line) {
    glad_glBlendFunciARB(buf, src, dst);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
    gl_check_error(_file, _line);
}


void _glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount, const char * _file, int _line) {
    glad_glDrawArraysInstancedARB(mode, first, count, primcount);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstancedARB(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, const char * _file, int _line) {
    glad_glDrawElementsInstancedARB(mode, count, type, indices, primcount);
    gl_check_error(_file, _line);
}


void _glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void *string, const char * _file, int _line) {
    glad_glProgramStringARB(target, format, len, string);
    gl_check_error(_file, _line);
}


void _glBindProgramARB(GLenum target, GLuint program, const char * _file, int _line) {
    glad_glBindProgramARB(target, program);
    gl_check_error(_file, _line);
}


void _glDeleteProgramsARB(GLsizei n, const GLuint *programs, const char * _file, int _line) {
    glad_glDeleteProgramsARB(n, programs);
    gl_check_error(_file, _line);
}


void _glGenProgramsARB(GLsizei n, GLuint *programs, const char * _file, int _line) {
    glad_glGenProgramsARB(n, programs);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glProgramEnvParameter4dARB(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line) {
    glad_glProgramEnvParameter4dvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glProgramEnvParameter4fARB(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line) {
    glad_glProgramEnvParameter4fvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glProgramLocalParameter4dARB(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line) {
    glad_glProgramLocalParameter4dvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glProgramLocalParameter4fARB(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line) {
    glad_glProgramLocalParameter4fvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble *params, const char * _file, int _line) {
    glad_glGetProgramEnvParameterdvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat *params, const char * _file, int _line) {
    glad_glGetProgramEnvParameterfvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble *params, const char * _file, int _line) {
    glad_glGetProgramLocalParameterdvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat *params, const char * _file, int _line) {
    glad_glGetProgramLocalParameterfvARB(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramivARB(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetProgramStringARB(GLenum target, GLenum pname, void *string, const char * _file, int _line) {
    glad_glGetProgramStringARB(target, pname, string);
    gl_check_error(_file, _line);
}


GLboolean _glIsProgramARB(GLuint program, const char * _file, int _line) {
    auto val = glad_glIsProgramARB(program);
    gl_check_error(_file, _line);
    return val;
}


void _glFramebufferParameteri(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glFramebufferParameteri(target, pname, param);
    gl_check_error(_file, _line);
}


void _glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFramebufferParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramParameteriARB(GLuint program, GLenum pname, GLint value, const char * _file, int _line) {
    glad_glProgramParameteriARB(program, pname, value);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureARB(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTextureARB(target, attachment, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureLayerARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line) {
    glad_glFramebufferTextureLayerARB(target, attachment, texture, level, layer);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureFaceARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line) {
    glad_glFramebufferTextureFaceARB(target, attachment, texture, level, face);
    gl_check_error(_file, _line);
}


void _glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels, const char * _file, int _line) {
    glad_glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
    gl_check_error(_file, _line);
}


void _glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels, const char * _file, int _line) {
    glad_glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
    gl_check_error(_file, _line);
}


void _glSpecializeShaderARB(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue, const char * _file, int _line) {
    glad_glSpecializeShaderARB(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
    gl_check_error(_file, _line);
}


void _glUniform1i64ARB(GLint location, GLint64 x, const char * _file, int _line) {
    glad_glUniform1i64ARB(location, x);
    gl_check_error(_file, _line);
}


void _glUniform2i64ARB(GLint location, GLint64 x, GLint64 y, const char * _file, int _line) {
    glad_glUniform2i64ARB(location, x, y);
    gl_check_error(_file, _line);
}


void _glUniform3i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z, const char * _file, int _line) {
    glad_glUniform3i64ARB(location, x, y, z);
    gl_check_error(_file, _line);
}


void _glUniform4i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w, const char * _file, int _line) {
    glad_glUniform4i64ARB(location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glUniform1i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glUniform1i64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glUniform2i64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glUniform3i64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glUniform4i64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform1ui64ARB(GLint location, GLuint64 x, const char * _file, int _line) {
    glad_glUniform1ui64ARB(location, x);
    gl_check_error(_file, _line);
}


void _glUniform2ui64ARB(GLint location, GLuint64 x, GLuint64 y, const char * _file, int _line) {
    glad_glUniform2ui64ARB(location, x, y);
    gl_check_error(_file, _line);
}


void _glUniform3ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, const char * _file, int _line) {
    glad_glUniform3ui64ARB(location, x, y, z);
    gl_check_error(_file, _line);
}


void _glUniform4ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w, const char * _file, int _line) {
    glad_glUniform4ui64ARB(location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glUniform1ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniform1ui64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniform2ui64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniform3ui64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniform4ui64vARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glGetUniformi64vARB(GLuint program, GLint location, GLint64 *params, const char * _file, int _line) {
    glad_glGetUniformi64vARB(program, location, params);
    gl_check_error(_file, _line);
}


void _glGetUniformui64vARB(GLuint program, GLint location, GLuint64 *params, const char * _file, int _line) {
    glad_glGetUniformui64vARB(program, location, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformi64vARB(GLuint program, GLint location, GLsizei bufSize, GLint64 *params, const char * _file, int _line) {
    glad_glGetnUniformi64vARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformui64vARB(GLuint program, GLint location, GLsizei bufSize, GLuint64 *params, const char * _file, int _line) {
    glad_glGetnUniformui64vARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glProgramUniform1i64ARB(GLuint program, GLint location, GLint64 x, const char * _file, int _line) {
    glad_glProgramUniform1i64ARB(program, location, x);
    gl_check_error(_file, _line);
}


void _glProgramUniform2i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, const char * _file, int _line) {
    glad_glProgramUniform2i64ARB(program, location, x, y);
    gl_check_error(_file, _line);
}


void _glProgramUniform3i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, const char * _file, int _line) {
    glad_glProgramUniform3i64ARB(program, location, x, y, z);
    gl_check_error(_file, _line);
}


void _glProgramUniform4i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w, const char * _file, int _line) {
    glad_glProgramUniform4i64ARB(program, location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramUniform1i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glProgramUniform1i64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glProgramUniform2i64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glProgramUniform3i64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line) {
    glad_glProgramUniform4i64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ui64ARB(GLuint program, GLint location, GLuint64 x, const char * _file, int _line) {
    glad_glProgramUniform1ui64ARB(program, location, x);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, const char * _file, int _line) {
    glad_glProgramUniform2ui64ARB(program, location, x, y);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, const char * _file, int _line) {
    glad_glProgramUniform3ui64ARB(program, location, x, y, z);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w, const char * _file, int _line) {
    glad_glProgramUniform4ui64ARB(program, location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glProgramUniform1ui64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glProgramUniform2ui64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glProgramUniform3ui64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glProgramUniform4ui64vARB(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line) {
    glad_glColorTable(target, internalformat, width, format, type, table);
    gl_check_error(_file, _line);
}


void _glColorTableParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glColorTableParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glColorTableParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glColorTableParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyColorTable(target, internalformat, x, y, width);
    gl_check_error(_file, _line);
}


void _glGetColorTable(GLenum target, GLenum format, GLenum type, void *table, const char * _file, int _line) {
    glad_glGetColorTable(target, format, type, table);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetColorTableParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetColorTableParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glColorSubTable(target, start, count, format, type, data);
    gl_check_error(_file, _line);
}


void _glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyColorSubTable(target, start, x, y, width);
    gl_check_error(_file, _line);
}


void _glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image, const char * _file, int _line) {
    glad_glConvolutionFilter1D(target, internalformat, width, format, type, image);
    gl_check_error(_file, _line);
}


void _glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image, const char * _file, int _line) {
    glad_glConvolutionFilter2D(target, internalformat, width, height, format, type, image);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params, const char * _file, int _line) {
    glad_glConvolutionParameterf(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glConvolutionParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameteri(GLenum target, GLenum pname, GLint params, const char * _file, int _line) {
    glad_glConvolutionParameteri(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glConvolutionParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyConvolutionFilter1D(target, internalformat, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyConvolutionFilter2D(target, internalformat, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, void *image, const char * _file, int _line) {
    glad_glGetConvolutionFilter(target, format, type, image);
    gl_check_error(_file, _line);
}


void _glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetConvolutionParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetConvolutionParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSeparableFilter(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span, const char * _file, int _line) {
    glad_glGetSeparableFilter(target, format, type, row, column, span);
    gl_check_error(_file, _line);
}


void _glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column, const char * _file, int _line) {
    glad_glSeparableFilter2D(target, internalformat, width, height, format, type, row, column);
    gl_check_error(_file, _line);
}


void _glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line) {
    glad_glGetHistogram(target, reset, format, type, values);
    gl_check_error(_file, _line);
}


void _glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetHistogramParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetHistogramParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetHistogramParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line) {
    glad_glGetMinmax(target, reset, format, type, values);
    gl_check_error(_file, _line);
}


void _glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMinmaxParameterfv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMinmaxParameteriv(target, pname, params);
    gl_check_error(_file, _line);
}


void _glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, const char * _file, int _line) {
    glad_glHistogram(target, width, internalformat, sink);
    gl_check_error(_file, _line);
}


void _glMinmax(GLenum target, GLenum internalformat, GLboolean sink, const char * _file, int _line) {
    glad_glMinmax(target, internalformat, sink);
    gl_check_error(_file, _line);
}


void _glResetHistogram(GLenum target, const char * _file, int _line) {
    glad_glResetHistogram(target);
    gl_check_error(_file, _line);
}


void _glResetMinmax(GLenum target, const char * _file, int _line) {
    glad_glResetMinmax(target);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysIndirectCountARB(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride);
    gl_check_error(_file, _line);
}


void _glVertexAttribDivisorARB(GLuint index, GLuint divisor, const char * _file, int _line) {
    glad_glVertexAttribDivisorARB(index, divisor);
    gl_check_error(_file, _line);
}


void _glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params, const char * _file, int _line) {
    glad_glGetInternalformati64v(target, internalformat, pname, count, params);
    gl_check_error(_file, _line);
}


void _glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
    gl_check_error(_file, _line);
}


void _glInvalidateTexImage(GLuint texture, GLint level, const char * _file, int _line) {
    glad_glInvalidateTexImage(texture, level);
    gl_check_error(_file, _line);
}


void _glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line) {
    glad_glInvalidateBufferSubData(buffer, offset, length);
    gl_check_error(_file, _line);
}


void _glInvalidateBufferData(GLuint buffer, const char * _file, int _line) {
    glad_glInvalidateBufferData(buffer);
    gl_check_error(_file, _line);
}


void _glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, const char * _file, int _line) {
    glad_glInvalidateFramebuffer(target, numAttachments, attachments);
    gl_check_error(_file, _line);
}


void _glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glCurrentPaletteMatrixARB(GLint index, const char * _file, int _line) {
    glad_glCurrentPaletteMatrixARB(index);
    gl_check_error(_file, _line);
}


void _glMatrixIndexubvARB(GLint size, const GLubyte *indices, const char * _file, int _line) {
    glad_glMatrixIndexubvARB(size, indices);
    gl_check_error(_file, _line);
}


void _glMatrixIndexusvARB(GLint size, const GLushort *indices, const char * _file, int _line) {
    glad_glMatrixIndexusvARB(size, indices);
    gl_check_error(_file, _line);
}


void _glMatrixIndexuivARB(GLint size, const GLuint *indices, const char * _file, int _line) {
    glad_glMatrixIndexuivARB(size, indices);
    gl_check_error(_file, _line);
}


void _glMatrixIndexPointerARB(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glMatrixIndexPointerARB(size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const char * _file, int _line) {
    glad_glBindBuffersBase(target, first, count, buffers);
    gl_check_error(_file, _line);
}


void _glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes, const char * _file, int _line) {
    glad_glBindBuffersRange(target, first, count, buffers, offsets, sizes);
    gl_check_error(_file, _line);
}


void _glBindTextures(GLuint first, GLsizei count, const GLuint *textures, const char * _file, int _line) {
    glad_glBindTextures(first, count, textures);
    gl_check_error(_file, _line);
}


void _glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers, const char * _file, int _line) {
    glad_glBindSamplers(first, count, samplers);
    gl_check_error(_file, _line);
}


void _glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures, const char * _file, int _line) {
    glad_glBindImageTextures(first, count, textures);
    gl_check_error(_file, _line);
}


void _glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides, const char * _file, int _line) {
    glad_glBindVertexBuffers(first, count, buffers, offsets, strides);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
    gl_check_error(_file, _line);
}


void _glSampleCoverageARB(GLfloat value, GLboolean invert, const char * _file, int _line) {
    glad_glSampleCoverageARB(value, invert);
    gl_check_error(_file, _line);
}


void _glActiveTextureARB(GLenum texture, const char * _file, int _line) {
    glad_glActiveTextureARB(texture);
    gl_check_error(_file, _line);
}


void _glClientActiveTextureARB(GLenum texture, const char * _file, int _line) {
    glad_glClientActiveTextureARB(texture);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1dARB(GLenum target, GLdouble s, const char * _file, int _line) {
    glad_glMultiTexCoord1dARB(target, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1dvARB(GLenum target, const GLdouble *v, const char * _file, int _line) {
    glad_glMultiTexCoord1dvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1fARB(GLenum target, GLfloat s, const char * _file, int _line) {
    glad_glMultiTexCoord1fARB(target, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1fvARB(GLenum target, const GLfloat *v, const char * _file, int _line) {
    glad_glMultiTexCoord1fvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1iARB(GLenum target, GLint s, const char * _file, int _line) {
    glad_glMultiTexCoord1iARB(target, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1ivARB(GLenum target, const GLint *v, const char * _file, int _line) {
    glad_glMultiTexCoord1ivARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1sARB(GLenum target, GLshort s, const char * _file, int _line) {
    glad_glMultiTexCoord1sARB(target, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1svARB(GLenum target, const GLshort *v, const char * _file, int _line) {
    glad_glMultiTexCoord1svARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t, const char * _file, int _line) {
    glad_glMultiTexCoord2dARB(target, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2dvARB(GLenum target, const GLdouble *v, const char * _file, int _line) {
    glad_glMultiTexCoord2dvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t, const char * _file, int _line) {
    glad_glMultiTexCoord2fARB(target, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2fvARB(GLenum target, const GLfloat *v, const char * _file, int _line) {
    glad_glMultiTexCoord2fvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2iARB(GLenum target, GLint s, GLint t, const char * _file, int _line) {
    glad_glMultiTexCoord2iARB(target, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2ivARB(GLenum target, const GLint *v, const char * _file, int _line) {
    glad_glMultiTexCoord2ivARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t, const char * _file, int _line) {
    glad_glMultiTexCoord2sARB(target, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2svARB(GLenum target, const GLshort *v, const char * _file, int _line) {
    glad_glMultiTexCoord2svARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, const char * _file, int _line) {
    glad_glMultiTexCoord3dARB(target, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3dvARB(GLenum target, const GLdouble *v, const char * _file, int _line) {
    glad_glMultiTexCoord3dvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, const char * _file, int _line) {
    glad_glMultiTexCoord3fARB(target, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3fvARB(GLenum target, const GLfloat *v, const char * _file, int _line) {
    glad_glMultiTexCoord3fvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r, const char * _file, int _line) {
    glad_glMultiTexCoord3iARB(target, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3ivARB(GLenum target, const GLint *v, const char * _file, int _line) {
    glad_glMultiTexCoord3ivARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r, const char * _file, int _line) {
    glad_glMultiTexCoord3sARB(target, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3svARB(GLenum target, const GLshort *v, const char * _file, int _line) {
    glad_glMultiTexCoord3svARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q, const char * _file, int _line) {
    glad_glMultiTexCoord4dARB(target, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4dvARB(GLenum target, const GLdouble *v, const char * _file, int _line) {
    glad_glMultiTexCoord4dvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q, const char * _file, int _line) {
    glad_glMultiTexCoord4fARB(target, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4fvARB(GLenum target, const GLfloat *v, const char * _file, int _line) {
    glad_glMultiTexCoord4fvARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q, const char * _file, int _line) {
    glad_glMultiTexCoord4iARB(target, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4ivARB(GLenum target, const GLint *v, const char * _file, int _line) {
    glad_glMultiTexCoord4ivARB(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q, const char * _file, int _line) {
    glad_glMultiTexCoord4sARB(target, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4svARB(GLenum target, const GLshort *v, const char * _file, int _line) {
    glad_glMultiTexCoord4svARB(target, v);
    gl_check_error(_file, _line);
}


void _glGenQueriesARB(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glGenQueriesARB(n, ids);
    gl_check_error(_file, _line);
}


void _glDeleteQueriesARB(GLsizei n, const GLuint *ids, const char * _file, int _line) {
    glad_glDeleteQueriesARB(n, ids);
    gl_check_error(_file, _line);
}


GLboolean _glIsQueryARB(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsQueryARB(id);
    gl_check_error(_file, _line);
    return val;
}


void _glBeginQueryARB(GLenum target, GLuint id, const char * _file, int _line) {
    glad_glBeginQueryARB(target, id);
    gl_check_error(_file, _line);
}


void _glEndQueryARB(GLenum target, const char * _file, int _line) {
    glad_glEndQueryARB(target);
    gl_check_error(_file, _line);
}


void _glGetQueryivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetQueryivARB(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectivARB(GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetQueryObjectivARB(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetQueryObjectuivARB(id, pname, params);
    gl_check_error(_file, _line);
}


void _glMaxShaderCompilerThreadsARB(GLuint count, const char * _file, int _line) {
    glad_glMaxShaderCompilerThreadsARB(count);
    gl_check_error(_file, _line);
}


void _glPointParameterfARB(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPointParameterfARB(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameterfvARB(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPointParameterfvARB(pname, params);
    gl_check_error(_file, _line);
}


void _glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp, const char * _file, int _line) {
    glad_glPolygonOffsetClamp(factor, units, clamp);
    gl_check_error(_file, _line);
}


void _glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramInterfaceiv(program, programInterface, pname, params);
    gl_check_error(_file, _line);
}


GLuint _glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetProgramResourceIndex(program, programInterface, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line) {
    glad_glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
    gl_check_error(_file, _line);
}


void _glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params, const char * _file, int _line) {
    glad_glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params);
    gl_check_error(_file, _line);
}


GLint _glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetProgramResourceLocation(program, programInterface, name);
    gl_check_error(_file, _line);
    return val;
}


GLint _glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetProgramResourceLocationIndex(program, programInterface, name);
    gl_check_error(_file, _line);
    return val;
}


GLenum _glGetGraphicsResetStatusARB(const char * _file, int _line) {
    auto val = glad_glGetGraphicsResetStatusARB();
    gl_check_error(_file, _line);
    return val;
}


void _glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *img, const char * _file, int _line) {
    glad_glGetnTexImageARB(target, level, format, type, bufSize, img);
    gl_check_error(_file, _line);
}


void _glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line) {
    glad_glReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
    gl_check_error(_file, _line);
}


void _glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, void *img, const char * _file, int _line) {
    glad_glGetnCompressedTexImageARB(target, lod, bufSize, img);
    gl_check_error(_file, _line);
}


void _glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line) {
    glad_glGetnUniformfvARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line) {
    glad_glGetnUniformivARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line) {
    glad_glGetnUniformuivARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble *params, const char * _file, int _line) {
    glad_glGetnUniformdvARB(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v, const char * _file, int _line) {
    glad_glGetnMapdvARB(target, query, bufSize, v);
    gl_check_error(_file, _line);
}


void _glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v, const char * _file, int _line) {
    glad_glGetnMapfvARB(target, query, bufSize, v);
    gl_check_error(_file, _line);
}


void _glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint *v, const char * _file, int _line) {
    glad_glGetnMapivARB(target, query, bufSize, v);
    gl_check_error(_file, _line);
}


void _glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat *values, const char * _file, int _line) {
    glad_glGetnPixelMapfvARB(map, bufSize, values);
    gl_check_error(_file, _line);
}


void _glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint *values, const char * _file, int _line) {
    glad_glGetnPixelMapuivARB(map, bufSize, values);
    gl_check_error(_file, _line);
}


void _glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort *values, const char * _file, int _line) {
    glad_glGetnPixelMapusvARB(map, bufSize, values);
    gl_check_error(_file, _line);
}


void _glGetnPolygonStippleARB(GLsizei bufSize, GLubyte *pattern, const char * _file, int _line) {
    glad_glGetnPolygonStippleARB(bufSize, pattern);
    gl_check_error(_file, _line);
}


void _glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table, const char * _file, int _line) {
    glad_glGetnColorTableARB(target, format, type, bufSize, table);
    gl_check_error(_file, _line);
}


void _glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image, const char * _file, int _line) {
    glad_glGetnConvolutionFilterARB(target, format, type, bufSize, image);
    gl_check_error(_file, _line);
}


void _glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span, const char * _file, int _line) {
    glad_glGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
    gl_check_error(_file, _line);
}


void _glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values, const char * _file, int _line) {
    glad_glGetnHistogramARB(target, reset, format, type, bufSize, values);
    gl_check_error(_file, _line);
}


void _glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values, const char * _file, int _line) {
    glad_glGetnMinmaxARB(target, reset, format, type, bufSize, values);
    gl_check_error(_file, _line);
}


void _glFramebufferSampleLocationsfvARB(GLenum target, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glFramebufferSampleLocationsfvARB(target, start, count, v);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferSampleLocationsfvARB(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glNamedFramebufferSampleLocationsfvARB(framebuffer, start, count, v);
    gl_check_error(_file, _line);
}


void _glEvaluateDepthValuesARB(const char * _file, int _line) {
    glad_glEvaluateDepthValuesARB();
    gl_check_error(_file, _line);
}


void _glMinSampleShadingARB(GLfloat value, const char * _file, int _line) {
    glad_glMinSampleShadingARB(value);
    gl_check_error(_file, _line);
}


void _glDeleteObjectARB(GLhandleARB obj, const char * _file, int _line) {
    glad_glDeleteObjectARB(obj);
    gl_check_error(_file, _line);
}


GLhandleARB _glGetHandleARB(GLenum pname, const char * _file, int _line) {
    auto val = glad_glGetHandleARB(pname);
    gl_check_error(_file, _line);
    return val;
}


void _glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj, const char * _file, int _line) {
    glad_glDetachObjectARB(containerObj, attachedObj);
    gl_check_error(_file, _line);
}


GLhandleARB _glCreateShaderObjectARB(GLenum shaderType, const char * _file, int _line) {
    auto val = glad_glCreateShaderObjectARB(shaderType);
    gl_check_error(_file, _line);
    return val;
}


void _glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, const GLcharARB **string, const GLint *length, const char * _file, int _line) {
    glad_glShaderSourceARB(shaderObj, count, string, length);
    gl_check_error(_file, _line);
}


void _glCompileShaderARB(GLhandleARB shaderObj, const char * _file, int _line) {
    glad_glCompileShaderARB(shaderObj);
    gl_check_error(_file, _line);
}


GLhandleARB _glCreateProgramObjectARB(const char * _file, int _line) {
    auto val = glad_glCreateProgramObjectARB();
    gl_check_error(_file, _line);
    return val;
}


void _glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj, const char * _file, int _line) {
    glad_glAttachObjectARB(containerObj, obj);
    gl_check_error(_file, _line);
}


void _glLinkProgramARB(GLhandleARB programObj, const char * _file, int _line) {
    glad_glLinkProgramARB(programObj);
    gl_check_error(_file, _line);
}


void _glUseProgramObjectARB(GLhandleARB programObj, const char * _file, int _line) {
    glad_glUseProgramObjectARB(programObj);
    gl_check_error(_file, _line);
}


void _glValidateProgramARB(GLhandleARB programObj, const char * _file, int _line) {
    glad_glValidateProgramARB(programObj);
    gl_check_error(_file, _line);
}


void _glUniform1fARB(GLint location, GLfloat v0, const char * _file, int _line) {
    glad_glUniform1fARB(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2fARB(GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line) {
    glad_glUniform2fARB(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line) {
    glad_glUniform3fARB(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line) {
    glad_glUniform4fARB(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1iARB(GLint location, GLint v0, const char * _file, int _line) {
    glad_glUniform1iARB(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2iARB(GLint location, GLint v0, GLint v1, const char * _file, int _line) {
    glad_glUniform2iARB(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line) {
    glad_glUniform3iARB(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line) {
    glad_glUniform4iARB(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform1fvARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform2fvARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform3fvARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glUniform4fvARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform1ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform1ivARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform2ivARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform3ivARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glUniform4ivARB(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix2fvARB(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix3fvARB(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glUniformMatrix4fvARB(location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetObjectParameterfvARB(obj, pname, params);
    gl_check_error(_file, _line);
}


void _glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetObjectParameterivARB(obj, pname, params);
    gl_check_error(_file, _line);
}


void _glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog, const char * _file, int _line) {
    glad_glGetInfoLogARB(obj, maxLength, length, infoLog);
    gl_check_error(_file, _line);
}


void _glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj, const char * _file, int _line) {
    glad_glGetAttachedObjectsARB(containerObj, maxCount, count, obj);
    gl_check_error(_file, _line);
}


GLint _glGetUniformLocationARB(GLhandleARB programObj, const GLcharARB *name, const char * _file, int _line) {
    auto val = glad_glGetUniformLocationARB(programObj, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name, const char * _file, int _line) {
    glad_glGetActiveUniformARB(programObj, index, maxLength, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat *params, const char * _file, int _line) {
    glad_glGetUniformfvARB(programObj, location, params);
    gl_check_error(_file, _line);
}


void _glGetUniformivARB(GLhandleARB programObj, GLint location, GLint *params, const char * _file, int _line) {
    glad_glGetUniformivARB(programObj, location, params);
    gl_check_error(_file, _line);
}


void _glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source, const char * _file, int _line) {
    glad_glGetShaderSourceARB(obj, maxLength, length, source);
    gl_check_error(_file, _line);
}


void _glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding, const char * _file, int _line) {
    glad_glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
    gl_check_error(_file, _line);
}


void _glNamedStringARB(GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string, const char * _file, int _line) {
    glad_glNamedStringARB(type, namelen, name, stringlen, string);
    gl_check_error(_file, _line);
}


void _glDeleteNamedStringARB(GLint namelen, const GLchar *name, const char * _file, int _line) {
    glad_glDeleteNamedStringARB(namelen, name);
    gl_check_error(_file, _line);
}


void _glCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar *const*path, const GLint *length, const char * _file, int _line) {
    glad_glCompileShaderIncludeARB(shader, count, path, length);
    gl_check_error(_file, _line);
}


GLboolean _glIsNamedStringARB(GLint namelen, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glIsNamedStringARB(namelen, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetNamedStringARB(GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string, const char * _file, int _line) {
    glad_glGetNamedStringARB(namelen, name, bufSize, stringlen, string);
    gl_check_error(_file, _line);
}


void _glGetNamedStringivARB(GLint namelen, const GLchar *name, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedStringivARB(namelen, name, pname, params);
    gl_check_error(_file, _line);
}


void _glBufferPageCommitmentARB(GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line) {
    glad_glBufferPageCommitmentARB(target, offset, size, commit);
    gl_check_error(_file, _line);
}


void _glNamedBufferPageCommitmentEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line) {
    glad_glNamedBufferPageCommitmentEXT(buffer, offset, size, commit);
    gl_check_error(_file, _line);
}


void _glNamedBufferPageCommitmentARB(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line) {
    glad_glNamedBufferPageCommitmentARB(buffer, offset, size, commit);
    gl_check_error(_file, _line);
}


void _glTexPageCommitmentARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit, const char * _file, int _line) {
    glad_glTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, commit);
    gl_check_error(_file, _line);
}


void _glTextureBarrier(const char * _file, int _line) {
    glad_glTextureBarrier();
    gl_check_error(_file, _line);
}


void _glTexBufferARB(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glTexBufferARB(target, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glTexBufferRange(target, internalformat, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glCompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line) {
    glad_glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data);
    gl_check_error(_file, _line);
}


void _glGetCompressedTexImageARB(GLenum target, GLint level, void *img, const char * _file, int _line) {
    glad_glGetCompressedTexImageARB(target, level, img);
    gl_check_error(_file, _line);
}


void _glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers, const char * _file, int _line) {
    glad_glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
    gl_check_error(_file, _line);
}


void _glLoadTransposeMatrixfARB(const GLfloat *m, const char * _file, int _line) {
    glad_glLoadTransposeMatrixfARB(m);
    gl_check_error(_file, _line);
}


void _glLoadTransposeMatrixdARB(const GLdouble *m, const char * _file, int _line) {
    glad_glLoadTransposeMatrixdARB(m);
    gl_check_error(_file, _line);
}


void _glMultTransposeMatrixfARB(const GLfloat *m, const char * _file, int _line) {
    glad_glMultTransposeMatrixfARB(m);
    gl_check_error(_file, _line);
}


void _glMultTransposeMatrixdARB(const GLdouble *m, const char * _file, int _line) {
    glad_glMultTransposeMatrixdARB(m);
    gl_check_error(_file, _line);
}


void _glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line) {
    glad_glBindVertexBuffer(bindingindex, buffer, offset, stride);
    gl_check_error(_file, _line);
}


void _glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexAttribIFormat(attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexAttribLFormat(attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexAttribBinding(GLuint attribindex, GLuint bindingindex, const char * _file, int _line) {
    glad_glVertexAttribBinding(attribindex, bindingindex);
    gl_check_error(_file, _line);
}


void _glVertexBindingDivisor(GLuint bindingindex, GLuint divisor, const char * _file, int _line) {
    glad_glVertexBindingDivisor(bindingindex, divisor);
    gl_check_error(_file, _line);
}


void _glWeightbvARB(GLint size, const GLbyte *weights, const char * _file, int _line) {
    glad_glWeightbvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightsvARB(GLint size, const GLshort *weights, const char * _file, int _line) {
    glad_glWeightsvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightivARB(GLint size, const GLint *weights, const char * _file, int _line) {
    glad_glWeightivARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightfvARB(GLint size, const GLfloat *weights, const char * _file, int _line) {
    glad_glWeightfvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightdvARB(GLint size, const GLdouble *weights, const char * _file, int _line) {
    glad_glWeightdvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightubvARB(GLint size, const GLubyte *weights, const char * _file, int _line) {
    glad_glWeightubvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightusvARB(GLint size, const GLushort *weights, const char * _file, int _line) {
    glad_glWeightusvARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightuivARB(GLint size, const GLuint *weights, const char * _file, int _line) {
    glad_glWeightuivARB(size, weights);
    gl_check_error(_file, _line);
}


void _glWeightPointerARB(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glWeightPointerARB(size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glVertexBlendARB(GLint count, const char * _file, int _line) {
    glad_glVertexBlendARB(count);
    gl_check_error(_file, _line);
}


void _glBindBufferARB(GLenum target, GLuint buffer, const char * _file, int _line) {
    glad_glBindBufferARB(target, buffer);
    gl_check_error(_file, _line);
}


void _glDeleteBuffersARB(GLsizei n, const GLuint *buffers, const char * _file, int _line) {
    glad_glDeleteBuffersARB(n, buffers);
    gl_check_error(_file, _line);
}


void _glGenBuffersARB(GLsizei n, GLuint *buffers, const char * _file, int _line) {
    glad_glGenBuffersARB(n, buffers);
    gl_check_error(_file, _line);
}


GLboolean _glIsBufferARB(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glIsBufferARB(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBufferDataARB(GLenum target, GLsizeiptrARB size, const void *data, GLenum usage, const char * _file, int _line) {
    glad_glBufferDataARB(target, size, data, usage);
    gl_check_error(_file, _line);
}


void _glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void *data, const char * _file, int _line) {
    glad_glBufferSubDataARB(target, offset, size, data);
    gl_check_error(_file, _line);
}


void _glGetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void *data, const char * _file, int _line) {
    glad_glGetBufferSubDataARB(target, offset, size, data);
    gl_check_error(_file, _line);
}


void * _glMapBufferARB(GLenum target, GLenum access, const char * _file, int _line) {
    auto val = glad_glMapBufferARB(target, access);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glUnmapBufferARB(GLenum target, const char * _file, int _line) {
    auto val = glad_glUnmapBufferARB(target);
    gl_check_error(_file, _line);
    return val;
}


void _glGetBufferParameterivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetBufferParameterivARB(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetBufferPointervARB(GLenum target, GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetBufferPointervARB(target, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1dARB(GLuint index, GLdouble x, const char * _file, int _line) {
    glad_glVertexAttrib1dARB(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1dvARB(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib1dvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1fARB(GLuint index, GLfloat x, const char * _file, int _line) {
    glad_glVertexAttrib1fARB(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1fvARB(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib1fvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1sARB(GLuint index, GLshort x, const char * _file, int _line) {
    glad_glVertexAttrib1sARB(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1svARB(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib1svARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexAttrib2dARB(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2dvARB(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib2dvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glVertexAttrib2fARB(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2fvARB(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib2fvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y, const char * _file, int _line) {
    glad_glVertexAttrib2sARB(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2svARB(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib2svARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexAttrib3dARB(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3dvARB(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib3dvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glVertexAttrib3fARB(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3fvARB(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib3fvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glVertexAttrib3sARB(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3svARB(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib3svARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NbvARB(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4NbvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NivARB(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttrib4NivARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NsvARB(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib4NsvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line) {
    glad_glVertexAttrib4NubARB(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NubvARB(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4NubvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NuivARB(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttrib4NuivARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4NusvARB(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttrib4NusvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4bvARB(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4bvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexAttrib4dARB(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4dvARB(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib4dvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glVertexAttrib4fARB(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4fvARB(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib4fvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4ivARB(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttrib4ivARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line) {
    glad_glVertexAttrib4sARB(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4svARB(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib4svARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4ubvARB(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4ubvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4uivARB(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttrib4uivARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4usvARB(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttrib4usvARB(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribPointerARB(index, size, type, normalized, stride, pointer);
    gl_check_error(_file, _line);
}


void _glEnableVertexAttribArrayARB(GLuint index, const char * _file, int _line) {
    glad_glEnableVertexAttribArrayARB(index);
    gl_check_error(_file, _line);
}


void _glDisableVertexAttribArrayARB(GLuint index, const char * _file, int _line) {
    glad_glDisableVertexAttribArrayARB(index);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVertexAttribdvARB(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVertexAttribfvARB(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribivARB(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribivARB(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribPointervARB(GLuint index, GLenum pname, void **pointer, const char * _file, int _line) {
    glad_glGetVertexAttribPointervARB(index, pname, pointer);
    gl_check_error(_file, _line);
}


void _glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB *name, const char * _file, int _line) {
    glad_glBindAttribLocationARB(programObj, index, name);
    gl_check_error(_file, _line);
}


void _glGetActiveAttribARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name, const char * _file, int _line) {
    glad_glGetActiveAttribARB(programObj, index, maxLength, length, size, type, name);
    gl_check_error(_file, _line);
}


GLint _glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB *name, const char * _file, int _line) {
    auto val = glad_glGetAttribLocationARB(programObj, name);
    gl_check_error(_file, _line);
    return val;
}


void _glDepthRangeArraydvNV(GLuint first, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glDepthRangeArraydvNV(first, count, v);
    gl_check_error(_file, _line);
}


void _glDepthRangeIndexeddNV(GLuint index, GLdouble n, GLdouble f, const char * _file, int _line) {
    glad_glDepthRangeIndexeddNV(index, n, f);
    gl_check_error(_file, _line);
}


void _glWindowPos2dARB(GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glWindowPos2dARB(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2dvARB(const GLdouble *v, const char * _file, int _line) {
    glad_glWindowPos2dvARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2fARB(GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glWindowPos2fARB(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2fvARB(const GLfloat *v, const char * _file, int _line) {
    glad_glWindowPos2fvARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2iARB(GLint x, GLint y, const char * _file, int _line) {
    glad_glWindowPos2iARB(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2ivARB(const GLint *v, const char * _file, int _line) {
    glad_glWindowPos2ivARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2sARB(GLshort x, GLshort y, const char * _file, int _line) {
    glad_glWindowPos2sARB(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2svARB(const GLshort *v, const char * _file, int _line) {
    glad_glWindowPos2svARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3dARB(GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glWindowPos3dARB(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3dvARB(const GLdouble *v, const char * _file, int _line) {
    glad_glWindowPos3dvARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3fARB(GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glWindowPos3fARB(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3fvARB(const GLfloat *v, const char * _file, int _line) {
    glad_glWindowPos3fvARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3iARB(GLint x, GLint y, GLint z, const char * _file, int _line) {
    glad_glWindowPos3iARB(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3ivARB(const GLint *v, const char * _file, int _line) {
    glad_glWindowPos3ivARB(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3sARB(GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glWindowPos3sARB(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3svARB(const GLshort *v, const char * _file, int _line) {
    glad_glWindowPos3svARB(v);
    gl_check_error(_file, _line);
}


void _glDrawBuffersATI(GLsizei n, const GLenum *bufs, const char * _file, int _line) {
    glad_glDrawBuffersATI(n, bufs);
    gl_check_error(_file, _line);
}


void _glElementPointerATI(GLenum type, const void *pointer, const char * _file, int _line) {
    glad_glElementPointerATI(type, pointer);
    gl_check_error(_file, _line);
}


void _glDrawElementArrayATI(GLenum mode, GLsizei count, const char * _file, int _line) {
    glad_glDrawElementArrayATI(mode, count);
    gl_check_error(_file, _line);
}


void _glDrawRangeElementArrayATI(GLenum mode, GLuint start, GLuint end, GLsizei count, const char * _file, int _line) {
    glad_glDrawRangeElementArrayATI(mode, start, end, count);
    gl_check_error(_file, _line);
}


void _glTexBumpParameterivATI(GLenum pname, const GLint *param, const char * _file, int _line) {
    glad_glTexBumpParameterivATI(pname, param);
    gl_check_error(_file, _line);
}


void _glTexBumpParameterfvATI(GLenum pname, const GLfloat *param, const char * _file, int _line) {
    glad_glTexBumpParameterfvATI(pname, param);
    gl_check_error(_file, _line);
}


void _glGetTexBumpParameterivATI(GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetTexBumpParameterivATI(pname, param);
    gl_check_error(_file, _line);
}


void _glGetTexBumpParameterfvATI(GLenum pname, GLfloat *param, const char * _file, int _line) {
    glad_glGetTexBumpParameterfvATI(pname, param);
    gl_check_error(_file, _line);
}


GLuint _glGenFragmentShadersATI(GLuint range, const char * _file, int _line) {
    auto val = glad_glGenFragmentShadersATI(range);
    gl_check_error(_file, _line);
    return val;
}


void _glBindFragmentShaderATI(GLuint id, const char * _file, int _line) {
    glad_glBindFragmentShaderATI(id);
    gl_check_error(_file, _line);
}


void _glDeleteFragmentShaderATI(GLuint id, const char * _file, int _line) {
    glad_glDeleteFragmentShaderATI(id);
    gl_check_error(_file, _line);
}


void _glBeginFragmentShaderATI(const char * _file, int _line) {
    glad_glBeginFragmentShaderATI();
    gl_check_error(_file, _line);
}


void _glEndFragmentShaderATI(const char * _file, int _line) {
    glad_glEndFragmentShaderATI();
    gl_check_error(_file, _line);
}


void _glPassTexCoordATI(GLuint dst, GLuint coord, GLenum swizzle, const char * _file, int _line) {
    glad_glPassTexCoordATI(dst, coord, swizzle);
    gl_check_error(_file, _line);
}


void _glSampleMapATI(GLuint dst, GLuint interp, GLenum swizzle, const char * _file, int _line) {
    glad_glSampleMapATI(dst, interp, swizzle);
    gl_check_error(_file, _line);
}


void _glColorFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, const char * _file, int _line) {
    glad_glColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod);
    gl_check_error(_file, _line);
}


void _glColorFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, const char * _file, int _line) {
    glad_glColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
    gl_check_error(_file, _line);
}


void _glColorFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod, const char * _file, int _line) {
    glad_glColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
    gl_check_error(_file, _line);
}


void _glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, const char * _file, int _line) {
    glad_glAlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod);
    gl_check_error(_file, _line);
}


void _glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, const char * _file, int _line) {
    glad_glAlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
    gl_check_error(_file, _line);
}


void _glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod, const char * _file, int _line) {
    glad_glAlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
    gl_check_error(_file, _line);
}


void _glSetFragmentShaderConstantATI(GLuint dst, const GLfloat *value, const char * _file, int _line) {
    glad_glSetFragmentShaderConstantATI(dst, value);
    gl_check_error(_file, _line);
}


void * _glMapObjectBufferATI(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glMapObjectBufferATI(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glUnmapObjectBufferATI(GLuint buffer, const char * _file, int _line) {
    glad_glUnmapObjectBufferATI(buffer);
    gl_check_error(_file, _line);
}


void _glPNTrianglesiATI(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPNTrianglesiATI(pname, param);
    gl_check_error(_file, _line);
}


void _glPNTrianglesfATI(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPNTrianglesfATI(pname, param);
    gl_check_error(_file, _line);
}


void _glStencilOpSeparateATI(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, const char * _file, int _line) {
    glad_glStencilOpSeparateATI(face, sfail, dpfail, dppass);
    gl_check_error(_file, _line);
}


void _glStencilFuncSeparateATI(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask, const char * _file, int _line) {
    glad_glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask);
    gl_check_error(_file, _line);
}


GLuint _glNewObjectBufferATI(GLsizei size, const void *pointer, GLenum usage, const char * _file, int _line) {
    auto val = glad_glNewObjectBufferATI(size, pointer, usage);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsObjectBufferATI(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glIsObjectBufferATI(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glUpdateObjectBufferATI(GLuint buffer, GLuint offset, GLsizei size, const void *pointer, GLenum preserve, const char * _file, int _line) {
    glad_glUpdateObjectBufferATI(buffer, offset, size, pointer, preserve);
    gl_check_error(_file, _line);
}


void _glGetObjectBufferfvATI(GLuint buffer, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetObjectBufferfvATI(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetObjectBufferivATI(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetObjectBufferivATI(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glFreeObjectBufferATI(GLuint buffer, const char * _file, int _line) {
    glad_glFreeObjectBufferATI(buffer);
    gl_check_error(_file, _line);
}


void _glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line) {
    glad_glArrayObjectATI(array, size, type, stride, buffer, offset);
    gl_check_error(_file, _line);
}


void _glGetArrayObjectfvATI(GLenum array, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetArrayObjectfvATI(array, pname, params);
    gl_check_error(_file, _line);
}


void _glGetArrayObjectivATI(GLenum array, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetArrayObjectivATI(array, pname, params);
    gl_check_error(_file, _line);
}


void _glVariantArrayObjectATI(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line) {
    glad_glVariantArrayObjectATI(id, type, stride, buffer, offset);
    gl_check_error(_file, _line);
}


void _glGetVariantArrayObjectfvATI(GLuint id, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVariantArrayObjectfvATI(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVariantArrayObjectivATI(GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVariantArrayObjectivATI(id, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexAttribArrayObjectATI(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line) {
    glad_glVertexAttribArrayObjectATI(index, size, type, normalized, stride, buffer, offset);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribArrayObjectfvATI(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVertexAttribArrayObjectfvATI(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribArrayObjectivATI(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribArrayObjectivATI(index, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexStream1sATI(GLenum stream, GLshort x, const char * _file, int _line) {
    glad_glVertexStream1sATI(stream, x);
    gl_check_error(_file, _line);
}


void _glVertexStream1svATI(GLenum stream, const GLshort *coords, const char * _file, int _line) {
    glad_glVertexStream1svATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream1iATI(GLenum stream, GLint x, const char * _file, int _line) {
    glad_glVertexStream1iATI(stream, x);
    gl_check_error(_file, _line);
}


void _glVertexStream1ivATI(GLenum stream, const GLint *coords, const char * _file, int _line) {
    glad_glVertexStream1ivATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream1fATI(GLenum stream, GLfloat x, const char * _file, int _line) {
    glad_glVertexStream1fATI(stream, x);
    gl_check_error(_file, _line);
}


void _glVertexStream1fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line) {
    glad_glVertexStream1fvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream1dATI(GLenum stream, GLdouble x, const char * _file, int _line) {
    glad_glVertexStream1dATI(stream, x);
    gl_check_error(_file, _line);
}


void _glVertexStream1dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line) {
    glad_glVertexStream1dvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream2sATI(GLenum stream, GLshort x, GLshort y, const char * _file, int _line) {
    glad_glVertexStream2sATI(stream, x, y);
    gl_check_error(_file, _line);
}


void _glVertexStream2svATI(GLenum stream, const GLshort *coords, const char * _file, int _line) {
    glad_glVertexStream2svATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream2iATI(GLenum stream, GLint x, GLint y, const char * _file, int _line) {
    glad_glVertexStream2iATI(stream, x, y);
    gl_check_error(_file, _line);
}


void _glVertexStream2ivATI(GLenum stream, const GLint *coords, const char * _file, int _line) {
    glad_glVertexStream2ivATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream2fATI(GLenum stream, GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glVertexStream2fATI(stream, x, y);
    gl_check_error(_file, _line);
}


void _glVertexStream2fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line) {
    glad_glVertexStream2fvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream2dATI(GLenum stream, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexStream2dATI(stream, x, y);
    gl_check_error(_file, _line);
}


void _glVertexStream2dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line) {
    glad_glVertexStream2dvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glVertexStream3sATI(stream, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexStream3svATI(GLenum stream, const GLshort *coords, const char * _file, int _line) {
    glad_glVertexStream3svATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream3iATI(GLenum stream, GLint x, GLint y, GLint z, const char * _file, int _line) {
    glad_glVertexStream3iATI(stream, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexStream3ivATI(GLenum stream, const GLint *coords, const char * _file, int _line) {
    glad_glVertexStream3ivATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glVertexStream3fATI(stream, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexStream3fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line) {
    glad_glVertexStream3fvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexStream3dATI(stream, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexStream3dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line) {
    glad_glVertexStream3dvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream4sATI(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line) {
    glad_glVertexStream4sATI(stream, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexStream4svATI(GLenum stream, const GLshort *coords, const char * _file, int _line) {
    glad_glVertexStream4svATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream4iATI(GLenum stream, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glVertexStream4iATI(stream, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexStream4ivATI(GLenum stream, const GLint *coords, const char * _file, int _line) {
    glad_glVertexStream4ivATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream4fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glVertexStream4fATI(stream, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexStream4fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line) {
    glad_glVertexStream4fvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glVertexStream4dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexStream4dATI(stream, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexStream4dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line) {
    glad_glVertexStream4dvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glNormalStream3bATI(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz, const char * _file, int _line) {
    glad_glNormalStream3bATI(stream, nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormalStream3bvATI(GLenum stream, const GLbyte *coords, const char * _file, int _line) {
    glad_glNormalStream3bvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glNormalStream3sATI(GLenum stream, GLshort nx, GLshort ny, GLshort nz, const char * _file, int _line) {
    glad_glNormalStream3sATI(stream, nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormalStream3svATI(GLenum stream, const GLshort *coords, const char * _file, int _line) {
    glad_glNormalStream3svATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glNormalStream3iATI(GLenum stream, GLint nx, GLint ny, GLint nz, const char * _file, int _line) {
    glad_glNormalStream3iATI(stream, nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormalStream3ivATI(GLenum stream, const GLint *coords, const char * _file, int _line) {
    glad_glNormalStream3ivATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glNormalStream3fATI(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz, const char * _file, int _line) {
    glad_glNormalStream3fATI(stream, nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormalStream3fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line) {
    glad_glNormalStream3fvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glNormalStream3dATI(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz, const char * _file, int _line) {
    glad_glNormalStream3dATI(stream, nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormalStream3dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line) {
    glad_glNormalStream3dvATI(stream, coords);
    gl_check_error(_file, _line);
}


void _glClientActiveVertexStreamATI(GLenum stream, const char * _file, int _line) {
    glad_glClientActiveVertexStreamATI(stream);
    gl_check_error(_file, _line);
}


void _glVertexBlendEnviATI(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glVertexBlendEnviATI(pname, param);
    gl_check_error(_file, _line);
}


void _glVertexBlendEnvfATI(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glVertexBlendEnvfATI(pname, param);
    gl_check_error(_file, _line);
}


void _glEGLImageTargetTexStorageEXT(GLenum target, GLeglImageOES image, const GLint* attrib_list, const char * _file, int _line) {
    glad_glEGLImageTargetTexStorageEXT(target, image, attrib_list);
    gl_check_error(_file, _line);
}


void _glEGLImageTargetTextureStorageEXT(GLuint texture, GLeglImageOES image, const GLint* attrib_list, const char * _file, int _line) {
    glad_glEGLImageTargetTextureStorageEXT(texture, image, attrib_list);
    gl_check_error(_file, _line);
}


void _glUniformBufferEXT(GLuint program, GLint location, GLuint buffer, const char * _file, int _line) {
    glad_glUniformBufferEXT(program, location, buffer);
    gl_check_error(_file, _line);
}


GLint _glGetUniformBufferSizeEXT(GLuint program, GLint location, const char * _file, int _line) {
    auto val = glad_glGetUniformBufferSizeEXT(program, location);
    gl_check_error(_file, _line);
    return val;
}


GLintptr _glGetUniformOffsetEXT(GLuint program, GLint location, const char * _file, int _line) {
    auto val = glad_glGetUniformOffsetEXT(program, location);
    gl_check_error(_file, _line);
    return val;
}


void _glBlendColorEXT(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line) {
    glad_glBlendColorEXT(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glBlendEquationSeparateEXT(GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line) {
    glad_glBlendEquationSeparateEXT(modeRGB, modeAlpha);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparateEXT(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    gl_check_error(_file, _line);
}


void _glBlendEquationEXT(GLenum mode, const char * _file, int _line) {
    glad_glBlendEquationEXT(mode);
    gl_check_error(_file, _line);
}


void _glColorSubTableEXT(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glColorSubTableEXT(target, start, count, format, type, data);
    gl_check_error(_file, _line);
}


void _glCopyColorSubTableEXT(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyColorSubTableEXT(target, start, x, y, width);
    gl_check_error(_file, _line);
}


void _glLockArraysEXT(GLint first, GLsizei count, const char * _file, int _line) {
    glad_glLockArraysEXT(first, count);
    gl_check_error(_file, _line);
}


void _glUnlockArraysEXT(const char * _file, int _line) {
    glad_glUnlockArraysEXT();
    gl_check_error(_file, _line);
}


void _glConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image, const char * _file, int _line) {
    glad_glConvolutionFilter1DEXT(target, internalformat, width, format, type, image);
    gl_check_error(_file, _line);
}


void _glConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image, const char * _file, int _line) {
    glad_glConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterfEXT(GLenum target, GLenum pname, GLfloat params, const char * _file, int _line) {
    glad_glConvolutionParameterfEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterfvEXT(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glConvolutionParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameteriEXT(GLenum target, GLenum pname, GLint params, const char * _file, int _line) {
    glad_glConvolutionParameteriEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glConvolutionParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glCopyConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyConvolutionFilter1DEXT(target, internalformat, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glGetConvolutionFilterEXT(GLenum target, GLenum format, GLenum type, void *image, const char * _file, int _line) {
    glad_glGetConvolutionFilterEXT(target, format, type, image);
    gl_check_error(_file, _line);
}


void _glGetConvolutionParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetConvolutionParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetConvolutionParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetConvolutionParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSeparableFilterEXT(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span, const char * _file, int _line) {
    glad_glGetSeparableFilterEXT(target, format, type, row, column, span);
    gl_check_error(_file, _line);
}


void _glSeparableFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column, const char * _file, int _line) {
    glad_glSeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column);
    gl_check_error(_file, _line);
}


void _glTangent3bEXT(GLbyte tx, GLbyte ty, GLbyte tz, const char * _file, int _line) {
    glad_glTangent3bEXT(tx, ty, tz);
    gl_check_error(_file, _line);
}


void _glTangent3bvEXT(const GLbyte *v, const char * _file, int _line) {
    glad_glTangent3bvEXT(v);
    gl_check_error(_file, _line);
}


void _glTangent3dEXT(GLdouble tx, GLdouble ty, GLdouble tz, const char * _file, int _line) {
    glad_glTangent3dEXT(tx, ty, tz);
    gl_check_error(_file, _line);
}


void _glTangent3dvEXT(const GLdouble *v, const char * _file, int _line) {
    glad_glTangent3dvEXT(v);
    gl_check_error(_file, _line);
}


void _glTangent3fEXT(GLfloat tx, GLfloat ty, GLfloat tz, const char * _file, int _line) {
    glad_glTangent3fEXT(tx, ty, tz);
    gl_check_error(_file, _line);
}


void _glTangent3fvEXT(const GLfloat *v, const char * _file, int _line) {
    glad_glTangent3fvEXT(v);
    gl_check_error(_file, _line);
}


void _glTangent3iEXT(GLint tx, GLint ty, GLint tz, const char * _file, int _line) {
    glad_glTangent3iEXT(tx, ty, tz);
    gl_check_error(_file, _line);
}


void _glTangent3ivEXT(const GLint *v, const char * _file, int _line) {
    glad_glTangent3ivEXT(v);
    gl_check_error(_file, _line);
}


void _glTangent3sEXT(GLshort tx, GLshort ty, GLshort tz, const char * _file, int _line) {
    glad_glTangent3sEXT(tx, ty, tz);
    gl_check_error(_file, _line);
}


void _glTangent3svEXT(const GLshort *v, const char * _file, int _line) {
    glad_glTangent3svEXT(v);
    gl_check_error(_file, _line);
}


void _glBinormal3bEXT(GLbyte bx, GLbyte by, GLbyte bz, const char * _file, int _line) {
    glad_glBinormal3bEXT(bx, by, bz);
    gl_check_error(_file, _line);
}


void _glBinormal3bvEXT(const GLbyte *v, const char * _file, int _line) {
    glad_glBinormal3bvEXT(v);
    gl_check_error(_file, _line);
}


void _glBinormal3dEXT(GLdouble bx, GLdouble by, GLdouble bz, const char * _file, int _line) {
    glad_glBinormal3dEXT(bx, by, bz);
    gl_check_error(_file, _line);
}


void _glBinormal3dvEXT(const GLdouble *v, const char * _file, int _line) {
    glad_glBinormal3dvEXT(v);
    gl_check_error(_file, _line);
}


void _glBinormal3fEXT(GLfloat bx, GLfloat by, GLfloat bz, const char * _file, int _line) {
    glad_glBinormal3fEXT(bx, by, bz);
    gl_check_error(_file, _line);
}


void _glBinormal3fvEXT(const GLfloat *v, const char * _file, int _line) {
    glad_glBinormal3fvEXT(v);
    gl_check_error(_file, _line);
}


void _glBinormal3iEXT(GLint bx, GLint by, GLint bz, const char * _file, int _line) {
    glad_glBinormal3iEXT(bx, by, bz);
    gl_check_error(_file, _line);
}


void _glBinormal3ivEXT(const GLint *v, const char * _file, int _line) {
    glad_glBinormal3ivEXT(v);
    gl_check_error(_file, _line);
}


void _glBinormal3sEXT(GLshort bx, GLshort by, GLshort bz, const char * _file, int _line) {
    glad_glBinormal3sEXT(bx, by, bz);
    gl_check_error(_file, _line);
}


void _glBinormal3svEXT(const GLshort *v, const char * _file, int _line) {
    glad_glBinormal3svEXT(v);
    gl_check_error(_file, _line);
}


void _glTangentPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glTangentPointerEXT(type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glBinormalPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glBinormalPointerEXT(type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glCopyTexImage1DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line) {
    glad_glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border);
    gl_check_error(_file, _line);
}


void _glCopyTexImage2DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line) {
    glad_glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glCopyTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glCullParameterdvEXT(GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glCullParameterdvEXT(pname, params);
    gl_check_error(_file, _line);
}


void _glCullParameterfvEXT(GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glCullParameterfvEXT(pname, params);
    gl_check_error(_file, _line);
}


void _glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label, const char * _file, int _line) {
    glad_glLabelObjectEXT(type, object, length, label);
    gl_check_error(_file, _line);
}


void _glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line) {
    glad_glGetObjectLabelEXT(type, object, bufSize, length, label);
    gl_check_error(_file, _line);
}


void _glInsertEventMarkerEXT(GLsizei length, const GLchar *marker, const char * _file, int _line) {
    glad_glInsertEventMarkerEXT(length, marker);
    gl_check_error(_file, _line);
}


void _glPushGroupMarkerEXT(GLsizei length, const GLchar *marker, const char * _file, int _line) {
    glad_glPushGroupMarkerEXT(length, marker);
    gl_check_error(_file, _line);
}


void _glPopGroupMarkerEXT(const char * _file, int _line) {
    glad_glPopGroupMarkerEXT();
    gl_check_error(_file, _line);
}


void _glDepthBoundsEXT(GLclampd zmin, GLclampd zmax, const char * _file, int _line) {
    glad_glDepthBoundsEXT(zmin, zmax);
    gl_check_error(_file, _line);
}


void _glMatrixLoadfEXT(GLenum mode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixLoadfEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixLoaddEXT(GLenum mode, const GLdouble *m, const char * _file, int _line) {
    glad_glMatrixLoaddEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMultfEXT(GLenum mode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixMultfEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMultdEXT(GLenum mode, const GLdouble *m, const char * _file, int _line) {
    glad_glMatrixMultdEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixLoadIdentityEXT(GLenum mode, const char * _file, int _line) {
    glad_glMatrixLoadIdentityEXT(mode);
    gl_check_error(_file, _line);
}


void _glMatrixRotatefEXT(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glMatrixRotatefEXT(mode, angle, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixRotatedEXT(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glMatrixRotatedEXT(mode, angle, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixScalefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glMatrixScalefEXT(mode, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixScaledEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glMatrixScaledEXT(mode, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixTranslatefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glMatrixTranslatefEXT(mode, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixTranslatedEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glMatrixTranslatedEXT(mode, x, y, z);
    gl_check_error(_file, _line);
}


void _glMatrixFrustumEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar, const char * _file, int _line) {
    glad_glMatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar);
    gl_check_error(_file, _line);
}


void _glMatrixOrthoEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar, const char * _file, int _line) {
    glad_glMatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar);
    gl_check_error(_file, _line);
}


void _glMatrixPopEXT(GLenum mode, const char * _file, int _line) {
    glad_glMatrixPopEXT(mode);
    gl_check_error(_file, _line);
}


void _glMatrixPushEXT(GLenum mode, const char * _file, int _line) {
    glad_glMatrixPushEXT(mode);
    gl_check_error(_file, _line);
}


void _glClientAttribDefaultEXT(GLbitfield mask, const char * _file, int _line) {
    glad_glClientAttribDefaultEXT(mask);
    gl_check_error(_file, _line);
}


void _glPushClientAttribDefaultEXT(GLbitfield mask, const char * _file, int _line) {
    glad_glPushClientAttribDefaultEXT(mask);
    gl_check_error(_file, _line);
}


void _glTextureParameterfEXT(GLuint texture, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glTextureParameterfEXT(texture, target, pname, param);
    gl_check_error(_file, _line);
}


void _glTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glTextureParameterfvEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureParameteriEXT(GLuint texture, GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glTextureParameteriEXT(texture, target, pname, param);
    gl_check_error(_file, _line);
}


void _glTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTextureParameterivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCopyTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line) {
    glad_glCopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border);
    gl_check_error(_file, _line);
}


void _glCopyTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line) {
    glad_glCopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line) {
    glad_glGetTextureImageEXT(texture, target, level, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTextureParameterfvEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureParameterivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureLevelParameterfvEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetTextureLevelParameterfvEXT(texture, target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureLevelParameterivEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureLevelParameterivEXT(texture, target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCopyTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture, const char * _file, int _line) {
    glad_glBindMultiTextureEXT(texunit, target, texture);
    gl_check_error(_file, _line);
}


void _glMultiTexCoordPointerEXT(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glMultiTexCoordPointerEXT(texunit, size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glMultiTexEnvfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glMultiTexEnvfEXT(texunit, target, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glMultiTexEnvfvEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexEnviEXT(GLenum texunit, GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glMultiTexEnviEXT(texunit, target, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMultiTexEnvivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexGendEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble param, const char * _file, int _line) {
    glad_glMultiTexGendEXT(texunit, coord, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLdouble *params, const char * _file, int _line) {
    glad_glMultiTexGendvEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexGenfEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glMultiTexGenfEXT(texunit, coord, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glMultiTexGenfvEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexGeniEXT(GLenum texunit, GLenum coord, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glMultiTexGeniEXT(texunit, coord, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMultiTexGenivEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMultiTexEnvfvEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMultiTexEnvivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetMultiTexGendvEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMultiTexGenfvEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMultiTexGenivEXT(texunit, coord, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexParameteriEXT(GLenum texunit, GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glMultiTexParameteriEXT(texunit, target, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMultiTexParameterivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexParameterfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glMultiTexParameterfEXT(texunit, target, pname, param);
    gl_check_error(_file, _line);
}


void _glMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glMultiTexParameterfvEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCopyMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line) {
    glad_glCopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border);
    gl_check_error(_file, _line);
}


void _glCopyMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line) {
    glad_glCopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border);
    gl_check_error(_file, _line);
}


void _glCopyMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width);
    gl_check_error(_file, _line);
}


void _glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glGetMultiTexImageEXT(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line) {
    glad_glGetMultiTexImageEXT(texunit, target, level, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glGetMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMultiTexParameterfvEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMultiTexParameterivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexLevelParameterfvEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexLevelParameterivEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMultiTexLevelParameterivEXT(texunit, target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glCopyMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glCopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height);
    gl_check_error(_file, _line);
}


void _glEnableClientStateIndexedEXT(GLenum array, GLuint index, const char * _file, int _line) {
    glad_glEnableClientStateIndexedEXT(array, index);
    gl_check_error(_file, _line);
}


void _glDisableClientStateIndexedEXT(GLenum array, GLuint index, const char * _file, int _line) {
    glad_glDisableClientStateIndexedEXT(array, index);
    gl_check_error(_file, _line);
}


void _glGetFloatIndexedvEXT(GLenum target, GLuint index, GLfloat *data, const char * _file, int _line) {
    glad_glGetFloatIndexedvEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetDoubleIndexedvEXT(GLenum target, GLuint index, GLdouble *data, const char * _file, int _line) {
    glad_glGetDoubleIndexedvEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetPointerIndexedvEXT(GLenum target, GLuint index, void **data, const char * _file, int _line) {
    glad_glGetPointerIndexedvEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glEnableIndexedEXT(GLenum target, GLuint index, const char * _file, int _line) {
    glad_glEnableIndexedEXT(target, index);
    gl_check_error(_file, _line);
}


void _glDisableIndexedEXT(GLenum target, GLuint index, const char * _file, int _line) {
    glad_glDisableIndexedEXT(target, index);
    gl_check_error(_file, _line);
}


GLboolean _glIsEnabledIndexedEXT(GLenum target, GLuint index, const char * _file, int _line) {
    auto val = glad_glIsEnabledIndexedEXT(target, index);
    gl_check_error(_file, _line);
    return val;
}


void _glGetIntegerIndexedvEXT(GLenum target, GLuint index, GLint *data, const char * _file, int _line) {
    glad_glGetIntegerIndexedvEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glGetBooleanIndexedvEXT(GLenum target, GLuint index, GLboolean *data, const char * _file, int _line) {
    glad_glGetBooleanIndexedvEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glCompressedTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glGetCompressedTextureImageEXT(GLuint texture, GLenum target, GLint lod, void *img, const char * _file, int _line) {
    glad_glGetCompressedTextureImageEXT(texture, target, lod, img);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glCompressedMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line) {
    glad_glCompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits);
    gl_check_error(_file, _line);
}


void _glGetCompressedMultiTexImageEXT(GLenum texunit, GLenum target, GLint lod, void *img, const char * _file, int _line) {
    glad_glGetCompressedMultiTexImageEXT(texunit, target, lod, img);
    gl_check_error(_file, _line);
}


void _glMatrixLoadTransposefEXT(GLenum mode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixLoadTransposefEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixLoadTransposedEXT(GLenum mode, const GLdouble *m, const char * _file, int _line) {
    glad_glMatrixLoadTransposedEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMultTransposefEXT(GLenum mode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixMultTransposefEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMultTransposedEXT(GLenum mode, const GLdouble *m, const char * _file, int _line) {
    glad_glMatrixMultTransposedEXT(mode, m);
    gl_check_error(_file, _line);
}


void _glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line) {
    glad_glNamedBufferDataEXT(buffer, size, data, usage);
    gl_check_error(_file, _line);
}


void _glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line) {
    glad_glNamedBufferSubDataEXT(buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void * _glMapNamedBufferEXT(GLuint buffer, GLenum access, const char * _file, int _line) {
    auto val = glad_glMapNamedBufferEXT(buffer, access);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glUnmapNamedBufferEXT(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glUnmapNamedBufferEXT(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glGetNamedBufferParameterivEXT(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedBufferParameterivEXT(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferPointervEXT(GLuint buffer, GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetNamedBufferPointervEXT(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line) {
    glad_glGetNamedBufferSubDataEXT(buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void _glProgramUniform1fEXT(GLuint program, GLint location, GLfloat v0, const char * _file, int _line) {
    glad_glProgramUniform1fEXT(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform2fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line) {
    glad_glProgramUniform2fEXT(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform3fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line) {
    glad_glProgramUniform3fEXT(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform4fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line) {
    glad_glProgramUniform4fEXT(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform1iEXT(GLuint program, GLint location, GLint v0, const char * _file, int _line) {
    glad_glProgramUniform1iEXT(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform2iEXT(GLuint program, GLint location, GLint v0, GLint v1, const char * _file, int _line) {
    glad_glProgramUniform2iEXT(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform3iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line) {
    glad_glProgramUniform3iEXT(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform4iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line) {
    glad_glProgramUniform4iEXT(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform1fvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform2fvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform3fvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniform4fvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform1ivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform2ivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform3ivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line) {
    glad_glProgramUniform4ivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glTextureBufferEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glTextureBufferEXT(texture, target, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glMultiTexBufferEXT(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glMultiTexBufferEXT(texunit, target, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTextureParameterIivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line) {
    glad_glTextureParameterIuivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTextureParameterIivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetTextureParameterIuivEXT(texture, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMultiTexParameterIivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line) {
    glad_glMultiTexParameterIuivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMultiTexParameterIivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetMultiTexParameterIuivEXT(texunit, target, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramUniform1uiEXT(GLuint program, GLint location, GLuint v0, const char * _file, int _line) {
    glad_glProgramUniform1uiEXT(program, location, v0);
    gl_check_error(_file, _line);
}


void _glProgramUniform2uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, const char * _file, int _line) {
    glad_glProgramUniform2uiEXT(program, location, v0, v1);
    gl_check_error(_file, _line);
}


void _glProgramUniform3uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line) {
    glad_glProgramUniform3uiEXT(program, location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glProgramUniform4uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line) {
    glad_glProgramUniform4uiEXT(program, location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform1uivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform2uivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform3uivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glProgramUniform4uivEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameters4fvEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParameters4fvEXT(program, target, index, count, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameterI4iEXT(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glNamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameterI4ivEXT(GLuint program, GLenum target, GLuint index, const GLint *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParameterI4ivEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParametersI4ivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParametersI4ivEXT(program, target, index, count, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameterI4uiEXT(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line) {
    glad_glNamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameterI4uivEXT(GLuint program, GLenum target, GLuint index, const GLuint *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParameterI4uivEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParametersI4uivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParametersI4uivEXT(program, target, index, count, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramLocalParameterIivEXT(GLuint program, GLenum target, GLuint index, GLint *params, const char * _file, int _line) {
    glad_glGetNamedProgramLocalParameterIivEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramLocalParameterIuivEXT(GLuint program, GLenum target, GLuint index, GLuint *params, const char * _file, int _line) {
    glad_glGetNamedProgramLocalParameterIuivEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glEnableClientStateiEXT(GLenum array, GLuint index, const char * _file, int _line) {
    glad_glEnableClientStateiEXT(array, index);
    gl_check_error(_file, _line);
}


void _glDisableClientStateiEXT(GLenum array, GLuint index, const char * _file, int _line) {
    glad_glDisableClientStateiEXT(array, index);
    gl_check_error(_file, _line);
}


void _glGetFloati_vEXT(GLenum pname, GLuint index, GLfloat *params, const char * _file, int _line) {
    glad_glGetFloati_vEXT(pname, index, params);
    gl_check_error(_file, _line);
}


void _glGetDoublei_vEXT(GLenum pname, GLuint index, GLdouble *params, const char * _file, int _line) {
    glad_glGetDoublei_vEXT(pname, index, params);
    gl_check_error(_file, _line);
}


void _glGetPointeri_vEXT(GLenum pname, GLuint index, void **params, const char * _file, int _line) {
    glad_glGetPointeri_vEXT(pname, index, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramStringEXT(GLuint program, GLenum target, GLenum format, GLsizei len, const void *string, const char * _file, int _line) {
    glad_glNamedProgramStringEXT(program, target, format, len, string);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameter4dEXT(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glNamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameter4dvEXT(GLuint program, GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParameter4dvEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameter4fEXT(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glNamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glNamedProgramLocalParameter4fvEXT(GLuint program, GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line) {
    glad_glNamedProgramLocalParameter4fvEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramLocalParameterdvEXT(GLuint program, GLenum target, GLuint index, GLdouble *params, const char * _file, int _line) {
    glad_glGetNamedProgramLocalParameterdvEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramLocalParameterfvEXT(GLuint program, GLenum target, GLuint index, GLfloat *params, const char * _file, int _line) {
    glad_glGetNamedProgramLocalParameterfvEXT(program, target, index, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramivEXT(GLuint program, GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedProgramivEXT(program, target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedProgramStringEXT(GLuint program, GLenum target, GLenum pname, void *string, const char * _file, int _line) {
    glad_glGetNamedProgramStringEXT(program, target, pname, string);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height);
    gl_check_error(_file, _line);
}


GLenum _glCheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target, const char * _file, int _line) {
    auto val = glad_glCheckNamedFramebufferStatusEXT(framebuffer, target);
    gl_check_error(_file, _line);
    return val;
}


void _glNamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line) {
    glad_glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line) {
    glad_glNamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer);
    gl_check_error(_file, _line);
}


void _glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params);
    gl_check_error(_file, _line);
}


void _glGenerateTextureMipmapEXT(GLuint texture, GLenum target, const char * _file, int _line) {
    glad_glGenerateTextureMipmapEXT(texture, target);
    gl_check_error(_file, _line);
}


void _glGenerateMultiTexMipmapEXT(GLenum texunit, GLenum target, const char * _file, int _line) {
    glad_glGenerateMultiTexMipmapEXT(texunit, target);
    gl_check_error(_file, _line);
}


void _glFramebufferDrawBufferEXT(GLuint framebuffer, GLenum mode, const char * _file, int _line) {
    glad_glFramebufferDrawBufferEXT(framebuffer, mode);
    gl_check_error(_file, _line);
}


void _glFramebufferDrawBuffersEXT(GLuint framebuffer, GLsizei n, const GLenum *bufs, const char * _file, int _line) {
    glad_glFramebufferDrawBuffersEXT(framebuffer, n, bufs);
    gl_check_error(_file, _line);
}


void _glFramebufferReadBufferEXT(GLuint framebuffer, GLenum mode, const char * _file, int _line) {
    glad_glFramebufferReadBufferEXT(framebuffer, mode);
    gl_check_error(_file, _line);
}


void _glGetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFramebufferParameterivEXT(framebuffer, pname, params);
    gl_check_error(_file, _line);
}


void _glNamedCopyBufferSubDataEXT(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line) {
    glad_glNamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTextureEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTextureLayerEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line) {
    glad_glNamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferTextureFaceEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line) {
    glad_glNamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face);
    gl_check_error(_file, _line);
}


void _glTextureRenderbufferEXT(GLuint texture, GLenum target, GLuint renderbuffer, const char * _file, int _line) {
    glad_glTextureRenderbufferEXT(texture, target, renderbuffer);
    gl_check_error(_file, _line);
}


void _glMultiTexRenderbufferEXT(GLenum texunit, GLenum target, GLuint renderbuffer, const char * _file, int _line) {
    glad_glMultiTexRenderbufferEXT(texunit, target, renderbuffer);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayIndexOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayNormalOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayFogCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArraySecondaryColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glEnableVertexArrayEXT(GLuint vaobj, GLenum array, const char * _file, int _line) {
    glad_glEnableVertexArrayEXT(vaobj, array);
    gl_check_error(_file, _line);
}


void _glDisableVertexArrayEXT(GLuint vaobj, GLenum array, const char * _file, int _line) {
    glad_glDisableVertexArrayEXT(vaobj, array);
    gl_check_error(_file, _line);
}


void _glEnableVertexArrayAttribEXT(GLuint vaobj, GLuint index, const char * _file, int _line) {
    glad_glEnableVertexArrayAttribEXT(vaobj, index);
    gl_check_error(_file, _line);
}


void _glDisableVertexArrayAttribEXT(GLuint vaobj, GLuint index, const char * _file, int _line) {
    glad_glDisableVertexArrayAttribEXT(vaobj, index);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayIntegervEXT(GLuint vaobj, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetVertexArrayIntegervEXT(vaobj, pname, param);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayPointervEXT(GLuint vaobj, GLenum pname, void **param, const char * _file, int _line) {
    glad_glGetVertexArrayPointervEXT(vaobj, pname, param);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayIntegeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, GLint *param, const char * _file, int _line) {
    glad_glGetVertexArrayIntegeri_vEXT(vaobj, index, pname, param);
    gl_check_error(_file, _line);
}


void _glGetVertexArrayPointeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, void **param, const char * _file, int _line) {
    glad_glGetVertexArrayPointeri_vEXT(vaobj, index, pname, param);
    gl_check_error(_file, _line);
}


void * _glMapNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line) {
    auto val = glad_glMapNamedBufferRangeEXT(buffer, offset, length, access);
    gl_check_error(_file, _line);
    return val;
}


void _glFlushMappedNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line) {
    glad_glFlushMappedNamedBufferRangeEXT(buffer, offset, length);
    gl_check_error(_file, _line);
}


void _glNamedBufferStorageEXT(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line) {
    glad_glNamedBufferStorageEXT(buffer, size, data, flags);
    gl_check_error(_file, _line);
}


void _glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearNamedBufferDataEXT(buffer, internalformat, format, type, data);
    gl_check_error(_file, _line);
}


void _glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line) {
    glad_glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glNamedFramebufferParameteriEXT(framebuffer, pname, param);
    gl_check_error(_file, _line);
}


void _glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetNamedFramebufferParameterivEXT(framebuffer, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramUniform1dEXT(GLuint program, GLint location, GLdouble x, const char * _file, int _line) {
    glad_glProgramUniform1dEXT(program, location, x);
    gl_check_error(_file, _line);
}


void _glProgramUniform2dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glProgramUniform2dEXT(program, location, x, y);
    gl_check_error(_file, _line);
}


void _glProgramUniform3dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glProgramUniform3dEXT(program, location, x, y, z);
    gl_check_error(_file, _line);
}


void _glProgramUniform4dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glProgramUniform4dEXT(program, location, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramUniform1dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform1dvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform2dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform2dvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform3dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform3dvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniform4dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniform4dvEXT(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix2x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix3x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformMatrix4x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line) {
    glad_glProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value);
    gl_check_error(_file, _line);
}


void _glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glTextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line) {
    glad_glTextureStorage1DEXT(texture, target, levels, internalformat, width);
    gl_check_error(_file, _line);
}


void _glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glTextureStorage2DEXT(texture, target, levels, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
    gl_check_error(_file, _line);
}


void _glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glTextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glVertexArrayBindVertexBufferEXT(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line) {
    glad_glVertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribIFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribLFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribBindingEXT(GLuint vaobj, GLuint attribindex, GLuint bindingindex, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexBindingDivisorEXT(GLuint vaobj, GLuint bindingindex, GLuint divisor, const char * _file, int _line) {
    glad_glVertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
    gl_check_error(_file, _line);
}


void _glTexturePageCommitmentEXT(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit, const char * _file, int _line) {
    glad_glTexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, commit);
    gl_check_error(_file, _line);
}


void _glVertexArrayVertexAttribDivisorEXT(GLuint vaobj, GLuint index, GLuint divisor, const char * _file, int _line) {
    glad_glVertexArrayVertexAttribDivisorEXT(vaobj, index, divisor);
    gl_check_error(_file, _line);
}


void _glColorMaskIndexedEXT(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, const char * _file, int _line) {
    glad_glColorMaskIndexedEXT(index, r, g, b, a);
    gl_check_error(_file, _line);
}


void _glDrawArraysInstancedEXT(GLenum mode, GLint start, GLsizei count, GLsizei primcount, const char * _file, int _line) {
    glad_glDrawArraysInstancedEXT(mode, start, count, primcount);
    gl_check_error(_file, _line);
}


void _glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, const char * _file, int _line) {
    glad_glDrawElementsInstancedEXT(mode, count, type, indices, primcount);
    gl_check_error(_file, _line);
}


void _glDrawRangeElementsEXT(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, const char * _file, int _line) {
    glad_glDrawRangeElementsEXT(mode, start, end, count, type, indices);
    gl_check_error(_file, _line);
}


void _glBufferStorageExternalEXT(GLenum target, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags, const char * _file, int _line) {
    glad_glBufferStorageExternalEXT(target, offset, size, clientBuffer, flags);
    gl_check_error(_file, _line);
}


void _glNamedBufferStorageExternalEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags, const char * _file, int _line) {
    glad_glNamedBufferStorageExternalEXT(buffer, offset, size, clientBuffer, flags);
    gl_check_error(_file, _line);
}


void _glFogCoordfEXT(GLfloat coord, const char * _file, int _line) {
    glad_glFogCoordfEXT(coord);
    gl_check_error(_file, _line);
}


void _glFogCoordfvEXT(const GLfloat *coord, const char * _file, int _line) {
    glad_glFogCoordfvEXT(coord);
    gl_check_error(_file, _line);
}


void _glFogCoorddEXT(GLdouble coord, const char * _file, int _line) {
    glad_glFogCoorddEXT(coord);
    gl_check_error(_file, _line);
}


void _glFogCoorddvEXT(const GLdouble *coord, const char * _file, int _line) {
    glad_glFogCoorddvEXT(coord);
    gl_check_error(_file, _line);
}


void _glFogCoordPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glFogCoordPointerEXT(type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line) {
    glad_glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
    gl_check_error(_file, _line);
}


GLboolean _glIsRenderbufferEXT(GLuint renderbuffer, const char * _file, int _line) {
    auto val = glad_glIsRenderbufferEXT(renderbuffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBindRenderbufferEXT(GLenum target, GLuint renderbuffer, const char * _file, int _line) {
    glad_glBindRenderbufferEXT(target, renderbuffer);
    gl_check_error(_file, _line);
}


void _glDeleteRenderbuffersEXT(GLsizei n, const GLuint *renderbuffers, const char * _file, int _line) {
    glad_glDeleteRenderbuffersEXT(n, renderbuffers);
    gl_check_error(_file, _line);
}


void _glGenRenderbuffersEXT(GLsizei n, GLuint *renderbuffers, const char * _file, int _line) {
    glad_glGenRenderbuffersEXT(n, renderbuffers);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorageEXT(target, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetRenderbufferParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


GLboolean _glIsFramebufferEXT(GLuint framebuffer, const char * _file, int _line) {
    auto val = glad_glIsFramebufferEXT(framebuffer);
    gl_check_error(_file, _line);
    return val;
}


void _glBindFramebufferEXT(GLenum target, GLuint framebuffer, const char * _file, int _line) {
    glad_glBindFramebufferEXT(target, framebuffer);
    gl_check_error(_file, _line);
}


void _glDeleteFramebuffersEXT(GLsizei n, const GLuint *framebuffers, const char * _file, int _line) {
    glad_glDeleteFramebuffersEXT(n, framebuffers);
    gl_check_error(_file, _line);
}


void _glGenFramebuffersEXT(GLsizei n, GLuint *framebuffers, const char * _file, int _line) {
    glad_glGenFramebuffersEXT(n, framebuffers);
    gl_check_error(_file, _line);
}


GLenum _glCheckFramebufferStatusEXT(GLenum target, const char * _file, int _line) {
    auto val = glad_glCheckFramebufferStatusEXT(target);
    gl_check_error(_file, _line);
    return val;
}


void _glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTexture1DEXT(target, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTexture2DEXT(target, attachment, textarget, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line) {
    glad_glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset);
    gl_check_error(_file, _line);
}


void _glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line) {
    glad_glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
    gl_check_error(_file, _line);
}


void _glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
    gl_check_error(_file, _line);
}


void _glGenerateMipmapEXT(GLenum target, const char * _file, int _line) {
    glad_glGenerateMipmapEXT(target);
    gl_check_error(_file, _line);
}


void _glProgramParameteriEXT(GLuint program, GLenum pname, GLint value, const char * _file, int _line) {
    glad_glProgramParameteriEXT(program, pname, value);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line) {
    glad_glProgramEnvParameters4fvEXT(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line) {
    glad_glProgramLocalParameters4fvEXT(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glGetUniformuivEXT(GLuint program, GLint location, GLuint *params, const char * _file, int _line) {
    glad_glGetUniformuivEXT(program, location, params);
    gl_check_error(_file, _line);
}


void _glBindFragDataLocationEXT(GLuint program, GLuint color, const GLchar *name, const char * _file, int _line) {
    glad_glBindFragDataLocationEXT(program, color, name);
    gl_check_error(_file, _line);
}


GLint _glGetFragDataLocationEXT(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetFragDataLocationEXT(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glUniform1uiEXT(GLint location, GLuint v0, const char * _file, int _line) {
    glad_glUniform1uiEXT(location, v0);
    gl_check_error(_file, _line);
}


void _glUniform2uiEXT(GLint location, GLuint v0, GLuint v1, const char * _file, int _line) {
    glad_glUniform2uiEXT(location, v0, v1);
    gl_check_error(_file, _line);
}


void _glUniform3uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line) {
    glad_glUniform3uiEXT(location, v0, v1, v2);
    gl_check_error(_file, _line);
}


void _glUniform4uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line) {
    glad_glUniform4uiEXT(location, v0, v1, v2, v3);
    gl_check_error(_file, _line);
}


void _glUniform1uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform1uivEXT(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform2uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform2uivEXT(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform3uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform3uivEXT(location, count, value);
    gl_check_error(_file, _line);
}


void _glUniform4uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line) {
    glad_glUniform4uivEXT(location, count, value);
    gl_check_error(_file, _line);
}


void _glGetHistogramEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line) {
    glad_glGetHistogramEXT(target, reset, format, type, values);
    gl_check_error(_file, _line);
}


void _glGetHistogramParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetHistogramParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetHistogramParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetHistogramParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMinmaxEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line) {
    glad_glGetMinmaxEXT(target, reset, format, type, values);
    gl_check_error(_file, _line);
}


void _glGetMinmaxParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMinmaxParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMinmaxParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMinmaxParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glHistogramEXT(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, const char * _file, int _line) {
    glad_glHistogramEXT(target, width, internalformat, sink);
    gl_check_error(_file, _line);
}


void _glMinmaxEXT(GLenum target, GLenum internalformat, GLboolean sink, const char * _file, int _line) {
    glad_glMinmaxEXT(target, internalformat, sink);
    gl_check_error(_file, _line);
}


void _glResetHistogramEXT(GLenum target, const char * _file, int _line) {
    glad_glResetHistogramEXT(target);
    gl_check_error(_file, _line);
}


void _glResetMinmaxEXT(GLenum target, const char * _file, int _line) {
    glad_glResetMinmaxEXT(target);
    gl_check_error(_file, _line);
}


void _glIndexFuncEXT(GLenum func, GLclampf ref, const char * _file, int _line) {
    glad_glIndexFuncEXT(func, ref);
    gl_check_error(_file, _line);
}


void _glIndexMaterialEXT(GLenum face, GLenum mode, const char * _file, int _line) {
    glad_glIndexMaterialEXT(face, mode);
    gl_check_error(_file, _line);
}


void _glApplyTextureEXT(GLenum mode, const char * _file, int _line) {
    glad_glApplyTextureEXT(mode);
    gl_check_error(_file, _line);
}


void _glTextureLightEXT(GLenum pname, const char * _file, int _line) {
    glad_glTextureLightEXT(pname);
    gl_check_error(_file, _line);
}


void _glTextureMaterialEXT(GLenum face, GLenum mode, const char * _file, int _line) {
    glad_glTextureMaterialEXT(face, mode);
    gl_check_error(_file, _line);
}


void _glGetUnsignedBytevEXT(GLenum pname, GLubyte *data, const char * _file, int _line) {
    glad_glGetUnsignedBytevEXT(pname, data);
    gl_check_error(_file, _line);
}


void _glGetUnsignedBytei_vEXT(GLenum target, GLuint index, GLubyte *data, const char * _file, int _line) {
    glad_glGetUnsignedBytei_vEXT(target, index, data);
    gl_check_error(_file, _line);
}


void _glDeleteMemoryObjectsEXT(GLsizei n, const GLuint *memoryObjects, const char * _file, int _line) {
    glad_glDeleteMemoryObjectsEXT(n, memoryObjects);
    gl_check_error(_file, _line);
}


GLboolean _glIsMemoryObjectEXT(GLuint memoryObject, const char * _file, int _line) {
    auto val = glad_glIsMemoryObjectEXT(memoryObject);
    gl_check_error(_file, _line);
    return val;
}


void _glCreateMemoryObjectsEXT(GLsizei n, GLuint *memoryObjects, const char * _file, int _line) {
    glad_glCreateMemoryObjectsEXT(n, memoryObjects);
    gl_check_error(_file, _line);
}


void _glMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMemoryObjectParameterivEXT(memoryObject, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMemoryObjectParameterivEXT(memoryObject, pname, params);
    gl_check_error(_file, _line);
}


void _glTexStorageMem2DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexStorageMem2DEXT(target, levels, internalFormat, width, height, memory, offset);
    gl_check_error(_file, _line);
}


void _glTexStorageMem2DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexStorageMem2DMultisampleEXT(target, samples, internalFormat, width, height, fixedSampleLocations, memory, offset);
    gl_check_error(_file, _line);
}


void _glTexStorageMem3DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexStorageMem3DEXT(target, levels, internalFormat, width, height, depth, memory, offset);
    gl_check_error(_file, _line);
}


void _glTexStorageMem3DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexStorageMem3DMultisampleEXT(target, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset);
    gl_check_error(_file, _line);
}


void _glBufferStorageMemEXT(GLenum target, GLsizeiptr size, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glBufferStorageMemEXT(target, size, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureStorageMem2DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureStorageMem2DEXT(texture, levels, internalFormat, width, height, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureStorageMem2DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureStorageMem2DMultisampleEXT(texture, samples, internalFormat, width, height, fixedSampleLocations, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureStorageMem3DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureStorageMem3DEXT(texture, levels, internalFormat, width, height, depth, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureStorageMem3DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureStorageMem3DMultisampleEXT(texture, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset);
    gl_check_error(_file, _line);
}


void _glNamedBufferStorageMemEXT(GLuint buffer, GLsizeiptr size, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glNamedBufferStorageMemEXT(buffer, size, memory, offset);
    gl_check_error(_file, _line);
}


void _glTexStorageMem1DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexStorageMem1DEXT(target, levels, internalFormat, width, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureStorageMem1DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureStorageMem1DEXT(texture, levels, internalFormat, width, memory, offset);
    gl_check_error(_file, _line);
}


void _glImportMemoryFdEXT(GLuint memory, GLuint64 size, GLenum handleType, GLint fd, const char * _file, int _line) {
    glad_glImportMemoryFdEXT(memory, size, handleType, fd);
    gl_check_error(_file, _line);
}


void _glImportMemoryWin32HandleEXT(GLuint memory, GLuint64 size, GLenum handleType, void *handle, const char * _file, int _line) {
    glad_glImportMemoryWin32HandleEXT(memory, size, handleType, handle);
    gl_check_error(_file, _line);
}


void _glImportMemoryWin32NameEXT(GLuint memory, GLuint64 size, GLenum handleType, const void *name, const char * _file, int _line) {
    glad_glImportMemoryWin32NameEXT(memory, size, handleType, name);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysEXT(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line) {
    glad_glMultiDrawArraysEXT(mode, first, count, primcount);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsEXT(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount, const char * _file, int _line) {
    glad_glMultiDrawElementsEXT(mode, count, type, indices, primcount);
    gl_check_error(_file, _line);
}


void _glSampleMaskEXT(GLclampf value, GLboolean invert, const char * _file, int _line) {
    glad_glSampleMaskEXT(value, invert);
    gl_check_error(_file, _line);
}


void _glSamplePatternEXT(GLenum pattern, const char * _file, int _line) {
    glad_glSamplePatternEXT(pattern);
    gl_check_error(_file, _line);
}


void _glColorTableEXT(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line) {
    glad_glColorTableEXT(target, internalFormat, width, format, type, table);
    gl_check_error(_file, _line);
}


void _glGetColorTableEXT(GLenum target, GLenum format, GLenum type, void *data, const char * _file, int _line) {
    glad_glGetColorTableEXT(target, format, type, data);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetColorTableParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetColorTableParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glPixelTransformParameteriEXT(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPixelTransformParameteriEXT(target, pname, param);
    gl_check_error(_file, _line);
}


void _glPixelTransformParameterfEXT(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPixelTransformParameterfEXT(target, pname, param);
    gl_check_error(_file, _line);
}


void _glPixelTransformParameterivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glPixelTransformParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glPixelTransformParameterfvEXT(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPixelTransformParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetPixelTransformParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetPixelTransformParameterivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetPixelTransformParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetPixelTransformParameterfvEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glPointParameterfEXT(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPointParameterfEXT(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameterfvEXT(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPointParameterfvEXT(pname, params);
    gl_check_error(_file, _line);
}


void _glPolygonOffsetEXT(GLfloat factor, GLfloat bias, const char * _file, int _line) {
    glad_glPolygonOffsetEXT(factor, bias);
    gl_check_error(_file, _line);
}


void _glPolygonOffsetClampEXT(GLfloat factor, GLfloat units, GLfloat clamp, const char * _file, int _line) {
    glad_glPolygonOffsetClampEXT(factor, units, clamp);
    gl_check_error(_file, _line);
}


void _glProvokingVertexEXT(GLenum mode, const char * _file, int _line) {
    glad_glProvokingVertexEXT(mode);
    gl_check_error(_file, _line);
}


void _glRasterSamplesEXT(GLuint samples, GLboolean fixedsamplelocations, const char * _file, int _line) {
    glad_glRasterSamplesEXT(samples, fixedsamplelocations);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3bEXT(GLbyte red, GLbyte green, GLbyte blue, const char * _file, int _line) {
    glad_glSecondaryColor3bEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3bvEXT(const GLbyte *v, const char * _file, int _line) {
    glad_glSecondaryColor3bvEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3dEXT(GLdouble red, GLdouble green, GLdouble blue, const char * _file, int _line) {
    glad_glSecondaryColor3dEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3dvEXT(const GLdouble *v, const char * _file, int _line) {
    glad_glSecondaryColor3dvEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3fEXT(GLfloat red, GLfloat green, GLfloat blue, const char * _file, int _line) {
    glad_glSecondaryColor3fEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3fvEXT(const GLfloat *v, const char * _file, int _line) {
    glad_glSecondaryColor3fvEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3iEXT(GLint red, GLint green, GLint blue, const char * _file, int _line) {
    glad_glSecondaryColor3iEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3ivEXT(const GLint *v, const char * _file, int _line) {
    glad_glSecondaryColor3ivEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3sEXT(GLshort red, GLshort green, GLshort blue, const char * _file, int _line) {
    glad_glSecondaryColor3sEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3svEXT(const GLshort *v, const char * _file, int _line) {
    glad_glSecondaryColor3svEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3ubEXT(GLubyte red, GLubyte green, GLubyte blue, const char * _file, int _line) {
    glad_glSecondaryColor3ubEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3ubvEXT(const GLubyte *v, const char * _file, int _line) {
    glad_glSecondaryColor3ubvEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3uiEXT(GLuint red, GLuint green, GLuint blue, const char * _file, int _line) {
    glad_glSecondaryColor3uiEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3uivEXT(const GLuint *v, const char * _file, int _line) {
    glad_glSecondaryColor3uivEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3usEXT(GLushort red, GLushort green, GLushort blue, const char * _file, int _line) {
    glad_glSecondaryColor3usEXT(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3usvEXT(const GLushort *v, const char * _file, int _line) {
    glad_glSecondaryColor3usvEXT(v);
    gl_check_error(_file, _line);
}


void _glSecondaryColorPointerEXT(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glSecondaryColorPointerEXT(size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glGenSemaphoresEXT(GLsizei n, GLuint *semaphores, const char * _file, int _line) {
    glad_glGenSemaphoresEXT(n, semaphores);
    gl_check_error(_file, _line);
}


void _glDeleteSemaphoresEXT(GLsizei n, const GLuint *semaphores, const char * _file, int _line) {
    glad_glDeleteSemaphoresEXT(n, semaphores);
    gl_check_error(_file, _line);
}


GLboolean _glIsSemaphoreEXT(GLuint semaphore, const char * _file, int _line) {
    auto val = glad_glIsSemaphoreEXT(semaphore);
    gl_check_error(_file, _line);
    return val;
}


void _glSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, const GLuint64 *params, const char * _file, int _line) {
    glad_glSemaphoreParameterui64vEXT(semaphore, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, GLuint64 *params, const char * _file, int _line) {
    glad_glGetSemaphoreParameterui64vEXT(semaphore, pname, params);
    gl_check_error(_file, _line);
}


void _glWaitSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint *buffers, GLuint numTextureBarriers, const GLuint *textures, const GLenum *srcLayouts, const char * _file, int _line) {
    glad_glWaitSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, srcLayouts);
    gl_check_error(_file, _line);
}


void _glSignalSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint *buffers, GLuint numTextureBarriers, const GLuint *textures, const GLenum *dstLayouts, const char * _file, int _line) {
    glad_glSignalSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, dstLayouts);
    gl_check_error(_file, _line);
}


void _glImportSemaphoreFdEXT(GLuint semaphore, GLenum handleType, GLint fd, const char * _file, int _line) {
    glad_glImportSemaphoreFdEXT(semaphore, handleType, fd);
    gl_check_error(_file, _line);
}


void _glImportSemaphoreWin32HandleEXT(GLuint semaphore, GLenum handleType, void *handle, const char * _file, int _line) {
    glad_glImportSemaphoreWin32HandleEXT(semaphore, handleType, handle);
    gl_check_error(_file, _line);
}


void _glImportSemaphoreWin32NameEXT(GLuint semaphore, GLenum handleType, const void *name, const char * _file, int _line) {
    glad_glImportSemaphoreWin32NameEXT(semaphore, handleType, name);
    gl_check_error(_file, _line);
}


void _glUseShaderProgramEXT(GLenum type, GLuint program, const char * _file, int _line) {
    glad_glUseShaderProgramEXT(type, program);
    gl_check_error(_file, _line);
}


void _glActiveProgramEXT(GLuint program, const char * _file, int _line) {
    glad_glActiveProgramEXT(program);
    gl_check_error(_file, _line);
}


GLuint _glCreateShaderProgramEXT(GLenum type, const GLchar *string, const char * _file, int _line) {
    auto val = glad_glCreateShaderProgramEXT(type, string);
    gl_check_error(_file, _line);
    return val;
}


void _glActiveShaderProgramEXT(GLuint pipeline, GLuint program, const char * _file, int _line) {
    glad_glActiveShaderProgramEXT(pipeline, program);
    gl_check_error(_file, _line);
}


void _glBindProgramPipelineEXT(GLuint pipeline, const char * _file, int _line) {
    glad_glBindProgramPipelineEXT(pipeline);
    gl_check_error(_file, _line);
}


GLuint _glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar **strings, const char * _file, int _line) {
    auto val = glad_glCreateShaderProgramvEXT(type, count, strings);
    gl_check_error(_file, _line);
    return val;
}


void _glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines, const char * _file, int _line) {
    glad_glDeleteProgramPipelinesEXT(n, pipelines);
    gl_check_error(_file, _line);
}


void _glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines, const char * _file, int _line) {
    glad_glGenProgramPipelinesEXT(n, pipelines);
    gl_check_error(_file, _line);
}


void _glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line) {
    glad_glGetProgramPipelineInfoLogEXT(pipeline, bufSize, length, infoLog);
    gl_check_error(_file, _line);
}


void _glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramPipelineivEXT(pipeline, pname, params);
    gl_check_error(_file, _line);
}


GLboolean _glIsProgramPipelineEXT(GLuint pipeline, const char * _file, int _line) {
    auto val = glad_glIsProgramPipelineEXT(pipeline);
    gl_check_error(_file, _line);
    return val;
}


void _glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program, const char * _file, int _line) {
    glad_glUseProgramStagesEXT(pipeline, stages, program);
    gl_check_error(_file, _line);
}


void _glValidateProgramPipelineEXT(GLuint pipeline, const char * _file, int _line) {
    glad_glValidateProgramPipelineEXT(pipeline);
    gl_check_error(_file, _line);
}


void _glFramebufferFetchBarrierEXT(const char * _file, int _line) {
    glad_glFramebufferFetchBarrierEXT();
    gl_check_error(_file, _line);
}


void _glBindImageTextureEXT(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format, const char * _file, int _line) {
    glad_glBindImageTextureEXT(index, texture, level, layered, layer, access, format);
    gl_check_error(_file, _line);
}


void _glMemoryBarrierEXT(GLbitfield barriers, const char * _file, int _line) {
    glad_glMemoryBarrierEXT(barriers);
    gl_check_error(_file, _line);
}


void _glStencilClearTagEXT(GLsizei stencilTagBits, GLuint stencilClearTag, const char * _file, int _line) {
    glad_glStencilClearTagEXT(stencilTagBits, stencilClearTag);
    gl_check_error(_file, _line);
}


void _glActiveStencilFaceEXT(GLenum face, const char * _file, int _line) {
    glad_glActiveStencilFaceEXT(face);
    gl_check_error(_file, _line);
}


void _glTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexImage3DEXT(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureLayerEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line) {
    glad_glFramebufferTextureLayerEXT(target, attachment, texture, level, layer);
    gl_check_error(_file, _line);
}


void _glTexBufferEXT(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line) {
    glad_glTexBufferEXT(target, internalformat, buffer);
    gl_check_error(_file, _line);
}


void _glTexParameterIivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glTexParameterIivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTexParameterIuivEXT(GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line) {
    glad_glTexParameterIuivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameterIivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTexParameterIivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameterIuivEXT(GLenum target, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetTexParameterIuivEXT(target, pname, params);
    gl_check_error(_file, _line);
}


void _glClearColorIiEXT(GLint red, GLint green, GLint blue, GLint alpha, const char * _file, int _line) {
    glad_glClearColorIiEXT(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glClearColorIuiEXT(GLuint red, GLuint green, GLuint blue, GLuint alpha, const char * _file, int _line) {
    glad_glClearColorIuiEXT(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


GLboolean _glAreTexturesResidentEXT(GLsizei n, const GLuint *textures, GLboolean *residences, const char * _file, int _line) {
    auto val = glad_glAreTexturesResidentEXT(n, textures, residences);
    gl_check_error(_file, _line);
    return val;
}


void _glBindTextureEXT(GLenum target, GLuint texture, const char * _file, int _line) {
    glad_glBindTextureEXT(target, texture);
    gl_check_error(_file, _line);
}


void _glDeleteTexturesEXT(GLsizei n, const GLuint *textures, const char * _file, int _line) {
    glad_glDeleteTexturesEXT(n, textures);
    gl_check_error(_file, _line);
}


void _glGenTexturesEXT(GLsizei n, GLuint *textures, const char * _file, int _line) {
    glad_glGenTexturesEXT(n, textures);
    gl_check_error(_file, _line);
}


GLboolean _glIsTextureEXT(GLuint texture, const char * _file, int _line) {
    auto val = glad_glIsTextureEXT(texture);
    gl_check_error(_file, _line);
    return val;
}


void _glPrioritizeTexturesEXT(GLsizei n, const GLuint *textures, const GLclampf *priorities, const char * _file, int _line) {
    glad_glPrioritizeTexturesEXT(n, textures, priorities);
    gl_check_error(_file, _line);
}


void _glTextureNormalEXT(GLenum mode, const char * _file, int _line) {
    glad_glTextureNormalEXT(mode);
    gl_check_error(_file, _line);
}


void _glGetQueryObjecti64vEXT(GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line) {
    glad_glGetQueryObjecti64vEXT(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetQueryObjectui64vEXT(GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line) {
    glad_glGetQueryObjectui64vEXT(id, pname, params);
    gl_check_error(_file, _line);
}


void _glBeginTransformFeedbackEXT(GLenum primitiveMode, const char * _file, int _line) {
    glad_glBeginTransformFeedbackEXT(primitiveMode);
    gl_check_error(_file, _line);
}


void _glEndTransformFeedbackEXT(const char * _file, int _line) {
    glad_glEndTransformFeedbackEXT();
    gl_check_error(_file, _line);
}


void _glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glBindBufferRangeEXT(target, index, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, const char * _file, int _line) {
    glad_glBindBufferOffsetEXT(target, index, buffer, offset);
    gl_check_error(_file, _line);
}


void _glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line) {
    glad_glBindBufferBaseEXT(target, index, buffer);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackVaryingsEXT(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode, const char * _file, int _line) {
    glad_glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbackVaryingEXT(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line) {
    glad_glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glArrayElementEXT(GLint i, const char * _file, int _line) {
    glad_glArrayElementEXT(i);
    gl_check_error(_file, _line);
}


void _glColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line) {
    glad_glColorPointerEXT(size, type, stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glDrawArraysEXT(GLenum mode, GLint first, GLsizei count, const char * _file, int _line) {
    glad_glDrawArraysEXT(mode, first, count);
    gl_check_error(_file, _line);
}


void _glEdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean *pointer, const char * _file, int _line) {
    glad_glEdgeFlagPointerEXT(stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glGetPointervEXT(GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetPointervEXT(pname, params);
    gl_check_error(_file, _line);
}


void _glIndexPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line) {
    glad_glIndexPointerEXT(type, stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glNormalPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line) {
    glad_glNormalPointerEXT(type, stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glTexCoordPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line) {
    glad_glTexCoordPointerEXT(size, type, stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glVertexPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line) {
    glad_glVertexPointerEXT(size, type, stride, count, pointer);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1dEXT(GLuint index, GLdouble x, const char * _file, int _line) {
    glad_glVertexAttribL1dEXT(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2dEXT(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexAttribL2dEXT(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexAttribL3dEXT(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexAttribL4dEXT(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL1dvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL2dvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL3dvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribL4dvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribLPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribLPointerEXT(index, size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribLdvEXT(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVertexAttribLdvEXT(index, pname, params);
    gl_check_error(_file, _line);
}


void _glBeginVertexShaderEXT(const char * _file, int _line) {
    glad_glBeginVertexShaderEXT();
    gl_check_error(_file, _line);
}


void _glEndVertexShaderEXT(const char * _file, int _line) {
    glad_glEndVertexShaderEXT();
    gl_check_error(_file, _line);
}


void _glBindVertexShaderEXT(GLuint id, const char * _file, int _line) {
    glad_glBindVertexShaderEXT(id);
    gl_check_error(_file, _line);
}


GLuint _glGenVertexShadersEXT(GLuint range, const char * _file, int _line) {
    auto val = glad_glGenVertexShadersEXT(range);
    gl_check_error(_file, _line);
    return val;
}


void _glDeleteVertexShaderEXT(GLuint id, const char * _file, int _line) {
    glad_glDeleteVertexShaderEXT(id);
    gl_check_error(_file, _line);
}


void _glShaderOp1EXT(GLenum op, GLuint res, GLuint arg1, const char * _file, int _line) {
    glad_glShaderOp1EXT(op, res, arg1);
    gl_check_error(_file, _line);
}


void _glShaderOp2EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, const char * _file, int _line) {
    glad_glShaderOp2EXT(op, res, arg1, arg2);
    gl_check_error(_file, _line);
}


void _glShaderOp3EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3, const char * _file, int _line) {
    glad_glShaderOp3EXT(op, res, arg1, arg2, arg3);
    gl_check_error(_file, _line);
}


void _glSwizzleEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW, const char * _file, int _line) {
    glad_glSwizzleEXT(res, in, outX, outY, outZ, outW);
    gl_check_error(_file, _line);
}


void _glWriteMaskEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW, const char * _file, int _line) {
    glad_glWriteMaskEXT(res, in, outX, outY, outZ, outW);
    gl_check_error(_file, _line);
}


void _glInsertComponentEXT(GLuint res, GLuint src, GLuint num, const char * _file, int _line) {
    glad_glInsertComponentEXT(res, src, num);
    gl_check_error(_file, _line);
}


void _glExtractComponentEXT(GLuint res, GLuint src, GLuint num, const char * _file, int _line) {
    glad_glExtractComponentEXT(res, src, num);
    gl_check_error(_file, _line);
}


GLuint _glGenSymbolsEXT(GLenum datatype, GLenum storagetype, GLenum range, GLuint components, const char * _file, int _line) {
    auto val = glad_glGenSymbolsEXT(datatype, storagetype, range, components);
    gl_check_error(_file, _line);
    return val;
}


void _glSetInvariantEXT(GLuint id, GLenum type, const void *addr, const char * _file, int _line) {
    glad_glSetInvariantEXT(id, type, addr);
    gl_check_error(_file, _line);
}


void _glSetLocalConstantEXT(GLuint id, GLenum type, const void *addr, const char * _file, int _line) {
    glad_glSetLocalConstantEXT(id, type, addr);
    gl_check_error(_file, _line);
}


void _glVariantbvEXT(GLuint id, const GLbyte *addr, const char * _file, int _line) {
    glad_glVariantbvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantsvEXT(GLuint id, const GLshort *addr, const char * _file, int _line) {
    glad_glVariantsvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantivEXT(GLuint id, const GLint *addr, const char * _file, int _line) {
    glad_glVariantivEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantfvEXT(GLuint id, const GLfloat *addr, const char * _file, int _line) {
    glad_glVariantfvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantdvEXT(GLuint id, const GLdouble *addr, const char * _file, int _line) {
    glad_glVariantdvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantubvEXT(GLuint id, const GLubyte *addr, const char * _file, int _line) {
    glad_glVariantubvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantusvEXT(GLuint id, const GLushort *addr, const char * _file, int _line) {
    glad_glVariantusvEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantuivEXT(GLuint id, const GLuint *addr, const char * _file, int _line) {
    glad_glVariantuivEXT(id, addr);
    gl_check_error(_file, _line);
}


void _glVariantPointerEXT(GLuint id, GLenum type, GLuint stride, const void *addr, const char * _file, int _line) {
    glad_glVariantPointerEXT(id, type, stride, addr);
    gl_check_error(_file, _line);
}


void _glEnableVariantClientStateEXT(GLuint id, const char * _file, int _line) {
    glad_glEnableVariantClientStateEXT(id);
    gl_check_error(_file, _line);
}


void _glDisableVariantClientStateEXT(GLuint id, const char * _file, int _line) {
    glad_glDisableVariantClientStateEXT(id);
    gl_check_error(_file, _line);
}


GLuint _glBindLightParameterEXT(GLenum light, GLenum value, const char * _file, int _line) {
    auto val = glad_glBindLightParameterEXT(light, value);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glBindMaterialParameterEXT(GLenum face, GLenum value, const char * _file, int _line) {
    auto val = glad_glBindMaterialParameterEXT(face, value);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glBindTexGenParameterEXT(GLenum unit, GLenum coord, GLenum value, const char * _file, int _line) {
    auto val = glad_glBindTexGenParameterEXT(unit, coord, value);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glBindTextureUnitParameterEXT(GLenum unit, GLenum value, const char * _file, int _line) {
    auto val = glad_glBindTextureUnitParameterEXT(unit, value);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glBindParameterEXT(GLenum value, const char * _file, int _line) {
    auto val = glad_glBindParameterEXT(value);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsVariantEnabledEXT(GLuint id, GLenum cap, const char * _file, int _line) {
    auto val = glad_glIsVariantEnabledEXT(id, cap);
    gl_check_error(_file, _line);
    return val;
}


void _glGetVariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line) {
    glad_glGetVariantBooleanvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetVariantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line) {
    glad_glGetVariantIntegervEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetVariantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line) {
    glad_glGetVariantFloatvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetVariantPointervEXT(GLuint id, GLenum value, void **data, const char * _file, int _line) {
    glad_glGetVariantPointervEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetInvariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line) {
    glad_glGetInvariantBooleanvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetInvariantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line) {
    glad_glGetInvariantIntegervEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetInvariantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line) {
    glad_glGetInvariantFloatvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetLocalConstantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line) {
    glad_glGetLocalConstantBooleanvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetLocalConstantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line) {
    glad_glGetLocalConstantIntegervEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glGetLocalConstantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line) {
    glad_glGetLocalConstantFloatvEXT(id, value, data);
    gl_check_error(_file, _line);
}


void _glVertexWeightfEXT(GLfloat weight, const char * _file, int _line) {
    glad_glVertexWeightfEXT(weight);
    gl_check_error(_file, _line);
}


void _glVertexWeightfvEXT(const GLfloat *weight, const char * _file, int _line) {
    glad_glVertexWeightfvEXT(weight);
    gl_check_error(_file, _line);
}


void _glVertexWeightPointerEXT(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexWeightPointerEXT(size, type, stride, pointer);
    gl_check_error(_file, _line);
}


GLboolean _glAcquireKeyedMutexWin32EXT(GLuint memory, GLuint64 key, GLuint timeout, const char * _file, int _line) {
    auto val = glad_glAcquireKeyedMutexWin32EXT(memory, key, timeout);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glReleaseKeyedMutexWin32EXT(GLuint memory, GLuint64 key, const char * _file, int _line) {
    auto val = glad_glReleaseKeyedMutexWin32EXT(memory, key);
    gl_check_error(_file, _line);
    return val;
}


void _glWindowRectanglesEXT(GLenum mode, GLsizei count, const GLint *box, const char * _file, int _line) {
    glad_glWindowRectanglesEXT(mode, count, box);
    gl_check_error(_file, _line);
}


GLsync _glImportSyncEXT(GLenum external_sync_type, GLintptr external_sync, GLbitfield flags, const char * _file, int _line) {
    auto val = glad_glImportSyncEXT(external_sync_type, external_sync, flags);
    gl_check_error(_file, _line);
    return val;
}


void _glFrameTerminatorGREMEDY(const char * _file, int _line) {
    glad_glFrameTerminatorGREMEDY();
    gl_check_error(_file, _line);
}


void _glStringMarkerGREMEDY(GLsizei len, const void *string, const char * _file, int _line) {
    glad_glStringMarkerGREMEDY(len, string);
    gl_check_error(_file, _line);
}


void _glImageTransformParameteriHP(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glImageTransformParameteriHP(target, pname, param);
    gl_check_error(_file, _line);
}


void _glImageTransformParameterfHP(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glImageTransformParameterfHP(target, pname, param);
    gl_check_error(_file, _line);
}


void _glImageTransformParameterivHP(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glImageTransformParameterivHP(target, pname, params);
    gl_check_error(_file, _line);
}


void _glImageTransformParameterfvHP(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glImageTransformParameterfvHP(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetImageTransformParameterivHP(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetImageTransformParameterivHP(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetImageTransformParameterfvHP(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetImageTransformParameterfvHP(target, pname, params);
    gl_check_error(_file, _line);
}


void _glMultiModeDrawArraysIBM(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride, const char * _file, int _line) {
    glad_glMultiModeDrawArraysIBM(mode, first, count, primcount, modestride);
    gl_check_error(_file, _line);
}


void _glMultiModeDrawElementsIBM(const GLenum *mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount, GLint modestride, const char * _file, int _line) {
    glad_glMultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride);
    gl_check_error(_file, _line);
}


void _glFlushStaticDataIBM(GLenum target, const char * _file, int _line) {
    glad_glFlushStaticDataIBM(target);
    gl_check_error(_file, _line);
}


void _glColorPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glColorPointerListIBM(size, type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glSecondaryColorPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glSecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glEdgeFlagPointerListIBM(GLint stride, const GLboolean **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glEdgeFlagPointerListIBM(stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glFogCoordPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glFogCoordPointerListIBM(type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glIndexPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glIndexPointerListIBM(type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glNormalPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glNormalPointerListIBM(type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glTexCoordPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glTexCoordPointerListIBM(size, type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glVertexPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line) {
    glad_glVertexPointerListIBM(size, type, stride, pointer, ptrstride);
    gl_check_error(_file, _line);
}


void _glBlendFuncSeparateINGR(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line) {
    glad_glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    gl_check_error(_file, _line);
}


void _glApplyFramebufferAttachmentCMAAINTEL(const char * _file, int _line) {
    glad_glApplyFramebufferAttachmentCMAAINTEL();
    gl_check_error(_file, _line);
}


void _glSyncTextureINTEL(GLuint texture, const char * _file, int _line) {
    glad_glSyncTextureINTEL(texture);
    gl_check_error(_file, _line);
}


void _glUnmapTexture2DINTEL(GLuint texture, GLint level, const char * _file, int _line) {
    glad_glUnmapTexture2DINTEL(texture, level);
    gl_check_error(_file, _line);
}


void * _glMapTexture2DINTEL(GLuint texture, GLint level, GLbitfield access, GLint *stride, GLenum *layout, const char * _file, int _line) {
    auto val = glad_glMapTexture2DINTEL(texture, level, access, stride, layout);
    gl_check_error(_file, _line);
    return val;
}


void _glVertexPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line) {
    glad_glVertexPointervINTEL(size, type, pointer);
    gl_check_error(_file, _line);
}


void _glNormalPointervINTEL(GLenum type, const void **pointer, const char * _file, int _line) {
    glad_glNormalPointervINTEL(type, pointer);
    gl_check_error(_file, _line);
}


void _glColorPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line) {
    glad_glColorPointervINTEL(size, type, pointer);
    gl_check_error(_file, _line);
}


void _glTexCoordPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line) {
    glad_glTexCoordPointervINTEL(size, type, pointer);
    gl_check_error(_file, _line);
}


void _glBeginPerfQueryINTEL(GLuint queryHandle, const char * _file, int _line) {
    glad_glBeginPerfQueryINTEL(queryHandle);
    gl_check_error(_file, _line);
}


void _glCreatePerfQueryINTEL(GLuint queryId, GLuint *queryHandle, const char * _file, int _line) {
    glad_glCreatePerfQueryINTEL(queryId, queryHandle);
    gl_check_error(_file, _line);
}


void _glDeletePerfQueryINTEL(GLuint queryHandle, const char * _file, int _line) {
    glad_glDeletePerfQueryINTEL(queryHandle);
    gl_check_error(_file, _line);
}


void _glEndPerfQueryINTEL(GLuint queryHandle, const char * _file, int _line) {
    glad_glEndPerfQueryINTEL(queryHandle);
    gl_check_error(_file, _line);
}


void _glGetFirstPerfQueryIdINTEL(GLuint *queryId, const char * _file, int _line) {
    glad_glGetFirstPerfQueryIdINTEL(queryId);
    gl_check_error(_file, _line);
}


void _glGetNextPerfQueryIdINTEL(GLuint queryId, GLuint *nextQueryId, const char * _file, int _line) {
    glad_glGetNextPerfQueryIdINTEL(queryId, nextQueryId);
    gl_check_error(_file, _line);
}


void _glGetPerfCounterInfoINTEL(GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar *counterName, GLuint counterDescLength, GLchar *counterDesc, GLuint *counterOffset, GLuint *counterDataSize, GLuint *counterTypeEnum, GLuint *counterDataTypeEnum, GLuint64 *rawCounterMaxValue, const char * _file, int _line) {
    glad_glGetPerfCounterInfoINTEL(queryId, counterId, counterNameLength, counterName, counterDescLength, counterDesc, counterOffset, counterDataSize, counterTypeEnum, counterDataTypeEnum, rawCounterMaxValue);
    gl_check_error(_file, _line);
}


void _glGetPerfQueryDataINTEL(GLuint queryHandle, GLuint flags, GLsizei dataSize, void *data, GLuint *bytesWritten, const char * _file, int _line) {
    glad_glGetPerfQueryDataINTEL(queryHandle, flags, dataSize, data, bytesWritten);
    gl_check_error(_file, _line);
}


void _glGetPerfQueryIdByNameINTEL(GLchar *queryName, GLuint *queryId, const char * _file, int _line) {
    glad_glGetPerfQueryIdByNameINTEL(queryName, queryId);
    gl_check_error(_file, _line);
}


void _glGetPerfQueryInfoINTEL(GLuint queryId, GLuint queryNameLength, GLchar *queryName, GLuint *dataSize, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask, const char * _file, int _line) {
    glad_glGetPerfQueryInfoINTEL(queryId, queryNameLength, queryName, dataSize, noCounters, noInstances, capsMask);
    gl_check_error(_file, _line);
}


void _glBlendBarrierKHR(const char * _file, int _line) {
    glad_glBlendBarrierKHR();
    gl_check_error(_file, _line);
}


void _glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line) {
    glad_glDebugMessageControl(source, type, severity, count, ids, enabled);
    gl_check_error(_file, _line);
}


void _glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line) {
    glad_glDebugMessageInsert(source, type, id, severity, length, buf);
    gl_check_error(_file, _line);
}


void _glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam, const char * _file, int _line) {
    glad_glDebugMessageCallback(callback, userParam);
    gl_check_error(_file, _line);
}


GLuint _glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line) {
    auto val = glad_glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
    gl_check_error(_file, _line);
    return val;
}


void _glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message, const char * _file, int _line) {
    glad_glPushDebugGroup(source, id, length, message);
    gl_check_error(_file, _line);
}


void _glPopDebugGroup(const char * _file, int _line) {
    glad_glPopDebugGroup();
    gl_check_error(_file, _line);
}


void _glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label, const char * _file, int _line) {
    glad_glObjectLabel(identifier, name, length, label);
    gl_check_error(_file, _line);
}


void _glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line) {
    glad_glGetObjectLabel(identifier, name, bufSize, length, label);
    gl_check_error(_file, _line);
}


void _glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label, const char * _file, int _line) {
    glad_glObjectPtrLabel(ptr, length, label);
    gl_check_error(_file, _line);
}


void _glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line) {
    glad_glGetObjectPtrLabel(ptr, bufSize, length, label);
    gl_check_error(_file, _line);
}


void _glGetPointerv(GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetPointerv(pname, params);
    gl_check_error(_file, _line);
}


void _glDebugMessageControlKHR(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line) {
    glad_glDebugMessageControlKHR(source, type, severity, count, ids, enabled);
    gl_check_error(_file, _line);
}


void _glDebugMessageInsertKHR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line) {
    glad_glDebugMessageInsertKHR(source, type, id, severity, length, buf);
    gl_check_error(_file, _line);
}


void _glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam, const char * _file, int _line) {
    glad_glDebugMessageCallbackKHR(callback, userParam);
    gl_check_error(_file, _line);
}


GLuint _glGetDebugMessageLogKHR(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line) {
    auto val = glad_glGetDebugMessageLogKHR(count, bufSize, sources, types, ids, severities, lengths, messageLog);
    gl_check_error(_file, _line);
    return val;
}


void _glPushDebugGroupKHR(GLenum source, GLuint id, GLsizei length, const GLchar *message, const char * _file, int _line) {
    glad_glPushDebugGroupKHR(source, id, length, message);
    gl_check_error(_file, _line);
}


void _glPopDebugGroupKHR(const char * _file, int _line) {
    glad_glPopDebugGroupKHR();
    gl_check_error(_file, _line);
}


void _glObjectLabelKHR(GLenum identifier, GLuint name, GLsizei length, const GLchar *label, const char * _file, int _line) {
    glad_glObjectLabelKHR(identifier, name, length, label);
    gl_check_error(_file, _line);
}


void _glGetObjectLabelKHR(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line) {
    glad_glGetObjectLabelKHR(identifier, name, bufSize, length, label);
    gl_check_error(_file, _line);
}


void _glObjectPtrLabelKHR(const void *ptr, GLsizei length, const GLchar *label, const char * _file, int _line) {
    glad_glObjectPtrLabelKHR(ptr, length, label);
    gl_check_error(_file, _line);
}


void _glGetObjectPtrLabelKHR(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line) {
    glad_glGetObjectPtrLabelKHR(ptr, bufSize, length, label);
    gl_check_error(_file, _line);
}


void _glGetPointervKHR(GLenum pname, void **params, const char * _file, int _line) {
    glad_glGetPointervKHR(pname, params);
    gl_check_error(_file, _line);
}


void _glMaxShaderCompilerThreadsKHR(GLuint count, const char * _file, int _line) {
    glad_glMaxShaderCompilerThreadsKHR(count);
    gl_check_error(_file, _line);
}


GLenum _glGetGraphicsResetStatus(const char * _file, int _line) {
    auto val = glad_glGetGraphicsResetStatus();
    gl_check_error(_file, _line);
    return val;
}


void _glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line) {
    glad_glReadnPixels(x, y, width, height, format, type, bufSize, data);
    gl_check_error(_file, _line);
}


void _glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line) {
    glad_glGetnUniformfv(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line) {
    glad_glGetnUniformiv(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line) {
    glad_glGetnUniformuiv(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


GLenum _glGetGraphicsResetStatusKHR(const char * _file, int _line) {
    auto val = glad_glGetGraphicsResetStatusKHR();
    gl_check_error(_file, _line);
    return val;
}


void _glReadnPixelsKHR(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line) {
    glad_glReadnPixelsKHR(x, y, width, height, format, type, bufSize, data);
    gl_check_error(_file, _line);
}


void _glGetnUniformfvKHR(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line) {
    glad_glGetnUniformfvKHR(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformivKHR(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line) {
    glad_glGetnUniformivKHR(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glGetnUniformuivKHR(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line) {
    glad_glGetnUniformuivKHR(program, location, bufSize, params);
    gl_check_error(_file, _line);
}


void _glFramebufferParameteriMESA(GLenum target, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glFramebufferParameteriMESA(target, pname, param);
    gl_check_error(_file, _line);
}


void _glGetFramebufferParameterivMESA(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFramebufferParameterivMESA(target, pname, params);
    gl_check_error(_file, _line);
}


void _glResizeBuffersMESA(const char * _file, int _line) {
    glad_glResizeBuffersMESA();
    gl_check_error(_file, _line);
}


void _glWindowPos2dMESA(GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glWindowPos2dMESA(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2dvMESA(const GLdouble *v, const char * _file, int _line) {
    glad_glWindowPos2dvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2fMESA(GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glWindowPos2fMESA(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2fvMESA(const GLfloat *v, const char * _file, int _line) {
    glad_glWindowPos2fvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2iMESA(GLint x, GLint y, const char * _file, int _line) {
    glad_glWindowPos2iMESA(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2ivMESA(const GLint *v, const char * _file, int _line) {
    glad_glWindowPos2ivMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos2sMESA(GLshort x, GLshort y, const char * _file, int _line) {
    glad_glWindowPos2sMESA(x, y);
    gl_check_error(_file, _line);
}


void _glWindowPos2svMESA(const GLshort *v, const char * _file, int _line) {
    glad_glWindowPos2svMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3dMESA(GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glWindowPos3dMESA(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3dvMESA(const GLdouble *v, const char * _file, int _line) {
    glad_glWindowPos3dvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3fMESA(GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glWindowPos3fMESA(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3fvMESA(const GLfloat *v, const char * _file, int _line) {
    glad_glWindowPos3fvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3iMESA(GLint x, GLint y, GLint z, const char * _file, int _line) {
    glad_glWindowPos3iMESA(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3ivMESA(const GLint *v, const char * _file, int _line) {
    glad_glWindowPos3ivMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos3sMESA(GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glWindowPos3sMESA(x, y, z);
    gl_check_error(_file, _line);
}


void _glWindowPos3svMESA(const GLshort *v, const char * _file, int _line) {
    glad_glWindowPos3svMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos4dMESA(GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glWindowPos4dMESA(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glWindowPos4dvMESA(const GLdouble *v, const char * _file, int _line) {
    glad_glWindowPos4dvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos4fMESA(GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glWindowPos4fMESA(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glWindowPos4fvMESA(const GLfloat *v, const char * _file, int _line) {
    glad_glWindowPos4fvMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos4iMESA(GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glWindowPos4iMESA(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glWindowPos4ivMESA(const GLint *v, const char * _file, int _line) {
    glad_glWindowPos4ivMESA(v);
    gl_check_error(_file, _line);
}


void _glWindowPos4sMESA(GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line) {
    glad_glWindowPos4sMESA(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glWindowPos4svMESA(const GLshort *v, const char * _file, int _line) {
    glad_glWindowPos4svMESA(v);
    gl_check_error(_file, _line);
}


void _glBeginConditionalRenderNVX(GLuint id, const char * _file, int _line) {
    glad_glBeginConditionalRenderNVX(id);
    gl_check_error(_file, _line);
}


void _glEndConditionalRenderNVX(const char * _file, int _line) {
    glad_glEndConditionalRenderNVX();
    gl_check_error(_file, _line);
}


void _glUploadGpuMaskNVX(GLbitfield mask, const char * _file, int _line) {
    glad_glUploadGpuMaskNVX(mask);
    gl_check_error(_file, _line);
}


void _glMulticastViewportArrayvNVX(GLuint gpu, GLuint first, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glMulticastViewportArrayvNVX(gpu, first, count, v);
    gl_check_error(_file, _line);
}


void _glMulticastViewportPositionWScaleNVX(GLuint gpu, GLuint index, GLfloat xcoeff, GLfloat ycoeff, const char * _file, int _line) {
    glad_glMulticastViewportPositionWScaleNVX(gpu, index, xcoeff, ycoeff);
    gl_check_error(_file, _line);
}


void _glMulticastScissorArrayvNVX(GLuint gpu, GLuint first, GLsizei count, const GLint *v, const char * _file, int _line) {
    glad_glMulticastScissorArrayvNVX(gpu, first, count, v);
    gl_check_error(_file, _line);
}


GLuint _glAsyncCopyBufferSubDataNVX(GLsizei waitSemaphoreCount, const GLuint *waitSemaphoreArray, const GLuint64 *fenceValueArray, GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, GLsizei signalSemaphoreCount, const GLuint *signalSemaphoreArray, const GLuint64 *signalValueArray, const char * _file, int _line) {
    auto val = glad_glAsyncCopyBufferSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, fenceValueArray, readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size, signalSemaphoreCount, signalSemaphoreArray, signalValueArray);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glAsyncCopyImageSubDataNVX(GLsizei waitSemaphoreCount, const GLuint *waitSemaphoreArray, const GLuint64 *waitValueArray, GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, GLsizei signalSemaphoreCount, const GLuint *signalSemaphoreArray, const GLuint64 *signalValueArray, const char * _file, int _line) {
    auto val = glad_glAsyncCopyImageSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, waitValueArray, srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth, signalSemaphoreCount, signalSemaphoreArray, signalValueArray);
    gl_check_error(_file, _line);
    return val;
}


void _glLGPUNamedBufferSubDataNVX(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line) {
    glad_glLGPUNamedBufferSubDataNVX(gpuMask, buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void _glLGPUCopyImageSubDataNVX(GLuint sourceGpu, GLbitfield destinationGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srxY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glLGPUCopyImageSubDataNVX(sourceGpu, destinationGpuMask, srcName, srcTarget, srcLevel, srcX, srxY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth);
    gl_check_error(_file, _line);
}


void _glLGPUInterlockNVX(const char * _file, int _line) {
    glad_glLGPUInterlockNVX();
    gl_check_error(_file, _line);
}


GLuint _glCreateProgressFenceNVX(const char * _file, int _line) {
    auto val = glad_glCreateProgressFenceNVX();
    gl_check_error(_file, _line);
    return val;
}


void _glSignalSemaphoreui64NVX(GLuint signalGpu, GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line) {
    glad_glSignalSemaphoreui64NVX(signalGpu, fenceObjectCount, semaphoreArray, fenceValueArray);
    gl_check_error(_file, _line);
}


void _glWaitSemaphoreui64NVX(GLuint waitGpu, GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line) {
    glad_glWaitSemaphoreui64NVX(waitGpu, fenceObjectCount, semaphoreArray, fenceValueArray);
    gl_check_error(_file, _line);
}


void _glClientWaitSemaphoreui64NVX(GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line) {
    glad_glClientWaitSemaphoreui64NVX(fenceObjectCount, semaphoreArray, fenceValueArray);
    gl_check_error(_file, _line);
}


void _glAlphaToCoverageDitherControlNV(GLenum mode, const char * _file, int _line) {
    glad_glAlphaToCoverageDitherControlNV(mode);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysIndirectBindlessNV(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line) {
    glad_glMultiDrawArraysIndirectBindlessNV(mode, indirect, drawCount, stride, vertexBufferCount);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsIndirectBindlessNV(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line) {
    glad_glMultiDrawElementsIndirectBindlessNV(mode, type, indirect, drawCount, stride, vertexBufferCount);
    gl_check_error(_file, _line);
}


void _glMultiDrawArraysIndirectBindlessCountNV(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line) {
    glad_glMultiDrawArraysIndirectBindlessCountNV(mode, indirect, drawCount, maxDrawCount, stride, vertexBufferCount);
    gl_check_error(_file, _line);
}


void _glMultiDrawElementsIndirectBindlessCountNV(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line) {
    glad_glMultiDrawElementsIndirectBindlessCountNV(mode, type, indirect, drawCount, maxDrawCount, stride, vertexBufferCount);
    gl_check_error(_file, _line);
}


GLuint64 _glGetTextureHandleNV(GLuint texture, const char * _file, int _line) {
    auto val = glad_glGetTextureHandleNV(texture);
    gl_check_error(_file, _line);
    return val;
}


GLuint64 _glGetTextureSamplerHandleNV(GLuint texture, GLuint sampler, const char * _file, int _line) {
    auto val = glad_glGetTextureSamplerHandleNV(texture, sampler);
    gl_check_error(_file, _line);
    return val;
}


void _glMakeTextureHandleResidentNV(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeTextureHandleResidentNV(handle);
    gl_check_error(_file, _line);
}


void _glMakeTextureHandleNonResidentNV(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeTextureHandleNonResidentNV(handle);
    gl_check_error(_file, _line);
}


GLuint64 _glGetImageHandleNV(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format, const char * _file, int _line) {
    auto val = glad_glGetImageHandleNV(texture, level, layered, layer, format);
    gl_check_error(_file, _line);
    return val;
}


void _glMakeImageHandleResidentNV(GLuint64 handle, GLenum access, const char * _file, int _line) {
    glad_glMakeImageHandleResidentNV(handle, access);
    gl_check_error(_file, _line);
}


void _glMakeImageHandleNonResidentNV(GLuint64 handle, const char * _file, int _line) {
    glad_glMakeImageHandleNonResidentNV(handle);
    gl_check_error(_file, _line);
}


void _glUniformHandleui64NV(GLint location, GLuint64 value, const char * _file, int _line) {
    glad_glUniformHandleui64NV(location, value);
    gl_check_error(_file, _line);
}


void _glUniformHandleui64vNV(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line) {
    glad_glUniformHandleui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformHandleui64NV(GLuint program, GLint location, GLuint64 value, const char * _file, int _line) {
    glad_glProgramUniformHandleui64NV(program, location, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformHandleui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64 *values, const char * _file, int _line) {
    glad_glProgramUniformHandleui64vNV(program, location, count, values);
    gl_check_error(_file, _line);
}


GLboolean _glIsTextureHandleResidentNV(GLuint64 handle, const char * _file, int _line) {
    auto val = glad_glIsTextureHandleResidentNV(handle);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsImageHandleResidentNV(GLuint64 handle, const char * _file, int _line) {
    auto val = glad_glIsImageHandleResidentNV(handle);
    gl_check_error(_file, _line);
    return val;
}


void _glBlendParameteriNV(GLenum pname, GLint value, const char * _file, int _line) {
    glad_glBlendParameteriNV(pname, value);
    gl_check_error(_file, _line);
}


void _glBlendBarrierNV(const char * _file, int _line) {
    glad_glBlendBarrierNV();
    gl_check_error(_file, _line);
}


void _glViewportPositionWScaleNV(GLuint index, GLfloat xcoeff, GLfloat ycoeff, const char * _file, int _line) {
    glad_glViewportPositionWScaleNV(index, xcoeff, ycoeff);
    gl_check_error(_file, _line);
}


void _glCreateStatesNV(GLsizei n, GLuint *states, const char * _file, int _line) {
    glad_glCreateStatesNV(n, states);
    gl_check_error(_file, _line);
}


void _glDeleteStatesNV(GLsizei n, const GLuint *states, const char * _file, int _line) {
    glad_glDeleteStatesNV(n, states);
    gl_check_error(_file, _line);
}


GLboolean _glIsStateNV(GLuint state, const char * _file, int _line) {
    auto val = glad_glIsStateNV(state);
    gl_check_error(_file, _line);
    return val;
}


void _glStateCaptureNV(GLuint state, GLenum mode, const char * _file, int _line) {
    glad_glStateCaptureNV(state, mode);
    gl_check_error(_file, _line);
}


GLuint _glGetCommandHeaderNV(GLenum tokenID, GLuint size, const char * _file, int _line) {
    auto val = glad_glGetCommandHeaderNV(tokenID, size);
    gl_check_error(_file, _line);
    return val;
}


GLushort _glGetStageIndexNV(GLenum shadertype, const char * _file, int _line) {
    auto val = glad_glGetStageIndexNV(shadertype);
    gl_check_error(_file, _line);
    return val;
}


void _glDrawCommandsNV(GLenum primitiveMode, GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, GLuint count, const char * _file, int _line) {
    glad_glDrawCommandsNV(primitiveMode, buffer, indirects, sizes, count);
    gl_check_error(_file, _line);
}


void _glDrawCommandsAddressNV(GLenum primitiveMode, const GLuint64 *indirects, const GLsizei *sizes, GLuint count, const char * _file, int _line) {
    glad_glDrawCommandsAddressNV(primitiveMode, indirects, sizes, count);
    gl_check_error(_file, _line);
}


void _glDrawCommandsStatesNV(GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line) {
    glad_glDrawCommandsStatesNV(buffer, indirects, sizes, states, fbos, count);
    gl_check_error(_file, _line);
}


void _glDrawCommandsStatesAddressNV(const GLuint64 *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line) {
    glad_glDrawCommandsStatesAddressNV(indirects, sizes, states, fbos, count);
    gl_check_error(_file, _line);
}


void _glCreateCommandListsNV(GLsizei n, GLuint *lists, const char * _file, int _line) {
    glad_glCreateCommandListsNV(n, lists);
    gl_check_error(_file, _line);
}


void _glDeleteCommandListsNV(GLsizei n, const GLuint *lists, const char * _file, int _line) {
    glad_glDeleteCommandListsNV(n, lists);
    gl_check_error(_file, _line);
}


GLboolean _glIsCommandListNV(GLuint list, const char * _file, int _line) {
    auto val = glad_glIsCommandListNV(list);
    gl_check_error(_file, _line);
    return val;
}


void _glListDrawCommandsStatesClientNV(GLuint list, GLuint segment, const void **indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line) {
    glad_glListDrawCommandsStatesClientNV(list, segment, indirects, sizes, states, fbos, count);
    gl_check_error(_file, _line);
}


void _glCommandListSegmentsNV(GLuint list, GLuint segments, const char * _file, int _line) {
    glad_glCommandListSegmentsNV(list, segments);
    gl_check_error(_file, _line);
}


void _glCompileCommandListNV(GLuint list, const char * _file, int _line) {
    glad_glCompileCommandListNV(list);
    gl_check_error(_file, _line);
}


void _glCallCommandListNV(GLuint list, const char * _file, int _line) {
    glad_glCallCommandListNV(list);
    gl_check_error(_file, _line);
}


void _glBeginConditionalRenderNV(GLuint id, GLenum mode, const char * _file, int _line) {
    glad_glBeginConditionalRenderNV(id, mode);
    gl_check_error(_file, _line);
}


void _glEndConditionalRenderNV(const char * _file, int _line) {
    glad_glEndConditionalRenderNV();
    gl_check_error(_file, _line);
}


void _glSubpixelPrecisionBiasNV(GLuint xbits, GLuint ybits, const char * _file, int _line) {
    glad_glSubpixelPrecisionBiasNV(xbits, ybits);
    gl_check_error(_file, _line);
}


void _glConservativeRasterParameterfNV(GLenum pname, GLfloat value, const char * _file, int _line) {
    glad_glConservativeRasterParameterfNV(pname, value);
    gl_check_error(_file, _line);
}


void _glConservativeRasterParameteriNV(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glConservativeRasterParameteriNV(pname, param);
    gl_check_error(_file, _line);
}


void _glCopyImageSubDataNV(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line) {
    glad_glCopyImageSubDataNV(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth);
    gl_check_error(_file, _line);
}


void _glDepthRangedNV(GLdouble zNear, GLdouble zFar, const char * _file, int _line) {
    glad_glDepthRangedNV(zNear, zFar);
    gl_check_error(_file, _line);
}


void _glClearDepthdNV(GLdouble depth, const char * _file, int _line) {
    glad_glClearDepthdNV(depth);
    gl_check_error(_file, _line);
}


void _glDepthBoundsdNV(GLdouble zmin, GLdouble zmax, const char * _file, int _line) {
    glad_glDepthBoundsdNV(zmin, zmax);
    gl_check_error(_file, _line);
}


void _glDrawTextureNV(GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1, const char * _file, int _line) {
    glad_glDrawTextureNV(texture, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1);
    gl_check_error(_file, _line);
}


void _glDrawVkImageNV(GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1, const char * _file, int _line) {
    glad_glDrawVkImageNV(vkImage, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1);
    gl_check_error(_file, _line);
}


GLVULKANPROCNV _glGetVkProcAddrNV(const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetVkProcAddrNV(name);
    gl_check_error(_file, _line);
    return val;
}


void _glWaitVkSemaphoreNV(GLuint64 vkSemaphore, const char * _file, int _line) {
    glad_glWaitVkSemaphoreNV(vkSemaphore);
    gl_check_error(_file, _line);
}


void _glSignalVkSemaphoreNV(GLuint64 vkSemaphore, const char * _file, int _line) {
    glad_glSignalVkSemaphoreNV(vkSemaphore);
    gl_check_error(_file, _line);
}


void _glSignalVkFenceNV(GLuint64 vkFence, const char * _file, int _line) {
    glad_glSignalVkFenceNV(vkFence);
    gl_check_error(_file, _line);
}


void _glMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void *points, const char * _file, int _line) {
    glad_glMapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points);
    gl_check_error(_file, _line);
}


void _glMapParameterivNV(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glMapParameterivNV(target, pname, params);
    gl_check_error(_file, _line);
}


void _glMapParameterfvNV(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glMapParameterfvNV(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void *points, const char * _file, int _line) {
    glad_glGetMapControlPointsNV(target, index, type, ustride, vstride, packed, points);
    gl_check_error(_file, _line);
}


void _glGetMapParameterivNV(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMapParameterivNV(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMapParameterfvNV(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMapParameterfvNV(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMapAttribParameterivNV(GLenum target, GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetMapAttribParameterivNV(target, index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMapAttribParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetMapAttribParameterfvNV(target, index, pname, params);
    gl_check_error(_file, _line);
}


void _glEvalMapsNV(GLenum target, GLenum mode, const char * _file, int _line) {
    glad_glEvalMapsNV(target, mode);
    gl_check_error(_file, _line);
}


void _glGetMultisamplefvNV(GLenum pname, GLuint index, GLfloat *val, const char * _file, int _line) {
    glad_glGetMultisamplefvNV(pname, index, val);
    gl_check_error(_file, _line);
}


void _glSampleMaskIndexedNV(GLuint index, GLbitfield mask, const char * _file, int _line) {
    glad_glSampleMaskIndexedNV(index, mask);
    gl_check_error(_file, _line);
}


void _glTexRenderbufferNV(GLenum target, GLuint renderbuffer, const char * _file, int _line) {
    glad_glTexRenderbufferNV(target, renderbuffer);
    gl_check_error(_file, _line);
}


void _glDeleteFencesNV(GLsizei n, const GLuint *fences, const char * _file, int _line) {
    glad_glDeleteFencesNV(n, fences);
    gl_check_error(_file, _line);
}


void _glGenFencesNV(GLsizei n, GLuint *fences, const char * _file, int _line) {
    glad_glGenFencesNV(n, fences);
    gl_check_error(_file, _line);
}


GLboolean _glIsFenceNV(GLuint fence, const char * _file, int _line) {
    auto val = glad_glIsFenceNV(fence);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glTestFenceNV(GLuint fence, const char * _file, int _line) {
    auto val = glad_glTestFenceNV(fence);
    gl_check_error(_file, _line);
    return val;
}


void _glGetFenceivNV(GLuint fence, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFenceivNV(fence, pname, params);
    gl_check_error(_file, _line);
}


void _glFinishFenceNV(GLuint fence, const char * _file, int _line) {
    glad_glFinishFenceNV(fence);
    gl_check_error(_file, _line);
}


void _glSetFenceNV(GLuint fence, GLenum condition, const char * _file, int _line) {
    glad_glSetFenceNV(fence, condition);
    gl_check_error(_file, _line);
}


void _glFragmentCoverageColorNV(GLuint color, const char * _file, int _line) {
    glad_glFragmentCoverageColorNV(color);
    gl_check_error(_file, _line);
}


void _glProgramNamedParameter4fNV(GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glProgramNamedParameter4fNV(id, len, name, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramNamedParameter4fvNV(GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v, const char * _file, int _line) {
    glad_glProgramNamedParameter4fvNV(id, len, name, v);
    gl_check_error(_file, _line);
}


void _glProgramNamedParameter4dNV(GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glProgramNamedParameter4dNV(id, len, name, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramNamedParameter4dvNV(GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v, const char * _file, int _line) {
    glad_glProgramNamedParameter4dvNV(id, len, name, v);
    gl_check_error(_file, _line);
}


void _glGetProgramNamedParameterfvNV(GLuint id, GLsizei len, const GLubyte *name, GLfloat *params, const char * _file, int _line) {
    glad_glGetProgramNamedParameterfvNV(id, len, name, params);
    gl_check_error(_file, _line);
}


void _glGetProgramNamedParameterdvNV(GLuint id, GLsizei len, const GLubyte *name, GLdouble *params, const char * _file, int _line) {
    glad_glGetProgramNamedParameterdvNV(id, len, name, params);
    gl_check_error(_file, _line);
}


void _glCoverageModulationTableNV(GLsizei n, const GLfloat *v, const char * _file, int _line) {
    glad_glCoverageModulationTableNV(n, v);
    gl_check_error(_file, _line);
}


void _glGetCoverageModulationTableNV(GLsizei bufSize, GLfloat *v, const char * _file, int _line) {
    glad_glGetCoverageModulationTableNV(bufSize, v);
    gl_check_error(_file, _line);
}


void _glCoverageModulationNV(GLenum components, const char * _file, int _line) {
    glad_glCoverageModulationNV(components);
    gl_check_error(_file, _line);
}


void _glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glRenderbufferStorageMultisampleCoverageNV(target, coverageSamples, colorSamples, internalformat, width, height);
    gl_check_error(_file, _line);
}


void _glProgramVertexLimitNV(GLenum target, GLint limit, const char * _file, int _line) {
    glad_glProgramVertexLimitNV(target, limit);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line) {
    glad_glFramebufferTextureEXT(target, attachment, texture, level);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureFaceEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line) {
    glad_glFramebufferTextureFaceEXT(target, attachment, texture, level, face);
    gl_check_error(_file, _line);
}


void _glRenderGpuMaskNV(GLbitfield mask, const char * _file, int _line) {
    glad_glRenderGpuMaskNV(mask);
    gl_check_error(_file, _line);
}


void _glMulticastBufferSubDataNV(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line) {
    glad_glMulticastBufferSubDataNV(gpuMask, buffer, offset, size, data);
    gl_check_error(_file, _line);
}


void _glMulticastCopyBufferSubDataNV(GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line) {
    glad_glMulticastCopyBufferSubDataNV(readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size);
    gl_check_error(_file, _line);
}


void _glMulticastCopyImageSubDataNV(GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, const char * _file, int _line) {
    glad_glMulticastCopyImageSubDataNV(srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    gl_check_error(_file, _line);
}


void _glMulticastBlitFramebufferNV(GLuint srcGpu, GLuint dstGpu, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line) {
    glad_glMulticastBlitFramebufferNV(srcGpu, dstGpu, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    gl_check_error(_file, _line);
}


void _glMulticastFramebufferSampleLocationsfvNV(GLuint gpu, GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glMulticastFramebufferSampleLocationsfvNV(gpu, framebuffer, start, count, v);
    gl_check_error(_file, _line);
}


void _glMulticastBarrierNV(const char * _file, int _line) {
    glad_glMulticastBarrierNV();
    gl_check_error(_file, _line);
}


void _glMulticastWaitSyncNV(GLuint signalGpu, GLbitfield waitGpuMask, const char * _file, int _line) {
    glad_glMulticastWaitSyncNV(signalGpu, waitGpuMask);
    gl_check_error(_file, _line);
}


void _glMulticastGetQueryObjectivNV(GLuint gpu, GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glMulticastGetQueryObjectivNV(gpu, id, pname, params);
    gl_check_error(_file, _line);
}


void _glMulticastGetQueryObjectuivNV(GLuint gpu, GLuint id, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glMulticastGetQueryObjectuivNV(gpu, id, pname, params);
    gl_check_error(_file, _line);
}


void _glMulticastGetQueryObjecti64vNV(GLuint gpu, GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line) {
    glad_glMulticastGetQueryObjecti64vNV(gpu, id, pname, params);
    gl_check_error(_file, _line);
}


void _glMulticastGetQueryObjectui64vNV(GLuint gpu, GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line) {
    glad_glMulticastGetQueryObjectui64vNV(gpu, id, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glProgramLocalParameterI4iNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameterI4ivNV(GLenum target, GLuint index, const GLint *params, const char * _file, int _line) {
    glad_glProgramLocalParameterI4ivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line) {
    glad_glProgramLocalParametersI4ivNV(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line) {
    glad_glProgramLocalParameterI4uiNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramLocalParameterI4uivNV(GLenum target, GLuint index, const GLuint *params, const char * _file, int _line) {
    glad_glProgramLocalParameterI4uivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramLocalParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line) {
    glad_glProgramLocalParametersI4uivNV(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glProgramEnvParameterI4iNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameterI4ivNV(GLenum target, GLuint index, const GLint *params, const char * _file, int _line) {
    glad_glProgramEnvParameterI4ivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramEnvParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line) {
    glad_glProgramEnvParametersI4ivNV(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line) {
    glad_glProgramEnvParameterI4uiNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramEnvParameterI4uivNV(GLenum target, GLuint index, const GLuint *params, const char * _file, int _line) {
    glad_glProgramEnvParameterI4uivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramEnvParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line) {
    glad_glProgramEnvParametersI4uivNV(target, index, count, params);
    gl_check_error(_file, _line);
}


void _glGetProgramLocalParameterIivNV(GLenum target, GLuint index, GLint *params, const char * _file, int _line) {
    glad_glGetProgramLocalParameterIivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramLocalParameterIuivNV(GLenum target, GLuint index, GLuint *params, const char * _file, int _line) {
    glad_glGetProgramLocalParameterIuivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramEnvParameterIivNV(GLenum target, GLuint index, GLint *params, const char * _file, int _line) {
    glad_glGetProgramEnvParameterIivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glGetProgramEnvParameterIuivNV(GLenum target, GLuint index, GLuint *params, const char * _file, int _line) {
    glad_glGetProgramEnvParameterIuivNV(target, index, params);
    gl_check_error(_file, _line);
}


void _glProgramSubroutineParametersuivNV(GLenum target, GLsizei count, const GLuint *params, const char * _file, int _line) {
    glad_glProgramSubroutineParametersuivNV(target, count, params);
    gl_check_error(_file, _line);
}


void _glGetProgramSubroutineParameteruivNV(GLenum target, GLuint index, GLuint *param, const char * _file, int _line) {
    glad_glGetProgramSubroutineParameteruivNV(target, index, param);
    gl_check_error(_file, _line);
}


void _glVertex2hNV(GLhalfNV x, GLhalfNV y, const char * _file, int _line) {
    glad_glVertex2hNV(x, y);
    gl_check_error(_file, _line);
}


void _glVertex2hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertex2hvNV(v);
    gl_check_error(_file, _line);
}


void _glVertex3hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, const char * _file, int _line) {
    glad_glVertex3hNV(x, y, z);
    gl_check_error(_file, _line);
}


void _glVertex3hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertex3hvNV(v);
    gl_check_error(_file, _line);
}


void _glVertex4hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w, const char * _file, int _line) {
    glad_glVertex4hNV(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertex4hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertex4hvNV(v);
    gl_check_error(_file, _line);
}


void _glNormal3hNV(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz, const char * _file, int _line) {
    glad_glNormal3hNV(nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glNormal3hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glNormal3hvNV(v);
    gl_check_error(_file, _line);
}


void _glColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, const char * _file, int _line) {
    glad_glColor3hNV(red, green, blue);
    gl_check_error(_file, _line);
}


void _glColor3hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glColor3hvNV(v);
    gl_check_error(_file, _line);
}


void _glColor4hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha, const char * _file, int _line) {
    glad_glColor4hNV(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glColor4hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glColor4hvNV(v);
    gl_check_error(_file, _line);
}


void _glTexCoord1hNV(GLhalfNV s, const char * _file, int _line) {
    glad_glTexCoord1hNV(s);
    gl_check_error(_file, _line);
}


void _glTexCoord1hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glTexCoord1hvNV(v);
    gl_check_error(_file, _line);
}


void _glTexCoord2hNV(GLhalfNV s, GLhalfNV t, const char * _file, int _line) {
    glad_glTexCoord2hNV(s, t);
    gl_check_error(_file, _line);
}


void _glTexCoord2hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glTexCoord2hvNV(v);
    gl_check_error(_file, _line);
}


void _glTexCoord3hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, const char * _file, int _line) {
    glad_glTexCoord3hNV(s, t, r);
    gl_check_error(_file, _line);
}


void _glTexCoord3hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glTexCoord3hvNV(v);
    gl_check_error(_file, _line);
}


void _glTexCoord4hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q, const char * _file, int _line) {
    glad_glTexCoord4hNV(s, t, r, q);
    gl_check_error(_file, _line);
}


void _glTexCoord4hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glTexCoord4hvNV(v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1hNV(GLenum target, GLhalfNV s, const char * _file, int _line) {
    glad_glMultiTexCoord1hNV(target, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line) {
    glad_glMultiTexCoord1hvNV(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2hNV(GLenum target, GLhalfNV s, GLhalfNV t, const char * _file, int _line) {
    glad_glMultiTexCoord2hNV(target, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line) {
    glad_glMultiTexCoord2hvNV(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, const char * _file, int _line) {
    glad_glMultiTexCoord3hNV(target, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line) {
    glad_glMultiTexCoord3hvNV(target, v);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q, const char * _file, int _line) {
    glad_glMultiTexCoord4hNV(target, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line) {
    glad_glMultiTexCoord4hvNV(target, v);
    gl_check_error(_file, _line);
}


void _glFogCoordhNV(GLhalfNV fog, const char * _file, int _line) {
    glad_glFogCoordhNV(fog);
    gl_check_error(_file, _line);
}


void _glFogCoordhvNV(const GLhalfNV *fog, const char * _file, int _line) {
    glad_glFogCoordhvNV(fog);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, const char * _file, int _line) {
    glad_glSecondaryColor3hNV(red, green, blue);
    gl_check_error(_file, _line);
}


void _glSecondaryColor3hvNV(const GLhalfNV *v, const char * _file, int _line) {
    glad_glSecondaryColor3hvNV(v);
    gl_check_error(_file, _line);
}


void _glVertexWeighthNV(GLhalfNV weight, const char * _file, int _line) {
    glad_glVertexWeighthNV(weight);
    gl_check_error(_file, _line);
}


void _glVertexWeighthvNV(const GLhalfNV *weight, const char * _file, int _line) {
    glad_glVertexWeighthvNV(weight);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1hNV(GLuint index, GLhalfNV x, const char * _file, int _line) {
    glad_glVertexAttrib1hNV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttrib1hvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2hNV(GLuint index, GLhalfNV x, GLhalfNV y, const char * _file, int _line) {
    glad_glVertexAttrib2hNV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttrib2hvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, const char * _file, int _line) {
    glad_glVertexAttrib3hNV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttrib3hvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w, const char * _file, int _line) {
    glad_glVertexAttrib4hNV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttrib4hvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs1hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttribs1hvNV(index, n, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs2hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttribs2hvNV(index, n, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs3hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttribs3hvNV(index, n, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs4hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line) {
    glad_glVertexAttribs4hvNV(index, n, v);
    gl_check_error(_file, _line);
}


void _glGetInternalformatSampleivNV(GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei count, GLint *params, const char * _file, int _line) {
    glad_glGetInternalformatSampleivNV(target, internalformat, samples, pname, count, params);
    gl_check_error(_file, _line);
}


void _glGetMemoryObjectDetachedResourcesuivNV(GLuint memory, GLenum pname, GLint first, GLsizei count, GLuint *params, const char * _file, int _line) {
    glad_glGetMemoryObjectDetachedResourcesuivNV(memory, pname, first, count, params);
    gl_check_error(_file, _line);
}


void _glResetMemoryObjectParameterNV(GLuint memory, GLenum pname, const char * _file, int _line) {
    glad_glResetMemoryObjectParameterNV(memory, pname);
    gl_check_error(_file, _line);
}


void _glTexAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTexAttachMemoryNV(target, memory, offset);
    gl_check_error(_file, _line);
}


void _glBufferAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glBufferAttachMemoryNV(target, memory, offset);
    gl_check_error(_file, _line);
}


void _glTextureAttachMemoryNV(GLuint texture, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glTextureAttachMemoryNV(texture, memory, offset);
    gl_check_error(_file, _line);
}


void _glNamedBufferAttachMemoryNV(GLuint buffer, GLuint memory, GLuint64 offset, const char * _file, int _line) {
    glad_glNamedBufferAttachMemoryNV(buffer, memory, offset);
    gl_check_error(_file, _line);
}


void _glBufferPageCommitmentMemNV(GLenum target, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit, const char * _file, int _line) {
    glad_glBufferPageCommitmentMemNV(target, offset, size, memory, memOffset, commit);
    gl_check_error(_file, _line);
}


void _glTexPageCommitmentMemNV(GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit, const char * _file, int _line) {
    glad_glTexPageCommitmentMemNV(target, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit);
    gl_check_error(_file, _line);
}


void _glNamedBufferPageCommitmentMemNV(GLuint buffer, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit, const char * _file, int _line) {
    glad_glNamedBufferPageCommitmentMemNV(buffer, offset, size, memory, memOffset, commit);
    gl_check_error(_file, _line);
}


void _glTexturePageCommitmentMemNV(GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit, const char * _file, int _line) {
    glad_glTexturePageCommitmentMemNV(texture, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit);
    gl_check_error(_file, _line);
}


void _glDrawMeshTasksNV(GLuint first, GLuint count, const char * _file, int _line) {
    glad_glDrawMeshTasksNV(first, count);
    gl_check_error(_file, _line);
}


void _glDrawMeshTasksIndirectNV(GLintptr indirect, const char * _file, int _line) {
    glad_glDrawMeshTasksIndirectNV(indirect);
    gl_check_error(_file, _line);
}


void _glMultiDrawMeshTasksIndirectNV(GLintptr indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawMeshTasksIndirectNV(indirect, drawcount, stride);
    gl_check_error(_file, _line);
}


void _glMultiDrawMeshTasksIndirectCountNV(GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line) {
    glad_glMultiDrawMeshTasksIndirectCountNV(indirect, drawcount, maxdrawcount, stride);
    gl_check_error(_file, _line);
}


void _glGenOcclusionQueriesNV(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glGenOcclusionQueriesNV(n, ids);
    gl_check_error(_file, _line);
}


void _glDeleteOcclusionQueriesNV(GLsizei n, const GLuint *ids, const char * _file, int _line) {
    glad_glDeleteOcclusionQueriesNV(n, ids);
    gl_check_error(_file, _line);
}


GLboolean _glIsOcclusionQueryNV(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsOcclusionQueryNV(id);
    gl_check_error(_file, _line);
    return val;
}


void _glBeginOcclusionQueryNV(GLuint id, const char * _file, int _line) {
    glad_glBeginOcclusionQueryNV(id);
    gl_check_error(_file, _line);
}


void _glEndOcclusionQueryNV(const char * _file, int _line) {
    glad_glEndOcclusionQueryNV();
    gl_check_error(_file, _line);
}


void _glGetOcclusionQueryivNV(GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetOcclusionQueryivNV(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetOcclusionQueryuivNV(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetOcclusionQueryuivNV(id, pname, params);
    gl_check_error(_file, _line);
}


void _glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLfloat *params, const char * _file, int _line) {
    glad_glProgramBufferParametersfvNV(target, bindingIndex, wordIndex, count, params);
    gl_check_error(_file, _line);
}


void _glProgramBufferParametersIivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLint *params, const char * _file, int _line) {
    glad_glProgramBufferParametersIivNV(target, bindingIndex, wordIndex, count, params);
    gl_check_error(_file, _line);
}


void _glProgramBufferParametersIuivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLuint *params, const char * _file, int _line) {
    glad_glProgramBufferParametersIuivNV(target, bindingIndex, wordIndex, count, params);
    gl_check_error(_file, _line);
}


GLuint _glGenPathsNV(GLsizei range, const char * _file, int _line) {
    auto val = glad_glGenPathsNV(range);
    gl_check_error(_file, _line);
    return val;
}


void _glDeletePathsNV(GLuint path, GLsizei range, const char * _file, int _line) {
    glad_glDeletePathsNV(path, range);
    gl_check_error(_file, _line);
}


GLboolean _glIsPathNV(GLuint path, const char * _file, int _line) {
    auto val = glad_glIsPathNV(path);
    gl_check_error(_file, _line);
    return val;
}


void _glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line) {
    glad_glPathCommandsNV(path, numCommands, commands, numCoords, coordType, coords);
    gl_check_error(_file, _line);
}


void _glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line) {
    glad_glPathCoordsNV(path, numCoords, coordType, coords);
    gl_check_error(_file, _line);
}


void _glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line) {
    glad_glPathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords);
    gl_check_error(_file, _line);
}


void _glPathSubCoordsNV(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line) {
    glad_glPathSubCoordsNV(path, coordStart, numCoords, coordType, coords);
    gl_check_error(_file, _line);
}


void _glPathStringNV(GLuint path, GLenum format, GLsizei length, const void *pathString, const char * _file, int _line) {
    glad_glPathStringNV(path, format, length, pathString);
    gl_check_error(_file, _line);
}


void _glPathGlyphsNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line) {
    glad_glPathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale);
    gl_check_error(_file, _line);
}


void _glPathGlyphRangeNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line) {
    glad_glPathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale);
    gl_check_error(_file, _line);
}


void _glWeightPathsNV(GLuint resultPath, GLsizei numPaths, const GLuint *paths, const GLfloat *weights, const char * _file, int _line) {
    glad_glWeightPathsNV(resultPath, numPaths, paths, weights);
    gl_check_error(_file, _line);
}


void _glCopyPathNV(GLuint resultPath, GLuint srcPath, const char * _file, int _line) {
    glad_glCopyPathNV(resultPath, srcPath);
    gl_check_error(_file, _line);
}


void _glInterpolatePathsNV(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight, const char * _file, int _line) {
    glad_glInterpolatePathsNV(resultPath, pathA, pathB, weight);
    gl_check_error(_file, _line);
}


void _glTransformPathNV(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glTransformPathNV(resultPath, srcPath, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glPathParameterivNV(GLuint path, GLenum pname, const GLint *value, const char * _file, int _line) {
    glad_glPathParameterivNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glPathParameteriNV(GLuint path, GLenum pname, GLint value, const char * _file, int _line) {
    glad_glPathParameteriNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glPathParameterfvNV(GLuint path, GLenum pname, const GLfloat *value, const char * _file, int _line) {
    glad_glPathParameterfvNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glPathParameterfNV(GLuint path, GLenum pname, GLfloat value, const char * _file, int _line) {
    glad_glPathParameterfNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glPathDashArrayNV(GLuint path, GLsizei dashCount, const GLfloat *dashArray, const char * _file, int _line) {
    glad_glPathDashArrayNV(path, dashCount, dashArray);
    gl_check_error(_file, _line);
}


void _glPathStencilFuncNV(GLenum func, GLint ref, GLuint mask, const char * _file, int _line) {
    glad_glPathStencilFuncNV(func, ref, mask);
    gl_check_error(_file, _line);
}


void _glPathStencilDepthOffsetNV(GLfloat factor, GLfloat units, const char * _file, int _line) {
    glad_glPathStencilDepthOffsetNV(factor, units);
    gl_check_error(_file, _line);
}


void _glStencilFillPathNV(GLuint path, GLenum fillMode, GLuint mask, const char * _file, int _line) {
    glad_glStencilFillPathNV(path, fillMode, mask);
    gl_check_error(_file, _line);
}


void _glStencilStrokePathNV(GLuint path, GLint reference, GLuint mask, const char * _file, int _line) {
    glad_glStencilStrokePathNV(path, reference, mask);
    gl_check_error(_file, _line);
}


void _glStencilFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glStencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glStencilStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glStencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glPathCoverDepthFuncNV(GLenum func, const char * _file, int _line) {
    glad_glPathCoverDepthFuncNV(func);
    gl_check_error(_file, _line);
}


void _glCoverFillPathNV(GLuint path, GLenum coverMode, const char * _file, int _line) {
    glad_glCoverFillPathNV(path, coverMode);
    gl_check_error(_file, _line);
}


void _glCoverStrokePathNV(GLuint path, GLenum coverMode, const char * _file, int _line) {
    glad_glCoverStrokePathNV(path, coverMode);
    gl_check_error(_file, _line);
}


void _glCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glGetPathParameterivNV(GLuint path, GLenum pname, GLint *value, const char * _file, int _line) {
    glad_glGetPathParameterivNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glGetPathParameterfvNV(GLuint path, GLenum pname, GLfloat *value, const char * _file, int _line) {
    glad_glGetPathParameterfvNV(path, pname, value);
    gl_check_error(_file, _line);
}


void _glGetPathCommandsNV(GLuint path, GLubyte *commands, const char * _file, int _line) {
    glad_glGetPathCommandsNV(path, commands);
    gl_check_error(_file, _line);
}


void _glGetPathCoordsNV(GLuint path, GLfloat *coords, const char * _file, int _line) {
    glad_glGetPathCoordsNV(path, coords);
    gl_check_error(_file, _line);
}


void _glGetPathDashArrayNV(GLuint path, GLfloat *dashArray, const char * _file, int _line) {
    glad_glGetPathDashArrayNV(path, dashArray);
    gl_check_error(_file, _line);
}


void _glGetPathMetricsNV(GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics, const char * _file, int _line) {
    glad_glGetPathMetricsNV(metricQueryMask, numPaths, pathNameType, paths, pathBase, stride, metrics);
    gl_check_error(_file, _line);
}


void _glGetPathMetricRangeNV(GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat *metrics, const char * _file, int _line) {
    glad_glGetPathMetricRangeNV(metricQueryMask, firstPathName, numPaths, stride, metrics);
    gl_check_error(_file, _line);
}


void _glGetPathSpacingNV(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing, const char * _file, int _line) {
    glad_glGetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing);
    gl_check_error(_file, _line);
}


GLboolean _glIsPointInFillPathNV(GLuint path, GLuint mask, GLfloat x, GLfloat y, const char * _file, int _line) {
    auto val = glad_glIsPointInFillPathNV(path, mask, x, y);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glIsPointInStrokePathNV(GLuint path, GLfloat x, GLfloat y, const char * _file, int _line) {
    auto val = glad_glIsPointInStrokePathNV(path, x, y);
    gl_check_error(_file, _line);
    return val;
}


GLfloat _glGetPathLengthNV(GLuint path, GLsizei startSegment, GLsizei numSegments, const char * _file, int _line) {
    auto val = glad_glGetPathLengthNV(path, startSegment, numSegments);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glPointAlongPathNV(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY, const char * _file, int _line) {
    auto val = glad_glPointAlongPathNV(path, startSegment, numSegments, distance, x, y, tangentX, tangentY);
    gl_check_error(_file, _line);
    return val;
}


void _glMatrixLoad3x2fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixLoad3x2fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glMatrixLoad3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixLoad3x3fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glMatrixLoadTranspose3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixLoadTranspose3x3fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMult3x2fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixMult3x2fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMult3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixMult3x3fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glMatrixMultTranspose3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line) {
    glad_glMatrixMultTranspose3x3fNV(matrixMode, m);
    gl_check_error(_file, _line);
}


void _glStencilThenCoverFillPathNV(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode, const char * _file, int _line) {
    glad_glStencilThenCoverFillPathNV(path, fillMode, mask, coverMode);
    gl_check_error(_file, _line);
}


void _glStencilThenCoverStrokePathNV(GLuint path, GLint reference, GLuint mask, GLenum coverMode, const char * _file, int _line) {
    glad_glStencilThenCoverStrokePathNV(path, reference, mask, coverMode);
    gl_check_error(_file, _line);
}


void _glStencilThenCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glStencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues);
    gl_check_error(_file, _line);
}


void _glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line) {
    glad_glStencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues);
    gl_check_error(_file, _line);
}


GLenum _glPathGlyphIndexRangeNV(GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2], const char * _file, int _line) {
    auto val = glad_glPathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount);
    gl_check_error(_file, _line);
    return val;
}


GLenum _glPathGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line) {
    auto val = glad_glPathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale);
    gl_check_error(_file, _line);
    return val;
}


GLenum _glPathMemoryGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void *fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line) {
    auto val = glad_glPathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale);
    gl_check_error(_file, _line);
    return val;
}


void _glProgramPathFragmentInputGenNV(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat *coeffs, const char * _file, int _line) {
    glad_glProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs);
    gl_check_error(_file, _line);
}


void _glGetProgramResourcefvNV(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLfloat *params, const char * _file, int _line) {
    glad_glGetProgramResourcefvNV(program, programInterface, index, propCount, props, count, length, params);
    gl_check_error(_file, _line);
}


void _glPathColorGenNV(GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat *coeffs, const char * _file, int _line) {
    glad_glPathColorGenNV(color, genMode, colorFormat, coeffs);
    gl_check_error(_file, _line);
}


void _glPathTexGenNV(GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat *coeffs, const char * _file, int _line) {
    glad_glPathTexGenNV(texCoordSet, genMode, components, coeffs);
    gl_check_error(_file, _line);
}


void _glPathFogGenNV(GLenum genMode, const char * _file, int _line) {
    glad_glPathFogGenNV(genMode);
    gl_check_error(_file, _line);
}


void _glGetPathColorGenivNV(GLenum color, GLenum pname, GLint *value, const char * _file, int _line) {
    glad_glGetPathColorGenivNV(color, pname, value);
    gl_check_error(_file, _line);
}


void _glGetPathColorGenfvNV(GLenum color, GLenum pname, GLfloat *value, const char * _file, int _line) {
    glad_glGetPathColorGenfvNV(color, pname, value);
    gl_check_error(_file, _line);
}


void _glGetPathTexGenivNV(GLenum texCoordSet, GLenum pname, GLint *value, const char * _file, int _line) {
    glad_glGetPathTexGenivNV(texCoordSet, pname, value);
    gl_check_error(_file, _line);
}


void _glGetPathTexGenfvNV(GLenum texCoordSet, GLenum pname, GLfloat *value, const char * _file, int _line) {
    glad_glGetPathTexGenfvNV(texCoordSet, pname, value);
    gl_check_error(_file, _line);
}


void _glPixelDataRangeNV(GLenum target, GLsizei length, const void *pointer, const char * _file, int _line) {
    glad_glPixelDataRangeNV(target, length, pointer);
    gl_check_error(_file, _line);
}


void _glFlushPixelDataRangeNV(GLenum target, const char * _file, int _line) {
    glad_glFlushPixelDataRangeNV(target);
    gl_check_error(_file, _line);
}


void _glPointParameteriNV(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPointParameteriNV(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameterivNV(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glPointParameterivNV(pname, params);
    gl_check_error(_file, _line);
}


void _glPresentFrameKeyedNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1, const char * _file, int _line) {
    glad_glPresentFrameKeyedNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, key0, target1, fill1, key1);
    gl_check_error(_file, _line);
}


void _glPresentFrameDualFillNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3, const char * _file, int _line) {
    glad_glPresentFrameDualFillNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, target1, fill1, target2, fill2, target3, fill3);
    gl_check_error(_file, _line);
}


void _glGetVideoivNV(GLuint video_slot, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVideoivNV(video_slot, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideouivNV(GLuint video_slot, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetVideouivNV(video_slot, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideoi64vNV(GLuint video_slot, GLenum pname, GLint64EXT *params, const char * _file, int _line) {
    glad_glGetVideoi64vNV(video_slot, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideoui64vNV(GLuint video_slot, GLenum pname, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetVideoui64vNV(video_slot, pname, params);
    gl_check_error(_file, _line);
}


void _glPrimitiveRestartNV(const char * _file, int _line) {
    glad_glPrimitiveRestartNV();
    gl_check_error(_file, _line);
}


void _glPrimitiveRestartIndexNV(GLuint index, const char * _file, int _line) {
    glad_glPrimitiveRestartIndexNV(index);
    gl_check_error(_file, _line);
}


GLint _glQueryResourceNV(GLenum queryType, GLint tagId, GLuint count, GLint *buffer, const char * _file, int _line) {
    auto val = glad_glQueryResourceNV(queryType, tagId, count, buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glGenQueryResourceTagNV(GLsizei n, GLint *tagIds, const char * _file, int _line) {
    glad_glGenQueryResourceTagNV(n, tagIds);
    gl_check_error(_file, _line);
}


void _glDeleteQueryResourceTagNV(GLsizei n, const GLint *tagIds, const char * _file, int _line) {
    glad_glDeleteQueryResourceTagNV(n, tagIds);
    gl_check_error(_file, _line);
}


void _glQueryResourceTagNV(GLint tagId, const GLchar *tagString, const char * _file, int _line) {
    glad_glQueryResourceTagNV(tagId, tagString);
    gl_check_error(_file, _line);
}


void _glCombinerParameterfvNV(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glCombinerParameterfvNV(pname, params);
    gl_check_error(_file, _line);
}


void _glCombinerParameterfNV(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glCombinerParameterfNV(pname, param);
    gl_check_error(_file, _line);
}


void _glCombinerParameterivNV(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glCombinerParameterivNV(pname, params);
    gl_check_error(_file, _line);
}


void _glCombinerParameteriNV(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glCombinerParameteriNV(pname, param);
    gl_check_error(_file, _line);
}


void _glCombinerInputNV(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage, const char * _file, int _line) {
    glad_glCombinerInputNV(stage, portion, variable, input, mapping, componentUsage);
    gl_check_error(_file, _line);
}


void _glCombinerOutputNV(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum, const char * _file, int _line) {
    glad_glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum);
    gl_check_error(_file, _line);
}


void _glFinalCombinerInputNV(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage, const char * _file, int _line) {
    glad_glFinalCombinerInputNV(variable, input, mapping, componentUsage);
    gl_check_error(_file, _line);
}


void _glGetCombinerInputParameterfvNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params);
    gl_check_error(_file, _line);
}


void _glGetCombinerInputParameterivNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetCombinerInputParameterivNV(stage, portion, variable, pname, params);
    gl_check_error(_file, _line);
}


void _glGetCombinerOutputParameterfvNV(GLenum stage, GLenum portion, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetCombinerOutputParameterfvNV(stage, portion, pname, params);
    gl_check_error(_file, _line);
}


void _glGetCombinerOutputParameterivNV(GLenum stage, GLenum portion, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetCombinerOutputParameterivNV(stage, portion, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFinalCombinerInputParameterfvNV(GLenum variable, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetFinalCombinerInputParameterfvNV(variable, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFinalCombinerInputParameterivNV(GLenum variable, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFinalCombinerInputParameterivNV(variable, pname, params);
    gl_check_error(_file, _line);
}


void _glCombinerStageParameterfvNV(GLenum stage, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glCombinerStageParameterfvNV(stage, pname, params);
    gl_check_error(_file, _line);
}


void _glGetCombinerStageParameterfvNV(GLenum stage, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetCombinerStageParameterfvNV(stage, pname, params);
    gl_check_error(_file, _line);
}


void _glFramebufferSampleLocationsfvNV(GLenum target, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glFramebufferSampleLocationsfvNV(target, start, count, v);
    gl_check_error(_file, _line);
}


void _glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glNamedFramebufferSampleLocationsfvNV(framebuffer, start, count, v);
    gl_check_error(_file, _line);
}


void _glResolveDepthValuesNV(const char * _file, int _line) {
    glad_glResolveDepthValuesNV();
    gl_check_error(_file, _line);
}


void _glScissorExclusiveNV(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line) {
    glad_glScissorExclusiveNV(x, y, width, height);
    gl_check_error(_file, _line);
}


void _glScissorExclusiveArrayvNV(GLuint first, GLsizei count, const GLint *v, const char * _file, int _line) {
    glad_glScissorExclusiveArrayvNV(first, count, v);
    gl_check_error(_file, _line);
}


void _glMakeBufferResidentNV(GLenum target, GLenum access, const char * _file, int _line) {
    glad_glMakeBufferResidentNV(target, access);
    gl_check_error(_file, _line);
}


void _glMakeBufferNonResidentNV(GLenum target, const char * _file, int _line) {
    glad_glMakeBufferNonResidentNV(target);
    gl_check_error(_file, _line);
}


GLboolean _glIsBufferResidentNV(GLenum target, const char * _file, int _line) {
    auto val = glad_glIsBufferResidentNV(target);
    gl_check_error(_file, _line);
    return val;
}


void _glMakeNamedBufferResidentNV(GLuint buffer, GLenum access, const char * _file, int _line) {
    glad_glMakeNamedBufferResidentNV(buffer, access);
    gl_check_error(_file, _line);
}


void _glMakeNamedBufferNonResidentNV(GLuint buffer, const char * _file, int _line) {
    glad_glMakeNamedBufferNonResidentNV(buffer);
    gl_check_error(_file, _line);
}


GLboolean _glIsNamedBufferResidentNV(GLuint buffer, const char * _file, int _line) {
    auto val = glad_glIsNamedBufferResidentNV(buffer);
    gl_check_error(_file, _line);
    return val;
}


void _glGetBufferParameterui64vNV(GLenum target, GLenum pname, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetBufferParameterui64vNV(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetNamedBufferParameterui64vNV(GLuint buffer, GLenum pname, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetNamedBufferParameterui64vNV(buffer, pname, params);
    gl_check_error(_file, _line);
}


void _glGetIntegerui64vNV(GLenum value, GLuint64EXT *result, const char * _file, int _line) {
    glad_glGetIntegerui64vNV(value, result);
    gl_check_error(_file, _line);
}


void _glUniformui64NV(GLint location, GLuint64EXT value, const char * _file, int _line) {
    glad_glUniformui64NV(location, value);
    gl_check_error(_file, _line);
}


void _glUniformui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glUniformui64vNV(location, count, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformui64NV(GLuint program, GLint location, GLuint64EXT value, const char * _file, int _line) {
    glad_glProgramUniformui64NV(program, location, value);
    gl_check_error(_file, _line);
}


void _glProgramUniformui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line) {
    glad_glProgramUniformui64vNV(program, location, count, value);
    gl_check_error(_file, _line);
}


void _glBindShadingRateImageNV(GLuint texture, const char * _file, int _line) {
    glad_glBindShadingRateImageNV(texture);
    gl_check_error(_file, _line);
}


void _glGetShadingRateImagePaletteNV(GLuint viewport, GLuint entry, GLenum *rate, const char * _file, int _line) {
    glad_glGetShadingRateImagePaletteNV(viewport, entry, rate);
    gl_check_error(_file, _line);
}


void _glGetShadingRateSampleLocationivNV(GLenum rate, GLuint samples, GLuint index, GLint *location, const char * _file, int _line) {
    glad_glGetShadingRateSampleLocationivNV(rate, samples, index, location);
    gl_check_error(_file, _line);
}


void _glShadingRateImageBarrierNV(GLboolean synchronize, const char * _file, int _line) {
    glad_glShadingRateImageBarrierNV(synchronize);
    gl_check_error(_file, _line);
}


void _glShadingRateImagePaletteNV(GLuint viewport, GLuint first, GLsizei count, const GLenum *rates, const char * _file, int _line) {
    glad_glShadingRateImagePaletteNV(viewport, first, count, rates);
    gl_check_error(_file, _line);
}


void _glShadingRateSampleOrderNV(GLenum order, const char * _file, int _line) {
    glad_glShadingRateSampleOrderNV(order);
    gl_check_error(_file, _line);
}


void _glShadingRateSampleOrderCustomNV(GLenum rate, GLuint samples, const GLint *locations, const char * _file, int _line) {
    glad_glShadingRateSampleOrderCustomNV(rate, samples, locations);
    gl_check_error(_file, _line);
}


void _glTextureBarrierNV(const char * _file, int _line) {
    glad_glTextureBarrierNV();
    gl_check_error(_file, _line);
}


void _glTexImage2DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTexImage2DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glTexImage3DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTexImage3DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glTextureImage2DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glTextureImage3DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glTextureImage2DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTextureImage2DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glTextureImage3DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line) {
    glad_glTextureImage3DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations);
    gl_check_error(_file, _line);
}


void _glCreateSemaphoresNV(GLsizei n, GLuint *semaphores, const char * _file, int _line) {
    glad_glCreateSemaphoresNV(n, semaphores);
    gl_check_error(_file, _line);
}


void _glSemaphoreParameterivNV(GLuint semaphore, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glSemaphoreParameterivNV(semaphore, pname, params);
    gl_check_error(_file, _line);
}


void _glGetSemaphoreParameterivNV(GLuint semaphore, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetSemaphoreParameterivNV(semaphore, pname, params);
    gl_check_error(_file, _line);
}


void _glBeginTransformFeedbackNV(GLenum primitiveMode, const char * _file, int _line) {
    glad_glBeginTransformFeedbackNV(primitiveMode);
    gl_check_error(_file, _line);
}


void _glEndTransformFeedbackNV(const char * _file, int _line) {
    glad_glEndTransformFeedbackNV();
    gl_check_error(_file, _line);
}


void _glTransformFeedbackAttribsNV(GLsizei count, const GLint *attribs, GLenum bufferMode, const char * _file, int _line) {
    glad_glTransformFeedbackAttribsNV(count, attribs, bufferMode);
    gl_check_error(_file, _line);
}


void _glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line) {
    glad_glBindBufferRangeNV(target, index, buffer, offset, size);
    gl_check_error(_file, _line);
}


void _glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, const char * _file, int _line) {
    glad_glBindBufferOffsetNV(target, index, buffer, offset);
    gl_check_error(_file, _line);
}


void _glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line) {
    glad_glBindBufferBaseNV(target, index, buffer);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackVaryingsNV(GLuint program, GLsizei count, const GLint *locations, GLenum bufferMode, const char * _file, int _line) {
    glad_glTransformFeedbackVaryingsNV(program, count, locations, bufferMode);
    gl_check_error(_file, _line);
}


void _glActiveVaryingNV(GLuint program, const GLchar *name, const char * _file, int _line) {
    glad_glActiveVaryingNV(program, name);
    gl_check_error(_file, _line);
}


GLint _glGetVaryingLocationNV(GLuint program, const GLchar *name, const char * _file, int _line) {
    auto val = glad_glGetVaryingLocationNV(program, name);
    gl_check_error(_file, _line);
    return val;
}


void _glGetActiveVaryingNV(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line) {
    glad_glGetActiveVaryingNV(program, index, bufSize, length, size, type, name);
    gl_check_error(_file, _line);
}


void _glGetTransformFeedbackVaryingNV(GLuint program, GLuint index, GLint *location, const char * _file, int _line) {
    glad_glGetTransformFeedbackVaryingNV(program, index, location);
    gl_check_error(_file, _line);
}


void _glTransformFeedbackStreamAttribsNV(GLsizei count, const GLint *attribs, GLsizei nbuffers, const GLint *bufstreams, GLenum bufferMode, const char * _file, int _line) {
    glad_glTransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode);
    gl_check_error(_file, _line);
}


void _glBindTransformFeedbackNV(GLenum target, GLuint id, const char * _file, int _line) {
    glad_glBindTransformFeedbackNV(target, id);
    gl_check_error(_file, _line);
}


void _glDeleteTransformFeedbacksNV(GLsizei n, const GLuint *ids, const char * _file, int _line) {
    glad_glDeleteTransformFeedbacksNV(n, ids);
    gl_check_error(_file, _line);
}


void _glGenTransformFeedbacksNV(GLsizei n, GLuint *ids, const char * _file, int _line) {
    glad_glGenTransformFeedbacksNV(n, ids);
    gl_check_error(_file, _line);
}


GLboolean _glIsTransformFeedbackNV(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsTransformFeedbackNV(id);
    gl_check_error(_file, _line);
    return val;
}


void _glPauseTransformFeedbackNV(const char * _file, int _line) {
    glad_glPauseTransformFeedbackNV();
    gl_check_error(_file, _line);
}


void _glResumeTransformFeedbackNV(const char * _file, int _line) {
    glad_glResumeTransformFeedbackNV();
    gl_check_error(_file, _line);
}


void _glDrawTransformFeedbackNV(GLenum mode, GLuint id, const char * _file, int _line) {
    glad_glDrawTransformFeedbackNV(mode, id);
    gl_check_error(_file, _line);
}


void _glVDPAUInitNV(const void *vdpDevice, const void *getProcAddress, const char * _file, int _line) {
    glad_glVDPAUInitNV(vdpDevice, getProcAddress);
    gl_check_error(_file, _line);
}


void _glVDPAUFiniNV(const char * _file, int _line) {
    glad_glVDPAUFiniNV();
    gl_check_error(_file, _line);
}


GLvdpauSurfaceNV _glVDPAURegisterVideoSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, const char * _file, int _line) {
    auto val = glad_glVDPAURegisterVideoSurfaceNV(vdpSurface, target, numTextureNames, textureNames);
    gl_check_error(_file, _line);
    return val;
}


GLvdpauSurfaceNV _glVDPAURegisterOutputSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, const char * _file, int _line) {
    auto val = glad_glVDPAURegisterOutputSurfaceNV(vdpSurface, target, numTextureNames, textureNames);
    gl_check_error(_file, _line);
    return val;
}


GLboolean _glVDPAUIsSurfaceNV(GLvdpauSurfaceNV surface, const char * _file, int _line) {
    auto val = glad_glVDPAUIsSurfaceNV(surface);
    gl_check_error(_file, _line);
    return val;
}


void _glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV surface, const char * _file, int _line) {
    glad_glVDPAUUnregisterSurfaceNV(surface);
    gl_check_error(_file, _line);
}


void _glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei count, GLsizei *length, GLint *values, const char * _file, int _line) {
    glad_glVDPAUGetSurfaceivNV(surface, pname, count, length, values);
    gl_check_error(_file, _line);
}


void _glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV surface, GLenum access, const char * _file, int _line) {
    glad_glVDPAUSurfaceAccessNV(surface, access);
    gl_check_error(_file, _line);
}


void _glVDPAUMapSurfacesNV(GLsizei numSurfaces, const GLvdpauSurfaceNV *surfaces, const char * _file, int _line) {
    glad_glVDPAUMapSurfacesNV(numSurfaces, surfaces);
    gl_check_error(_file, _line);
}


void _glVDPAUUnmapSurfacesNV(GLsizei numSurface, const GLvdpauSurfaceNV *surfaces, const char * _file, int _line) {
    glad_glVDPAUUnmapSurfacesNV(numSurface, surfaces);
    gl_check_error(_file, _line);
}


GLvdpauSurfaceNV _glVDPAURegisterVideoSurfaceWithPictureStructureNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, GLboolean isFrameStructure, const char * _file, int _line) {
    auto val = glad_glVDPAURegisterVideoSurfaceWithPictureStructureNV(vdpSurface, target, numTextureNames, textureNames, isFrameStructure);
    gl_check_error(_file, _line);
    return val;
}


void _glFlushVertexArrayRangeNV(const char * _file, int _line) {
    glad_glFlushVertexArrayRangeNV();
    gl_check_error(_file, _line);
}


void _glVertexArrayRangeNV(GLsizei length, const void *pointer, const char * _file, int _line) {
    glad_glVertexArrayRangeNV(length, pointer);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1i64NV(GLuint index, GLint64EXT x, const char * _file, int _line) {
    glad_glVertexAttribL1i64NV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2i64NV(GLuint index, GLint64EXT x, GLint64EXT y, const char * _file, int _line) {
    glad_glVertexAttribL2i64NV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line) {
    glad_glVertexAttribL3i64NV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line) {
    glad_glVertexAttribL4i64NV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL1i64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL2i64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL3i64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL4i64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1ui64NV(GLuint index, GLuint64EXT x, const char * _file, int _line) {
    glad_glVertexAttribL1ui64NV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line) {
    glad_glVertexAttribL2ui64NV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line) {
    glad_glVertexAttribL3ui64NV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line) {
    glad_glVertexAttribL4ui64NV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribL1ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL1ui64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL2ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL2ui64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL3ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL3ui64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribL4ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line) {
    glad_glVertexAttribL4ui64vNV(index, v);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribLi64vNV(GLuint index, GLenum pname, GLint64EXT *params, const char * _file, int _line) {
    glad_glGetVertexAttribLi64vNV(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribLui64vNV(GLuint index, GLenum pname, GLuint64EXT *params, const char * _file, int _line) {
    glad_glGetVertexAttribLui64vNV(index, pname, params);
    gl_check_error(_file, _line);
}


void _glVertexAttribLFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glVertexAttribLFormatNV(index, size, type, stride);
    gl_check_error(_file, _line);
}


void _glBufferAddressRangeNV(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length, const char * _file, int _line) {
    glad_glBufferAddressRangeNV(pname, index, address, length);
    gl_check_error(_file, _line);
}


void _glVertexFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glVertexFormatNV(size, type, stride);
    gl_check_error(_file, _line);
}


void _glNormalFormatNV(GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glNormalFormatNV(type, stride);
    gl_check_error(_file, _line);
}


void _glColorFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glColorFormatNV(size, type, stride);
    gl_check_error(_file, _line);
}


void _glIndexFormatNV(GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glIndexFormatNV(type, stride);
    gl_check_error(_file, _line);
}


void _glTexCoordFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glTexCoordFormatNV(size, type, stride);
    gl_check_error(_file, _line);
}


void _glEdgeFlagFormatNV(GLsizei stride, const char * _file, int _line) {
    glad_glEdgeFlagFormatNV(stride);
    gl_check_error(_file, _line);
}


void _glSecondaryColorFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glSecondaryColorFormatNV(size, type, stride);
    gl_check_error(_file, _line);
}


void _glFogCoordFormatNV(GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glFogCoordFormatNV(type, stride);
    gl_check_error(_file, _line);
}


void _glVertexAttribFormatNV(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const char * _file, int _line) {
    glad_glVertexAttribFormatNV(index, size, type, normalized, stride);
    gl_check_error(_file, _line);
}


void _glVertexAttribIFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride, const char * _file, int _line) {
    glad_glVertexAttribIFormatNV(index, size, type, stride);
    gl_check_error(_file, _line);
}


void _glGetIntegerui64i_vNV(GLenum value, GLuint index, GLuint64EXT *result, const char * _file, int _line) {
    glad_glGetIntegerui64i_vNV(value, index, result);
    gl_check_error(_file, _line);
}


GLboolean _glAreProgramsResidentNV(GLsizei n, const GLuint *programs, GLboolean *residences, const char * _file, int _line) {
    auto val = glad_glAreProgramsResidentNV(n, programs, residences);
    gl_check_error(_file, _line);
    return val;
}


void _glBindProgramNV(GLenum target, GLuint id, const char * _file, int _line) {
    glad_glBindProgramNV(target, id);
    gl_check_error(_file, _line);
}


void _glDeleteProgramsNV(GLsizei n, const GLuint *programs, const char * _file, int _line) {
    glad_glDeleteProgramsNV(n, programs);
    gl_check_error(_file, _line);
}


void _glExecuteProgramNV(GLenum target, GLuint id, const GLfloat *params, const char * _file, int _line) {
    glad_glExecuteProgramNV(target, id, params);
    gl_check_error(_file, _line);
}


void _glGenProgramsNV(GLsizei n, GLuint *programs, const char * _file, int _line) {
    glad_glGenProgramsNV(n, programs);
    gl_check_error(_file, _line);
}


void _glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetProgramParameterdvNV(target, index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetProgramParameterfvNV(target, index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetProgramivNV(GLuint id, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetProgramivNV(id, pname, params);
    gl_check_error(_file, _line);
}


void _glGetProgramStringNV(GLuint id, GLenum pname, GLubyte *program, const char * _file, int _line) {
    glad_glGetProgramStringNV(id, pname, program);
    gl_check_error(_file, _line);
}


void _glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetTrackMatrixivNV(target, address, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVertexAttribdvNV(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVertexAttribfvNV(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribivNV(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribivNV(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribPointervNV(GLuint index, GLenum pname, void **pointer, const char * _file, int _line) {
    glad_glGetVertexAttribPointervNV(index, pname, pointer);
    gl_check_error(_file, _line);
}


GLboolean _glIsProgramNV(GLuint id, const char * _file, int _line) {
    auto val = glad_glIsProgramNV(id);
    gl_check_error(_file, _line);
    return val;
}


void _glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte *program, const char * _file, int _line) {
    glad_glLoadProgramNV(target, id, len, program);
    gl_check_error(_file, _line);
}


void _glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glProgramParameter4dNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glProgramParameter4dvNV(target, index, v);
    gl_check_error(_file, _line);
}


void _glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glProgramParameter4fNV(target, index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glProgramParameter4fvNV(target, index, v);
    gl_check_error(_file, _line);
}


void _glProgramParameters4dvNV(GLenum target, GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glProgramParameters4dvNV(target, index, count, v);
    gl_check_error(_file, _line);
}


void _glProgramParameters4fvNV(GLenum target, GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glProgramParameters4fvNV(target, index, count, v);
    gl_check_error(_file, _line);
}


void _glRequestResidentProgramsNV(GLsizei n, const GLuint *programs, const char * _file, int _line) {
    glad_glRequestResidentProgramsNV(n, programs);
    gl_check_error(_file, _line);
}


void _glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform, const char * _file, int _line) {
    glad_glTrackMatrixNV(target, address, matrix, transform);
    gl_check_error(_file, _line);
}


void _glVertexAttribPointerNV(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribPointerNV(index, fsize, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1dNV(GLuint index, GLdouble x, const char * _file, int _line) {
    glad_glVertexAttrib1dNV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1dvNV(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib1dvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1fNV(GLuint index, GLfloat x, const char * _file, int _line) {
    glad_glVertexAttrib1fNV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1fvNV(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib1fvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1sNV(GLuint index, GLshort x, const char * _file, int _line) {
    glad_glVertexAttrib1sNV(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttrib1svNV(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib1svNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line) {
    glad_glVertexAttrib2dNV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2dvNV(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib2dvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glVertexAttrib2fNV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2fvNV(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib2fvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y, const char * _file, int _line) {
    glad_glVertexAttrib2sNV(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttrib2svNV(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib2svNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line) {
    glad_glVertexAttrib3dNV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3dvNV(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib3dvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glVertexAttrib3fNV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3fvNV(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib3fvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line) {
    glad_glVertexAttrib3sNV(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttrib3svNV(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib3svNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line) {
    glad_glVertexAttrib4dNV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4dvNV(GLuint index, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttrib4dvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glVertexAttrib4fNV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4fvNV(GLuint index, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttrib4fvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line) {
    glad_glVertexAttrib4sNV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4svNV(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttrib4svNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line) {
    glad_glVertexAttrib4ubNV(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttrib4ubvNV(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttrib4ubvNV(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs1dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribs1dvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs1fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttribs1fvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs1svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribs1svNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs2dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribs2dvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs2fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttribs2fvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs2svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribs2svNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs3dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribs3dvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs3fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttribs3fvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs3svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribs3svNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs4dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line) {
    glad_glVertexAttribs4dvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs4fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line) {
    glad_glVertexAttribs4fvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs4svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribs4svNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribs4ubvNV(GLuint index, GLsizei count, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttribs4ubvNV(index, count, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1iEXT(GLuint index, GLint x, const char * _file, int _line) {
    glad_glVertexAttribI1iEXT(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2iEXT(GLuint index, GLint x, GLint y, const char * _file, int _line) {
    glad_glVertexAttribI2iEXT(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3iEXT(GLuint index, GLint x, GLint y, GLint z, const char * _file, int _line) {
    glad_glVertexAttribI3iEXT(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4iEXT(GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line) {
    glad_glVertexAttribI4iEXT(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1uiEXT(GLuint index, GLuint x, const char * _file, int _line) {
    glad_glVertexAttribI1uiEXT(index, x);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2uiEXT(GLuint index, GLuint x, GLuint y, const char * _file, int _line) {
    glad_glVertexAttribI2uiEXT(index, x, y);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, const char * _file, int _line) {
    glad_glVertexAttribI3uiEXT(index, x, y, z);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line) {
    glad_glVertexAttribI4uiEXT(index, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1ivEXT(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI1ivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2ivEXT(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI2ivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3ivEXT(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI3ivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4ivEXT(GLuint index, const GLint *v, const char * _file, int _line) {
    glad_glVertexAttribI4ivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI1uivEXT(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI1uivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI2uivEXT(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI2uivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI3uivEXT(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI3uivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4uivEXT(GLuint index, const GLuint *v, const char * _file, int _line) {
    glad_glVertexAttribI4uivEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4bvEXT(GLuint index, const GLbyte *v, const char * _file, int _line) {
    glad_glVertexAttribI4bvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4svEXT(GLuint index, const GLshort *v, const char * _file, int _line) {
    glad_glVertexAttribI4svEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4ubvEXT(GLuint index, const GLubyte *v, const char * _file, int _line) {
    glad_glVertexAttribI4ubvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribI4usvEXT(GLuint index, const GLushort *v, const char * _file, int _line) {
    glad_glVertexAttribI4usvEXT(index, v);
    gl_check_error(_file, _line);
}


void _glVertexAttribIPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line) {
    glad_glVertexAttribIPointerEXT(index, size, type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribIivEXT(GLuint index, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVertexAttribIivEXT(index, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVertexAttribIuivEXT(GLuint index, GLenum pname, GLuint *params, const char * _file, int _line) {
    glad_glGetVertexAttribIuivEXT(index, pname, params);
    gl_check_error(_file, _line);
}


void _glBeginVideoCaptureNV(GLuint video_capture_slot, const char * _file, int _line) {
    glad_glBeginVideoCaptureNV(video_capture_slot);
    gl_check_error(_file, _line);
}


void _glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset, const char * _file, int _line) {
    glad_glBindVideoCaptureStreamBufferNV(video_capture_slot, stream, frame_region, offset);
    gl_check_error(_file, _line);
}


void _glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture, const char * _file, int _line) {
    glad_glBindVideoCaptureStreamTextureNV(video_capture_slot, stream, frame_region, target, texture);
    gl_check_error(_file, _line);
}


void _glEndVideoCaptureNV(GLuint video_capture_slot, const char * _file, int _line) {
    glad_glEndVideoCaptureNV(video_capture_slot);
    gl_check_error(_file, _line);
}


void _glGetVideoCaptureivNV(GLuint video_capture_slot, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVideoCaptureivNV(video_capture_slot, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideoCaptureStreamivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetVideoCaptureStreamivNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideoCaptureStreamfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetVideoCaptureStreamfvNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


void _glGetVideoCaptureStreamdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble *params, const char * _file, int _line) {
    glad_glGetVideoCaptureStreamdvNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


GLenum _glVideoCaptureNV(GLuint video_capture_slot, GLuint *sequence_num, GLuint64EXT *capture_time, const char * _file, int _line) {
    auto val = glad_glVideoCaptureNV(video_capture_slot, sequence_num, capture_time);
    gl_check_error(_file, _line);
    return val;
}


void _glVideoCaptureStreamParameterivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glVideoCaptureStreamParameterivNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


void _glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glVideoCaptureStreamParameterfvNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


void _glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble *params, const char * _file, int _line) {
    glad_glVideoCaptureStreamParameterdvNV(video_capture_slot, stream, pname, params);
    gl_check_error(_file, _line);
}


void _glViewportSwizzleNV(GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew, const char * _file, int _line) {
    glad_glViewportSwizzleNV(index, swizzlex, swizzley, swizzlez, swizzlew);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1bOES(GLenum texture, GLbyte s, const char * _file, int _line) {
    glad_glMultiTexCoord1bOES(texture, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line) {
    glad_glMultiTexCoord1bvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2bOES(GLenum texture, GLbyte s, GLbyte t, const char * _file, int _line) {
    glad_glMultiTexCoord2bOES(texture, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line) {
    glad_glMultiTexCoord2bvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, const char * _file, int _line) {
    glad_glMultiTexCoord3bOES(texture, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line) {
    glad_glMultiTexCoord3bvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, GLbyte q, const char * _file, int _line) {
    glad_glMultiTexCoord4bOES(texture, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line) {
    glad_glMultiTexCoord4bvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glTexCoord1bOES(GLbyte s, const char * _file, int _line) {
    glad_glTexCoord1bOES(s);
    gl_check_error(_file, _line);
}


void _glTexCoord1bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glTexCoord1bvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord2bOES(GLbyte s, GLbyte t, const char * _file, int _line) {
    glad_glTexCoord2bOES(s, t);
    gl_check_error(_file, _line);
}


void _glTexCoord2bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glTexCoord2bvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord3bOES(GLbyte s, GLbyte t, GLbyte r, const char * _file, int _line) {
    glad_glTexCoord3bOES(s, t, r);
    gl_check_error(_file, _line);
}


void _glTexCoord3bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glTexCoord3bvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord4bOES(GLbyte s, GLbyte t, GLbyte r, GLbyte q, const char * _file, int _line) {
    glad_glTexCoord4bOES(s, t, r, q);
    gl_check_error(_file, _line);
}


void _glTexCoord4bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glTexCoord4bvOES(coords);
    gl_check_error(_file, _line);
}


void _glVertex2bOES(GLbyte x, GLbyte y, const char * _file, int _line) {
    glad_glVertex2bOES(x, y);
    gl_check_error(_file, _line);
}


void _glVertex2bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glVertex2bvOES(coords);
    gl_check_error(_file, _line);
}


void _glVertex3bOES(GLbyte x, GLbyte y, GLbyte z, const char * _file, int _line) {
    glad_glVertex3bOES(x, y, z);
    gl_check_error(_file, _line);
}


void _glVertex3bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glVertex3bvOES(coords);
    gl_check_error(_file, _line);
}


void _glVertex4bOES(GLbyte x, GLbyte y, GLbyte z, GLbyte w, const char * _file, int _line) {
    glad_glVertex4bOES(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glVertex4bvOES(const GLbyte *coords, const char * _file, int _line) {
    glad_glVertex4bvOES(coords);
    gl_check_error(_file, _line);
}


void _glAlphaFuncxOES(GLenum func, GLfixed ref, const char * _file, int _line) {
    glad_glAlphaFuncxOES(func, ref);
    gl_check_error(_file, _line);
}


void _glClearColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line) {
    glad_glClearColorxOES(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glClearDepthxOES(GLfixed depth, const char * _file, int _line) {
    glad_glClearDepthxOES(depth);
    gl_check_error(_file, _line);
}


void _glClipPlanexOES(GLenum plane, const GLfixed *equation, const char * _file, int _line) {
    glad_glClipPlanexOES(plane, equation);
    gl_check_error(_file, _line);
}


void _glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line) {
    glad_glColor4xOES(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glDepthRangexOES(GLfixed n, GLfixed f, const char * _file, int _line) {
    glad_glDepthRangexOES(n, f);
    gl_check_error(_file, _line);
}


void _glFogxOES(GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glFogxOES(pname, param);
    gl_check_error(_file, _line);
}


void _glFogxvOES(GLenum pname, const GLfixed *param, const char * _file, int _line) {
    glad_glFogxvOES(pname, param);
    gl_check_error(_file, _line);
}


void _glFrustumxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f, const char * _file, int _line) {
    glad_glFrustumxOES(l, r, b, t, n, f);
    gl_check_error(_file, _line);
}


void _glGetClipPlanexOES(GLenum plane, GLfixed *equation, const char * _file, int _line) {
    glad_glGetClipPlanexOES(plane, equation);
    gl_check_error(_file, _line);
}


void _glGetFixedvOES(GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetFixedvOES(pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetTexEnvxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetTexParameterxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glLightModelxOES(GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glLightModelxOES(pname, param);
    gl_check_error(_file, _line);
}


void _glLightModelxvOES(GLenum pname, const GLfixed *param, const char * _file, int _line) {
    glad_glLightModelxvOES(pname, param);
    gl_check_error(_file, _line);
}


void _glLightxOES(GLenum light, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glLightxOES(light, pname, param);
    gl_check_error(_file, _line);
}


void _glLightxvOES(GLenum light, GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glLightxvOES(light, pname, params);
    gl_check_error(_file, _line);
}


void _glLineWidthxOES(GLfixed width, const char * _file, int _line) {
    glad_glLineWidthxOES(width);
    gl_check_error(_file, _line);
}


void _glLoadMatrixxOES(const GLfixed *m, const char * _file, int _line) {
    glad_glLoadMatrixxOES(m);
    gl_check_error(_file, _line);
}


void _glMaterialxOES(GLenum face, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glMaterialxOES(face, pname, param);
    gl_check_error(_file, _line);
}


void _glMaterialxvOES(GLenum face, GLenum pname, const GLfixed *param, const char * _file, int _line) {
    glad_glMaterialxvOES(face, pname, param);
    gl_check_error(_file, _line);
}


void _glMultMatrixxOES(const GLfixed *m, const char * _file, int _line) {
    glad_glMultMatrixxOES(m);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q, const char * _file, int _line) {
    glad_glMultiTexCoord4xOES(texture, s, t, r, q);
    gl_check_error(_file, _line);
}


void _glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz, const char * _file, int _line) {
    glad_glNormal3xOES(nx, ny, nz);
    gl_check_error(_file, _line);
}


void _glOrthoxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f, const char * _file, int _line) {
    glad_glOrthoxOES(l, r, b, t, n, f);
    gl_check_error(_file, _line);
}


void _glPointParameterxvOES(GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glPointParameterxvOES(pname, params);
    gl_check_error(_file, _line);
}


void _glPointSizexOES(GLfixed size, const char * _file, int _line) {
    glad_glPointSizexOES(size);
    gl_check_error(_file, _line);
}


void _glPolygonOffsetxOES(GLfixed factor, GLfixed units, const char * _file, int _line) {
    glad_glPolygonOffsetxOES(factor, units);
    gl_check_error(_file, _line);
}


void _glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line) {
    glad_glRotatexOES(angle, x, y, z);
    gl_check_error(_file, _line);
}


void _glScalexOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line) {
    glad_glScalexOES(x, y, z);
    gl_check_error(_file, _line);
}


void _glTexEnvxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glTexEnvxOES(target, pname, param);
    gl_check_error(_file, _line);
}


void _glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glTexEnvxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTexParameterxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glTexParameterxOES(target, pname, param);
    gl_check_error(_file, _line);
}


void _glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glTexParameterxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glTranslatexOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line) {
    glad_glTranslatexOES(x, y, z);
    gl_check_error(_file, _line);
}


void _glGetLightxvOES(GLenum light, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetLightxvOES(light, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMaterialxvOES(GLenum face, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetMaterialxvOES(face, pname, params);
    gl_check_error(_file, _line);
}


void _glPointParameterxOES(GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glPointParameterxOES(pname, param);
    gl_check_error(_file, _line);
}


void _glSampleCoveragexOES(GLclampx value, GLboolean invert, const char * _file, int _line) {
    glad_glSampleCoveragexOES(value, invert);
    gl_check_error(_file, _line);
}


void _glAccumxOES(GLenum op, GLfixed value, const char * _file, int _line) {
    glad_glAccumxOES(op, value);
    gl_check_error(_file, _line);
}


void _glBitmapxOES(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig, GLfixed xmove, GLfixed ymove, const GLubyte *bitmap, const char * _file, int _line) {
    glad_glBitmapxOES(width, height, xorig, yorig, xmove, ymove, bitmap);
    gl_check_error(_file, _line);
}


void _glBlendColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line) {
    glad_glBlendColorxOES(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glClearAccumxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line) {
    glad_glClearAccumxOES(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glColor3xOES(GLfixed red, GLfixed green, GLfixed blue, const char * _file, int _line) {
    glad_glColor3xOES(red, green, blue);
    gl_check_error(_file, _line);
}


void _glColor3xvOES(const GLfixed *components, const char * _file, int _line) {
    glad_glColor3xvOES(components);
    gl_check_error(_file, _line);
}


void _glColor4xvOES(const GLfixed *components, const char * _file, int _line) {
    glad_glColor4xvOES(components);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glConvolutionParameterxOES(target, pname, param);
    gl_check_error(_file, _line);
}


void _glConvolutionParameterxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glConvolutionParameterxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glEvalCoord1xOES(GLfixed u, const char * _file, int _line) {
    glad_glEvalCoord1xOES(u);
    gl_check_error(_file, _line);
}


void _glEvalCoord1xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glEvalCoord1xvOES(coords);
    gl_check_error(_file, _line);
}


void _glEvalCoord2xOES(GLfixed u, GLfixed v, const char * _file, int _line) {
    glad_glEvalCoord2xOES(u, v);
    gl_check_error(_file, _line);
}


void _glEvalCoord2xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glEvalCoord2xvOES(coords);
    gl_check_error(_file, _line);
}


void _glFeedbackBufferxOES(GLsizei n, GLenum type, const GLfixed *buffer, const char * _file, int _line) {
    glad_glFeedbackBufferxOES(n, type, buffer);
    gl_check_error(_file, _line);
}


void _glGetConvolutionParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetConvolutionParameterxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetHistogramParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetHistogramParameterxvOES(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetLightxOES(GLenum light, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetLightxOES(light, pname, params);
    gl_check_error(_file, _line);
}


void _glGetMapxvOES(GLenum target, GLenum query, GLfixed *v, const char * _file, int _line) {
    glad_glGetMapxvOES(target, query, v);
    gl_check_error(_file, _line);
}


void _glGetMaterialxOES(GLenum face, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glGetMaterialxOES(face, pname, param);
    gl_check_error(_file, _line);
}


void _glGetPixelMapxv(GLenum map, GLint size, GLfixed *values, const char * _file, int _line) {
    glad_glGetPixelMapxv(map, size, values);
    gl_check_error(_file, _line);
}


void _glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetTexGenxvOES(coord, pname, params);
    gl_check_error(_file, _line);
}


void _glGetTexLevelParameterxvOES(GLenum target, GLint level, GLenum pname, GLfixed *params, const char * _file, int _line) {
    glad_glGetTexLevelParameterxvOES(target, level, pname, params);
    gl_check_error(_file, _line);
}


void _glIndexxOES(GLfixed component, const char * _file, int _line) {
    glad_glIndexxOES(component);
    gl_check_error(_file, _line);
}


void _glIndexxvOES(const GLfixed *component, const char * _file, int _line) {
    glad_glIndexxvOES(component);
    gl_check_error(_file, _line);
}


void _glLoadTransposeMatrixxOES(const GLfixed *m, const char * _file, int _line) {
    glad_glLoadTransposeMatrixxOES(m);
    gl_check_error(_file, _line);
}


void _glMap1xOES(GLenum target, GLfixed u1, GLfixed u2, GLint stride, GLint order, GLfixed points, const char * _file, int _line) {
    glad_glMap1xOES(target, u1, u2, stride, order, points);
    gl_check_error(_file, _line);
}


void _glMap2xOES(GLenum target, GLfixed u1, GLfixed u2, GLint ustride, GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder, GLfixed points, const char * _file, int _line) {
    glad_glMap2xOES(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
    gl_check_error(_file, _line);
}


void _glMapGrid1xOES(GLint n, GLfixed u1, GLfixed u2, const char * _file, int _line) {
    glad_glMapGrid1xOES(n, u1, u2);
    gl_check_error(_file, _line);
}


void _glMapGrid2xOES(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2, const char * _file, int _line) {
    glad_glMapGrid2xOES(n, u1, u2, v1, v2);
    gl_check_error(_file, _line);
}


void _glMultTransposeMatrixxOES(const GLfixed *m, const char * _file, int _line) {
    glad_glMultTransposeMatrixxOES(m);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1xOES(GLenum texture, GLfixed s, const char * _file, int _line) {
    glad_glMultiTexCoord1xOES(texture, s);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord1xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line) {
    glad_glMultiTexCoord1xvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2xOES(GLenum texture, GLfixed s, GLfixed t, const char * _file, int _line) {
    glad_glMultiTexCoord2xOES(texture, s, t);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord2xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line) {
    glad_glMultiTexCoord2xvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, const char * _file, int _line) {
    glad_glMultiTexCoord3xOES(texture, s, t, r);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord3xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line) {
    glad_glMultiTexCoord3xvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glMultiTexCoord4xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line) {
    glad_glMultiTexCoord4xvOES(texture, coords);
    gl_check_error(_file, _line);
}


void _glNormal3xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glNormal3xvOES(coords);
    gl_check_error(_file, _line);
}


void _glPassThroughxOES(GLfixed token, const char * _file, int _line) {
    glad_glPassThroughxOES(token);
    gl_check_error(_file, _line);
}


void _glPixelMapx(GLenum map, GLint size, const GLfixed *values, const char * _file, int _line) {
    glad_glPixelMapx(map, size, values);
    gl_check_error(_file, _line);
}


void _glPixelStorex(GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glPixelStorex(pname, param);
    gl_check_error(_file, _line);
}


void _glPixelTransferxOES(GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glPixelTransferxOES(pname, param);
    gl_check_error(_file, _line);
}


void _glPixelZoomxOES(GLfixed xfactor, GLfixed yfactor, const char * _file, int _line) {
    glad_glPixelZoomxOES(xfactor, yfactor);
    gl_check_error(_file, _line);
}


void _glPrioritizeTexturesxOES(GLsizei n, const GLuint *textures, const GLfixed *priorities, const char * _file, int _line) {
    glad_glPrioritizeTexturesxOES(n, textures, priorities);
    gl_check_error(_file, _line);
}


void _glRasterPos2xOES(GLfixed x, GLfixed y, const char * _file, int _line) {
    glad_glRasterPos2xOES(x, y);
    gl_check_error(_file, _line);
}


void _glRasterPos2xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glRasterPos2xvOES(coords);
    gl_check_error(_file, _line);
}


void _glRasterPos3xOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line) {
    glad_glRasterPos3xOES(x, y, z);
    gl_check_error(_file, _line);
}


void _glRasterPos3xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glRasterPos3xvOES(coords);
    gl_check_error(_file, _line);
}


void _glRasterPos4xOES(GLfixed x, GLfixed y, GLfixed z, GLfixed w, const char * _file, int _line) {
    glad_glRasterPos4xOES(x, y, z, w);
    gl_check_error(_file, _line);
}


void _glRasterPos4xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glRasterPos4xvOES(coords);
    gl_check_error(_file, _line);
}


void _glRectxOES(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2, const char * _file, int _line) {
    glad_glRectxOES(x1, y1, x2, y2);
    gl_check_error(_file, _line);
}


void _glRectxvOES(const GLfixed *v1, const GLfixed *v2, const char * _file, int _line) {
    glad_glRectxvOES(v1, v2);
    gl_check_error(_file, _line);
}


void _glTexCoord1xOES(GLfixed s, const char * _file, int _line) {
    glad_glTexCoord1xOES(s);
    gl_check_error(_file, _line);
}


void _glTexCoord1xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glTexCoord1xvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord2xOES(GLfixed s, GLfixed t, const char * _file, int _line) {
    glad_glTexCoord2xOES(s, t);
    gl_check_error(_file, _line);
}


void _glTexCoord2xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glTexCoord2xvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord3xOES(GLfixed s, GLfixed t, GLfixed r, const char * _file, int _line) {
    glad_glTexCoord3xOES(s, t, r);
    gl_check_error(_file, _line);
}


void _glTexCoord3xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glTexCoord3xvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexCoord4xOES(GLfixed s, GLfixed t, GLfixed r, GLfixed q, const char * _file, int _line) {
    glad_glTexCoord4xOES(s, t, r, q);
    gl_check_error(_file, _line);
}


void _glTexCoord4xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glTexCoord4xvOES(coords);
    gl_check_error(_file, _line);
}


void _glTexGenxOES(GLenum coord, GLenum pname, GLfixed param, const char * _file, int _line) {
    glad_glTexGenxOES(coord, pname, param);
    gl_check_error(_file, _line);
}


void _glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed *params, const char * _file, int _line) {
    glad_glTexGenxvOES(coord, pname, params);
    gl_check_error(_file, _line);
}


void _glVertex2xOES(GLfixed x, const char * _file, int _line) {
    glad_glVertex2xOES(x);
    gl_check_error(_file, _line);
}


void _glVertex2xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glVertex2xvOES(coords);
    gl_check_error(_file, _line);
}


void _glVertex3xOES(GLfixed x, GLfixed y, const char * _file, int _line) {
    glad_glVertex3xOES(x, y);
    gl_check_error(_file, _line);
}


void _glVertex3xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glVertex3xvOES(coords);
    gl_check_error(_file, _line);
}


void _glVertex4xOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line) {
    glad_glVertex4xOES(x, y, z);
    gl_check_error(_file, _line);
}


void _glVertex4xvOES(const GLfixed *coords, const char * _file, int _line) {
    glad_glVertex4xvOES(coords);
    gl_check_error(_file, _line);
}


GLbitfield _glQueryMatrixxOES(GLfixed *mantissa, GLint *exponent, const char * _file, int _line) {
    auto val = glad_glQueryMatrixxOES(mantissa, exponent);
    gl_check_error(_file, _line);
    return val;
}


void _glClearDepthfOES(GLclampf depth, const char * _file, int _line) {
    glad_glClearDepthfOES(depth);
    gl_check_error(_file, _line);
}


void _glClipPlanefOES(GLenum plane, const GLfloat *equation, const char * _file, int _line) {
    glad_glClipPlanefOES(plane, equation);
    gl_check_error(_file, _line);
}


void _glDepthRangefOES(GLclampf n, GLclampf f, const char * _file, int _line) {
    glad_glDepthRangefOES(n, f);
    gl_check_error(_file, _line);
}


void _glFrustumfOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f, const char * _file, int _line) {
    glad_glFrustumfOES(l, r, b, t, n, f);
    gl_check_error(_file, _line);
}


void _glGetClipPlanefOES(GLenum plane, GLfloat *equation, const char * _file, int _line) {
    glad_glGetClipPlanefOES(plane, equation);
    gl_check_error(_file, _line);
}


void _glOrthofOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f, const char * _file, int _line) {
    glad_glOrthofOES(l, r, b, t, n, f);
    gl_check_error(_file, _line);
}


void _glFramebufferTextureMultiviewOVR(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews, const char * _file, int _line) {
    glad_glFramebufferTextureMultiviewOVR(target, attachment, texture, level, baseViewIndex, numViews);
    gl_check_error(_file, _line);
}


void _glHintPGI(GLenum target, GLint mode, const char * _file, int _line) {
    glad_glHintPGI(target, mode);
    gl_check_error(_file, _line);
}


void _glDetailTexFuncSGIS(GLenum target, GLsizei n, const GLfloat *points, const char * _file, int _line) {
    glad_glDetailTexFuncSGIS(target, n, points);
    gl_check_error(_file, _line);
}


void _glGetDetailTexFuncSGIS(GLenum target, GLfloat *points, const char * _file, int _line) {
    glad_glGetDetailTexFuncSGIS(target, points);
    gl_check_error(_file, _line);
}


void _glFogFuncSGIS(GLsizei n, const GLfloat *points, const char * _file, int _line) {
    glad_glFogFuncSGIS(n, points);
    gl_check_error(_file, _line);
}


void _glGetFogFuncSGIS(GLfloat *points, const char * _file, int _line) {
    glad_glGetFogFuncSGIS(points);
    gl_check_error(_file, _line);
}


void _glSampleMaskSGIS(GLclampf value, GLboolean invert, const char * _file, int _line) {
    glad_glSampleMaskSGIS(value, invert);
    gl_check_error(_file, _line);
}


void _glSamplePatternSGIS(GLenum pattern, const char * _file, int _line) {
    glad_glSamplePatternSGIS(pattern);
    gl_check_error(_file, _line);
}


void _glPixelTexGenParameteriSGIS(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glPixelTexGenParameteriSGIS(pname, param);
    gl_check_error(_file, _line);
}


void _glPixelTexGenParameterivSGIS(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glPixelTexGenParameterivSGIS(pname, params);
    gl_check_error(_file, _line);
}


void _glPixelTexGenParameterfSGIS(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPixelTexGenParameterfSGIS(pname, param);
    gl_check_error(_file, _line);
}


void _glPixelTexGenParameterfvSGIS(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPixelTexGenParameterfvSGIS(pname, params);
    gl_check_error(_file, _line);
}


void _glGetPixelTexGenParameterivSGIS(GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetPixelTexGenParameterivSGIS(pname, params);
    gl_check_error(_file, _line);
}


void _glGetPixelTexGenParameterfvSGIS(GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetPixelTexGenParameterfvSGIS(pname, params);
    gl_check_error(_file, _line);
}


void _glPointParameterfSGIS(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glPointParameterfSGIS(pname, param);
    gl_check_error(_file, _line);
}


void _glPointParameterfvSGIS(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glPointParameterfvSGIS(pname, params);
    gl_check_error(_file, _line);
}


void _glSharpenTexFuncSGIS(GLenum target, GLsizei n, const GLfloat *points, const char * _file, int _line) {
    glad_glSharpenTexFuncSGIS(target, n, points);
    gl_check_error(_file, _line);
}


void _glGetSharpenTexFuncSGIS(GLenum target, GLfloat *points, const char * _file, int _line) {
    glad_glGetSharpenTexFuncSGIS(target, points);
    gl_check_error(_file, _line);
}


void _glTexImage4DSGIS(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTexSubImage4DSGIS(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const void *pixels, const char * _file, int _line) {
    glad_glTexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels);
    gl_check_error(_file, _line);
}


void _glTextureColorMaskSGIS(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, const char * _file, int _line) {
    glad_glTextureColorMaskSGIS(red, green, blue, alpha);
    gl_check_error(_file, _line);
}


void _glGetTexFilterFuncSGIS(GLenum target, GLenum filter, GLfloat *weights, const char * _file, int _line) {
    glad_glGetTexFilterFuncSGIS(target, filter, weights);
    gl_check_error(_file, _line);
}


void _glTexFilterFuncSGIS(GLenum target, GLenum filter, GLsizei n, const GLfloat *weights, const char * _file, int _line) {
    glad_glTexFilterFuncSGIS(target, filter, n, weights);
    gl_check_error(_file, _line);
}


void _glAsyncMarkerSGIX(GLuint marker, const char * _file, int _line) {
    glad_glAsyncMarkerSGIX(marker);
    gl_check_error(_file, _line);
}


GLint _glFinishAsyncSGIX(GLuint *markerp, const char * _file, int _line) {
    auto val = glad_glFinishAsyncSGIX(markerp);
    gl_check_error(_file, _line);
    return val;
}


GLint _glPollAsyncSGIX(GLuint *markerp, const char * _file, int _line) {
    auto val = glad_glPollAsyncSGIX(markerp);
    gl_check_error(_file, _line);
    return val;
}


GLuint _glGenAsyncMarkersSGIX(GLsizei range, const char * _file, int _line) {
    auto val = glad_glGenAsyncMarkersSGIX(range);
    gl_check_error(_file, _line);
    return val;
}


void _glDeleteAsyncMarkersSGIX(GLuint marker, GLsizei range, const char * _file, int _line) {
    glad_glDeleteAsyncMarkersSGIX(marker, range);
    gl_check_error(_file, _line);
}


GLboolean _glIsAsyncMarkerSGIX(GLuint marker, const char * _file, int _line) {
    auto val = glad_glIsAsyncMarkerSGIX(marker);
    gl_check_error(_file, _line);
    return val;
}


void _glFlushRasterSGIX(const char * _file, int _line) {
    glad_glFlushRasterSGIX();
    gl_check_error(_file, _line);
}


void _glFragmentColorMaterialSGIX(GLenum face, GLenum mode, const char * _file, int _line) {
    glad_glFragmentColorMaterialSGIX(face, mode);
    gl_check_error(_file, _line);
}


void _glFragmentLightfSGIX(GLenum light, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glFragmentLightfSGIX(light, pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentLightfvSGIX(GLenum light, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glFragmentLightfvSGIX(light, pname, params);
    gl_check_error(_file, _line);
}


void _glFragmentLightiSGIX(GLenum light, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glFragmentLightiSGIX(light, pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentLightivSGIX(GLenum light, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glFragmentLightivSGIX(light, pname, params);
    gl_check_error(_file, _line);
}


void _glFragmentLightModelfSGIX(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glFragmentLightModelfSGIX(pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentLightModelfvSGIX(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glFragmentLightModelfvSGIX(pname, params);
    gl_check_error(_file, _line);
}


void _glFragmentLightModeliSGIX(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glFragmentLightModeliSGIX(pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentLightModelivSGIX(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glFragmentLightModelivSGIX(pname, params);
    gl_check_error(_file, _line);
}


void _glFragmentMaterialfSGIX(GLenum face, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glFragmentMaterialfSGIX(face, pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentMaterialfvSGIX(GLenum face, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glFragmentMaterialfvSGIX(face, pname, params);
    gl_check_error(_file, _line);
}


void _glFragmentMaterialiSGIX(GLenum face, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glFragmentMaterialiSGIX(face, pname, param);
    gl_check_error(_file, _line);
}


void _glFragmentMaterialivSGIX(GLenum face, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glFragmentMaterialivSGIX(face, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFragmentLightfvSGIX(GLenum light, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetFragmentLightfvSGIX(light, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFragmentLightivSGIX(GLenum light, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFragmentLightivSGIX(light, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFragmentMaterialfvSGIX(GLenum face, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetFragmentMaterialfvSGIX(face, pname, params);
    gl_check_error(_file, _line);
}


void _glGetFragmentMaterialivSGIX(GLenum face, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetFragmentMaterialivSGIX(face, pname, params);
    gl_check_error(_file, _line);
}


void _glLightEnviSGIX(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glLightEnviSGIX(pname, param);
    gl_check_error(_file, _line);
}


void _glFrameZoomSGIX(GLint factor, const char * _file, int _line) {
    glad_glFrameZoomSGIX(factor);
    gl_check_error(_file, _line);
}


void _glIglooInterfaceSGIX(GLenum pname, const void *params, const char * _file, int _line) {
    glad_glIglooInterfaceSGIX(pname, params);
    gl_check_error(_file, _line);
}


GLint _glGetInstrumentsSGIX(const char * _file, int _line) {
    auto val = glad_glGetInstrumentsSGIX();
    gl_check_error(_file, _line);
    return val;
}


void _glInstrumentsBufferSGIX(GLsizei size, GLint *buffer, const char * _file, int _line) {
    glad_glInstrumentsBufferSGIX(size, buffer);
    gl_check_error(_file, _line);
}


GLint _glPollInstrumentsSGIX(GLint *marker_p, const char * _file, int _line) {
    auto val = glad_glPollInstrumentsSGIX(marker_p);
    gl_check_error(_file, _line);
    return val;
}


void _glReadInstrumentsSGIX(GLint marker, const char * _file, int _line) {
    glad_glReadInstrumentsSGIX(marker);
    gl_check_error(_file, _line);
}


void _glStartInstrumentsSGIX(const char * _file, int _line) {
    glad_glStartInstrumentsSGIX();
    gl_check_error(_file, _line);
}


void _glStopInstrumentsSGIX(GLint marker, const char * _file, int _line) {
    glad_glStopInstrumentsSGIX(marker);
    gl_check_error(_file, _line);
}


void _glGetListParameterfvSGIX(GLuint list, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetListParameterfvSGIX(list, pname, params);
    gl_check_error(_file, _line);
}


void _glGetListParameterivSGIX(GLuint list, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetListParameterivSGIX(list, pname, params);
    gl_check_error(_file, _line);
}


void _glListParameterfSGIX(GLuint list, GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glListParameterfSGIX(list, pname, param);
    gl_check_error(_file, _line);
}


void _glListParameterfvSGIX(GLuint list, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glListParameterfvSGIX(list, pname, params);
    gl_check_error(_file, _line);
}


void _glListParameteriSGIX(GLuint list, GLenum pname, GLint param, const char * _file, int _line) {
    glad_glListParameteriSGIX(list, pname, param);
    gl_check_error(_file, _line);
}


void _glListParameterivSGIX(GLuint list, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glListParameterivSGIX(list, pname, params);
    gl_check_error(_file, _line);
}


void _glPixelTexGenSGIX(GLenum mode, const char * _file, int _line) {
    glad_glPixelTexGenSGIX(mode);
    gl_check_error(_file, _line);
}


void _glDeformationMap3dSGIX(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points, const char * _file, int _line) {
    glad_glDeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
    gl_check_error(_file, _line);
}


void _glDeformationMap3fSGIX(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points, const char * _file, int _line) {
    glad_glDeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
    gl_check_error(_file, _line);
}


void _glDeformSGIX(GLbitfield mask, const char * _file, int _line) {
    glad_glDeformSGIX(mask);
    gl_check_error(_file, _line);
}


void _glLoadIdentityDeformationMapSGIX(GLbitfield mask, const char * _file, int _line) {
    glad_glLoadIdentityDeformationMapSGIX(mask);
    gl_check_error(_file, _line);
}


void _glReferencePlaneSGIX(const GLdouble *equation, const char * _file, int _line) {
    glad_glReferencePlaneSGIX(equation);
    gl_check_error(_file, _line);
}


void _glSpriteParameterfSGIX(GLenum pname, GLfloat param, const char * _file, int _line) {
    glad_glSpriteParameterfSGIX(pname, param);
    gl_check_error(_file, _line);
}


void _glSpriteParameterfvSGIX(GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glSpriteParameterfvSGIX(pname, params);
    gl_check_error(_file, _line);
}


void _glSpriteParameteriSGIX(GLenum pname, GLint param, const char * _file, int _line) {
    glad_glSpriteParameteriSGIX(pname, param);
    gl_check_error(_file, _line);
}


void _glSpriteParameterivSGIX(GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glSpriteParameterivSGIX(pname, params);
    gl_check_error(_file, _line);
}


void _glTagSampleBufferSGIX(const char * _file, int _line) {
    glad_glTagSampleBufferSGIX();
    gl_check_error(_file, _line);
}


void _glColorTableSGI(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line) {
    glad_glColorTableSGI(target, internalformat, width, format, type, table);
    gl_check_error(_file, _line);
}


void _glColorTableParameterfvSGI(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line) {
    glad_glColorTableParameterfvSGI(target, pname, params);
    gl_check_error(_file, _line);
}


void _glColorTableParameterivSGI(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line) {
    glad_glColorTableParameterivSGI(target, pname, params);
    gl_check_error(_file, _line);
}


void _glCopyColorTableSGI(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line) {
    glad_glCopyColorTableSGI(target, internalformat, x, y, width);
    gl_check_error(_file, _line);
}


void _glGetColorTableSGI(GLenum target, GLenum format, GLenum type, void *table, const char * _file, int _line) {
    glad_glGetColorTableSGI(target, format, type, table);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameterfvSGI(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line) {
    glad_glGetColorTableParameterfvSGI(target, pname, params);
    gl_check_error(_file, _line);
}


void _glGetColorTableParameterivSGI(GLenum target, GLenum pname, GLint *params, const char * _file, int _line) {
    glad_glGetColorTableParameterivSGI(target, pname, params);
    gl_check_error(_file, _line);
}


void _glFinishTextureSUNX(const char * _file, int _line) {
    glad_glFinishTextureSUNX();
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactorbSUN(GLbyte factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactorbSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactorsSUN(GLshort factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactorsSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactoriSUN(GLint factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactoriSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactorfSUN(GLfloat factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactorfSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactordSUN(GLdouble factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactordSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactorubSUN(GLubyte factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactorubSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactorusSUN(GLushort factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactorusSUN(factor);
    gl_check_error(_file, _line);
}


void _glGlobalAlphaFactoruiSUN(GLuint factor, const char * _file, int _line) {
    glad_glGlobalAlphaFactoruiSUN(factor);
    gl_check_error(_file, _line);
}


void _glDrawMeshArraysSUN(GLenum mode, GLint first, GLsizei count, GLsizei width, const char * _file, int _line) {
    glad_glDrawMeshArraysSUN(mode, first, count, width);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiSUN(GLuint code, const char * _file, int _line) {
    glad_glReplacementCodeuiSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodeusSUN(GLushort code, const char * _file, int _line) {
    glad_glReplacementCodeusSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodeubSUN(GLubyte code, const char * _file, int _line) {
    glad_glReplacementCodeubSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuivSUN(const GLuint *code, const char * _file, int _line) {
    glad_glReplacementCodeuivSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodeusvSUN(const GLushort *code, const char * _file, int _line) {
    glad_glReplacementCodeusvSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodeubvSUN(const GLubyte *code, const char * _file, int _line) {
    glad_glReplacementCodeubvSUN(code);
    gl_check_error(_file, _line);
}


void _glReplacementCodePointerSUN(GLenum type, GLsizei stride, const void **pointer, const char * _file, int _line) {
    glad_glReplacementCodePointerSUN(type, stride, pointer);
    gl_check_error(_file, _line);
}


void _glColor4ubVertex2fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, const char * _file, int _line) {
    glad_glColor4ubVertex2fSUN(r, g, b, a, x, y);
    gl_check_error(_file, _line);
}


void _glColor4ubVertex2fvSUN(const GLubyte *c, const GLfloat *v, const char * _file, int _line) {
    glad_glColor4ubVertex2fvSUN(c, v);
    gl_check_error(_file, _line);
}


void _glColor4ubVertex3fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glColor4ubVertex3fSUN(r, g, b, a, x, y, z);
    gl_check_error(_file, _line);
}


void _glColor4ubVertex3fvSUN(const GLubyte *c, const GLfloat *v, const char * _file, int _line) {
    glad_glColor4ubVertex3fvSUN(c, v);
    gl_check_error(_file, _line);
}


void _glColor3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glColor3fVertex3fSUN(r, g, b, x, y, z);
    gl_check_error(_file, _line);
}


void _glColor3fVertex3fvSUN(const GLfloat *c, const GLfloat *v, const char * _file, int _line) {
    glad_glColor3fVertex3fvSUN(c, v);
    gl_check_error(_file, _line);
}


void _glNormal3fVertex3fSUN(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glNormal3fVertex3fSUN(nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glNormal3fVertex3fvSUN(const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glNormal3fVertex3fvSUN(n, v);
    gl_check_error(_file, _line);
}


void _glColor4fNormal3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glColor4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glColor4fNormal3fVertex3fvSUN(const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glColor4fNormal3fVertex3fvSUN(c, n, v);
    gl_check_error(_file, _line);
}


void _glTexCoord2fVertex3fSUN(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glTexCoord2fVertex3fSUN(s, t, x, y, z);
    gl_check_error(_file, _line);
}


void _glTexCoord2fVertex3fvSUN(const GLfloat *tc, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord2fVertex3fvSUN(tc, v);
    gl_check_error(_file, _line);
}


void _glTexCoord4fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glTexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glTexCoord4fVertex4fvSUN(const GLfloat *tc, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord4fVertex4fvSUN(tc, v);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor4ubVertex3fSUN(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glTexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor4ubVertex3fvSUN(const GLfloat *tc, const GLubyte *c, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord2fColor4ubVertex3fvSUN(tc, c, v);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glTexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord2fColor3fVertex3fvSUN(tc, c, v);
    gl_check_error(_file, _line);
}


void _glTexCoord2fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glTexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glTexCoord2fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord2fNormal3fVertex3fvSUN(tc, n, v);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glTexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v);
    gl_check_error(_file, _line);
}


void _glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line) {
    glad_glTexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w);
    gl_check_error(_file, _line);
}


void _glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glTexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiVertex3fSUN(GLuint rc, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiVertex3fSUN(rc, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiVertex3fvSUN(const GLuint *rc, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiVertex3fvSUN(rc, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor4ubVertex3fSUN(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint *rc, const GLubyte *c, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiColor3fVertex3fvSUN(rc, c, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiNormal3fVertex3fSUN(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z);
    gl_check_error(_file, _line);
}


void _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line) {
    glad_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v);
    gl_check_error(_file, _line);
}

