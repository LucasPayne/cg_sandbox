#ifndef GL_GL_SHADER_PROGRAM_H
#define GL_GL_SHADER_PROGRAM_H

class GLShader {
private:
    GLuint m_gl_shader_id;
    GLenum m_gl_shader_type;
public:
    GLShader() {}
    GLShader(GLenum shader_type, std::string const &shader_path);
    static GLShader from_string(GLenum shader_type, const char *source);

    GLuint ID() const {
        return m_gl_shader_id;
    }
    GLenum type() const {
        return m_gl_shader_type;
    }
};

class GLShaderProgram {
private:
    GLShader m_vertex_shader;
    GLShader m_fragment_shader;

    GLuint m_gl_shader_program_id;
public:
    GLShaderProgram(GLShader vertex_shader, GLShader fragment_shader, GLuint *passed_program_id = nullptr);
    GLShaderProgram(std::string const &vertex_shader_path, std::string const &fragment_shader_path) :
        // Constructor variant to compile from shader paths.
        GLShaderProgram(GLShader(GL_VERTEX_SHADER, vertex_shader_path),
                        GLShader(GL_FRAGMENT_SHADER, fragment_shader_path))
    {}

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
