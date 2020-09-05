#include "glad/glad.h"
#include "gl_shader_program.h"
#include <stdio.h>
#include <iostream>

GLShader GLShader::from_string(GLenum shader_type, const char *source)
{
    GLShader shader_object;
    shader_object.m_gl_shader_type = shader_type;
    shader_object.m_gl_shader_id = glCreateShader(shader_type);
    if (shader_object.m_gl_shader_id == 0) {
        std::cerr << "ERROR: Failed to create a shader ID.\n";
        exit(EXIT_FAILURE);
    }
    glShaderSource(shader_object.m_gl_shader_id, 1, (const GLchar **) &source, NULL);

    glCompileShader(shader_object.m_gl_shader_id);
    GLint success;
    glGetShaderiv(shader_object.m_gl_shader_id, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        puts(source);
        std::cerr << "ERROR: Failed to compile shader.\n";
        GLint info_length;
        glGetShaderiv(shader_object.m_gl_shader_id, GL_INFO_LOG_LENGTH, &info_length);
        char *info = new char[info_length + 1];
        glGetShaderInfoLog(shader_object.m_gl_shader_id, info_length, NULL, info);
        info[info_length] = '\0';
        std::cerr << "--------------------------------------------------------------------------------\n";
        std::cerr << " SHADER ERROR LOG";
        std::cerr << "--------------------------------------------------------------------------------\n";
        fputs(info, stderr);
        std::cerr << "--------------------------------------------------------------------------------\n";
        exit(EXIT_FAILURE);
    }
    // printf("Created new shader of type %u, id %u\n", shader_object.m_gl_shader_type, shader_object.m_gl_shader_id);
    // getchar();
    return shader_object;
}

// Load a shader.
GLShader::GLShader(GLenum shader_type, std::string const &shader_path)
{
    // https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
    FILE *file = fopen(shader_path.c_str(), "r");
    if (file == NULL) {
        std::cerr << "ERROR: Failed to open shader \"" << shader_path << "\".\n";
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    size_t source_size = ftell(file) + 1;
    char *source = new char[source_size];
    rewind(file);
    fread(source, sizeof(char), source_size-1, file);
    source[source_size-1] = '\0';

    *this = from_string(shader_type, source);
    fclose(file);
}


GLShaderProgram::GLShaderProgram(GLShader vertex_shader, GLShader fragment_shader, GLuint *passed_program_id)
{
    m_vertex_shader = vertex_shader;
    m_fragment_shader = fragment_shader;
    if (passed_program_id == nullptr) {
        m_gl_shader_program_id = glCreateProgram();
    } else {
        // A pointer to a program ID can be passed. This allows the caller to do pre-link setup.
        m_gl_shader_program_id = *passed_program_id;
    }
    if (m_gl_shader_program_id == 0) {
        std::cerr << "ERROR: Failed to create shader program.\n";
        exit(EXIT_FAILURE);
    }
    glAttachShader(m_gl_shader_program_id, m_vertex_shader.ID());
    glAttachShader(m_gl_shader_program_id, m_fragment_shader.ID());
    glLinkProgram(m_gl_shader_program_id);
    GLint success;
    glGetProgramiv(m_gl_shader_program_id, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        std::cerr << "ERROR: Failed to link shader program.\n";
        //----print log
        exit(EXIT_FAILURE);
    }
    glDetachShader(m_gl_shader_program_id, m_vertex_shader.ID());
    glDetachShader(m_gl_shader_program_id, m_fragment_shader.ID());
}
