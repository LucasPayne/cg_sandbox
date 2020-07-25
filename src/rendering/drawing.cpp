#include "rendering/drawing.h"

void Draw::draw()
{
    printf("Drawing\n");
    glUseProgram(shading_program->program_id);
    glBindVertexArray(g_instance->vertex_array->gl_vao_id);

    GeometricMaterial &geometric_material = *(g_instance->base);
    Material &material = *(m_instance->base);
    ShadingModel &shading_model = *(sm_instance->base);

    // Bind property sheets.
    // First, make sure that the data in graphics memory is up-to-date.
    // Then, bind the property sheet buffers to the reserved binding points, 0, 1, and 2.
    //     0: GeometricMaterial properties
    //     1: Material properties
    //     2: ShadingModel properties
    if (geometric_material.has_properties) {
        g_instance->properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, g_instance->properties.buffer_id);
    }
    if (material.has_properties) {
        m_instance->properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_instance->properties.buffer_id);
    }
    if (shading_model.has_properties) {
        sm_instance->properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, sm_instance->properties.buffer_id);
    }

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
    // Unbind OpenGL state.
    glUseProgram(0);
}


PropertySheet PropertySheet::instantiate_from(ShadingBlock &properties)
{
    // Create a property sheet for a specific block. This matches the size of the block.
    PropertySheet sheet;
    sheet.block = &properties;
    sheet.size = properties.block_size;
    // Create properties data in application memory.
    sheet.data = std::vector<uint8_t>(sheet.size);
    memset(&sheet.data[0], 0, sheet.size);
    // Shadow the buffer in graphics memory. This will be synchronized to application memory when needed.
    glGenBuffers(1, &sheet.buffer_id);
    glBindBuffer(GL_UNIFORM_BUFFER, sheet.buffer_id);
    glBufferData(GL_UNIFORM_BUFFER,
                 (GLsizeiptr) sheet.size,
                 (const void *) &sheet.data[0],
                 GL_DYNAMIC_DRAW);
    sheet.in_sync = true;
    // Unbind OpenGL state.
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return sheet;
}

// Synchronize application data with graphics data. This only uploads if a property changes.
void PropertySheet::synchronize()
{
    if (in_sync) return;
    // Update the buffer.
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
    glBufferSubData(GL_UNIFORM_BUFFER,
                    (GLintptr) 0,
                    (GLsizeiptr) size,
                    (const void *) &data[0]);
    // Unbind OpenGL state.
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
    in_sync = true;
}
