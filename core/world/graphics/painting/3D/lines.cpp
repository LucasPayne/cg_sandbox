#include "world/world.h"


void Painting::render_lines()
{
    for (auto camera : world.entities.aspects<Camera>()) {
        graphics.begin_camera_rendering(camera);

        lines_shader_program->bind();

        mat4x4 vp_matrix = camera->view_projection_matrix();
        glUniformMatrix4fv(lines_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

        for (auto &line_chain : lines) {
            glUniform4fv(lines_shader_program->uniform_location("color"), 1, (const GLfloat *) &line_chain.color);
    
            GLuint vao;
            glCreateVertexArrays(1, &vao);
            glBindVertexArray(vao);

            GLuint vertex_buffer;
            glGenBuffers(1, &vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * line_chain.points.size(), (const void *) &line_chain.points[0], GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
            glEnableVertexAttribArray(0);

            glLineWidth(line_chain.width);
            glDrawArrays(GL_LINE_STRIP, 0, line_chain.points.size());

            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vertex_buffer);
        }

        graphics.end_camera_rendering(camera);
    }
}


void Painting::chain(std::vector<vec3> &points, float width, vec4 color)
{
    lines.push_back(PaintingLines(points, width, color));
}
