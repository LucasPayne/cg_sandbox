#ifndef OPENGL_UTILITIES_GLAD_DEBUG_WRAPPERS
#define OPENGL_UTILITIES_GLAD_DEBUG_WRAPPERS


void _glCullFace(GLenum mode, const char * _file, int _line);
void _glFrontFace(GLenum mode, const char * _file, int _line);
void _glHint(GLenum target, GLenum mode, const char * _file, int _line);
void _glLineWidth(GLfloat width, const char * _file, int _line);
void _glPointSize(GLfloat size, const char * _file, int _line);
void _glPolygonMode(GLenum face, GLenum mode, const char * _file, int _line);
void _glScissor(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTexParameterf(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glTexParameteri(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glTexParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glDrawBuffer(GLenum buf, const char * _file, int _line);
void _glClear(GLbitfield mask, const char * _file, int _line);
void _glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line);
void _glClearStencil(GLint s, const char * _file, int _line);
void _glClearDepth(GLdouble depth, const char * _file, int _line);
void _glStencilMask(GLuint mask, const char * _file, int _line);
void _glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, const char * _file, int _line);
void _glDepthMask(GLboolean flag, const char * _file, int _line);
void _glDisable(GLenum cap, const char * _file, int _line);
void _glEnable(GLenum cap, const char * _file, int _line);
void _glFinish(const char * _file, int _line);
void _glFlush(const char * _file, int _line);
void _glBlendFunc(GLenum sfactor, GLenum dfactor, const char * _file, int _line);
void _glLogicOp(GLenum opcode, const char * _file, int _line);
void _glStencilFunc(GLenum func, GLint ref, GLuint mask, const char * _file, int _line);
void _glStencilOp(GLenum fail, GLenum zfail, GLenum zpass, const char * _file, int _line);
void _glDepthFunc(GLenum func, const char * _file, int _line);
void _glPixelStoref(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPixelStorei(GLenum pname, GLint param, const char * _file, int _line);
void _glReadBuffer(GLenum src, const char * _file, int _line);
void _glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels, const char * _file, int _line);
void _glGetBooleanv(GLenum pname, GLboolean *data, const char * _file, int _line);
void _glGetDoublev(GLenum pname, GLdouble *data, const char * _file, int _line);
void _glGetFloatv(GLenum pname, GLfloat *data, const char * _file, int _line);
void _glGetIntegerv(GLenum pname, GLint *data, const char * _file, int _line);
const GLubyte * _glGetString(GLenum name, const char * _file, int _line);
void _glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line);
void _glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTexParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line);
GLboolean _glIsEnabled(GLenum cap, const char * _file, int _line);
void _glDepthRange(GLdouble n, GLdouble f, const char * _file, int _line);
void _glViewport(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glDrawArrays(GLenum mode, GLint first, GLsizei count, const char * _file, int _line);
void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices, const char * _file, int _line);
void _glPolygonOffset(GLfloat factor, GLfloat units, const char * _file, int _line);
void _glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line);
void _glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line);
void _glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glBindTexture(GLenum target, GLuint texture, const char * _file, int _line);
void _glDeleteTextures(GLsizei n, const GLuint *textures, const char * _file, int _line);
void _glGenTextures(GLsizei n, GLuint *textures, const char * _file, int _line);
GLboolean _glIsTexture(GLuint texture, const char * _file, int _line);
void _glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, const char * _file, int _line);
void _glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glActiveTexture(GLenum texture, const char * _file, int _line);
void _glSampleCoverage(GLfloat value, GLboolean invert, const char * _file, int _line);
void _glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glGetCompressedTexImage(GLenum target, GLint level, void *img, const char * _file, int _line);
void _glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line);
void _glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount, const char * _file, int _line);
void _glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const char * _file, int _line);
void _glPointParameterf(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPointParameterfv(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glPointParameteri(GLenum pname, GLint param, const char * _file, int _line);
void _glPointParameteriv(GLenum pname, const GLint *params, const char * _file, int _line);
void _glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line);
void _glBlendEquation(GLenum mode, const char * _file, int _line);
void _glGenQueries(GLsizei n, GLuint *ids, const char * _file, int _line);
void _glDeleteQueries(GLsizei n, const GLuint *ids, const char * _file, int _line);
GLboolean _glIsQuery(GLuint id, const char * _file, int _line);
void _glBeginQuery(GLenum target, GLuint id, const char * _file, int _line);
void _glEndQuery(GLenum target, const char * _file, int _line);
void _glGetQueryiv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line);
void _glBindBuffer(GLenum target, GLuint buffer, const char * _file, int _line);
void _glDeleteBuffers(GLsizei n, const GLuint *buffers, const char * _file, int _line);
void _glGenBuffers(GLsizei n, GLuint *buffers, const char * _file, int _line);
GLboolean _glIsBuffer(GLuint buffer, const char * _file, int _line);
void _glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line);
void _glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line);
void _glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line);
void * _glMapBuffer(GLenum target, GLenum access, const char * _file, int _line);
GLboolean _glUnmapBuffer(GLenum target, const char * _file, int _line);
void _glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetBufferPointerv(GLenum target, GLenum pname, void **params, const char * _file, int _line);
void _glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line);
void _glDrawBuffers(GLsizei n, const GLenum *bufs, const char * _file, int _line);
void _glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, const char * _file, int _line);
void _glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask, const char * _file, int _line);
void _glStencilMaskSeparate(GLenum face, GLuint mask, const char * _file, int _line);
void _glAttachShader(GLuint program, GLuint shader, const char * _file, int _line);
void _glBindAttribLocation(GLuint program, GLuint index, const GLchar *name, const char * _file, int _line);
void _glCompileShader(GLuint shader, const char * _file, int _line);
GLuint _glCreateProgram(const char * _file, int _line);
GLuint _glCreateShader(GLenum type, const char * _file, int _line);
void _glDeleteProgram(GLuint program, const char * _file, int _line);
void _glDeleteShader(GLuint shader, const char * _file, int _line);
void _glDetachShader(GLuint program, GLuint shader, const char * _file, int _line);
void _glDisableVertexAttribArray(GLuint index, const char * _file, int _line);
void _glEnableVertexAttribArray(GLuint index, const char * _file, int _line);
void _glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name, const char * _file, int _line);
void _glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name, const char * _file, int _line);
void _glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders, const char * _file, int _line);
GLint _glGetAttribLocation(GLuint program, const GLchar *name, const char * _file, int _line);
void _glGetProgramiv(GLuint program, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line);
void _glGetShaderiv(GLuint shader, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line);
void _glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source, const char * _file, int _line);
GLint _glGetUniformLocation(GLuint program, const GLchar *name, const char * _file, int _line);
void _glGetUniformfv(GLuint program, GLint location, GLfloat *params, const char * _file, int _line);
void _glGetUniformiv(GLuint program, GLint location, GLint *params, const char * _file, int _line);
void _glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer, const char * _file, int _line);
GLboolean _glIsProgram(GLuint program, const char * _file, int _line);
GLboolean _glIsShader(GLuint shader, const char * _file, int _line);
void _glLinkProgram(GLuint program, const char * _file, int _line);
void _glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length, const char * _file, int _line);
void _glUseProgram(GLuint program, const char * _file, int _line);
void _glUniform1f(GLint location, GLfloat v0, const char * _file, int _line);
void _glUniform2f(GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line);
void _glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line);
void _glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line);
void _glUniform1i(GLint location, GLint v0, const char * _file, int _line);
void _glUniform2i(GLint location, GLint v0, GLint v1, const char * _file, int _line);
void _glUniform3i(GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line);
void _glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line);
void _glUniform1fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform2fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform3fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform4fv(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform1iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform2iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform3iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform4iv(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glValidateProgram(GLuint program, const char * _file, int _line);
void _glVertexAttrib1d(GLuint index, GLdouble x, const char * _file, int _line);
void _glVertexAttrib1dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib1f(GLuint index, GLfloat x, const char * _file, int _line);
void _glVertexAttrib1fv(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib1s(GLuint index, GLshort x, const char * _file, int _line);
void _glVertexAttrib1sv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexAttrib2dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line);
void _glVertexAttrib2fv(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib2s(GLuint index, GLshort x, GLshort y, const char * _file, int _line);
void _glVertexAttrib2sv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexAttrib3dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glVertexAttrib3fv(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glVertexAttrib3sv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4Nbv(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttrib4Niv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttrib4Nsv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line);
void _glVertexAttrib4Nubv(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttrib4Nuiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttrib4Nusv(GLuint index, const GLushort *v, const char * _file, int _line);
void _glVertexAttrib4bv(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexAttrib4dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glVertexAttrib4fv(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib4iv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line);
void _glVertexAttrib4sv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4ubv(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttrib4uiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttrib4usv(GLuint index, const GLushort *v, const char * _file, int _line);
void _glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, const char * _file, int _line);
void _glGetBooleani_v(GLenum target, GLuint index, GLboolean *data, const char * _file, int _line);
void _glGetIntegeri_v(GLenum target, GLuint index, GLint *data, const char * _file, int _line);
void _glEnablei(GLenum target, GLuint index, const char * _file, int _line);
void _glDisablei(GLenum target, GLuint index, const char * _file, int _line);
GLboolean _glIsEnabledi(GLenum target, GLuint index, const char * _file, int _line);
void _glBeginTransformFeedback(GLenum primitiveMode, const char * _file, int _line);
void _glEndTransformFeedback(const char * _file, int _line);
void _glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glBindBufferBase(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line);
void _glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode, const char * _file, int _line);
void _glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line);
void _glClampColor(GLenum target, GLenum clamp, const char * _file, int _line);
void _glBeginConditionalRender(GLuint id, GLenum mode, const char * _file, int _line);
void _glEndConditionalRender(const char * _file, int _line);
void _glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params, const char * _file, int _line);
void _glVertexAttribI1i(GLuint index, GLint x, const char * _file, int _line);
void _glVertexAttribI2i(GLuint index, GLint x, GLint y, const char * _file, int _line);
void _glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z, const char * _file, int _line);
void _glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glVertexAttribI1ui(GLuint index, GLuint x, const char * _file, int _line);
void _glVertexAttribI2ui(GLuint index, GLuint x, GLuint y, const char * _file, int _line);
void _glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z, const char * _file, int _line);
void _glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line);
void _glVertexAttribI1iv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI2iv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI3iv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI4iv(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI1uiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI2uiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI3uiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI4uiv(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI4bv(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttribI4sv(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttribI4ubv(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttribI4usv(GLuint index, const GLushort *v, const char * _file, int _line);
void _glGetUniformuiv(GLuint program, GLint location, GLuint *params, const char * _file, int _line);
void _glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name, const char * _file, int _line);
GLint _glGetFragDataLocation(GLuint program, const GLchar *name, const char * _file, int _line);
void _glUniform1ui(GLint location, GLuint v0, const char * _file, int _line);
void _glUniform2ui(GLint location, GLuint v0, GLuint v1, const char * _file, int _line);
void _glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line);
void _glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line);
void _glUniform1uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform2uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform3uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform4uiv(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glTexParameterIiv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line);
void _glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params, const char * _file, int _line);
void _glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value, const char * _file, int _line);
void _glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value, const char * _file, int _line);
void _glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value, const char * _file, int _line);
void _glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, const char * _file, int _line);
const GLubyte * _glGetStringi(GLenum name, GLuint index, const char * _file, int _line);
GLboolean _glIsRenderbuffer(GLuint renderbuffer, const char * _file, int _line);
void _glBindRenderbuffer(GLenum target, GLuint renderbuffer, const char * _file, int _line);
void _glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers, const char * _file, int _line);
void _glGenRenderbuffers(GLsizei n, GLuint *renderbuffers, const char * _file, int _line);
void _glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
GLboolean _glIsFramebuffer(GLuint framebuffer, const char * _file, int _line);
void _glBindFramebuffer(GLenum target, GLuint framebuffer, const char * _file, int _line);
void _glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers, const char * _file, int _line);
void _glGenFramebuffers(GLsizei n, GLuint *framebuffers, const char * _file, int _line);
GLenum _glCheckFramebufferStatus(GLenum target, const char * _file, int _line);
void _glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line);
void _glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line);
void _glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line);
void _glGenerateMipmap(GLenum target, const char * _file, int _line);
void _glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line);
void _glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line);
void * _glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line);
void _glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, const char * _file, int _line);
void _glBindVertexArray(GLuint array, const char * _file, int _line);
void _glDeleteVertexArrays(GLsizei n, const GLuint *arrays, const char * _file, int _line);
void _glGenVertexArrays(GLsizei n, GLuint *arrays, const char * _file, int _line);
GLboolean _glIsVertexArray(GLuint array, const char * _file, int _line);
void _glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, const char * _file, int _line);
void _glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, const char * _file, int _line);
void _glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glPrimitiveRestartIndex(GLuint index, const char * _file, int _line);
void _glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line);
void _glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices, const char * _file, int _line);
void _glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName, const char * _file, int _line);
GLuint _glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName, const char * _file, int _line);
void _glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName, const char * _file, int _line);
void _glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding, const char * _file, int _line);
void _glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex, const char * _file, int _line);
void _glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex, const char * _file, int _line);
void _glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, const char * _file, int _line);
void _glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex, const char * _file, int _line);
void _glProvokingVertex(GLenum mode, const char * _file, int _line);
GLsync _glFenceSync(GLenum condition, GLbitfield flags, const char * _file, int _line);
GLboolean _glIsSync(GLsync sync, const char * _file, int _line);
void _glDeleteSync(GLsync sync, const char * _file, int _line);
GLenum _glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char * _file, int _line);
void _glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout, const char * _file, int _line);
void _glGetInteger64v(GLenum pname, GLint64 *data, const char * _file, int _line);
void _glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values, const char * _file, int _line);
void _glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data, const char * _file, int _line);
void _glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params, const char * _file, int _line);
void _glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line);
void _glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val, const char * _file, int _line);
void _glSampleMaski(GLuint maskNumber, GLbitfield mask, const char * _file, int _line);
void _glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name, const char * _file, int _line);
GLint _glGetFragDataIndex(GLuint program, const GLchar *name, const char * _file, int _line);
void _glGenSamplers(GLsizei count, GLuint *samplers, const char * _file, int _line);
void _glDeleteSamplers(GLsizei count, const GLuint *samplers, const char * _file, int _line);
GLboolean _glIsSampler(GLuint sampler, const char * _file, int _line);
void _glBindSampler(GLuint unit, GLuint sampler, const char * _file, int _line);
void _glSamplerParameteri(GLuint sampler, GLenum pname, GLint param, const char * _file, int _line);
void _glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param, const char * _file, int _line);
void _glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param, const char * _file, int _line);
void _glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param, const char * _file, int _line);
void _glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param, const char * _file, int _line);
void _glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param, const char * _file, int _line);
void _glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params, const char * _file, int _line);
void _glQueryCounter(GLuint id, GLenum target, const char * _file, int _line);
void _glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line);
void _glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line);
void _glVertexAttribDivisor(GLuint index, GLuint divisor, const char * _file, int _line);
void _glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line);
void _glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line);
void _glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line);
void _glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line);
void _glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line);
void _glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line);
void _glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value, const char * _file, int _line);
void _glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value, const char * _file, int _line);
void _glVertexP2ui(GLenum type, GLuint value, const char * _file, int _line);
void _glVertexP2uiv(GLenum type, const GLuint *value, const char * _file, int _line);
void _glVertexP3ui(GLenum type, GLuint value, const char * _file, int _line);
void _glVertexP3uiv(GLenum type, const GLuint *value, const char * _file, int _line);
void _glVertexP4ui(GLenum type, GLuint value, const char * _file, int _line);
void _glVertexP4uiv(GLenum type, const GLuint *value, const char * _file, int _line);
void _glTexCoordP1ui(GLenum type, GLuint coords, const char * _file, int _line);
void _glTexCoordP1uiv(GLenum type, const GLuint *coords, const char * _file, int _line);
void _glTexCoordP2ui(GLenum type, GLuint coords, const char * _file, int _line);
void _glTexCoordP2uiv(GLenum type, const GLuint *coords, const char * _file, int _line);
void _glTexCoordP3ui(GLenum type, GLuint coords, const char * _file, int _line);
void _glTexCoordP3uiv(GLenum type, const GLuint *coords, const char * _file, int _line);
void _glTexCoordP4ui(GLenum type, GLuint coords, const char * _file, int _line);
void _glTexCoordP4uiv(GLenum type, const GLuint *coords, const char * _file, int _line);
void _glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line);
void _glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line);
void _glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line);
void _glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line);
void _glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line);
void _glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line);
void _glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords, const char * _file, int _line);
void _glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint *coords, const char * _file, int _line);
void _glNormalP3ui(GLenum type, GLuint coords, const char * _file, int _line);
void _glNormalP3uiv(GLenum type, const GLuint *coords, const char * _file, int _line);
void _glColorP3ui(GLenum type, GLuint color, const char * _file, int _line);
void _glColorP3uiv(GLenum type, const GLuint *color, const char * _file, int _line);
void _glColorP4ui(GLenum type, GLuint color, const char * _file, int _line);
void _glColorP4uiv(GLenum type, const GLuint *color, const char * _file, int _line);
void _glSecondaryColorP3ui(GLenum type, GLuint color, const char * _file, int _line);
void _glSecondaryColorP3uiv(GLenum type, const GLuint *color, const char * _file, int _line);
void _glMinSampleShading(GLfloat value, const char * _file, int _line);
void _glBlendEquationi(GLuint buf, GLenum mode, const char * _file, int _line);
void _glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line);
void _glBlendFunci(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line);
void _glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line);
void _glDrawArraysIndirect(GLenum mode, const void *indirect, const char * _file, int _line);
void _glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, const char * _file, int _line);
void _glUniform1d(GLint location, GLdouble x, const char * _file, int _line);
void _glUniform2d(GLint location, GLdouble x, GLdouble y, const char * _file, int _line);
void _glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glUniform1dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glUniform2dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glUniform3dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glUniform4dv(GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glGetUniformdv(GLuint program, GLint location, GLdouble *params, const char * _file, int _line);
GLint _glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name, const char * _file, int _line);
GLuint _glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name, const char * _file, int _line);
void _glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values, const char * _file, int _line);
void _glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line);
void _glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line);
void _glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices, const char * _file, int _line);
void _glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params, const char * _file, int _line);
void _glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values, const char * _file, int _line);
void _glPatchParameteri(GLenum pname, GLint value, const char * _file, int _line);
void _glPatchParameterfv(GLenum pname, const GLfloat *values, const char * _file, int _line);
void _glBindTransformFeedback(GLenum target, GLuint id, const char * _file, int _line);
void _glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids, const char * _file, int _line);
void _glGenTransformFeedbacks(GLsizei n, GLuint *ids, const char * _file, int _line);
GLboolean _glIsTransformFeedback(GLuint id, const char * _file, int _line);
void _glPauseTransformFeedback(const char * _file, int _line);
void _glResumeTransformFeedback(const char * _file, int _line);
void _glDrawTransformFeedback(GLenum mode, GLuint id, const char * _file, int _line);
void _glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream, const char * _file, int _line);
void _glBeginQueryIndexed(GLenum target, GLuint index, GLuint id, const char * _file, int _line);
void _glEndQueryIndexed(GLenum target, GLuint index, const char * _file, int _line);
void _glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glReleaseShaderCompiler(const char * _file, int _line);
void _glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length, const char * _file, int _line);
void _glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision, const char * _file, int _line);
void _glDepthRangef(GLfloat n, GLfloat f, const char * _file, int _line);
void _glClearDepthf(GLfloat d, const char * _file, int _line);
void _glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary, const char * _file, int _line);
void _glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length, const char * _file, int _line);
void _glProgramParameteri(GLuint program, GLenum pname, GLint value, const char * _file, int _line);
void _glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program, const char * _file, int _line);
void _glActiveShaderProgram(GLuint pipeline, GLuint program, const char * _file, int _line);
GLuint _glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings, const char * _file, int _line);
void _glBindProgramPipeline(GLuint pipeline, const char * _file, int _line);
void _glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines, const char * _file, int _line);
void _glGenProgramPipelines(GLsizei n, GLuint *pipelines, const char * _file, int _line);
GLboolean _glIsProgramPipeline(GLuint pipeline, const char * _file, int _line);
void _glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params, const char * _file, int _line);
void _glProgramUniform1i(GLuint program, GLint location, GLint v0, const char * _file, int _line);
void _glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform1f(GLuint program, GLint location, GLfloat v0, const char * _file, int _line);
void _glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform1d(GLuint program, GLint location, GLdouble v0, const char * _file, int _line);
void _glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform1ui(GLuint program, GLint location, GLuint v0, const char * _file, int _line);
void _glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1, const char * _file, int _line);
void _glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line);
void _glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1, const char * _file, int _line);
void _glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1, const char * _file, int _line);
void _glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line);
void _glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line);
void _glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, const char * _file, int _line);
void _glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line);
void _glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line);
void _glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line);
void _glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3, const char * _file, int _line);
void _glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line);
void _glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glValidateProgramPipeline(GLuint pipeline, const char * _file, int _line);
void _glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line);
void _glVertexAttribL1d(GLuint index, GLdouble x, const char * _file, int _line);
void _glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexAttribL1dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL2dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL3dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL4dv(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const char * _file, int _line);
void _glViewportIndexedfv(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glScissorArrayv(GLuint first, GLsizei count, const GLint *v, const char * _file, int _line);
void _glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height, const char * _file, int _line);
void _glScissorIndexedv(GLuint index, const GLint *v, const char * _file, int _line);
void _glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f, const char * _file, int _line);
void _glGetFloati_v(GLenum target, GLuint index, GLfloat *data, const char * _file, int _line);
void _glGetDoublei_v(GLenum target, GLuint index, GLdouble *data, const char * _file, int _line);
void _glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance, const char * _file, int _line);
void _glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance, const char * _file, int _line);
void _glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance, const char * _file, int _line);
void _glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params, const char * _file, int _line);
void _glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params, const char * _file, int _line);
void _glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format, const char * _file, int _line);
void _glMemoryBarrier(GLbitfield barriers, const char * _file, int _line);
void _glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line);
void _glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount, const char * _file, int _line);
void _glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount, const char * _file, int _line);
void _glTbufferMask3DFX(GLuint mask, const char * _file, int _line);
void _glDebugMessageEnableAMD(GLenum category, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line);
void _glDebugMessageInsertAMD(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar *buf, const char * _file, int _line);
void _glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void *userParam, const char * _file, int _line);
GLuint _glGetDebugMessageLogAMD(GLuint count, GLsizei bufSize, GLenum *categories, GLuint *severities, GLuint *ids, GLsizei *lengths, GLchar *message, const char * _file, int _line);
void _glBlendFuncIndexedAMD(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line);
void _glBlendFuncSeparateIndexedAMD(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line);
void _glBlendEquationIndexedAMD(GLuint buf, GLenum mode, const char * _file, int _line);
void _glBlendEquationSeparateIndexedAMD(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line);
void _glRenderbufferStorageMultisampleAdvancedAMD(GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glNamedRenderbufferStorageMultisampleAdvancedAMD(GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glFramebufferSamplePositionsfvAMD(GLenum target, GLuint numsamples, GLuint pixelindex, const GLfloat *values, const char * _file, int _line);
void _glNamedFramebufferSamplePositionsfvAMD(GLuint framebuffer, GLuint numsamples, GLuint pixelindex, const GLfloat *values, const char * _file, int _line);
void _glGetFramebufferParameterfvAMD(GLenum target, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat *values, const char * _file, int _line);
void _glGetNamedFramebufferParameterfvAMD(GLuint framebuffer, GLenum pname, GLuint numsamples, GLuint pixelindex, GLsizei size, GLfloat *values, const char * _file, int _line);
void _glUniform1i64NV(GLint location, GLint64EXT x, const char * _file, int _line);
void _glUniform2i64NV(GLint location, GLint64EXT x, GLint64EXT y, const char * _file, int _line);
void _glUniform3i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line);
void _glUniform4i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line);
void _glUniform1i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glUniform2i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glUniform3i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glUniform4i64vNV(GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glUniform1ui64NV(GLint location, GLuint64EXT x, const char * _file, int _line);
void _glUniform2ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line);
void _glUniform3ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line);
void _glUniform4ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line);
void _glUniform1ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glUniform2ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glUniform3ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glUniform4ui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glGetUniformi64vNV(GLuint program, GLint location, GLint64EXT *params, const char * _file, int _line);
void _glGetUniformui64vNV(GLuint program, GLint location, GLuint64EXT *params, const char * _file, int _line);
void _glProgramUniform1i64NV(GLuint program, GLint location, GLint64EXT x, const char * _file, int _line);
void _glProgramUniform2i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, const char * _file, int _line);
void _glProgramUniform3i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line);
void _glProgramUniform4i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line);
void _glProgramUniform1i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glProgramUniform2i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glProgramUniform3i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glProgramUniform4i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT *value, const char * _file, int _line);
void _glProgramUniform1ui64NV(GLuint program, GLint location, GLuint64EXT x, const char * _file, int _line);
void _glProgramUniform2ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line);
void _glProgramUniform3ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line);
void _glProgramUniform4ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line);
void _glProgramUniform1ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glProgramUniform2ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glProgramUniform3ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glProgramUniform4ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glVertexAttribParameteriAMD(GLuint index, GLenum pname, GLint param, const char * _file, int _line);
void _glMultiDrawArraysIndirectAMD(GLenum mode, const void *indirect, GLsizei primcount, GLsizei stride, const char * _file, int _line);
void _glMultiDrawElementsIndirectAMD(GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride, const char * _file, int _line);
void _glGenNamesAMD(GLenum identifier, GLuint num, GLuint *names, const char * _file, int _line);
void _glDeleteNamesAMD(GLenum identifier, GLuint num, const GLuint *names, const char * _file, int _line);
GLboolean _glIsNameAMD(GLenum identifier, GLuint name, const char * _file, int _line);
void _glQueryObjectParameteruiAMD(GLenum target, GLuint id, GLenum pname, GLuint param, const char * _file, int _line);
void _glGetPerfMonitorGroupsAMD(GLint *numGroups, GLsizei groupsSize, GLuint *groups, const char * _file, int _line);
void _glGetPerfMonitorCountersAMD(GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters, const char * _file, int _line);
void _glGetPerfMonitorGroupStringAMD(GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString, const char * _file, int _line);
void _glGetPerfMonitorCounterStringAMD(GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString, const char * _file, int _line);
void _glGetPerfMonitorCounterInfoAMD(GLuint group, GLuint counter, GLenum pname, void *data, const char * _file, int _line);
void _glGenPerfMonitorsAMD(GLsizei n, GLuint *monitors, const char * _file, int _line);
void _glDeletePerfMonitorsAMD(GLsizei n, GLuint *monitors, const char * _file, int _line);
void _glSelectPerfMonitorCountersAMD(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList, const char * _file, int _line);
void _glBeginPerfMonitorAMD(GLuint monitor, const char * _file, int _line);
void _glEndPerfMonitorAMD(GLuint monitor, const char * _file, int _line);
void _glGetPerfMonitorCounterDataAMD(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten, const char * _file, int _line);
void _glSetMultisamplefvAMD(GLenum pname, GLuint index, const GLfloat *val, const char * _file, int _line);
void _glTexStorageSparseAMD(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags, const char * _file, int _line);
void _glTextureStorageSparseAMD(GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, GLbitfield flags, const char * _file, int _line);
void _glStencilOpValueAMD(GLenum face, GLuint value, const char * _file, int _line);
void _glTessellationFactorAMD(GLfloat factor, const char * _file, int _line);
void _glTessellationModeAMD(GLenum mode, const char * _file, int _line);
void _glElementPointerAPPLE(GLenum type, const void *pointer, const char * _file, int _line);
void _glDrawElementArrayAPPLE(GLenum mode, GLint first, GLsizei count, const char * _file, int _line);
void _glDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count, const char * _file, int _line);
void _glMultiDrawElementArrayAPPLE(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line);
void _glMultiDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line);
void _glGenFencesAPPLE(GLsizei n, GLuint *fences, const char * _file, int _line);
void _glDeleteFencesAPPLE(GLsizei n, const GLuint *fences, const char * _file, int _line);
void _glSetFenceAPPLE(GLuint fence, const char * _file, int _line);
GLboolean _glIsFenceAPPLE(GLuint fence, const char * _file, int _line);
GLboolean _glTestFenceAPPLE(GLuint fence, const char * _file, int _line);
void _glFinishFenceAPPLE(GLuint fence, const char * _file, int _line);
GLboolean _glTestObjectAPPLE(GLenum object, GLuint name, const char * _file, int _line);
void _glFinishObjectAPPLE(GLenum object, GLint name, const char * _file, int _line);
void _glBufferParameteriAPPLE(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glFlushMappedBufferRangeAPPLE(GLenum target, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
GLenum _glObjectPurgeableAPPLE(GLenum objectType, GLuint name, GLenum option, const char * _file, int _line);
GLenum _glObjectUnpurgeableAPPLE(GLenum objectType, GLuint name, GLenum option, const char * _file, int _line);
void _glGetObjectParameterivAPPLE(GLenum objectType, GLuint name, GLenum pname, GLint *params, const char * _file, int _line);
void _glTextureRangeAPPLE(GLenum target, GLsizei length, const void *pointer, const char * _file, int _line);
void _glGetTexParameterPointervAPPLE(GLenum target, GLenum pname, void **params, const char * _file, int _line);
void _glBindVertexArrayAPPLE(GLuint array, const char * _file, int _line);
void _glDeleteVertexArraysAPPLE(GLsizei n, const GLuint *arrays, const char * _file, int _line);
void _glGenVertexArraysAPPLE(GLsizei n, GLuint *arrays, const char * _file, int _line);
GLboolean _glIsVertexArrayAPPLE(GLuint array, const char * _file, int _line);
void _glVertexArrayRangeAPPLE(GLsizei length, void *pointer, const char * _file, int _line);
void _glFlushVertexArrayRangeAPPLE(GLsizei length, void *pointer, const char * _file, int _line);
void _glVertexArrayParameteriAPPLE(GLenum pname, GLint param, const char * _file, int _line);
void _glEnableVertexAttribAPPLE(GLuint index, GLenum pname, const char * _file, int _line);
void _glDisableVertexAttribAPPLE(GLuint index, GLenum pname, const char * _file, int _line);
GLboolean _glIsVertexAttribEnabledAPPLE(GLuint index, GLenum pname, const char * _file, int _line);
void _glMapVertexAttrib1dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points, const char * _file, int _line);
void _glMapVertexAttrib1fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points, const char * _file, int _line);
void _glMapVertexAttrib2dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points, const char * _file, int _line);
void _glMapVertexAttrib2fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points, const char * _file, int _line);
void _glMemoryBarrierByRegion(GLbitfield barriers, const char * _file, int _line);
void _glPrimitiveBoundingBoxARB(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW, const char * _file, int _line);
GLuint64 _glGetTextureHandleARB(GLuint texture, const char * _file, int _line);
GLuint64 _glGetTextureSamplerHandleARB(GLuint texture, GLuint sampler, const char * _file, int _line);
void _glMakeTextureHandleResidentARB(GLuint64 handle, const char * _file, int _line);
void _glMakeTextureHandleNonResidentARB(GLuint64 handle, const char * _file, int _line);
GLuint64 _glGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format, const char * _file, int _line);
void _glMakeImageHandleResidentARB(GLuint64 handle, GLenum access, const char * _file, int _line);
void _glMakeImageHandleNonResidentARB(GLuint64 handle, const char * _file, int _line);
void _glUniformHandleui64ARB(GLint location, GLuint64 value, const char * _file, int _line);
void _glUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value, const char * _file, int _line);
void _glProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *values, const char * _file, int _line);
GLboolean _glIsTextureHandleResidentARB(GLuint64 handle, const char * _file, int _line);
GLboolean _glIsImageHandleResidentARB(GLuint64 handle, const char * _file, int _line);
void _glVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x, const char * _file, int _line);
void _glVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT *v, const char * _file, int _line);
void _glGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT *params, const char * _file, int _line);
void _glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line);
GLsync _glCreateSyncFromCLeventARB(struct _cl_context *context, struct _cl_event *event, GLbitfield flags, const char * _file, int _line);
void _glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClipControl(GLenum origin, GLenum depth, const char * _file, int _line);
void _glClampColorARB(GLenum target, GLenum clamp, const char * _file, int _line);
void _glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, const char * _file, int _line);
void _glDispatchComputeIndirect(GLintptr indirect, const char * _file, int _line);
void _glDispatchComputeGroupSizeARB(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z, const char * _file, int _line);
void _glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, const char * _file, int _line);
void _glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line);
void _glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line);
void _glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void *userParam, const char * _file, int _line);
GLuint _glGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line);
void _glCreateTransformFeedbacks(GLsizei n, GLuint *ids, const char * _file, int _line);
void _glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer, const char * _file, int _line);
void _glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint *param, const char * _file, int _line);
void _glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 *param, const char * _file, int _line);
void _glCreateBuffers(GLsizei n, GLuint *buffers, const char * _file, int _line);
void _glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line);
void _glNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line);
void _glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line);
void _glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line);
void _glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void * _glMapNamedBuffer(GLuint buffer, GLenum access, const char * _file, int _line);
void * _glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line);
GLboolean _glUnmapNamedBuffer(GLuint buffer, const char * _file, int _line);
void _glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line);
void _glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 *params, const char * _file, int _line);
void _glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void **params, const char * _file, int _line);
void _glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line);
void _glCreateFramebuffers(GLsizei n, GLuint *framebuffers, const char * _file, int _line);
void _glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line);
void _glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param, const char * _file, int _line);
void _glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line);
void _glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line);
void _glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf, const char * _file, int _line);
void _glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs, const char * _file, int _line);
void _glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src, const char * _file, int _line);
void _glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, const char * _file, int _line);
void _glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value, const char * _file, int _line);
void _glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value, const char * _file, int _line);
void _glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value, const char * _file, int _line);
void _glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil, const char * _file, int _line);
void _glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line);
GLenum _glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target, const char * _file, int _line);
void _glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line);
void _glCreateRenderbuffers(GLsizei n, GLuint *renderbuffers, const char * _file, int _line);
void _glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glCreateTextures(GLenum target, GLsizei n, GLuint *textures, const char * _file, int _line);
void _glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line);
void _glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTextureParameterf(GLuint texture, GLenum pname, GLfloat param, const char * _file, int _line);
void _glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat *param, const char * _file, int _line);
void _glTextureParameteri(GLuint texture, GLenum pname, GLint param, const char * _file, int _line);
void _glTextureParameterIiv(GLuint texture, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint *params, const char * _file, int _line);
void _glTextureParameteriv(GLuint texture, GLenum pname, const GLint *param, const char * _file, int _line);
void _glGenerateTextureMipmap(GLuint texture, const char * _file, int _line);
void _glBindTextureUnit(GLuint unit, GLuint texture, const char * _file, int _line);
void _glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels, const char * _file, int _line);
void _glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void *pixels, const char * _file, int _line);
void _glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint *params, const char * _file, int _line);
void _glGetTextureParameteriv(GLuint texture, GLenum pname, GLint *params, const char * _file, int _line);
void _glCreateVertexArrays(GLsizei n, GLuint *arrays, const char * _file, int _line);
void _glDisableVertexArrayAttrib(GLuint vaobj, GLuint index, const char * _file, int _line);
void _glEnableVertexArrayAttrib(GLuint vaobj, GLuint index, const char * _file, int _line);
void _glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer, const char * _file, int _line);
void _glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line);
void _glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides, const char * _file, int _line);
void _glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex, const char * _file, int _line);
void _glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor, const char * _file, int _line);
void _glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param, const char * _file, int _line);
void _glCreateSamplers(GLsizei n, GLuint *samplers, const char * _file, int _line);
void _glCreateProgramPipelines(GLsizei n, GLuint *pipelines, const char * _file, int _line);
void _glCreateQueries(GLenum target, GLsizei n, GLuint *ids, const char * _file, int _line);
void _glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line);
void _glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line);
void _glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line);
void _glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset, const char * _file, int _line);
void _glDrawBuffersARB(GLsizei n, const GLenum *bufs, const char * _file, int _line);
void _glBlendEquationiARB(GLuint buf, GLenum mode, const char * _file, int _line);
void _glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line);
void _glBlendFunciARB(GLuint buf, GLenum src, GLenum dst, const char * _file, int _line);
void _glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha, const char * _file, int _line);
void _glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount, const char * _file, int _line);
void _glDrawElementsInstancedARB(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, const char * _file, int _line);
void _glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void *string, const char * _file, int _line);
void _glBindProgramARB(GLenum target, GLuint program, const char * _file, int _line);
void _glDeleteProgramsARB(GLsizei n, const GLuint *programs, const char * _file, int _line);
void _glGenProgramsARB(GLsizei n, GLuint *programs, const char * _file, int _line);
void _glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line);
void _glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line);
void _glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line);
void _glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line);
void _glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble *params, const char * _file, int _line);
void _glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat *params, const char * _file, int _line);
void _glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble *params, const char * _file, int _line);
void _glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat *params, const char * _file, int _line);
void _glGetProgramivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetProgramStringARB(GLenum target, GLenum pname, void *string, const char * _file, int _line);
GLboolean _glIsProgramARB(GLuint program, const char * _file, int _line);
void _glFramebufferParameteri(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glProgramParameteriARB(GLuint program, GLenum pname, GLint value, const char * _file, int _line);
void _glFramebufferTextureARB(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTextureLayerARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line);
void _glFramebufferTextureFaceARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line);
void _glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels, const char * _file, int _line);
void _glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels, const char * _file, int _line);
void _glSpecializeShaderARB(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue, const char * _file, int _line);
void _glUniform1i64ARB(GLint location, GLint64 x, const char * _file, int _line);
void _glUniform2i64ARB(GLint location, GLint64 x, GLint64 y, const char * _file, int _line);
void _glUniform3i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z, const char * _file, int _line);
void _glUniform4i64ARB(GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w, const char * _file, int _line);
void _glUniform1i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glUniform2i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glUniform3i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glUniform4i64vARB(GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glUniform1ui64ARB(GLint location, GLuint64 x, const char * _file, int _line);
void _glUniform2ui64ARB(GLint location, GLuint64 x, GLuint64 y, const char * _file, int _line);
void _glUniform3ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, const char * _file, int _line);
void _glUniform4ui64ARB(GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w, const char * _file, int _line);
void _glUniform1ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glUniform2ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glUniform3ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glUniform4ui64vARB(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glGetUniformi64vARB(GLuint program, GLint location, GLint64 *params, const char * _file, int _line);
void _glGetUniformui64vARB(GLuint program, GLint location, GLuint64 *params, const char * _file, int _line);
void _glGetnUniformi64vARB(GLuint program, GLint location, GLsizei bufSize, GLint64 *params, const char * _file, int _line);
void _glGetnUniformui64vARB(GLuint program, GLint location, GLsizei bufSize, GLuint64 *params, const char * _file, int _line);
void _glProgramUniform1i64ARB(GLuint program, GLint location, GLint64 x, const char * _file, int _line);
void _glProgramUniform2i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, const char * _file, int _line);
void _glProgramUniform3i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, const char * _file, int _line);
void _glProgramUniform4i64ARB(GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w, const char * _file, int _line);
void _glProgramUniform1i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glProgramUniform2i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glProgramUniform3i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glProgramUniform4i64vARB(GLuint program, GLint location, GLsizei count, const GLint64 *value, const char * _file, int _line);
void _glProgramUniform1ui64ARB(GLuint program, GLint location, GLuint64 x, const char * _file, int _line);
void _glProgramUniform2ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, const char * _file, int _line);
void _glProgramUniform3ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, const char * _file, int _line);
void _glProgramUniform4ui64ARB(GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w, const char * _file, int _line);
void _glProgramUniform1ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glProgramUniform2ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glProgramUniform3ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glProgramUniform4ui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line);
void _glColorTableParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glColorTableParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glGetColorTable(GLenum target, GLenum format, GLenum type, void *table, const char * _file, int _line);
void _glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetColorTableParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image, const char * _file, int _line);
void _glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image, const char * _file, int _line);
void _glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params, const char * _file, int _line);
void _glConvolutionParameterfv(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glConvolutionParameteri(GLenum target, GLenum pname, GLint params, const char * _file, int _line);
void _glConvolutionParameteriv(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, void *image, const char * _file, int _line);
void _glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetSeparableFilter(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span, const char * _file, int _line);
void _glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column, const char * _file, int _line);
void _glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line);
void _glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetHistogramParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line);
void _glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, const char * _file, int _line);
void _glMinmax(GLenum target, GLenum internalformat, GLboolean sink, const char * _file, int _line);
void _glResetHistogram(GLenum target, const char * _file, int _line);
void _glResetMinmax(GLenum target, const char * _file, int _line);
void _glMultiDrawArraysIndirectCountARB(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line);
void _glMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line);
void _glVertexAttribDivisorARB(GLuint index, GLuint divisor, const char * _file, int _line);
void _glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params, const char * _file, int _line);
void _glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glInvalidateTexImage(GLuint texture, GLint level, const char * _file, int _line);
void _glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line);
void _glInvalidateBufferData(GLuint buffer, const char * _file, int _line);
void _glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, const char * _file, int _line);
void _glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glCurrentPaletteMatrixARB(GLint index, const char * _file, int _line);
void _glMatrixIndexubvARB(GLint size, const GLubyte *indices, const char * _file, int _line);
void _glMatrixIndexusvARB(GLint size, const GLushort *indices, const char * _file, int _line);
void _glMatrixIndexuivARB(GLint size, const GLuint *indices, const char * _file, int _line);
void _glMatrixIndexPointerARB(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const char * _file, int _line);
void _glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes, const char * _file, int _line);
void _glBindTextures(GLuint first, GLsizei count, const GLuint *textures, const char * _file, int _line);
void _glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers, const char * _file, int _line);
void _glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures, const char * _file, int _line);
void _glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides, const char * _file, int _line);
void _glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line);
void _glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line);
void _glSampleCoverageARB(GLfloat value, GLboolean invert, const char * _file, int _line);
void _glActiveTextureARB(GLenum texture, const char * _file, int _line);
void _glClientActiveTextureARB(GLenum texture, const char * _file, int _line);
void _glMultiTexCoord1dARB(GLenum target, GLdouble s, const char * _file, int _line);
void _glMultiTexCoord1dvARB(GLenum target, const GLdouble *v, const char * _file, int _line);
void _glMultiTexCoord1fARB(GLenum target, GLfloat s, const char * _file, int _line);
void _glMultiTexCoord1fvARB(GLenum target, const GLfloat *v, const char * _file, int _line);
void _glMultiTexCoord1iARB(GLenum target, GLint s, const char * _file, int _line);
void _glMultiTexCoord1ivARB(GLenum target, const GLint *v, const char * _file, int _line);
void _glMultiTexCoord1sARB(GLenum target, GLshort s, const char * _file, int _line);
void _glMultiTexCoord1svARB(GLenum target, const GLshort *v, const char * _file, int _line);
void _glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t, const char * _file, int _line);
void _glMultiTexCoord2dvARB(GLenum target, const GLdouble *v, const char * _file, int _line);
void _glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t, const char * _file, int _line);
void _glMultiTexCoord2fvARB(GLenum target, const GLfloat *v, const char * _file, int _line);
void _glMultiTexCoord2iARB(GLenum target, GLint s, GLint t, const char * _file, int _line);
void _glMultiTexCoord2ivARB(GLenum target, const GLint *v, const char * _file, int _line);
void _glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t, const char * _file, int _line);
void _glMultiTexCoord2svARB(GLenum target, const GLshort *v, const char * _file, int _line);
void _glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, const char * _file, int _line);
void _glMultiTexCoord3dvARB(GLenum target, const GLdouble *v, const char * _file, int _line);
void _glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, const char * _file, int _line);
void _glMultiTexCoord3fvARB(GLenum target, const GLfloat *v, const char * _file, int _line);
void _glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r, const char * _file, int _line);
void _glMultiTexCoord3ivARB(GLenum target, const GLint *v, const char * _file, int _line);
void _glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r, const char * _file, int _line);
void _glMultiTexCoord3svARB(GLenum target, const GLshort *v, const char * _file, int _line);
void _glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q, const char * _file, int _line);
void _glMultiTexCoord4dvARB(GLenum target, const GLdouble *v, const char * _file, int _line);
void _glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q, const char * _file, int _line);
void _glMultiTexCoord4fvARB(GLenum target, const GLfloat *v, const char * _file, int _line);
void _glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q, const char * _file, int _line);
void _glMultiTexCoord4ivARB(GLenum target, const GLint *v, const char * _file, int _line);
void _glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q, const char * _file, int _line);
void _glMultiTexCoord4svARB(GLenum target, const GLshort *v, const char * _file, int _line);
void _glGenQueriesARB(GLsizei n, GLuint *ids, const char * _file, int _line);
void _glDeleteQueriesARB(GLsizei n, const GLuint *ids, const char * _file, int _line);
GLboolean _glIsQueryARB(GLuint id, const char * _file, int _line);
void _glBeginQueryARB(GLenum target, GLuint id, const char * _file, int _line);
void _glEndQueryARB(GLenum target, const char * _file, int _line);
void _glGetQueryivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetQueryObjectivARB(GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line);
void _glMaxShaderCompilerThreadsARB(GLuint count, const char * _file, int _line);
void _glPointParameterfARB(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPointParameterfvARB(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp, const char * _file, int _line);
void _glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params, const char * _file, int _line);
GLuint _glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line);
void _glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name, const char * _file, int _line);
void _glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params, const char * _file, int _line);
GLint _glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line);
GLint _glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name, const char * _file, int _line);
GLenum _glGetGraphicsResetStatusARB(const char * _file, int _line);
void _glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *img, const char * _file, int _line);
void _glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line);
void _glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, void *img, const char * _file, int _line);
void _glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line);
void _glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line);
void _glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line);
void _glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble *params, const char * _file, int _line);
void _glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v, const char * _file, int _line);
void _glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v, const char * _file, int _line);
void _glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint *v, const char * _file, int _line);
void _glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat *values, const char * _file, int _line);
void _glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint *values, const char * _file, int _line);
void _glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort *values, const char * _file, int _line);
void _glGetnPolygonStippleARB(GLsizei bufSize, GLubyte *pattern, const char * _file, int _line);
void _glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table, const char * _file, int _line);
void _glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image, const char * _file, int _line);
void _glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span, const char * _file, int _line);
void _glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values, const char * _file, int _line);
void _glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values, const char * _file, int _line);
void _glFramebufferSampleLocationsfvARB(GLenum target, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glNamedFramebufferSampleLocationsfvARB(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glEvaluateDepthValuesARB(const char * _file, int _line);
void _glMinSampleShadingARB(GLfloat value, const char * _file, int _line);
void _glDeleteObjectARB(GLhandleARB obj, const char * _file, int _line);
GLhandleARB _glGetHandleARB(GLenum pname, const char * _file, int _line);
void _glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj, const char * _file, int _line);
GLhandleARB _glCreateShaderObjectARB(GLenum shaderType, const char * _file, int _line);
void _glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, const GLcharARB **string, const GLint *length, const char * _file, int _line);
void _glCompileShaderARB(GLhandleARB shaderObj, const char * _file, int _line);
GLhandleARB _glCreateProgramObjectARB(const char * _file, int _line);
void _glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj, const char * _file, int _line);
void _glLinkProgramARB(GLhandleARB programObj, const char * _file, int _line);
void _glUseProgramObjectARB(GLhandleARB programObj, const char * _file, int _line);
void _glValidateProgramARB(GLhandleARB programObj, const char * _file, int _line);
void _glUniform1fARB(GLint location, GLfloat v0, const char * _file, int _line);
void _glUniform2fARB(GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line);
void _glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line);
void _glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line);
void _glUniform1iARB(GLint location, GLint v0, const char * _file, int _line);
void _glUniform2iARB(GLint location, GLint v0, GLint v1, const char * _file, int _line);
void _glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line);
void _glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line);
void _glUniform1fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform2fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform3fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform4fvARB(GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glUniform1ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform2ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform3ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniform4ivARB(GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog, const char * _file, int _line);
void _glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj, const char * _file, int _line);
GLint _glGetUniformLocationARB(GLhandleARB programObj, const GLcharARB *name, const char * _file, int _line);
void _glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name, const char * _file, int _line);
void _glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat *params, const char * _file, int _line);
void _glGetUniformivARB(GLhandleARB programObj, GLint location, GLint *params, const char * _file, int _line);
void _glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source, const char * _file, int _line);
void _glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding, const char * _file, int _line);
void _glNamedStringARB(GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string, const char * _file, int _line);
void _glDeleteNamedStringARB(GLint namelen, const GLchar *name, const char * _file, int _line);
void _glCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar *const*path, const GLint *length, const char * _file, int _line);
GLboolean _glIsNamedStringARB(GLint namelen, const GLchar *name, const char * _file, int _line);
void _glGetNamedStringARB(GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string, const char * _file, int _line);
void _glGetNamedStringivARB(GLint namelen, const GLchar *name, GLenum pname, GLint *params, const char * _file, int _line);
void _glBufferPageCommitmentARB(GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line);
void _glNamedBufferPageCommitmentEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line);
void _glNamedBufferPageCommitmentARB(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit, const char * _file, int _line);
void _glTexPageCommitmentARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit, const char * _file, int _line);
void _glTextureBarrier(const char * _file, int _line);
void _glTexBufferARB(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glCompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glCompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data, const char * _file, int _line);
void _glGetCompressedTexImageARB(GLenum target, GLint level, void *img, const char * _file, int _line);
void _glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers, const char * _file, int _line);
void _glLoadTransposeMatrixfARB(const GLfloat *m, const char * _file, int _line);
void _glLoadTransposeMatrixdARB(const GLdouble *m, const char * _file, int _line);
void _glMultTransposeMatrixfARB(const GLfloat *m, const char * _file, int _line);
void _glMultTransposeMatrixdARB(const GLdouble *m, const char * _file, int _line);
void _glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line);
void _glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line);
void _glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexAttribBinding(GLuint attribindex, GLuint bindingindex, const char * _file, int _line);
void _glVertexBindingDivisor(GLuint bindingindex, GLuint divisor, const char * _file, int _line);
void _glWeightbvARB(GLint size, const GLbyte *weights, const char * _file, int _line);
void _glWeightsvARB(GLint size, const GLshort *weights, const char * _file, int _line);
void _glWeightivARB(GLint size, const GLint *weights, const char * _file, int _line);
void _glWeightfvARB(GLint size, const GLfloat *weights, const char * _file, int _line);
void _glWeightdvARB(GLint size, const GLdouble *weights, const char * _file, int _line);
void _glWeightubvARB(GLint size, const GLubyte *weights, const char * _file, int _line);
void _glWeightusvARB(GLint size, const GLushort *weights, const char * _file, int _line);
void _glWeightuivARB(GLint size, const GLuint *weights, const char * _file, int _line);
void _glWeightPointerARB(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glVertexBlendARB(GLint count, const char * _file, int _line);
void _glBindBufferARB(GLenum target, GLuint buffer, const char * _file, int _line);
void _glDeleteBuffersARB(GLsizei n, const GLuint *buffers, const char * _file, int _line);
void _glGenBuffersARB(GLsizei n, GLuint *buffers, const char * _file, int _line);
GLboolean _glIsBufferARB(GLuint buffer, const char * _file, int _line);
void _glBufferDataARB(GLenum target, GLsizeiptrARB size, const void *data, GLenum usage, const char * _file, int _line);
void _glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void *data, const char * _file, int _line);
void _glGetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void *data, const char * _file, int _line);
void * _glMapBufferARB(GLenum target, GLenum access, const char * _file, int _line);
GLboolean _glUnmapBufferARB(GLenum target, const char * _file, int _line);
void _glGetBufferParameterivARB(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetBufferPointervARB(GLenum target, GLenum pname, void **params, const char * _file, int _line);
void _glVertexAttrib1dARB(GLuint index, GLdouble x, const char * _file, int _line);
void _glVertexAttrib1dvARB(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib1fARB(GLuint index, GLfloat x, const char * _file, int _line);
void _glVertexAttrib1fvARB(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib1sARB(GLuint index, GLshort x, const char * _file, int _line);
void _glVertexAttrib1svARB(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexAttrib2dvARB(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line);
void _glVertexAttrib2fvARB(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y, const char * _file, int _line);
void _glVertexAttrib2svARB(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexAttrib3dvARB(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glVertexAttrib3fvARB(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glVertexAttrib3svARB(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4NbvARB(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttrib4NivARB(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttrib4NsvARB(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line);
void _glVertexAttrib4NubvARB(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttrib4NuivARB(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttrib4NusvARB(GLuint index, const GLushort *v, const char * _file, int _line);
void _glVertexAttrib4bvARB(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexAttrib4dvARB(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glVertexAttrib4fvARB(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib4ivARB(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line);
void _glVertexAttrib4svARB(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4ubvARB(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttrib4uivARB(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttrib4usvARB(GLuint index, const GLushort *v, const char * _file, int _line);
void _glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glEnableVertexAttribArrayARB(GLuint index, const char * _file, int _line);
void _glDisableVertexAttribArrayARB(GLuint index, const char * _file, int _line);
void _glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVertexAttribivARB(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribPointervARB(GLuint index, GLenum pname, void **pointer, const char * _file, int _line);
void _glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB *name, const char * _file, int _line);
void _glGetActiveAttribARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name, const char * _file, int _line);
GLint _glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB *name, const char * _file, int _line);
void _glDepthRangeArraydvNV(GLuint first, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glDepthRangeIndexeddNV(GLuint index, GLdouble n, GLdouble f, const char * _file, int _line);
void _glWindowPos2dARB(GLdouble x, GLdouble y, const char * _file, int _line);
void _glWindowPos2dvARB(const GLdouble *v, const char * _file, int _line);
void _glWindowPos2fARB(GLfloat x, GLfloat y, const char * _file, int _line);
void _glWindowPos2fvARB(const GLfloat *v, const char * _file, int _line);
void _glWindowPos2iARB(GLint x, GLint y, const char * _file, int _line);
void _glWindowPos2ivARB(const GLint *v, const char * _file, int _line);
void _glWindowPos2sARB(GLshort x, GLshort y, const char * _file, int _line);
void _glWindowPos2svARB(const GLshort *v, const char * _file, int _line);
void _glWindowPos3dARB(GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glWindowPos3dvARB(const GLdouble *v, const char * _file, int _line);
void _glWindowPos3fARB(GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glWindowPos3fvARB(const GLfloat *v, const char * _file, int _line);
void _glWindowPos3iARB(GLint x, GLint y, GLint z, const char * _file, int _line);
void _glWindowPos3ivARB(const GLint *v, const char * _file, int _line);
void _glWindowPos3sARB(GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glWindowPos3svARB(const GLshort *v, const char * _file, int _line);
void _glDrawBuffersATI(GLsizei n, const GLenum *bufs, const char * _file, int _line);
void _glElementPointerATI(GLenum type, const void *pointer, const char * _file, int _line);
void _glDrawElementArrayATI(GLenum mode, GLsizei count, const char * _file, int _line);
void _glDrawRangeElementArrayATI(GLenum mode, GLuint start, GLuint end, GLsizei count, const char * _file, int _line);
void _glTexBumpParameterivATI(GLenum pname, const GLint *param, const char * _file, int _line);
void _glTexBumpParameterfvATI(GLenum pname, const GLfloat *param, const char * _file, int _line);
void _glGetTexBumpParameterivATI(GLenum pname, GLint *param, const char * _file, int _line);
void _glGetTexBumpParameterfvATI(GLenum pname, GLfloat *param, const char * _file, int _line);
GLuint _glGenFragmentShadersATI(GLuint range, const char * _file, int _line);
void _glBindFragmentShaderATI(GLuint id, const char * _file, int _line);
void _glDeleteFragmentShaderATI(GLuint id, const char * _file, int _line);
void _glBeginFragmentShaderATI(const char * _file, int _line);
void _glEndFragmentShaderATI(const char * _file, int _line);
void _glPassTexCoordATI(GLuint dst, GLuint coord, GLenum swizzle, const char * _file, int _line);
void _glSampleMapATI(GLuint dst, GLuint interp, GLenum swizzle, const char * _file, int _line);
void _glColorFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, const char * _file, int _line);
void _glColorFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, const char * _file, int _line);
void _glColorFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod, const char * _file, int _line);
void _glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, const char * _file, int _line);
void _glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, const char * _file, int _line);
void _glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod, const char * _file, int _line);
void _glSetFragmentShaderConstantATI(GLuint dst, const GLfloat *value, const char * _file, int _line);
void * _glMapObjectBufferATI(GLuint buffer, const char * _file, int _line);
void _glUnmapObjectBufferATI(GLuint buffer, const char * _file, int _line);
void _glPNTrianglesiATI(GLenum pname, GLint param, const char * _file, int _line);
void _glPNTrianglesfATI(GLenum pname, GLfloat param, const char * _file, int _line);
void _glStencilOpSeparateATI(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass, const char * _file, int _line);
void _glStencilFuncSeparateATI(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask, const char * _file, int _line);
GLuint _glNewObjectBufferATI(GLsizei size, const void *pointer, GLenum usage, const char * _file, int _line);
GLboolean _glIsObjectBufferATI(GLuint buffer, const char * _file, int _line);
void _glUpdateObjectBufferATI(GLuint buffer, GLuint offset, GLsizei size, const void *pointer, GLenum preserve, const char * _file, int _line);
void _glGetObjectBufferfvATI(GLuint buffer, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetObjectBufferivATI(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glFreeObjectBufferATI(GLuint buffer, const char * _file, int _line);
void _glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line);
void _glGetArrayObjectfvATI(GLenum array, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetArrayObjectivATI(GLenum array, GLenum pname, GLint *params, const char * _file, int _line);
void _glVariantArrayObjectATI(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line);
void _glGetVariantArrayObjectfvATI(GLuint id, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVariantArrayObjectivATI(GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glVertexAttribArrayObjectATI(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset, const char * _file, int _line);
void _glGetVertexAttribArrayObjectfvATI(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVertexAttribArrayObjectivATI(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glVertexStream1sATI(GLenum stream, GLshort x, const char * _file, int _line);
void _glVertexStream1svATI(GLenum stream, const GLshort *coords, const char * _file, int _line);
void _glVertexStream1iATI(GLenum stream, GLint x, const char * _file, int _line);
void _glVertexStream1ivATI(GLenum stream, const GLint *coords, const char * _file, int _line);
void _glVertexStream1fATI(GLenum stream, GLfloat x, const char * _file, int _line);
void _glVertexStream1fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line);
void _glVertexStream1dATI(GLenum stream, GLdouble x, const char * _file, int _line);
void _glVertexStream1dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line);
void _glVertexStream2sATI(GLenum stream, GLshort x, GLshort y, const char * _file, int _line);
void _glVertexStream2svATI(GLenum stream, const GLshort *coords, const char * _file, int _line);
void _glVertexStream2iATI(GLenum stream, GLint x, GLint y, const char * _file, int _line);
void _glVertexStream2ivATI(GLenum stream, const GLint *coords, const char * _file, int _line);
void _glVertexStream2fATI(GLenum stream, GLfloat x, GLfloat y, const char * _file, int _line);
void _glVertexStream2fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line);
void _glVertexStream2dATI(GLenum stream, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexStream2dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line);
void _glVertexStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glVertexStream3svATI(GLenum stream, const GLshort *coords, const char * _file, int _line);
void _glVertexStream3iATI(GLenum stream, GLint x, GLint y, GLint z, const char * _file, int _line);
void _glVertexStream3ivATI(GLenum stream, const GLint *coords, const char * _file, int _line);
void _glVertexStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glVertexStream3fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line);
void _glVertexStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexStream3dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line);
void _glVertexStream4sATI(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line);
void _glVertexStream4svATI(GLenum stream, const GLshort *coords, const char * _file, int _line);
void _glVertexStream4iATI(GLenum stream, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glVertexStream4ivATI(GLenum stream, const GLint *coords, const char * _file, int _line);
void _glVertexStream4fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glVertexStream4fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line);
void _glVertexStream4dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexStream4dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line);
void _glNormalStream3bATI(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz, const char * _file, int _line);
void _glNormalStream3bvATI(GLenum stream, const GLbyte *coords, const char * _file, int _line);
void _glNormalStream3sATI(GLenum stream, GLshort nx, GLshort ny, GLshort nz, const char * _file, int _line);
void _glNormalStream3svATI(GLenum stream, const GLshort *coords, const char * _file, int _line);
void _glNormalStream3iATI(GLenum stream, GLint nx, GLint ny, GLint nz, const char * _file, int _line);
void _glNormalStream3ivATI(GLenum stream, const GLint *coords, const char * _file, int _line);
void _glNormalStream3fATI(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz, const char * _file, int _line);
void _glNormalStream3fvATI(GLenum stream, const GLfloat *coords, const char * _file, int _line);
void _glNormalStream3dATI(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz, const char * _file, int _line);
void _glNormalStream3dvATI(GLenum stream, const GLdouble *coords, const char * _file, int _line);
void _glClientActiveVertexStreamATI(GLenum stream, const char * _file, int _line);
void _glVertexBlendEnviATI(GLenum pname, GLint param, const char * _file, int _line);
void _glVertexBlendEnvfATI(GLenum pname, GLfloat param, const char * _file, int _line);
void _glEGLImageTargetTexStorageEXT(GLenum target, GLeglImageOES image, const GLint* attrib_list, const char * _file, int _line);
void _glEGLImageTargetTextureStorageEXT(GLuint texture, GLeglImageOES image, const GLint* attrib_list, const char * _file, int _line);
void _glUniformBufferEXT(GLuint program, GLint location, GLuint buffer, const char * _file, int _line);
GLint _glGetUniformBufferSizeEXT(GLuint program, GLint location, const char * _file, int _line);
GLintptr _glGetUniformOffsetEXT(GLuint program, GLint location, const char * _file, int _line);
void _glBlendColorEXT(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char * _file, int _line);
void _glBlendEquationSeparateEXT(GLenum modeRGB, GLenum modeAlpha, const char * _file, int _line);
void _glBlendFuncSeparateEXT(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line);
void _glBlendEquationEXT(GLenum mode, const char * _file, int _line);
void _glColorSubTableEXT(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glCopyColorSubTableEXT(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glLockArraysEXT(GLint first, GLsizei count, const char * _file, int _line);
void _glUnlockArraysEXT(const char * _file, int _line);
void _glConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *image, const char * _file, int _line);
void _glConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *image, const char * _file, int _line);
void _glConvolutionParameterfEXT(GLenum target, GLenum pname, GLfloat params, const char * _file, int _line);
void _glConvolutionParameterfvEXT(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glConvolutionParameteriEXT(GLenum target, GLenum pname, GLint params, const char * _file, int _line);
void _glConvolutionParameterivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glCopyConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetConvolutionFilterEXT(GLenum target, GLenum format, GLenum type, void *image, const char * _file, int _line);
void _glGetConvolutionParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetConvolutionParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetSeparableFilterEXT(GLenum target, GLenum format, GLenum type, void *row, void *column, void *span, const char * _file, int _line);
void _glSeparableFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *row, const void *column, const char * _file, int _line);
void _glTangent3bEXT(GLbyte tx, GLbyte ty, GLbyte tz, const char * _file, int _line);
void _glTangent3bvEXT(const GLbyte *v, const char * _file, int _line);
void _glTangent3dEXT(GLdouble tx, GLdouble ty, GLdouble tz, const char * _file, int _line);
void _glTangent3dvEXT(const GLdouble *v, const char * _file, int _line);
void _glTangent3fEXT(GLfloat tx, GLfloat ty, GLfloat tz, const char * _file, int _line);
void _glTangent3fvEXT(const GLfloat *v, const char * _file, int _line);
void _glTangent3iEXT(GLint tx, GLint ty, GLint tz, const char * _file, int _line);
void _glTangent3ivEXT(const GLint *v, const char * _file, int _line);
void _glTangent3sEXT(GLshort tx, GLshort ty, GLshort tz, const char * _file, int _line);
void _glTangent3svEXT(const GLshort *v, const char * _file, int _line);
void _glBinormal3bEXT(GLbyte bx, GLbyte by, GLbyte bz, const char * _file, int _line);
void _glBinormal3bvEXT(const GLbyte *v, const char * _file, int _line);
void _glBinormal3dEXT(GLdouble bx, GLdouble by, GLdouble bz, const char * _file, int _line);
void _glBinormal3dvEXT(const GLdouble *v, const char * _file, int _line);
void _glBinormal3fEXT(GLfloat bx, GLfloat by, GLfloat bz, const char * _file, int _line);
void _glBinormal3fvEXT(const GLfloat *v, const char * _file, int _line);
void _glBinormal3iEXT(GLint bx, GLint by, GLint bz, const char * _file, int _line);
void _glBinormal3ivEXT(const GLint *v, const char * _file, int _line);
void _glBinormal3sEXT(GLshort bx, GLshort by, GLshort bz, const char * _file, int _line);
void _glBinormal3svEXT(const GLshort *v, const char * _file, int _line);
void _glTangentPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glBinormalPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glCopyTexImage1DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line);
void _glCopyTexImage2DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line);
void _glCopyTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glCopyTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glCullParameterdvEXT(GLenum pname, GLdouble *params, const char * _file, int _line);
void _glCullParameterfvEXT(GLenum pname, GLfloat *params, const char * _file, int _line);
void _glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label, const char * _file, int _line);
void _glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line);
void _glInsertEventMarkerEXT(GLsizei length, const GLchar *marker, const char * _file, int _line);
void _glPushGroupMarkerEXT(GLsizei length, const GLchar *marker, const char * _file, int _line);
void _glPopGroupMarkerEXT(const char * _file, int _line);
void _glDepthBoundsEXT(GLclampd zmin, GLclampd zmax, const char * _file, int _line);
void _glMatrixLoadfEXT(GLenum mode, const GLfloat *m, const char * _file, int _line);
void _glMatrixLoaddEXT(GLenum mode, const GLdouble *m, const char * _file, int _line);
void _glMatrixMultfEXT(GLenum mode, const GLfloat *m, const char * _file, int _line);
void _glMatrixMultdEXT(GLenum mode, const GLdouble *m, const char * _file, int _line);
void _glMatrixLoadIdentityEXT(GLenum mode, const char * _file, int _line);
void _glMatrixRotatefEXT(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glMatrixRotatedEXT(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glMatrixScalefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glMatrixScaledEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glMatrixTranslatefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glMatrixTranslatedEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glMatrixFrustumEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar, const char * _file, int _line);
void _glMatrixOrthoEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar, const char * _file, int _line);
void _glMatrixPopEXT(GLenum mode, const char * _file, int _line);
void _glMatrixPushEXT(GLenum mode, const char * _file, int _line);
void _glClientAttribDefaultEXT(GLbitfield mask, const char * _file, int _line);
void _glPushClientAttribDefaultEXT(GLbitfield mask, const char * _file, int _line);
void _glTextureParameterfEXT(GLuint texture, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glTextureParameteriEXT(GLuint texture, GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCopyTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line);
void _glCopyTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line);
void _glCopyTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line);
void _glGetTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTextureLevelParameterfvEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetTextureLevelParameterivEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line);
void _glTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCopyTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture, const char * _file, int _line);
void _glMultiTexCoordPointerEXT(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glMultiTexEnvfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glMultiTexEnviEXT(GLenum texunit, GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glMultiTexGendEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble param, const char * _file, int _line);
void _glMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLdouble *params, const char * _file, int _line);
void _glMultiTexGenfEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat param, const char * _file, int _line);
void _glMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glMultiTexGeniEXT(GLenum texunit, GLenum coord, GLenum pname, GLint param, const char * _file, int _line);
void _glMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, const GLint *params, const char * _file, int _line);
void _glGetMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glGetMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, GLint *params, const char * _file, int _line);
void _glMultiTexParameteriEXT(GLenum texunit, GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glMultiTexParameterfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCopyMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border, const char * _file, int _line);
void _glCopyMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border, const char * _file, int _line);
void _glCopyMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetMultiTexImageEXT(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void *pixels, const char * _file, int _line);
void _glGetMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMultiTexLevelParameterfvEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMultiTexLevelParameterivEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint *params, const char * _file, int _line);
void _glMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glCopyMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glEnableClientStateIndexedEXT(GLenum array, GLuint index, const char * _file, int _line);
void _glDisableClientStateIndexedEXT(GLenum array, GLuint index, const char * _file, int _line);
void _glGetFloatIndexedvEXT(GLenum target, GLuint index, GLfloat *data, const char * _file, int _line);
void _glGetDoubleIndexedvEXT(GLenum target, GLuint index, GLdouble *data, const char * _file, int _line);
void _glGetPointerIndexedvEXT(GLenum target, GLuint index, void **data, const char * _file, int _line);
void _glEnableIndexedEXT(GLenum target, GLuint index, const char * _file, int _line);
void _glDisableIndexedEXT(GLenum target, GLuint index, const char * _file, int _line);
GLboolean _glIsEnabledIndexedEXT(GLenum target, GLuint index, const char * _file, int _line);
void _glGetIntegerIndexedvEXT(GLenum target, GLuint index, GLint *data, const char * _file, int _line);
void _glGetBooleanIndexedvEXT(GLenum target, GLuint index, GLboolean *data, const char * _file, int _line);
void _glCompressedTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glGetCompressedTextureImageEXT(GLuint texture, GLenum target, GLint lod, void *img, const char * _file, int _line);
void _glCompressedMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glCompressedMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits, const char * _file, int _line);
void _glGetCompressedMultiTexImageEXT(GLenum texunit, GLenum target, GLint lod, void *img, const char * _file, int _line);
void _glMatrixLoadTransposefEXT(GLenum mode, const GLfloat *m, const char * _file, int _line);
void _glMatrixLoadTransposedEXT(GLenum mode, const GLdouble *m, const char * _file, int _line);
void _glMatrixMultTransposefEXT(GLenum mode, const GLfloat *m, const char * _file, int _line);
void _glMatrixMultTransposedEXT(GLenum mode, const GLdouble *m, const char * _file, int _line);
void _glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage, const char * _file, int _line);
void _glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line);
void * _glMapNamedBufferEXT(GLuint buffer, GLenum access, const char * _file, int _line);
GLboolean _glUnmapNamedBufferEXT(GLuint buffer, const char * _file, int _line);
void _glGetNamedBufferParameterivEXT(GLuint buffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetNamedBufferPointervEXT(GLuint buffer, GLenum pname, void **params, const char * _file, int _line);
void _glGetNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data, const char * _file, int _line);
void _glProgramUniform1fEXT(GLuint program, GLint location, GLfloat v0, const char * _file, int _line);
void _glProgramUniform2fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, const char * _file, int _line);
void _glProgramUniform3fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char * _file, int _line);
void _glProgramUniform4fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char * _file, int _line);
void _glProgramUniform1iEXT(GLuint program, GLint location, GLint v0, const char * _file, int _line);
void _glProgramUniform2iEXT(GLuint program, GLint location, GLint v0, GLint v1, const char * _file, int _line);
void _glProgramUniform3iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, const char * _file, int _line);
void _glProgramUniform4iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3, const char * _file, int _line);
void _glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value, const char * _file, int _line);
void _glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value, const char * _file, int _line);
void _glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char * _file, int _line);
void _glTextureBufferEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glMultiTexBufferEXT(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line);
void _glGetTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, GLuint *params, const char * _file, int _line);
void _glMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line);
void _glGetMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, GLuint *params, const char * _file, int _line);
void _glProgramUniform1uiEXT(GLuint program, GLint location, GLuint v0, const char * _file, int _line);
void _glProgramUniform2uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, const char * _file, int _line);
void _glProgramUniform3uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line);
void _glProgramUniform4uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line);
void _glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glNamedProgramLocalParameters4fvEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line);
void _glNamedProgramLocalParameterI4iEXT(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glNamedProgramLocalParameterI4ivEXT(GLuint program, GLenum target, GLuint index, const GLint *params, const char * _file, int _line);
void _glNamedProgramLocalParametersI4ivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line);
void _glNamedProgramLocalParameterI4uiEXT(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line);
void _glNamedProgramLocalParameterI4uivEXT(GLuint program, GLenum target, GLuint index, const GLuint *params, const char * _file, int _line);
void _glNamedProgramLocalParametersI4uivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line);
void _glGetNamedProgramLocalParameterIivEXT(GLuint program, GLenum target, GLuint index, GLint *params, const char * _file, int _line);
void _glGetNamedProgramLocalParameterIuivEXT(GLuint program, GLenum target, GLuint index, GLuint *params, const char * _file, int _line);
void _glEnableClientStateiEXT(GLenum array, GLuint index, const char * _file, int _line);
void _glDisableClientStateiEXT(GLenum array, GLuint index, const char * _file, int _line);
void _glGetFloati_vEXT(GLenum pname, GLuint index, GLfloat *params, const char * _file, int _line);
void _glGetDoublei_vEXT(GLenum pname, GLuint index, GLdouble *params, const char * _file, int _line);
void _glGetPointeri_vEXT(GLenum pname, GLuint index, void **params, const char * _file, int _line);
void _glNamedProgramStringEXT(GLuint program, GLenum target, GLenum format, GLsizei len, const void *string, const char * _file, int _line);
void _glNamedProgramLocalParameter4dEXT(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glNamedProgramLocalParameter4dvEXT(GLuint program, GLenum target, GLuint index, const GLdouble *params, const char * _file, int _line);
void _glNamedProgramLocalParameter4fEXT(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glNamedProgramLocalParameter4fvEXT(GLuint program, GLenum target, GLuint index, const GLfloat *params, const char * _file, int _line);
void _glGetNamedProgramLocalParameterdvEXT(GLuint program, GLenum target, GLuint index, GLdouble *params, const char * _file, int _line);
void _glGetNamedProgramLocalParameterfvEXT(GLuint program, GLenum target, GLuint index, GLfloat *params, const char * _file, int _line);
void _glGetNamedProgramivEXT(GLuint program, GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetNamedProgramStringEXT(GLuint program, GLenum target, GLenum pname, void *string, const char * _file, int _line);
void _glNamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
GLenum _glCheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target, const char * _file, int _line);
void _glNamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glNamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glNamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line);
void _glNamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line);
void _glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line);
void _glGenerateTextureMipmapEXT(GLuint texture, GLenum target, const char * _file, int _line);
void _glGenerateMultiTexMipmapEXT(GLenum texunit, GLenum target, const char * _file, int _line);
void _glFramebufferDrawBufferEXT(GLuint framebuffer, GLenum mode, const char * _file, int _line);
void _glFramebufferDrawBuffersEXT(GLuint framebuffer, GLsizei n, const GLenum *bufs, const char * _file, int _line);
void _glFramebufferReadBufferEXT(GLuint framebuffer, GLenum mode, const char * _file, int _line);
void _glGetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glNamedCopyBufferSubDataEXT(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line);
void _glNamedFramebufferTextureEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line);
void _glNamedFramebufferTextureLayerEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line);
void _glNamedFramebufferTextureFaceEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line);
void _glTextureRenderbufferEXT(GLuint texture, GLenum target, GLuint renderbuffer, const char * _file, int _line);
void _glMultiTexRenderbufferEXT(GLenum texunit, GLenum target, GLuint renderbuffer, const char * _file, int _line);
void _glVertexArrayVertexOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayIndexOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayNormalOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayFogCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArraySecondaryColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayVertexAttribOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glEnableVertexArrayEXT(GLuint vaobj, GLenum array, const char * _file, int _line);
void _glDisableVertexArrayEXT(GLuint vaobj, GLenum array, const char * _file, int _line);
void _glEnableVertexArrayAttribEXT(GLuint vaobj, GLuint index, const char * _file, int _line);
void _glDisableVertexArrayAttribEXT(GLuint vaobj, GLuint index, const char * _file, int _line);
void _glGetVertexArrayIntegervEXT(GLuint vaobj, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetVertexArrayPointervEXT(GLuint vaobj, GLenum pname, void **param, const char * _file, int _line);
void _glGetVertexArrayIntegeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, GLint *param, const char * _file, int _line);
void _glGetVertexArrayPointeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, void **param, const char * _file, int _line);
void * _glMapNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access, const char * _file, int _line);
void _glFlushMappedNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, const char * _file, int _line);
void _glNamedBufferStorageEXT(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags, const char * _file, int _line);
void _glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data, const char * _file, int _line);
void _glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param, const char * _file, int _line);
void _glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint *params, const char * _file, int _line);
void _glProgramUniform1dEXT(GLuint program, GLint location, GLdouble x, const char * _file, int _line);
void _glProgramUniform2dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, const char * _file, int _line);
void _glProgramUniform3dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glProgramUniform4dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glProgramUniform1dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform2dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform3dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniform4dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix2x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix2x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix3x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glProgramUniformMatrix4x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value, const char * _file, int _line);
void _glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, const char * _file, int _line);
void _glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glVertexArrayBindVertexBufferEXT(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, const char * _file, int _line);
void _glVertexArrayVertexAttribFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayVertexAttribIFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayVertexAttribLFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset, const char * _file, int _line);
void _glVertexArrayVertexAttribBindingEXT(GLuint vaobj, GLuint attribindex, GLuint bindingindex, const char * _file, int _line);
void _glVertexArrayVertexBindingDivisorEXT(GLuint vaobj, GLuint bindingindex, GLuint divisor, const char * _file, int _line);
void _glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset, const char * _file, int _line);
void _glTexturePageCommitmentEXT(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit, const char * _file, int _line);
void _glVertexArrayVertexAttribDivisorEXT(GLuint vaobj, GLuint index, GLuint divisor, const char * _file, int _line);
void _glColorMaskIndexedEXT(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a, const char * _file, int _line);
void _glDrawArraysInstancedEXT(GLenum mode, GLint start, GLsizei count, GLsizei primcount, const char * _file, int _line);
void _glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, const char * _file, int _line);
void _glDrawRangeElementsEXT(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, const char * _file, int _line);
void _glBufferStorageExternalEXT(GLenum target, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags, const char * _file, int _line);
void _glNamedBufferStorageExternalEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags, const char * _file, int _line);
void _glFogCoordfEXT(GLfloat coord, const char * _file, int _line);
void _glFogCoordfvEXT(const GLfloat *coord, const char * _file, int _line);
void _glFogCoorddEXT(GLdouble coord, const char * _file, int _line);
void _glFogCoorddvEXT(const GLdouble *coord, const char * _file, int _line);
void _glFogCoordPointerEXT(GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line);
void _glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
GLboolean _glIsRenderbufferEXT(GLuint renderbuffer, const char * _file, int _line);
void _glBindRenderbufferEXT(GLenum target, GLuint renderbuffer, const char * _file, int _line);
void _glDeleteRenderbuffersEXT(GLsizei n, const GLuint *renderbuffers, const char * _file, int _line);
void _glGenRenderbuffersEXT(GLsizei n, GLuint *renderbuffers, const char * _file, int _line);
void _glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
GLboolean _glIsFramebufferEXT(GLuint framebuffer, const char * _file, int _line);
void _glBindFramebufferEXT(GLenum target, GLuint framebuffer, const char * _file, int _line);
void _glDeleteFramebuffersEXT(GLsizei n, const GLuint *framebuffers, const char * _file, int _line);
void _glGenFramebuffersEXT(GLsizei n, GLuint *framebuffers, const char * _file, int _line);
GLenum _glCheckFramebufferStatusEXT(GLenum target, const char * _file, int _line);
void _glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset, const char * _file, int _line);
void _glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer, const char * _file, int _line);
void _glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint *params, const char * _file, int _line);
void _glGenerateMipmapEXT(GLenum target, const char * _file, int _line);
void _glProgramParameteriEXT(GLuint program, GLenum pname, GLint value, const char * _file, int _line);
void _glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line);
void _glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat *params, const char * _file, int _line);
void _glGetUniformuivEXT(GLuint program, GLint location, GLuint *params, const char * _file, int _line);
void _glBindFragDataLocationEXT(GLuint program, GLuint color, const GLchar *name, const char * _file, int _line);
GLint _glGetFragDataLocationEXT(GLuint program, const GLchar *name, const char * _file, int _line);
void _glUniform1uiEXT(GLint location, GLuint v0, const char * _file, int _line);
void _glUniform2uiEXT(GLint location, GLuint v0, GLuint v1, const char * _file, int _line);
void _glUniform3uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, const char * _file, int _line);
void _glUniform4uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3, const char * _file, int _line);
void _glUniform1uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform2uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform3uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glUniform4uivEXT(GLint location, GLsizei count, const GLuint *value, const char * _file, int _line);
void _glGetHistogramEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line);
void _glGetHistogramParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetHistogramParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMinmaxEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void *values, const char * _file, int _line);
void _glGetMinmaxParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMinmaxParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glHistogramEXT(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink, const char * _file, int _line);
void _glMinmaxEXT(GLenum target, GLenum internalformat, GLboolean sink, const char * _file, int _line);
void _glResetHistogramEXT(GLenum target, const char * _file, int _line);
void _glResetMinmaxEXT(GLenum target, const char * _file, int _line);
void _glIndexFuncEXT(GLenum func, GLclampf ref, const char * _file, int _line);
void _glIndexMaterialEXT(GLenum face, GLenum mode, const char * _file, int _line);
void _glApplyTextureEXT(GLenum mode, const char * _file, int _line);
void _glTextureLightEXT(GLenum pname, const char * _file, int _line);
void _glTextureMaterialEXT(GLenum face, GLenum mode, const char * _file, int _line);
void _glGetUnsignedBytevEXT(GLenum pname, GLubyte *data, const char * _file, int _line);
void _glGetUnsignedBytei_vEXT(GLenum target, GLuint index, GLubyte *data, const char * _file, int _line);
void _glDeleteMemoryObjectsEXT(GLsizei n, const GLuint *memoryObjects, const char * _file, int _line);
GLboolean _glIsMemoryObjectEXT(GLuint memoryObject, const char * _file, int _line);
void _glCreateMemoryObjectsEXT(GLsizei n, GLuint *memoryObjects, const char * _file, int _line);
void _glMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, const GLint *params, const char * _file, int _line);
void _glGetMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, GLint *params, const char * _file, int _line);
void _glTexStorageMem2DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTexStorageMem2DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTexStorageMem3DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTexStorageMem3DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glBufferStorageMemEXT(GLenum target, GLsizeiptr size, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureStorageMem2DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureStorageMem2DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureStorageMem3DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureStorageMem3DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glNamedBufferStorageMemEXT(GLuint buffer, GLsizeiptr size, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTexStorageMem1DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureStorageMem1DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glImportMemoryFdEXT(GLuint memory, GLuint64 size, GLenum handleType, GLint fd, const char * _file, int _line);
void _glImportMemoryWin32HandleEXT(GLuint memory, GLuint64 size, GLenum handleType, void *handle, const char * _file, int _line);
void _glImportMemoryWin32NameEXT(GLuint memory, GLuint64 size, GLenum handleType, const void *name, const char * _file, int _line);
void _glMultiDrawArraysEXT(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount, const char * _file, int _line);
void _glMultiDrawElementsEXT(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount, const char * _file, int _line);
void _glSampleMaskEXT(GLclampf value, GLboolean invert, const char * _file, int _line);
void _glSamplePatternEXT(GLenum pattern, const char * _file, int _line);
void _glColorTableEXT(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line);
void _glGetColorTableEXT(GLenum target, GLenum format, GLenum type, void *data, const char * _file, int _line);
void _glGetColorTableParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetColorTableParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glPixelTransformParameteriEXT(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glPixelTransformParameterfEXT(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glPixelTransformParameterivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glPixelTransformParameterfvEXT(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glGetPixelTransformParameterivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetPixelTransformParameterfvEXT(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glPointParameterfEXT(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPointParameterfvEXT(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glPolygonOffsetEXT(GLfloat factor, GLfloat bias, const char * _file, int _line);
void _glPolygonOffsetClampEXT(GLfloat factor, GLfloat units, GLfloat clamp, const char * _file, int _line);
void _glProvokingVertexEXT(GLenum mode, const char * _file, int _line);
void _glRasterSamplesEXT(GLuint samples, GLboolean fixedsamplelocations, const char * _file, int _line);
void _glSecondaryColor3bEXT(GLbyte red, GLbyte green, GLbyte blue, const char * _file, int _line);
void _glSecondaryColor3bvEXT(const GLbyte *v, const char * _file, int _line);
void _glSecondaryColor3dEXT(GLdouble red, GLdouble green, GLdouble blue, const char * _file, int _line);
void _glSecondaryColor3dvEXT(const GLdouble *v, const char * _file, int _line);
void _glSecondaryColor3fEXT(GLfloat red, GLfloat green, GLfloat blue, const char * _file, int _line);
void _glSecondaryColor3fvEXT(const GLfloat *v, const char * _file, int _line);
void _glSecondaryColor3iEXT(GLint red, GLint green, GLint blue, const char * _file, int _line);
void _glSecondaryColor3ivEXT(const GLint *v, const char * _file, int _line);
void _glSecondaryColor3sEXT(GLshort red, GLshort green, GLshort blue, const char * _file, int _line);
void _glSecondaryColor3svEXT(const GLshort *v, const char * _file, int _line);
void _glSecondaryColor3ubEXT(GLubyte red, GLubyte green, GLubyte blue, const char * _file, int _line);
void _glSecondaryColor3ubvEXT(const GLubyte *v, const char * _file, int _line);
void _glSecondaryColor3uiEXT(GLuint red, GLuint green, GLuint blue, const char * _file, int _line);
void _glSecondaryColor3uivEXT(const GLuint *v, const char * _file, int _line);
void _glSecondaryColor3usEXT(GLushort red, GLushort green, GLushort blue, const char * _file, int _line);
void _glSecondaryColor3usvEXT(const GLushort *v, const char * _file, int _line);
void _glSecondaryColorPointerEXT(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glGenSemaphoresEXT(GLsizei n, GLuint *semaphores, const char * _file, int _line);
void _glDeleteSemaphoresEXT(GLsizei n, const GLuint *semaphores, const char * _file, int _line);
GLboolean _glIsSemaphoreEXT(GLuint semaphore, const char * _file, int _line);
void _glSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, const GLuint64 *params, const char * _file, int _line);
void _glGetSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, GLuint64 *params, const char * _file, int _line);
void _glWaitSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint *buffers, GLuint numTextureBarriers, const GLuint *textures, const GLenum *srcLayouts, const char * _file, int _line);
void _glSignalSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint *buffers, GLuint numTextureBarriers, const GLuint *textures, const GLenum *dstLayouts, const char * _file, int _line);
void _glImportSemaphoreFdEXT(GLuint semaphore, GLenum handleType, GLint fd, const char * _file, int _line);
void _glImportSemaphoreWin32HandleEXT(GLuint semaphore, GLenum handleType, void *handle, const char * _file, int _line);
void _glImportSemaphoreWin32NameEXT(GLuint semaphore, GLenum handleType, const void *name, const char * _file, int _line);
void _glUseShaderProgramEXT(GLenum type, GLuint program, const char * _file, int _line);
void _glActiveProgramEXT(GLuint program, const char * _file, int _line);
GLuint _glCreateShaderProgramEXT(GLenum type, const GLchar *string, const char * _file, int _line);
void _glActiveShaderProgramEXT(GLuint pipeline, GLuint program, const char * _file, int _line);
void _glBindProgramPipelineEXT(GLuint pipeline, const char * _file, int _line);
GLuint _glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar **strings, const char * _file, int _line);
void _glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines, const char * _file, int _line);
void _glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines, const char * _file, int _line);
void _glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char * _file, int _line);
void _glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params, const char * _file, int _line);
GLboolean _glIsProgramPipelineEXT(GLuint pipeline, const char * _file, int _line);
void _glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program, const char * _file, int _line);
void _glValidateProgramPipelineEXT(GLuint pipeline, const char * _file, int _line);
void _glFramebufferFetchBarrierEXT(const char * _file, int _line);
void _glBindImageTextureEXT(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format, const char * _file, int _line);
void _glMemoryBarrierEXT(GLbitfield barriers, const char * _file, int _line);
void _glStencilClearTagEXT(GLsizei stencilTagBits, GLuint stencilClearTag, const char * _file, int _line);
void _glActiveStencilFaceEXT(GLenum face, const char * _file, int _line);
void _glTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexImage3DEXT(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glFramebufferTextureLayerEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, const char * _file, int _line);
void _glTexBufferEXT(GLenum target, GLenum internalformat, GLuint buffer, const char * _file, int _line);
void _glTexParameterIivEXT(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glTexParameterIuivEXT(GLenum target, GLenum pname, const GLuint *params, const char * _file, int _line);
void _glGetTexParameterIivEXT(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetTexParameterIuivEXT(GLenum target, GLenum pname, GLuint *params, const char * _file, int _line);
void _glClearColorIiEXT(GLint red, GLint green, GLint blue, GLint alpha, const char * _file, int _line);
void _glClearColorIuiEXT(GLuint red, GLuint green, GLuint blue, GLuint alpha, const char * _file, int _line);
GLboolean _glAreTexturesResidentEXT(GLsizei n, const GLuint *textures, GLboolean *residences, const char * _file, int _line);
void _glBindTextureEXT(GLenum target, GLuint texture, const char * _file, int _line);
void _glDeleteTexturesEXT(GLsizei n, const GLuint *textures, const char * _file, int _line);
void _glGenTexturesEXT(GLsizei n, GLuint *textures, const char * _file, int _line);
GLboolean _glIsTextureEXT(GLuint texture, const char * _file, int _line);
void _glPrioritizeTexturesEXT(GLsizei n, const GLuint *textures, const GLclampf *priorities, const char * _file, int _line);
void _glTextureNormalEXT(GLenum mode, const char * _file, int _line);
void _glGetQueryObjecti64vEXT(GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line);
void _glGetQueryObjectui64vEXT(GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line);
void _glBeginTransformFeedbackEXT(GLenum primitiveMode, const char * _file, int _line);
void _glEndTransformFeedbackEXT(const char * _file, int _line);
void _glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, const char * _file, int _line);
void _glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line);
void _glTransformFeedbackVaryingsEXT(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode, const char * _file, int _line);
void _glGetTransformFeedbackVaryingEXT(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line);
void _glArrayElementEXT(GLint i, const char * _file, int _line);
void _glColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line);
void _glDrawArraysEXT(GLenum mode, GLint first, GLsizei count, const char * _file, int _line);
void _glEdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean *pointer, const char * _file, int _line);
void _glGetPointervEXT(GLenum pname, void **params, const char * _file, int _line);
void _glIndexPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line);
void _glNormalPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line);
void _glTexCoordPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line);
void _glVertexPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer, const char * _file, int _line);
void _glVertexAttribL1dEXT(GLuint index, GLdouble x, const char * _file, int _line);
void _glVertexAttribL2dEXT(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexAttribL3dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexAttribL4dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexAttribL1dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL2dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL3dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribL4dvEXT(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribLPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glGetVertexAttribLdvEXT(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glBeginVertexShaderEXT(const char * _file, int _line);
void _glEndVertexShaderEXT(const char * _file, int _line);
void _glBindVertexShaderEXT(GLuint id, const char * _file, int _line);
GLuint _glGenVertexShadersEXT(GLuint range, const char * _file, int _line);
void _glDeleteVertexShaderEXT(GLuint id, const char * _file, int _line);
void _glShaderOp1EXT(GLenum op, GLuint res, GLuint arg1, const char * _file, int _line);
void _glShaderOp2EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, const char * _file, int _line);
void _glShaderOp3EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3, const char * _file, int _line);
void _glSwizzleEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW, const char * _file, int _line);
void _glWriteMaskEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW, const char * _file, int _line);
void _glInsertComponentEXT(GLuint res, GLuint src, GLuint num, const char * _file, int _line);
void _glExtractComponentEXT(GLuint res, GLuint src, GLuint num, const char * _file, int _line);
GLuint _glGenSymbolsEXT(GLenum datatype, GLenum storagetype, GLenum range, GLuint components, const char * _file, int _line);
void _glSetInvariantEXT(GLuint id, GLenum type, const void *addr, const char * _file, int _line);
void _glSetLocalConstantEXT(GLuint id, GLenum type, const void *addr, const char * _file, int _line);
void _glVariantbvEXT(GLuint id, const GLbyte *addr, const char * _file, int _line);
void _glVariantsvEXT(GLuint id, const GLshort *addr, const char * _file, int _line);
void _glVariantivEXT(GLuint id, const GLint *addr, const char * _file, int _line);
void _glVariantfvEXT(GLuint id, const GLfloat *addr, const char * _file, int _line);
void _glVariantdvEXT(GLuint id, const GLdouble *addr, const char * _file, int _line);
void _glVariantubvEXT(GLuint id, const GLubyte *addr, const char * _file, int _line);
void _glVariantusvEXT(GLuint id, const GLushort *addr, const char * _file, int _line);
void _glVariantuivEXT(GLuint id, const GLuint *addr, const char * _file, int _line);
void _glVariantPointerEXT(GLuint id, GLenum type, GLuint stride, const void *addr, const char * _file, int _line);
void _glEnableVariantClientStateEXT(GLuint id, const char * _file, int _line);
void _glDisableVariantClientStateEXT(GLuint id, const char * _file, int _line);
GLuint _glBindLightParameterEXT(GLenum light, GLenum value, const char * _file, int _line);
GLuint _glBindMaterialParameterEXT(GLenum face, GLenum value, const char * _file, int _line);
GLuint _glBindTexGenParameterEXT(GLenum unit, GLenum coord, GLenum value, const char * _file, int _line);
GLuint _glBindTextureUnitParameterEXT(GLenum unit, GLenum value, const char * _file, int _line);
GLuint _glBindParameterEXT(GLenum value, const char * _file, int _line);
GLboolean _glIsVariantEnabledEXT(GLuint id, GLenum cap, const char * _file, int _line);
void _glGetVariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line);
void _glGetVariantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line);
void _glGetVariantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line);
void _glGetVariantPointervEXT(GLuint id, GLenum value, void **data, const char * _file, int _line);
void _glGetInvariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line);
void _glGetInvariantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line);
void _glGetInvariantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line);
void _glGetLocalConstantBooleanvEXT(GLuint id, GLenum value, GLboolean *data, const char * _file, int _line);
void _glGetLocalConstantIntegervEXT(GLuint id, GLenum value, GLint *data, const char * _file, int _line);
void _glGetLocalConstantFloatvEXT(GLuint id, GLenum value, GLfloat *data, const char * _file, int _line);
void _glVertexWeightfEXT(GLfloat weight, const char * _file, int _line);
void _glVertexWeightfvEXT(const GLfloat *weight, const char * _file, int _line);
void _glVertexWeightPointerEXT(GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
GLboolean _glAcquireKeyedMutexWin32EXT(GLuint memory, GLuint64 key, GLuint timeout, const char * _file, int _line);
GLboolean _glReleaseKeyedMutexWin32EXT(GLuint memory, GLuint64 key, const char * _file, int _line);
void _glWindowRectanglesEXT(GLenum mode, GLsizei count, const GLint *box, const char * _file, int _line);
GLsync _glImportSyncEXT(GLenum external_sync_type, GLintptr external_sync, GLbitfield flags, const char * _file, int _line);
void _glFrameTerminatorGREMEDY(const char * _file, int _line);
void _glStringMarkerGREMEDY(GLsizei len, const void *string, const char * _file, int _line);
void _glImageTransformParameteriHP(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glImageTransformParameterfHP(GLenum target, GLenum pname, GLfloat param, const char * _file, int _line);
void _glImageTransformParameterivHP(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glImageTransformParameterfvHP(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glGetImageTransformParameterivHP(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetImageTransformParameterfvHP(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glMultiModeDrawArraysIBM(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride, const char * _file, int _line);
void _glMultiModeDrawElementsIBM(const GLenum *mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount, GLint modestride, const char * _file, int _line);
void _glFlushStaticDataIBM(GLenum target, const char * _file, int _line);
void _glColorPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glSecondaryColorPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glEdgeFlagPointerListIBM(GLint stride, const GLboolean **pointer, GLint ptrstride, const char * _file, int _line);
void _glFogCoordPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glIndexPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glNormalPointerListIBM(GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glTexCoordPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glVertexPointerListIBM(GLint size, GLenum type, GLint stride, const void **pointer, GLint ptrstride, const char * _file, int _line);
void _glBlendFuncSeparateINGR(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha, const char * _file, int _line);
void _glApplyFramebufferAttachmentCMAAINTEL(const char * _file, int _line);
void _glSyncTextureINTEL(GLuint texture, const char * _file, int _line);
void _glUnmapTexture2DINTEL(GLuint texture, GLint level, const char * _file, int _line);
void * _glMapTexture2DINTEL(GLuint texture, GLint level, GLbitfield access, GLint *stride, GLenum *layout, const char * _file, int _line);
void _glVertexPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line);
void _glNormalPointervINTEL(GLenum type, const void **pointer, const char * _file, int _line);
void _glColorPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line);
void _glTexCoordPointervINTEL(GLint size, GLenum type, const void **pointer, const char * _file, int _line);
void _glBeginPerfQueryINTEL(GLuint queryHandle, const char * _file, int _line);
void _glCreatePerfQueryINTEL(GLuint queryId, GLuint *queryHandle, const char * _file, int _line);
void _glDeletePerfQueryINTEL(GLuint queryHandle, const char * _file, int _line);
void _glEndPerfQueryINTEL(GLuint queryHandle, const char * _file, int _line);
void _glGetFirstPerfQueryIdINTEL(GLuint *queryId, const char * _file, int _line);
void _glGetNextPerfQueryIdINTEL(GLuint queryId, GLuint *nextQueryId, const char * _file, int _line);
void _glGetPerfCounterInfoINTEL(GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar *counterName, GLuint counterDescLength, GLchar *counterDesc, GLuint *counterOffset, GLuint *counterDataSize, GLuint *counterTypeEnum, GLuint *counterDataTypeEnum, GLuint64 *rawCounterMaxValue, const char * _file, int _line);
void _glGetPerfQueryDataINTEL(GLuint queryHandle, GLuint flags, GLsizei dataSize, void *data, GLuint *bytesWritten, const char * _file, int _line);
void _glGetPerfQueryIdByNameINTEL(GLchar *queryName, GLuint *queryId, const char * _file, int _line);
void _glGetPerfQueryInfoINTEL(GLuint queryId, GLuint queryNameLength, GLchar *queryName, GLuint *dataSize, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask, const char * _file, int _line);
void _glBlendBarrierKHR(const char * _file, int _line);
void _glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line);
void _glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line);
void _glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam, const char * _file, int _line);
GLuint _glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line);
void _glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message, const char * _file, int _line);
void _glPopDebugGroup(const char * _file, int _line);
void _glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label, const char * _file, int _line);
void _glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line);
void _glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label, const char * _file, int _line);
void _glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line);
void _glGetPointerv(GLenum pname, void **params, const char * _file, int _line);
void _glDebugMessageControlKHR(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled, const char * _file, int _line);
void _glDebugMessageInsertKHR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf, const char * _file, int _line);
void _glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam, const char * _file, int _line);
GLuint _glGetDebugMessageLogKHR(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog, const char * _file, int _line);
void _glPushDebugGroupKHR(GLenum source, GLuint id, GLsizei length, const GLchar *message, const char * _file, int _line);
void _glPopDebugGroupKHR(const char * _file, int _line);
void _glObjectLabelKHR(GLenum identifier, GLuint name, GLsizei length, const GLchar *label, const char * _file, int _line);
void _glGetObjectLabelKHR(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line);
void _glObjectPtrLabelKHR(const void *ptr, GLsizei length, const GLchar *label, const char * _file, int _line);
void _glGetObjectPtrLabelKHR(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label, const char * _file, int _line);
void _glGetPointervKHR(GLenum pname, void **params, const char * _file, int _line);
void _glMaxShaderCompilerThreadsKHR(GLuint count, const char * _file, int _line);
GLenum _glGetGraphicsResetStatus(const char * _file, int _line);
void _glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line);
void _glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line);
void _glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line);
void _glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line);
GLenum _glGetGraphicsResetStatusKHR(const char * _file, int _line);
void _glReadnPixelsKHR(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data, const char * _file, int _line);
void _glGetnUniformfvKHR(GLuint program, GLint location, GLsizei bufSize, GLfloat *params, const char * _file, int _line);
void _glGetnUniformivKHR(GLuint program, GLint location, GLsizei bufSize, GLint *params, const char * _file, int _line);
void _glGetnUniformuivKHR(GLuint program, GLint location, GLsizei bufSize, GLuint *params, const char * _file, int _line);
void _glFramebufferParameteriMESA(GLenum target, GLenum pname, GLint param, const char * _file, int _line);
void _glGetFramebufferParameterivMESA(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glResizeBuffersMESA(const char * _file, int _line);
void _glWindowPos2dMESA(GLdouble x, GLdouble y, const char * _file, int _line);
void _glWindowPos2dvMESA(const GLdouble *v, const char * _file, int _line);
void _glWindowPos2fMESA(GLfloat x, GLfloat y, const char * _file, int _line);
void _glWindowPos2fvMESA(const GLfloat *v, const char * _file, int _line);
void _glWindowPos2iMESA(GLint x, GLint y, const char * _file, int _line);
void _glWindowPos2ivMESA(const GLint *v, const char * _file, int _line);
void _glWindowPos2sMESA(GLshort x, GLshort y, const char * _file, int _line);
void _glWindowPos2svMESA(const GLshort *v, const char * _file, int _line);
void _glWindowPos3dMESA(GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glWindowPos3dvMESA(const GLdouble *v, const char * _file, int _line);
void _glWindowPos3fMESA(GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glWindowPos3fvMESA(const GLfloat *v, const char * _file, int _line);
void _glWindowPos3iMESA(GLint x, GLint y, GLint z, const char * _file, int _line);
void _glWindowPos3ivMESA(const GLint *v, const char * _file, int _line);
void _glWindowPos3sMESA(GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glWindowPos3svMESA(const GLshort *v, const char * _file, int _line);
void _glWindowPos4dMESA(GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glWindowPos4dvMESA(const GLdouble *v, const char * _file, int _line);
void _glWindowPos4fMESA(GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glWindowPos4fvMESA(const GLfloat *v, const char * _file, int _line);
void _glWindowPos4iMESA(GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glWindowPos4ivMESA(const GLint *v, const char * _file, int _line);
void _glWindowPos4sMESA(GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line);
void _glWindowPos4svMESA(const GLshort *v, const char * _file, int _line);
void _glBeginConditionalRenderNVX(GLuint id, const char * _file, int _line);
void _glEndConditionalRenderNVX(const char * _file, int _line);
void _glUploadGpuMaskNVX(GLbitfield mask, const char * _file, int _line);
void _glMulticastViewportArrayvNVX(GLuint gpu, GLuint first, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glMulticastViewportPositionWScaleNVX(GLuint gpu, GLuint index, GLfloat xcoeff, GLfloat ycoeff, const char * _file, int _line);
void _glMulticastScissorArrayvNVX(GLuint gpu, GLuint first, GLsizei count, const GLint *v, const char * _file, int _line);
GLuint _glAsyncCopyBufferSubDataNVX(GLsizei waitSemaphoreCount, const GLuint *waitSemaphoreArray, const GLuint64 *fenceValueArray, GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, GLsizei signalSemaphoreCount, const GLuint *signalSemaphoreArray, const GLuint64 *signalValueArray, const char * _file, int _line);
GLuint _glAsyncCopyImageSubDataNVX(GLsizei waitSemaphoreCount, const GLuint *waitSemaphoreArray, const GLuint64 *waitValueArray, GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, GLsizei signalSemaphoreCount, const GLuint *signalSemaphoreArray, const GLuint64 *signalValueArray, const char * _file, int _line);
void _glLGPUNamedBufferSubDataNVX(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line);
void _glLGPUCopyImageSubDataNVX(GLuint sourceGpu, GLbitfield destinationGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srxY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glLGPUInterlockNVX(const char * _file, int _line);
GLuint _glCreateProgressFenceNVX(const char * _file, int _line);
void _glSignalSemaphoreui64NVX(GLuint signalGpu, GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line);
void _glWaitSemaphoreui64NVX(GLuint waitGpu, GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line);
void _glClientWaitSemaphoreui64NVX(GLsizei fenceObjectCount, const GLuint *semaphoreArray, const GLuint64 *fenceValueArray, const char * _file, int _line);
void _glAlphaToCoverageDitherControlNV(GLenum mode, const char * _file, int _line);
void _glMultiDrawArraysIndirectBindlessNV(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line);
void _glMultiDrawElementsIndirectBindlessNV(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line);
void _glMultiDrawArraysIndirectBindlessCountNV(GLenum mode, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line);
void _glMultiDrawElementsIndirectBindlessCountNV(GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount, const char * _file, int _line);
GLuint64 _glGetTextureHandleNV(GLuint texture, const char * _file, int _line);
GLuint64 _glGetTextureSamplerHandleNV(GLuint texture, GLuint sampler, const char * _file, int _line);
void _glMakeTextureHandleResidentNV(GLuint64 handle, const char * _file, int _line);
void _glMakeTextureHandleNonResidentNV(GLuint64 handle, const char * _file, int _line);
GLuint64 _glGetImageHandleNV(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format, const char * _file, int _line);
void _glMakeImageHandleResidentNV(GLuint64 handle, GLenum access, const char * _file, int _line);
void _glMakeImageHandleNonResidentNV(GLuint64 handle, const char * _file, int _line);
void _glUniformHandleui64NV(GLint location, GLuint64 value, const char * _file, int _line);
void _glUniformHandleui64vNV(GLint location, GLsizei count, const GLuint64 *value, const char * _file, int _line);
void _glProgramUniformHandleui64NV(GLuint program, GLint location, GLuint64 value, const char * _file, int _line);
void _glProgramUniformHandleui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64 *values, const char * _file, int _line);
GLboolean _glIsTextureHandleResidentNV(GLuint64 handle, const char * _file, int _line);
GLboolean _glIsImageHandleResidentNV(GLuint64 handle, const char * _file, int _line);
void _glBlendParameteriNV(GLenum pname, GLint value, const char * _file, int _line);
void _glBlendBarrierNV(const char * _file, int _line);
void _glViewportPositionWScaleNV(GLuint index, GLfloat xcoeff, GLfloat ycoeff, const char * _file, int _line);
void _glCreateStatesNV(GLsizei n, GLuint *states, const char * _file, int _line);
void _glDeleteStatesNV(GLsizei n, const GLuint *states, const char * _file, int _line);
GLboolean _glIsStateNV(GLuint state, const char * _file, int _line);
void _glStateCaptureNV(GLuint state, GLenum mode, const char * _file, int _line);
GLuint _glGetCommandHeaderNV(GLenum tokenID, GLuint size, const char * _file, int _line);
GLushort _glGetStageIndexNV(GLenum shadertype, const char * _file, int _line);
void _glDrawCommandsNV(GLenum primitiveMode, GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, GLuint count, const char * _file, int _line);
void _glDrawCommandsAddressNV(GLenum primitiveMode, const GLuint64 *indirects, const GLsizei *sizes, GLuint count, const char * _file, int _line);
void _glDrawCommandsStatesNV(GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line);
void _glDrawCommandsStatesAddressNV(const GLuint64 *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line);
void _glCreateCommandListsNV(GLsizei n, GLuint *lists, const char * _file, int _line);
void _glDeleteCommandListsNV(GLsizei n, const GLuint *lists, const char * _file, int _line);
GLboolean _glIsCommandListNV(GLuint list, const char * _file, int _line);
void _glListDrawCommandsStatesClientNV(GLuint list, GLuint segment, const void **indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count, const char * _file, int _line);
void _glCommandListSegmentsNV(GLuint list, GLuint segments, const char * _file, int _line);
void _glCompileCommandListNV(GLuint list, const char * _file, int _line);
void _glCallCommandListNV(GLuint list, const char * _file, int _line);
void _glBeginConditionalRenderNV(GLuint id, GLenum mode, const char * _file, int _line);
void _glEndConditionalRenderNV(const char * _file, int _line);
void _glSubpixelPrecisionBiasNV(GLuint xbits, GLuint ybits, const char * _file, int _line);
void _glConservativeRasterParameterfNV(GLenum pname, GLfloat value, const char * _file, int _line);
void _glConservativeRasterParameteriNV(GLenum pname, GLint param, const char * _file, int _line);
void _glCopyImageSubDataNV(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth, const char * _file, int _line);
void _glDepthRangedNV(GLdouble zNear, GLdouble zFar, const char * _file, int _line);
void _glClearDepthdNV(GLdouble depth, const char * _file, int _line);
void _glDepthBoundsdNV(GLdouble zmin, GLdouble zmax, const char * _file, int _line);
void _glDrawTextureNV(GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1, const char * _file, int _line);
void _glDrawVkImageNV(GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1, const char * _file, int _line);
GLVULKANPROCNV _glGetVkProcAddrNV(const GLchar *name, const char * _file, int _line);
void _glWaitVkSemaphoreNV(GLuint64 vkSemaphore, const char * _file, int _line);
void _glSignalVkSemaphoreNV(GLuint64 vkSemaphore, const char * _file, int _line);
void _glSignalVkFenceNV(GLuint64 vkFence, const char * _file, int _line);
void _glMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void *points, const char * _file, int _line);
void _glMapParameterivNV(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glMapParameterfvNV(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glGetMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void *points, const char * _file, int _line);
void _glGetMapParameterivNV(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMapParameterfvNV(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetMapAttribParameterivNV(GLenum target, GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetMapAttribParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glEvalMapsNV(GLenum target, GLenum mode, const char * _file, int _line);
void _glGetMultisamplefvNV(GLenum pname, GLuint index, GLfloat *val, const char * _file, int _line);
void _glSampleMaskIndexedNV(GLuint index, GLbitfield mask, const char * _file, int _line);
void _glTexRenderbufferNV(GLenum target, GLuint renderbuffer, const char * _file, int _line);
void _glDeleteFencesNV(GLsizei n, const GLuint *fences, const char * _file, int _line);
void _glGenFencesNV(GLsizei n, GLuint *fences, const char * _file, int _line);
GLboolean _glIsFenceNV(GLuint fence, const char * _file, int _line);
GLboolean _glTestFenceNV(GLuint fence, const char * _file, int _line);
void _glGetFenceivNV(GLuint fence, GLenum pname, GLint *params, const char * _file, int _line);
void _glFinishFenceNV(GLuint fence, const char * _file, int _line);
void _glSetFenceNV(GLuint fence, GLenum condition, const char * _file, int _line);
void _glFragmentCoverageColorNV(GLuint color, const char * _file, int _line);
void _glProgramNamedParameter4fNV(GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glProgramNamedParameter4fvNV(GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v, const char * _file, int _line);
void _glProgramNamedParameter4dNV(GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glProgramNamedParameter4dvNV(GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v, const char * _file, int _line);
void _glGetProgramNamedParameterfvNV(GLuint id, GLsizei len, const GLubyte *name, GLfloat *params, const char * _file, int _line);
void _glGetProgramNamedParameterdvNV(GLuint id, GLsizei len, const GLubyte *name, GLdouble *params, const char * _file, int _line);
void _glCoverageModulationTableNV(GLsizei n, const GLfloat *v, const char * _file, int _line);
void _glGetCoverageModulationTableNV(GLsizei bufSize, GLfloat *v, const char * _file, int _line);
void _glCoverageModulationNV(GLenum components, const char * _file, int _line);
void _glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height, const char * _file, int _line);
void _glProgramVertexLimitNV(GLenum target, GLint limit, const char * _file, int _line);
void _glFramebufferTextureEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, const char * _file, int _line);
void _glFramebufferTextureFaceEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face, const char * _file, int _line);
void _glRenderGpuMaskNV(GLbitfield mask, const char * _file, int _line);
void _glMulticastBufferSubDataNV(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data, const char * _file, int _line);
void _glMulticastCopyBufferSubDataNV(GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size, const char * _file, int _line);
void _glMulticastCopyImageSubDataNV(GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth, const char * _file, int _line);
void _glMulticastBlitFramebufferNV(GLuint srcGpu, GLuint dstGpu, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char * _file, int _line);
void _glMulticastFramebufferSampleLocationsfvNV(GLuint gpu, GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glMulticastBarrierNV(const char * _file, int _line);
void _glMulticastWaitSyncNV(GLuint signalGpu, GLbitfield waitGpuMask, const char * _file, int _line);
void _glMulticastGetQueryObjectivNV(GLuint gpu, GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glMulticastGetQueryObjectuivNV(GLuint gpu, GLuint id, GLenum pname, GLuint *params, const char * _file, int _line);
void _glMulticastGetQueryObjecti64vNV(GLuint gpu, GLuint id, GLenum pname, GLint64 *params, const char * _file, int _line);
void _glMulticastGetQueryObjectui64vNV(GLuint gpu, GLuint id, GLenum pname, GLuint64 *params, const char * _file, int _line);
void _glProgramLocalParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glProgramLocalParameterI4ivNV(GLenum target, GLuint index, const GLint *params, const char * _file, int _line);
void _glProgramLocalParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line);
void _glProgramLocalParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line);
void _glProgramLocalParameterI4uivNV(GLenum target, GLuint index, const GLuint *params, const char * _file, int _line);
void _glProgramLocalParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line);
void _glProgramEnvParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glProgramEnvParameterI4ivNV(GLenum target, GLuint index, const GLint *params, const char * _file, int _line);
void _glProgramEnvParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint *params, const char * _file, int _line);
void _glProgramEnvParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line);
void _glProgramEnvParameterI4uivNV(GLenum target, GLuint index, const GLuint *params, const char * _file, int _line);
void _glProgramEnvParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint *params, const char * _file, int _line);
void _glGetProgramLocalParameterIivNV(GLenum target, GLuint index, GLint *params, const char * _file, int _line);
void _glGetProgramLocalParameterIuivNV(GLenum target, GLuint index, GLuint *params, const char * _file, int _line);
void _glGetProgramEnvParameterIivNV(GLenum target, GLuint index, GLint *params, const char * _file, int _line);
void _glGetProgramEnvParameterIuivNV(GLenum target, GLuint index, GLuint *params, const char * _file, int _line);
void _glProgramSubroutineParametersuivNV(GLenum target, GLsizei count, const GLuint *params, const char * _file, int _line);
void _glGetProgramSubroutineParameteruivNV(GLenum target, GLuint index, GLuint *param, const char * _file, int _line);
void _glVertex2hNV(GLhalfNV x, GLhalfNV y, const char * _file, int _line);
void _glVertex2hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glVertex3hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, const char * _file, int _line);
void _glVertex3hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glVertex4hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w, const char * _file, int _line);
void _glVertex4hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glNormal3hNV(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz, const char * _file, int _line);
void _glNormal3hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, const char * _file, int _line);
void _glColor3hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glColor4hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha, const char * _file, int _line);
void _glColor4hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glTexCoord1hNV(GLhalfNV s, const char * _file, int _line);
void _glTexCoord1hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glTexCoord2hNV(GLhalfNV s, GLhalfNV t, const char * _file, int _line);
void _glTexCoord2hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glTexCoord3hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, const char * _file, int _line);
void _glTexCoord3hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glTexCoord4hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q, const char * _file, int _line);
void _glTexCoord4hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glMultiTexCoord1hNV(GLenum target, GLhalfNV s, const char * _file, int _line);
void _glMultiTexCoord1hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line);
void _glMultiTexCoord2hNV(GLenum target, GLhalfNV s, GLhalfNV t, const char * _file, int _line);
void _glMultiTexCoord2hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line);
void _glMultiTexCoord3hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, const char * _file, int _line);
void _glMultiTexCoord3hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line);
void _glMultiTexCoord4hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q, const char * _file, int _line);
void _glMultiTexCoord4hvNV(GLenum target, const GLhalfNV *v, const char * _file, int _line);
void _glFogCoordhNV(GLhalfNV fog, const char * _file, int _line);
void _glFogCoordhvNV(const GLhalfNV *fog, const char * _file, int _line);
void _glSecondaryColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, const char * _file, int _line);
void _glSecondaryColor3hvNV(const GLhalfNV *v, const char * _file, int _line);
void _glVertexWeighthNV(GLhalfNV weight, const char * _file, int _line);
void _glVertexWeighthvNV(const GLhalfNV *weight, const char * _file, int _line);
void _glVertexAttrib1hNV(GLuint index, GLhalfNV x, const char * _file, int _line);
void _glVertexAttrib1hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttrib2hNV(GLuint index, GLhalfNV x, GLhalfNV y, const char * _file, int _line);
void _glVertexAttrib2hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttrib3hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, const char * _file, int _line);
void _glVertexAttrib3hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttrib4hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w, const char * _file, int _line);
void _glVertexAttrib4hvNV(GLuint index, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttribs1hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttribs2hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttribs3hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line);
void _glVertexAttribs4hvNV(GLuint index, GLsizei n, const GLhalfNV *v, const char * _file, int _line);
void _glGetInternalformatSampleivNV(GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei count, GLint *params, const char * _file, int _line);
void _glGetMemoryObjectDetachedResourcesuivNV(GLuint memory, GLenum pname, GLint first, GLsizei count, GLuint *params, const char * _file, int _line);
void _glResetMemoryObjectParameterNV(GLuint memory, GLenum pname, const char * _file, int _line);
void _glTexAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glBufferAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glTextureAttachMemoryNV(GLuint texture, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glNamedBufferAttachMemoryNV(GLuint buffer, GLuint memory, GLuint64 offset, const char * _file, int _line);
void _glBufferPageCommitmentMemNV(GLenum target, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit, const char * _file, int _line);
void _glTexPageCommitmentMemNV(GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit, const char * _file, int _line);
void _glNamedBufferPageCommitmentMemNV(GLuint buffer, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit, const char * _file, int _line);
void _glTexturePageCommitmentMemNV(GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit, const char * _file, int _line);
void _glDrawMeshTasksNV(GLuint first, GLuint count, const char * _file, int _line);
void _glDrawMeshTasksIndirectNV(GLintptr indirect, const char * _file, int _line);
void _glMultiDrawMeshTasksIndirectNV(GLintptr indirect, GLsizei drawcount, GLsizei stride, const char * _file, int _line);
void _glMultiDrawMeshTasksIndirectCountNV(GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride, const char * _file, int _line);
void _glGenOcclusionQueriesNV(GLsizei n, GLuint *ids, const char * _file, int _line);
void _glDeleteOcclusionQueriesNV(GLsizei n, const GLuint *ids, const char * _file, int _line);
GLboolean _glIsOcclusionQueryNV(GLuint id, const char * _file, int _line);
void _glBeginOcclusionQueryNV(GLuint id, const char * _file, int _line);
void _glEndOcclusionQueryNV(const char * _file, int _line);
void _glGetOcclusionQueryivNV(GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetOcclusionQueryuivNV(GLuint id, GLenum pname, GLuint *params, const char * _file, int _line);
void _glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLfloat *params, const char * _file, int _line);
void _glProgramBufferParametersIivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLint *params, const char * _file, int _line);
void _glProgramBufferParametersIuivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLuint *params, const char * _file, int _line);
GLuint _glGenPathsNV(GLsizei range, const char * _file, int _line);
void _glDeletePathsNV(GLuint path, GLsizei range, const char * _file, int _line);
GLboolean _glIsPathNV(GLuint path, const char * _file, int _line);
void _glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line);
void _glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line);
void _glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line);
void _glPathSubCoordsNV(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void *coords, const char * _file, int _line);
void _glPathStringNV(GLuint path, GLenum format, GLsizei length, const void *pathString, const char * _file, int _line);
void _glPathGlyphsNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line);
void _glPathGlyphRangeNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line);
void _glWeightPathsNV(GLuint resultPath, GLsizei numPaths, const GLuint *paths, const GLfloat *weights, const char * _file, int _line);
void _glCopyPathNV(GLuint resultPath, GLuint srcPath, const char * _file, int _line);
void _glInterpolatePathsNV(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight, const char * _file, int _line);
void _glTransformPathNV(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glPathParameterivNV(GLuint path, GLenum pname, const GLint *value, const char * _file, int _line);
void _glPathParameteriNV(GLuint path, GLenum pname, GLint value, const char * _file, int _line);
void _glPathParameterfvNV(GLuint path, GLenum pname, const GLfloat *value, const char * _file, int _line);
void _glPathParameterfNV(GLuint path, GLenum pname, GLfloat value, const char * _file, int _line);
void _glPathDashArrayNV(GLuint path, GLsizei dashCount, const GLfloat *dashArray, const char * _file, int _line);
void _glPathStencilFuncNV(GLenum func, GLint ref, GLuint mask, const char * _file, int _line);
void _glPathStencilDepthOffsetNV(GLfloat factor, GLfloat units, const char * _file, int _line);
void _glStencilFillPathNV(GLuint path, GLenum fillMode, GLuint mask, const char * _file, int _line);
void _glStencilStrokePathNV(GLuint path, GLint reference, GLuint mask, const char * _file, int _line);
void _glStencilFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glStencilStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glPathCoverDepthFuncNV(GLenum func, const char * _file, int _line);
void _glCoverFillPathNV(GLuint path, GLenum coverMode, const char * _file, int _line);
void _glCoverStrokePathNV(GLuint path, GLenum coverMode, const char * _file, int _line);
void _glCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glGetPathParameterivNV(GLuint path, GLenum pname, GLint *value, const char * _file, int _line);
void _glGetPathParameterfvNV(GLuint path, GLenum pname, GLfloat *value, const char * _file, int _line);
void _glGetPathCommandsNV(GLuint path, GLubyte *commands, const char * _file, int _line);
void _glGetPathCoordsNV(GLuint path, GLfloat *coords, const char * _file, int _line);
void _glGetPathDashArrayNV(GLuint path, GLfloat *dashArray, const char * _file, int _line);
void _glGetPathMetricsNV(GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics, const char * _file, int _line);
void _glGetPathMetricRangeNV(GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat *metrics, const char * _file, int _line);
void _glGetPathSpacingNV(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing, const char * _file, int _line);
GLboolean _glIsPointInFillPathNV(GLuint path, GLuint mask, GLfloat x, GLfloat y, const char * _file, int _line);
GLboolean _glIsPointInStrokePathNV(GLuint path, GLfloat x, GLfloat y, const char * _file, int _line);
GLfloat _glGetPathLengthNV(GLuint path, GLsizei startSegment, GLsizei numSegments, const char * _file, int _line);
GLboolean _glPointAlongPathNV(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY, const char * _file, int _line);
void _glMatrixLoad3x2fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glMatrixLoad3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glMatrixLoadTranspose3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glMatrixMult3x2fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glMatrixMult3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glMatrixMultTranspose3x3fNV(GLenum matrixMode, const GLfloat *m, const char * _file, int _line);
void _glStencilThenCoverFillPathNV(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode, const char * _file, int _line);
void _glStencilThenCoverStrokePathNV(GLuint path, GLint reference, GLuint mask, GLenum coverMode, const char * _file, int _line);
void _glStencilThenCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
void _glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues, const char * _file, int _line);
GLenum _glPathGlyphIndexRangeNV(GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2], const char * _file, int _line);
GLenum _glPathGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line);
GLenum _glPathMemoryGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void *fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale, const char * _file, int _line);
void _glProgramPathFragmentInputGenNV(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat *coeffs, const char * _file, int _line);
void _glGetProgramResourcefvNV(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLfloat *params, const char * _file, int _line);
void _glPathColorGenNV(GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat *coeffs, const char * _file, int _line);
void _glPathTexGenNV(GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat *coeffs, const char * _file, int _line);
void _glPathFogGenNV(GLenum genMode, const char * _file, int _line);
void _glGetPathColorGenivNV(GLenum color, GLenum pname, GLint *value, const char * _file, int _line);
void _glGetPathColorGenfvNV(GLenum color, GLenum pname, GLfloat *value, const char * _file, int _line);
void _glGetPathTexGenivNV(GLenum texCoordSet, GLenum pname, GLint *value, const char * _file, int _line);
void _glGetPathTexGenfvNV(GLenum texCoordSet, GLenum pname, GLfloat *value, const char * _file, int _line);
void _glPixelDataRangeNV(GLenum target, GLsizei length, const void *pointer, const char * _file, int _line);
void _glFlushPixelDataRangeNV(GLenum target, const char * _file, int _line);
void _glPointParameteriNV(GLenum pname, GLint param, const char * _file, int _line);
void _glPointParameterivNV(GLenum pname, const GLint *params, const char * _file, int _line);
void _glPresentFrameKeyedNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1, const char * _file, int _line);
void _glPresentFrameDualFillNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3, const char * _file, int _line);
void _glGetVideoivNV(GLuint video_slot, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVideouivNV(GLuint video_slot, GLenum pname, GLuint *params, const char * _file, int _line);
void _glGetVideoi64vNV(GLuint video_slot, GLenum pname, GLint64EXT *params, const char * _file, int _line);
void _glGetVideoui64vNV(GLuint video_slot, GLenum pname, GLuint64EXT *params, const char * _file, int _line);
void _glPrimitiveRestartNV(const char * _file, int _line);
void _glPrimitiveRestartIndexNV(GLuint index, const char * _file, int _line);
GLint _glQueryResourceNV(GLenum queryType, GLint tagId, GLuint count, GLint *buffer, const char * _file, int _line);
void _glGenQueryResourceTagNV(GLsizei n, GLint *tagIds, const char * _file, int _line);
void _glDeleteQueryResourceTagNV(GLsizei n, const GLint *tagIds, const char * _file, int _line);
void _glQueryResourceTagNV(GLint tagId, const GLchar *tagString, const char * _file, int _line);
void _glCombinerParameterfvNV(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glCombinerParameterfNV(GLenum pname, GLfloat param, const char * _file, int _line);
void _glCombinerParameterivNV(GLenum pname, const GLint *params, const char * _file, int _line);
void _glCombinerParameteriNV(GLenum pname, GLint param, const char * _file, int _line);
void _glCombinerInputNV(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage, const char * _file, int _line);
void _glCombinerOutputNV(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum, const char * _file, int _line);
void _glFinalCombinerInputNV(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage, const char * _file, int _line);
void _glGetCombinerInputParameterfvNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetCombinerInputParameterivNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetCombinerOutputParameterfvNV(GLenum stage, GLenum portion, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetCombinerOutputParameterivNV(GLenum stage, GLenum portion, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetFinalCombinerInputParameterfvNV(GLenum variable, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetFinalCombinerInputParameterivNV(GLenum variable, GLenum pname, GLint *params, const char * _file, int _line);
void _glCombinerStageParameterfvNV(GLenum stage, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glGetCombinerStageParameterfvNV(GLenum stage, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glFramebufferSampleLocationsfvNV(GLenum target, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glResolveDepthValuesNV(const char * _file, int _line);
void _glScissorExclusiveNV(GLint x, GLint y, GLsizei width, GLsizei height, const char * _file, int _line);
void _glScissorExclusiveArrayvNV(GLuint first, GLsizei count, const GLint *v, const char * _file, int _line);
void _glMakeBufferResidentNV(GLenum target, GLenum access, const char * _file, int _line);
void _glMakeBufferNonResidentNV(GLenum target, const char * _file, int _line);
GLboolean _glIsBufferResidentNV(GLenum target, const char * _file, int _line);
void _glMakeNamedBufferResidentNV(GLuint buffer, GLenum access, const char * _file, int _line);
void _glMakeNamedBufferNonResidentNV(GLuint buffer, const char * _file, int _line);
GLboolean _glIsNamedBufferResidentNV(GLuint buffer, const char * _file, int _line);
void _glGetBufferParameterui64vNV(GLenum target, GLenum pname, GLuint64EXT *params, const char * _file, int _line);
void _glGetNamedBufferParameterui64vNV(GLuint buffer, GLenum pname, GLuint64EXT *params, const char * _file, int _line);
void _glGetIntegerui64vNV(GLenum value, GLuint64EXT *result, const char * _file, int _line);
void _glUniformui64NV(GLint location, GLuint64EXT value, const char * _file, int _line);
void _glUniformui64vNV(GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glProgramUniformui64NV(GLuint program, GLint location, GLuint64EXT value, const char * _file, int _line);
void _glProgramUniformui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value, const char * _file, int _line);
void _glBindShadingRateImageNV(GLuint texture, const char * _file, int _line);
void _glGetShadingRateImagePaletteNV(GLuint viewport, GLuint entry, GLenum *rate, const char * _file, int _line);
void _glGetShadingRateSampleLocationivNV(GLenum rate, GLuint samples, GLuint index, GLint *location, const char * _file, int _line);
void _glShadingRateImageBarrierNV(GLboolean synchronize, const char * _file, int _line);
void _glShadingRateImagePaletteNV(GLuint viewport, GLuint first, GLsizei count, const GLenum *rates, const char * _file, int _line);
void _glShadingRateSampleOrderNV(GLenum order, const char * _file, int _line);
void _glShadingRateSampleOrderCustomNV(GLenum rate, GLuint samples, const GLint *locations, const char * _file, int _line);
void _glTextureBarrierNV(const char * _file, int _line);
void _glTexImage2DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glTexImage3DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glTextureImage2DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glTextureImage3DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glTextureImage2DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glTextureImage3DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, const char * _file, int _line);
void _glCreateSemaphoresNV(GLsizei n, GLuint *semaphores, const char * _file, int _line);
void _glSemaphoreParameterivNV(GLuint semaphore, GLenum pname, const GLint *params, const char * _file, int _line);
void _glGetSemaphoreParameterivNV(GLuint semaphore, GLenum pname, GLint *params, const char * _file, int _line);
void _glBeginTransformFeedbackNV(GLenum primitiveMode, const char * _file, int _line);
void _glEndTransformFeedbackNV(const char * _file, int _line);
void _glTransformFeedbackAttribsNV(GLsizei count, const GLint *attribs, GLenum bufferMode, const char * _file, int _line);
void _glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size, const char * _file, int _line);
void _glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, const char * _file, int _line);
void _glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer, const char * _file, int _line);
void _glTransformFeedbackVaryingsNV(GLuint program, GLsizei count, const GLint *locations, GLenum bufferMode, const char * _file, int _line);
void _glActiveVaryingNV(GLuint program, const GLchar *name, const char * _file, int _line);
GLint _glGetVaryingLocationNV(GLuint program, const GLchar *name, const char * _file, int _line);
void _glGetActiveVaryingNV(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name, const char * _file, int _line);
void _glGetTransformFeedbackVaryingNV(GLuint program, GLuint index, GLint *location, const char * _file, int _line);
void _glTransformFeedbackStreamAttribsNV(GLsizei count, const GLint *attribs, GLsizei nbuffers, const GLint *bufstreams, GLenum bufferMode, const char * _file, int _line);
void _glBindTransformFeedbackNV(GLenum target, GLuint id, const char * _file, int _line);
void _glDeleteTransformFeedbacksNV(GLsizei n, const GLuint *ids, const char * _file, int _line);
void _glGenTransformFeedbacksNV(GLsizei n, GLuint *ids, const char * _file, int _line);
GLboolean _glIsTransformFeedbackNV(GLuint id, const char * _file, int _line);
void _glPauseTransformFeedbackNV(const char * _file, int _line);
void _glResumeTransformFeedbackNV(const char * _file, int _line);
void _glDrawTransformFeedbackNV(GLenum mode, GLuint id, const char * _file, int _line);
void _glVDPAUInitNV(const void *vdpDevice, const void *getProcAddress, const char * _file, int _line);
void _glVDPAUFiniNV(const char * _file, int _line);
GLvdpauSurfaceNV _glVDPAURegisterVideoSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, const char * _file, int _line);
GLvdpauSurfaceNV _glVDPAURegisterOutputSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, const char * _file, int _line);
GLboolean _glVDPAUIsSurfaceNV(GLvdpauSurfaceNV surface, const char * _file, int _line);
void _glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV surface, const char * _file, int _line);
void _glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei count, GLsizei *length, GLint *values, const char * _file, int _line);
void _glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV surface, GLenum access, const char * _file, int _line);
void _glVDPAUMapSurfacesNV(GLsizei numSurfaces, const GLvdpauSurfaceNV *surfaces, const char * _file, int _line);
void _glVDPAUUnmapSurfacesNV(GLsizei numSurface, const GLvdpauSurfaceNV *surfaces, const char * _file, int _line);
GLvdpauSurfaceNV _glVDPAURegisterVideoSurfaceWithPictureStructureNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames, GLboolean isFrameStructure, const char * _file, int _line);
void _glFlushVertexArrayRangeNV(const char * _file, int _line);
void _glVertexArrayRangeNV(GLsizei length, const void *pointer, const char * _file, int _line);
void _glVertexAttribL1i64NV(GLuint index, GLint64EXT x, const char * _file, int _line);
void _glVertexAttribL2i64NV(GLuint index, GLint64EXT x, GLint64EXT y, const char * _file, int _line);
void _glVertexAttribL3i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, const char * _file, int _line);
void _glVertexAttribL4i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w, const char * _file, int _line);
void _glVertexAttribL1i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line);
void _glVertexAttribL2i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line);
void _glVertexAttribL3i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line);
void _glVertexAttribL4i64vNV(GLuint index, const GLint64EXT *v, const char * _file, int _line);
void _glVertexAttribL1ui64NV(GLuint index, GLuint64EXT x, const char * _file, int _line);
void _glVertexAttribL2ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, const char * _file, int _line);
void _glVertexAttribL3ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, const char * _file, int _line);
void _glVertexAttribL4ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w, const char * _file, int _line);
void _glVertexAttribL1ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line);
void _glVertexAttribL2ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line);
void _glVertexAttribL3ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line);
void _glVertexAttribL4ui64vNV(GLuint index, const GLuint64EXT *v, const char * _file, int _line);
void _glGetVertexAttribLi64vNV(GLuint index, GLenum pname, GLint64EXT *params, const char * _file, int _line);
void _glGetVertexAttribLui64vNV(GLuint index, GLenum pname, GLuint64EXT *params, const char * _file, int _line);
void _glVertexAttribLFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glBufferAddressRangeNV(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length, const char * _file, int _line);
void _glVertexFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glNormalFormatNV(GLenum type, GLsizei stride, const char * _file, int _line);
void _glColorFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glIndexFormatNV(GLenum type, GLsizei stride, const char * _file, int _line);
void _glTexCoordFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glEdgeFlagFormatNV(GLsizei stride, const char * _file, int _line);
void _glSecondaryColorFormatNV(GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glFogCoordFormatNV(GLenum type, GLsizei stride, const char * _file, int _line);
void _glVertexAttribFormatNV(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const char * _file, int _line);
void _glVertexAttribIFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride, const char * _file, int _line);
void _glGetIntegerui64i_vNV(GLenum value, GLuint index, GLuint64EXT *result, const char * _file, int _line);
GLboolean _glAreProgramsResidentNV(GLsizei n, const GLuint *programs, GLboolean *residences, const char * _file, int _line);
void _glBindProgramNV(GLenum target, GLuint id, const char * _file, int _line);
void _glDeleteProgramsNV(GLsizei n, const GLuint *programs, const char * _file, int _line);
void _glExecuteProgramNV(GLenum target, GLuint id, const GLfloat *params, const char * _file, int _line);
void _glGenProgramsNV(GLsizei n, GLuint *programs, const char * _file, int _line);
void _glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetProgramivNV(GLuint id, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetProgramStringNV(GLuint id, GLenum pname, GLubyte *program, const char * _file, int _line);
void _glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble *params, const char * _file, int _line);
void _glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVertexAttribivNV(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribPointervNV(GLuint index, GLenum pname, void **pointer, const char * _file, int _line);
GLboolean _glIsProgramNV(GLuint id, const char * _file, int _line);
void _glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte *program, const char * _file, int _line);
void _glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble *v, const char * _file, int _line);
void _glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat *v, const char * _file, int _line);
void _glProgramParameters4dvNV(GLenum target, GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glProgramParameters4fvNV(GLenum target, GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glRequestResidentProgramsNV(GLsizei n, const GLuint *programs, const char * _file, int _line);
void _glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform, const char * _file, int _line);
void _glVertexAttribPointerNV(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glVertexAttrib1dNV(GLuint index, GLdouble x, const char * _file, int _line);
void _glVertexAttrib1dvNV(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib1fNV(GLuint index, GLfloat x, const char * _file, int _line);
void _glVertexAttrib1fvNV(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib1sNV(GLuint index, GLshort x, const char * _file, int _line);
void _glVertexAttrib1svNV(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y, const char * _file, int _line);
void _glVertexAttrib2dvNV(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y, const char * _file, int _line);
void _glVertexAttrib2fvNV(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y, const char * _file, int _line);
void _glVertexAttrib2svNV(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, const char * _file, int _line);
void _glVertexAttrib3dvNV(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glVertexAttrib3fvNV(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z, const char * _file, int _line);
void _glVertexAttrib3svNV(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w, const char * _file, int _line);
void _glVertexAttrib4dvNV(GLuint index, const GLdouble *v, const char * _file, int _line);
void _glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glVertexAttrib4fvNV(GLuint index, const GLfloat *v, const char * _file, int _line);
void _glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w, const char * _file, int _line);
void _glVertexAttrib4svNV(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w, const char * _file, int _line);
void _glVertexAttrib4ubvNV(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttribs1dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribs1fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glVertexAttribs1svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line);
void _glVertexAttribs2dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribs2fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glVertexAttribs2svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line);
void _glVertexAttribs3dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribs3fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glVertexAttribs3svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line);
void _glVertexAttribs4dvNV(GLuint index, GLsizei count, const GLdouble *v, const char * _file, int _line);
void _glVertexAttribs4fvNV(GLuint index, GLsizei count, const GLfloat *v, const char * _file, int _line);
void _glVertexAttribs4svNV(GLuint index, GLsizei count, const GLshort *v, const char * _file, int _line);
void _glVertexAttribs4ubvNV(GLuint index, GLsizei count, const GLubyte *v, const char * _file, int _line);
void _glVertexAttribI1iEXT(GLuint index, GLint x, const char * _file, int _line);
void _glVertexAttribI2iEXT(GLuint index, GLint x, GLint y, const char * _file, int _line);
void _glVertexAttribI3iEXT(GLuint index, GLint x, GLint y, GLint z, const char * _file, int _line);
void _glVertexAttribI4iEXT(GLuint index, GLint x, GLint y, GLint z, GLint w, const char * _file, int _line);
void _glVertexAttribI1uiEXT(GLuint index, GLuint x, const char * _file, int _line);
void _glVertexAttribI2uiEXT(GLuint index, GLuint x, GLuint y, const char * _file, int _line);
void _glVertexAttribI3uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, const char * _file, int _line);
void _glVertexAttribI4uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w, const char * _file, int _line);
void _glVertexAttribI1ivEXT(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI2ivEXT(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI3ivEXT(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI4ivEXT(GLuint index, const GLint *v, const char * _file, int _line);
void _glVertexAttribI1uivEXT(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI2uivEXT(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI3uivEXT(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI4uivEXT(GLuint index, const GLuint *v, const char * _file, int _line);
void _glVertexAttribI4bvEXT(GLuint index, const GLbyte *v, const char * _file, int _line);
void _glVertexAttribI4svEXT(GLuint index, const GLshort *v, const char * _file, int _line);
void _glVertexAttribI4ubvEXT(GLuint index, const GLubyte *v, const char * _file, int _line);
void _glVertexAttribI4usvEXT(GLuint index, const GLushort *v, const char * _file, int _line);
void _glVertexAttribIPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer, const char * _file, int _line);
void _glGetVertexAttribIivEXT(GLuint index, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVertexAttribIuivEXT(GLuint index, GLenum pname, GLuint *params, const char * _file, int _line);
void _glBeginVideoCaptureNV(GLuint video_capture_slot, const char * _file, int _line);
void _glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset, const char * _file, int _line);
void _glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture, const char * _file, int _line);
void _glEndVideoCaptureNV(GLuint video_capture_slot, const char * _file, int _line);
void _glGetVideoCaptureivNV(GLuint video_capture_slot, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVideoCaptureStreamivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetVideoCaptureStreamfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetVideoCaptureStreamdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble *params, const char * _file, int _line);
GLenum _glVideoCaptureNV(GLuint video_capture_slot, GLuint *sequence_num, GLuint64EXT *capture_time, const char * _file, int _line);
void _glVideoCaptureStreamParameterivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint *params, const char * _file, int _line);
void _glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble *params, const char * _file, int _line);
void _glViewportSwizzleNV(GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew, const char * _file, int _line);
void _glMultiTexCoord1bOES(GLenum texture, GLbyte s, const char * _file, int _line);
void _glMultiTexCoord1bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line);
void _glMultiTexCoord2bOES(GLenum texture, GLbyte s, GLbyte t, const char * _file, int _line);
void _glMultiTexCoord2bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line);
void _glMultiTexCoord3bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, const char * _file, int _line);
void _glMultiTexCoord3bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line);
void _glMultiTexCoord4bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, GLbyte q, const char * _file, int _line);
void _glMultiTexCoord4bvOES(GLenum texture, const GLbyte *coords, const char * _file, int _line);
void _glTexCoord1bOES(GLbyte s, const char * _file, int _line);
void _glTexCoord1bvOES(const GLbyte *coords, const char * _file, int _line);
void _glTexCoord2bOES(GLbyte s, GLbyte t, const char * _file, int _line);
void _glTexCoord2bvOES(const GLbyte *coords, const char * _file, int _line);
void _glTexCoord3bOES(GLbyte s, GLbyte t, GLbyte r, const char * _file, int _line);
void _glTexCoord3bvOES(const GLbyte *coords, const char * _file, int _line);
void _glTexCoord4bOES(GLbyte s, GLbyte t, GLbyte r, GLbyte q, const char * _file, int _line);
void _glTexCoord4bvOES(const GLbyte *coords, const char * _file, int _line);
void _glVertex2bOES(GLbyte x, GLbyte y, const char * _file, int _line);
void _glVertex2bvOES(const GLbyte *coords, const char * _file, int _line);
void _glVertex3bOES(GLbyte x, GLbyte y, GLbyte z, const char * _file, int _line);
void _glVertex3bvOES(const GLbyte *coords, const char * _file, int _line);
void _glVertex4bOES(GLbyte x, GLbyte y, GLbyte z, GLbyte w, const char * _file, int _line);
void _glVertex4bvOES(const GLbyte *coords, const char * _file, int _line);
void _glAlphaFuncxOES(GLenum func, GLfixed ref, const char * _file, int _line);
void _glClearColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line);
void _glClearDepthxOES(GLfixed depth, const char * _file, int _line);
void _glClipPlanexOES(GLenum plane, const GLfixed *equation, const char * _file, int _line);
void _glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line);
void _glDepthRangexOES(GLfixed n, GLfixed f, const char * _file, int _line);
void _glFogxOES(GLenum pname, GLfixed param, const char * _file, int _line);
void _glFogxvOES(GLenum pname, const GLfixed *param, const char * _file, int _line);
void _glFrustumxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f, const char * _file, int _line);
void _glGetClipPlanexOES(GLenum plane, GLfixed *equation, const char * _file, int _line);
void _glGetFixedvOES(GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glLightModelxOES(GLenum pname, GLfixed param, const char * _file, int _line);
void _glLightModelxvOES(GLenum pname, const GLfixed *param, const char * _file, int _line);
void _glLightxOES(GLenum light, GLenum pname, GLfixed param, const char * _file, int _line);
void _glLightxvOES(GLenum light, GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glLineWidthxOES(GLfixed width, const char * _file, int _line);
void _glLoadMatrixxOES(const GLfixed *m, const char * _file, int _line);
void _glMaterialxOES(GLenum face, GLenum pname, GLfixed param, const char * _file, int _line);
void _glMaterialxvOES(GLenum face, GLenum pname, const GLfixed *param, const char * _file, int _line);
void _glMultMatrixxOES(const GLfixed *m, const char * _file, int _line);
void _glMultiTexCoord4xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q, const char * _file, int _line);
void _glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz, const char * _file, int _line);
void _glOrthoxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f, const char * _file, int _line);
void _glPointParameterxvOES(GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glPointSizexOES(GLfixed size, const char * _file, int _line);
void _glPolygonOffsetxOES(GLfixed factor, GLfixed units, const char * _file, int _line);
void _glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line);
void _glScalexOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line);
void _glTexEnvxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line);
void _glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glTexParameterxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line);
void _glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glTranslatexOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line);
void _glGetLightxvOES(GLenum light, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetMaterialxvOES(GLenum face, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glPointParameterxOES(GLenum pname, GLfixed param, const char * _file, int _line);
void _glSampleCoveragexOES(GLclampx value, GLboolean invert, const char * _file, int _line);
void _glAccumxOES(GLenum op, GLfixed value, const char * _file, int _line);
void _glBitmapxOES(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig, GLfixed xmove, GLfixed ymove, const GLubyte *bitmap, const char * _file, int _line);
void _glBlendColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line);
void _glClearAccumxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha, const char * _file, int _line);
void _glColor3xOES(GLfixed red, GLfixed green, GLfixed blue, const char * _file, int _line);
void _glColor3xvOES(const GLfixed *components, const char * _file, int _line);
void _glColor4xvOES(const GLfixed *components, const char * _file, int _line);
void _glConvolutionParameterxOES(GLenum target, GLenum pname, GLfixed param, const char * _file, int _line);
void _glConvolutionParameterxvOES(GLenum target, GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glEvalCoord1xOES(GLfixed u, const char * _file, int _line);
void _glEvalCoord1xvOES(const GLfixed *coords, const char * _file, int _line);
void _glEvalCoord2xOES(GLfixed u, GLfixed v, const char * _file, int _line);
void _glEvalCoord2xvOES(const GLfixed *coords, const char * _file, int _line);
void _glFeedbackBufferxOES(GLsizei n, GLenum type, const GLfixed *buffer, const char * _file, int _line);
void _glGetConvolutionParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetHistogramParameterxvOES(GLenum target, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetLightxOES(GLenum light, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetMapxvOES(GLenum target, GLenum query, GLfixed *v, const char * _file, int _line);
void _glGetMaterialxOES(GLenum face, GLenum pname, GLfixed param, const char * _file, int _line);
void _glGetPixelMapxv(GLenum map, GLint size, GLfixed *values, const char * _file, int _line);
void _glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glGetTexLevelParameterxvOES(GLenum target, GLint level, GLenum pname, GLfixed *params, const char * _file, int _line);
void _glIndexxOES(GLfixed component, const char * _file, int _line);
void _glIndexxvOES(const GLfixed *component, const char * _file, int _line);
void _glLoadTransposeMatrixxOES(const GLfixed *m, const char * _file, int _line);
void _glMap1xOES(GLenum target, GLfixed u1, GLfixed u2, GLint stride, GLint order, GLfixed points, const char * _file, int _line);
void _glMap2xOES(GLenum target, GLfixed u1, GLfixed u2, GLint ustride, GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder, GLfixed points, const char * _file, int _line);
void _glMapGrid1xOES(GLint n, GLfixed u1, GLfixed u2, const char * _file, int _line);
void _glMapGrid2xOES(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2, const char * _file, int _line);
void _glMultTransposeMatrixxOES(const GLfixed *m, const char * _file, int _line);
void _glMultiTexCoord1xOES(GLenum texture, GLfixed s, const char * _file, int _line);
void _glMultiTexCoord1xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line);
void _glMultiTexCoord2xOES(GLenum texture, GLfixed s, GLfixed t, const char * _file, int _line);
void _glMultiTexCoord2xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line);
void _glMultiTexCoord3xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, const char * _file, int _line);
void _glMultiTexCoord3xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line);
void _glMultiTexCoord4xvOES(GLenum texture, const GLfixed *coords, const char * _file, int _line);
void _glNormal3xvOES(const GLfixed *coords, const char * _file, int _line);
void _glPassThroughxOES(GLfixed token, const char * _file, int _line);
void _glPixelMapx(GLenum map, GLint size, const GLfixed *values, const char * _file, int _line);
void _glPixelStorex(GLenum pname, GLfixed param, const char * _file, int _line);
void _glPixelTransferxOES(GLenum pname, GLfixed param, const char * _file, int _line);
void _glPixelZoomxOES(GLfixed xfactor, GLfixed yfactor, const char * _file, int _line);
void _glPrioritizeTexturesxOES(GLsizei n, const GLuint *textures, const GLfixed *priorities, const char * _file, int _line);
void _glRasterPos2xOES(GLfixed x, GLfixed y, const char * _file, int _line);
void _glRasterPos2xvOES(const GLfixed *coords, const char * _file, int _line);
void _glRasterPos3xOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line);
void _glRasterPos3xvOES(const GLfixed *coords, const char * _file, int _line);
void _glRasterPos4xOES(GLfixed x, GLfixed y, GLfixed z, GLfixed w, const char * _file, int _line);
void _glRasterPos4xvOES(const GLfixed *coords, const char * _file, int _line);
void _glRectxOES(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2, const char * _file, int _line);
void _glRectxvOES(const GLfixed *v1, const GLfixed *v2, const char * _file, int _line);
void _glTexCoord1xOES(GLfixed s, const char * _file, int _line);
void _glTexCoord1xvOES(const GLfixed *coords, const char * _file, int _line);
void _glTexCoord2xOES(GLfixed s, GLfixed t, const char * _file, int _line);
void _glTexCoord2xvOES(const GLfixed *coords, const char * _file, int _line);
void _glTexCoord3xOES(GLfixed s, GLfixed t, GLfixed r, const char * _file, int _line);
void _glTexCoord3xvOES(const GLfixed *coords, const char * _file, int _line);
void _glTexCoord4xOES(GLfixed s, GLfixed t, GLfixed r, GLfixed q, const char * _file, int _line);
void _glTexCoord4xvOES(const GLfixed *coords, const char * _file, int _line);
void _glTexGenxOES(GLenum coord, GLenum pname, GLfixed param, const char * _file, int _line);
void _glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed *params, const char * _file, int _line);
void _glVertex2xOES(GLfixed x, const char * _file, int _line);
void _glVertex2xvOES(const GLfixed *coords, const char * _file, int _line);
void _glVertex3xOES(GLfixed x, GLfixed y, const char * _file, int _line);
void _glVertex3xvOES(const GLfixed *coords, const char * _file, int _line);
void _glVertex4xOES(GLfixed x, GLfixed y, GLfixed z, const char * _file, int _line);
void _glVertex4xvOES(const GLfixed *coords, const char * _file, int _line);
GLbitfield _glQueryMatrixxOES(GLfixed *mantissa, GLint *exponent, const char * _file, int _line);
void _glClearDepthfOES(GLclampf depth, const char * _file, int _line);
void _glClipPlanefOES(GLenum plane, const GLfloat *equation, const char * _file, int _line);
void _glDepthRangefOES(GLclampf n, GLclampf f, const char * _file, int _line);
void _glFrustumfOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f, const char * _file, int _line);
void _glGetClipPlanefOES(GLenum plane, GLfloat *equation, const char * _file, int _line);
void _glOrthofOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f, const char * _file, int _line);
void _glFramebufferTextureMultiviewOVR(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews, const char * _file, int _line);
void _glHintPGI(GLenum target, GLint mode, const char * _file, int _line);
void _glDetailTexFuncSGIS(GLenum target, GLsizei n, const GLfloat *points, const char * _file, int _line);
void _glGetDetailTexFuncSGIS(GLenum target, GLfloat *points, const char * _file, int _line);
void _glFogFuncSGIS(GLsizei n, const GLfloat *points, const char * _file, int _line);
void _glGetFogFuncSGIS(GLfloat *points, const char * _file, int _line);
void _glSampleMaskSGIS(GLclampf value, GLboolean invert, const char * _file, int _line);
void _glSamplePatternSGIS(GLenum pattern, const char * _file, int _line);
void _glPixelTexGenParameteriSGIS(GLenum pname, GLint param, const char * _file, int _line);
void _glPixelTexGenParameterivSGIS(GLenum pname, const GLint *params, const char * _file, int _line);
void _glPixelTexGenParameterfSGIS(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPixelTexGenParameterfvSGIS(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glGetPixelTexGenParameterivSGIS(GLenum pname, GLint *params, const char * _file, int _line);
void _glGetPixelTexGenParameterfvSGIS(GLenum pname, GLfloat *params, const char * _file, int _line);
void _glPointParameterfSGIS(GLenum pname, GLfloat param, const char * _file, int _line);
void _glPointParameterfvSGIS(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glSharpenTexFuncSGIS(GLenum target, GLsizei n, const GLfloat *points, const char * _file, int _line);
void _glGetSharpenTexFuncSGIS(GLenum target, GLfloat *points, const char * _file, int _line);
void _glTexImage4DSGIS(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTexSubImage4DSGIS(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const void *pixels, const char * _file, int _line);
void _glTextureColorMaskSGIS(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha, const char * _file, int _line);
void _glGetTexFilterFuncSGIS(GLenum target, GLenum filter, GLfloat *weights, const char * _file, int _line);
void _glTexFilterFuncSGIS(GLenum target, GLenum filter, GLsizei n, const GLfloat *weights, const char * _file, int _line);
void _glAsyncMarkerSGIX(GLuint marker, const char * _file, int _line);
GLint _glFinishAsyncSGIX(GLuint *markerp, const char * _file, int _line);
GLint _glPollAsyncSGIX(GLuint *markerp, const char * _file, int _line);
GLuint _glGenAsyncMarkersSGIX(GLsizei range, const char * _file, int _line);
void _glDeleteAsyncMarkersSGIX(GLuint marker, GLsizei range, const char * _file, int _line);
GLboolean _glIsAsyncMarkerSGIX(GLuint marker, const char * _file, int _line);
void _glFlushRasterSGIX(const char * _file, int _line);
void _glFragmentColorMaterialSGIX(GLenum face, GLenum mode, const char * _file, int _line);
void _glFragmentLightfSGIX(GLenum light, GLenum pname, GLfloat param, const char * _file, int _line);
void _glFragmentLightfvSGIX(GLenum light, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glFragmentLightiSGIX(GLenum light, GLenum pname, GLint param, const char * _file, int _line);
void _glFragmentLightivSGIX(GLenum light, GLenum pname, const GLint *params, const char * _file, int _line);
void _glFragmentLightModelfSGIX(GLenum pname, GLfloat param, const char * _file, int _line);
void _glFragmentLightModelfvSGIX(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glFragmentLightModeliSGIX(GLenum pname, GLint param, const char * _file, int _line);
void _glFragmentLightModelivSGIX(GLenum pname, const GLint *params, const char * _file, int _line);
void _glFragmentMaterialfSGIX(GLenum face, GLenum pname, GLfloat param, const char * _file, int _line);
void _glFragmentMaterialfvSGIX(GLenum face, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glFragmentMaterialiSGIX(GLenum face, GLenum pname, GLint param, const char * _file, int _line);
void _glFragmentMaterialivSGIX(GLenum face, GLenum pname, const GLint *params, const char * _file, int _line);
void _glGetFragmentLightfvSGIX(GLenum light, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetFragmentLightivSGIX(GLenum light, GLenum pname, GLint *params, const char * _file, int _line);
void _glGetFragmentMaterialfvSGIX(GLenum face, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetFragmentMaterialivSGIX(GLenum face, GLenum pname, GLint *params, const char * _file, int _line);
void _glLightEnviSGIX(GLenum pname, GLint param, const char * _file, int _line);
void _glFrameZoomSGIX(GLint factor, const char * _file, int _line);
void _glIglooInterfaceSGIX(GLenum pname, const void *params, const char * _file, int _line);
GLint _glGetInstrumentsSGIX(const char * _file, int _line);
void _glInstrumentsBufferSGIX(GLsizei size, GLint *buffer, const char * _file, int _line);
GLint _glPollInstrumentsSGIX(GLint *marker_p, const char * _file, int _line);
void _glReadInstrumentsSGIX(GLint marker, const char * _file, int _line);
void _glStartInstrumentsSGIX(const char * _file, int _line);
void _glStopInstrumentsSGIX(GLint marker, const char * _file, int _line);
void _glGetListParameterfvSGIX(GLuint list, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetListParameterivSGIX(GLuint list, GLenum pname, GLint *params, const char * _file, int _line);
void _glListParameterfSGIX(GLuint list, GLenum pname, GLfloat param, const char * _file, int _line);
void _glListParameterfvSGIX(GLuint list, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glListParameteriSGIX(GLuint list, GLenum pname, GLint param, const char * _file, int _line);
void _glListParameterivSGIX(GLuint list, GLenum pname, const GLint *params, const char * _file, int _line);
void _glPixelTexGenSGIX(GLenum mode, const char * _file, int _line);
void _glDeformationMap3dSGIX(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points, const char * _file, int _line);
void _glDeformationMap3fSGIX(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points, const char * _file, int _line);
void _glDeformSGIX(GLbitfield mask, const char * _file, int _line);
void _glLoadIdentityDeformationMapSGIX(GLbitfield mask, const char * _file, int _line);
void _glReferencePlaneSGIX(const GLdouble *equation, const char * _file, int _line);
void _glSpriteParameterfSGIX(GLenum pname, GLfloat param, const char * _file, int _line);
void _glSpriteParameterfvSGIX(GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glSpriteParameteriSGIX(GLenum pname, GLint param, const char * _file, int _line);
void _glSpriteParameterivSGIX(GLenum pname, const GLint *params, const char * _file, int _line);
void _glTagSampleBufferSGIX(const char * _file, int _line);
void _glColorTableSGI(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void *table, const char * _file, int _line);
void _glColorTableParameterfvSGI(GLenum target, GLenum pname, const GLfloat *params, const char * _file, int _line);
void _glColorTableParameterivSGI(GLenum target, GLenum pname, const GLint *params, const char * _file, int _line);
void _glCopyColorTableSGI(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, const char * _file, int _line);
void _glGetColorTableSGI(GLenum target, GLenum format, GLenum type, void *table, const char * _file, int _line);
void _glGetColorTableParameterfvSGI(GLenum target, GLenum pname, GLfloat *params, const char * _file, int _line);
void _glGetColorTableParameterivSGI(GLenum target, GLenum pname, GLint *params, const char * _file, int _line);
void _glFinishTextureSUNX(const char * _file, int _line);
void _glGlobalAlphaFactorbSUN(GLbyte factor, const char * _file, int _line);
void _glGlobalAlphaFactorsSUN(GLshort factor, const char * _file, int _line);
void _glGlobalAlphaFactoriSUN(GLint factor, const char * _file, int _line);
void _glGlobalAlphaFactorfSUN(GLfloat factor, const char * _file, int _line);
void _glGlobalAlphaFactordSUN(GLdouble factor, const char * _file, int _line);
void _glGlobalAlphaFactorubSUN(GLubyte factor, const char * _file, int _line);
void _glGlobalAlphaFactorusSUN(GLushort factor, const char * _file, int _line);
void _glGlobalAlphaFactoruiSUN(GLuint factor, const char * _file, int _line);
void _glDrawMeshArraysSUN(GLenum mode, GLint first, GLsizei count, GLsizei width, const char * _file, int _line);
void _glReplacementCodeuiSUN(GLuint code, const char * _file, int _line);
void _glReplacementCodeusSUN(GLushort code, const char * _file, int _line);
void _glReplacementCodeubSUN(GLubyte code, const char * _file, int _line);
void _glReplacementCodeuivSUN(const GLuint *code, const char * _file, int _line);
void _glReplacementCodeusvSUN(const GLushort *code, const char * _file, int _line);
void _glReplacementCodeubvSUN(const GLubyte *code, const char * _file, int _line);
void _glReplacementCodePointerSUN(GLenum type, GLsizei stride, const void **pointer, const char * _file, int _line);
void _glColor4ubVertex2fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, const char * _file, int _line);
void _glColor4ubVertex2fvSUN(const GLubyte *c, const GLfloat *v, const char * _file, int _line);
void _glColor4ubVertex3fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glColor4ubVertex3fvSUN(const GLubyte *c, const GLfloat *v, const char * _file, int _line);
void _glColor3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glColor3fVertex3fvSUN(const GLfloat *c, const GLfloat *v, const char * _file, int _line);
void _glNormal3fVertex3fSUN(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glNormal3fVertex3fvSUN(const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glColor4fNormal3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glColor4fNormal3fVertex3fvSUN(const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glTexCoord2fVertex3fSUN(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glTexCoord2fVertex3fvSUN(const GLfloat *tc, const GLfloat *v, const char * _file, int _line);
void _glTexCoord4fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glTexCoord4fVertex4fvSUN(const GLfloat *tc, const GLfloat *v, const char * _file, int _line);
void _glTexCoord2fColor4ubVertex3fSUN(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glTexCoord2fColor4ubVertex3fvSUN(const GLfloat *tc, const GLubyte *c, const GLfloat *v, const char * _file, int _line);
void _glTexCoord2fColor3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glTexCoord2fColor3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *v, const char * _file, int _line);
void _glTexCoord2fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glTexCoord2fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w, const char * _file, int _line);
void _glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiVertex3fSUN(GLuint rc, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiVertex3fvSUN(const GLuint *rc, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiColor4ubVertex3fSUN(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint *rc, const GLubyte *c, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiColor3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiColor3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiNormal3fVertex3fSUN(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, const char * _file, int _line);
void _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v, const char * _file, int _line);

#define glCullFace(mode) _glCullFace(mode, __FILE__, __LINE__)
#define glFrontFace(mode) _glFrontFace(mode, __FILE__, __LINE__)
#define glHint(target, mode) _glHint(target, mode, __FILE__, __LINE__)
#define glLineWidth(width) _glLineWidth(width, __FILE__, __LINE__)
#define glPointSize(size) _glPointSize(size, __FILE__, __LINE__)
#define glPolygonMode(face, mode) _glPolygonMode(face, mode, __FILE__, __LINE__)
#define glScissor(x, y, width, height) _glScissor(x, y, width, height, __FILE__, __LINE__)
#define glTexParameterf(target, pname, param) _glTexParameterf(target, pname, param, __FILE__, __LINE__)
#define glTexParameterfv(target, pname, params) _glTexParameterfv(target, pname, params, __FILE__, __LINE__)
#define glTexParameteri(target, pname, param) _glTexParameteri(target, pname, param, __FILE__, __LINE__)
#define glTexParameteriv(target, pname, params) _glTexParameteriv(target, pname, params, __FILE__, __LINE__)
#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) _glTexImage1D(target, level, internalformat, width, border, format, type, pixels, __FILE__, __LINE__)
#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) _glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels, __FILE__, __LINE__)
#define glDrawBuffer(buf) _glDrawBuffer(buf, __FILE__, __LINE__)
#define glClear(mask) _glClear(mask, __FILE__, __LINE__)
#define glClearColor(red, green, blue, alpha) _glClearColor(red, green, blue, alpha, __FILE__, __LINE__)
#define glClearStencil(s) _glClearStencil(s, __FILE__, __LINE__)
#define glClearDepth(depth) _glClearDepth(depth, __FILE__, __LINE__)
#define glStencilMask(mask) _glStencilMask(mask, __FILE__, __LINE__)
#define glColorMask(red, green, blue, alpha) _glColorMask(red, green, blue, alpha, __FILE__, __LINE__)
#define glDepthMask(flag) _glDepthMask(flag, __FILE__, __LINE__)
#define glDisable(cap) _glDisable(cap, __FILE__, __LINE__)
#define glEnable(cap) _glEnable(cap, __FILE__, __LINE__)
#define glFinish() _glFinish(__FILE__, __LINE__)
#define glFlush() _glFlush(__FILE__, __LINE__)
#define glBlendFunc(sfactor, dfactor) _glBlendFunc(sfactor, dfactor, __FILE__, __LINE__)
#define glLogicOp(opcode) _glLogicOp(opcode, __FILE__, __LINE__)
#define glStencilFunc(func, ref, mask) _glStencilFunc(func, ref, mask, __FILE__, __LINE__)
#define glStencilOp(fail, zfail, zpass) _glStencilOp(fail, zfail, zpass, __FILE__, __LINE__)
#define glDepthFunc(func) _glDepthFunc(func, __FILE__, __LINE__)
#define glPixelStoref(pname, param) _glPixelStoref(pname, param, __FILE__, __LINE__)
#define glPixelStorei(pname, param) _glPixelStorei(pname, param, __FILE__, __LINE__)
#define glReadBuffer(src) _glReadBuffer(src, __FILE__, __LINE__)
#define glReadPixels(x, y, width, height, format, type, pixels) _glReadPixels(x, y, width, height, format, type, pixels, __FILE__, __LINE__)
#define glGetBooleanv(pname, data) _glGetBooleanv(pname, data, __FILE__, __LINE__)
#define glGetDoublev(pname, data) _glGetDoublev(pname, data, __FILE__, __LINE__)
#define glGetFloatv(pname, data) _glGetFloatv(pname, data, __FILE__, __LINE__)
#define glGetIntegerv(pname, data) _glGetIntegerv(pname, data, __FILE__, __LINE__)
#define glGetString(name) _glGetString(name, __FILE__, __LINE__)
#define glGetTexImage(target, level, format, type, pixels) _glGetTexImage(target, level, format, type, pixels, __FILE__, __LINE__)
#define glGetTexParameterfv(target, pname, params) _glGetTexParameterfv(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameteriv(target, pname, params) _glGetTexParameteriv(target, pname, params, __FILE__, __LINE__)
#define glGetTexLevelParameterfv(target, level, pname, params) _glGetTexLevelParameterfv(target, level, pname, params, __FILE__, __LINE__)
#define glGetTexLevelParameteriv(target, level, pname, params) _glGetTexLevelParameteriv(target, level, pname, params, __FILE__, __LINE__)
#define glIsEnabled(cap) _glIsEnabled(cap, __FILE__, __LINE__)
#define glDepthRange(n, f) _glDepthRange(n, f, __FILE__, __LINE__)
#define glViewport(x, y, width, height) _glViewport(x, y, width, height, __FILE__, __LINE__)
#define glDrawArrays(mode, first, count) _glDrawArrays(mode, first, count, __FILE__, __LINE__)
#define glDrawElements(mode, count, type, indices) _glDrawElements(mode, count, type, indices, __FILE__, __LINE__)
#define glPolygonOffset(factor, units) _glPolygonOffset(factor, units, __FILE__, __LINE__)
#define glCopyTexImage1D(target, level, internalformat, x, y, width, border) _glCopyTexImage1D(target, level, internalformat, x, y, width, border, __FILE__, __LINE__)
#define glCopyTexImage2D(target, level, internalformat, x, y, width, height, border) _glCopyTexImage2D(target, level, internalformat, x, y, width, height, border, __FILE__, __LINE__)
#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) _glCopyTexSubImage1D(target, level, xoffset, x, y, width, __FILE__, __LINE__)
#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) _glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height, __FILE__, __LINE__)
#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) _glTexSubImage1D(target, level, xoffset, width, format, type, pixels, __FILE__, __LINE__)
#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) _glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels, __FILE__, __LINE__)
#define glBindTexture(target, texture) _glBindTexture(target, texture, __FILE__, __LINE__)
#define glDeleteTextures(n, textures) _glDeleteTextures(n, textures, __FILE__, __LINE__)
#define glGenTextures(n, textures) _glGenTextures(n, textures, __FILE__, __LINE__)
#define glIsTexture(texture) _glIsTexture(texture, __FILE__, __LINE__)
#define glDrawRangeElements(mode, start, end, count, type, indices) _glDrawRangeElements(mode, start, end, count, type, indices, __FILE__, __LINE__)
#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels) _glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels, __FILE__, __LINE__)
#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) _glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels, __FILE__, __LINE__)
#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) _glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height, __FILE__, __LINE__)
#define glActiveTexture(texture) _glActiveTexture(texture, __FILE__, __LINE__)
#define glSampleCoverage(value, invert) _glSampleCoverage(value, invert, __FILE__, __LINE__)
#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) _glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) _glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) _glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) _glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) _glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) _glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data, __FILE__, __LINE__)
#define glGetCompressedTexImage(target, level, img) _glGetCompressedTexImage(target, level, img, __FILE__, __LINE__)
#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) _glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha, __FILE__, __LINE__)
#define glMultiDrawArrays(mode, first, count, drawcount) _glMultiDrawArrays(mode, first, count, drawcount, __FILE__, __LINE__)
#define glMultiDrawElements(mode, count, type, indices, drawcount) _glMultiDrawElements(mode, count, type, indices, drawcount, __FILE__, __LINE__)
#define glPointParameterf(pname, param) _glPointParameterf(pname, param, __FILE__, __LINE__)
#define glPointParameterfv(pname, params) _glPointParameterfv(pname, params, __FILE__, __LINE__)
#define glPointParameteri(pname, param) _glPointParameteri(pname, param, __FILE__, __LINE__)
#define glPointParameteriv(pname, params) _glPointParameteriv(pname, params, __FILE__, __LINE__)
#define glBlendColor(red, green, blue, alpha) _glBlendColor(red, green, blue, alpha, __FILE__, __LINE__)
#define glBlendEquation(mode) _glBlendEquation(mode, __FILE__, __LINE__)
#define glGenQueries(n, ids) _glGenQueries(n, ids, __FILE__, __LINE__)
#define glDeleteQueries(n, ids) _glDeleteQueries(n, ids, __FILE__, __LINE__)
#define glIsQuery(id) _glIsQuery(id, __FILE__, __LINE__)
#define glBeginQuery(target, id) _glBeginQuery(target, id, __FILE__, __LINE__)
#define glEndQuery(target) _glEndQuery(target, __FILE__, __LINE__)
#define glGetQueryiv(target, pname, params) _glGetQueryiv(target, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectiv(id, pname, params) _glGetQueryObjectiv(id, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectuiv(id, pname, params) _glGetQueryObjectuiv(id, pname, params, __FILE__, __LINE__)
#define glBindBuffer(target, buffer) _glBindBuffer(target, buffer, __FILE__, __LINE__)
#define glDeleteBuffers(n, buffers) _glDeleteBuffers(n, buffers, __FILE__, __LINE__)
#define glGenBuffers(n, buffers) _glGenBuffers(n, buffers, __FILE__, __LINE__)
#define glIsBuffer(buffer) _glIsBuffer(buffer, __FILE__, __LINE__)
#define glBufferData(target, size, data, usage) _glBufferData(target, size, data, usage, __FILE__, __LINE__)
#define glBufferSubData(target, offset, size, data) _glBufferSubData(target, offset, size, data, __FILE__, __LINE__)
#define glGetBufferSubData(target, offset, size, data) _glGetBufferSubData(target, offset, size, data, __FILE__, __LINE__)
#define glMapBuffer(target, _) _glMapBuffer(target, _, __FILE__, __LINE__)
#define glUnmapBuffer(target) _glUnmapBuffer(target, __FILE__, __LINE__)
#define glGetBufferParameteriv(target, pname, params) _glGetBufferParameteriv(target, pname, params, __FILE__, __LINE__)
#define glGetBufferPointerv(target, pname, params) _glGetBufferPointerv(target, pname, params, __FILE__, __LINE__)
#define glBlendEquationSeparate(modeRGB, modeAlpha) _glBlendEquationSeparate(modeRGB, modeAlpha, __FILE__, __LINE__)
#define glDrawBuffers(n, bufs) _glDrawBuffers(n, bufs, __FILE__, __LINE__)
#define glStencilOpSeparate(face, sfail, dpfail, dppass) _glStencilOpSeparate(face, sfail, dpfail, dppass, __FILE__, __LINE__)
#define glStencilFuncSeparate(face, func, ref, mask) _glStencilFuncSeparate(face, func, ref, mask, __FILE__, __LINE__)
#define glStencilMaskSeparate(face, mask) _glStencilMaskSeparate(face, mask, __FILE__, __LINE__)
#define glAttachShader(program, shader) _glAttachShader(program, shader, __FILE__, __LINE__)
#define glBindAttribLocation(program, index, name) _glBindAttribLocation(program, index, name, __FILE__, __LINE__)
#define glCompileShader(shader) _glCompileShader(shader, __FILE__, __LINE__)
#define glCreateProgram() _glCreateProgram(__FILE__, __LINE__)
#define glCreateShader(type) _glCreateShader(type, __FILE__, __LINE__)
#define glDeleteProgram(program) _glDeleteProgram(program, __FILE__, __LINE__)
#define glDeleteShader(shader) _glDeleteShader(shader, __FILE__, __LINE__)
#define glDetachShader(program, shader) _glDetachShader(program, shader, __FILE__, __LINE__)
#define glDisableVertexAttribArray(index) _glDisableVertexAttribArray(index, __FILE__, __LINE__)
#define glEnableVertexAttribArray(index) _glEnableVertexAttribArray(index, __FILE__, __LINE__)
#define glGetActiveAttrib(program, index, bufSize, length, size, type, name) _glGetActiveAttrib(program, index, bufSize, length, size, type, name, __FILE__, __LINE__)
#define glGetActiveUniform(program, index, bufSize, length, size, type, name) _glGetActiveUniform(program, index, bufSize, length, size, type, name, __FILE__, __LINE__)
#define glGetAttachedShaders(program, maxCount, count, shaders) _glGetAttachedShaders(program, maxCount, count, shaders, __FILE__, __LINE__)
#define glGetAttribLocation(program, name) _glGetAttribLocation(program, name, __FILE__, __LINE__)
#define glGetProgramiv(program, pname, params) _glGetProgramiv(program, pname, params, __FILE__, __LINE__)
#define glGetProgramInfoLog(program, bufSize, length, infoLog) _glGetProgramInfoLog(program, bufSize, length, infoLog, __FILE__, __LINE__)
#define glGetShaderiv(shader, pname, params) _glGetShaderiv(shader, pname, params, __FILE__, __LINE__)
#define glGetShaderInfoLog(shader, bufSize, length, infoLog) _glGetShaderInfoLog(shader, bufSize, length, infoLog, __FILE__, __LINE__)
#define glGetShaderSource(shader, bufSize, length, source) _glGetShaderSource(shader, bufSize, length, source, __FILE__, __LINE__)
#define glGetUniformLocation(program, name) _glGetUniformLocation(program, name, __FILE__, __LINE__)
#define glGetUniformfv(program, location, params) _glGetUniformfv(program, location, params, __FILE__, __LINE__)
#define glGetUniformiv(program, location, params) _glGetUniformiv(program, location, params, __FILE__, __LINE__)
#define glGetVertexAttribdv(index, pname, params) _glGetVertexAttribdv(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribfv(index, pname, params) _glGetVertexAttribfv(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribiv(index, pname, params) _glGetVertexAttribiv(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribPointerv(index, pname, pointer) _glGetVertexAttribPointerv(index, pname, pointer, __FILE__, __LINE__)
#define glIsProgram(program) _glIsProgram(program, __FILE__, __LINE__)
#define glIsShader(shader) _glIsShader(shader, __FILE__, __LINE__)
#define glLinkProgram(program) _glLinkProgram(program, __FILE__, __LINE__)
#define glShaderSource(shader, count, string, length) _glShaderSource(shader, count, string, length, __FILE__, __LINE__)
#define glUseProgram(program) _glUseProgram(program, __FILE__, __LINE__)
#define glUniform1f(location, v0) _glUniform1f(location, v0, __FILE__, __LINE__)
#define glUniform2f(location, v0, v1) _glUniform2f(location, v0, v1, __FILE__, __LINE__)
#define glUniform3f(location, v0, v1, v2) _glUniform3f(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4f(location, v0, v1, v2, v3) _glUniform4f(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1i(location, v0) _glUniform1i(location, v0, __FILE__, __LINE__)
#define glUniform2i(location, v0, v1) _glUniform2i(location, v0, v1, __FILE__, __LINE__)
#define glUniform3i(location, v0, v1, v2) _glUniform3i(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4i(location, v0, v1, v2, v3) _glUniform4i(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1fv(location, count, value) _glUniform1fv(location, count, value, __FILE__, __LINE__)
#define glUniform2fv(location, count, value) _glUniform2fv(location, count, value, __FILE__, __LINE__)
#define glUniform3fv(location, count, value) _glUniform3fv(location, count, value, __FILE__, __LINE__)
#define glUniform4fv(location, count, value) _glUniform4fv(location, count, value, __FILE__, __LINE__)
#define glUniform1iv(location, count, value) _glUniform1iv(location, count, value, __FILE__, __LINE__)
#define glUniform2iv(location, count, value) _glUniform2iv(location, count, value, __FILE__, __LINE__)
#define glUniform3iv(location, count, value) _glUniform3iv(location, count, value, __FILE__, __LINE__)
#define glUniform4iv(location, count, value) _glUniform4iv(location, count, value, __FILE__, __LINE__)
#define glUniformMatrix2fv(location, count, transpose, value) _glUniformMatrix2fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3fv(location, count, transpose, value) _glUniformMatrix3fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4fv(location, count, transpose, value) _glUniformMatrix4fv(location, count, transpose, value, __FILE__, __LINE__)
#define glValidateProgram(program) _glValidateProgram(program, __FILE__, __LINE__)
#define glVertexAttrib1d(index, x) _glVertexAttrib1d(index, x, __FILE__, __LINE__)
#define glVertexAttrib1dv(index, v) _glVertexAttrib1dv(index, v, __FILE__, __LINE__)
#define glVertexAttrib1f(index, x) _glVertexAttrib1f(index, x, __FILE__, __LINE__)
#define glVertexAttrib1fv(index, v) _glVertexAttrib1fv(index, v, __FILE__, __LINE__)
#define glVertexAttrib1s(index, x) _glVertexAttrib1s(index, x, __FILE__, __LINE__)
#define glVertexAttrib1sv(index, v) _glVertexAttrib1sv(index, v, __FILE__, __LINE__)
#define glVertexAttrib2d(index, x, y) _glVertexAttrib2d(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2dv(index, v) _glVertexAttrib2dv(index, v, __FILE__, __LINE__)
#define glVertexAttrib2f(index, x, y) _glVertexAttrib2f(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2fv(index, v) _glVertexAttrib2fv(index, v, __FILE__, __LINE__)
#define glVertexAttrib2s(index, x, y) _glVertexAttrib2s(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2sv(index, v) _glVertexAttrib2sv(index, v, __FILE__, __LINE__)
#define glVertexAttrib3d(index, x, y, z) _glVertexAttrib3d(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3dv(index, v) _glVertexAttrib3dv(index, v, __FILE__, __LINE__)
#define glVertexAttrib3f(index, x, y, z) _glVertexAttrib3f(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3fv(index, v) _glVertexAttrib3fv(index, v, __FILE__, __LINE__)
#define glVertexAttrib3s(index, x, y, z) _glVertexAttrib3s(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3sv(index, v) _glVertexAttrib3sv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Nbv(index, v) _glVertexAttrib4Nbv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Niv(index, v) _glVertexAttrib4Niv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Nsv(index, v) _glVertexAttrib4Nsv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Nub(index, x, y, z, w) _glVertexAttrib4Nub(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4Nubv(index, v) _glVertexAttrib4Nubv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Nuiv(index, v) _glVertexAttrib4Nuiv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4Nusv(index, v) _glVertexAttrib4Nusv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4bv(index, v) _glVertexAttrib4bv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4d(index, x, y, z, w) _glVertexAttrib4d(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4dv(index, v) _glVertexAttrib4dv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4f(index, x, y, z, w) _glVertexAttrib4f(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4fv(index, v) _glVertexAttrib4fv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4iv(index, v) _glVertexAttrib4iv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4s(index, x, y, z, w) _glVertexAttrib4s(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4sv(index, v) _glVertexAttrib4sv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4ubv(index, v) _glVertexAttrib4ubv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4uiv(index, v) _glVertexAttrib4uiv(index, v, __FILE__, __LINE__)
#define glVertexAttrib4usv(index, v) _glVertexAttrib4usv(index, v, __FILE__, __LINE__)
#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) _glVertexAttribPointer(index, size, type, normalized, stride, pointer, __FILE__, __LINE__)
#define glUniformMatrix2x3fv(location, count, transpose, value) _glUniformMatrix2x3fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3x2fv(location, count, transpose, value) _glUniformMatrix3x2fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix2x4fv(location, count, transpose, value) _glUniformMatrix2x4fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4x2fv(location, count, transpose, value) _glUniformMatrix4x2fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3x4fv(location, count, transpose, value) _glUniformMatrix3x4fv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4x3fv(location, count, transpose, value) _glUniformMatrix4x3fv(location, count, transpose, value, __FILE__, __LINE__)
#define glColorMaski(index, r, g, b, a) _glColorMaski(index, r, g, b, a, __FILE__, __LINE__)
#define glGetBooleani_v(target, index, data) _glGetBooleani_v(target, index, data, __FILE__, __LINE__)
#define glGetIntegeri_v(target, index, data) _glGetIntegeri_v(target, index, data, __FILE__, __LINE__)
#define glEnablei(target, index) _glEnablei(target, index, __FILE__, __LINE__)
#define glDisablei(target, index) _glDisablei(target, index, __FILE__, __LINE__)
#define glIsEnabledi(target, index) _glIsEnabledi(target, index, __FILE__, __LINE__)
#define glBeginTransformFeedback(primitiveMode) _glBeginTransformFeedback(primitiveMode, __FILE__, __LINE__)
#define glEndTransformFeedback() _glEndTransformFeedback(__FILE__, __LINE__)
#define glBindBufferRange(target, index, buffer, offset, size) _glBindBufferRange(target, index, buffer, offset, size, __FILE__, __LINE__)
#define glBindBufferBase(target, index, buffer) _glBindBufferBase(target, index, buffer, __FILE__, __LINE__)
#define glTransformFeedbackVaryings(program, count, varyings, bufferMode) _glTransformFeedbackVaryings(program, count, varyings, bufferMode, __FILE__, __LINE__)
#define glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name) _glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name, __FILE__, __LINE__)
#define glClampColor(target, clamp) _glClampColor(target, clamp, __FILE__, __LINE__)
#define glBeginConditionalRender(id, mode) _glBeginConditionalRender(id, mode, __FILE__, __LINE__)
#define glEndConditionalRender() _glEndConditionalRender(__FILE__, __LINE__)
#define glVertexAttribIPointer(index, size, type, stride, pointer) _glVertexAttribIPointer(index, size, type, stride, pointer, __FILE__, __LINE__)
#define glGetVertexAttribIiv(index, pname, params) _glGetVertexAttribIiv(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribIuiv(index, pname, params) _glGetVertexAttribIuiv(index, pname, params, __FILE__, __LINE__)
#define glVertexAttribI1i(index, x) _glVertexAttribI1i(index, x, __FILE__, __LINE__)
#define glVertexAttribI2i(index, x, y) _glVertexAttribI2i(index, x, y, __FILE__, __LINE__)
#define glVertexAttribI3i(index, x, y, z) _glVertexAttribI3i(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribI4i(index, x, y, z, w) _glVertexAttribI4i(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribI1ui(index, x) _glVertexAttribI1ui(index, x, __FILE__, __LINE__)
#define glVertexAttribI2ui(index, x, y) _glVertexAttribI2ui(index, x, y, __FILE__, __LINE__)
#define glVertexAttribI3ui(index, x, y, z) _glVertexAttribI3ui(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribI4ui(index, x, y, z, w) _glVertexAttribI4ui(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribI1iv(index, v) _glVertexAttribI1iv(index, v, __FILE__, __LINE__)
#define glVertexAttribI2iv(index, v) _glVertexAttribI2iv(index, v, __FILE__, __LINE__)
#define glVertexAttribI3iv(index, v) _glVertexAttribI3iv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4iv(index, v) _glVertexAttribI4iv(index, v, __FILE__, __LINE__)
#define glVertexAttribI1uiv(index, v) _glVertexAttribI1uiv(index, v, __FILE__, __LINE__)
#define glVertexAttribI2uiv(index, v) _glVertexAttribI2uiv(index, v, __FILE__, __LINE__)
#define glVertexAttribI3uiv(index, v) _glVertexAttribI3uiv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4uiv(index, v) _glVertexAttribI4uiv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4bv(index, v) _glVertexAttribI4bv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4sv(index, v) _glVertexAttribI4sv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4ubv(index, v) _glVertexAttribI4ubv(index, v, __FILE__, __LINE__)
#define glVertexAttribI4usv(index, v) _glVertexAttribI4usv(index, v, __FILE__, __LINE__)
#define glGetUniformuiv(program, location, params) _glGetUniformuiv(program, location, params, __FILE__, __LINE__)
#define glBindFragDataLocation(program, color, name) _glBindFragDataLocation(program, color, name, __FILE__, __LINE__)
#define glGetFragDataLocation(program, name) _glGetFragDataLocation(program, name, __FILE__, __LINE__)
#define glUniform1ui(location, v0) _glUniform1ui(location, v0, __FILE__, __LINE__)
#define glUniform2ui(location, v0, v1) _glUniform2ui(location, v0, v1, __FILE__, __LINE__)
#define glUniform3ui(location, v0, v1, v2) _glUniform3ui(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4ui(location, v0, v1, v2, v3) _glUniform4ui(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1uiv(location, count, value) _glUniform1uiv(location, count, value, __FILE__, __LINE__)
#define glUniform2uiv(location, count, value) _glUniform2uiv(location, count, value, __FILE__, __LINE__)
#define glUniform3uiv(location, count, value) _glUniform3uiv(location, count, value, __FILE__, __LINE__)
#define glUniform4uiv(location, count, value) _glUniform4uiv(location, count, value, __FILE__, __LINE__)
#define glTexParameterIiv(target, pname, params) _glTexParameterIiv(target, pname, params, __FILE__, __LINE__)
#define glTexParameterIuiv(target, pname, params) _glTexParameterIuiv(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameterIiv(target, pname, params) _glGetTexParameterIiv(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameterIuiv(target, pname, params) _glGetTexParameterIuiv(target, pname, params, __FILE__, __LINE__)
#define glClearBufferiv(buffer, drawbuffer, value) _glClearBufferiv(buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearBufferuiv(buffer, drawbuffer, value) _glClearBufferuiv(buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearBufferfv(buffer, drawbuffer, value) _glClearBufferfv(buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearBufferfi(buffer, drawbuffer, depth, stencil) _glClearBufferfi(buffer, drawbuffer, depth, stencil, __FILE__, __LINE__)
#define glGetStringi(name, index) _glGetStringi(name, index, __FILE__, __LINE__)
#define glIsRenderbuffer(renderbuffer) _glIsRenderbuffer(renderbuffer, __FILE__, __LINE__)
#define glBindRenderbuffer(target, renderbuffer) _glBindRenderbuffer(target, renderbuffer, __FILE__, __LINE__)
#define glDeleteRenderbuffers(n, renderbuffers) _glDeleteRenderbuffers(n, renderbuffers, __FILE__, __LINE__)
#define glGenRenderbuffers(n, renderbuffers) _glGenRenderbuffers(n, renderbuffers, __FILE__, __LINE__)
#define glRenderbufferStorage(target, internalformat, width, height) _glRenderbufferStorage(target, internalformat, width, height, __FILE__, __LINE__)
#define glGetRenderbufferParameteriv(target, pname, params) _glGetRenderbufferParameteriv(target, pname, params, __FILE__, __LINE__)
#define glIsFramebuffer(framebuffer) _glIsFramebuffer(framebuffer, __FILE__, __LINE__)
#define glBindFramebuffer(target, framebuffer) _glBindFramebuffer(target, framebuffer, __FILE__, __LINE__)
#define glDeleteFramebuffers(n, framebuffers) _glDeleteFramebuffers(n, framebuffers, __FILE__, __LINE__)
#define glGenFramebuffers(n, framebuffers) _glGenFramebuffers(n, framebuffers, __FILE__, __LINE__)
#define glCheckFramebufferStatus(target) _glCheckFramebufferStatus(target, __FILE__, __LINE__)
#define glFramebufferTexture1D(target, attachment, textarget, texture, level) _glFramebufferTexture1D(target, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glFramebufferTexture2D(target, attachment, textarget, texture, level) _glFramebufferTexture2D(target, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset) _glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset, __FILE__, __LINE__)
#define glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer) _glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer, __FILE__, __LINE__)
#define glGetFramebufferAttachmentParameteriv(target, attachment, pname, params) _glGetFramebufferAttachmentParameteriv(target, attachment, pname, params, __FILE__, __LINE__)
#define glGenerateMipmap(target) _glGenerateMipmap(target, __FILE__, __LINE__)
#define glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) _glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter, __FILE__, __LINE__)
#define glRenderbufferStorageMultisample(target, samples, internalformat, width, height) _glRenderbufferStorageMultisample(target, samples, internalformat, width, height, __FILE__, __LINE__)
#define glFramebufferTextureLayer(target, attachment, texture, level, layer) _glFramebufferTextureLayer(target, attachment, texture, level, layer, __FILE__, __LINE__)
#define glMapBufferRange(target, offset, length, _) _glMapBufferRange(target, offset, length, _, __FILE__, __LINE__)
#define glFlushMappedBufferRange(target, offset, length) _glFlushMappedBufferRange(target, offset, length, __FILE__, __LINE__)
#define glBindVertexArray(array) _glBindVertexArray(array, __FILE__, __LINE__)
#define glDeleteVertexArrays(n, arrays) _glDeleteVertexArrays(n, arrays, __FILE__, __LINE__)
#define glGenVertexArrays(n, arrays) _glGenVertexArrays(n, arrays, __FILE__, __LINE__)
#define glIsVertexArray(array) _glIsVertexArray(array, __FILE__, __LINE__)
#define glDrawArraysInstanced(mode, first, count, instancecount) _glDrawArraysInstanced(mode, first, count, instancecount, __FILE__, __LINE__)
#define glDrawElementsInstanced(mode, count, type, indices, instancecount) _glDrawElementsInstanced(mode, count, type, indices, instancecount, __FILE__, __LINE__)
#define glTexBuffer(target, internalformat, buffer) _glTexBuffer(target, internalformat, buffer, __FILE__, __LINE__)
#define glPrimitiveRestartIndex(index) _glPrimitiveRestartIndex(index, __FILE__, __LINE__)
#define glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size) _glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size, __FILE__, __LINE__)
#define glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices) _glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices, __FILE__, __LINE__)
#define glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params) _glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params, __FILE__, __LINE__)
#define glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName) _glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName, __FILE__, __LINE__)
#define glGetUniformBlockIndex(program, uniformBlockName) _glGetUniformBlockIndex(program, uniformBlockName, __FILE__, __LINE__)
#define glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params) _glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params, __FILE__, __LINE__)
#define glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName) _glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName, __FILE__, __LINE__)
#define glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding) _glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding, __FILE__, __LINE__)
#define glDrawElementsBaseVertex(mode, count, type, indices, basevertex) _glDrawElementsBaseVertex(mode, count, type, indices, basevertex, __FILE__, __LINE__)
#define glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex) _glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex, __FILE__, __LINE__)
#define glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex) _glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex, __FILE__, __LINE__)
#define glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex) _glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex, __FILE__, __LINE__)
#define glProvokingVertex(mode) _glProvokingVertex(mode, __FILE__, __LINE__)
#define glFenceSync(condition, flags) _glFenceSync(condition, flags, __FILE__, __LINE__)
#define glIsSync(sync) _glIsSync(sync, __FILE__, __LINE__)
#define glDeleteSync(sync) _glDeleteSync(sync, __FILE__, __LINE__)
#define glClientWaitSync(sync, flags, timeout) _glClientWaitSync(sync, flags, timeout, __FILE__, __LINE__)
#define glWaitSync(sync, flags, timeout) _glWaitSync(sync, flags, timeout, __FILE__, __LINE__)
#define glGetInteger64v(pname, data) _glGetInteger64v(pname, data, __FILE__, __LINE__)
#define glGetSynciv(sync, pname, count, length, values) _glGetSynciv(sync, pname, count, length, values, __FILE__, __LINE__)
#define glGetInteger64i_v(target, index, data) _glGetInteger64i_v(target, index, data, __FILE__, __LINE__)
#define glGetBufferParameteri64v(target, pname, params) _glGetBufferParameteri64v(target, pname, params, __FILE__, __LINE__)
#define glFramebufferTexture(target, attachment, texture, level) _glFramebufferTexture(target, attachment, texture, level, __FILE__, __LINE__)
#define glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations) _glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations, __FILE__, __LINE__)
#define glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations) _glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations, __FILE__, __LINE__)
#define glGetMultisamplefv(pname, index, val) _glGetMultisamplefv(pname, index, val, __FILE__, __LINE__)
#define glSampleMaski(maskNumber, mask) _glSampleMaski(maskNumber, mask, __FILE__, __LINE__)
#define glBindFragDataLocationIndexed(program, colorNumber, index, name) _glBindFragDataLocationIndexed(program, colorNumber, index, name, __FILE__, __LINE__)
#define glGetFragDataIndex(program, name) _glGetFragDataIndex(program, name, __FILE__, __LINE__)
#define glGenSamplers(count, samplers) _glGenSamplers(count, samplers, __FILE__, __LINE__)
#define glDeleteSamplers(count, samplers) _glDeleteSamplers(count, samplers, __FILE__, __LINE__)
#define glIsSampler(sampler) _glIsSampler(sampler, __FILE__, __LINE__)
#define glBindSampler(unit, sampler) _glBindSampler(unit, sampler, __FILE__, __LINE__)
#define glSamplerParameteri(sampler, pname, param) _glSamplerParameteri(sampler, pname, param, __FILE__, __LINE__)
#define glSamplerParameteriv(sampler, pname, param) _glSamplerParameteriv(sampler, pname, param, __FILE__, __LINE__)
#define glSamplerParameterf(sampler, pname, param) _glSamplerParameterf(sampler, pname, param, __FILE__, __LINE__)
#define glSamplerParameterfv(sampler, pname, param) _glSamplerParameterfv(sampler, pname, param, __FILE__, __LINE__)
#define glSamplerParameterIiv(sampler, pname, param) _glSamplerParameterIiv(sampler, pname, param, __FILE__, __LINE__)
#define glSamplerParameterIuiv(sampler, pname, param) _glSamplerParameterIuiv(sampler, pname, param, __FILE__, __LINE__)
#define glGetSamplerParameteriv(sampler, pname, params) _glGetSamplerParameteriv(sampler, pname, params, __FILE__, __LINE__)
#define glGetSamplerParameterIiv(sampler, pname, params) _glGetSamplerParameterIiv(sampler, pname, params, __FILE__, __LINE__)
#define glGetSamplerParameterfv(sampler, pname, params) _glGetSamplerParameterfv(sampler, pname, params, __FILE__, __LINE__)
#define glGetSamplerParameterIuiv(sampler, pname, params) _glGetSamplerParameterIuiv(sampler, pname, params, __FILE__, __LINE__)
#define glQueryCounter(id, target) _glQueryCounter(id, target, __FILE__, __LINE__)
#define glGetQueryObjecti64v(id, pname, params) _glGetQueryObjecti64v(id, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectui64v(id, pname, params) _glGetQueryObjectui64v(id, pname, params, __FILE__, __LINE__)
#define glVertexAttribDivisor(index, divisor) _glVertexAttribDivisor(index, divisor, __FILE__, __LINE__)
#define glVertexAttribP1ui(index, type, normalized, value) _glVertexAttribP1ui(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP1uiv(index, type, normalized, value) _glVertexAttribP1uiv(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP2ui(index, type, normalized, value) _glVertexAttribP2ui(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP2uiv(index, type, normalized, value) _glVertexAttribP2uiv(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP3ui(index, type, normalized, value) _glVertexAttribP3ui(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP3uiv(index, type, normalized, value) _glVertexAttribP3uiv(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP4ui(index, type, normalized, value) _glVertexAttribP4ui(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexAttribP4uiv(index, type, normalized, value) _glVertexAttribP4uiv(index, type, normalized, value, __FILE__, __LINE__)
#define glVertexP2ui(type, value) _glVertexP2ui(type, value, __FILE__, __LINE__)
#define glVertexP2uiv(type, value) _glVertexP2uiv(type, value, __FILE__, __LINE__)
#define glVertexP3ui(type, value) _glVertexP3ui(type, value, __FILE__, __LINE__)
#define glVertexP3uiv(type, value) _glVertexP3uiv(type, value, __FILE__, __LINE__)
#define glVertexP4ui(type, value) _glVertexP4ui(type, value, __FILE__, __LINE__)
#define glVertexP4uiv(type, value) _glVertexP4uiv(type, value, __FILE__, __LINE__)
#define glTexCoordP1ui(type, coords) _glTexCoordP1ui(type, coords, __FILE__, __LINE__)
#define glTexCoordP1uiv(type, coords) _glTexCoordP1uiv(type, coords, __FILE__, __LINE__)
#define glTexCoordP2ui(type, coords) _glTexCoordP2ui(type, coords, __FILE__, __LINE__)
#define glTexCoordP2uiv(type, coords) _glTexCoordP2uiv(type, coords, __FILE__, __LINE__)
#define glTexCoordP3ui(type, coords) _glTexCoordP3ui(type, coords, __FILE__, __LINE__)
#define glTexCoordP3uiv(type, coords) _glTexCoordP3uiv(type, coords, __FILE__, __LINE__)
#define glTexCoordP4ui(type, coords) _glTexCoordP4ui(type, coords, __FILE__, __LINE__)
#define glTexCoordP4uiv(type, coords) _glTexCoordP4uiv(type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP1ui(texture, type, coords) _glMultiTexCoordP1ui(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP1uiv(texture, type, coords) _glMultiTexCoordP1uiv(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP2ui(texture, type, coords) _glMultiTexCoordP2ui(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP2uiv(texture, type, coords) _glMultiTexCoordP2uiv(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP3ui(texture, type, coords) _glMultiTexCoordP3ui(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP3uiv(texture, type, coords) _glMultiTexCoordP3uiv(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP4ui(texture, type, coords) _glMultiTexCoordP4ui(texture, type, coords, __FILE__, __LINE__)
#define glMultiTexCoordP4uiv(texture, type, coords) _glMultiTexCoordP4uiv(texture, type, coords, __FILE__, __LINE__)
#define glNormalP3ui(type, coords) _glNormalP3ui(type, coords, __FILE__, __LINE__)
#define glNormalP3uiv(type, coords) _glNormalP3uiv(type, coords, __FILE__, __LINE__)
#define glColorP3ui(type, color) _glColorP3ui(type, color, __FILE__, __LINE__)
#define glColorP3uiv(type, color) _glColorP3uiv(type, color, __FILE__, __LINE__)
#define glColorP4ui(type, color) _glColorP4ui(type, color, __FILE__, __LINE__)
#define glColorP4uiv(type, color) _glColorP4uiv(type, color, __FILE__, __LINE__)
#define glSecondaryColorP3ui(type, color) _glSecondaryColorP3ui(type, color, __FILE__, __LINE__)
#define glSecondaryColorP3uiv(type, color) _glSecondaryColorP3uiv(type, color, __FILE__, __LINE__)
#define glMinSampleShading(value) _glMinSampleShading(value, __FILE__, __LINE__)
#define glBlendEquationi(buf, mode) _glBlendEquationi(buf, mode, __FILE__, __LINE__)
#define glBlendEquationSeparatei(buf, modeRGB, modeAlpha) _glBlendEquationSeparatei(buf, modeRGB, modeAlpha, __FILE__, __LINE__)
#define glBlendFunci(buf, src, dst) _glBlendFunci(buf, src, dst, __FILE__, __LINE__)
#define glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha) _glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha, __FILE__, __LINE__)
#define glDrawArraysIndirect(mode, indirect) _glDrawArraysIndirect(mode, indirect, __FILE__, __LINE__)
#define glDrawElementsIndirect(mode, type, indirect) _glDrawElementsIndirect(mode, type, indirect, __FILE__, __LINE__)
#define glUniform1d(location, x) _glUniform1d(location, x, __FILE__, __LINE__)
#define glUniform2d(location, x, y) _glUniform2d(location, x, y, __FILE__, __LINE__)
#define glUniform3d(location, x, y, z) _glUniform3d(location, x, y, z, __FILE__, __LINE__)
#define glUniform4d(location, x, y, z, w) _glUniform4d(location, x, y, z, w, __FILE__, __LINE__)
#define glUniform1dv(location, count, value) _glUniform1dv(location, count, value, __FILE__, __LINE__)
#define glUniform2dv(location, count, value) _glUniform2dv(location, count, value, __FILE__, __LINE__)
#define glUniform3dv(location, count, value) _glUniform3dv(location, count, value, __FILE__, __LINE__)
#define glUniform4dv(location, count, value) _glUniform4dv(location, count, value, __FILE__, __LINE__)
#define glUniformMatrix2dv(location, count, transpose, value) _glUniformMatrix2dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3dv(location, count, transpose, value) _glUniformMatrix3dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4dv(location, count, transpose, value) _glUniformMatrix4dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix2x3dv(location, count, transpose, value) _glUniformMatrix2x3dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix2x4dv(location, count, transpose, value) _glUniformMatrix2x4dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3x2dv(location, count, transpose, value) _glUniformMatrix3x2dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3x4dv(location, count, transpose, value) _glUniformMatrix3x4dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4x2dv(location, count, transpose, value) _glUniformMatrix4x2dv(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4x3dv(location, count, transpose, value) _glUniformMatrix4x3dv(location, count, transpose, value, __FILE__, __LINE__)
#define glGetUniformdv(program, location, params) _glGetUniformdv(program, location, params, __FILE__, __LINE__)
#define glGetSubroutineUniformLocation(program, shadertype, name) _glGetSubroutineUniformLocation(program, shadertype, name, __FILE__, __LINE__)
#define glGetSubroutineIndex(program, shadertype, name) _glGetSubroutineIndex(program, shadertype, name, __FILE__, __LINE__)
#define glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values) _glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values, __FILE__, __LINE__)
#define glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name) _glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name, __FILE__, __LINE__)
#define glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name) _glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name, __FILE__, __LINE__)
#define glUniformSubroutinesuiv(shadertype, count, indices) _glUniformSubroutinesuiv(shadertype, count, indices, __FILE__, __LINE__)
#define glGetUniformSubroutineuiv(shadertype, location, params) _glGetUniformSubroutineuiv(shadertype, location, params, __FILE__, __LINE__)
#define glGetProgramStageiv(program, shadertype, pname, values) _glGetProgramStageiv(program, shadertype, pname, values, __FILE__, __LINE__)
#define glPatchParameteri(pname, value) _glPatchParameteri(pname, value, __FILE__, __LINE__)
#define glPatchParameterfv(pname, values) _glPatchParameterfv(pname, values, __FILE__, __LINE__)
#define glBindTransformFeedback(target, id) _glBindTransformFeedback(target, id, __FILE__, __LINE__)
#define glDeleteTransformFeedbacks(n, ids) _glDeleteTransformFeedbacks(n, ids, __FILE__, __LINE__)
#define glGenTransformFeedbacks(n, ids) _glGenTransformFeedbacks(n, ids, __FILE__, __LINE__)
#define glIsTransformFeedback(id) _glIsTransformFeedback(id, __FILE__, __LINE__)
#define glPauseTransformFeedback() _glPauseTransformFeedback(__FILE__, __LINE__)
#define glResumeTransformFeedback() _glResumeTransformFeedback(__FILE__, __LINE__)
#define glDrawTransformFeedback(mode, id) _glDrawTransformFeedback(mode, id, __FILE__, __LINE__)
#define glDrawTransformFeedbackStream(mode, id, stream) _glDrawTransformFeedbackStream(mode, id, stream, __FILE__, __LINE__)
#define glBeginQueryIndexed(target, index, id) _glBeginQueryIndexed(target, index, id, __FILE__, __LINE__)
#define glEndQueryIndexed(target, index) _glEndQueryIndexed(target, index, __FILE__, __LINE__)
#define glGetQueryIndexediv(target, index, pname, params) _glGetQueryIndexediv(target, index, pname, params, __FILE__, __LINE__)
#define glReleaseShaderCompiler() _glReleaseShaderCompiler(__FILE__, __LINE__)
#define glShaderBinary(count, shaders, binaryFormat, binary, length) _glShaderBinary(count, shaders, binaryFormat, binary, length, __FILE__, __LINE__)
#define glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision) _glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision, __FILE__, __LINE__)
#define glDepthRangef(n, f) _glDepthRangef(n, f, __FILE__, __LINE__)
#define glClearDepthf(d) _glClearDepthf(d, __FILE__, __LINE__)
#define glGetProgramBinary(program, bufSize, length, binaryFormat, binary) _glGetProgramBinary(program, bufSize, length, binaryFormat, binary, __FILE__, __LINE__)
#define glProgramBinary(program, binaryFormat, binary, length) _glProgramBinary(program, binaryFormat, binary, length, __FILE__, __LINE__)
#define glProgramParameteri(program, pname, value) _glProgramParameteri(program, pname, value, __FILE__, __LINE__)
#define glUseProgramStages(pipeline, stages, program) _glUseProgramStages(pipeline, stages, program, __FILE__, __LINE__)
#define glActiveShaderProgram(pipeline, program) _glActiveShaderProgram(pipeline, program, __FILE__, __LINE__)
#define glCreateShaderProgramv(type, count, strings) _glCreateShaderProgramv(type, count, strings, __FILE__, __LINE__)
#define glBindProgramPipeline(pipeline) _glBindProgramPipeline(pipeline, __FILE__, __LINE__)
#define glDeleteProgramPipelines(n, pipelines) _glDeleteProgramPipelines(n, pipelines, __FILE__, __LINE__)
#define glGenProgramPipelines(n, pipelines) _glGenProgramPipelines(n, pipelines, __FILE__, __LINE__)
#define glIsProgramPipeline(pipeline) _glIsProgramPipeline(pipeline, __FILE__, __LINE__)
#define glGetProgramPipelineiv(pipeline, pname, params) _glGetProgramPipelineiv(pipeline, pname, params, __FILE__, __LINE__)
#define glProgramUniform1i(program, location, v0) _glProgramUniform1i(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform1iv(program, location, count, value) _glProgramUniform1iv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1f(program, location, v0) _glProgramUniform1f(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform1fv(program, location, count, value) _glProgramUniform1fv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1d(program, location, v0) _glProgramUniform1d(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform1dv(program, location, count, value) _glProgramUniform1dv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1ui(program, location, v0) _glProgramUniform1ui(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform1uiv(program, location, count, value) _glProgramUniform1uiv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2i(program, location, v0, v1) _glProgramUniform2i(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform2iv(program, location, count, value) _glProgramUniform2iv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2f(program, location, v0, v1) _glProgramUniform2f(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform2fv(program, location, count, value) _glProgramUniform2fv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2d(program, location, v0, v1) _glProgramUniform2d(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform2dv(program, location, count, value) _glProgramUniform2dv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2ui(program, location, v0, v1) _glProgramUniform2ui(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform2uiv(program, location, count, value) _glProgramUniform2uiv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3i(program, location, v0, v1, v2) _glProgramUniform3i(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform3iv(program, location, count, value) _glProgramUniform3iv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3f(program, location, v0, v1, v2) _glProgramUniform3f(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform3fv(program, location, count, value) _glProgramUniform3fv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3d(program, location, v0, v1, v2) _glProgramUniform3d(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform3dv(program, location, count, value) _glProgramUniform3dv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3ui(program, location, v0, v1, v2) _glProgramUniform3ui(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform3uiv(program, location, count, value) _glProgramUniform3uiv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4i(program, location, v0, v1, v2, v3) _glProgramUniform4i(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform4iv(program, location, count, value) _glProgramUniform4iv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4f(program, location, v0, v1, v2, v3) _glProgramUniform4f(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform4fv(program, location, count, value) _glProgramUniform4fv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4d(program, location, v0, v1, v2, v3) _glProgramUniform4d(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform4dv(program, location, count, value) _glProgramUniform4dv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4ui(program, location, v0, v1, v2, v3) _glProgramUniform4ui(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform4uiv(program, location, count, value) _glProgramUniform4uiv(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2fv(program, location, count, transpose, value) _glProgramUniformMatrix2fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3fv(program, location, count, transpose, value) _glProgramUniformMatrix3fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4fv(program, location, count, transpose, value) _glProgramUniformMatrix4fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2dv(program, location, count, transpose, value) _glProgramUniformMatrix2dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3dv(program, location, count, transpose, value) _glProgramUniformMatrix3dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4dv(program, location, count, transpose, value) _glProgramUniformMatrix4dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x3fv(program, location, count, transpose, value) _glProgramUniformMatrix2x3fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x2fv(program, location, count, transpose, value) _glProgramUniformMatrix3x2fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x4fv(program, location, count, transpose, value) _glProgramUniformMatrix2x4fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x2fv(program, location, count, transpose, value) _glProgramUniformMatrix4x2fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x4fv(program, location, count, transpose, value) _glProgramUniformMatrix3x4fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x3fv(program, location, count, transpose, value) _glProgramUniformMatrix4x3fv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x3dv(program, location, count, transpose, value) _glProgramUniformMatrix2x3dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x2dv(program, location, count, transpose, value) _glProgramUniformMatrix3x2dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x4dv(program, location, count, transpose, value) _glProgramUniformMatrix2x4dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x2dv(program, location, count, transpose, value) _glProgramUniformMatrix4x2dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x4dv(program, location, count, transpose, value) _glProgramUniformMatrix3x4dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x3dv(program, location, count, transpose, value) _glProgramUniformMatrix4x3dv(program, location, count, transpose, value, __FILE__, __LINE__)
#define glValidateProgramPipeline(pipeline) _glValidateProgramPipeline(pipeline, __FILE__, __LINE__)
#define glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog) _glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog, __FILE__, __LINE__)
#define glVertexAttribL1d(index, x) _glVertexAttribL1d(index, x, __FILE__, __LINE__)
#define glVertexAttribL2d(index, x, y) _glVertexAttribL2d(index, x, y, __FILE__, __LINE__)
#define glVertexAttribL3d(index, x, y, z) _glVertexAttribL3d(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribL4d(index, x, y, z, w) _glVertexAttribL4d(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribL1dv(index, v) _glVertexAttribL1dv(index, v, __FILE__, __LINE__)
#define glVertexAttribL2dv(index, v) _glVertexAttribL2dv(index, v, __FILE__, __LINE__)
#define glVertexAttribL3dv(index, v) _glVertexAttribL3dv(index, v, __FILE__, __LINE__)
#define glVertexAttribL4dv(index, v) _glVertexAttribL4dv(index, v, __FILE__, __LINE__)
#define glVertexAttribLPointer(index, size, type, stride, pointer) _glVertexAttribLPointer(index, size, type, stride, pointer, __FILE__, __LINE__)
#define glGetVertexAttribLdv(index, pname, params) _glGetVertexAttribLdv(index, pname, params, __FILE__, __LINE__)
#define glViewportArrayv(first, count, v) _glViewportArrayv(first, count, v, __FILE__, __LINE__)
#define glViewportIndexedf(index, x, y, w, h) _glViewportIndexedf(index, x, y, w, h, __FILE__, __LINE__)
#define glViewportIndexedfv(index, v) _glViewportIndexedfv(index, v, __FILE__, __LINE__)
#define glScissorArrayv(first, count, v) _glScissorArrayv(first, count, v, __FILE__, __LINE__)
#define glScissorIndexed(index, left, bottom, width, height) _glScissorIndexed(index, left, bottom, width, height, __FILE__, __LINE__)
#define glScissorIndexedv(index, v) _glScissorIndexedv(index, v, __FILE__, __LINE__)
#define glDepthRangeArrayv(first, count, v) _glDepthRangeArrayv(first, count, v, __FILE__, __LINE__)
#define glDepthRangeIndexed(index, n, f) _glDepthRangeIndexed(index, n, f, __FILE__, __LINE__)
#define glGetFloati_v(target, index, data) _glGetFloati_v(target, index, data, __FILE__, __LINE__)
#define glGetDoublei_v(target, index, data) _glGetDoublei_v(target, index, data, __FILE__, __LINE__)
#define glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance) _glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance, __FILE__, __LINE__)
#define glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance) _glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance, __FILE__, __LINE__)
#define glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance) _glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance, __FILE__, __LINE__)
#define glGetInternalformativ(target, internalformat, pname, count, params) _glGetInternalformativ(target, internalformat, pname, count, params, __FILE__, __LINE__)
#define glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params) _glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params, __FILE__, __LINE__)
#define glBindImageTexture(unit, texture, level, layered, layer, access, format) _glBindImageTexture(unit, texture, level, layered, layer, access, format, __FILE__, __LINE__)
#define glMemoryBarrier(barriers) _glMemoryBarrier(barriers, __FILE__, __LINE__)
#define glTexStorage1D(target, levels, internalformat, width) _glTexStorage1D(target, levels, internalformat, width, __FILE__, __LINE__)
#define glTexStorage2D(target, levels, internalformat, width, height) _glTexStorage2D(target, levels, internalformat, width, height, __FILE__, __LINE__)
#define glTexStorage3D(target, levels, internalformat, width, height, depth) _glTexStorage3D(target, levels, internalformat, width, height, depth, __FILE__, __LINE__)
#define glDrawTransformFeedbackInstanced(mode, id, instancecount) _glDrawTransformFeedbackInstanced(mode, id, instancecount, __FILE__, __LINE__)
#define glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount) _glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount, __FILE__, __LINE__)
#define glTbufferMask3DFX(mask) _glTbufferMask3DFX(mask, __FILE__, __LINE__)
#define glDebugMessageEnableAMD(category, severity, count, ids, enabled) _glDebugMessageEnableAMD(category, severity, count, ids, enabled, __FILE__, __LINE__)
#define glDebugMessageInsertAMD(category, severity, id, length, buf) _glDebugMessageInsertAMD(category, severity, id, length, buf, __FILE__, __LINE__)
#define glDebugMessageCallbackAMD(callback, userParam) _glDebugMessageCallbackAMD(callback, userParam, __FILE__, __LINE__)
#define glGetDebugMessageLogAMD(count, bufSize, categories, severities, ids, lengths, message) _glGetDebugMessageLogAMD(count, bufSize, categories, severities, ids, lengths, message, __FILE__, __LINE__)
#define glBlendFuncIndexedAMD(buf, src, dst) _glBlendFuncIndexedAMD(buf, src, dst, __FILE__, __LINE__)
#define glBlendFuncSeparateIndexedAMD(buf, srcRGB, dstRGB, srcAlpha, dstAlpha) _glBlendFuncSeparateIndexedAMD(buf, srcRGB, dstRGB, srcAlpha, dstAlpha, __FILE__, __LINE__)
#define glBlendEquationIndexedAMD(buf, mode) _glBlendEquationIndexedAMD(buf, mode, __FILE__, __LINE__)
#define glBlendEquationSeparateIndexedAMD(buf, modeRGB, modeAlpha) _glBlendEquationSeparateIndexedAMD(buf, modeRGB, modeAlpha, __FILE__, __LINE__)
#define glRenderbufferStorageMultisampleAdvancedAMD(target, samples, storageSamples, internalformat, width, height) _glRenderbufferStorageMultisampleAdvancedAMD(target, samples, storageSamples, internalformat, width, height, __FILE__, __LINE__)
#define glNamedRenderbufferStorageMultisampleAdvancedAMD(renderbuffer, samples, storageSamples, internalformat, width, height) _glNamedRenderbufferStorageMultisampleAdvancedAMD(renderbuffer, samples, storageSamples, internalformat, width, height, __FILE__, __LINE__)
#define glFramebufferSamplePositionsfvAMD(target, numsamples, pixelindex, values) _glFramebufferSamplePositionsfvAMD(target, numsamples, pixelindex, values, __FILE__, __LINE__)
#define glNamedFramebufferSamplePositionsfvAMD(framebuffer, numsamples, pixelindex, values) _glNamedFramebufferSamplePositionsfvAMD(framebuffer, numsamples, pixelindex, values, __FILE__, __LINE__)
#define glGetFramebufferParameterfvAMD(target, pname, numsamples, pixelindex, size, values) _glGetFramebufferParameterfvAMD(target, pname, numsamples, pixelindex, size, values, __FILE__, __LINE__)
#define glGetNamedFramebufferParameterfvAMD(framebuffer, pname, numsamples, pixelindex, size, values) _glGetNamedFramebufferParameterfvAMD(framebuffer, pname, numsamples, pixelindex, size, values, __FILE__, __LINE__)
#define glUniform1i64NV(location, x) _glUniform1i64NV(location, x, __FILE__, __LINE__)
#define glUniform2i64NV(location, x, y) _glUniform2i64NV(location, x, y, __FILE__, __LINE__)
#define glUniform3i64NV(location, x, y, z) _glUniform3i64NV(location, x, y, z, __FILE__, __LINE__)
#define glUniform4i64NV(location, x, y, z, w) _glUniform4i64NV(location, x, y, z, w, __FILE__, __LINE__)
#define glUniform1i64vNV(location, count, value) _glUniform1i64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform2i64vNV(location, count, value) _glUniform2i64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform3i64vNV(location, count, value) _glUniform3i64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform4i64vNV(location, count, value) _glUniform4i64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform1ui64NV(location, x) _glUniform1ui64NV(location, x, __FILE__, __LINE__)
#define glUniform2ui64NV(location, x, y) _glUniform2ui64NV(location, x, y, __FILE__, __LINE__)
#define glUniform3ui64NV(location, x, y, z) _glUniform3ui64NV(location, x, y, z, __FILE__, __LINE__)
#define glUniform4ui64NV(location, x, y, z, w) _glUniform4ui64NV(location, x, y, z, w, __FILE__, __LINE__)
#define glUniform1ui64vNV(location, count, value) _glUniform1ui64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform2ui64vNV(location, count, value) _glUniform2ui64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform3ui64vNV(location, count, value) _glUniform3ui64vNV(location, count, value, __FILE__, __LINE__)
#define glUniform4ui64vNV(location, count, value) _glUniform4ui64vNV(location, count, value, __FILE__, __LINE__)
#define glGetUniformi64vNV(program, location, params) _glGetUniformi64vNV(program, location, params, __FILE__, __LINE__)
#define glGetUniformui64vNV(program, location, params) _glGetUniformui64vNV(program, location, params, __FILE__, __LINE__)
#define glProgramUniform1i64NV(program, location, x) _glProgramUniform1i64NV(program, location, x, __FILE__, __LINE__)
#define glProgramUniform2i64NV(program, location, x, y) _glProgramUniform2i64NV(program, location, x, y, __FILE__, __LINE__)
#define glProgramUniform3i64NV(program, location, x, y, z) _glProgramUniform3i64NV(program, location, x, y, z, __FILE__, __LINE__)
#define glProgramUniform4i64NV(program, location, x, y, z, w) _glProgramUniform4i64NV(program, location, x, y, z, w, __FILE__, __LINE__)
#define glProgramUniform1i64vNV(program, location, count, value) _glProgramUniform1i64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2i64vNV(program, location, count, value) _glProgramUniform2i64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3i64vNV(program, location, count, value) _glProgramUniform3i64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4i64vNV(program, location, count, value) _glProgramUniform4i64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1ui64NV(program, location, x) _glProgramUniform1ui64NV(program, location, x, __FILE__, __LINE__)
#define glProgramUniform2ui64NV(program, location, x, y) _glProgramUniform2ui64NV(program, location, x, y, __FILE__, __LINE__)
#define glProgramUniform3ui64NV(program, location, x, y, z) _glProgramUniform3ui64NV(program, location, x, y, z, __FILE__, __LINE__)
#define glProgramUniform4ui64NV(program, location, x, y, z, w) _glProgramUniform4ui64NV(program, location, x, y, z, w, __FILE__, __LINE__)
#define glProgramUniform1ui64vNV(program, location, count, value) _glProgramUniform1ui64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2ui64vNV(program, location, count, value) _glProgramUniform2ui64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3ui64vNV(program, location, count, value) _glProgramUniform3ui64vNV(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4ui64vNV(program, location, count, value) _glProgramUniform4ui64vNV(program, location, count, value, __FILE__, __LINE__)
#define glVertexAttribParameteriAMD(index, pname, param) _glVertexAttribParameteriAMD(index, pname, param, __FILE__, __LINE__)
#define glMultiDrawArraysIndirectAMD(mode, indirect, primcount, stride) _glMultiDrawArraysIndirectAMD(mode, indirect, primcount, stride, __FILE__, __LINE__)
#define glMultiDrawElementsIndirectAMD(mode, type, indirect, primcount, stride) _glMultiDrawElementsIndirectAMD(mode, type, indirect, primcount, stride, __FILE__, __LINE__)
#define glGenNamesAMD(identifier, num, names) _glGenNamesAMD(identifier, num, names, __FILE__, __LINE__)
#define glDeleteNamesAMD(identifier, num, names) _glDeleteNamesAMD(identifier, num, names, __FILE__, __LINE__)
#define glIsNameAMD(identifier, name) _glIsNameAMD(identifier, name, __FILE__, __LINE__)
#define glQueryObjectParameteruiAMD(target, id, pname, param) _glQueryObjectParameteruiAMD(target, id, pname, param, __FILE__, __LINE__)
#define glGetPerfMonitorGroupsAMD(numGroups, groupsSize, groups) _glGetPerfMonitorGroupsAMD(numGroups, groupsSize, groups, __FILE__, __LINE__)
#define glGetPerfMonitorCountersAMD(group, numCounters, maxActiveCounters, counterSize, counters) _glGetPerfMonitorCountersAMD(group, numCounters, maxActiveCounters, counterSize, counters, __FILE__, __LINE__)
#define glGetPerfMonitorGroupStringAMD(group, bufSize, length, groupString) _glGetPerfMonitorGroupStringAMD(group, bufSize, length, groupString, __FILE__, __LINE__)
#define glGetPerfMonitorCounterStringAMD(group, counter, bufSize, length, counterString) _glGetPerfMonitorCounterStringAMD(group, counter, bufSize, length, counterString, __FILE__, __LINE__)
#define glGetPerfMonitorCounterInfoAMD(group, counter, pname, data) _glGetPerfMonitorCounterInfoAMD(group, counter, pname, data, __FILE__, __LINE__)
#define glGenPerfMonitorsAMD(n, monitors) _glGenPerfMonitorsAMD(n, monitors, __FILE__, __LINE__)
#define glDeletePerfMonitorsAMD(n, monitors) _glDeletePerfMonitorsAMD(n, monitors, __FILE__, __LINE__)
#define glSelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList) _glSelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList, __FILE__, __LINE__)
#define glBeginPerfMonitorAMD(monitor) _glBeginPerfMonitorAMD(monitor, __FILE__, __LINE__)
#define glEndPerfMonitorAMD(monitor) _glEndPerfMonitorAMD(monitor, __FILE__, __LINE__)
#define glGetPerfMonitorCounterDataAMD(monitor, pname, dataSize, data, bytesWritten) _glGetPerfMonitorCounterDataAMD(monitor, pname, dataSize, data, bytesWritten, __FILE__, __LINE__)
#define glSetMultisamplefvAMD(pname, index, val) _glSetMultisamplefvAMD(pname, index, val, __FILE__, __LINE__)
#define glTexStorageSparseAMD(target, internalFormat, width, height, depth, layers, flags) _glTexStorageSparseAMD(target, internalFormat, width, height, depth, layers, flags, __FILE__, __LINE__)
#define glTextureStorageSparseAMD(texture, target, internalFormat, width, height, depth, layers, flags) _glTextureStorageSparseAMD(texture, target, internalFormat, width, height, depth, layers, flags, __FILE__, __LINE__)
#define glStencilOpValueAMD(face, value) _glStencilOpValueAMD(face, value, __FILE__, __LINE__)
#define glTessellationFactorAMD(factor) _glTessellationFactorAMD(factor, __FILE__, __LINE__)
#define glTessellationModeAMD(mode) _glTessellationModeAMD(mode, __FILE__, __LINE__)
#define glElementPointerAPPLE(type, pointer) _glElementPointerAPPLE(type, pointer, __FILE__, __LINE__)
#define glDrawElementArrayAPPLE(mode, first, count) _glDrawElementArrayAPPLE(mode, first, count, __FILE__, __LINE__)
#define glDrawRangeElementArrayAPPLE(mode, start, end, first, count) _glDrawRangeElementArrayAPPLE(mode, start, end, first, count, __FILE__, __LINE__)
#define glMultiDrawElementArrayAPPLE(mode, first, count, primcount) _glMultiDrawElementArrayAPPLE(mode, first, count, primcount, __FILE__, __LINE__)
#define glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount) _glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount, __FILE__, __LINE__)
#define glGenFencesAPPLE(n, fences) _glGenFencesAPPLE(n, fences, __FILE__, __LINE__)
#define glDeleteFencesAPPLE(n, fences) _glDeleteFencesAPPLE(n, fences, __FILE__, __LINE__)
#define glSetFenceAPPLE(fence) _glSetFenceAPPLE(fence, __FILE__, __LINE__)
#define glIsFenceAPPLE(fence) _glIsFenceAPPLE(fence, __FILE__, __LINE__)
#define glTestFenceAPPLE(fence) _glTestFenceAPPLE(fence, __FILE__, __LINE__)
#define glFinishFenceAPPLE(fence) _glFinishFenceAPPLE(fence, __FILE__, __LINE__)
#define glTestObjectAPPLE(object, name) _glTestObjectAPPLE(object, name, __FILE__, __LINE__)
#define glFinishObjectAPPLE(object, name) _glFinishObjectAPPLE(object, name, __FILE__, __LINE__)
#define glBufferParameteriAPPLE(target, pname, param) _glBufferParameteriAPPLE(target, pname, param, __FILE__, __LINE__)
#define glFlushMappedBufferRangeAPPLE(target, offset, size) _glFlushMappedBufferRangeAPPLE(target, offset, size, __FILE__, __LINE__)
#define glObjectPurgeableAPPLE(objectType, name, option) _glObjectPurgeableAPPLE(objectType, name, option, __FILE__, __LINE__)
#define glObjectUnpurgeableAPPLE(objectType, name, option) _glObjectUnpurgeableAPPLE(objectType, name, option, __FILE__, __LINE__)
#define glGetObjectParameterivAPPLE(objectType, name, pname, params) _glGetObjectParameterivAPPLE(objectType, name, pname, params, __FILE__, __LINE__)
#define glTextureRangeAPPLE(target, length, pointer) _glTextureRangeAPPLE(target, length, pointer, __FILE__, __LINE__)
#define glGetTexParameterPointervAPPLE(target, pname, params) _glGetTexParameterPointervAPPLE(target, pname, params, __FILE__, __LINE__)
#define glBindVertexArrayAPPLE(array) _glBindVertexArrayAPPLE(array, __FILE__, __LINE__)
#define glDeleteVertexArraysAPPLE(n, arrays) _glDeleteVertexArraysAPPLE(n, arrays, __FILE__, __LINE__)
#define glGenVertexArraysAPPLE(n, arrays) _glGenVertexArraysAPPLE(n, arrays, __FILE__, __LINE__)
#define glIsVertexArrayAPPLE(array) _glIsVertexArrayAPPLE(array, __FILE__, __LINE__)
#define glVertexArrayRangeAPPLE(length, pointer) _glVertexArrayRangeAPPLE(length, pointer, __FILE__, __LINE__)
#define glFlushVertexArrayRangeAPPLE(length, pointer) _glFlushVertexArrayRangeAPPLE(length, pointer, __FILE__, __LINE__)
#define glVertexArrayParameteriAPPLE(pname, param) _glVertexArrayParameteriAPPLE(pname, param, __FILE__, __LINE__)
#define glEnableVertexAttribAPPLE(index, pname) _glEnableVertexAttribAPPLE(index, pname, __FILE__, __LINE__)
#define glDisableVertexAttribAPPLE(index, pname) _glDisableVertexAttribAPPLE(index, pname, __FILE__, __LINE__)
#define glIsVertexAttribEnabledAPPLE(index, pname) _glIsVertexAttribEnabledAPPLE(index, pname, __FILE__, __LINE__)
#define glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points) _glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points, __FILE__, __LINE__)
#define glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points) _glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points, __FILE__, __LINE__)
#define glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) _glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points, __FILE__, __LINE__)
#define glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) _glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points, __FILE__, __LINE__)
#define glMemoryBarrierByRegion(barriers) _glMemoryBarrierByRegion(barriers, __FILE__, __LINE__)
#define glPrimitiveBoundingBoxARB(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW) _glPrimitiveBoundingBoxARB(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW, __FILE__, __LINE__)
#define glGetTextureHandleARB(texture) _glGetTextureHandleARB(texture, __FILE__, __LINE__)
#define glGetTextureSamplerHandleARB(texture, sampler) _glGetTextureSamplerHandleARB(texture, sampler, __FILE__, __LINE__)
#define glMakeTextureHandleResidentARB(handle) _glMakeTextureHandleResidentARB(handle, __FILE__, __LINE__)
#define glMakeTextureHandleNonResidentARB(handle) _glMakeTextureHandleNonResidentARB(handle, __FILE__, __LINE__)
#define glGetImageHandleARB(texture, level, layered, layer, format) _glGetImageHandleARB(texture, level, layered, layer, format, __FILE__, __LINE__)
#define glMakeImageHandleResidentARB(handle, access) _glMakeImageHandleResidentARB(handle, access, __FILE__, __LINE__)
#define glMakeImageHandleNonResidentARB(handle) _glMakeImageHandleNonResidentARB(handle, __FILE__, __LINE__)
#define glUniformHandleui64ARB(location, value) _glUniformHandleui64ARB(location, value, __FILE__, __LINE__)
#define glUniformHandleui64vARB(location, count, value) _glUniformHandleui64vARB(location, count, value, __FILE__, __LINE__)
#define glProgramUniformHandleui64ARB(program, location, value) _glProgramUniformHandleui64ARB(program, location, value, __FILE__, __LINE__)
#define glProgramUniformHandleui64vARB(program, location, count, values) _glProgramUniformHandleui64vARB(program, location, count, values, __FILE__, __LINE__)
#define glIsTextureHandleResidentARB(handle) _glIsTextureHandleResidentARB(handle, __FILE__, __LINE__)
#define glIsImageHandleResidentARB(handle) _glIsImageHandleResidentARB(handle, __FILE__, __LINE__)
#define glVertexAttribL1ui64ARB(index, x) _glVertexAttribL1ui64ARB(index, x, __FILE__, __LINE__)
#define glVertexAttribL1ui64vARB(index, v) _glVertexAttribL1ui64vARB(index, v, __FILE__, __LINE__)
#define glGetVertexAttribLui64vARB(index, pname, params) _glGetVertexAttribLui64vARB(index, pname, params, __FILE__, __LINE__)
#define glBufferStorage(target, size, data, flags) _glBufferStorage(target, size, data, flags, __FILE__, __LINE__)
#define glCreateSyncFromCLeventARB(context, event, flags) _glCreateSyncFromCLeventARB(context, event, flags, __FILE__, __LINE__)
#define glClearBufferData(target, internalformat, format, type, data) _glClearBufferData(target, internalformat, format, type, data, __FILE__, __LINE__)
#define glClearBufferSubData(target, internalformat, offset, size, format, type, data) _glClearBufferSubData(target, internalformat, offset, size, format, type, data, __FILE__, __LINE__)
#define glClearTexImage(texture, level, format, type, data) _glClearTexImage(texture, level, format, type, data, __FILE__, __LINE__)
#define glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data) _glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data, __FILE__, __LINE__)
#define glClipControl(origin, depth) _glClipControl(origin, depth, __FILE__, __LINE__)
#define glClampColorARB(target, clamp) _glClampColorARB(target, clamp, __FILE__, __LINE__)
#define glDispatchCompute(num_groups_x, num_groups_y, num_groups_z) _glDispatchCompute(num_groups_x, num_groups_y, num_groups_z, __FILE__, __LINE__)
#define glDispatchComputeIndirect(indirect) _glDispatchComputeIndirect(indirect, __FILE__, __LINE__)
#define glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z) _glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z, __FILE__, __LINE__)
#define glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth) _glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth, __FILE__, __LINE__)
#define glDebugMessageControlARB(source, type, severity, count, ids, enabled) _glDebugMessageControlARB(source, type, severity, count, ids, enabled, __FILE__, __LINE__)
#define glDebugMessageInsertARB(source, type, id, severity, length, buf) _glDebugMessageInsertARB(source, type, id, severity, length, buf, __FILE__, __LINE__)
#define glDebugMessageCallbackARB(callback, userParam) _glDebugMessageCallbackARB(callback, userParam, __FILE__, __LINE__)
#define glGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog) _glGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog, __FILE__, __LINE__)
#define glCreateTransformFeedbacks(n, ids) _glCreateTransformFeedbacks(n, ids, __FILE__, __LINE__)
#define glTransformFeedbackBufferBase(xfb, index, buffer) _glTransformFeedbackBufferBase(xfb, index, buffer, __FILE__, __LINE__)
#define glTransformFeedbackBufferRange(xfb, index, buffer, offset, size) _glTransformFeedbackBufferRange(xfb, index, buffer, offset, size, __FILE__, __LINE__)
#define glGetTransformFeedbackiv(xfb, pname, param) _glGetTransformFeedbackiv(xfb, pname, param, __FILE__, __LINE__)
#define glGetTransformFeedbacki_v(xfb, pname, index, param) _glGetTransformFeedbacki_v(xfb, pname, index, param, __FILE__, __LINE__)
#define glGetTransformFeedbacki64_v(xfb, pname, index, param) _glGetTransformFeedbacki64_v(xfb, pname, index, param, __FILE__, __LINE__)
#define glCreateBuffers(n, buffers) _glCreateBuffers(n, buffers, __FILE__, __LINE__)
#define glNamedBufferStorage(buffer, size, data, flags) _glNamedBufferStorage(buffer, size, data, flags, __FILE__, __LINE__)
#define glNamedBufferData(buffer, size, data, usage) _glNamedBufferData(buffer, size, data, usage, __FILE__, __LINE__)
#define glNamedBufferSubData(buffer, offset, size, data) _glNamedBufferSubData(buffer, offset, size, data, __FILE__, __LINE__)
#define glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size) _glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size, __FILE__, __LINE__)
#define glClearNamedBufferData(buffer, internalformat, format, type, data) _glClearNamedBufferData(buffer, internalformat, format, type, data, __FILE__, __LINE__)
#define glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data) _glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data, __FILE__, __LINE__)
#define glMapNamedBuffer(buffer, _) _glMapNamedBuffer(buffer, _, __FILE__, __LINE__)
#define glMapNamedBufferRange(buffer, offset, length, _) _glMapNamedBufferRange(buffer, offset, length, _, __FILE__, __LINE__)
#define glUnmapNamedBuffer(buffer) _glUnmapNamedBuffer(buffer, __FILE__, __LINE__)
#define glFlushMappedNamedBufferRange(buffer, offset, length) _glFlushMappedNamedBufferRange(buffer, offset, length, __FILE__, __LINE__)
#define glGetNamedBufferParameteriv(buffer, pname, params) _glGetNamedBufferParameteriv(buffer, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferParameteri64v(buffer, pname, params) _glGetNamedBufferParameteri64v(buffer, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferPointerv(buffer, pname, params) _glGetNamedBufferPointerv(buffer, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferSubData(buffer, offset, size, data) _glGetNamedBufferSubData(buffer, offset, size, data, __FILE__, __LINE__)
#define glCreateFramebuffers(n, framebuffers) _glCreateFramebuffers(n, framebuffers, __FILE__, __LINE__)
#define glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer) _glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer, __FILE__, __LINE__)
#define glNamedFramebufferParameteri(framebuffer, pname, param) _glNamedFramebufferParameteri(framebuffer, pname, param, __FILE__, __LINE__)
#define glNamedFramebufferTexture(framebuffer, attachment, texture, level) _glNamedFramebufferTexture(framebuffer, attachment, texture, level, __FILE__, __LINE__)
#define glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer) _glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer, __FILE__, __LINE__)
#define glNamedFramebufferDrawBuffer(framebuffer, buf) _glNamedFramebufferDrawBuffer(framebuffer, buf, __FILE__, __LINE__)
#define glNamedFramebufferDrawBuffers(framebuffer, n, bufs) _glNamedFramebufferDrawBuffers(framebuffer, n, bufs, __FILE__, __LINE__)
#define glNamedFramebufferReadBuffer(framebuffer, src) _glNamedFramebufferReadBuffer(framebuffer, src, __FILE__, __LINE__)
#define glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments) _glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments, __FILE__, __LINE__)
#define glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height) _glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height, __FILE__, __LINE__)
#define glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value) _glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value) _glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value) _glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value, __FILE__, __LINE__)
#define glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil) _glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil, __FILE__, __LINE__)
#define glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) _glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter, __FILE__, __LINE__)
#define glCheckNamedFramebufferStatus(framebuffer, target) _glCheckNamedFramebufferStatus(framebuffer, target, __FILE__, __LINE__)
#define glGetNamedFramebufferParameteriv(framebuffer, pname, param) _glGetNamedFramebufferParameteriv(framebuffer, pname, param, __FILE__, __LINE__)
#define glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params) _glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params, __FILE__, __LINE__)
#define glCreateRenderbuffers(n, renderbuffers) _glCreateRenderbuffers(n, renderbuffers, __FILE__, __LINE__)
#define glNamedRenderbufferStorage(renderbuffer, internalformat, width, height) _glNamedRenderbufferStorage(renderbuffer, internalformat, width, height, __FILE__, __LINE__)
#define glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height) _glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height, __FILE__, __LINE__)
#define glGetNamedRenderbufferParameteriv(renderbuffer, pname, params) _glGetNamedRenderbufferParameteriv(renderbuffer, pname, params, __FILE__, __LINE__)
#define glCreateTextures(target, n, textures) _glCreateTextures(target, n, textures, __FILE__, __LINE__)
#define glTextureBuffer(texture, internalformat, buffer) _glTextureBuffer(texture, internalformat, buffer, __FILE__, __LINE__)
#define glTextureBufferRange(texture, internalformat, buffer, offset, size) _glTextureBufferRange(texture, internalformat, buffer, offset, size, __FILE__, __LINE__)
#define glTextureStorage1D(texture, levels, internalformat, width) _glTextureStorage1D(texture, levels, internalformat, width, __FILE__, __LINE__)
#define glTextureStorage2D(texture, levels, internalformat, width, height) _glTextureStorage2D(texture, levels, internalformat, width, height, __FILE__, __LINE__)
#define glTextureStorage3D(texture, levels, internalformat, width, height, depth) _glTextureStorage3D(texture, levels, internalformat, width, height, depth, __FILE__, __LINE__)
#define glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations) _glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations, __FILE__, __LINE__)
#define glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations) _glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations, __FILE__, __LINE__)
#define glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels) _glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels, __FILE__, __LINE__)
#define glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels) _glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels, __FILE__, __LINE__)
#define glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) _glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels, __FILE__, __LINE__)
#define glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data) _glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data) _glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) _glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data, __FILE__, __LINE__)
#define glCopyTextureSubImage1D(texture, level, xoffset, x, y, width) _glCopyTextureSubImage1D(texture, level, xoffset, x, y, width, __FILE__, __LINE__)
#define glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height) _glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height, __FILE__, __LINE__)
#define glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height) _glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height, __FILE__, __LINE__)
#define glTextureParameterf(texture, pname, param) _glTextureParameterf(texture, pname, param, __FILE__, __LINE__)
#define glTextureParameterfv(texture, pname, param) _glTextureParameterfv(texture, pname, param, __FILE__, __LINE__)
#define glTextureParameteri(texture, pname, param) _glTextureParameteri(texture, pname, param, __FILE__, __LINE__)
#define glTextureParameterIiv(texture, pname, params) _glTextureParameterIiv(texture, pname, params, __FILE__, __LINE__)
#define glTextureParameterIuiv(texture, pname, params) _glTextureParameterIuiv(texture, pname, params, __FILE__, __LINE__)
#define glTextureParameteriv(texture, pname, param) _glTextureParameteriv(texture, pname, param, __FILE__, __LINE__)
#define glGenerateTextureMipmap(texture) _glGenerateTextureMipmap(texture, __FILE__, __LINE__)
#define glBindTextureUnit(unit, texture) _glBindTextureUnit(unit, texture, __FILE__, __LINE__)
#define glGetTextureImage(texture, level, format, type, bufSize, pixels) _glGetTextureImage(texture, level, format, type, bufSize, pixels, __FILE__, __LINE__)
#define glGetCompressedTextureImage(texture, level, bufSize, pixels) _glGetCompressedTextureImage(texture, level, bufSize, pixels, __FILE__, __LINE__)
#define glGetTextureLevelParameterfv(texture, level, pname, params) _glGetTextureLevelParameterfv(texture, level, pname, params, __FILE__, __LINE__)
#define glGetTextureLevelParameteriv(texture, level, pname, params) _glGetTextureLevelParameteriv(texture, level, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterfv(texture, pname, params) _glGetTextureParameterfv(texture, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterIiv(texture, pname, params) _glGetTextureParameterIiv(texture, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterIuiv(texture, pname, params) _glGetTextureParameterIuiv(texture, pname, params, __FILE__, __LINE__)
#define glGetTextureParameteriv(texture, pname, params) _glGetTextureParameteriv(texture, pname, params, __FILE__, __LINE__)
#define glCreateVertexArrays(n, arrays) _glCreateVertexArrays(n, arrays, __FILE__, __LINE__)
#define glDisableVertexArrayAttrib(vaobj, index) _glDisableVertexArrayAttrib(vaobj, index, __FILE__, __LINE__)
#define glEnableVertexArrayAttrib(vaobj, index) _glEnableVertexArrayAttrib(vaobj, index, __FILE__, __LINE__)
#define glVertexArrayElementBuffer(vaobj, buffer) _glVertexArrayElementBuffer(vaobj, buffer, __FILE__, __LINE__)
#define glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride) _glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride, __FILE__, __LINE__)
#define glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides) _glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides, __FILE__, __LINE__)
#define glVertexArrayAttribBinding(vaobj, attribindex, bindingindex) _glVertexArrayAttribBinding(vaobj, attribindex, bindingindex, __FILE__, __LINE__)
#define glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset) _glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset) _glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset) _glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayBindingDivisor(vaobj, bindingindex, divisor) _glVertexArrayBindingDivisor(vaobj, bindingindex, divisor, __FILE__, __LINE__)
#define glGetVertexArrayiv(vaobj, pname, param) _glGetVertexArrayiv(vaobj, pname, param, __FILE__, __LINE__)
#define glGetVertexArrayIndexediv(vaobj, index, pname, param) _glGetVertexArrayIndexediv(vaobj, index, pname, param, __FILE__, __LINE__)
#define glGetVertexArrayIndexed64iv(vaobj, index, pname, param) _glGetVertexArrayIndexed64iv(vaobj, index, pname, param, __FILE__, __LINE__)
#define glCreateSamplers(n, samplers) _glCreateSamplers(n, samplers, __FILE__, __LINE__)
#define glCreateProgramPipelines(n, pipelines) _glCreateProgramPipelines(n, pipelines, __FILE__, __LINE__)
#define glCreateQueries(target, n, ids) _glCreateQueries(target, n, ids, __FILE__, __LINE__)
#define glGetQueryBufferObjecti64v(id, buffer, pname, offset) _glGetQueryBufferObjecti64v(id, buffer, pname, offset, __FILE__, __LINE__)
#define glGetQueryBufferObjectiv(id, buffer, pname, offset) _glGetQueryBufferObjectiv(id, buffer, pname, offset, __FILE__, __LINE__)
#define glGetQueryBufferObjectui64v(id, buffer, pname, offset) _glGetQueryBufferObjectui64v(id, buffer, pname, offset, __FILE__, __LINE__)
#define glGetQueryBufferObjectuiv(id, buffer, pname, offset) _glGetQueryBufferObjectuiv(id, buffer, pname, offset, __FILE__, __LINE__)
#define glDrawBuffersARB(n, bufs) _glDrawBuffersARB(n, bufs, __FILE__, __LINE__)
#define glBlendEquationiARB(buf, mode) _glBlendEquationiARB(buf, mode, __FILE__, __LINE__)
#define glBlendEquationSeparateiARB(buf, modeRGB, modeAlpha) _glBlendEquationSeparateiARB(buf, modeRGB, modeAlpha, __FILE__, __LINE__)
#define glBlendFunciARB(buf, src, dst) _glBlendFunciARB(buf, src, dst, __FILE__, __LINE__)
#define glBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha) _glBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha, __FILE__, __LINE__)
#define glDrawArraysInstancedARB(mode, first, count, primcount) _glDrawArraysInstancedARB(mode, first, count, primcount, __FILE__, __LINE__)
#define glDrawElementsInstancedARB(mode, count, type, indices, primcount) _glDrawElementsInstancedARB(mode, count, type, indices, primcount, __FILE__, __LINE__)
#define glProgramStringARB(target, format, len, string) _glProgramStringARB(target, format, len, string, __FILE__, __LINE__)
#define glBindProgramARB(target, program) _glBindProgramARB(target, program, __FILE__, __LINE__)
#define glDeleteProgramsARB(n, programs) _glDeleteProgramsARB(n, programs, __FILE__, __LINE__)
#define glGenProgramsARB(n, programs) _glGenProgramsARB(n, programs, __FILE__, __LINE__)
#define glProgramEnvParameter4dARB(target, index, x, y, z, w) _glProgramEnvParameter4dARB(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramEnvParameter4dvARB(target, index, params) _glProgramEnvParameter4dvARB(target, index, params, __FILE__, __LINE__)
#define glProgramEnvParameter4fARB(target, index, x, y, z, w) _glProgramEnvParameter4fARB(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramEnvParameter4fvARB(target, index, params) _glProgramEnvParameter4fvARB(target, index, params, __FILE__, __LINE__)
#define glProgramLocalParameter4dARB(target, index, x, y, z, w) _glProgramLocalParameter4dARB(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramLocalParameter4dvARB(target, index, params) _glProgramLocalParameter4dvARB(target, index, params, __FILE__, __LINE__)
#define glProgramLocalParameter4fARB(target, index, x, y, z, w) _glProgramLocalParameter4fARB(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramLocalParameter4fvARB(target, index, params) _glProgramLocalParameter4fvARB(target, index, params, __FILE__, __LINE__)
#define glGetProgramEnvParameterdvARB(target, index, params) _glGetProgramEnvParameterdvARB(target, index, params, __FILE__, __LINE__)
#define glGetProgramEnvParameterfvARB(target, index, params) _glGetProgramEnvParameterfvARB(target, index, params, __FILE__, __LINE__)
#define glGetProgramLocalParameterdvARB(target, index, params) _glGetProgramLocalParameterdvARB(target, index, params, __FILE__, __LINE__)
#define glGetProgramLocalParameterfvARB(target, index, params) _glGetProgramLocalParameterfvARB(target, index, params, __FILE__, __LINE__)
#define glGetProgramivARB(target, pname, params) _glGetProgramivARB(target, pname, params, __FILE__, __LINE__)
#define glGetProgramStringARB(target, pname, string) _glGetProgramStringARB(target, pname, string, __FILE__, __LINE__)
#define glIsProgramARB(program) _glIsProgramARB(program, __FILE__, __LINE__)
#define glFramebufferParameteri(target, pname, param) _glFramebufferParameteri(target, pname, param, __FILE__, __LINE__)
#define glGetFramebufferParameteriv(target, pname, params) _glGetFramebufferParameteriv(target, pname, params, __FILE__, __LINE__)
#define glProgramParameteriARB(program, pname, value) _glProgramParameteriARB(program, pname, value, __FILE__, __LINE__)
#define glFramebufferTextureARB(target, attachment, texture, level) _glFramebufferTextureARB(target, attachment, texture, level, __FILE__, __LINE__)
#define glFramebufferTextureLayerARB(target, attachment, texture, level, layer) _glFramebufferTextureLayerARB(target, attachment, texture, level, layer, __FILE__, __LINE__)
#define glFramebufferTextureFaceARB(target, attachment, texture, level, face) _glFramebufferTextureFaceARB(target, attachment, texture, level, face, __FILE__, __LINE__)
#define glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels) _glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels, __FILE__, __LINE__)
#define glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels) _glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels, __FILE__, __LINE__)
#define glSpecializeShaderARB(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue) _glSpecializeShaderARB(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue, __FILE__, __LINE__)
#define glUniform1i64ARB(location, x) _glUniform1i64ARB(location, x, __FILE__, __LINE__)
#define glUniform2i64ARB(location, x, y) _glUniform2i64ARB(location, x, y, __FILE__, __LINE__)
#define glUniform3i64ARB(location, x, y, z) _glUniform3i64ARB(location, x, y, z, __FILE__, __LINE__)
#define glUniform4i64ARB(location, x, y, z, w) _glUniform4i64ARB(location, x, y, z, w, __FILE__, __LINE__)
#define glUniform1i64vARB(location, count, value) _glUniform1i64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform2i64vARB(location, count, value) _glUniform2i64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform3i64vARB(location, count, value) _glUniform3i64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform4i64vARB(location, count, value) _glUniform4i64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform1ui64ARB(location, x) _glUniform1ui64ARB(location, x, __FILE__, __LINE__)
#define glUniform2ui64ARB(location, x, y) _glUniform2ui64ARB(location, x, y, __FILE__, __LINE__)
#define glUniform3ui64ARB(location, x, y, z) _glUniform3ui64ARB(location, x, y, z, __FILE__, __LINE__)
#define glUniform4ui64ARB(location, x, y, z, w) _glUniform4ui64ARB(location, x, y, z, w, __FILE__, __LINE__)
#define glUniform1ui64vARB(location, count, value) _glUniform1ui64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform2ui64vARB(location, count, value) _glUniform2ui64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform3ui64vARB(location, count, value) _glUniform3ui64vARB(location, count, value, __FILE__, __LINE__)
#define glUniform4ui64vARB(location, count, value) _glUniform4ui64vARB(location, count, value, __FILE__, __LINE__)
#define glGetUniformi64vARB(program, location, params) _glGetUniformi64vARB(program, location, params, __FILE__, __LINE__)
#define glGetUniformui64vARB(program, location, params) _glGetUniformui64vARB(program, location, params, __FILE__, __LINE__)
#define glGetnUniformi64vARB(program, location, bufSize, params) _glGetnUniformi64vARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformui64vARB(program, location, bufSize, params) _glGetnUniformui64vARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glProgramUniform1i64ARB(program, location, x) _glProgramUniform1i64ARB(program, location, x, __FILE__, __LINE__)
#define glProgramUniform2i64ARB(program, location, x, y) _glProgramUniform2i64ARB(program, location, x, y, __FILE__, __LINE__)
#define glProgramUniform3i64ARB(program, location, x, y, z) _glProgramUniform3i64ARB(program, location, x, y, z, __FILE__, __LINE__)
#define glProgramUniform4i64ARB(program, location, x, y, z, w) _glProgramUniform4i64ARB(program, location, x, y, z, w, __FILE__, __LINE__)
#define glProgramUniform1i64vARB(program, location, count, value) _glProgramUniform1i64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2i64vARB(program, location, count, value) _glProgramUniform2i64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3i64vARB(program, location, count, value) _glProgramUniform3i64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4i64vARB(program, location, count, value) _glProgramUniform4i64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1ui64ARB(program, location, x) _glProgramUniform1ui64ARB(program, location, x, __FILE__, __LINE__)
#define glProgramUniform2ui64ARB(program, location, x, y) _glProgramUniform2ui64ARB(program, location, x, y, __FILE__, __LINE__)
#define glProgramUniform3ui64ARB(program, location, x, y, z) _glProgramUniform3ui64ARB(program, location, x, y, z, __FILE__, __LINE__)
#define glProgramUniform4ui64ARB(program, location, x, y, z, w) _glProgramUniform4ui64ARB(program, location, x, y, z, w, __FILE__, __LINE__)
#define glProgramUniform1ui64vARB(program, location, count, value) _glProgramUniform1ui64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2ui64vARB(program, location, count, value) _glProgramUniform2ui64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3ui64vARB(program, location, count, value) _glProgramUniform3ui64vARB(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4ui64vARB(program, location, count, value) _glProgramUniform4ui64vARB(program, location, count, value, __FILE__, __LINE__)
#define glColorTable(target, internalformat, width, format, type, table) _glColorTable(target, internalformat, width, format, type, table, __FILE__, __LINE__)
#define glColorTableParameterfv(target, pname, params) _glColorTableParameterfv(target, pname, params, __FILE__, __LINE__)
#define glColorTableParameteriv(target, pname, params) _glColorTableParameteriv(target, pname, params, __FILE__, __LINE__)
#define glCopyColorTable(target, internalformat, x, y, width) _glCopyColorTable(target, internalformat, x, y, width, __FILE__, __LINE__)
#define glGetColorTable(target, format, type, table) _glGetColorTable(target, format, type, table, __FILE__, __LINE__)
#define glGetColorTableParameterfv(target, pname, params) _glGetColorTableParameterfv(target, pname, params, __FILE__, __LINE__)
#define glGetColorTableParameteriv(target, pname, params) _glGetColorTableParameteriv(target, pname, params, __FILE__, __LINE__)
#define glColorSubTable(target, start, count, format, type, data) _glColorSubTable(target, start, count, format, type, data, __FILE__, __LINE__)
#define glCopyColorSubTable(target, start, x, y, width) _glCopyColorSubTable(target, start, x, y, width, __FILE__, __LINE__)
#define glConvolutionFilter1D(target, internalformat, width, format, type, image) _glConvolutionFilter1D(target, internalformat, width, format, type, image, __FILE__, __LINE__)
#define glConvolutionFilter2D(target, internalformat, width, height, format, type, image) _glConvolutionFilter2D(target, internalformat, width, height, format, type, image, __FILE__, __LINE__)
#define glConvolutionParameterf(target, pname, params) _glConvolutionParameterf(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameterfv(target, pname, params) _glConvolutionParameterfv(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameteri(target, pname, params) _glConvolutionParameteri(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameteriv(target, pname, params) _glConvolutionParameteriv(target, pname, params, __FILE__, __LINE__)
#define glCopyConvolutionFilter1D(target, internalformat, x, y, width) _glCopyConvolutionFilter1D(target, internalformat, x, y, width, __FILE__, __LINE__)
#define glCopyConvolutionFilter2D(target, internalformat, x, y, width, height) _glCopyConvolutionFilter2D(target, internalformat, x, y, width, height, __FILE__, __LINE__)
#define glGetConvolutionFilter(target, format, type, image) _glGetConvolutionFilter(target, format, type, image, __FILE__, __LINE__)
#define glGetConvolutionParameterfv(target, pname, params) _glGetConvolutionParameterfv(target, pname, params, __FILE__, __LINE__)
#define glGetConvolutionParameteriv(target, pname, params) _glGetConvolutionParameteriv(target, pname, params, __FILE__, __LINE__)
#define glGetSeparableFilter(target, format, type, row, column, span) _glGetSeparableFilter(target, format, type, row, column, span, __FILE__, __LINE__)
#define glSeparableFilter2D(target, internalformat, width, height, format, type, row, column) _glSeparableFilter2D(target, internalformat, width, height, format, type, row, column, __FILE__, __LINE__)
#define glGetHistogram(target, reset, format, type, values) _glGetHistogram(target, reset, format, type, values, __FILE__, __LINE__)
#define glGetHistogramParameterfv(target, pname, params) _glGetHistogramParameterfv(target, pname, params, __FILE__, __LINE__)
#define glGetHistogramParameteriv(target, pname, params) _glGetHistogramParameteriv(target, pname, params, __FILE__, __LINE__)
#define glGetMinmax(target, reset, format, type, values) _glGetMinmax(target, reset, format, type, values, __FILE__, __LINE__)
#define glGetMinmaxParameterfv(target, pname, params) _glGetMinmaxParameterfv(target, pname, params, __FILE__, __LINE__)
#define glGetMinmaxParameteriv(target, pname, params) _glGetMinmaxParameteriv(target, pname, params, __FILE__, __LINE__)
#define glHistogram(target, width, internalformat, sink) _glHistogram(target, width, internalformat, sink, __FILE__, __LINE__)
#define glMinmax(target, internalformat, sink) _glMinmax(target, internalformat, sink, __FILE__, __LINE__)
#define glResetHistogram(target) _glResetHistogram(target, __FILE__, __LINE__)
#define glResetMinmax(target) _glResetMinmax(target, __FILE__, __LINE__)
#define glMultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride) _glMultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride, __FILE__, __LINE__)
#define glMultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride) _glMultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride, __FILE__, __LINE__)
#define glVertexAttribDivisorARB(index, divisor) _glVertexAttribDivisorARB(index, divisor, __FILE__, __LINE__)
#define glGetInternalformati64v(target, internalformat, pname, count, params) _glGetInternalformati64v(target, internalformat, pname, count, params, __FILE__, __LINE__)
#define glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth) _glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, __FILE__, __LINE__)
#define glInvalidateTexImage(texture, level) _glInvalidateTexImage(texture, level, __FILE__, __LINE__)
#define glInvalidateBufferSubData(buffer, offset, length) _glInvalidateBufferSubData(buffer, offset, length, __FILE__, __LINE__)
#define glInvalidateBufferData(buffer) _glInvalidateBufferData(buffer, __FILE__, __LINE__)
#define glInvalidateFramebuffer(target, numAttachments, attachments) _glInvalidateFramebuffer(target, numAttachments, attachments, __FILE__, __LINE__)
#define glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height) _glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height, __FILE__, __LINE__)
#define glCurrentPaletteMatrixARB(index) _glCurrentPaletteMatrixARB(index, __FILE__, __LINE__)
#define glMatrixIndexubvARB(size, indices) _glMatrixIndexubvARB(size, indices, __FILE__, __LINE__)
#define glMatrixIndexusvARB(size, indices) _glMatrixIndexusvARB(size, indices, __FILE__, __LINE__)
#define glMatrixIndexuivARB(size, indices) _glMatrixIndexuivARB(size, indices, __FILE__, __LINE__)
#define glMatrixIndexPointerARB(size, type, stride, pointer) _glMatrixIndexPointerARB(size, type, stride, pointer, __FILE__, __LINE__)
#define glBindBuffersBase(target, first, count, buffers) _glBindBuffersBase(target, first, count, buffers, __FILE__, __LINE__)
#define glBindBuffersRange(target, first, count, buffers, offsets, sizes) _glBindBuffersRange(target, first, count, buffers, offsets, sizes, __FILE__, __LINE__)
#define glBindTextures(first, count, textures) _glBindTextures(first, count, textures, __FILE__, __LINE__)
#define glBindSamplers(first, count, samplers) _glBindSamplers(first, count, samplers, __FILE__, __LINE__)
#define glBindImageTextures(first, count, textures) _glBindImageTextures(first, count, textures, __FILE__, __LINE__)
#define glBindVertexBuffers(first, count, buffers, offsets, strides) _glBindVertexBuffers(first, count, buffers, offsets, strides, __FILE__, __LINE__)
#define glMultiDrawArraysIndirect(mode, indirect, drawcount, stride) _glMultiDrawArraysIndirect(mode, indirect, drawcount, stride, __FILE__, __LINE__)
#define glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride) _glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride, __FILE__, __LINE__)
#define glSampleCoverageARB(value, invert) _glSampleCoverageARB(value, invert, __FILE__, __LINE__)
#define glActiveTextureARB(texture) _glActiveTextureARB(texture, __FILE__, __LINE__)
#define glClientActiveTextureARB(texture) _glClientActiveTextureARB(texture, __FILE__, __LINE__)
#define glMultiTexCoord1dARB(target, s) _glMultiTexCoord1dARB(target, s, __FILE__, __LINE__)
#define glMultiTexCoord1dvARB(target, v) _glMultiTexCoord1dvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord1fARB(target, s) _glMultiTexCoord1fARB(target, s, __FILE__, __LINE__)
#define glMultiTexCoord1fvARB(target, v) _glMultiTexCoord1fvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord1iARB(target, s) _glMultiTexCoord1iARB(target, s, __FILE__, __LINE__)
#define glMultiTexCoord1ivARB(target, v) _glMultiTexCoord1ivARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord1sARB(target, s) _glMultiTexCoord1sARB(target, s, __FILE__, __LINE__)
#define glMultiTexCoord1svARB(target, v) _glMultiTexCoord1svARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord2dARB(target, s, t) _glMultiTexCoord2dARB(target, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2dvARB(target, v) _glMultiTexCoord2dvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord2fARB(target, s, t) _glMultiTexCoord2fARB(target, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2fvARB(target, v) _glMultiTexCoord2fvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord2iARB(target, s, t) _glMultiTexCoord2iARB(target, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2ivARB(target, v) _glMultiTexCoord2ivARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord2sARB(target, s, t) _glMultiTexCoord2sARB(target, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2svARB(target, v) _glMultiTexCoord2svARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord3dARB(target, s, t, r) _glMultiTexCoord3dARB(target, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3dvARB(target, v) _glMultiTexCoord3dvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord3fARB(target, s, t, r) _glMultiTexCoord3fARB(target, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3fvARB(target, v) _glMultiTexCoord3fvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord3iARB(target, s, t, r) _glMultiTexCoord3iARB(target, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3ivARB(target, v) _glMultiTexCoord3ivARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord3sARB(target, s, t, r) _glMultiTexCoord3sARB(target, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3svARB(target, v) _glMultiTexCoord3svARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord4dARB(target, s, t, r, q) _glMultiTexCoord4dARB(target, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4dvARB(target, v) _glMultiTexCoord4dvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord4fARB(target, s, t, r, q) _glMultiTexCoord4fARB(target, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4fvARB(target, v) _glMultiTexCoord4fvARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord4iARB(target, s, t, r, q) _glMultiTexCoord4iARB(target, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4ivARB(target, v) _glMultiTexCoord4ivARB(target, v, __FILE__, __LINE__)
#define glMultiTexCoord4sARB(target, s, t, r, q) _glMultiTexCoord4sARB(target, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4svARB(target, v) _glMultiTexCoord4svARB(target, v, __FILE__, __LINE__)
#define glGenQueriesARB(n, ids) _glGenQueriesARB(n, ids, __FILE__, __LINE__)
#define glDeleteQueriesARB(n, ids) _glDeleteQueriesARB(n, ids, __FILE__, __LINE__)
#define glIsQueryARB(id) _glIsQueryARB(id, __FILE__, __LINE__)
#define glBeginQueryARB(target, id) _glBeginQueryARB(target, id, __FILE__, __LINE__)
#define glEndQueryARB(target) _glEndQueryARB(target, __FILE__, __LINE__)
#define glGetQueryivARB(target, pname, params) _glGetQueryivARB(target, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectivARB(id, pname, params) _glGetQueryObjectivARB(id, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectuivARB(id, pname, params) _glGetQueryObjectuivARB(id, pname, params, __FILE__, __LINE__)
#define glMaxShaderCompilerThreadsARB(count) _glMaxShaderCompilerThreadsARB(count, __FILE__, __LINE__)
#define glPointParameterfARB(pname, param) _glPointParameterfARB(pname, param, __FILE__, __LINE__)
#define glPointParameterfvARB(pname, params) _glPointParameterfvARB(pname, params, __FILE__, __LINE__)
#define glPolygonOffsetClamp(factor, units, clamp) _glPolygonOffsetClamp(factor, units, clamp, __FILE__, __LINE__)
#define glGetProgramInterfaceiv(program, programInterface, pname, params) _glGetProgramInterfaceiv(program, programInterface, pname, params, __FILE__, __LINE__)
#define glGetProgramResourceIndex(program, programInterface, name) _glGetProgramResourceIndex(program, programInterface, name, __FILE__, __LINE__)
#define glGetProgramResourceName(program, programInterface, index, bufSize, length, name) _glGetProgramResourceName(program, programInterface, index, bufSize, length, name, __FILE__, __LINE__)
#define glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params) _glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params, __FILE__, __LINE__)
#define glGetProgramResourceLocation(program, programInterface, name) _glGetProgramResourceLocation(program, programInterface, name, __FILE__, __LINE__)
#define glGetProgramResourceLocationIndex(program, programInterface, name) _glGetProgramResourceLocationIndex(program, programInterface, name, __FILE__, __LINE__)
#define glGetGraphicsResetStatusARB() _glGetGraphicsResetStatusARB(__FILE__, __LINE__)
#define glGetnTexImageARB(target, level, format, type, bufSize, img) _glGetnTexImageARB(target, level, format, type, bufSize, img, __FILE__, __LINE__)
#define glReadnPixelsARB(x, y, width, height, format, type, bufSize, data) _glReadnPixelsARB(x, y, width, height, format, type, bufSize, data, __FILE__, __LINE__)
#define glGetnCompressedTexImageARB(target, lod, bufSize, img) _glGetnCompressedTexImageARB(target, lod, bufSize, img, __FILE__, __LINE__)
#define glGetnUniformfvARB(program, location, bufSize, params) _glGetnUniformfvARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformivARB(program, location, bufSize, params) _glGetnUniformivARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformuivARB(program, location, bufSize, params) _glGetnUniformuivARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformdvARB(program, location, bufSize, params) _glGetnUniformdvARB(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnMapdvARB(target, query, bufSize, v) _glGetnMapdvARB(target, query, bufSize, v, __FILE__, __LINE__)
#define glGetnMapfvARB(target, query, bufSize, v) _glGetnMapfvARB(target, query, bufSize, v, __FILE__, __LINE__)
#define glGetnMapivARB(target, query, bufSize, v) _glGetnMapivARB(target, query, bufSize, v, __FILE__, __LINE__)
#define glGetnPixelMapfvARB(map, bufSize, values) _glGetnPixelMapfvARB(map, bufSize, values, __FILE__, __LINE__)
#define glGetnPixelMapuivARB(map, bufSize, values) _glGetnPixelMapuivARB(map, bufSize, values, __FILE__, __LINE__)
#define glGetnPixelMapusvARB(map, bufSize, values) _glGetnPixelMapusvARB(map, bufSize, values, __FILE__, __LINE__)
#define glGetnPolygonStippleARB(bufSize, pattern) _glGetnPolygonStippleARB(bufSize, pattern, __FILE__, __LINE__)
#define glGetnColorTableARB(target, format, type, bufSize, table) _glGetnColorTableARB(target, format, type, bufSize, table, __FILE__, __LINE__)
#define glGetnConvolutionFilterARB(target, format, type, bufSize, image) _glGetnConvolutionFilterARB(target, format, type, bufSize, image, __FILE__, __LINE__)
#define glGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span) _glGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span, __FILE__, __LINE__)
#define glGetnHistogramARB(target, reset, format, type, bufSize, values) _glGetnHistogramARB(target, reset, format, type, bufSize, values, __FILE__, __LINE__)
#define glGetnMinmaxARB(target, reset, format, type, bufSize, values) _glGetnMinmaxARB(target, reset, format, type, bufSize, values, __FILE__, __LINE__)
#define glFramebufferSampleLocationsfvARB(target, start, count, v) _glFramebufferSampleLocationsfvARB(target, start, count, v, __FILE__, __LINE__)
#define glNamedFramebufferSampleLocationsfvARB(framebuffer, start, count, v) _glNamedFramebufferSampleLocationsfvARB(framebuffer, start, count, v, __FILE__, __LINE__)
#define glEvaluateDepthValuesARB() _glEvaluateDepthValuesARB(__FILE__, __LINE__)
#define glMinSampleShadingARB(value) _glMinSampleShadingARB(value, __FILE__, __LINE__)
#define glDeleteObjectARB(obj) _glDeleteObjectARB(obj, __FILE__, __LINE__)
#define glGetHandleARB(pname) _glGetHandleARB(pname, __FILE__, __LINE__)
#define glDetachObjectARB(containerObj, attachedObj) _glDetachObjectARB(containerObj, attachedObj, __FILE__, __LINE__)
#define glCreateShaderObjectARB(shaderType) _glCreateShaderObjectARB(shaderType, __FILE__, __LINE__)
#define glShaderSourceARB(shaderObj, count, string, length) _glShaderSourceARB(shaderObj, count, string, length, __FILE__, __LINE__)
#define glCompileShaderARB(shaderObj) _glCompileShaderARB(shaderObj, __FILE__, __LINE__)
#define glCreateProgramObjectARB() _glCreateProgramObjectARB(__FILE__, __LINE__)
#define glAttachObjectARB(containerObj, obj) _glAttachObjectARB(containerObj, obj, __FILE__, __LINE__)
#define glLinkProgramARB(programObj) _glLinkProgramARB(programObj, __FILE__, __LINE__)
#define glUseProgramObjectARB(programObj) _glUseProgramObjectARB(programObj, __FILE__, __LINE__)
#define glValidateProgramARB(programObj) _glValidateProgramARB(programObj, __FILE__, __LINE__)
#define glUniform1fARB(location, v0) _glUniform1fARB(location, v0, __FILE__, __LINE__)
#define glUniform2fARB(location, v0, v1) _glUniform2fARB(location, v0, v1, __FILE__, __LINE__)
#define glUniform3fARB(location, v0, v1, v2) _glUniform3fARB(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4fARB(location, v0, v1, v2, v3) _glUniform4fARB(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1iARB(location, v0) _glUniform1iARB(location, v0, __FILE__, __LINE__)
#define glUniform2iARB(location, v0, v1) _glUniform2iARB(location, v0, v1, __FILE__, __LINE__)
#define glUniform3iARB(location, v0, v1, v2) _glUniform3iARB(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4iARB(location, v0, v1, v2, v3) _glUniform4iARB(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1fvARB(location, count, value) _glUniform1fvARB(location, count, value, __FILE__, __LINE__)
#define glUniform2fvARB(location, count, value) _glUniform2fvARB(location, count, value, __FILE__, __LINE__)
#define glUniform3fvARB(location, count, value) _glUniform3fvARB(location, count, value, __FILE__, __LINE__)
#define glUniform4fvARB(location, count, value) _glUniform4fvARB(location, count, value, __FILE__, __LINE__)
#define glUniform1ivARB(location, count, value) _glUniform1ivARB(location, count, value, __FILE__, __LINE__)
#define glUniform2ivARB(location, count, value) _glUniform2ivARB(location, count, value, __FILE__, __LINE__)
#define glUniform3ivARB(location, count, value) _glUniform3ivARB(location, count, value, __FILE__, __LINE__)
#define glUniform4ivARB(location, count, value) _glUniform4ivARB(location, count, value, __FILE__, __LINE__)
#define glUniformMatrix2fvARB(location, count, transpose, value) _glUniformMatrix2fvARB(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix3fvARB(location, count, transpose, value) _glUniformMatrix3fvARB(location, count, transpose, value, __FILE__, __LINE__)
#define glUniformMatrix4fvARB(location, count, transpose, value) _glUniformMatrix4fvARB(location, count, transpose, value, __FILE__, __LINE__)
#define glGetObjectParameterfvARB(obj, pname, params) _glGetObjectParameterfvARB(obj, pname, params, __FILE__, __LINE__)
#define glGetObjectParameterivARB(obj, pname, params) _glGetObjectParameterivARB(obj, pname, params, __FILE__, __LINE__)
#define glGetInfoLogARB(obj, maxLength, length, infoLog) _glGetInfoLogARB(obj, maxLength, length, infoLog, __FILE__, __LINE__)
#define glGetAttachedObjectsARB(containerObj, maxCount, count, obj) _glGetAttachedObjectsARB(containerObj, maxCount, count, obj, __FILE__, __LINE__)
#define glGetUniformLocationARB(programObj, name) _glGetUniformLocationARB(programObj, name, __FILE__, __LINE__)
#define glGetActiveUniformARB(programObj, index, maxLength, length, size, type, name) _glGetActiveUniformARB(programObj, index, maxLength, length, size, type, name, __FILE__, __LINE__)
#define glGetUniformfvARB(programObj, location, params) _glGetUniformfvARB(programObj, location, params, __FILE__, __LINE__)
#define glGetUniformivARB(programObj, location, params) _glGetUniformivARB(programObj, location, params, __FILE__, __LINE__)
#define glGetShaderSourceARB(obj, maxLength, length, source) _glGetShaderSourceARB(obj, maxLength, length, source, __FILE__, __LINE__)
#define glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding) _glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding, __FILE__, __LINE__)
#define glNamedStringARB(type, namelen, name, stringlen, string) _glNamedStringARB(type, namelen, name, stringlen, string, __FILE__, __LINE__)
#define glDeleteNamedStringARB(namelen, name) _glDeleteNamedStringARB(namelen, name, __FILE__, __LINE__)
#define glCompileShaderIncludeARB(shader, count, path, length) _glCompileShaderIncludeARB(shader, count, path, length, __FILE__, __LINE__)
#define glIsNamedStringARB(namelen, name) _glIsNamedStringARB(namelen, name, __FILE__, __LINE__)
#define glGetNamedStringARB(namelen, name, bufSize, stringlen, string) _glGetNamedStringARB(namelen, name, bufSize, stringlen, string, __FILE__, __LINE__)
#define glGetNamedStringivARB(namelen, name, pname, params) _glGetNamedStringivARB(namelen, name, pname, params, __FILE__, __LINE__)
#define glBufferPageCommitmentARB(target, offset, size, commit) _glBufferPageCommitmentARB(target, offset, size, commit, __FILE__, __LINE__)
#define glNamedBufferPageCommitmentEXT(buffer, offset, size, commit) _glNamedBufferPageCommitmentEXT(buffer, offset, size, commit, __FILE__, __LINE__)
#define glNamedBufferPageCommitmentARB(buffer, offset, size, commit) _glNamedBufferPageCommitmentARB(buffer, offset, size, commit, __FILE__, __LINE__)
#define glTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, commit) _glTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, commit, __FILE__, __LINE__)
#define glTextureBarrier() _glTextureBarrier(__FILE__, __LINE__)
#define glTexBufferARB(target, internalformat, buffer) _glTexBufferARB(target, internalformat, buffer, __FILE__, __LINE__)
#define glTexBufferRange(target, internalformat, buffer, offset, size) _glTexBufferRange(target, internalformat, buffer, offset, size, __FILE__, __LINE__)
#define glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data) _glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data) _glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data) _glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) _glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data) _glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data, __FILE__, __LINE__)
#define glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data) _glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data, __FILE__, __LINE__)
#define glGetCompressedTexImageARB(target, level, img) _glGetCompressedTexImageARB(target, level, img, __FILE__, __LINE__)
#define glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations) _glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations, __FILE__, __LINE__)
#define glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations) _glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations, __FILE__, __LINE__)
#define glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers) _glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers, __FILE__, __LINE__)
#define glLoadTransposeMatrixfARB(m) _glLoadTransposeMatrixfARB(m, __FILE__, __LINE__)
#define glLoadTransposeMatrixdARB(m) _glLoadTransposeMatrixdARB(m, __FILE__, __LINE__)
#define glMultTransposeMatrixfARB(m) _glMultTransposeMatrixfARB(m, __FILE__, __LINE__)
#define glMultTransposeMatrixdARB(m) _glMultTransposeMatrixdARB(m, __FILE__, __LINE__)
#define glBindVertexBuffer(bindingindex, buffer, offset, stride) _glBindVertexBuffer(bindingindex, buffer, offset, stride, __FILE__, __LINE__)
#define glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset) _glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset, __FILE__, __LINE__)
#define glVertexAttribIFormat(attribindex, size, type, relativeoffset) _glVertexAttribIFormat(attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexAttribLFormat(attribindex, size, type, relativeoffset) _glVertexAttribLFormat(attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexAttribBinding(attribindex, bindingindex) _glVertexAttribBinding(attribindex, bindingindex, __FILE__, __LINE__)
#define glVertexBindingDivisor(bindingindex, divisor) _glVertexBindingDivisor(bindingindex, divisor, __FILE__, __LINE__)
#define glWeightbvARB(size, weights) _glWeightbvARB(size, weights, __FILE__, __LINE__)
#define glWeightsvARB(size, weights) _glWeightsvARB(size, weights, __FILE__, __LINE__)
#define glWeightivARB(size, weights) _glWeightivARB(size, weights, __FILE__, __LINE__)
#define glWeightfvARB(size, weights) _glWeightfvARB(size, weights, __FILE__, __LINE__)
#define glWeightdvARB(size, weights) _glWeightdvARB(size, weights, __FILE__, __LINE__)
#define glWeightubvARB(size, weights) _glWeightubvARB(size, weights, __FILE__, __LINE__)
#define glWeightusvARB(size, weights) _glWeightusvARB(size, weights, __FILE__, __LINE__)
#define glWeightuivARB(size, weights) _glWeightuivARB(size, weights, __FILE__, __LINE__)
#define glWeightPointerARB(size, type, stride, pointer) _glWeightPointerARB(size, type, stride, pointer, __FILE__, __LINE__)
#define glVertexBlendARB(count) _glVertexBlendARB(count, __FILE__, __LINE__)
#define glBindBufferARB(target, buffer) _glBindBufferARB(target, buffer, __FILE__, __LINE__)
#define glDeleteBuffersARB(n, buffers) _glDeleteBuffersARB(n, buffers, __FILE__, __LINE__)
#define glGenBuffersARB(n, buffers) _glGenBuffersARB(n, buffers, __FILE__, __LINE__)
#define glIsBufferARB(buffer) _glIsBufferARB(buffer, __FILE__, __LINE__)
#define glBufferDataARB(target, size, data, usage) _glBufferDataARB(target, size, data, usage, __FILE__, __LINE__)
#define glBufferSubDataARB(target, offset, size, data) _glBufferSubDataARB(target, offset, size, data, __FILE__, __LINE__)
#define glGetBufferSubDataARB(target, offset, size, data) _glGetBufferSubDataARB(target, offset, size, data, __FILE__, __LINE__)
#define glMapBufferARB(target, _) _glMapBufferARB(target, _, __FILE__, __LINE__)
#define glUnmapBufferARB(target) _glUnmapBufferARB(target, __FILE__, __LINE__)
#define glGetBufferParameterivARB(target, pname, params) _glGetBufferParameterivARB(target, pname, params, __FILE__, __LINE__)
#define glGetBufferPointervARB(target, pname, params) _glGetBufferPointervARB(target, pname, params, __FILE__, __LINE__)
#define glVertexAttrib1dARB(index, x) _glVertexAttrib1dARB(index, x, __FILE__, __LINE__)
#define glVertexAttrib1dvARB(index, v) _glVertexAttrib1dvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib1fARB(index, x) _glVertexAttrib1fARB(index, x, __FILE__, __LINE__)
#define glVertexAttrib1fvARB(index, v) _glVertexAttrib1fvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib1sARB(index, x) _glVertexAttrib1sARB(index, x, __FILE__, __LINE__)
#define glVertexAttrib1svARB(index, v) _glVertexAttrib1svARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib2dARB(index, x, y) _glVertexAttrib2dARB(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2dvARB(index, v) _glVertexAttrib2dvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib2fARB(index, x, y) _glVertexAttrib2fARB(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2fvARB(index, v) _glVertexAttrib2fvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib2sARB(index, x, y) _glVertexAttrib2sARB(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2svARB(index, v) _glVertexAttrib2svARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib3dARB(index, x, y, z) _glVertexAttrib3dARB(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3dvARB(index, v) _glVertexAttrib3dvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib3fARB(index, x, y, z) _glVertexAttrib3fARB(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3fvARB(index, v) _glVertexAttrib3fvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib3sARB(index, x, y, z) _glVertexAttrib3sARB(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3svARB(index, v) _glVertexAttrib3svARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NbvARB(index, v) _glVertexAttrib4NbvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NivARB(index, v) _glVertexAttrib4NivARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NsvARB(index, v) _glVertexAttrib4NsvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NubARB(index, x, y, z, w) _glVertexAttrib4NubARB(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4NubvARB(index, v) _glVertexAttrib4NubvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NuivARB(index, v) _glVertexAttrib4NuivARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4NusvARB(index, v) _glVertexAttrib4NusvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4bvARB(index, v) _glVertexAttrib4bvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4dARB(index, x, y, z, w) _glVertexAttrib4dARB(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4dvARB(index, v) _glVertexAttrib4dvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4fARB(index, x, y, z, w) _glVertexAttrib4fARB(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4fvARB(index, v) _glVertexAttrib4fvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4ivARB(index, v) _glVertexAttrib4ivARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4sARB(index, x, y, z, w) _glVertexAttrib4sARB(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4svARB(index, v) _glVertexAttrib4svARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4ubvARB(index, v) _glVertexAttrib4ubvARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4uivARB(index, v) _glVertexAttrib4uivARB(index, v, __FILE__, __LINE__)
#define glVertexAttrib4usvARB(index, v) _glVertexAttrib4usvARB(index, v, __FILE__, __LINE__)
#define glVertexAttribPointerARB(index, size, type, normalized, stride, pointer) _glVertexAttribPointerARB(index, size, type, normalized, stride, pointer, __FILE__, __LINE__)
#define glEnableVertexAttribArrayARB(index) _glEnableVertexAttribArrayARB(index, __FILE__, __LINE__)
#define glDisableVertexAttribArrayARB(index) _glDisableVertexAttribArrayARB(index, __FILE__, __LINE__)
#define glGetVertexAttribdvARB(index, pname, params) _glGetVertexAttribdvARB(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribfvARB(index, pname, params) _glGetVertexAttribfvARB(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribivARB(index, pname, params) _glGetVertexAttribivARB(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribPointervARB(index, pname, pointer) _glGetVertexAttribPointervARB(index, pname, pointer, __FILE__, __LINE__)
#define glBindAttribLocationARB(programObj, index, name) _glBindAttribLocationARB(programObj, index, name, __FILE__, __LINE__)
#define glGetActiveAttribARB(programObj, index, maxLength, length, size, type, name) _glGetActiveAttribARB(programObj, index, maxLength, length, size, type, name, __FILE__, __LINE__)
#define glGetAttribLocationARB(programObj, name) _glGetAttribLocationARB(programObj, name, __FILE__, __LINE__)
#define glDepthRangeArraydvNV(first, count, v) _glDepthRangeArraydvNV(first, count, v, __FILE__, __LINE__)
#define glDepthRangeIndexeddNV(index, n, f) _glDepthRangeIndexeddNV(index, n, f, __FILE__, __LINE__)
#define glWindowPos2dARB(x, y) _glWindowPos2dARB(x, y, __FILE__, __LINE__)
#define glWindowPos2dvARB(v) _glWindowPos2dvARB(v, __FILE__, __LINE__)
#define glWindowPos2fARB(x, y) _glWindowPos2fARB(x, y, __FILE__, __LINE__)
#define glWindowPos2fvARB(v) _glWindowPos2fvARB(v, __FILE__, __LINE__)
#define glWindowPos2iARB(x, y) _glWindowPos2iARB(x, y, __FILE__, __LINE__)
#define glWindowPos2ivARB(v) _glWindowPos2ivARB(v, __FILE__, __LINE__)
#define glWindowPos2sARB(x, y) _glWindowPos2sARB(x, y, __FILE__, __LINE__)
#define glWindowPos2svARB(v) _glWindowPos2svARB(v, __FILE__, __LINE__)
#define glWindowPos3dARB(x, y, z) _glWindowPos3dARB(x, y, z, __FILE__, __LINE__)
#define glWindowPos3dvARB(v) _glWindowPos3dvARB(v, __FILE__, __LINE__)
#define glWindowPos3fARB(x, y, z) _glWindowPos3fARB(x, y, z, __FILE__, __LINE__)
#define glWindowPos3fvARB(v) _glWindowPos3fvARB(v, __FILE__, __LINE__)
#define glWindowPos3iARB(x, y, z) _glWindowPos3iARB(x, y, z, __FILE__, __LINE__)
#define glWindowPos3ivARB(v) _glWindowPos3ivARB(v, __FILE__, __LINE__)
#define glWindowPos3sARB(x, y, z) _glWindowPos3sARB(x, y, z, __FILE__, __LINE__)
#define glWindowPos3svARB(v) _glWindowPos3svARB(v, __FILE__, __LINE__)
#define glDrawBuffersATI(n, bufs) _glDrawBuffersATI(n, bufs, __FILE__, __LINE__)
#define glElementPointerATI(type, pointer) _glElementPointerATI(type, pointer, __FILE__, __LINE__)
#define glDrawElementArrayATI(mode, count) _glDrawElementArrayATI(mode, count, __FILE__, __LINE__)
#define glDrawRangeElementArrayATI(mode, start, end, count) _glDrawRangeElementArrayATI(mode, start, end, count, __FILE__, __LINE__)
#define glTexBumpParameterivATI(pname, param) _glTexBumpParameterivATI(pname, param, __FILE__, __LINE__)
#define glTexBumpParameterfvATI(pname, param) _glTexBumpParameterfvATI(pname, param, __FILE__, __LINE__)
#define glGetTexBumpParameterivATI(pname, param) _glGetTexBumpParameterivATI(pname, param, __FILE__, __LINE__)
#define glGetTexBumpParameterfvATI(pname, param) _glGetTexBumpParameterfvATI(pname, param, __FILE__, __LINE__)
#define glGenFragmentShadersATI(range) _glGenFragmentShadersATI(range, __FILE__, __LINE__)
#define glBindFragmentShaderATI(id) _glBindFragmentShaderATI(id, __FILE__, __LINE__)
#define glDeleteFragmentShaderATI(id) _glDeleteFragmentShaderATI(id, __FILE__, __LINE__)
#define glBeginFragmentShaderATI() _glBeginFragmentShaderATI(__FILE__, __LINE__)
#define glEndFragmentShaderATI() _glEndFragmentShaderATI(__FILE__, __LINE__)
#define glPassTexCoordATI(dst, coord, swizzle) _glPassTexCoordATI(dst, coord, swizzle, __FILE__, __LINE__)
#define glSampleMapATI(dst, interp, swizzle) _glSampleMapATI(dst, interp, swizzle, __FILE__, __LINE__)
#define glColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod) _glColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, __FILE__, __LINE__)
#define glColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod) _glColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, __FILE__, __LINE__)
#define glColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod) _glColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod, __FILE__, __LINE__)
#define glAlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod) _glAlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, __FILE__, __LINE__)
#define glAlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod) _glAlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, __FILE__, __LINE__)
#define glAlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod) _glAlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod, __FILE__, __LINE__)
#define glSetFragmentShaderConstantATI(dst, value) _glSetFragmentShaderConstantATI(dst, value, __FILE__, __LINE__)
#define glMapObjectBufferATI(_) _glMapObjectBufferATI(_, __FILE__, __LINE__)
#define glUnmapObjectBufferATI(buffer) _glUnmapObjectBufferATI(buffer, __FILE__, __LINE__)
#define glPNTrianglesiATI(pname, param) _glPNTrianglesiATI(pname, param, __FILE__, __LINE__)
#define glPNTrianglesfATI(pname, param) _glPNTrianglesfATI(pname, param, __FILE__, __LINE__)
#define glStencilOpSeparateATI(face, sfail, dpfail, dppass) _glStencilOpSeparateATI(face, sfail, dpfail, dppass, __FILE__, __LINE__)
#define glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask) _glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask, __FILE__, __LINE__)
#define glNewObjectBufferATI(size, pointer, usage) _glNewObjectBufferATI(size, pointer, usage, __FILE__, __LINE__)
#define glIsObjectBufferATI(buffer) _glIsObjectBufferATI(buffer, __FILE__, __LINE__)
#define glUpdateObjectBufferATI(buffer, offset, size, pointer, preserve) _glUpdateObjectBufferATI(buffer, offset, size, pointer, preserve, __FILE__, __LINE__)
#define glGetObjectBufferfvATI(buffer, pname, params) _glGetObjectBufferfvATI(buffer, pname, params, __FILE__, __LINE__)
#define glGetObjectBufferivATI(buffer, pname, params) _glGetObjectBufferivATI(buffer, pname, params, __FILE__, __LINE__)
#define glFreeObjectBufferATI(buffer) _glFreeObjectBufferATI(buffer, __FILE__, __LINE__)
#define glArrayObjectATI(array, size, type, stride, buffer, offset) _glArrayObjectATI(array, size, type, stride, buffer, offset, __FILE__, __LINE__)
#define glGetArrayObjectfvATI(array, pname, params) _glGetArrayObjectfvATI(array, pname, params, __FILE__, __LINE__)
#define glGetArrayObjectivATI(array, pname, params) _glGetArrayObjectivATI(array, pname, params, __FILE__, __LINE__)
#define glVariantArrayObjectATI(id, type, stride, buffer, offset) _glVariantArrayObjectATI(id, type, stride, buffer, offset, __FILE__, __LINE__)
#define glGetVariantArrayObjectfvATI(id, pname, params) _glGetVariantArrayObjectfvATI(id, pname, params, __FILE__, __LINE__)
#define glGetVariantArrayObjectivATI(id, pname, params) _glGetVariantArrayObjectivATI(id, pname, params, __FILE__, __LINE__)
#define glVertexAttribArrayObjectATI(index, size, type, normalized, stride, buffer, offset) _glVertexAttribArrayObjectATI(index, size, type, normalized, stride, buffer, offset, __FILE__, __LINE__)
#define glGetVertexAttribArrayObjectfvATI(index, pname, params) _glGetVertexAttribArrayObjectfvATI(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribArrayObjectivATI(index, pname, params) _glGetVertexAttribArrayObjectivATI(index, pname, params, __FILE__, __LINE__)
#define glVertexStream1sATI(stream, x) _glVertexStream1sATI(stream, x, __FILE__, __LINE__)
#define glVertexStream1svATI(stream, coords) _glVertexStream1svATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream1iATI(stream, x) _glVertexStream1iATI(stream, x, __FILE__, __LINE__)
#define glVertexStream1ivATI(stream, coords) _glVertexStream1ivATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream1fATI(stream, x) _glVertexStream1fATI(stream, x, __FILE__, __LINE__)
#define glVertexStream1fvATI(stream, coords) _glVertexStream1fvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream1dATI(stream, x) _glVertexStream1dATI(stream, x, __FILE__, __LINE__)
#define glVertexStream1dvATI(stream, coords) _glVertexStream1dvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream2sATI(stream, x, y) _glVertexStream2sATI(stream, x, y, __FILE__, __LINE__)
#define glVertexStream2svATI(stream, coords) _glVertexStream2svATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream2iATI(stream, x, y) _glVertexStream2iATI(stream, x, y, __FILE__, __LINE__)
#define glVertexStream2ivATI(stream, coords) _glVertexStream2ivATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream2fATI(stream, x, y) _glVertexStream2fATI(stream, x, y, __FILE__, __LINE__)
#define glVertexStream2fvATI(stream, coords) _glVertexStream2fvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream2dATI(stream, x, y) _glVertexStream2dATI(stream, x, y, __FILE__, __LINE__)
#define glVertexStream2dvATI(stream, coords) _glVertexStream2dvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream3sATI(stream, x, y, z) _glVertexStream3sATI(stream, x, y, z, __FILE__, __LINE__)
#define glVertexStream3svATI(stream, coords) _glVertexStream3svATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream3iATI(stream, x, y, z) _glVertexStream3iATI(stream, x, y, z, __FILE__, __LINE__)
#define glVertexStream3ivATI(stream, coords) _glVertexStream3ivATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream3fATI(stream, x, y, z) _glVertexStream3fATI(stream, x, y, z, __FILE__, __LINE__)
#define glVertexStream3fvATI(stream, coords) _glVertexStream3fvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream3dATI(stream, x, y, z) _glVertexStream3dATI(stream, x, y, z, __FILE__, __LINE__)
#define glVertexStream3dvATI(stream, coords) _glVertexStream3dvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream4sATI(stream, x, y, z, w) _glVertexStream4sATI(stream, x, y, z, w, __FILE__, __LINE__)
#define glVertexStream4svATI(stream, coords) _glVertexStream4svATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream4iATI(stream, x, y, z, w) _glVertexStream4iATI(stream, x, y, z, w, __FILE__, __LINE__)
#define glVertexStream4ivATI(stream, coords) _glVertexStream4ivATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream4fATI(stream, x, y, z, w) _glVertexStream4fATI(stream, x, y, z, w, __FILE__, __LINE__)
#define glVertexStream4fvATI(stream, coords) _glVertexStream4fvATI(stream, coords, __FILE__, __LINE__)
#define glVertexStream4dATI(stream, x, y, z, w) _glVertexStream4dATI(stream, x, y, z, w, __FILE__, __LINE__)
#define glVertexStream4dvATI(stream, coords) _glVertexStream4dvATI(stream, coords, __FILE__, __LINE__)
#define glNormalStream3bATI(stream, nx, ny, nz) _glNormalStream3bATI(stream, nx, ny, nz, __FILE__, __LINE__)
#define glNormalStream3bvATI(stream, coords) _glNormalStream3bvATI(stream, coords, __FILE__, __LINE__)
#define glNormalStream3sATI(stream, nx, ny, nz) _glNormalStream3sATI(stream, nx, ny, nz, __FILE__, __LINE__)
#define glNormalStream3svATI(stream, coords) _glNormalStream3svATI(stream, coords, __FILE__, __LINE__)
#define glNormalStream3iATI(stream, nx, ny, nz) _glNormalStream3iATI(stream, nx, ny, nz, __FILE__, __LINE__)
#define glNormalStream3ivATI(stream, coords) _glNormalStream3ivATI(stream, coords, __FILE__, __LINE__)
#define glNormalStream3fATI(stream, nx, ny, nz) _glNormalStream3fATI(stream, nx, ny, nz, __FILE__, __LINE__)
#define glNormalStream3fvATI(stream, coords) _glNormalStream3fvATI(stream, coords, __FILE__, __LINE__)
#define glNormalStream3dATI(stream, nx, ny, nz) _glNormalStream3dATI(stream, nx, ny, nz, __FILE__, __LINE__)
#define glNormalStream3dvATI(stream, coords) _glNormalStream3dvATI(stream, coords, __FILE__, __LINE__)
#define glClientActiveVertexStreamATI(stream) _glClientActiveVertexStreamATI(stream, __FILE__, __LINE__)
#define glVertexBlendEnviATI(pname, param) _glVertexBlendEnviATI(pname, param, __FILE__, __LINE__)
#define glVertexBlendEnvfATI(pname, param) _glVertexBlendEnvfATI(pname, param, __FILE__, __LINE__)
#define glEGLImageTargetTexStorageEXT(target, image, attrib_list) _glEGLImageTargetTexStorageEXT(target, image, attrib_list, __FILE__, __LINE__)
#define glEGLImageTargetTextureStorageEXT(texture, image, attrib_list) _glEGLImageTargetTextureStorageEXT(texture, image, attrib_list, __FILE__, __LINE__)
#define glUniformBufferEXT(program, location, buffer) _glUniformBufferEXT(program, location, buffer, __FILE__, __LINE__)
#define glGetUniformBufferSizeEXT(program, location) _glGetUniformBufferSizeEXT(program, location, __FILE__, __LINE__)
#define glGetUniformOffsetEXT(program, location) _glGetUniformOffsetEXT(program, location, __FILE__, __LINE__)
#define glBlendColorEXT(red, green, blue, alpha) _glBlendColorEXT(red, green, blue, alpha, __FILE__, __LINE__)
#define glBlendEquationSeparateEXT(modeRGB, modeAlpha) _glBlendEquationSeparateEXT(modeRGB, modeAlpha, __FILE__, __LINE__)
#define glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) _glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha, __FILE__, __LINE__)
#define glBlendEquationEXT(mode) _glBlendEquationEXT(mode, __FILE__, __LINE__)
#define glColorSubTableEXT(target, start, count, format, type, data) _glColorSubTableEXT(target, start, count, format, type, data, __FILE__, __LINE__)
#define glCopyColorSubTableEXT(target, start, x, y, width) _glCopyColorSubTableEXT(target, start, x, y, width, __FILE__, __LINE__)
#define glLockArraysEXT(first, count) _glLockArraysEXT(first, count, __FILE__, __LINE__)
#define glUnlockArraysEXT() _glUnlockArraysEXT(__FILE__, __LINE__)
#define glConvolutionFilter1DEXT(target, internalformat, width, format, type, image) _glConvolutionFilter1DEXT(target, internalformat, width, format, type, image, __FILE__, __LINE__)
#define glConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image) _glConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image, __FILE__, __LINE__)
#define glConvolutionParameterfEXT(target, pname, params) _glConvolutionParameterfEXT(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameterfvEXT(target, pname, params) _glConvolutionParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameteriEXT(target, pname, params) _glConvolutionParameteriEXT(target, pname, params, __FILE__, __LINE__)
#define glConvolutionParameterivEXT(target, pname, params) _glConvolutionParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glCopyConvolutionFilter1DEXT(target, internalformat, x, y, width) _glCopyConvolutionFilter1DEXT(target, internalformat, x, y, width, __FILE__, __LINE__)
#define glCopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height) _glCopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height, __FILE__, __LINE__)
#define glGetConvolutionFilterEXT(target, format, type, image) _glGetConvolutionFilterEXT(target, format, type, image, __FILE__, __LINE__)
#define glGetConvolutionParameterfvEXT(target, pname, params) _glGetConvolutionParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glGetConvolutionParameterivEXT(target, pname, params) _glGetConvolutionParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetSeparableFilterEXT(target, format, type, row, column, span) _glGetSeparableFilterEXT(target, format, type, row, column, span, __FILE__, __LINE__)
#define glSeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column) _glSeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column, __FILE__, __LINE__)
#define glTangent3bEXT(tx, ty, tz) _glTangent3bEXT(tx, ty, tz, __FILE__, __LINE__)
#define glTangent3bvEXT(v) _glTangent3bvEXT(v, __FILE__, __LINE__)
#define glTangent3dEXT(tx, ty, tz) _glTangent3dEXT(tx, ty, tz, __FILE__, __LINE__)
#define glTangent3dvEXT(v) _glTangent3dvEXT(v, __FILE__, __LINE__)
#define glTangent3fEXT(tx, ty, tz) _glTangent3fEXT(tx, ty, tz, __FILE__, __LINE__)
#define glTangent3fvEXT(v) _glTangent3fvEXT(v, __FILE__, __LINE__)
#define glTangent3iEXT(tx, ty, tz) _glTangent3iEXT(tx, ty, tz, __FILE__, __LINE__)
#define glTangent3ivEXT(v) _glTangent3ivEXT(v, __FILE__, __LINE__)
#define glTangent3sEXT(tx, ty, tz) _glTangent3sEXT(tx, ty, tz, __FILE__, __LINE__)
#define glTangent3svEXT(v) _glTangent3svEXT(v, __FILE__, __LINE__)
#define glBinormal3bEXT(bx, by, bz) _glBinormal3bEXT(bx, by, bz, __FILE__, __LINE__)
#define glBinormal3bvEXT(v) _glBinormal3bvEXT(v, __FILE__, __LINE__)
#define glBinormal3dEXT(bx, by, bz) _glBinormal3dEXT(bx, by, bz, __FILE__, __LINE__)
#define glBinormal3dvEXT(v) _glBinormal3dvEXT(v, __FILE__, __LINE__)
#define glBinormal3fEXT(bx, by, bz) _glBinormal3fEXT(bx, by, bz, __FILE__, __LINE__)
#define glBinormal3fvEXT(v) _glBinormal3fvEXT(v, __FILE__, __LINE__)
#define glBinormal3iEXT(bx, by, bz) _glBinormal3iEXT(bx, by, bz, __FILE__, __LINE__)
#define glBinormal3ivEXT(v) _glBinormal3ivEXT(v, __FILE__, __LINE__)
#define glBinormal3sEXT(bx, by, bz) _glBinormal3sEXT(bx, by, bz, __FILE__, __LINE__)
#define glBinormal3svEXT(v) _glBinormal3svEXT(v, __FILE__, __LINE__)
#define glTangentPointerEXT(type, stride, pointer) _glTangentPointerEXT(type, stride, pointer, __FILE__, __LINE__)
#define glBinormalPointerEXT(type, stride, pointer) _glBinormalPointerEXT(type, stride, pointer, __FILE__, __LINE__)
#define glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border) _glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border, __FILE__, __LINE__)
#define glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border) _glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border, __FILE__, __LINE__)
#define glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width) _glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width, __FILE__, __LINE__)
#define glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height) _glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height, __FILE__, __LINE__)
#define glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height) _glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height, __FILE__, __LINE__)
#define glCullParameterdvEXT(pname, params) _glCullParameterdvEXT(pname, params, __FILE__, __LINE__)
#define glCullParameterfvEXT(pname, params) _glCullParameterfvEXT(pname, params, __FILE__, __LINE__)
#define glLabelObjectEXT(type, object, length, label) _glLabelObjectEXT(type, object, length, label, __FILE__, __LINE__)
#define glGetObjectLabelEXT(type, object, bufSize, length, label) _glGetObjectLabelEXT(type, object, bufSize, length, label, __FILE__, __LINE__)
#define glInsertEventMarkerEXT(length, marker) _glInsertEventMarkerEXT(length, marker, __FILE__, __LINE__)
#define glPushGroupMarkerEXT(length, marker) _glPushGroupMarkerEXT(length, marker, __FILE__, __LINE__)
#define glPopGroupMarkerEXT() _glPopGroupMarkerEXT(__FILE__, __LINE__)
#define glDepthBoundsEXT(zmin, zmax) _glDepthBoundsEXT(zmin, zmax, __FILE__, __LINE__)
#define glMatrixLoadfEXT(mode, m) _glMatrixLoadfEXT(mode, m, __FILE__, __LINE__)
#define glMatrixLoaddEXT(mode, m) _glMatrixLoaddEXT(mode, m, __FILE__, __LINE__)
#define glMatrixMultfEXT(mode, m) _glMatrixMultfEXT(mode, m, __FILE__, __LINE__)
#define glMatrixMultdEXT(mode, m) _glMatrixMultdEXT(mode, m, __FILE__, __LINE__)
#define glMatrixLoadIdentityEXT(mode) _glMatrixLoadIdentityEXT(mode, __FILE__, __LINE__)
#define glMatrixRotatefEXT(mode, angle, x, y, z) _glMatrixRotatefEXT(mode, angle, x, y, z, __FILE__, __LINE__)
#define glMatrixRotatedEXT(mode, angle, x, y, z) _glMatrixRotatedEXT(mode, angle, x, y, z, __FILE__, __LINE__)
#define glMatrixScalefEXT(mode, x, y, z) _glMatrixScalefEXT(mode, x, y, z, __FILE__, __LINE__)
#define glMatrixScaledEXT(mode, x, y, z) _glMatrixScaledEXT(mode, x, y, z, __FILE__, __LINE__)
#define glMatrixTranslatefEXT(mode, x, y, z) _glMatrixTranslatefEXT(mode, x, y, z, __FILE__, __LINE__)
#define glMatrixTranslatedEXT(mode, x, y, z) _glMatrixTranslatedEXT(mode, x, y, z, __FILE__, __LINE__)
#define glMatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar) _glMatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar, __FILE__, __LINE__)
#define glMatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar) _glMatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar, __FILE__, __LINE__)
#define glMatrixPopEXT(mode) _glMatrixPopEXT(mode, __FILE__, __LINE__)
#define glMatrixPushEXT(mode) _glMatrixPushEXT(mode, __FILE__, __LINE__)
#define glClientAttribDefaultEXT(mask) _glClientAttribDefaultEXT(mask, __FILE__, __LINE__)
#define glPushClientAttribDefaultEXT(mask) _glPushClientAttribDefaultEXT(mask, __FILE__, __LINE__)
#define glTextureParameterfEXT(texture, target, pname, param) _glTextureParameterfEXT(texture, target, pname, param, __FILE__, __LINE__)
#define glTextureParameterfvEXT(texture, target, pname, params) _glTextureParameterfvEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glTextureParameteriEXT(texture, target, pname, param) _glTextureParameteriEXT(texture, target, pname, param, __FILE__, __LINE__)
#define glTextureParameterivEXT(texture, target, pname, params) _glTextureParameterivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glTextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels) _glTextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels, __FILE__, __LINE__)
#define glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels) _glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels, __FILE__, __LINE__)
#define glTextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels) _glTextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels, __FILE__, __LINE__)
#define glTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels) _glTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels, __FILE__, __LINE__)
#define glCopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border) _glCopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border, __FILE__, __LINE__)
#define glCopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border) _glCopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border, __FILE__, __LINE__)
#define glCopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width) _glCopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width, __FILE__, __LINE__)
#define glCopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height) _glCopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height, __FILE__, __LINE__)
#define glGetTextureImageEXT(texture, target, level, format, type, pixels) _glGetTextureImageEXT(texture, target, level, format, type, pixels, __FILE__, __LINE__)
#define glGetTextureParameterfvEXT(texture, target, pname, params) _glGetTextureParameterfvEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterivEXT(texture, target, pname, params) _glGetTextureParameterivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glGetTextureLevelParameterfvEXT(texture, target, level, pname, params) _glGetTextureLevelParameterfvEXT(texture, target, level, pname, params, __FILE__, __LINE__)
#define glGetTextureLevelParameterivEXT(texture, target, level, pname, params) _glGetTextureLevelParameterivEXT(texture, target, level, pname, params, __FILE__, __LINE__)
#define glTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels) _glTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels, __FILE__, __LINE__)
#define glTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) _glTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels, __FILE__, __LINE__)
#define glCopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height) _glCopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height, __FILE__, __LINE__)
#define glBindMultiTextureEXT(texunit, target, texture) _glBindMultiTextureEXT(texunit, target, texture, __FILE__, __LINE__)
#define glMultiTexCoordPointerEXT(texunit, size, type, stride, pointer) _glMultiTexCoordPointerEXT(texunit, size, type, stride, pointer, __FILE__, __LINE__)
#define glMultiTexEnvfEXT(texunit, target, pname, param) _glMultiTexEnvfEXT(texunit, target, pname, param, __FILE__, __LINE__)
#define glMultiTexEnvfvEXT(texunit, target, pname, params) _glMultiTexEnvfvEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glMultiTexEnviEXT(texunit, target, pname, param) _glMultiTexEnviEXT(texunit, target, pname, param, __FILE__, __LINE__)
#define glMultiTexEnvivEXT(texunit, target, pname, params) _glMultiTexEnvivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glMultiTexGendEXT(texunit, coord, pname, param) _glMultiTexGendEXT(texunit, coord, pname, param, __FILE__, __LINE__)
#define glMultiTexGendvEXT(texunit, coord, pname, params) _glMultiTexGendvEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glMultiTexGenfEXT(texunit, coord, pname, param) _glMultiTexGenfEXT(texunit, coord, pname, param, __FILE__, __LINE__)
#define glMultiTexGenfvEXT(texunit, coord, pname, params) _glMultiTexGenfvEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glMultiTexGeniEXT(texunit, coord, pname, param) _glMultiTexGeniEXT(texunit, coord, pname, param, __FILE__, __LINE__)
#define glMultiTexGenivEXT(texunit, coord, pname, params) _glMultiTexGenivEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glGetMultiTexEnvfvEXT(texunit, target, pname, params) _glGetMultiTexEnvfvEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexEnvivEXT(texunit, target, pname, params) _glGetMultiTexEnvivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexGendvEXT(texunit, coord, pname, params) _glGetMultiTexGendvEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glGetMultiTexGenfvEXT(texunit, coord, pname, params) _glGetMultiTexGenfvEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glGetMultiTexGenivEXT(texunit, coord, pname, params) _glGetMultiTexGenivEXT(texunit, coord, pname, params, __FILE__, __LINE__)
#define glMultiTexParameteriEXT(texunit, target, pname, param) _glMultiTexParameteriEXT(texunit, target, pname, param, __FILE__, __LINE__)
#define glMultiTexParameterivEXT(texunit, target, pname, params) _glMultiTexParameterivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glMultiTexParameterfEXT(texunit, target, pname, param) _glMultiTexParameterfEXT(texunit, target, pname, param, __FILE__, __LINE__)
#define glMultiTexParameterfvEXT(texunit, target, pname, params) _glMultiTexParameterfvEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels) _glMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels, __FILE__, __LINE__)
#define glMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels) _glMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels, __FILE__, __LINE__)
#define glMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels) _glMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels, __FILE__, __LINE__)
#define glMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels) _glMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels, __FILE__, __LINE__)
#define glCopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border) _glCopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border, __FILE__, __LINE__)
#define glCopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border) _glCopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border, __FILE__, __LINE__)
#define glCopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width) _glCopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width, __FILE__, __LINE__)
#define glCopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height) _glCopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height, __FILE__, __LINE__)
#define glGetMultiTexImageEXT(texunit, target, level, format, type, pixels) _glGetMultiTexImageEXT(texunit, target, level, format, type, pixels, __FILE__, __LINE__)
#define glGetMultiTexParameterfvEXT(texunit, target, pname, params) _glGetMultiTexParameterfvEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexParameterivEXT(texunit, target, pname, params) _glGetMultiTexParameterivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params) _glGetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params, __FILE__, __LINE__)
#define glGetMultiTexLevelParameterivEXT(texunit, target, level, pname, params) _glGetMultiTexLevelParameterivEXT(texunit, target, level, pname, params, __FILE__, __LINE__)
#define glMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels) _glMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels, __FILE__, __LINE__)
#define glMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) _glMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels, __FILE__, __LINE__)
#define glCopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height) _glCopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height, __FILE__, __LINE__)
#define glEnableClientStateIndexedEXT(array, index) _glEnableClientStateIndexedEXT(array, index, __FILE__, __LINE__)
#define glDisableClientStateIndexedEXT(array, index) _glDisableClientStateIndexedEXT(array, index, __FILE__, __LINE__)
#define glGetFloatIndexedvEXT(target, index, data) _glGetFloatIndexedvEXT(target, index, data, __FILE__, __LINE__)
#define glGetDoubleIndexedvEXT(target, index, data) _glGetDoubleIndexedvEXT(target, index, data, __FILE__, __LINE__)
#define glGetPointerIndexedvEXT(target, index, data) _glGetPointerIndexedvEXT(target, index, data, __FILE__, __LINE__)
#define glEnableIndexedEXT(target, index) _glEnableIndexedEXT(target, index, __FILE__, __LINE__)
#define glDisableIndexedEXT(target, index) _glDisableIndexedEXT(target, index, __FILE__, __LINE__)
#define glIsEnabledIndexedEXT(target, index) _glIsEnabledIndexedEXT(target, index, __FILE__, __LINE__)
#define glGetIntegerIndexedvEXT(target, index, data) _glGetIntegerIndexedvEXT(target, index, data, __FILE__, __LINE__)
#define glGetBooleanIndexedvEXT(target, index, data) _glGetBooleanIndexedvEXT(target, index, data, __FILE__, __LINE__)
#define glCompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits) _glCompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits) _glCompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits) _glCompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits) _glCompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits, __FILE__, __LINE__)
#define glCompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits) _glCompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits, __FILE__, __LINE__)
#define glCompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits) _glCompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits, __FILE__, __LINE__)
#define glGetCompressedTextureImageEXT(texture, target, lod, img) _glGetCompressedTextureImageEXT(texture, target, lod, img, __FILE__, __LINE__)
#define glCompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits) _glCompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits) _glCompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits) _glCompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits, __FILE__, __LINE__)
#define glCompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits) _glCompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits, __FILE__, __LINE__)
#define glCompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits) _glCompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits, __FILE__, __LINE__)
#define glCompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits) _glCompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits, __FILE__, __LINE__)
#define glGetCompressedMultiTexImageEXT(texunit, target, lod, img) _glGetCompressedMultiTexImageEXT(texunit, target, lod, img, __FILE__, __LINE__)
#define glMatrixLoadTransposefEXT(mode, m) _glMatrixLoadTransposefEXT(mode, m, __FILE__, __LINE__)
#define glMatrixLoadTransposedEXT(mode, m) _glMatrixLoadTransposedEXT(mode, m, __FILE__, __LINE__)
#define glMatrixMultTransposefEXT(mode, m) _glMatrixMultTransposefEXT(mode, m, __FILE__, __LINE__)
#define glMatrixMultTransposedEXT(mode, m) _glMatrixMultTransposedEXT(mode, m, __FILE__, __LINE__)
#define glNamedBufferDataEXT(buffer, size, data, usage) _glNamedBufferDataEXT(buffer, size, data, usage, __FILE__, __LINE__)
#define glNamedBufferSubDataEXT(buffer, offset, size, data) _glNamedBufferSubDataEXT(buffer, offset, size, data, __FILE__, __LINE__)
#define glMapNamedBufferEXT(buffer, _) _glMapNamedBufferEXT(buffer, _, __FILE__, __LINE__)
#define glUnmapNamedBufferEXT(buffer) _glUnmapNamedBufferEXT(buffer, __FILE__, __LINE__)
#define glGetNamedBufferParameterivEXT(buffer, pname, params) _glGetNamedBufferParameterivEXT(buffer, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferPointervEXT(buffer, pname, params) _glGetNamedBufferPointervEXT(buffer, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferSubDataEXT(buffer, offset, size, data) _glGetNamedBufferSubDataEXT(buffer, offset, size, data, __FILE__, __LINE__)
#define glProgramUniform1fEXT(program, location, v0) _glProgramUniform1fEXT(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform2fEXT(program, location, v0, v1) _glProgramUniform2fEXT(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform3fEXT(program, location, v0, v1, v2) _glProgramUniform3fEXT(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform4fEXT(program, location, v0, v1, v2, v3) _glProgramUniform4fEXT(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform1iEXT(program, location, v0) _glProgramUniform1iEXT(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform2iEXT(program, location, v0, v1) _glProgramUniform2iEXT(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform3iEXT(program, location, v0, v1, v2) _glProgramUniform3iEXT(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform4iEXT(program, location, v0, v1, v2, v3) _glProgramUniform4iEXT(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform1fvEXT(program, location, count, value) _glProgramUniform1fvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2fvEXT(program, location, count, value) _glProgramUniform2fvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3fvEXT(program, location, count, value) _glProgramUniform3fvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4fvEXT(program, location, count, value) _glProgramUniform4fvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform1ivEXT(program, location, count, value) _glProgramUniform1ivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2ivEXT(program, location, count, value) _glProgramUniform2ivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3ivEXT(program, location, count, value) _glProgramUniform3ivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4ivEXT(program, location, count, value) _glProgramUniform4ivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glTextureBufferEXT(texture, target, internalformat, buffer) _glTextureBufferEXT(texture, target, internalformat, buffer, __FILE__, __LINE__)
#define glMultiTexBufferEXT(texunit, target, internalformat, buffer) _glMultiTexBufferEXT(texunit, target, internalformat, buffer, __FILE__, __LINE__)
#define glTextureParameterIivEXT(texture, target, pname, params) _glTextureParameterIivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glTextureParameterIuivEXT(texture, target, pname, params) _glTextureParameterIuivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterIivEXT(texture, target, pname, params) _glGetTextureParameterIivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glGetTextureParameterIuivEXT(texture, target, pname, params) _glGetTextureParameterIuivEXT(texture, target, pname, params, __FILE__, __LINE__)
#define glMultiTexParameterIivEXT(texunit, target, pname, params) _glMultiTexParameterIivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glMultiTexParameterIuivEXT(texunit, target, pname, params) _glMultiTexParameterIuivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexParameterIivEXT(texunit, target, pname, params) _glGetMultiTexParameterIivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glGetMultiTexParameterIuivEXT(texunit, target, pname, params) _glGetMultiTexParameterIuivEXT(texunit, target, pname, params, __FILE__, __LINE__)
#define glProgramUniform1uiEXT(program, location, v0) _glProgramUniform1uiEXT(program, location, v0, __FILE__, __LINE__)
#define glProgramUniform2uiEXT(program, location, v0, v1) _glProgramUniform2uiEXT(program, location, v0, v1, __FILE__, __LINE__)
#define glProgramUniform3uiEXT(program, location, v0, v1, v2) _glProgramUniform3uiEXT(program, location, v0, v1, v2, __FILE__, __LINE__)
#define glProgramUniform4uiEXT(program, location, v0, v1, v2, v3) _glProgramUniform4uiEXT(program, location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glProgramUniform1uivEXT(program, location, count, value) _glProgramUniform1uivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2uivEXT(program, location, count, value) _glProgramUniform2uivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3uivEXT(program, location, count, value) _glProgramUniform3uivEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4uivEXT(program, location, count, value) _glProgramUniform4uivEXT(program, location, count, value, __FILE__, __LINE__)
#define glNamedProgramLocalParameters4fvEXT(program, target, index, count, params) _glNamedProgramLocalParameters4fvEXT(program, target, index, count, params, __FILE__, __LINE__)
#define glNamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w) _glNamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w, __FILE__, __LINE__)
#define glNamedProgramLocalParameterI4ivEXT(program, target, index, params) _glNamedProgramLocalParameterI4ivEXT(program, target, index, params, __FILE__, __LINE__)
#define glNamedProgramLocalParametersI4ivEXT(program, target, index, count, params) _glNamedProgramLocalParametersI4ivEXT(program, target, index, count, params, __FILE__, __LINE__)
#define glNamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w) _glNamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w, __FILE__, __LINE__)
#define glNamedProgramLocalParameterI4uivEXT(program, target, index, params) _glNamedProgramLocalParameterI4uivEXT(program, target, index, params, __FILE__, __LINE__)
#define glNamedProgramLocalParametersI4uivEXT(program, target, index, count, params) _glNamedProgramLocalParametersI4uivEXT(program, target, index, count, params, __FILE__, __LINE__)
#define glGetNamedProgramLocalParameterIivEXT(program, target, index, params) _glGetNamedProgramLocalParameterIivEXT(program, target, index, params, __FILE__, __LINE__)
#define glGetNamedProgramLocalParameterIuivEXT(program, target, index, params) _glGetNamedProgramLocalParameterIuivEXT(program, target, index, params, __FILE__, __LINE__)
#define glEnableClientStateiEXT(array, index) _glEnableClientStateiEXT(array, index, __FILE__, __LINE__)
#define glDisableClientStateiEXT(array, index) _glDisableClientStateiEXT(array, index, __FILE__, __LINE__)
#define glGetFloati_vEXT(pname, index, params) _glGetFloati_vEXT(pname, index, params, __FILE__, __LINE__)
#define glGetDoublei_vEXT(pname, index, params) _glGetDoublei_vEXT(pname, index, params, __FILE__, __LINE__)
#define glGetPointeri_vEXT(pname, index, params) _glGetPointeri_vEXT(pname, index, params, __FILE__, __LINE__)
#define glNamedProgramStringEXT(program, target, format, len, string) _glNamedProgramStringEXT(program, target, format, len, string, __FILE__, __LINE__)
#define glNamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w) _glNamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w, __FILE__, __LINE__)
#define glNamedProgramLocalParameter4dvEXT(program, target, index, params) _glNamedProgramLocalParameter4dvEXT(program, target, index, params, __FILE__, __LINE__)
#define glNamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w) _glNamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w, __FILE__, __LINE__)
#define glNamedProgramLocalParameter4fvEXT(program, target, index, params) _glNamedProgramLocalParameter4fvEXT(program, target, index, params, __FILE__, __LINE__)
#define glGetNamedProgramLocalParameterdvEXT(program, target, index, params) _glGetNamedProgramLocalParameterdvEXT(program, target, index, params, __FILE__, __LINE__)
#define glGetNamedProgramLocalParameterfvEXT(program, target, index, params) _glGetNamedProgramLocalParameterfvEXT(program, target, index, params, __FILE__, __LINE__)
#define glGetNamedProgramivEXT(program, target, pname, params) _glGetNamedProgramivEXT(program, target, pname, params, __FILE__, __LINE__)
#define glGetNamedProgramStringEXT(program, target, pname, string) _glGetNamedProgramStringEXT(program, target, pname, string, __FILE__, __LINE__)
#define glNamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height) _glNamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height, __FILE__, __LINE__)
#define glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params) _glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params, __FILE__, __LINE__)
#define glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height) _glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height, __FILE__, __LINE__)
#define glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height) _glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height, __FILE__, __LINE__)
#define glCheckNamedFramebufferStatusEXT(framebuffer, target) _glCheckNamedFramebufferStatusEXT(framebuffer, target, __FILE__, __LINE__)
#define glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level) _glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level) _glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset) _glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset, __FILE__, __LINE__)
#define glNamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer) _glNamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer, __FILE__, __LINE__)
#define glGetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params) _glGetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params, __FILE__, __LINE__)
#define glGenerateTextureMipmapEXT(texture, target) _glGenerateTextureMipmapEXT(texture, target, __FILE__, __LINE__)
#define glGenerateMultiTexMipmapEXT(texunit, target) _glGenerateMultiTexMipmapEXT(texunit, target, __FILE__, __LINE__)
#define glFramebufferDrawBufferEXT(framebuffer, mode) _glFramebufferDrawBufferEXT(framebuffer, mode, __FILE__, __LINE__)
#define glFramebufferDrawBuffersEXT(framebuffer, n, bufs) _glFramebufferDrawBuffersEXT(framebuffer, n, bufs, __FILE__, __LINE__)
#define glFramebufferReadBufferEXT(framebuffer, mode) _glFramebufferReadBufferEXT(framebuffer, mode, __FILE__, __LINE__)
#define glGetFramebufferParameterivEXT(framebuffer, pname, params) _glGetFramebufferParameterivEXT(framebuffer, pname, params, __FILE__, __LINE__)
#define glNamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size) _glNamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size, __FILE__, __LINE__)
#define glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level) _glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level, __FILE__, __LINE__)
#define glNamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer) _glNamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer, __FILE__, __LINE__)
#define glNamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face) _glNamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face, __FILE__, __LINE__)
#define glTextureRenderbufferEXT(texture, target, renderbuffer) _glTextureRenderbufferEXT(texture, target, renderbuffer, __FILE__, __LINE__)
#define glMultiTexRenderbufferEXT(texunit, target, renderbuffer) _glMultiTexRenderbufferEXT(texunit, target, renderbuffer, __FILE__, __LINE__)
#define glVertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset) _glVertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset) _glVertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset) _glVertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset, __FILE__, __LINE__)
#define glVertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset) _glVertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset) _glVertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset) _glVertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset) _glVertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset) _glVertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset, __FILE__, __LINE__)
#define glVertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset) _glVertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset, __FILE__, __LINE__)
#define glVertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset) _glVertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset, __FILE__, __LINE__)
#define glVertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset) _glVertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset, __FILE__, __LINE__)
#define glEnableVertexArrayEXT(vaobj, array) _glEnableVertexArrayEXT(vaobj, array, __FILE__, __LINE__)
#define glDisableVertexArrayEXT(vaobj, array) _glDisableVertexArrayEXT(vaobj, array, __FILE__, __LINE__)
#define glEnableVertexArrayAttribEXT(vaobj, index) _glEnableVertexArrayAttribEXT(vaobj, index, __FILE__, __LINE__)
#define glDisableVertexArrayAttribEXT(vaobj, index) _glDisableVertexArrayAttribEXT(vaobj, index, __FILE__, __LINE__)
#define glGetVertexArrayIntegervEXT(vaobj, pname, param) _glGetVertexArrayIntegervEXT(vaobj, pname, param, __FILE__, __LINE__)
#define glGetVertexArrayPointervEXT(vaobj, pname, param) _glGetVertexArrayPointervEXT(vaobj, pname, param, __FILE__, __LINE__)
#define glGetVertexArrayIntegeri_vEXT(vaobj, index, pname, param) _glGetVertexArrayIntegeri_vEXT(vaobj, index, pname, param, __FILE__, __LINE__)
#define glGetVertexArrayPointeri_vEXT(vaobj, index, pname, param) _glGetVertexArrayPointeri_vEXT(vaobj, index, pname, param, __FILE__, __LINE__)
#define glMapNamedBufferRangeEXT(buffer, offset, length, _) _glMapNamedBufferRangeEXT(buffer, offset, length, _, __FILE__, __LINE__)
#define glFlushMappedNamedBufferRangeEXT(buffer, offset, length) _glFlushMappedNamedBufferRangeEXT(buffer, offset, length, __FILE__, __LINE__)
#define glNamedBufferStorageEXT(buffer, size, data, flags) _glNamedBufferStorageEXT(buffer, size, data, flags, __FILE__, __LINE__)
#define glClearNamedBufferDataEXT(buffer, internalformat, format, type, data) _glClearNamedBufferDataEXT(buffer, internalformat, format, type, data, __FILE__, __LINE__)
#define glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data) _glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data, __FILE__, __LINE__)
#define glNamedFramebufferParameteriEXT(framebuffer, pname, param) _glNamedFramebufferParameteriEXT(framebuffer, pname, param, __FILE__, __LINE__)
#define glGetNamedFramebufferParameterivEXT(framebuffer, pname, params) _glGetNamedFramebufferParameterivEXT(framebuffer, pname, params, __FILE__, __LINE__)
#define glProgramUniform1dEXT(program, location, x) _glProgramUniform1dEXT(program, location, x, __FILE__, __LINE__)
#define glProgramUniform2dEXT(program, location, x, y) _glProgramUniform2dEXT(program, location, x, y, __FILE__, __LINE__)
#define glProgramUniform3dEXT(program, location, x, y, z) _glProgramUniform3dEXT(program, location, x, y, z, __FILE__, __LINE__)
#define glProgramUniform4dEXT(program, location, x, y, z, w) _glProgramUniform4dEXT(program, location, x, y, z, w, __FILE__, __LINE__)
#define glProgramUniform1dvEXT(program, location, count, value) _glProgramUniform1dvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform2dvEXT(program, location, count, value) _glProgramUniform2dvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform3dvEXT(program, location, count, value) _glProgramUniform3dvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniform4dvEXT(program, location, count, value) _glProgramUniform4dvEXT(program, location, count, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value) _glProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value, __FILE__, __LINE__)
#define glTextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size) _glTextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size, __FILE__, __LINE__)
#define glTextureStorage1DEXT(texture, target, levels, internalformat, width) _glTextureStorage1DEXT(texture, target, levels, internalformat, width, __FILE__, __LINE__)
#define glTextureStorage2DEXT(texture, target, levels, internalformat, width, height) _glTextureStorage2DEXT(texture, target, levels, internalformat, width, height, __FILE__, __LINE__)
#define glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth) _glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth, __FILE__, __LINE__)
#define glTextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations) _glTextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations, __FILE__, __LINE__)
#define glTextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations) _glTextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations, __FILE__, __LINE__)
#define glVertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride) _glVertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride, __FILE__, __LINE__)
#define glVertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset) _glVertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset) _glVertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset) _glVertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset, __FILE__, __LINE__)
#define glVertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex) _glVertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex, __FILE__, __LINE__)
#define glVertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor) _glVertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor, __FILE__, __LINE__)
#define glVertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset) _glVertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset, __FILE__, __LINE__)
#define glTexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, commit) _glTexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, commit, __FILE__, __LINE__)
#define glVertexArrayVertexAttribDivisorEXT(vaobj, index, divisor) _glVertexArrayVertexAttribDivisorEXT(vaobj, index, divisor, __FILE__, __LINE__)
#define glColorMaskIndexedEXT(index, r, g, b, a) _glColorMaskIndexedEXT(index, r, g, b, a, __FILE__, __LINE__)
#define glDrawArraysInstancedEXT(mode, start, count, primcount) _glDrawArraysInstancedEXT(mode, start, count, primcount, __FILE__, __LINE__)
#define glDrawElementsInstancedEXT(mode, count, type, indices, primcount) _glDrawElementsInstancedEXT(mode, count, type, indices, primcount, __FILE__, __LINE__)
#define glDrawRangeElementsEXT(mode, start, end, count, type, indices) _glDrawRangeElementsEXT(mode, start, end, count, type, indices, __FILE__, __LINE__)
#define glBufferStorageExternalEXT(target, offset, size, clientBuffer, flags) _glBufferStorageExternalEXT(target, offset, size, clientBuffer, flags, __FILE__, __LINE__)
#define glNamedBufferStorageExternalEXT(buffer, offset, size, clientBuffer, flags) _glNamedBufferStorageExternalEXT(buffer, offset, size, clientBuffer, flags, __FILE__, __LINE__)
#define glFogCoordfEXT(coord) _glFogCoordfEXT(coord, __FILE__, __LINE__)
#define glFogCoordfvEXT(coord) _glFogCoordfvEXT(coord, __FILE__, __LINE__)
#define glFogCoorddEXT(coord) _glFogCoorddEXT(coord, __FILE__, __LINE__)
#define glFogCoorddvEXT(coord) _glFogCoorddvEXT(coord, __FILE__, __LINE__)
#define glFogCoordPointerEXT(type, stride, pointer) _glFogCoordPointerEXT(type, stride, pointer, __FILE__, __LINE__)
#define glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) _glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter, __FILE__, __LINE__)
#define glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height) _glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height, __FILE__, __LINE__)
#define glIsRenderbufferEXT(renderbuffer) _glIsRenderbufferEXT(renderbuffer, __FILE__, __LINE__)
#define glBindRenderbufferEXT(target, renderbuffer) _glBindRenderbufferEXT(target, renderbuffer, __FILE__, __LINE__)
#define glDeleteRenderbuffersEXT(n, renderbuffers) _glDeleteRenderbuffersEXT(n, renderbuffers, __FILE__, __LINE__)
#define glGenRenderbuffersEXT(n, renderbuffers) _glGenRenderbuffersEXT(n, renderbuffers, __FILE__, __LINE__)
#define glRenderbufferStorageEXT(target, internalformat, width, height) _glRenderbufferStorageEXT(target, internalformat, width, height, __FILE__, __LINE__)
#define glGetRenderbufferParameterivEXT(target, pname, params) _glGetRenderbufferParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glIsFramebufferEXT(framebuffer) _glIsFramebufferEXT(framebuffer, __FILE__, __LINE__)
#define glBindFramebufferEXT(target, framebuffer) _glBindFramebufferEXT(target, framebuffer, __FILE__, __LINE__)
#define glDeleteFramebuffersEXT(n, framebuffers) _glDeleteFramebuffersEXT(n, framebuffers, __FILE__, __LINE__)
#define glGenFramebuffersEXT(n, framebuffers) _glGenFramebuffersEXT(n, framebuffers, __FILE__, __LINE__)
#define glCheckFramebufferStatusEXT(target) _glCheckFramebufferStatusEXT(target, __FILE__, __LINE__)
#define glFramebufferTexture1DEXT(target, attachment, textarget, texture, level) _glFramebufferTexture1DEXT(target, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glFramebufferTexture2DEXT(target, attachment, textarget, texture, level) _glFramebufferTexture2DEXT(target, attachment, textarget, texture, level, __FILE__, __LINE__)
#define glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset) _glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset, __FILE__, __LINE__)
#define glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer) _glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer, __FILE__, __LINE__)
#define glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params) _glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params, __FILE__, __LINE__)
#define glGenerateMipmapEXT(target) _glGenerateMipmapEXT(target, __FILE__, __LINE__)
#define glProgramParameteriEXT(program, pname, value) _glProgramParameteriEXT(program, pname, value, __FILE__, __LINE__)
#define glProgramEnvParameters4fvEXT(target, index, count, params) _glProgramEnvParameters4fvEXT(target, index, count, params, __FILE__, __LINE__)
#define glProgramLocalParameters4fvEXT(target, index, count, params) _glProgramLocalParameters4fvEXT(target, index, count, params, __FILE__, __LINE__)
#define glGetUniformuivEXT(program, location, params) _glGetUniformuivEXT(program, location, params, __FILE__, __LINE__)
#define glBindFragDataLocationEXT(program, color, name) _glBindFragDataLocationEXT(program, color, name, __FILE__, __LINE__)
#define glGetFragDataLocationEXT(program, name) _glGetFragDataLocationEXT(program, name, __FILE__, __LINE__)
#define glUniform1uiEXT(location, v0) _glUniform1uiEXT(location, v0, __FILE__, __LINE__)
#define glUniform2uiEXT(location, v0, v1) _glUniform2uiEXT(location, v0, v1, __FILE__, __LINE__)
#define glUniform3uiEXT(location, v0, v1, v2) _glUniform3uiEXT(location, v0, v1, v2, __FILE__, __LINE__)
#define glUniform4uiEXT(location, v0, v1, v2, v3) _glUniform4uiEXT(location, v0, v1, v2, v3, __FILE__, __LINE__)
#define glUniform1uivEXT(location, count, value) _glUniform1uivEXT(location, count, value, __FILE__, __LINE__)
#define glUniform2uivEXT(location, count, value) _glUniform2uivEXT(location, count, value, __FILE__, __LINE__)
#define glUniform3uivEXT(location, count, value) _glUniform3uivEXT(location, count, value, __FILE__, __LINE__)
#define glUniform4uivEXT(location, count, value) _glUniform4uivEXT(location, count, value, __FILE__, __LINE__)
#define glGetHistogramEXT(target, reset, format, type, values) _glGetHistogramEXT(target, reset, format, type, values, __FILE__, __LINE__)
#define glGetHistogramParameterfvEXT(target, pname, params) _glGetHistogramParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glGetHistogramParameterivEXT(target, pname, params) _glGetHistogramParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetMinmaxEXT(target, reset, format, type, values) _glGetMinmaxEXT(target, reset, format, type, values, __FILE__, __LINE__)
#define glGetMinmaxParameterfvEXT(target, pname, params) _glGetMinmaxParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glGetMinmaxParameterivEXT(target, pname, params) _glGetMinmaxParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glHistogramEXT(target, width, internalformat, sink) _glHistogramEXT(target, width, internalformat, sink, __FILE__, __LINE__)
#define glMinmaxEXT(target, internalformat, sink) _glMinmaxEXT(target, internalformat, sink, __FILE__, __LINE__)
#define glResetHistogramEXT(target) _glResetHistogramEXT(target, __FILE__, __LINE__)
#define glResetMinmaxEXT(target) _glResetMinmaxEXT(target, __FILE__, __LINE__)
#define glIndexFuncEXT(func, ref) _glIndexFuncEXT(func, ref, __FILE__, __LINE__)
#define glIndexMaterialEXT(face, mode) _glIndexMaterialEXT(face, mode, __FILE__, __LINE__)
#define glApplyTextureEXT(mode) _glApplyTextureEXT(mode, __FILE__, __LINE__)
#define glTextureLightEXT(pname) _glTextureLightEXT(pname, __FILE__, __LINE__)
#define glTextureMaterialEXT(face, mode) _glTextureMaterialEXT(face, mode, __FILE__, __LINE__)
#define glGetUnsignedBytevEXT(pname, data) _glGetUnsignedBytevEXT(pname, data, __FILE__, __LINE__)
#define glGetUnsignedBytei_vEXT(target, index, data) _glGetUnsignedBytei_vEXT(target, index, data, __FILE__, __LINE__)
#define glDeleteMemoryObjectsEXT(n, memoryObjects) _glDeleteMemoryObjectsEXT(n, memoryObjects, __FILE__, __LINE__)
#define glIsMemoryObjectEXT(memoryObject) _glIsMemoryObjectEXT(memoryObject, __FILE__, __LINE__)
#define glCreateMemoryObjectsEXT(n, memoryObjects) _glCreateMemoryObjectsEXT(n, memoryObjects, __FILE__, __LINE__)
#define glMemoryObjectParameterivEXT(memoryObject, pname, params) _glMemoryObjectParameterivEXT(memoryObject, pname, params, __FILE__, __LINE__)
#define glGetMemoryObjectParameterivEXT(memoryObject, pname, params) _glGetMemoryObjectParameterivEXT(memoryObject, pname, params, __FILE__, __LINE__)
#define glTexStorageMem2DEXT(target, levels, internalFormat, width, height, memory, offset) _glTexStorageMem2DEXT(target, levels, internalFormat, width, height, memory, offset, __FILE__, __LINE__)
#define glTexStorageMem2DMultisampleEXT(target, samples, internalFormat, width, height, fixedSampleLocations, memory, offset) _glTexStorageMem2DMultisampleEXT(target, samples, internalFormat, width, height, fixedSampleLocations, memory, offset, __FILE__, __LINE__)
#define glTexStorageMem3DEXT(target, levels, internalFormat, width, height, depth, memory, offset) _glTexStorageMem3DEXT(target, levels, internalFormat, width, height, depth, memory, offset, __FILE__, __LINE__)
#define glTexStorageMem3DMultisampleEXT(target, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset) _glTexStorageMem3DMultisampleEXT(target, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset, __FILE__, __LINE__)
#define glBufferStorageMemEXT(target, size, memory, offset) _glBufferStorageMemEXT(target, size, memory, offset, __FILE__, __LINE__)
#define glTextureStorageMem2DEXT(texture, levels, internalFormat, width, height, memory, offset) _glTextureStorageMem2DEXT(texture, levels, internalFormat, width, height, memory, offset, __FILE__, __LINE__)
#define glTextureStorageMem2DMultisampleEXT(texture, samples, internalFormat, width, height, fixedSampleLocations, memory, offset) _glTextureStorageMem2DMultisampleEXT(texture, samples, internalFormat, width, height, fixedSampleLocations, memory, offset, __FILE__, __LINE__)
#define glTextureStorageMem3DEXT(texture, levels, internalFormat, width, height, depth, memory, offset) _glTextureStorageMem3DEXT(texture, levels, internalFormat, width, height, depth, memory, offset, __FILE__, __LINE__)
#define glTextureStorageMem3DMultisampleEXT(texture, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset) _glTextureStorageMem3DMultisampleEXT(texture, samples, internalFormat, width, height, depth, fixedSampleLocations, memory, offset, __FILE__, __LINE__)
#define glNamedBufferStorageMemEXT(buffer, size, memory, offset) _glNamedBufferStorageMemEXT(buffer, size, memory, offset, __FILE__, __LINE__)
#define glTexStorageMem1DEXT(target, levels, internalFormat, width, memory, offset) _glTexStorageMem1DEXT(target, levels, internalFormat, width, memory, offset, __FILE__, __LINE__)
#define glTextureStorageMem1DEXT(texture, levels, internalFormat, width, memory, offset) _glTextureStorageMem1DEXT(texture, levels, internalFormat, width, memory, offset, __FILE__, __LINE__)
#define glImportMemoryFdEXT(memory, size, handleType, fd) _glImportMemoryFdEXT(memory, size, handleType, fd, __FILE__, __LINE__)
#define glImportMemoryWin32HandleEXT(memory, size, handleType, handle) _glImportMemoryWin32HandleEXT(memory, size, handleType, handle, __FILE__, __LINE__)
#define glImportMemoryWin32NameEXT(memory, size, handleType, name) _glImportMemoryWin32NameEXT(memory, size, handleType, name, __FILE__, __LINE__)
#define glMultiDrawArraysEXT(mode, first, count, primcount) _glMultiDrawArraysEXT(mode, first, count, primcount, __FILE__, __LINE__)
#define glMultiDrawElementsEXT(mode, count, type, indices, primcount) _glMultiDrawElementsEXT(mode, count, type, indices, primcount, __FILE__, __LINE__)
#define glSampleMaskEXT(value, invert) _glSampleMaskEXT(value, invert, __FILE__, __LINE__)
#define glSamplePatternEXT(pattern) _glSamplePatternEXT(pattern, __FILE__, __LINE__)
#define glColorTableEXT(target, internalFormat, width, format, type, table) _glColorTableEXT(target, internalFormat, width, format, type, table, __FILE__, __LINE__)
#define glGetColorTableEXT(target, format, type, data) _glGetColorTableEXT(target, format, type, data, __FILE__, __LINE__)
#define glGetColorTableParameterivEXT(target, pname, params) _glGetColorTableParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetColorTableParameterfvEXT(target, pname, params) _glGetColorTableParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glPixelTransformParameteriEXT(target, pname, param) _glPixelTransformParameteriEXT(target, pname, param, __FILE__, __LINE__)
#define glPixelTransformParameterfEXT(target, pname, param) _glPixelTransformParameterfEXT(target, pname, param, __FILE__, __LINE__)
#define glPixelTransformParameterivEXT(target, pname, params) _glPixelTransformParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glPixelTransformParameterfvEXT(target, pname, params) _glPixelTransformParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glGetPixelTransformParameterivEXT(target, pname, params) _glGetPixelTransformParameterivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetPixelTransformParameterfvEXT(target, pname, params) _glGetPixelTransformParameterfvEXT(target, pname, params, __FILE__, __LINE__)
#define glPointParameterfEXT(pname, param) _glPointParameterfEXT(pname, param, __FILE__, __LINE__)
#define glPointParameterfvEXT(pname, params) _glPointParameterfvEXT(pname, params, __FILE__, __LINE__)
#define glPolygonOffsetEXT(factor, bias) _glPolygonOffsetEXT(factor, bias, __FILE__, __LINE__)
#define glPolygonOffsetClampEXT(factor, units, clamp) _glPolygonOffsetClampEXT(factor, units, clamp, __FILE__, __LINE__)
#define glProvokingVertexEXT(mode) _glProvokingVertexEXT(mode, __FILE__, __LINE__)
#define glRasterSamplesEXT(samples, fixedsamplelocations) _glRasterSamplesEXT(samples, fixedsamplelocations, __FILE__, __LINE__)
#define glSecondaryColor3bEXT(red, green, blue) _glSecondaryColor3bEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3bvEXT(v) _glSecondaryColor3bvEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3dEXT(red, green, blue) _glSecondaryColor3dEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3dvEXT(v) _glSecondaryColor3dvEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3fEXT(red, green, blue) _glSecondaryColor3fEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3fvEXT(v) _glSecondaryColor3fvEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3iEXT(red, green, blue) _glSecondaryColor3iEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3ivEXT(v) _glSecondaryColor3ivEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3sEXT(red, green, blue) _glSecondaryColor3sEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3svEXT(v) _glSecondaryColor3svEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3ubEXT(red, green, blue) _glSecondaryColor3ubEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3ubvEXT(v) _glSecondaryColor3ubvEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3uiEXT(red, green, blue) _glSecondaryColor3uiEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3uivEXT(v) _glSecondaryColor3uivEXT(v, __FILE__, __LINE__)
#define glSecondaryColor3usEXT(red, green, blue) _glSecondaryColor3usEXT(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3usvEXT(v) _glSecondaryColor3usvEXT(v, __FILE__, __LINE__)
#define glSecondaryColorPointerEXT(size, type, stride, pointer) _glSecondaryColorPointerEXT(size, type, stride, pointer, __FILE__, __LINE__)
#define glGenSemaphoresEXT(n, semaphores) _glGenSemaphoresEXT(n, semaphores, __FILE__, __LINE__)
#define glDeleteSemaphoresEXT(n, semaphores) _glDeleteSemaphoresEXT(n, semaphores, __FILE__, __LINE__)
#define glIsSemaphoreEXT(semaphore) _glIsSemaphoreEXT(semaphore, __FILE__, __LINE__)
#define glSemaphoreParameterui64vEXT(semaphore, pname, params) _glSemaphoreParameterui64vEXT(semaphore, pname, params, __FILE__, __LINE__)
#define glGetSemaphoreParameterui64vEXT(semaphore, pname, params) _glGetSemaphoreParameterui64vEXT(semaphore, pname, params, __FILE__, __LINE__)
#define glWaitSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, srcLayouts) _glWaitSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, srcLayouts, __FILE__, __LINE__)
#define glSignalSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, dstLayouts) _glSignalSemaphoreEXT(semaphore, numBufferBarriers, buffers, numTextureBarriers, textures, dstLayouts, __FILE__, __LINE__)
#define glImportSemaphoreFdEXT(semaphore, handleType, fd) _glImportSemaphoreFdEXT(semaphore, handleType, fd, __FILE__, __LINE__)
#define glImportSemaphoreWin32HandleEXT(semaphore, handleType, handle) _glImportSemaphoreWin32HandleEXT(semaphore, handleType, handle, __FILE__, __LINE__)
#define glImportSemaphoreWin32NameEXT(semaphore, handleType, name) _glImportSemaphoreWin32NameEXT(semaphore, handleType, name, __FILE__, __LINE__)
#define glUseShaderProgramEXT(type, program) _glUseShaderProgramEXT(type, program, __FILE__, __LINE__)
#define glActiveProgramEXT(program) _glActiveProgramEXT(program, __FILE__, __LINE__)
#define glCreateShaderProgramEXT(type, string) _glCreateShaderProgramEXT(type, string, __FILE__, __LINE__)
#define glActiveShaderProgramEXT(pipeline, program) _glActiveShaderProgramEXT(pipeline, program, __FILE__, __LINE__)
#define glBindProgramPipelineEXT(pipeline) _glBindProgramPipelineEXT(pipeline, __FILE__, __LINE__)
#define glCreateShaderProgramvEXT(type, count, strings) _glCreateShaderProgramvEXT(type, count, strings, __FILE__, __LINE__)
#define glDeleteProgramPipelinesEXT(n, pipelines) _glDeleteProgramPipelinesEXT(n, pipelines, __FILE__, __LINE__)
#define glGenProgramPipelinesEXT(n, pipelines) _glGenProgramPipelinesEXT(n, pipelines, __FILE__, __LINE__)
#define glGetProgramPipelineInfoLogEXT(pipeline, bufSize, length, infoLog) _glGetProgramPipelineInfoLogEXT(pipeline, bufSize, length, infoLog, __FILE__, __LINE__)
#define glGetProgramPipelineivEXT(pipeline, pname, params) _glGetProgramPipelineivEXT(pipeline, pname, params, __FILE__, __LINE__)
#define glIsProgramPipelineEXT(pipeline) _glIsProgramPipelineEXT(pipeline, __FILE__, __LINE__)
#define glUseProgramStagesEXT(pipeline, stages, program) _glUseProgramStagesEXT(pipeline, stages, program, __FILE__, __LINE__)
#define glValidateProgramPipelineEXT(pipeline) _glValidateProgramPipelineEXT(pipeline, __FILE__, __LINE__)
#define glFramebufferFetchBarrierEXT() _glFramebufferFetchBarrierEXT(__FILE__, __LINE__)
#define glBindImageTextureEXT(index, texture, level, layered, layer, access, format) _glBindImageTextureEXT(index, texture, level, layered, layer, access, format, __FILE__, __LINE__)
#define glMemoryBarrierEXT(barriers) _glMemoryBarrierEXT(barriers, __FILE__, __LINE__)
#define glStencilClearTagEXT(stencilTagBits, stencilClearTag) _glStencilClearTagEXT(stencilTagBits, stencilClearTag, __FILE__, __LINE__)
#define glActiveStencilFaceEXT(face) _glActiveStencilFaceEXT(face, __FILE__, __LINE__)
#define glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels) _glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels, __FILE__, __LINE__)
#define glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels) _glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels, __FILE__, __LINE__)
#define glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels) _glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels, __FILE__, __LINE__)
#define glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) _glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels, __FILE__, __LINE__)
#define glFramebufferTextureLayerEXT(target, attachment, texture, level, layer) _glFramebufferTextureLayerEXT(target, attachment, texture, level, layer, __FILE__, __LINE__)
#define glTexBufferEXT(target, internalformat, buffer) _glTexBufferEXT(target, internalformat, buffer, __FILE__, __LINE__)
#define glTexParameterIivEXT(target, pname, params) _glTexParameterIivEXT(target, pname, params, __FILE__, __LINE__)
#define glTexParameterIuivEXT(target, pname, params) _glTexParameterIuivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameterIivEXT(target, pname, params) _glGetTexParameterIivEXT(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameterIuivEXT(target, pname, params) _glGetTexParameterIuivEXT(target, pname, params, __FILE__, __LINE__)
#define glClearColorIiEXT(red, green, blue, alpha) _glClearColorIiEXT(red, green, blue, alpha, __FILE__, __LINE__)
#define glClearColorIuiEXT(red, green, blue, alpha) _glClearColorIuiEXT(red, green, blue, alpha, __FILE__, __LINE__)
#define glAreTexturesResidentEXT(n, textures, residences) _glAreTexturesResidentEXT(n, textures, residences, __FILE__, __LINE__)
#define glBindTextureEXT(target, texture) _glBindTextureEXT(target, texture, __FILE__, __LINE__)
#define glDeleteTexturesEXT(n, textures) _glDeleteTexturesEXT(n, textures, __FILE__, __LINE__)
#define glGenTexturesEXT(n, textures) _glGenTexturesEXT(n, textures, __FILE__, __LINE__)
#define glIsTextureEXT(texture) _glIsTextureEXT(texture, __FILE__, __LINE__)
#define glPrioritizeTexturesEXT(n, textures, priorities) _glPrioritizeTexturesEXT(n, textures, priorities, __FILE__, __LINE__)
#define glTextureNormalEXT(mode) _glTextureNormalEXT(mode, __FILE__, __LINE__)
#define glGetQueryObjecti64vEXT(id, pname, params) _glGetQueryObjecti64vEXT(id, pname, params, __FILE__, __LINE__)
#define glGetQueryObjectui64vEXT(id, pname, params) _glGetQueryObjectui64vEXT(id, pname, params, __FILE__, __LINE__)
#define glBeginTransformFeedbackEXT(primitiveMode) _glBeginTransformFeedbackEXT(primitiveMode, __FILE__, __LINE__)
#define glEndTransformFeedbackEXT() _glEndTransformFeedbackEXT(__FILE__, __LINE__)
#define glBindBufferRangeEXT(target, index, buffer, offset, size) _glBindBufferRangeEXT(target, index, buffer, offset, size, __FILE__, __LINE__)
#define glBindBufferOffsetEXT(target, index, buffer, offset) _glBindBufferOffsetEXT(target, index, buffer, offset, __FILE__, __LINE__)
#define glBindBufferBaseEXT(target, index, buffer) _glBindBufferBaseEXT(target, index, buffer, __FILE__, __LINE__)
#define glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode) _glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode, __FILE__, __LINE__)
#define glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name) _glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name, __FILE__, __LINE__)
#define glArrayElementEXT(i) _glArrayElementEXT(i, __FILE__, __LINE__)
#define glColorPointerEXT(size, type, stride, count, pointer) _glColorPointerEXT(size, type, stride, count, pointer, __FILE__, __LINE__)
#define glDrawArraysEXT(mode, first, count) _glDrawArraysEXT(mode, first, count, __FILE__, __LINE__)
#define glEdgeFlagPointerEXT(stride, count, pointer) _glEdgeFlagPointerEXT(stride, count, pointer, __FILE__, __LINE__)
#define glGetPointervEXT(pname, params) _glGetPointervEXT(pname, params, __FILE__, __LINE__)
#define glIndexPointerEXT(type, stride, count, pointer) _glIndexPointerEXT(type, stride, count, pointer, __FILE__, __LINE__)
#define glNormalPointerEXT(type, stride, count, pointer) _glNormalPointerEXT(type, stride, count, pointer, __FILE__, __LINE__)
#define glTexCoordPointerEXT(size, type, stride, count, pointer) _glTexCoordPointerEXT(size, type, stride, count, pointer, __FILE__, __LINE__)
#define glVertexPointerEXT(size, type, stride, count, pointer) _glVertexPointerEXT(size, type, stride, count, pointer, __FILE__, __LINE__)
#define glVertexAttribL1dEXT(index, x) _glVertexAttribL1dEXT(index, x, __FILE__, __LINE__)
#define glVertexAttribL2dEXT(index, x, y) _glVertexAttribL2dEXT(index, x, y, __FILE__, __LINE__)
#define glVertexAttribL3dEXT(index, x, y, z) _glVertexAttribL3dEXT(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribL4dEXT(index, x, y, z, w) _glVertexAttribL4dEXT(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribL1dvEXT(index, v) _glVertexAttribL1dvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribL2dvEXT(index, v) _glVertexAttribL2dvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribL3dvEXT(index, v) _glVertexAttribL3dvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribL4dvEXT(index, v) _glVertexAttribL4dvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribLPointerEXT(index, size, type, stride, pointer) _glVertexAttribLPointerEXT(index, size, type, stride, pointer, __FILE__, __LINE__)
#define glGetVertexAttribLdvEXT(index, pname, params) _glGetVertexAttribLdvEXT(index, pname, params, __FILE__, __LINE__)
#define glBeginVertexShaderEXT() _glBeginVertexShaderEXT(__FILE__, __LINE__)
#define glEndVertexShaderEXT() _glEndVertexShaderEXT(__FILE__, __LINE__)
#define glBindVertexShaderEXT(id) _glBindVertexShaderEXT(id, __FILE__, __LINE__)
#define glGenVertexShadersEXT(range) _glGenVertexShadersEXT(range, __FILE__, __LINE__)
#define glDeleteVertexShaderEXT(id) _glDeleteVertexShaderEXT(id, __FILE__, __LINE__)
#define glShaderOp1EXT(op, res, arg1) _glShaderOp1EXT(op, res, arg1, __FILE__, __LINE__)
#define glShaderOp2EXT(op, res, arg1, arg2) _glShaderOp2EXT(op, res, arg1, arg2, __FILE__, __LINE__)
#define glShaderOp3EXT(op, res, arg1, arg2, arg3) _glShaderOp3EXT(op, res, arg1, arg2, arg3, __FILE__, __LINE__)
#define glSwizzleEXT(res, in, outX, outY, outZ, outW) _glSwizzleEXT(res, in, outX, outY, outZ, outW, __FILE__, __LINE__)
#define glWriteMaskEXT(res, in, outX, outY, outZ, outW) _glWriteMaskEXT(res, in, outX, outY, outZ, outW, __FILE__, __LINE__)
#define glInsertComponentEXT(res, src, num) _glInsertComponentEXT(res, src, num, __FILE__, __LINE__)
#define glExtractComponentEXT(res, src, num) _glExtractComponentEXT(res, src, num, __FILE__, __LINE__)
#define glGenSymbolsEXT(datatype, storagetype, range, components) _glGenSymbolsEXT(datatype, storagetype, range, components, __FILE__, __LINE__)
#define glSetInvariantEXT(id, type, addr) _glSetInvariantEXT(id, type, addr, __FILE__, __LINE__)
#define glSetLocalConstantEXT(id, type, addr) _glSetLocalConstantEXT(id, type, addr, __FILE__, __LINE__)
#define glVariantbvEXT(id, addr) _glVariantbvEXT(id, addr, __FILE__, __LINE__)
#define glVariantsvEXT(id, addr) _glVariantsvEXT(id, addr, __FILE__, __LINE__)
#define glVariantivEXT(id, addr) _glVariantivEXT(id, addr, __FILE__, __LINE__)
#define glVariantfvEXT(id, addr) _glVariantfvEXT(id, addr, __FILE__, __LINE__)
#define glVariantdvEXT(id, addr) _glVariantdvEXT(id, addr, __FILE__, __LINE__)
#define glVariantubvEXT(id, addr) _glVariantubvEXT(id, addr, __FILE__, __LINE__)
#define glVariantusvEXT(id, addr) _glVariantusvEXT(id, addr, __FILE__, __LINE__)
#define glVariantuivEXT(id, addr) _glVariantuivEXT(id, addr, __FILE__, __LINE__)
#define glVariantPointerEXT(id, type, stride, addr) _glVariantPointerEXT(id, type, stride, addr, __FILE__, __LINE__)
#define glEnableVariantClientStateEXT(id) _glEnableVariantClientStateEXT(id, __FILE__, __LINE__)
#define glDisableVariantClientStateEXT(id) _glDisableVariantClientStateEXT(id, __FILE__, __LINE__)
#define glBindLightParameterEXT(light, value) _glBindLightParameterEXT(light, value, __FILE__, __LINE__)
#define glBindMaterialParameterEXT(face, value) _glBindMaterialParameterEXT(face, value, __FILE__, __LINE__)
#define glBindTexGenParameterEXT(unit, coord, value) _glBindTexGenParameterEXT(unit, coord, value, __FILE__, __LINE__)
#define glBindTextureUnitParameterEXT(unit, value) _glBindTextureUnitParameterEXT(unit, value, __FILE__, __LINE__)
#define glBindParameterEXT(value) _glBindParameterEXT(value, __FILE__, __LINE__)
#define glIsVariantEnabledEXT(id, cap) _glIsVariantEnabledEXT(id, cap, __FILE__, __LINE__)
#define glGetVariantBooleanvEXT(id, value, data) _glGetVariantBooleanvEXT(id, value, data, __FILE__, __LINE__)
#define glGetVariantIntegervEXT(id, value, data) _glGetVariantIntegervEXT(id, value, data, __FILE__, __LINE__)
#define glGetVariantFloatvEXT(id, value, data) _glGetVariantFloatvEXT(id, value, data, __FILE__, __LINE__)
#define glGetVariantPointervEXT(id, value, data) _glGetVariantPointervEXT(id, value, data, __FILE__, __LINE__)
#define glGetInvariantBooleanvEXT(id, value, data) _glGetInvariantBooleanvEXT(id, value, data, __FILE__, __LINE__)
#define glGetInvariantIntegervEXT(id, value, data) _glGetInvariantIntegervEXT(id, value, data, __FILE__, __LINE__)
#define glGetInvariantFloatvEXT(id, value, data) _glGetInvariantFloatvEXT(id, value, data, __FILE__, __LINE__)
#define glGetLocalConstantBooleanvEXT(id, value, data) _glGetLocalConstantBooleanvEXT(id, value, data, __FILE__, __LINE__)
#define glGetLocalConstantIntegervEXT(id, value, data) _glGetLocalConstantIntegervEXT(id, value, data, __FILE__, __LINE__)
#define glGetLocalConstantFloatvEXT(id, value, data) _glGetLocalConstantFloatvEXT(id, value, data, __FILE__, __LINE__)
#define glVertexWeightfEXT(weight) _glVertexWeightfEXT(weight, __FILE__, __LINE__)
#define glVertexWeightfvEXT(weight) _glVertexWeightfvEXT(weight, __FILE__, __LINE__)
#define glVertexWeightPointerEXT(size, type, stride, pointer) _glVertexWeightPointerEXT(size, type, stride, pointer, __FILE__, __LINE__)
#define glAcquireKeyedMutexWin32EXT(memory, key, timeout) _glAcquireKeyedMutexWin32EXT(memory, key, timeout, __FILE__, __LINE__)
#define glReleaseKeyedMutexWin32EXT(memory, key) _glReleaseKeyedMutexWin32EXT(memory, key, __FILE__, __LINE__)
#define glWindowRectanglesEXT(mode, count, box) _glWindowRectanglesEXT(mode, count, box, __FILE__, __LINE__)
#define glImportSyncEXT(external_sync_type, external_sync, flags) _glImportSyncEXT(external_sync_type, external_sync, flags, __FILE__, __LINE__)
#define glFrameTerminatorGREMEDY() _glFrameTerminatorGREMEDY(__FILE__, __LINE__)
#define glStringMarkerGREMEDY(len, string) _glStringMarkerGREMEDY(len, string, __FILE__, __LINE__)
#define glImageTransformParameteriHP(target, pname, param) _glImageTransformParameteriHP(target, pname, param, __FILE__, __LINE__)
#define glImageTransformParameterfHP(target, pname, param) _glImageTransformParameterfHP(target, pname, param, __FILE__, __LINE__)
#define glImageTransformParameterivHP(target, pname, params) _glImageTransformParameterivHP(target, pname, params, __FILE__, __LINE__)
#define glImageTransformParameterfvHP(target, pname, params) _glImageTransformParameterfvHP(target, pname, params, __FILE__, __LINE__)
#define glGetImageTransformParameterivHP(target, pname, params) _glGetImageTransformParameterivHP(target, pname, params, __FILE__, __LINE__)
#define glGetImageTransformParameterfvHP(target, pname, params) _glGetImageTransformParameterfvHP(target, pname, params, __FILE__, __LINE__)
#define glMultiModeDrawArraysIBM(mode, first, count, primcount, modestride) _glMultiModeDrawArraysIBM(mode, first, count, primcount, modestride, __FILE__, __LINE__)
#define glMultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride) _glMultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride, __FILE__, __LINE__)
#define glFlushStaticDataIBM(target) _glFlushStaticDataIBM(target, __FILE__, __LINE__)
#define glColorPointerListIBM(size, type, stride, pointer, ptrstride) _glColorPointerListIBM(size, type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glSecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride) _glSecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glEdgeFlagPointerListIBM(stride, pointer, ptrstride) _glEdgeFlagPointerListIBM(stride, pointer, ptrstride, __FILE__, __LINE__)
#define glFogCoordPointerListIBM(type, stride, pointer, ptrstride) _glFogCoordPointerListIBM(type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glIndexPointerListIBM(type, stride, pointer, ptrstride) _glIndexPointerListIBM(type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glNormalPointerListIBM(type, stride, pointer, ptrstride) _glNormalPointerListIBM(type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glTexCoordPointerListIBM(size, type, stride, pointer, ptrstride) _glTexCoordPointerListIBM(size, type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glVertexPointerListIBM(size, type, stride, pointer, ptrstride) _glVertexPointerListIBM(size, type, stride, pointer, ptrstride, __FILE__, __LINE__)
#define glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) _glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha, __FILE__, __LINE__)
#define glApplyFramebufferAttachmentCMAAINTEL() _glApplyFramebufferAttachmentCMAAINTEL(__FILE__, __LINE__)
#define glSyncTextureINTEL(texture) _glSyncTextureINTEL(texture, __FILE__, __LINE__)
#define glUnmapTexture2DINTEL(texture, level) _glUnmapTexture2DINTEL(texture, level, __FILE__, __LINE__)
#define glMapTexture2DINTEL(texture, level, access, stride, _) _glMapTexture2DINTEL(texture, level, access, stride, _, __FILE__, __LINE__)
#define glVertexPointervINTEL(size, type, pointer) _glVertexPointervINTEL(size, type, pointer, __FILE__, __LINE__)
#define glNormalPointervINTEL(type, pointer) _glNormalPointervINTEL(type, pointer, __FILE__, __LINE__)
#define glColorPointervINTEL(size, type, pointer) _glColorPointervINTEL(size, type, pointer, __FILE__, __LINE__)
#define glTexCoordPointervINTEL(size, type, pointer) _glTexCoordPointervINTEL(size, type, pointer, __FILE__, __LINE__)
#define glBeginPerfQueryINTEL(queryHandle) _glBeginPerfQueryINTEL(queryHandle, __FILE__, __LINE__)
#define glCreatePerfQueryINTEL(queryId, queryHandle) _glCreatePerfQueryINTEL(queryId, queryHandle, __FILE__, __LINE__)
#define glDeletePerfQueryINTEL(queryHandle) _glDeletePerfQueryINTEL(queryHandle, __FILE__, __LINE__)
#define glEndPerfQueryINTEL(queryHandle) _glEndPerfQueryINTEL(queryHandle, __FILE__, __LINE__)
#define glGetFirstPerfQueryIdINTEL(queryId) _glGetFirstPerfQueryIdINTEL(queryId, __FILE__, __LINE__)
#define glGetNextPerfQueryIdINTEL(queryId, nextQueryId) _glGetNextPerfQueryIdINTEL(queryId, nextQueryId, __FILE__, __LINE__)
#define glGetPerfCounterInfoINTEL(queryId, counterId, counterNameLength, counterName, counterDescLength, counterDesc, counterOffset, counterDataSize, counterTypeEnum, counterDataTypeEnum, rawCounterMaxValue) _glGetPerfCounterInfoINTEL(queryId, counterId, counterNameLength, counterName, counterDescLength, counterDesc, counterOffset, counterDataSize, counterTypeEnum, counterDataTypeEnum, rawCounterMaxValue, __FILE__, __LINE__)
#define glGetPerfQueryDataINTEL(queryHandle, flags, dataSize, data, bytesWritten) _glGetPerfQueryDataINTEL(queryHandle, flags, dataSize, data, bytesWritten, __FILE__, __LINE__)
#define glGetPerfQueryIdByNameINTEL(queryName, queryId) _glGetPerfQueryIdByNameINTEL(queryName, queryId, __FILE__, __LINE__)
#define glGetPerfQueryInfoINTEL(queryId, queryNameLength, queryName, dataSize, noCounters, noInstances, capsMask) _glGetPerfQueryInfoINTEL(queryId, queryNameLength, queryName, dataSize, noCounters, noInstances, capsMask, __FILE__, __LINE__)
#define glBlendBarrierKHR() _glBlendBarrierKHR(__FILE__, __LINE__)
#define glDebugMessageControl(source, type, severity, count, ids, enabled) _glDebugMessageControl(source, type, severity, count, ids, enabled, __FILE__, __LINE__)
#define glDebugMessageInsert(source, type, id, severity, length, buf) _glDebugMessageInsert(source, type, id, severity, length, buf, __FILE__, __LINE__)
#define glDebugMessageCallback(callback, userParam) _glDebugMessageCallback(callback, userParam, __FILE__, __LINE__)
#define glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog) _glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog, __FILE__, __LINE__)
#define glPushDebugGroup(source, id, length, message) _glPushDebugGroup(source, id, length, message, __FILE__, __LINE__)
#define glPopDebugGroup() _glPopDebugGroup(__FILE__, __LINE__)
#define glObjectLabel(identifier, name, length, label) _glObjectLabel(identifier, name, length, label, __FILE__, __LINE__)
#define glGetObjectLabel(identifier, name, bufSize, length, label) _glGetObjectLabel(identifier, name, bufSize, length, label, __FILE__, __LINE__)
#define glObjectPtrLabel(ptr, length, label) _glObjectPtrLabel(ptr, length, label, __FILE__, __LINE__)
#define glGetObjectPtrLabel(ptr, bufSize, length, label) _glGetObjectPtrLabel(ptr, bufSize, length, label, __FILE__, __LINE__)
#define glGetPointerv(pname, params) _glGetPointerv(pname, params, __FILE__, __LINE__)
#define glDebugMessageControlKHR(source, type, severity, count, ids, enabled) _glDebugMessageControlKHR(source, type, severity, count, ids, enabled, __FILE__, __LINE__)
#define glDebugMessageInsertKHR(source, type, id, severity, length, buf) _glDebugMessageInsertKHR(source, type, id, severity, length, buf, __FILE__, __LINE__)
#define glDebugMessageCallbackKHR(callback, userParam) _glDebugMessageCallbackKHR(callback, userParam, __FILE__, __LINE__)
#define glGetDebugMessageLogKHR(count, bufSize, sources, types, ids, severities, lengths, messageLog) _glGetDebugMessageLogKHR(count, bufSize, sources, types, ids, severities, lengths, messageLog, __FILE__, __LINE__)
#define glPushDebugGroupKHR(source, id, length, message) _glPushDebugGroupKHR(source, id, length, message, __FILE__, __LINE__)
#define glPopDebugGroupKHR() _glPopDebugGroupKHR(__FILE__, __LINE__)
#define glObjectLabelKHR(identifier, name, length, label) _glObjectLabelKHR(identifier, name, length, label, __FILE__, __LINE__)
#define glGetObjectLabelKHR(identifier, name, bufSize, length, label) _glGetObjectLabelKHR(identifier, name, bufSize, length, label, __FILE__, __LINE__)
#define glObjectPtrLabelKHR(ptr, length, label) _glObjectPtrLabelKHR(ptr, length, label, __FILE__, __LINE__)
#define glGetObjectPtrLabelKHR(ptr, bufSize, length, label) _glGetObjectPtrLabelKHR(ptr, bufSize, length, label, __FILE__, __LINE__)
#define glGetPointervKHR(pname, params) _glGetPointervKHR(pname, params, __FILE__, __LINE__)
#define glMaxShaderCompilerThreadsKHR(count) _glMaxShaderCompilerThreadsKHR(count, __FILE__, __LINE__)
#define glGetGraphicsResetStatus() _glGetGraphicsResetStatus(__FILE__, __LINE__)
#define glReadnPixels(x, y, width, height, format, type, bufSize, data) _glReadnPixels(x, y, width, height, format, type, bufSize, data, __FILE__, __LINE__)
#define glGetnUniformfv(program, location, bufSize, params) _glGetnUniformfv(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformiv(program, location, bufSize, params) _glGetnUniformiv(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformuiv(program, location, bufSize, params) _glGetnUniformuiv(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetGraphicsResetStatusKHR() _glGetGraphicsResetStatusKHR(__FILE__, __LINE__)
#define glReadnPixelsKHR(x, y, width, height, format, type, bufSize, data) _glReadnPixelsKHR(x, y, width, height, format, type, bufSize, data, __FILE__, __LINE__)
#define glGetnUniformfvKHR(program, location, bufSize, params) _glGetnUniformfvKHR(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformivKHR(program, location, bufSize, params) _glGetnUniformivKHR(program, location, bufSize, params, __FILE__, __LINE__)
#define glGetnUniformuivKHR(program, location, bufSize, params) _glGetnUniformuivKHR(program, location, bufSize, params, __FILE__, __LINE__)
#define glFramebufferParameteriMESA(target, pname, param) _glFramebufferParameteriMESA(target, pname, param, __FILE__, __LINE__)
#define glGetFramebufferParameterivMESA(target, pname, params) _glGetFramebufferParameterivMESA(target, pname, params, __FILE__, __LINE__)
#define glResizeBuffersMESA() _glResizeBuffersMESA(__FILE__, __LINE__)
#define glWindowPos2dMESA(x, y) _glWindowPos2dMESA(x, y, __FILE__, __LINE__)
#define glWindowPos2dvMESA(v) _glWindowPos2dvMESA(v, __FILE__, __LINE__)
#define glWindowPos2fMESA(x, y) _glWindowPos2fMESA(x, y, __FILE__, __LINE__)
#define glWindowPos2fvMESA(v) _glWindowPos2fvMESA(v, __FILE__, __LINE__)
#define glWindowPos2iMESA(x, y) _glWindowPos2iMESA(x, y, __FILE__, __LINE__)
#define glWindowPos2ivMESA(v) _glWindowPos2ivMESA(v, __FILE__, __LINE__)
#define glWindowPos2sMESA(x, y) _glWindowPos2sMESA(x, y, __FILE__, __LINE__)
#define glWindowPos2svMESA(v) _glWindowPos2svMESA(v, __FILE__, __LINE__)
#define glWindowPos3dMESA(x, y, z) _glWindowPos3dMESA(x, y, z, __FILE__, __LINE__)
#define glWindowPos3dvMESA(v) _glWindowPos3dvMESA(v, __FILE__, __LINE__)
#define glWindowPos3fMESA(x, y, z) _glWindowPos3fMESA(x, y, z, __FILE__, __LINE__)
#define glWindowPos3fvMESA(v) _glWindowPos3fvMESA(v, __FILE__, __LINE__)
#define glWindowPos3iMESA(x, y, z) _glWindowPos3iMESA(x, y, z, __FILE__, __LINE__)
#define glWindowPos3ivMESA(v) _glWindowPos3ivMESA(v, __FILE__, __LINE__)
#define glWindowPos3sMESA(x, y, z) _glWindowPos3sMESA(x, y, z, __FILE__, __LINE__)
#define glWindowPos3svMESA(v) _glWindowPos3svMESA(v, __FILE__, __LINE__)
#define glWindowPos4dMESA(x, y, z, w) _glWindowPos4dMESA(x, y, z, w, __FILE__, __LINE__)
#define glWindowPos4dvMESA(v) _glWindowPos4dvMESA(v, __FILE__, __LINE__)
#define glWindowPos4fMESA(x, y, z, w) _glWindowPos4fMESA(x, y, z, w, __FILE__, __LINE__)
#define glWindowPos4fvMESA(v) _glWindowPos4fvMESA(v, __FILE__, __LINE__)
#define glWindowPos4iMESA(x, y, z, w) _glWindowPos4iMESA(x, y, z, w, __FILE__, __LINE__)
#define glWindowPos4ivMESA(v) _glWindowPos4ivMESA(v, __FILE__, __LINE__)
#define glWindowPos4sMESA(x, y, z, w) _glWindowPos4sMESA(x, y, z, w, __FILE__, __LINE__)
#define glWindowPos4svMESA(v) _glWindowPos4svMESA(v, __FILE__, __LINE__)
#define glBeginConditionalRenderNVX(id) _glBeginConditionalRenderNVX(id, __FILE__, __LINE__)
#define glEndConditionalRenderNVX() _glEndConditionalRenderNVX(__FILE__, __LINE__)
#define glUploadGpuMaskNVX(mask) _glUploadGpuMaskNVX(mask, __FILE__, __LINE__)
#define glMulticastViewportArrayvNVX(gpu, first, count, v) _glMulticastViewportArrayvNVX(gpu, first, count, v, __FILE__, __LINE__)
#define glMulticastViewportPositionWScaleNVX(gpu, index, xcoeff, ycoeff) _glMulticastViewportPositionWScaleNVX(gpu, index, xcoeff, ycoeff, __FILE__, __LINE__)
#define glMulticastScissorArrayvNVX(gpu, first, count, v) _glMulticastScissorArrayvNVX(gpu, first, count, v, __FILE__, __LINE__)
#define glAsyncCopyBufferSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, fenceValueArray, readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size, signalSemaphoreCount, signalSemaphoreArray, signalValueArray) _glAsyncCopyBufferSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, fenceValueArray, readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size, signalSemaphoreCount, signalSemaphoreArray, signalValueArray, __FILE__, __LINE__)
#define glAsyncCopyImageSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, waitValueArray, srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth, signalSemaphoreCount, signalSemaphoreArray, signalValueArray) _glAsyncCopyImageSubDataNVX(waitSemaphoreCount, waitSemaphoreArray, waitValueArray, srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth, signalSemaphoreCount, signalSemaphoreArray, signalValueArray, __FILE__, __LINE__)
#define glLGPUNamedBufferSubDataNVX(gpuMask, buffer, offset, size, data) _glLGPUNamedBufferSubDataNVX(gpuMask, buffer, offset, size, data, __FILE__, __LINE__)
#define glLGPUCopyImageSubDataNVX(sourceGpu, destinationGpuMask, srcName, srcTarget, srcLevel, srcX, srxY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth) _glLGPUCopyImageSubDataNVX(sourceGpu, destinationGpuMask, srcName, srcTarget, srcLevel, srcX, srxY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth, __FILE__, __LINE__)
#define glLGPUInterlockNVX() _glLGPUInterlockNVX(__FILE__, __LINE__)
#define glCreateProgressFenceNVX() _glCreateProgressFenceNVX(__FILE__, __LINE__)
#define glSignalSemaphoreui64NVX(signalGpu, fenceObjectCount, semaphoreArray, fenceValueArray) _glSignalSemaphoreui64NVX(signalGpu, fenceObjectCount, semaphoreArray, fenceValueArray, __FILE__, __LINE__)
#define glWaitSemaphoreui64NVX(waitGpu, fenceObjectCount, semaphoreArray, fenceValueArray) _glWaitSemaphoreui64NVX(waitGpu, fenceObjectCount, semaphoreArray, fenceValueArray, __FILE__, __LINE__)
#define glClientWaitSemaphoreui64NVX(fenceObjectCount, semaphoreArray, fenceValueArray) _glClientWaitSemaphoreui64NVX(fenceObjectCount, semaphoreArray, fenceValueArray, __FILE__, __LINE__)
#define glAlphaToCoverageDitherControlNV(mode) _glAlphaToCoverageDitherControlNV(mode, __FILE__, __LINE__)
#define glMultiDrawArraysIndirectBindlessNV(mode, indirect, drawCount, stride, vertexBufferCount) _glMultiDrawArraysIndirectBindlessNV(mode, indirect, drawCount, stride, vertexBufferCount, __FILE__, __LINE__)
#define glMultiDrawElementsIndirectBindlessNV(mode, type, indirect, drawCount, stride, vertexBufferCount) _glMultiDrawElementsIndirectBindlessNV(mode, type, indirect, drawCount, stride, vertexBufferCount, __FILE__, __LINE__)
#define glMultiDrawArraysIndirectBindlessCountNV(mode, indirect, drawCount, maxDrawCount, stride, vertexBufferCount) _glMultiDrawArraysIndirectBindlessCountNV(mode, indirect, drawCount, maxDrawCount, stride, vertexBufferCount, __FILE__, __LINE__)
#define glMultiDrawElementsIndirectBindlessCountNV(mode, type, indirect, drawCount, maxDrawCount, stride, vertexBufferCount) _glMultiDrawElementsIndirectBindlessCountNV(mode, type, indirect, drawCount, maxDrawCount, stride, vertexBufferCount, __FILE__, __LINE__)
#define glGetTextureHandleNV(texture) _glGetTextureHandleNV(texture, __FILE__, __LINE__)
#define glGetTextureSamplerHandleNV(texture, sampler) _glGetTextureSamplerHandleNV(texture, sampler, __FILE__, __LINE__)
#define glMakeTextureHandleResidentNV(handle) _glMakeTextureHandleResidentNV(handle, __FILE__, __LINE__)
#define glMakeTextureHandleNonResidentNV(handle) _glMakeTextureHandleNonResidentNV(handle, __FILE__, __LINE__)
#define glGetImageHandleNV(texture, level, layered, layer, format) _glGetImageHandleNV(texture, level, layered, layer, format, __FILE__, __LINE__)
#define glMakeImageHandleResidentNV(handle, access) _glMakeImageHandleResidentNV(handle, access, __FILE__, __LINE__)
#define glMakeImageHandleNonResidentNV(handle) _glMakeImageHandleNonResidentNV(handle, __FILE__, __LINE__)
#define glUniformHandleui64NV(location, value) _glUniformHandleui64NV(location, value, __FILE__, __LINE__)
#define glUniformHandleui64vNV(location, count, value) _glUniformHandleui64vNV(location, count, value, __FILE__, __LINE__)
#define glProgramUniformHandleui64NV(program, location, value) _glProgramUniformHandleui64NV(program, location, value, __FILE__, __LINE__)
#define glProgramUniformHandleui64vNV(program, location, count, values) _glProgramUniformHandleui64vNV(program, location, count, values, __FILE__, __LINE__)
#define glIsTextureHandleResidentNV(handle) _glIsTextureHandleResidentNV(handle, __FILE__, __LINE__)
#define glIsImageHandleResidentNV(handle) _glIsImageHandleResidentNV(handle, __FILE__, __LINE__)
#define glBlendParameteriNV(pname, value) _glBlendParameteriNV(pname, value, __FILE__, __LINE__)
#define glBlendBarrierNV() _glBlendBarrierNV(__FILE__, __LINE__)
#define glViewportPositionWScaleNV(index, xcoeff, ycoeff) _glViewportPositionWScaleNV(index, xcoeff, ycoeff, __FILE__, __LINE__)
#define glCreateStatesNV(n, states) _glCreateStatesNV(n, states, __FILE__, __LINE__)
#define glDeleteStatesNV(n, states) _glDeleteStatesNV(n, states, __FILE__, __LINE__)
#define glIsStateNV(state) _glIsStateNV(state, __FILE__, __LINE__)
#define glStateCaptureNV(state, mode) _glStateCaptureNV(state, mode, __FILE__, __LINE__)
#define glGetCommandHeaderNV(tokenID, size) _glGetCommandHeaderNV(tokenID, size, __FILE__, __LINE__)
#define glGetStageIndexNV(shadertype) _glGetStageIndexNV(shadertype, __FILE__, __LINE__)
#define glDrawCommandsNV(primitiveMode, buffer, indirects, sizes, count) _glDrawCommandsNV(primitiveMode, buffer, indirects, sizes, count, __FILE__, __LINE__)
#define glDrawCommandsAddressNV(primitiveMode, indirects, sizes, count) _glDrawCommandsAddressNV(primitiveMode, indirects, sizes, count, __FILE__, __LINE__)
#define glDrawCommandsStatesNV(buffer, indirects, sizes, states, fbos, count) _glDrawCommandsStatesNV(buffer, indirects, sizes, states, fbos, count, __FILE__, __LINE__)
#define glDrawCommandsStatesAddressNV(indirects, sizes, states, fbos, count) _glDrawCommandsStatesAddressNV(indirects, sizes, states, fbos, count, __FILE__, __LINE__)
#define glCreateCommandListsNV(n, lists) _glCreateCommandListsNV(n, lists, __FILE__, __LINE__)
#define glDeleteCommandListsNV(n, lists) _glDeleteCommandListsNV(n, lists, __FILE__, __LINE__)
#define glIsCommandListNV(list) _glIsCommandListNV(list, __FILE__, __LINE__)
#define glListDrawCommandsStatesClientNV(list, segment, indirects, sizes, states, fbos, count) _glListDrawCommandsStatesClientNV(list, segment, indirects, sizes, states, fbos, count, __FILE__, __LINE__)
#define glCommandListSegmentsNV(list, segments) _glCommandListSegmentsNV(list, segments, __FILE__, __LINE__)
#define glCompileCommandListNV(list) _glCompileCommandListNV(list, __FILE__, __LINE__)
#define glCallCommandListNV(list) _glCallCommandListNV(list, __FILE__, __LINE__)
#define glBeginConditionalRenderNV(id, mode) _glBeginConditionalRenderNV(id, mode, __FILE__, __LINE__)
#define glEndConditionalRenderNV() _glEndConditionalRenderNV(__FILE__, __LINE__)
#define glSubpixelPrecisionBiasNV(xbits, ybits) _glSubpixelPrecisionBiasNV(xbits, ybits, __FILE__, __LINE__)
#define glConservativeRasterParameterfNV(pname, value) _glConservativeRasterParameterfNV(pname, value, __FILE__, __LINE__)
#define glConservativeRasterParameteriNV(pname, param) _glConservativeRasterParameteriNV(pname, param, __FILE__, __LINE__)
#define glCopyImageSubDataNV(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth) _glCopyImageSubDataNV(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth, __FILE__, __LINE__)
#define glDepthRangedNV(zNear, zFar) _glDepthRangedNV(zNear, zFar, __FILE__, __LINE__)
#define glClearDepthdNV(depth) _glClearDepthdNV(depth, __FILE__, __LINE__)
#define glDepthBoundsdNV(zmin, zmax) _glDepthBoundsdNV(zmin, zmax, __FILE__, __LINE__)
#define glDrawTextureNV(texture, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1) _glDrawTextureNV(texture, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1, __FILE__, __LINE__)
#define glDrawVkImageNV(vkImage, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1) _glDrawVkImageNV(vkImage, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1, __FILE__, __LINE__)
#define glGetVkProcAddrNV(name) _glGetVkProcAddrNV(name, __FILE__, __LINE__)
#define glWaitVkSemaphoreNV(vkSemaphore) _glWaitVkSemaphoreNV(vkSemaphore, __FILE__, __LINE__)
#define glSignalVkSemaphoreNV(vkSemaphore) _glSignalVkSemaphoreNV(vkSemaphore, __FILE__, __LINE__)
#define glSignalVkFenceNV(vkFence) _glSignalVkFenceNV(vkFence, __FILE__, __LINE__)
#define glMapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points) _glMapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points, __FILE__, __LINE__)
#define glMapParameterivNV(target, pname, params) _glMapParameterivNV(target, pname, params, __FILE__, __LINE__)
#define glMapParameterfvNV(target, pname, params) _glMapParameterfvNV(target, pname, params, __FILE__, __LINE__)
#define glGetMapControlPointsNV(target, index, type, ustride, vstride, packed, points) _glGetMapControlPointsNV(target, index, type, ustride, vstride, packed, points, __FILE__, __LINE__)
#define glGetMapParameterivNV(target, pname, params) _glGetMapParameterivNV(target, pname, params, __FILE__, __LINE__)
#define glGetMapParameterfvNV(target, pname, params) _glGetMapParameterfvNV(target, pname, params, __FILE__, __LINE__)
#define glGetMapAttribParameterivNV(target, index, pname, params) _glGetMapAttribParameterivNV(target, index, pname, params, __FILE__, __LINE__)
#define glGetMapAttribParameterfvNV(target, index, pname, params) _glGetMapAttribParameterfvNV(target, index, pname, params, __FILE__, __LINE__)
#define glEvalMapsNV(target, mode) _glEvalMapsNV(target, mode, __FILE__, __LINE__)
#define glGetMultisamplefvNV(pname, index, val) _glGetMultisamplefvNV(pname, index, val, __FILE__, __LINE__)
#define glSampleMaskIndexedNV(index, mask) _glSampleMaskIndexedNV(index, mask, __FILE__, __LINE__)
#define glTexRenderbufferNV(target, renderbuffer) _glTexRenderbufferNV(target, renderbuffer, __FILE__, __LINE__)
#define glDeleteFencesNV(n, fences) _glDeleteFencesNV(n, fences, __FILE__, __LINE__)
#define glGenFencesNV(n, fences) _glGenFencesNV(n, fences, __FILE__, __LINE__)
#define glIsFenceNV(fence) _glIsFenceNV(fence, __FILE__, __LINE__)
#define glTestFenceNV(fence) _glTestFenceNV(fence, __FILE__, __LINE__)
#define glGetFenceivNV(fence, pname, params) _glGetFenceivNV(fence, pname, params, __FILE__, __LINE__)
#define glFinishFenceNV(fence) _glFinishFenceNV(fence, __FILE__, __LINE__)
#define glSetFenceNV(fence, condition) _glSetFenceNV(fence, condition, __FILE__, __LINE__)
#define glFragmentCoverageColorNV(color) _glFragmentCoverageColorNV(color, __FILE__, __LINE__)
#define glProgramNamedParameter4fNV(id, len, name, x, y, z, w) _glProgramNamedParameter4fNV(id, len, name, x, y, z, w, __FILE__, __LINE__)
#define glProgramNamedParameter4fvNV(id, len, name, v) _glProgramNamedParameter4fvNV(id, len, name, v, __FILE__, __LINE__)
#define glProgramNamedParameter4dNV(id, len, name, x, y, z, w) _glProgramNamedParameter4dNV(id, len, name, x, y, z, w, __FILE__, __LINE__)
#define glProgramNamedParameter4dvNV(id, len, name, v) _glProgramNamedParameter4dvNV(id, len, name, v, __FILE__, __LINE__)
#define glGetProgramNamedParameterfvNV(id, len, name, params) _glGetProgramNamedParameterfvNV(id, len, name, params, __FILE__, __LINE__)
#define glGetProgramNamedParameterdvNV(id, len, name, params) _glGetProgramNamedParameterdvNV(id, len, name, params, __FILE__, __LINE__)
#define glCoverageModulationTableNV(n, v) _glCoverageModulationTableNV(n, v, __FILE__, __LINE__)
#define glGetCoverageModulationTableNV(bufSize, v) _glGetCoverageModulationTableNV(bufSize, v, __FILE__, __LINE__)
#define glCoverageModulationNV(components) _glCoverageModulationNV(components, __FILE__, __LINE__)
#define glRenderbufferStorageMultisampleCoverageNV(target, coverageSamples, colorSamples, internalformat, width, height) _glRenderbufferStorageMultisampleCoverageNV(target, coverageSamples, colorSamples, internalformat, width, height, __FILE__, __LINE__)
#define glProgramVertexLimitNV(target, limit) _glProgramVertexLimitNV(target, limit, __FILE__, __LINE__)
#define glFramebufferTextureEXT(target, attachment, texture, level) _glFramebufferTextureEXT(target, attachment, texture, level, __FILE__, __LINE__)
#define glFramebufferTextureFaceEXT(target, attachment, texture, level, face) _glFramebufferTextureFaceEXT(target, attachment, texture, level, face, __FILE__, __LINE__)
#define glRenderGpuMaskNV(mask) _glRenderGpuMaskNV(mask, __FILE__, __LINE__)
#define glMulticastBufferSubDataNV(gpuMask, buffer, offset, size, data) _glMulticastBufferSubDataNV(gpuMask, buffer, offset, size, data, __FILE__, __LINE__)
#define glMulticastCopyBufferSubDataNV(readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size) _glMulticastCopyBufferSubDataNV(readGpu, writeGpuMask, readBuffer, writeBuffer, readOffset, writeOffset, size, __FILE__, __LINE__)
#define glMulticastCopyImageSubDataNV(srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth) _glMulticastCopyImageSubDataNV(srcGpu, dstGpuMask, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth, __FILE__, __LINE__)
#define glMulticastBlitFramebufferNV(srcGpu, dstGpu, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) _glMulticastBlitFramebufferNV(srcGpu, dstGpu, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter, __FILE__, __LINE__)
#define glMulticastFramebufferSampleLocationsfvNV(gpu, framebuffer, start, count, v) _glMulticastFramebufferSampleLocationsfvNV(gpu, framebuffer, start, count, v, __FILE__, __LINE__)
#define glMulticastBarrierNV() _glMulticastBarrierNV(__FILE__, __LINE__)
#define glMulticastWaitSyncNV(signalGpu, waitGpuMask) _glMulticastWaitSyncNV(signalGpu, waitGpuMask, __FILE__, __LINE__)
#define glMulticastGetQueryObjectivNV(gpu, id, pname, params) _glMulticastGetQueryObjectivNV(gpu, id, pname, params, __FILE__, __LINE__)
#define glMulticastGetQueryObjectuivNV(gpu, id, pname, params) _glMulticastGetQueryObjectuivNV(gpu, id, pname, params, __FILE__, __LINE__)
#define glMulticastGetQueryObjecti64vNV(gpu, id, pname, params) _glMulticastGetQueryObjecti64vNV(gpu, id, pname, params, __FILE__, __LINE__)
#define glMulticastGetQueryObjectui64vNV(gpu, id, pname, params) _glMulticastGetQueryObjectui64vNV(gpu, id, pname, params, __FILE__, __LINE__)
#define glProgramLocalParameterI4iNV(target, index, x, y, z, w) _glProgramLocalParameterI4iNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramLocalParameterI4ivNV(target, index, params) _glProgramLocalParameterI4ivNV(target, index, params, __FILE__, __LINE__)
#define glProgramLocalParametersI4ivNV(target, index, count, params) _glProgramLocalParametersI4ivNV(target, index, count, params, __FILE__, __LINE__)
#define glProgramLocalParameterI4uiNV(target, index, x, y, z, w) _glProgramLocalParameterI4uiNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramLocalParameterI4uivNV(target, index, params) _glProgramLocalParameterI4uivNV(target, index, params, __FILE__, __LINE__)
#define glProgramLocalParametersI4uivNV(target, index, count, params) _glProgramLocalParametersI4uivNV(target, index, count, params, __FILE__, __LINE__)
#define glProgramEnvParameterI4iNV(target, index, x, y, z, w) _glProgramEnvParameterI4iNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramEnvParameterI4ivNV(target, index, params) _glProgramEnvParameterI4ivNV(target, index, params, __FILE__, __LINE__)
#define glProgramEnvParametersI4ivNV(target, index, count, params) _glProgramEnvParametersI4ivNV(target, index, count, params, __FILE__, __LINE__)
#define glProgramEnvParameterI4uiNV(target, index, x, y, z, w) _glProgramEnvParameterI4uiNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramEnvParameterI4uivNV(target, index, params) _glProgramEnvParameterI4uivNV(target, index, params, __FILE__, __LINE__)
#define glProgramEnvParametersI4uivNV(target, index, count, params) _glProgramEnvParametersI4uivNV(target, index, count, params, __FILE__, __LINE__)
#define glGetProgramLocalParameterIivNV(target, index, params) _glGetProgramLocalParameterIivNV(target, index, params, __FILE__, __LINE__)
#define glGetProgramLocalParameterIuivNV(target, index, params) _glGetProgramLocalParameterIuivNV(target, index, params, __FILE__, __LINE__)
#define glGetProgramEnvParameterIivNV(target, index, params) _glGetProgramEnvParameterIivNV(target, index, params, __FILE__, __LINE__)
#define glGetProgramEnvParameterIuivNV(target, index, params) _glGetProgramEnvParameterIuivNV(target, index, params, __FILE__, __LINE__)
#define glProgramSubroutineParametersuivNV(target, count, params) _glProgramSubroutineParametersuivNV(target, count, params, __FILE__, __LINE__)
#define glGetProgramSubroutineParameteruivNV(target, index, param) _glGetProgramSubroutineParameteruivNV(target, index, param, __FILE__, __LINE__)
#define glVertex2hNV(x, y) _glVertex2hNV(x, y, __FILE__, __LINE__)
#define glVertex2hvNV(v) _glVertex2hvNV(v, __FILE__, __LINE__)
#define glVertex3hNV(x, y, z) _glVertex3hNV(x, y, z, __FILE__, __LINE__)
#define glVertex3hvNV(v) _glVertex3hvNV(v, __FILE__, __LINE__)
#define glVertex4hNV(x, y, z, w) _glVertex4hNV(x, y, z, w, __FILE__, __LINE__)
#define glVertex4hvNV(v) _glVertex4hvNV(v, __FILE__, __LINE__)
#define glNormal3hNV(nx, ny, nz) _glNormal3hNV(nx, ny, nz, __FILE__, __LINE__)
#define glNormal3hvNV(v) _glNormal3hvNV(v, __FILE__, __LINE__)
#define glColor3hNV(red, green, blue) _glColor3hNV(red, green, blue, __FILE__, __LINE__)
#define glColor3hvNV(v) _glColor3hvNV(v, __FILE__, __LINE__)
#define glColor4hNV(red, green, blue, alpha) _glColor4hNV(red, green, blue, alpha, __FILE__, __LINE__)
#define glColor4hvNV(v) _glColor4hvNV(v, __FILE__, __LINE__)
#define glTexCoord1hNV(s) _glTexCoord1hNV(s, __FILE__, __LINE__)
#define glTexCoord1hvNV(v) _glTexCoord1hvNV(v, __FILE__, __LINE__)
#define glTexCoord2hNV(s, t) _glTexCoord2hNV(s, t, __FILE__, __LINE__)
#define glTexCoord2hvNV(v) _glTexCoord2hvNV(v, __FILE__, __LINE__)
#define glTexCoord3hNV(s, t, r) _glTexCoord3hNV(s, t, r, __FILE__, __LINE__)
#define glTexCoord3hvNV(v) _glTexCoord3hvNV(v, __FILE__, __LINE__)
#define glTexCoord4hNV(s, t, r, q) _glTexCoord4hNV(s, t, r, q, __FILE__, __LINE__)
#define glTexCoord4hvNV(v) _glTexCoord4hvNV(v, __FILE__, __LINE__)
#define glMultiTexCoord1hNV(target, s) _glMultiTexCoord1hNV(target, s, __FILE__, __LINE__)
#define glMultiTexCoord1hvNV(target, v) _glMultiTexCoord1hvNV(target, v, __FILE__, __LINE__)
#define glMultiTexCoord2hNV(target, s, t) _glMultiTexCoord2hNV(target, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2hvNV(target, v) _glMultiTexCoord2hvNV(target, v, __FILE__, __LINE__)
#define glMultiTexCoord3hNV(target, s, t, r) _glMultiTexCoord3hNV(target, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3hvNV(target, v) _glMultiTexCoord3hvNV(target, v, __FILE__, __LINE__)
#define glMultiTexCoord4hNV(target, s, t, r, q) _glMultiTexCoord4hNV(target, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4hvNV(target, v) _glMultiTexCoord4hvNV(target, v, __FILE__, __LINE__)
#define glFogCoordhNV(fog) _glFogCoordhNV(fog, __FILE__, __LINE__)
#define glFogCoordhvNV(fog) _glFogCoordhvNV(fog, __FILE__, __LINE__)
#define glSecondaryColor3hNV(red, green, blue) _glSecondaryColor3hNV(red, green, blue, __FILE__, __LINE__)
#define glSecondaryColor3hvNV(v) _glSecondaryColor3hvNV(v, __FILE__, __LINE__)
#define glVertexWeighthNV(weight) _glVertexWeighthNV(weight, __FILE__, __LINE__)
#define glVertexWeighthvNV(weight) _glVertexWeighthvNV(weight, __FILE__, __LINE__)
#define glVertexAttrib1hNV(index, x) _glVertexAttrib1hNV(index, x, __FILE__, __LINE__)
#define glVertexAttrib1hvNV(index, v) _glVertexAttrib1hvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib2hNV(index, x, y) _glVertexAttrib2hNV(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2hvNV(index, v) _glVertexAttrib2hvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib3hNV(index, x, y, z) _glVertexAttrib3hNV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3hvNV(index, v) _glVertexAttrib3hvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib4hNV(index, x, y, z, w) _glVertexAttrib4hNV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4hvNV(index, v) _glVertexAttrib4hvNV(index, v, __FILE__, __LINE__)
#define glVertexAttribs1hvNV(index, n, v) _glVertexAttribs1hvNV(index, n, v, __FILE__, __LINE__)
#define glVertexAttribs2hvNV(index, n, v) _glVertexAttribs2hvNV(index, n, v, __FILE__, __LINE__)
#define glVertexAttribs3hvNV(index, n, v) _glVertexAttribs3hvNV(index, n, v, __FILE__, __LINE__)
#define glVertexAttribs4hvNV(index, n, v) _glVertexAttribs4hvNV(index, n, v, __FILE__, __LINE__)
#define glGetInternalformatSampleivNV(target, internalformat, samples, pname, count, params) _glGetInternalformatSampleivNV(target, internalformat, samples, pname, count, params, __FILE__, __LINE__)
#define glGetMemoryObjectDetachedResourcesuivNV(memory, pname, first, count, params) _glGetMemoryObjectDetachedResourcesuivNV(memory, pname, first, count, params, __FILE__, __LINE__)
#define glResetMemoryObjectParameterNV(memory, pname) _glResetMemoryObjectParameterNV(memory, pname, __FILE__, __LINE__)
#define glTexAttachMemoryNV(target, memory, offset) _glTexAttachMemoryNV(target, memory, offset, __FILE__, __LINE__)
#define glBufferAttachMemoryNV(target, memory, offset) _glBufferAttachMemoryNV(target, memory, offset, __FILE__, __LINE__)
#define glTextureAttachMemoryNV(texture, memory, offset) _glTextureAttachMemoryNV(texture, memory, offset, __FILE__, __LINE__)
#define glNamedBufferAttachMemoryNV(buffer, memory, offset) _glNamedBufferAttachMemoryNV(buffer, memory, offset, __FILE__, __LINE__)
#define glBufferPageCommitmentMemNV(target, offset, size, memory, memOffset, commit) _glBufferPageCommitmentMemNV(target, offset, size, memory, memOffset, commit, __FILE__, __LINE__)
#define glTexPageCommitmentMemNV(target, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit) _glTexPageCommitmentMemNV(target, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit, __FILE__, __LINE__)
#define glNamedBufferPageCommitmentMemNV(buffer, offset, size, memory, memOffset, commit) _glNamedBufferPageCommitmentMemNV(buffer, offset, size, memory, memOffset, commit, __FILE__, __LINE__)
#define glTexturePageCommitmentMemNV(texture, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit) _glTexturePageCommitmentMemNV(texture, layer, level, xoffset, yoffset, zoffset, width, height, depth, memory, offset, commit, __FILE__, __LINE__)
#define glDrawMeshTasksNV(first, count) _glDrawMeshTasksNV(first, count, __FILE__, __LINE__)
#define glDrawMeshTasksIndirectNV(indirect) _glDrawMeshTasksIndirectNV(indirect, __FILE__, __LINE__)
#define glMultiDrawMeshTasksIndirectNV(indirect, drawcount, stride) _glMultiDrawMeshTasksIndirectNV(indirect, drawcount, stride, __FILE__, __LINE__)
#define glMultiDrawMeshTasksIndirectCountNV(indirect, drawcount, maxdrawcount, stride) _glMultiDrawMeshTasksIndirectCountNV(indirect, drawcount, maxdrawcount, stride, __FILE__, __LINE__)
#define glGenOcclusionQueriesNV(n, ids) _glGenOcclusionQueriesNV(n, ids, __FILE__, __LINE__)
#define glDeleteOcclusionQueriesNV(n, ids) _glDeleteOcclusionQueriesNV(n, ids, __FILE__, __LINE__)
#define glIsOcclusionQueryNV(id) _glIsOcclusionQueryNV(id, __FILE__, __LINE__)
#define glBeginOcclusionQueryNV(id) _glBeginOcclusionQueryNV(id, __FILE__, __LINE__)
#define glEndOcclusionQueryNV() _glEndOcclusionQueryNV(__FILE__, __LINE__)
#define glGetOcclusionQueryivNV(id, pname, params) _glGetOcclusionQueryivNV(id, pname, params, __FILE__, __LINE__)
#define glGetOcclusionQueryuivNV(id, pname, params) _glGetOcclusionQueryuivNV(id, pname, params, __FILE__, __LINE__)
#define glProgramBufferParametersfvNV(target, bindingIndex, wordIndex, count, params) _glProgramBufferParametersfvNV(target, bindingIndex, wordIndex, count, params, __FILE__, __LINE__)
#define glProgramBufferParametersIivNV(target, bindingIndex, wordIndex, count, params) _glProgramBufferParametersIivNV(target, bindingIndex, wordIndex, count, params, __FILE__, __LINE__)
#define glProgramBufferParametersIuivNV(target, bindingIndex, wordIndex, count, params) _glProgramBufferParametersIuivNV(target, bindingIndex, wordIndex, count, params, __FILE__, __LINE__)
#define glGenPathsNV(range) _glGenPathsNV(range, __FILE__, __LINE__)
#define glDeletePathsNV(path, range) _glDeletePathsNV(path, range, __FILE__, __LINE__)
#define glIsPathNV(path) _glIsPathNV(path, __FILE__, __LINE__)
#define glPathCommandsNV(path, numCommands, commands, numCoords, coordType, coords) _glPathCommandsNV(path, numCommands, commands, numCoords, coordType, coords, __FILE__, __LINE__)
#define glPathCoordsNV(path, numCoords, coordType, coords) _glPathCoordsNV(path, numCoords, coordType, coords, __FILE__, __LINE__)
#define glPathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords) _glPathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords, __FILE__, __LINE__)
#define glPathSubCoordsNV(path, coordStart, numCoords, coordType, coords) _glPathSubCoordsNV(path, coordStart, numCoords, coordType, coords, __FILE__, __LINE__)
#define glPathStringNV(path, format, length, pathString) _glPathStringNV(path, format, length, pathString, __FILE__, __LINE__)
#define glPathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale) _glPathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale, __FILE__, __LINE__)
#define glPathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale) _glPathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale, __FILE__, __LINE__)
#define glWeightPathsNV(resultPath, numPaths, paths, weights) _glWeightPathsNV(resultPath, numPaths, paths, weights, __FILE__, __LINE__)
#define glCopyPathNV(resultPath, srcPath) _glCopyPathNV(resultPath, srcPath, __FILE__, __LINE__)
#define glInterpolatePathsNV(resultPath, pathA, pathB, weight) _glInterpolatePathsNV(resultPath, pathA, pathB, weight, __FILE__, __LINE__)
#define glTransformPathNV(resultPath, srcPath, transformType, transformValues) _glTransformPathNV(resultPath, srcPath, transformType, transformValues, __FILE__, __LINE__)
#define glPathParameterivNV(path, pname, value) _glPathParameterivNV(path, pname, value, __FILE__, __LINE__)
#define glPathParameteriNV(path, pname, value) _glPathParameteriNV(path, pname, value, __FILE__, __LINE__)
#define glPathParameterfvNV(path, pname, value) _glPathParameterfvNV(path, pname, value, __FILE__, __LINE__)
#define glPathParameterfNV(path, pname, value) _glPathParameterfNV(path, pname, value, __FILE__, __LINE__)
#define glPathDashArrayNV(path, dashCount, dashArray) _glPathDashArrayNV(path, dashCount, dashArray, __FILE__, __LINE__)
#define glPathStencilFuncNV(func, ref, mask) _glPathStencilFuncNV(func, ref, mask, __FILE__, __LINE__)
#define glPathStencilDepthOffsetNV(factor, units) _glPathStencilDepthOffsetNV(factor, units, __FILE__, __LINE__)
#define glStencilFillPathNV(path, fillMode, mask) _glStencilFillPathNV(path, fillMode, mask, __FILE__, __LINE__)
#define glStencilStrokePathNV(path, reference, mask) _glStencilStrokePathNV(path, reference, mask, __FILE__, __LINE__)
#define glStencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues) _glStencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues, __FILE__, __LINE__)
#define glStencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues) _glStencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues, __FILE__, __LINE__)
#define glPathCoverDepthFuncNV(func) _glPathCoverDepthFuncNV(func, __FILE__, __LINE__)
#define glCoverFillPathNV(path, coverMode) _glCoverFillPathNV(path, coverMode, __FILE__, __LINE__)
#define glCoverStrokePathNV(path, coverMode) _glCoverStrokePathNV(path, coverMode, __FILE__, __LINE__)
#define glCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues) _glCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues, __FILE__, __LINE__)
#define glCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues) _glCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues, __FILE__, __LINE__)
#define glGetPathParameterivNV(path, pname, value) _glGetPathParameterivNV(path, pname, value, __FILE__, __LINE__)
#define glGetPathParameterfvNV(path, pname, value) _glGetPathParameterfvNV(path, pname, value, __FILE__, __LINE__)
#define glGetPathCommandsNV(path, commands) _glGetPathCommandsNV(path, commands, __FILE__, __LINE__)
#define glGetPathCoordsNV(path, coords) _glGetPathCoordsNV(path, coords, __FILE__, __LINE__)
#define glGetPathDashArrayNV(path, dashArray) _glGetPathDashArrayNV(path, dashArray, __FILE__, __LINE__)
#define glGetPathMetricsNV(metricQueryMask, numPaths, pathNameType, paths, pathBase, stride, metrics) _glGetPathMetricsNV(metricQueryMask, numPaths, pathNameType, paths, pathBase, stride, metrics, __FILE__, __LINE__)
#define glGetPathMetricRangeNV(metricQueryMask, firstPathName, numPaths, stride, metrics) _glGetPathMetricRangeNV(metricQueryMask, firstPathName, numPaths, stride, metrics, __FILE__, __LINE__)
#define glGetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing) _glGetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing, __FILE__, __LINE__)
#define glIsPointInFillPathNV(path, mask, x, y) _glIsPointInFillPathNV(path, mask, x, y, __FILE__, __LINE__)
#define glIsPointInStrokePathNV(path, x, y) _glIsPointInStrokePathNV(path, x, y, __FILE__, __LINE__)
#define glGetPathLengthNV(path, startSegment, numSegments) _glGetPathLengthNV(path, startSegment, numSegments, __FILE__, __LINE__)
#define glPointAlongPathNV(path, startSegment, numSegments, distance, x, y, tangentX, tangentY) _glPointAlongPathNV(path, startSegment, numSegments, distance, x, y, tangentX, tangentY, __FILE__, __LINE__)
#define glMatrixLoad3x2fNV(matrixMode, m) _glMatrixLoad3x2fNV(matrixMode, m, __FILE__, __LINE__)
#define glMatrixLoad3x3fNV(matrixMode, m) _glMatrixLoad3x3fNV(matrixMode, m, __FILE__, __LINE__)
#define glMatrixLoadTranspose3x3fNV(matrixMode, m) _glMatrixLoadTranspose3x3fNV(matrixMode, m, __FILE__, __LINE__)
#define glMatrixMult3x2fNV(matrixMode, m) _glMatrixMult3x2fNV(matrixMode, m, __FILE__, __LINE__)
#define glMatrixMult3x3fNV(matrixMode, m) _glMatrixMult3x3fNV(matrixMode, m, __FILE__, __LINE__)
#define glMatrixMultTranspose3x3fNV(matrixMode, m) _glMatrixMultTranspose3x3fNV(matrixMode, m, __FILE__, __LINE__)
#define glStencilThenCoverFillPathNV(path, fillMode, mask, coverMode) _glStencilThenCoverFillPathNV(path, fillMode, mask, coverMode, __FILE__, __LINE__)
#define glStencilThenCoverStrokePathNV(path, reference, mask, coverMode) _glStencilThenCoverStrokePathNV(path, reference, mask, coverMode, __FILE__, __LINE__)
#define glStencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues) _glStencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues, __FILE__, __LINE__)
#define glStencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues) _glStencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues, __FILE__, __LINE__)
#define glPathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount) _glPathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount, __FILE__, __LINE__)
#define glPathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale) _glPathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale, __FILE__, __LINE__)
#define glPathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale) _glPathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale, __FILE__, __LINE__)
#define glProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs) _glProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs, __FILE__, __LINE__)
#define glGetProgramResourcefvNV(program, programInterface, index, propCount, props, count, length, params) _glGetProgramResourcefvNV(program, programInterface, index, propCount, props, count, length, params, __FILE__, __LINE__)
#define glPathColorGenNV(color, genMode, colorFormat, coeffs) _glPathColorGenNV(color, genMode, colorFormat, coeffs, __FILE__, __LINE__)
#define glPathTexGenNV(texCoordSet, genMode, components, coeffs) _glPathTexGenNV(texCoordSet, genMode, components, coeffs, __FILE__, __LINE__)
#define glPathFogGenNV(genMode) _glPathFogGenNV(genMode, __FILE__, __LINE__)
#define glGetPathColorGenivNV(color, pname, value) _glGetPathColorGenivNV(color, pname, value, __FILE__, __LINE__)
#define glGetPathColorGenfvNV(color, pname, value) _glGetPathColorGenfvNV(color, pname, value, __FILE__, __LINE__)
#define glGetPathTexGenivNV(texCoordSet, pname, value) _glGetPathTexGenivNV(texCoordSet, pname, value, __FILE__, __LINE__)
#define glGetPathTexGenfvNV(texCoordSet, pname, value) _glGetPathTexGenfvNV(texCoordSet, pname, value, __FILE__, __LINE__)
#define glPixelDataRangeNV(target, length, pointer) _glPixelDataRangeNV(target, length, pointer, __FILE__, __LINE__)
#define glFlushPixelDataRangeNV(target) _glFlushPixelDataRangeNV(target, __FILE__, __LINE__)
#define glPointParameteriNV(pname, param) _glPointParameteriNV(pname, param, __FILE__, __LINE__)
#define glPointParameterivNV(pname, params) _glPointParameterivNV(pname, params, __FILE__, __LINE__)
#define glPresentFrameKeyedNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, key0, target1, fill1, key1) _glPresentFrameKeyedNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, key0, target1, fill1, key1, __FILE__, __LINE__)
#define glPresentFrameDualFillNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, target1, fill1, target2, fill2, target3, fill3) _glPresentFrameDualFillNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, target1, fill1, target2, fill2, target3, fill3, __FILE__, __LINE__)
#define glGetVideoivNV(video_slot, pname, params) _glGetVideoivNV(video_slot, pname, params, __FILE__, __LINE__)
#define glGetVideouivNV(video_slot, pname, params) _glGetVideouivNV(video_slot, pname, params, __FILE__, __LINE__)
#define glGetVideoi64vNV(video_slot, pname, params) _glGetVideoi64vNV(video_slot, pname, params, __FILE__, __LINE__)
#define glGetVideoui64vNV(video_slot, pname, params) _glGetVideoui64vNV(video_slot, pname, params, __FILE__, __LINE__)
#define glPrimitiveRestartNV() _glPrimitiveRestartNV(__FILE__, __LINE__)
#define glPrimitiveRestartIndexNV(index) _glPrimitiveRestartIndexNV(index, __FILE__, __LINE__)
#define glQueryResourceNV(queryType, tagId, count, buffer) _glQueryResourceNV(queryType, tagId, count, buffer, __FILE__, __LINE__)
#define glGenQueryResourceTagNV(n, tagIds) _glGenQueryResourceTagNV(n, tagIds, __FILE__, __LINE__)
#define glDeleteQueryResourceTagNV(n, tagIds) _glDeleteQueryResourceTagNV(n, tagIds, __FILE__, __LINE__)
#define glQueryResourceTagNV(tagId, tagString) _glQueryResourceTagNV(tagId, tagString, __FILE__, __LINE__)
#define glCombinerParameterfvNV(pname, params) _glCombinerParameterfvNV(pname, params, __FILE__, __LINE__)
#define glCombinerParameterfNV(pname, param) _glCombinerParameterfNV(pname, param, __FILE__, __LINE__)
#define glCombinerParameterivNV(pname, params) _glCombinerParameterivNV(pname, params, __FILE__, __LINE__)
#define glCombinerParameteriNV(pname, param) _glCombinerParameteriNV(pname, param, __FILE__, __LINE__)
#define glCombinerInputNV(stage, portion, variable, input, mapping, componentUsage) _glCombinerInputNV(stage, portion, variable, input, mapping, componentUsage, __FILE__, __LINE__)
#define glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum) _glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum, __FILE__, __LINE__)
#define glFinalCombinerInputNV(variable, input, mapping, componentUsage) _glFinalCombinerInputNV(variable, input, mapping, componentUsage, __FILE__, __LINE__)
#define glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params) _glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params, __FILE__, __LINE__)
#define glGetCombinerInputParameterivNV(stage, portion, variable, pname, params) _glGetCombinerInputParameterivNV(stage, portion, variable, pname, params, __FILE__, __LINE__)
#define glGetCombinerOutputParameterfvNV(stage, portion, pname, params) _glGetCombinerOutputParameterfvNV(stage, portion, pname, params, __FILE__, __LINE__)
#define glGetCombinerOutputParameterivNV(stage, portion, pname, params) _glGetCombinerOutputParameterivNV(stage, portion, pname, params, __FILE__, __LINE__)
#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) _glGetFinalCombinerInputParameterfvNV(variable, pname, params, __FILE__, __LINE__)
#define glGetFinalCombinerInputParameterivNV(variable, pname, params) _glGetFinalCombinerInputParameterivNV(variable, pname, params, __FILE__, __LINE__)
#define glCombinerStageParameterfvNV(stage, pname, params) _glCombinerStageParameterfvNV(stage, pname, params, __FILE__, __LINE__)
#define glGetCombinerStageParameterfvNV(stage, pname, params) _glGetCombinerStageParameterfvNV(stage, pname, params, __FILE__, __LINE__)
#define glFramebufferSampleLocationsfvNV(target, start, count, v) _glFramebufferSampleLocationsfvNV(target, start, count, v, __FILE__, __LINE__)
#define glNamedFramebufferSampleLocationsfvNV(framebuffer, start, count, v) _glNamedFramebufferSampleLocationsfvNV(framebuffer, start, count, v, __FILE__, __LINE__)
#define glResolveDepthValuesNV() _glResolveDepthValuesNV(__FILE__, __LINE__)
#define glScissorExclusiveNV(x, y, width, height) _glScissorExclusiveNV(x, y, width, height, __FILE__, __LINE__)
#define glScissorExclusiveArrayvNV(first, count, v) _glScissorExclusiveArrayvNV(first, count, v, __FILE__, __LINE__)
#define glMakeBufferResidentNV(target, access) _glMakeBufferResidentNV(target, access, __FILE__, __LINE__)
#define glMakeBufferNonResidentNV(target) _glMakeBufferNonResidentNV(target, __FILE__, __LINE__)
#define glIsBufferResidentNV(target) _glIsBufferResidentNV(target, __FILE__, __LINE__)
#define glMakeNamedBufferResidentNV(buffer, access) _glMakeNamedBufferResidentNV(buffer, access, __FILE__, __LINE__)
#define glMakeNamedBufferNonResidentNV(buffer) _glMakeNamedBufferNonResidentNV(buffer, __FILE__, __LINE__)
#define glIsNamedBufferResidentNV(buffer) _glIsNamedBufferResidentNV(buffer, __FILE__, __LINE__)
#define glGetBufferParameterui64vNV(target, pname, params) _glGetBufferParameterui64vNV(target, pname, params, __FILE__, __LINE__)
#define glGetNamedBufferParameterui64vNV(buffer, pname, params) _glGetNamedBufferParameterui64vNV(buffer, pname, params, __FILE__, __LINE__)
#define glGetIntegerui64vNV(value, result) _glGetIntegerui64vNV(value, result, __FILE__, __LINE__)
#define glUniformui64NV(location, value) _glUniformui64NV(location, value, __FILE__, __LINE__)
#define glUniformui64vNV(location, count, value) _glUniformui64vNV(location, count, value, __FILE__, __LINE__)
#define glProgramUniformui64NV(program, location, value) _glProgramUniformui64NV(program, location, value, __FILE__, __LINE__)
#define glProgramUniformui64vNV(program, location, count, value) _glProgramUniformui64vNV(program, location, count, value, __FILE__, __LINE__)
#define glBindShadingRateImageNV(texture) _glBindShadingRateImageNV(texture, __FILE__, __LINE__)
#define glGetShadingRateImagePaletteNV(viewport, entry, rate) _glGetShadingRateImagePaletteNV(viewport, entry, rate, __FILE__, __LINE__)
#define glGetShadingRateSampleLocationivNV(rate, samples, index, location) _glGetShadingRateSampleLocationivNV(rate, samples, index, location, __FILE__, __LINE__)
#define glShadingRateImageBarrierNV(synchronize) _glShadingRateImageBarrierNV(synchronize, __FILE__, __LINE__)
#define glShadingRateImagePaletteNV(viewport, first, count, rates) _glShadingRateImagePaletteNV(viewport, first, count, rates, __FILE__, __LINE__)
#define glShadingRateSampleOrderNV(order) _glShadingRateSampleOrderNV(order, __FILE__, __LINE__)
#define glShadingRateSampleOrderCustomNV(rate, samples, locations) _glShadingRateSampleOrderCustomNV(rate, samples, locations, __FILE__, __LINE__)
#define glTextureBarrierNV() _glTextureBarrierNV(__FILE__, __LINE__)
#define glTexImage2DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations) _glTexImage2DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations, __FILE__, __LINE__)
#define glTexImage3DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations) _glTexImage3DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations, __FILE__, __LINE__)
#define glTextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations) _glTextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations, __FILE__, __LINE__)
#define glTextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations) _glTextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations, __FILE__, __LINE__)
#define glTextureImage2DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations) _glTextureImage2DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations, __FILE__, __LINE__)
#define glTextureImage3DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations) _glTextureImage3DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations, __FILE__, __LINE__)
#define glCreateSemaphoresNV(n, semaphores) _glCreateSemaphoresNV(n, semaphores, __FILE__, __LINE__)
#define glSemaphoreParameterivNV(semaphore, pname, params) _glSemaphoreParameterivNV(semaphore, pname, params, __FILE__, __LINE__)
#define glGetSemaphoreParameterivNV(semaphore, pname, params) _glGetSemaphoreParameterivNV(semaphore, pname, params, __FILE__, __LINE__)
#define glBeginTransformFeedbackNV(primitiveMode) _glBeginTransformFeedbackNV(primitiveMode, __FILE__, __LINE__)
#define glEndTransformFeedbackNV() _glEndTransformFeedbackNV(__FILE__, __LINE__)
#define glTransformFeedbackAttribsNV(count, attribs, bufferMode) _glTransformFeedbackAttribsNV(count, attribs, bufferMode, __FILE__, __LINE__)
#define glBindBufferRangeNV(target, index, buffer, offset, size) _glBindBufferRangeNV(target, index, buffer, offset, size, __FILE__, __LINE__)
#define glBindBufferOffsetNV(target, index, buffer, offset) _glBindBufferOffsetNV(target, index, buffer, offset, __FILE__, __LINE__)
#define glBindBufferBaseNV(target, index, buffer) _glBindBufferBaseNV(target, index, buffer, __FILE__, __LINE__)
#define glTransformFeedbackVaryingsNV(program, count, locations, bufferMode) _glTransformFeedbackVaryingsNV(program, count, locations, bufferMode, __FILE__, __LINE__)
#define glActiveVaryingNV(program, name) _glActiveVaryingNV(program, name, __FILE__, __LINE__)
#define glGetVaryingLocationNV(program, name) _glGetVaryingLocationNV(program, name, __FILE__, __LINE__)
#define glGetActiveVaryingNV(program, index, bufSize, length, size, type, name) _glGetActiveVaryingNV(program, index, bufSize, length, size, type, name, __FILE__, __LINE__)
#define glGetTransformFeedbackVaryingNV(program, index, location) _glGetTransformFeedbackVaryingNV(program, index, location, __FILE__, __LINE__)
#define glTransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode) _glTransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode, __FILE__, __LINE__)
#define glBindTransformFeedbackNV(target, id) _glBindTransformFeedbackNV(target, id, __FILE__, __LINE__)
#define glDeleteTransformFeedbacksNV(n, ids) _glDeleteTransformFeedbacksNV(n, ids, __FILE__, __LINE__)
#define glGenTransformFeedbacksNV(n, ids) _glGenTransformFeedbacksNV(n, ids, __FILE__, __LINE__)
#define glIsTransformFeedbackNV(id) _glIsTransformFeedbackNV(id, __FILE__, __LINE__)
#define glPauseTransformFeedbackNV() _glPauseTransformFeedbackNV(__FILE__, __LINE__)
#define glResumeTransformFeedbackNV() _glResumeTransformFeedbackNV(__FILE__, __LINE__)
#define glDrawTransformFeedbackNV(mode, id) _glDrawTransformFeedbackNV(mode, id, __FILE__, __LINE__)
#define glVDPAUInitNV(vdpDevice, getProcAddress) _glVDPAUInitNV(vdpDevice, getProcAddress, __FILE__, __LINE__)
#define glVDPAUFiniNV() _glVDPAUFiniNV(__FILE__, __LINE__)
#define glVDPAURegisterVideoSurfaceNV(vdpSurface, target, numTextureNames, textureNames) _glVDPAURegisterVideoSurfaceNV(vdpSurface, target, numTextureNames, textureNames, __FILE__, __LINE__)
#define glVDPAURegisterOutputSurfaceNV(vdpSurface, target, numTextureNames, textureNames) _glVDPAURegisterOutputSurfaceNV(vdpSurface, target, numTextureNames, textureNames, __FILE__, __LINE__)
#define glVDPAUIsSurfaceNV(surface) _glVDPAUIsSurfaceNV(surface, __FILE__, __LINE__)
#define glVDPAUUnregisterSurfaceNV(surface) _glVDPAUUnregisterSurfaceNV(surface, __FILE__, __LINE__)
#define glVDPAUGetSurfaceivNV(surface, pname, count, length, values) _glVDPAUGetSurfaceivNV(surface, pname, count, length, values, __FILE__, __LINE__)
#define glVDPAUSurfaceAccessNV(surface, access) _glVDPAUSurfaceAccessNV(surface, access, __FILE__, __LINE__)
#define glVDPAUMapSurfacesNV(numSurfaces, surfaces) _glVDPAUMapSurfacesNV(numSurfaces, surfaces, __FILE__, __LINE__)
#define glVDPAUUnmapSurfacesNV(numSurface, surfaces) _glVDPAUUnmapSurfacesNV(numSurface, surfaces, __FILE__, __LINE__)
#define glVDPAURegisterVideoSurfaceWithPictureStructureNV(vdpSurface, target, numTextureNames, textureNames, isFrameStructure) _glVDPAURegisterVideoSurfaceWithPictureStructureNV(vdpSurface, target, numTextureNames, textureNames, isFrameStructure, __FILE__, __LINE__)
#define glFlushVertexArrayRangeNV() _glFlushVertexArrayRangeNV(__FILE__, __LINE__)
#define glVertexArrayRangeNV(length, pointer) _glVertexArrayRangeNV(length, pointer, __FILE__, __LINE__)
#define glVertexAttribL1i64NV(index, x) _glVertexAttribL1i64NV(index, x, __FILE__, __LINE__)
#define glVertexAttribL2i64NV(index, x, y) _glVertexAttribL2i64NV(index, x, y, __FILE__, __LINE__)
#define glVertexAttribL3i64NV(index, x, y, z) _glVertexAttribL3i64NV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribL4i64NV(index, x, y, z, w) _glVertexAttribL4i64NV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribL1i64vNV(index, v) _glVertexAttribL1i64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL2i64vNV(index, v) _glVertexAttribL2i64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL3i64vNV(index, v) _glVertexAttribL3i64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL4i64vNV(index, v) _glVertexAttribL4i64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL1ui64NV(index, x) _glVertexAttribL1ui64NV(index, x, __FILE__, __LINE__)
#define glVertexAttribL2ui64NV(index, x, y) _glVertexAttribL2ui64NV(index, x, y, __FILE__, __LINE__)
#define glVertexAttribL3ui64NV(index, x, y, z) _glVertexAttribL3ui64NV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribL4ui64NV(index, x, y, z, w) _glVertexAttribL4ui64NV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribL1ui64vNV(index, v) _glVertexAttribL1ui64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL2ui64vNV(index, v) _glVertexAttribL2ui64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL3ui64vNV(index, v) _glVertexAttribL3ui64vNV(index, v, __FILE__, __LINE__)
#define glVertexAttribL4ui64vNV(index, v) _glVertexAttribL4ui64vNV(index, v, __FILE__, __LINE__)
#define glGetVertexAttribLi64vNV(index, pname, params) _glGetVertexAttribLi64vNV(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribLui64vNV(index, pname, params) _glGetVertexAttribLui64vNV(index, pname, params, __FILE__, __LINE__)
#define glVertexAttribLFormatNV(index, size, type, stride) _glVertexAttribLFormatNV(index, size, type, stride, __FILE__, __LINE__)
#define glBufferAddressRangeNV(pname, index, address, length) _glBufferAddressRangeNV(pname, index, address, length, __FILE__, __LINE__)
#define glVertexFormatNV(size, type, stride) _glVertexFormatNV(size, type, stride, __FILE__, __LINE__)
#define glNormalFormatNV(type, stride) _glNormalFormatNV(type, stride, __FILE__, __LINE__)
#define glColorFormatNV(size, type, stride) _glColorFormatNV(size, type, stride, __FILE__, __LINE__)
#define glIndexFormatNV(type, stride) _glIndexFormatNV(type, stride, __FILE__, __LINE__)
#define glTexCoordFormatNV(size, type, stride) _glTexCoordFormatNV(size, type, stride, __FILE__, __LINE__)
#define glEdgeFlagFormatNV(stride) _glEdgeFlagFormatNV(stride, __FILE__, __LINE__)
#define glSecondaryColorFormatNV(size, type, stride) _glSecondaryColorFormatNV(size, type, stride, __FILE__, __LINE__)
#define glFogCoordFormatNV(type, stride) _glFogCoordFormatNV(type, stride, __FILE__, __LINE__)
#define glVertexAttribFormatNV(index, size, type, normalized, stride) _glVertexAttribFormatNV(index, size, type, normalized, stride, __FILE__, __LINE__)
#define glVertexAttribIFormatNV(index, size, type, stride) _glVertexAttribIFormatNV(index, size, type, stride, __FILE__, __LINE__)
#define glGetIntegerui64i_vNV(value, index, result) _glGetIntegerui64i_vNV(value, index, result, __FILE__, __LINE__)
#define glAreProgramsResidentNV(n, programs, residences) _glAreProgramsResidentNV(n, programs, residences, __FILE__, __LINE__)
#define glBindProgramNV(target, id) _glBindProgramNV(target, id, __FILE__, __LINE__)
#define glDeleteProgramsNV(n, programs) _glDeleteProgramsNV(n, programs, __FILE__, __LINE__)
#define glExecuteProgramNV(target, id, params) _glExecuteProgramNV(target, id, params, __FILE__, __LINE__)
#define glGenProgramsNV(n, programs) _glGenProgramsNV(n, programs, __FILE__, __LINE__)
#define glGetProgramParameterdvNV(target, index, pname, params) _glGetProgramParameterdvNV(target, index, pname, params, __FILE__, __LINE__)
#define glGetProgramParameterfvNV(target, index, pname, params) _glGetProgramParameterfvNV(target, index, pname, params, __FILE__, __LINE__)
#define glGetProgramivNV(id, pname, params) _glGetProgramivNV(id, pname, params, __FILE__, __LINE__)
#define glGetProgramStringNV(id, pname, program) _glGetProgramStringNV(id, pname, program, __FILE__, __LINE__)
#define glGetTrackMatrixivNV(target, address, pname, params) _glGetTrackMatrixivNV(target, address, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribdvNV(index, pname, params) _glGetVertexAttribdvNV(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribfvNV(index, pname, params) _glGetVertexAttribfvNV(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribivNV(index, pname, params) _glGetVertexAttribivNV(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribPointervNV(index, pname, pointer) _glGetVertexAttribPointervNV(index, pname, pointer, __FILE__, __LINE__)
#define glIsProgramNV(id) _glIsProgramNV(id, __FILE__, __LINE__)
#define glLoadProgramNV(target, id, len, program) _glLoadProgramNV(target, id, len, program, __FILE__, __LINE__)
#define glProgramParameter4dNV(target, index, x, y, z, w) _glProgramParameter4dNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramParameter4dvNV(target, index, v) _glProgramParameter4dvNV(target, index, v, __FILE__, __LINE__)
#define glProgramParameter4fNV(target, index, x, y, z, w) _glProgramParameter4fNV(target, index, x, y, z, w, __FILE__, __LINE__)
#define glProgramParameter4fvNV(target, index, v) _glProgramParameter4fvNV(target, index, v, __FILE__, __LINE__)
#define glProgramParameters4dvNV(target, index, count, v) _glProgramParameters4dvNV(target, index, count, v, __FILE__, __LINE__)
#define glProgramParameters4fvNV(target, index, count, v) _glProgramParameters4fvNV(target, index, count, v, __FILE__, __LINE__)
#define glRequestResidentProgramsNV(n, programs) _glRequestResidentProgramsNV(n, programs, __FILE__, __LINE__)
#define glTrackMatrixNV(target, address, matrix, transform) _glTrackMatrixNV(target, address, matrix, transform, __FILE__, __LINE__)
#define glVertexAttribPointerNV(index, fsize, type, stride, pointer) _glVertexAttribPointerNV(index, fsize, type, stride, pointer, __FILE__, __LINE__)
#define glVertexAttrib1dNV(index, x) _glVertexAttrib1dNV(index, x, __FILE__, __LINE__)
#define glVertexAttrib1dvNV(index, v) _glVertexAttrib1dvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib1fNV(index, x) _glVertexAttrib1fNV(index, x, __FILE__, __LINE__)
#define glVertexAttrib1fvNV(index, v) _glVertexAttrib1fvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib1sNV(index, x) _glVertexAttrib1sNV(index, x, __FILE__, __LINE__)
#define glVertexAttrib1svNV(index, v) _glVertexAttrib1svNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib2dNV(index, x, y) _glVertexAttrib2dNV(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2dvNV(index, v) _glVertexAttrib2dvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib2fNV(index, x, y) _glVertexAttrib2fNV(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2fvNV(index, v) _glVertexAttrib2fvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib2sNV(index, x, y) _glVertexAttrib2sNV(index, x, y, __FILE__, __LINE__)
#define glVertexAttrib2svNV(index, v) _glVertexAttrib2svNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib3dNV(index, x, y, z) _glVertexAttrib3dNV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3dvNV(index, v) _glVertexAttrib3dvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib3fNV(index, x, y, z) _glVertexAttrib3fNV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3fvNV(index, v) _glVertexAttrib3fvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib3sNV(index, x, y, z) _glVertexAttrib3sNV(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttrib3svNV(index, v) _glVertexAttrib3svNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib4dNV(index, x, y, z, w) _glVertexAttrib4dNV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4dvNV(index, v) _glVertexAttrib4dvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib4fNV(index, x, y, z, w) _glVertexAttrib4fNV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4fvNV(index, v) _glVertexAttrib4fvNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib4sNV(index, x, y, z, w) _glVertexAttrib4sNV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4svNV(index, v) _glVertexAttrib4svNV(index, v, __FILE__, __LINE__)
#define glVertexAttrib4ubNV(index, x, y, z, w) _glVertexAttrib4ubNV(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttrib4ubvNV(index, v) _glVertexAttrib4ubvNV(index, v, __FILE__, __LINE__)
#define glVertexAttribs1dvNV(index, count, v) _glVertexAttribs1dvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs1fvNV(index, count, v) _glVertexAttribs1fvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs1svNV(index, count, v) _glVertexAttribs1svNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs2dvNV(index, count, v) _glVertexAttribs2dvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs2fvNV(index, count, v) _glVertexAttribs2fvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs2svNV(index, count, v) _glVertexAttribs2svNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs3dvNV(index, count, v) _glVertexAttribs3dvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs3fvNV(index, count, v) _glVertexAttribs3fvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs3svNV(index, count, v) _glVertexAttribs3svNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs4dvNV(index, count, v) _glVertexAttribs4dvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs4fvNV(index, count, v) _glVertexAttribs4fvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs4svNV(index, count, v) _glVertexAttribs4svNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribs4ubvNV(index, count, v) _glVertexAttribs4ubvNV(index, count, v, __FILE__, __LINE__)
#define glVertexAttribI1iEXT(index, x) _glVertexAttribI1iEXT(index, x, __FILE__, __LINE__)
#define glVertexAttribI2iEXT(index, x, y) _glVertexAttribI2iEXT(index, x, y, __FILE__, __LINE__)
#define glVertexAttribI3iEXT(index, x, y, z) _glVertexAttribI3iEXT(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribI4iEXT(index, x, y, z, w) _glVertexAttribI4iEXT(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribI1uiEXT(index, x) _glVertexAttribI1uiEXT(index, x, __FILE__, __LINE__)
#define glVertexAttribI2uiEXT(index, x, y) _glVertexAttribI2uiEXT(index, x, y, __FILE__, __LINE__)
#define glVertexAttribI3uiEXT(index, x, y, z) _glVertexAttribI3uiEXT(index, x, y, z, __FILE__, __LINE__)
#define glVertexAttribI4uiEXT(index, x, y, z, w) _glVertexAttribI4uiEXT(index, x, y, z, w, __FILE__, __LINE__)
#define glVertexAttribI1ivEXT(index, v) _glVertexAttribI1ivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI2ivEXT(index, v) _glVertexAttribI2ivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI3ivEXT(index, v) _glVertexAttribI3ivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4ivEXT(index, v) _glVertexAttribI4ivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI1uivEXT(index, v) _glVertexAttribI1uivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI2uivEXT(index, v) _glVertexAttribI2uivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI3uivEXT(index, v) _glVertexAttribI3uivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4uivEXT(index, v) _glVertexAttribI4uivEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4bvEXT(index, v) _glVertexAttribI4bvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4svEXT(index, v) _glVertexAttribI4svEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4ubvEXT(index, v) _glVertexAttribI4ubvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribI4usvEXT(index, v) _glVertexAttribI4usvEXT(index, v, __FILE__, __LINE__)
#define glVertexAttribIPointerEXT(index, size, type, stride, pointer) _glVertexAttribIPointerEXT(index, size, type, stride, pointer, __FILE__, __LINE__)
#define glGetVertexAttribIivEXT(index, pname, params) _glGetVertexAttribIivEXT(index, pname, params, __FILE__, __LINE__)
#define glGetVertexAttribIuivEXT(index, pname, params) _glGetVertexAttribIuivEXT(index, pname, params, __FILE__, __LINE__)
#define glBeginVideoCaptureNV(video_capture_slot) _glBeginVideoCaptureNV(video_capture_slot, __FILE__, __LINE__)
#define glBindVideoCaptureStreamBufferNV(video_capture_slot, stream, frame_region, offset) _glBindVideoCaptureStreamBufferNV(video_capture_slot, stream, frame_region, offset, __FILE__, __LINE__)
#define glBindVideoCaptureStreamTextureNV(video_capture_slot, stream, frame_region, target, texture) _glBindVideoCaptureStreamTextureNV(video_capture_slot, stream, frame_region, target, texture, __FILE__, __LINE__)
#define glEndVideoCaptureNV(video_capture_slot) _glEndVideoCaptureNV(video_capture_slot, __FILE__, __LINE__)
#define glGetVideoCaptureivNV(video_capture_slot, pname, params) _glGetVideoCaptureivNV(video_capture_slot, pname, params, __FILE__, __LINE__)
#define glGetVideoCaptureStreamivNV(video_capture_slot, stream, pname, params) _glGetVideoCaptureStreamivNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glGetVideoCaptureStreamfvNV(video_capture_slot, stream, pname, params) _glGetVideoCaptureStreamfvNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glGetVideoCaptureStreamdvNV(video_capture_slot, stream, pname, params) _glGetVideoCaptureStreamdvNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glVideoCaptureNV(video_capture_slot, sequence_num, capture_time) _glVideoCaptureNV(video_capture_slot, sequence_num, capture_time, __FILE__, __LINE__)
#define glVideoCaptureStreamParameterivNV(video_capture_slot, stream, pname, params) _glVideoCaptureStreamParameterivNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glVideoCaptureStreamParameterfvNV(video_capture_slot, stream, pname, params) _glVideoCaptureStreamParameterfvNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glVideoCaptureStreamParameterdvNV(video_capture_slot, stream, pname, params) _glVideoCaptureStreamParameterdvNV(video_capture_slot, stream, pname, params, __FILE__, __LINE__)
#define glViewportSwizzleNV(index, swizzlex, swizzley, swizzlez, swizzlew) _glViewportSwizzleNV(index, swizzlex, swizzley, swizzlez, swizzlew, __FILE__, __LINE__)
#define glMultiTexCoord1bOES(texture, s) _glMultiTexCoord1bOES(texture, s, __FILE__, __LINE__)
#define glMultiTexCoord1bvOES(texture, coords) _glMultiTexCoord1bvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord2bOES(texture, s, t) _glMultiTexCoord2bOES(texture, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2bvOES(texture, coords) _glMultiTexCoord2bvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord3bOES(texture, s, t, r) _glMultiTexCoord3bOES(texture, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3bvOES(texture, coords) _glMultiTexCoord3bvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord4bOES(texture, s, t, r, q) _glMultiTexCoord4bOES(texture, s, t, r, q, __FILE__, __LINE__)
#define glMultiTexCoord4bvOES(texture, coords) _glMultiTexCoord4bvOES(texture, coords, __FILE__, __LINE__)
#define glTexCoord1bOES(s) _glTexCoord1bOES(s, __FILE__, __LINE__)
#define glTexCoord1bvOES(coords) _glTexCoord1bvOES(coords, __FILE__, __LINE__)
#define glTexCoord2bOES(s, t) _glTexCoord2bOES(s, t, __FILE__, __LINE__)
#define glTexCoord2bvOES(coords) _glTexCoord2bvOES(coords, __FILE__, __LINE__)
#define glTexCoord3bOES(s, t, r) _glTexCoord3bOES(s, t, r, __FILE__, __LINE__)
#define glTexCoord3bvOES(coords) _glTexCoord3bvOES(coords, __FILE__, __LINE__)
#define glTexCoord4bOES(s, t, r, q) _glTexCoord4bOES(s, t, r, q, __FILE__, __LINE__)
#define glTexCoord4bvOES(coords) _glTexCoord4bvOES(coords, __FILE__, __LINE__)
#define glVertex2bOES(x, y) _glVertex2bOES(x, y, __FILE__, __LINE__)
#define glVertex2bvOES(coords) _glVertex2bvOES(coords, __FILE__, __LINE__)
#define glVertex3bOES(x, y, z) _glVertex3bOES(x, y, z, __FILE__, __LINE__)
#define glVertex3bvOES(coords) _glVertex3bvOES(coords, __FILE__, __LINE__)
#define glVertex4bOES(x, y, z, w) _glVertex4bOES(x, y, z, w, __FILE__, __LINE__)
#define glVertex4bvOES(coords) _glVertex4bvOES(coords, __FILE__, __LINE__)
#define glAlphaFuncxOES(func, ref) _glAlphaFuncxOES(func, ref, __FILE__, __LINE__)
#define glClearColorxOES(red, green, blue, alpha) _glClearColorxOES(red, green, blue, alpha, __FILE__, __LINE__)
#define glClearDepthxOES(depth) _glClearDepthxOES(depth, __FILE__, __LINE__)
#define glClipPlanexOES(plane, equation) _glClipPlanexOES(plane, equation, __FILE__, __LINE__)
#define glColor4xOES(red, green, blue, alpha) _glColor4xOES(red, green, blue, alpha, __FILE__, __LINE__)
#define glDepthRangexOES(n, f) _glDepthRangexOES(n, f, __FILE__, __LINE__)
#define glFogxOES(pname, param) _glFogxOES(pname, param, __FILE__, __LINE__)
#define glFogxvOES(pname, param) _glFogxvOES(pname, param, __FILE__, __LINE__)
#define glFrustumxOES(l, r, b, t, n, f) _glFrustumxOES(l, r, b, t, n, f, __FILE__, __LINE__)
#define glGetClipPlanexOES(plane, equation) _glGetClipPlanexOES(plane, equation, __FILE__, __LINE__)
#define glGetFixedvOES(pname, params) _glGetFixedvOES(pname, params, __FILE__, __LINE__)
#define glGetTexEnvxvOES(target, pname, params) _glGetTexEnvxvOES(target, pname, params, __FILE__, __LINE__)
#define glGetTexParameterxvOES(target, pname, params) _glGetTexParameterxvOES(target, pname, params, __FILE__, __LINE__)
#define glLightModelxOES(pname, param) _glLightModelxOES(pname, param, __FILE__, __LINE__)
#define glLightModelxvOES(pname, param) _glLightModelxvOES(pname, param, __FILE__, __LINE__)
#define glLightxOES(light, pname, param) _glLightxOES(light, pname, param, __FILE__, __LINE__)
#define glLightxvOES(light, pname, params) _glLightxvOES(light, pname, params, __FILE__, __LINE__)
#define glLineWidthxOES(width) _glLineWidthxOES(width, __FILE__, __LINE__)
#define glLoadMatrixxOES(m) _glLoadMatrixxOES(m, __FILE__, __LINE__)
#define glMaterialxOES(face, pname, param) _glMaterialxOES(face, pname, param, __FILE__, __LINE__)
#define glMaterialxvOES(face, pname, param) _glMaterialxvOES(face, pname, param, __FILE__, __LINE__)
#define glMultMatrixxOES(m) _glMultMatrixxOES(m, __FILE__, __LINE__)
#define glMultiTexCoord4xOES(texture, s, t, r, q) _glMultiTexCoord4xOES(texture, s, t, r, q, __FILE__, __LINE__)
#define glNormal3xOES(nx, ny, nz) _glNormal3xOES(nx, ny, nz, __FILE__, __LINE__)
#define glOrthoxOES(l, r, b, t, n, f) _glOrthoxOES(l, r, b, t, n, f, __FILE__, __LINE__)
#define glPointParameterxvOES(pname, params) _glPointParameterxvOES(pname, params, __FILE__, __LINE__)
#define glPointSizexOES(size) _glPointSizexOES(size, __FILE__, __LINE__)
#define glPolygonOffsetxOES(factor, units) _glPolygonOffsetxOES(factor, units, __FILE__, __LINE__)
#define glRotatexOES(angle, x, y, z) _glRotatexOES(angle, x, y, z, __FILE__, __LINE__)
#define glScalexOES(x, y, z) _glScalexOES(x, y, z, __FILE__, __LINE__)
#define glTexEnvxOES(target, pname, param) _glTexEnvxOES(target, pname, param, __FILE__, __LINE__)
#define glTexEnvxvOES(target, pname, params) _glTexEnvxvOES(target, pname, params, __FILE__, __LINE__)
#define glTexParameterxOES(target, pname, param) _glTexParameterxOES(target, pname, param, __FILE__, __LINE__)
#define glTexParameterxvOES(target, pname, params) _glTexParameterxvOES(target, pname, params, __FILE__, __LINE__)
#define glTranslatexOES(x, y, z) _glTranslatexOES(x, y, z, __FILE__, __LINE__)
#define glGetLightxvOES(light, pname, params) _glGetLightxvOES(light, pname, params, __FILE__, __LINE__)
#define glGetMaterialxvOES(face, pname, params) _glGetMaterialxvOES(face, pname, params, __FILE__, __LINE__)
#define glPointParameterxOES(pname, param) _glPointParameterxOES(pname, param, __FILE__, __LINE__)
#define glSampleCoveragexOES(value, invert) _glSampleCoveragexOES(value, invert, __FILE__, __LINE__)
#define glAccumxOES(op, value) _glAccumxOES(op, value, __FILE__, __LINE__)
#define glBitmapxOES(width, height, xorig, yorig, xmove, ymove, bitmap) _glBitmapxOES(width, height, xorig, yorig, xmove, ymove, bitmap, __FILE__, __LINE__)
#define glBlendColorxOES(red, green, blue, alpha) _glBlendColorxOES(red, green, blue, alpha, __FILE__, __LINE__)
#define glClearAccumxOES(red, green, blue, alpha) _glClearAccumxOES(red, green, blue, alpha, __FILE__, __LINE__)
#define glColor3xOES(red, green, blue) _glColor3xOES(red, green, blue, __FILE__, __LINE__)
#define glColor3xvOES(components) _glColor3xvOES(components, __FILE__, __LINE__)
#define glColor4xvOES(components) _glColor4xvOES(components, __FILE__, __LINE__)
#define glConvolutionParameterxOES(target, pname, param) _glConvolutionParameterxOES(target, pname, param, __FILE__, __LINE__)
#define glConvolutionParameterxvOES(target, pname, params) _glConvolutionParameterxvOES(target, pname, params, __FILE__, __LINE__)
#define glEvalCoord1xOES(u) _glEvalCoord1xOES(u, __FILE__, __LINE__)
#define glEvalCoord1xvOES(coords) _glEvalCoord1xvOES(coords, __FILE__, __LINE__)
#define glEvalCoord2xOES(u, v) _glEvalCoord2xOES(u, v, __FILE__, __LINE__)
#define glEvalCoord2xvOES(coords) _glEvalCoord2xvOES(coords, __FILE__, __LINE__)
#define glFeedbackBufferxOES(n, type, buffer) _glFeedbackBufferxOES(n, type, buffer, __FILE__, __LINE__)
#define glGetConvolutionParameterxvOES(target, pname, params) _glGetConvolutionParameterxvOES(target, pname, params, __FILE__, __LINE__)
#define glGetHistogramParameterxvOES(target, pname, params) _glGetHistogramParameterxvOES(target, pname, params, __FILE__, __LINE__)
#define glGetLightxOES(light, pname, params) _glGetLightxOES(light, pname, params, __FILE__, __LINE__)
#define glGetMapxvOES(target, query, v) _glGetMapxvOES(target, query, v, __FILE__, __LINE__)
#define glGetMaterialxOES(face, pname, param) _glGetMaterialxOES(face, pname, param, __FILE__, __LINE__)
#define glGetPixelMapxv(map, size, values) _glGetPixelMapxv(map, size, values, __FILE__, __LINE__)
#define glGetTexGenxvOES(coord, pname, params) _glGetTexGenxvOES(coord, pname, params, __FILE__, __LINE__)
#define glGetTexLevelParameterxvOES(target, level, pname, params) _glGetTexLevelParameterxvOES(target, level, pname, params, __FILE__, __LINE__)
#define glIndexxOES(component) _glIndexxOES(component, __FILE__, __LINE__)
#define glIndexxvOES(component) _glIndexxvOES(component, __FILE__, __LINE__)
#define glLoadTransposeMatrixxOES(m) _glLoadTransposeMatrixxOES(m, __FILE__, __LINE__)
#define glMap1xOES(target, u1, u2, stride, order, points) _glMap1xOES(target, u1, u2, stride, order, points, __FILE__, __LINE__)
#define glMap2xOES(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) _glMap2xOES(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points, __FILE__, __LINE__)
#define glMapGrid1xOES(n, u1, u2) _glMapGrid1xOES(n, u1, u2, __FILE__, __LINE__)
#define glMapGrid2xOES(n, u1, u2, v1, v2) _glMapGrid2xOES(n, u1, u2, v1, v2, __FILE__, __LINE__)
#define glMultTransposeMatrixxOES(m) _glMultTransposeMatrixxOES(m, __FILE__, __LINE__)
#define glMultiTexCoord1xOES(texture, s) _glMultiTexCoord1xOES(texture, s, __FILE__, __LINE__)
#define glMultiTexCoord1xvOES(texture, coords) _glMultiTexCoord1xvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord2xOES(texture, s, t) _glMultiTexCoord2xOES(texture, s, t, __FILE__, __LINE__)
#define glMultiTexCoord2xvOES(texture, coords) _glMultiTexCoord2xvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord3xOES(texture, s, t, r) _glMultiTexCoord3xOES(texture, s, t, r, __FILE__, __LINE__)
#define glMultiTexCoord3xvOES(texture, coords) _glMultiTexCoord3xvOES(texture, coords, __FILE__, __LINE__)
#define glMultiTexCoord4xvOES(texture, coords) _glMultiTexCoord4xvOES(texture, coords, __FILE__, __LINE__)
#define glNormal3xvOES(coords) _glNormal3xvOES(coords, __FILE__, __LINE__)
#define glPassThroughxOES(token) _glPassThroughxOES(token, __FILE__, __LINE__)
#define glPixelMapx(map, size, values) _glPixelMapx(map, size, values, __FILE__, __LINE__)
#define glPixelStorex(pname, param) _glPixelStorex(pname, param, __FILE__, __LINE__)
#define glPixelTransferxOES(pname, param) _glPixelTransferxOES(pname, param, __FILE__, __LINE__)
#define glPixelZoomxOES(xfactor, yfactor) _glPixelZoomxOES(xfactor, yfactor, __FILE__, __LINE__)
#define glPrioritizeTexturesxOES(n, textures, priorities) _glPrioritizeTexturesxOES(n, textures, priorities, __FILE__, __LINE__)
#define glRasterPos2xOES(x, y) _glRasterPos2xOES(x, y, __FILE__, __LINE__)
#define glRasterPos2xvOES(coords) _glRasterPos2xvOES(coords, __FILE__, __LINE__)
#define glRasterPos3xOES(x, y, z) _glRasterPos3xOES(x, y, z, __FILE__, __LINE__)
#define glRasterPos3xvOES(coords) _glRasterPos3xvOES(coords, __FILE__, __LINE__)
#define glRasterPos4xOES(x, y, z, w) _glRasterPos4xOES(x, y, z, w, __FILE__, __LINE__)
#define glRasterPos4xvOES(coords) _glRasterPos4xvOES(coords, __FILE__, __LINE__)
#define glRectxOES(x1, y1, x2, y2) _glRectxOES(x1, y1, x2, y2, __FILE__, __LINE__)
#define glRectxvOES(v1, v2) _glRectxvOES(v1, v2, __FILE__, __LINE__)
#define glTexCoord1xOES(s) _glTexCoord1xOES(s, __FILE__, __LINE__)
#define glTexCoord1xvOES(coords) _glTexCoord1xvOES(coords, __FILE__, __LINE__)
#define glTexCoord2xOES(s, t) _glTexCoord2xOES(s, t, __FILE__, __LINE__)
#define glTexCoord2xvOES(coords) _glTexCoord2xvOES(coords, __FILE__, __LINE__)
#define glTexCoord3xOES(s, t, r) _glTexCoord3xOES(s, t, r, __FILE__, __LINE__)
#define glTexCoord3xvOES(coords) _glTexCoord3xvOES(coords, __FILE__, __LINE__)
#define glTexCoord4xOES(s, t, r, q) _glTexCoord4xOES(s, t, r, q, __FILE__, __LINE__)
#define glTexCoord4xvOES(coords) _glTexCoord4xvOES(coords, __FILE__, __LINE__)
#define glTexGenxOES(coord, pname, param) _glTexGenxOES(coord, pname, param, __FILE__, __LINE__)
#define glTexGenxvOES(coord, pname, params) _glTexGenxvOES(coord, pname, params, __FILE__, __LINE__)
#define glVertex2xOES(x) _glVertex2xOES(x, __FILE__, __LINE__)
#define glVertex2xvOES(coords) _glVertex2xvOES(coords, __FILE__, __LINE__)
#define glVertex3xOES(x, y) _glVertex3xOES(x, y, __FILE__, __LINE__)
#define glVertex3xvOES(coords) _glVertex3xvOES(coords, __FILE__, __LINE__)
#define glVertex4xOES(x, y, z) _glVertex4xOES(x, y, z, __FILE__, __LINE__)
#define glVertex4xvOES(coords) _glVertex4xvOES(coords, __FILE__, __LINE__)
#define glQueryMatrixxOES(mantissa, exponent) _glQueryMatrixxOES(mantissa, exponent, __FILE__, __LINE__)
#define glClearDepthfOES(depth) _glClearDepthfOES(depth, __FILE__, __LINE__)
#define glClipPlanefOES(plane, equation) _glClipPlanefOES(plane, equation, __FILE__, __LINE__)
#define glDepthRangefOES(n, f) _glDepthRangefOES(n, f, __FILE__, __LINE__)
#define glFrustumfOES(l, r, b, t, n, f) _glFrustumfOES(l, r, b, t, n, f, __FILE__, __LINE__)
#define glGetClipPlanefOES(plane, equation) _glGetClipPlanefOES(plane, equation, __FILE__, __LINE__)
#define glOrthofOES(l, r, b, t, n, f) _glOrthofOES(l, r, b, t, n, f, __FILE__, __LINE__)
#define glFramebufferTextureMultiviewOVR(target, attachment, texture, level, baseViewIndex, numViews) _glFramebufferTextureMultiviewOVR(target, attachment, texture, level, baseViewIndex, numViews, __FILE__, __LINE__)
#define glHintPGI(target, mode) _glHintPGI(target, mode, __FILE__, __LINE__)
#define glDetailTexFuncSGIS(target, n, points) _glDetailTexFuncSGIS(target, n, points, __FILE__, __LINE__)
#define glGetDetailTexFuncSGIS(target, points) _glGetDetailTexFuncSGIS(target, points, __FILE__, __LINE__)
#define glFogFuncSGIS(n, points) _glFogFuncSGIS(n, points, __FILE__, __LINE__)
#define glGetFogFuncSGIS(points) _glGetFogFuncSGIS(points, __FILE__, __LINE__)
#define glSampleMaskSGIS(value, invert) _glSampleMaskSGIS(value, invert, __FILE__, __LINE__)
#define glSamplePatternSGIS(pattern) _glSamplePatternSGIS(pattern, __FILE__, __LINE__)
#define glPixelTexGenParameteriSGIS(pname, param) _glPixelTexGenParameteriSGIS(pname, param, __FILE__, __LINE__)
#define glPixelTexGenParameterivSGIS(pname, params) _glPixelTexGenParameterivSGIS(pname, params, __FILE__, __LINE__)
#define glPixelTexGenParameterfSGIS(pname, param) _glPixelTexGenParameterfSGIS(pname, param, __FILE__, __LINE__)
#define glPixelTexGenParameterfvSGIS(pname, params) _glPixelTexGenParameterfvSGIS(pname, params, __FILE__, __LINE__)
#define glGetPixelTexGenParameterivSGIS(pname, params) _glGetPixelTexGenParameterivSGIS(pname, params, __FILE__, __LINE__)
#define glGetPixelTexGenParameterfvSGIS(pname, params) _glGetPixelTexGenParameterfvSGIS(pname, params, __FILE__, __LINE__)
#define glPointParameterfSGIS(pname, param) _glPointParameterfSGIS(pname, param, __FILE__, __LINE__)
#define glPointParameterfvSGIS(pname, params) _glPointParameterfvSGIS(pname, params, __FILE__, __LINE__)
#define glSharpenTexFuncSGIS(target, n, points) _glSharpenTexFuncSGIS(target, n, points, __FILE__, __LINE__)
#define glGetSharpenTexFuncSGIS(target, points) _glGetSharpenTexFuncSGIS(target, points, __FILE__, __LINE__)
#define glTexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels) _glTexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels, __FILE__, __LINE__)
#define glTexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels) _glTexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels, __FILE__, __LINE__)
#define glTextureColorMaskSGIS(red, green, blue, alpha) _glTextureColorMaskSGIS(red, green, blue, alpha, __FILE__, __LINE__)
#define glGetTexFilterFuncSGIS(target, filter, weights) _glGetTexFilterFuncSGIS(target, filter, weights, __FILE__, __LINE__)
#define glTexFilterFuncSGIS(target, filter, n, weights) _glTexFilterFuncSGIS(target, filter, n, weights, __FILE__, __LINE__)
#define glAsyncMarkerSGIX(marker) _glAsyncMarkerSGIX(marker, __FILE__, __LINE__)
#define glFinishAsyncSGIX(markerp) _glFinishAsyncSGIX(markerp, __FILE__, __LINE__)
#define glPollAsyncSGIX(markerp) _glPollAsyncSGIX(markerp, __FILE__, __LINE__)
#define glGenAsyncMarkersSGIX(range) _glGenAsyncMarkersSGIX(range, __FILE__, __LINE__)
#define glDeleteAsyncMarkersSGIX(marker, range) _glDeleteAsyncMarkersSGIX(marker, range, __FILE__, __LINE__)
#define glIsAsyncMarkerSGIX(marker) _glIsAsyncMarkerSGIX(marker, __FILE__, __LINE__)
#define glFlushRasterSGIX() _glFlushRasterSGIX(__FILE__, __LINE__)
#define glFragmentColorMaterialSGIX(face, mode) _glFragmentColorMaterialSGIX(face, mode, __FILE__, __LINE__)
#define glFragmentLightfSGIX(light, pname, param) _glFragmentLightfSGIX(light, pname, param, __FILE__, __LINE__)
#define glFragmentLightfvSGIX(light, pname, params) _glFragmentLightfvSGIX(light, pname, params, __FILE__, __LINE__)
#define glFragmentLightiSGIX(light, pname, param) _glFragmentLightiSGIX(light, pname, param, __FILE__, __LINE__)
#define glFragmentLightivSGIX(light, pname, params) _glFragmentLightivSGIX(light, pname, params, __FILE__, __LINE__)
#define glFragmentLightModelfSGIX(pname, param) _glFragmentLightModelfSGIX(pname, param, __FILE__, __LINE__)
#define glFragmentLightModelfvSGIX(pname, params) _glFragmentLightModelfvSGIX(pname, params, __FILE__, __LINE__)
#define glFragmentLightModeliSGIX(pname, param) _glFragmentLightModeliSGIX(pname, param, __FILE__, __LINE__)
#define glFragmentLightModelivSGIX(pname, params) _glFragmentLightModelivSGIX(pname, params, __FILE__, __LINE__)
#define glFragmentMaterialfSGIX(face, pname, param) _glFragmentMaterialfSGIX(face, pname, param, __FILE__, __LINE__)
#define glFragmentMaterialfvSGIX(face, pname, params) _glFragmentMaterialfvSGIX(face, pname, params, __FILE__, __LINE__)
#define glFragmentMaterialiSGIX(face, pname, param) _glFragmentMaterialiSGIX(face, pname, param, __FILE__, __LINE__)
#define glFragmentMaterialivSGIX(face, pname, params) _glFragmentMaterialivSGIX(face, pname, params, __FILE__, __LINE__)
#define glGetFragmentLightfvSGIX(light, pname, params) _glGetFragmentLightfvSGIX(light, pname, params, __FILE__, __LINE__)
#define glGetFragmentLightivSGIX(light, pname, params) _glGetFragmentLightivSGIX(light, pname, params, __FILE__, __LINE__)
#define glGetFragmentMaterialfvSGIX(face, pname, params) _glGetFragmentMaterialfvSGIX(face, pname, params, __FILE__, __LINE__)
#define glGetFragmentMaterialivSGIX(face, pname, params) _glGetFragmentMaterialivSGIX(face, pname, params, __FILE__, __LINE__)
#define glLightEnviSGIX(pname, param) _glLightEnviSGIX(pname, param, __FILE__, __LINE__)
#define glFrameZoomSGIX(factor) _glFrameZoomSGIX(factor, __FILE__, __LINE__)
#define glIglooInterfaceSGIX(pname, params) _glIglooInterfaceSGIX(pname, params, __FILE__, __LINE__)
#define glGetInstrumentsSGIX() _glGetInstrumentsSGIX(__FILE__, __LINE__)
#define glInstrumentsBufferSGIX(size, buffer) _glInstrumentsBufferSGIX(size, buffer, __FILE__, __LINE__)
#define glPollInstrumentsSGIX(marker_p) _glPollInstrumentsSGIX(marker_p, __FILE__, __LINE__)
#define glReadInstrumentsSGIX(marker) _glReadInstrumentsSGIX(marker, __FILE__, __LINE__)
#define glStartInstrumentsSGIX() _glStartInstrumentsSGIX(__FILE__, __LINE__)
#define glStopInstrumentsSGIX(marker) _glStopInstrumentsSGIX(marker, __FILE__, __LINE__)
#define glGetListParameterfvSGIX(list, pname, params) _glGetListParameterfvSGIX(list, pname, params, __FILE__, __LINE__)
#define glGetListParameterivSGIX(list, pname, params) _glGetListParameterivSGIX(list, pname, params, __FILE__, __LINE__)
#define glListParameterfSGIX(list, pname, param) _glListParameterfSGIX(list, pname, param, __FILE__, __LINE__)
#define glListParameterfvSGIX(list, pname, params) _glListParameterfvSGIX(list, pname, params, __FILE__, __LINE__)
#define glListParameteriSGIX(list, pname, param) _glListParameteriSGIX(list, pname, param, __FILE__, __LINE__)
#define glListParameterivSGIX(list, pname, params) _glListParameterivSGIX(list, pname, params, __FILE__, __LINE__)
#define glPixelTexGenSGIX(mode) _glPixelTexGenSGIX(mode, __FILE__, __LINE__)
#define glDeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points) _glDeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points, __FILE__, __LINE__)
#define glDeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points) _glDeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points, __FILE__, __LINE__)
#define glDeformSGIX(mask) _glDeformSGIX(mask, __FILE__, __LINE__)
#define glLoadIdentityDeformationMapSGIX(mask) _glLoadIdentityDeformationMapSGIX(mask, __FILE__, __LINE__)
#define glReferencePlaneSGIX(equation) _glReferencePlaneSGIX(equation, __FILE__, __LINE__)
#define glSpriteParameterfSGIX(pname, param) _glSpriteParameterfSGIX(pname, param, __FILE__, __LINE__)
#define glSpriteParameterfvSGIX(pname, params) _glSpriteParameterfvSGIX(pname, params, __FILE__, __LINE__)
#define glSpriteParameteriSGIX(pname, param) _glSpriteParameteriSGIX(pname, param, __FILE__, __LINE__)
#define glSpriteParameterivSGIX(pname, params) _glSpriteParameterivSGIX(pname, params, __FILE__, __LINE__)
#define glTagSampleBufferSGIX() _glTagSampleBufferSGIX(__FILE__, __LINE__)
#define glColorTableSGI(target, internalformat, width, format, type, table) _glColorTableSGI(target, internalformat, width, format, type, table, __FILE__, __LINE__)
#define glColorTableParameterfvSGI(target, pname, params) _glColorTableParameterfvSGI(target, pname, params, __FILE__, __LINE__)
#define glColorTableParameterivSGI(target, pname, params) _glColorTableParameterivSGI(target, pname, params, __FILE__, __LINE__)
#define glCopyColorTableSGI(target, internalformat, x, y, width) _glCopyColorTableSGI(target, internalformat, x, y, width, __FILE__, __LINE__)
#define glGetColorTableSGI(target, format, type, table) _glGetColorTableSGI(target, format, type, table, __FILE__, __LINE__)
#define glGetColorTableParameterfvSGI(target, pname, params) _glGetColorTableParameterfvSGI(target, pname, params, __FILE__, __LINE__)
#define glGetColorTableParameterivSGI(target, pname, params) _glGetColorTableParameterivSGI(target, pname, params, __FILE__, __LINE__)
#define glFinishTextureSUNX() _glFinishTextureSUNX(__FILE__, __LINE__)
#define glGlobalAlphaFactorbSUN(factor) _glGlobalAlphaFactorbSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactorsSUN(factor) _glGlobalAlphaFactorsSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactoriSUN(factor) _glGlobalAlphaFactoriSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactorfSUN(factor) _glGlobalAlphaFactorfSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactordSUN(factor) _glGlobalAlphaFactordSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactorubSUN(factor) _glGlobalAlphaFactorubSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactorusSUN(factor) _glGlobalAlphaFactorusSUN(factor, __FILE__, __LINE__)
#define glGlobalAlphaFactoruiSUN(factor) _glGlobalAlphaFactoruiSUN(factor, __FILE__, __LINE__)
#define glDrawMeshArraysSUN(mode, first, count, width) _glDrawMeshArraysSUN(mode, first, count, width, __FILE__, __LINE__)
#define glReplacementCodeuiSUN(code) _glReplacementCodeuiSUN(code, __FILE__, __LINE__)
#define glReplacementCodeusSUN(code) _glReplacementCodeusSUN(code, __FILE__, __LINE__)
#define glReplacementCodeubSUN(code) _glReplacementCodeubSUN(code, __FILE__, __LINE__)
#define glReplacementCodeuivSUN(code) _glReplacementCodeuivSUN(code, __FILE__, __LINE__)
#define glReplacementCodeusvSUN(code) _glReplacementCodeusvSUN(code, __FILE__, __LINE__)
#define glReplacementCodeubvSUN(code) _glReplacementCodeubvSUN(code, __FILE__, __LINE__)
#define glReplacementCodePointerSUN(type, stride, pointer) _glReplacementCodePointerSUN(type, stride, pointer, __FILE__, __LINE__)
#define glColor4ubVertex2fSUN(r, g, b, a, x, y) _glColor4ubVertex2fSUN(r, g, b, a, x, y, __FILE__, __LINE__)
#define glColor4ubVertex2fvSUN(c, v) _glColor4ubVertex2fvSUN(c, v, __FILE__, __LINE__)
#define glColor4ubVertex3fSUN(r, g, b, a, x, y, z) _glColor4ubVertex3fSUN(r, g, b, a, x, y, z, __FILE__, __LINE__)
#define glColor4ubVertex3fvSUN(c, v) _glColor4ubVertex3fvSUN(c, v, __FILE__, __LINE__)
#define glColor3fVertex3fSUN(r, g, b, x, y, z) _glColor3fVertex3fSUN(r, g, b, x, y, z, __FILE__, __LINE__)
#define glColor3fVertex3fvSUN(c, v) _glColor3fVertex3fvSUN(c, v, __FILE__, __LINE__)
#define glNormal3fVertex3fSUN(nx, ny, nz, x, y, z) _glNormal3fVertex3fSUN(nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glNormal3fVertex3fvSUN(n, v) _glNormal3fVertex3fvSUN(n, v, __FILE__, __LINE__)
#define glColor4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z) _glColor4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glColor4fNormal3fVertex3fvSUN(c, n, v) _glColor4fNormal3fVertex3fvSUN(c, n, v, __FILE__, __LINE__)
#define glTexCoord2fVertex3fSUN(s, t, x, y, z) _glTexCoord2fVertex3fSUN(s, t, x, y, z, __FILE__, __LINE__)
#define glTexCoord2fVertex3fvSUN(tc, v) _glTexCoord2fVertex3fvSUN(tc, v, __FILE__, __LINE__)
#define glTexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w) _glTexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w, __FILE__, __LINE__)
#define glTexCoord4fVertex4fvSUN(tc, v) _glTexCoord4fVertex4fvSUN(tc, v, __FILE__, __LINE__)
#define glTexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z) _glTexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z, __FILE__, __LINE__)
#define glTexCoord2fColor4ubVertex3fvSUN(tc, c, v) _glTexCoord2fColor4ubVertex3fvSUN(tc, c, v, __FILE__, __LINE__)
#define glTexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z) _glTexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z, __FILE__, __LINE__)
#define glTexCoord2fColor3fVertex3fvSUN(tc, c, v) _glTexCoord2fColor3fVertex3fvSUN(tc, c, v, __FILE__, __LINE__)
#define glTexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z) _glTexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glTexCoord2fNormal3fVertex3fvSUN(tc, n, v) _glTexCoord2fNormal3fVertex3fvSUN(tc, n, v, __FILE__, __LINE__)
#define glTexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z) _glTexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glTexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v) _glTexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v, __FILE__, __LINE__)
#define glTexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w) _glTexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w, __FILE__, __LINE__)
#define glTexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v) _glTexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v, __FILE__, __LINE__)
#define glReplacementCodeuiVertex3fSUN(rc, x, y, z) _glReplacementCodeuiVertex3fSUN(rc, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiVertex3fvSUN(rc, v) _glReplacementCodeuiVertex3fvSUN(rc, v, __FILE__, __LINE__)
#define glReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z) _glReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v) _glReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v, __FILE__, __LINE__)
#define glReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z) _glReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiColor3fVertex3fvSUN(rc, c, v) _glReplacementCodeuiColor3fVertex3fvSUN(rc, c, v, __FILE__, __LINE__)
#define glReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z) _glReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v) _glReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v, __FILE__, __LINE__)
#define glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z) _glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v) _glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z) _glReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v) _glReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z) _glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v) _glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z) _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z, __FILE__, __LINE__)
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v) _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v, __FILE__, __LINE__)


#endif //  OPENGL_UTILITIES_GLAD_DEBUG_WRAPPER

