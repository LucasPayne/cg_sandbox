#include "world/world.h"


void Painting::render_lines_2D()
{
    primitive_lines_2D_shader_program->bind();
    glDisable(GL_BLEND);

    for (auto &line_chain : lines_2D) {
        glUniform4fv(primitive_lines_2D_shader_program->uniform_location("color"), 1, (const GLfloat *) &line_chain.color);
    
        GLuint vao;
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * line_chain.points.size(), (const void *) &line_chain.points[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
        glEnableVertexAttribArray(0);

        glLineWidth(line_chain.width);
        glDrawArrays(GL_LINE_STRIP, 0, line_chain.points.size());

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vertex_buffer);
    }
    primitive_lines_2D_shader_program->unbind();
}



void Painting::chain_2D(std::vector<vec2> &points, float width, vec4 color)
{
    lines_2D.push_back(PaintingLines2D(points, width, color));
}

