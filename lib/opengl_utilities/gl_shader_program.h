#ifndef GL_GL_SHADER_PROGRAM_H
#define GL_GL_SHADER_PROGRAM_H
#include <assert.h>
#include <string>


enum GLShaderType {
    VertexShader,
    GeometryShader,
    TessEvaluationShader,
    TessControlShader,
    FragmentShader,
    NUM_SHADER_TYPES
};
//-Leaving these here since they might be useful later.
#define SHADER_PROGRAM_VF ((1 << VertexShader) & (1 << FragmentShader))
#define SHADER_PROGRAM_VGF ((1 << VertexShader) & (1 << GeometryShader) & (1 << FragmentShader))
#define SHADER_PROGRAM_VTGF ((1 << VertexShader) & (1 << TessEvaluationShader) & (1 << GeometryShader) & (1 << FragmentShader))
#define SHADER_PROGRAM_VTTGF ((1 << VertexShader) & (1 << TessControlShader) & (1 << TessEvaluationShader) & (1 << GeometryShader) & (1 << FragmentShader))
#define SHADER_PROGRAM_VTTF ((1 << VertexShader) & (1 << TessControlShader) & (1 << TessEvaluationShader) & (1 << FragmentShader))


class GLShader {
private:
    GLuint m_gl_shader_id;
    int shader_type;
public:
    GLShader() {}
    GLShader(int shader_type, std::string const &shader_path);
    static GLShader from_string(int shader_type, const char *source);

    GLuint ID() const {
        return m_gl_shader_id;
    }
    int type() const {
        return shader_type;
    }
    GLenum gl_type() const {
        if (shader_type == VertexShader) return GL_VERTEX_SHADER;
        if (shader_type == FragmentShader) return GL_FRAGMENT_SHADER;
        if (shader_type == TessEvaluationShader) return GL_TESS_EVALUATION_SHADER;
        if (shader_type == TessControlShader) return GL_TESS_CONTROL_SHADER;
        if (shader_type == GeometryShader) return GL_GEOMETRY_SHADER;
        assert(0);
    }
};

class GLShaderProgram {
private:
    GLShader shaders[NUM_SHADER_TYPES];
    bool has_shader[NUM_SHADER_TYPES];

    GLuint m_gl_shader_program_id;
    bool linked;
public:
    GLShaderProgram(GLuint program_id = 0);
    void add_shader(GLShader shader);
    void link();

    GLuint ID() const {
        return m_gl_shader_program_id;
    }
    void bind() const {
        glUseProgram(m_gl_shader_program_id);
    }
    void unbind() const {
        glUseProgram(0);
    }
};

#endif // GL_GL_SHADER_PROGRAM_H
