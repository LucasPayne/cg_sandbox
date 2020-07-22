/*--------------------------------------------------------------------------------
Implementations for the vertex arrays submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/vertex_arrays.h"

bool VertexArray::load(void *data, std::istream &stream)
{
    VertexArray *vertex_array = reinterpret_cast<VertexArray *>(data);
    memset(vertex_array, 0, sizeof(VertexArray));
}
bool VertexArray::unload(void *data)
{
    return false;
}
