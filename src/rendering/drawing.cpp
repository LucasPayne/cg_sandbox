#include "rendering/drawing.h"

void Draw::draw()
{
    printf("Drawing\n");
    glUseProgram(shading_program->program_id);
    glBindVertexArray(g_instance->vertex_array->gl_vao_id);

    g_instance->bind();
    m_instance->bind();
    sm_instance->bind();

    GLenum primitive_type = g_instance->base->primitive;
    VertexArrayLayout &layout = g_instance->vertex_array->layout;
    if (layout.indexed) {
        glDrawElements(primitive_type,
                       (GLsizei) layout.num_indices,
                       layout.index_type,
                       (const void *) layout.indices_starting_index);
    } else {
        glDrawArrays(primitive_type,
                     (GLint) layout.vertices_starting_index,
                     (GLsizei) layout.num_vertices);
    }
}
