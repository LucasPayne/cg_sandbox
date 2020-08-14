#include "world/graphics/drawing.h"


PropertySheet PropertySheet::instantiate_from(Resource<ShadingBlock> properties)
{
    // Create a property sheet for a specific block. This matches the size of the block.
    PropertySheet sheet;
    sheet.block = properties;
    sheet.size = properties->block_size;
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




/*================================================================================
    Reflection
================================================================================*/
DESCRIPTOR_INSTANCE(PropertySheet);
BEGIN_ENTRIES(PropertySheet)
    ENTRY(data)
    ENTRY(size)
    ENTRY(in_sync)
    ENTRY(buffer_id)
    ENTRY(block)
END_ENTRIES()


DESCRIPTOR_INSTANCE(GeometricMaterialInstance);
BEGIN_ENTRIES(GeometricMaterialInstance)
    ENTRY(base)
    ENTRY(properties)
    ENTRY(vertex_array)
END_ENTRIES()


DESCRIPTOR_INSTANCE(MaterialInstance);
BEGIN_ENTRIES(MaterialInstance)
    ENTRY(base)
    ENTRY(properties)
END_ENTRIES()


DESCRIPTOR_INSTANCE(ShadingModelInstance);
BEGIN_ENTRIES(ShadingModelInstance)
    ENTRY(base)
    ENTRY(properties)
END_ENTRIES()
