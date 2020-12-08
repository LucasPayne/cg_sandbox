#include "world/world.h"


void Painting::render_lines()
{
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    lines_shader_program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {
        auto viewport = camera->viewport();
        graphics.set_post(viewport);
        graphics.swap_post();

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
    }
    lines_shader_program->unbind();
}


void Painting::chain(std::vector<vec3> &points, float width, vec4 color)
{
    lines.push_back(PaintingLines(points, width, color));
}

void Painting::line(vec3 a, vec3 b, float width, vec4 color)
{
    std::vector<vec3> points(2);
    points[0] = a;
    points[1] = b;
    lines.push_back(PaintingLines(points, width, color));
}
