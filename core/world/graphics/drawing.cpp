#include "world/graphics/drawing.h"

std::ostream &operator<<(std::ostream &os, Viewport &viewport)
{
    os << "Viewport(" << viewport.x << ", " << viewport.y << ", " << viewport.w << ", " << viewport.h << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, Framebuffer &framebuffer)
{
    os << "Framebuffer(" << framebuffer.resolution_x << "x" << framebuffer.resolution_y << ", id:" << framebuffer.id << ", texid:" << framebuffer.texture << ")";
    return os;
}


PropertySheet::PropertySheet(Resource<ShadingBlock> properties)
{
    // Create a property sheet for a specific block. This matches the size of the block.
    block = properties;
    size = properties->block_size;
    // Create properties data in application memory.
    data = std::vector<uint8_t>(size);
    memset(&data[0], 0, size);
    // Shadow the buffer in graphics memory. This will be synchronized to application memory when needed.
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
    glBufferData(GL_UNIFORM_BUFFER,
                 (GLsizeiptr) size,
                 (const void *) &data[0],
                 GL_DYNAMIC_DRAW);
    in_sync = true;
    // Unbind OpenGL state.
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
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
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    in_sync = true;
}


/*================================================================================
    Reflection
================================================================================*/
DESCRIPTOR_INSTANCE(PropertySheet);
BEGIN_ENTRIES(PropertySheet)
    ENTRY(block)
    ENTRY(data)
    ENTRY(size)
    ENTRY(in_sync)
    ENTRY(buffer_id)
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
