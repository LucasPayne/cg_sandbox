#include "glad/glad.h"
#include "gl_shader_program.h"
#include <stdio.h>
#include <iostream>


GLShader GLShader::from_string(int shader_type, const char *source)
{
    GLShader shader_object;
    shader_object.shader_type = shader_type;
    shader_object.m_gl_shader_id = glCreateShader(shader_object.gl_type());
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
GLShader::GLShader(int shader_type, std::string const &shader_path)
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






GLShaderProgram::GLShaderProgram(GLuint program_id) :
    linked{false}
{
    if (program_id == 0) m_gl_shader_program_id = glCreateProgram();
    else m_gl_shader_program_id = program_id;

    for (int i = 0; i < NUM_SHADER_TYPES; i++) {
        has_shader[i] = false;
    }

    if (m_gl_shader_program_id == 0) {
        std::cerr << "ERROR [GLShaderProgram::GLShaderProgram]: Failed to create shader program.\n";
        exit(EXIT_FAILURE);
    }
}

void GLShaderProgram::add_shader(GLShader shader)
{
    if (linked) {
        std::cerr << "ERROR [GLShaderProgram::add_shader_program]: Shader program already linked.\n";
        exit(EXIT_FAILURE);
    }
    if (shader.type() < 0 || shader.type() > NUM_SHADER_TYPES) {
        std::cerr << "ERROR [add_shader_program]: Invalid shader type given.\n";
        exit(EXIT_FAILURE);
    }
    if (has_shader[shader.type()]) {
        std::cerr << "ERROR [add_shader_program]: Attempted to add a shader type twice.\n";
        exit(EXIT_FAILURE);
    }
    has_shader[shader.type()] = true;
    shaders[shader.type()] = shader;
}

void GLShaderProgram::link()
{
    if (linked) {
        std::cerr << "ERROR [GLShaderProgram::link]: Shader program already linked.\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_SHADER_TYPES; i++) {
        if (has_shader[i]) {
            glAttachShader(m_gl_shader_program_id, shaders[i].ID());
        }
    }
    glLinkProgram(m_gl_shader_program_id);
    GLint success;
    glGetProgramiv(m_gl_shader_program_id, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        std::cerr << "ERROR [GLShaderProgram::link]: Failed to link shader program.\n";
        GLint log_length; 
        glGetProgramiv(m_gl_shader_program_id, GL_INFO_LOG_LENGTH, &log_length);
        char *log = (char *) malloc(log_length * sizeof(char));
        glGetProgramInfoLog(m_gl_shader_program_id, log_length, NULL, log);
        printf("%s", log);
        free(log);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_SHADER_TYPES; i++) {
        if (has_shader[i]) {
            glDetachShader(m_gl_shader_program_id, shaders[i].ID());
        }
    }
    linked = true;

    // Introspect.
    GLint num_active_uniforms;
    // Each active uniform is assigned an "index", distinct from location or block indices.
    // This is an identifier for use with the (< 4.3) introspection API.
    glGetProgramiv(m_gl_shader_program_id, GL_ACTIVE_UNIFORMS, &num_active_uniforms);
    for (int i = 0; i < num_active_uniforms; i++) {
        const GLsizei buf_size = 2048;
        char name[buf_size];
        GLsizei name_length;
        glGetActiveUniformName(m_gl_shader_program_id, i, buf_size, &name_length, name);
        if (name_length > buf_size-1) {
            std::cerr << "ERROR [GLShaderProgram::link]: Uniform name far too long.\n";
            exit(EXIT_FAILURE);
        }
        GLint location = glGetUniformLocation(m_gl_shader_program_id, name);
        if (location >= 0) {
            std::string name_string(name, name_length);
            uniform_location_dictionary[name_string] = location;
            printf("Active uniform: %s, %d\n", name, location);
        }
        // If location < 0, just don't add it, something went wrong.
        //    ---When is location < 0?
    }
}


GLint GLShaderProgram::uniform_location(const std::string &name)
{
    auto found = uniform_location_dictionary.find(name);
    if (found == uniform_location_dictionary.end()) {
        std::cerr << "ERROR [GLShaderProgram::uniform_location]: Uniform \"" << name << "\" not found.\n";
        exit(EXIT_FAILURE);
    }
    return found->second;
}



/*--------------------------------------------------------------------------------
Simple functions to create a ShaderProgram from strings of letters denoting the types of shaders used.
All these do is fill up the relevant shaders, then send the partially created ShaderProgram
to a general shader linker.

V: Vertex shader
T: Tessellation evaluation shader
Second T: Tessellation control shader (their order in parameters is control then evaluation!)
G: Geometry shader
F: Fragment shader
--------------------------------------------------------------------------------*/
// GLShaderProgram GLShaderProgram::VF(GLShader &vertex_shader, GLShader &fragment_shader, GLint program_id = 0)
// {
//     GLShaderProgram p;
//     p.has_shaders[VertexShader] = true;
//     p.has_shaders[FragmentShader] = true;
//     p.shaders[VertexShader] = vertex_shader;
//     p.shaders[FragmentShader] = fragment_shader;
//     link_shader_program(p);
//     return p;
// }
// GLShaderProgram GLShaderProgram::VTF(GLShader &vertex_shader,
//                                      GLShader &tess_evaluation_shader,
//                                      GLShader &fragment_shader, GLint program_id)
// {
//     GLShaderProgram p;
//     p.has_shaders[VertexShader] = true;
//     p.has_shaders[FragmentShader] = true;
//     p.shaders[VertexShader] = vertex_shader;
//     p.shaders[FragmentShader] = fragment_shader;
// 
//     p.has_shaders[TessEvaluationShader] = true;
//     p.shaders[TessEvaluationShader] = tess_evaluation_shader;
//     link_shader_program(p);
//     return p;
// }
// GLShaderProgram GLShaderProgram::VTTF(GLShader &vertex_shader,
//                                       GLShader &tess_control_shader,
//                                       GLShader &tess_evaluation_shader,
//                                       GLShader &fragment_shader, GLint program_id)
// {
//     GLShaderProgram p;
//     p.has_shaders[VertexShader] = true;
//     p.has_shaders[FragmentShader] = true;
//     p.shaders[VertexShader] = vertex_shader;
//     p.shaders[FragmentShader] = fragment_shader;
// 
//     p.has_shaders[TessEvaluationShader] = true;
//     p.shaders[TessEvaluationShader] = tess_evaluation_shader;
// 
//     p.has_shaders[TessControlShader] = true;
//     p.shaders[TessControlShader] = tess_control_shader;
//     link_shader_program(p);
//     return p;
// }
// GLShaderProgram GLShaderProgram::VGF(GLShader &vertex_shader,
//                                      GLShader &geometry_shader,
//                                      GLShader &fragment_shader, GLint program_id)
// {
//     GLShaderProgram p;
//     p.has_shaders[VertexShader] = true;
//     p.has_shaders[FragmentShader] = true;
//     p.shaders[VertexShader] = vertex_shader;
//     p.shaders[FragmentShader] = fragment_shader;
// 
//     p.has_shaders[GeometryShader] = true;
//     p.shaders[GeometryShader] = geometry_shader;
//     link_shader_program(p);
//     return p;
// }
// 
// GLShaderProgram GLShaderProgram::VTTGF(GLShader &vertex_shader,
//                                        GLShader &tess_control_shader,
//                                        GLShader &tess_evaluation_shader,
//                                        GLShader &geometry_shader,
//                                        GLShader &fragment_shader, GLint program_id)
// {
//     GLShaderProgram p;
//     p.has_shaders[VertexShader] = true;
//     p.has_shaders[FragmentShader] = true;
//     p.shaders[VertexShader] = vertex_shader;
//     p.shaders[FragmentShader] = fragment_shader;
// 
//     p.has_shaders[TessEvaluationShader] = true;
//     p.shaders[TessEvaluationShader] = tess_evaluation_shader;
// 
//     p.has_shaders[TessControlShader] = true;
//     p.shaders[TessControlShader] = tess_control_shader;
// 
//     p.has_shaders[GeometryShader] = true;
//     p.shaders[GeometryShader] = geometry_shader;
//     link_shader_program(p);
//     return p;
// }


