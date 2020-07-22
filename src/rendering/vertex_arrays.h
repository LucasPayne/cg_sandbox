#ifndef VERTEX_ARRAYS_H
#define VERTEX_ARRAYS_H
/*--------------------------------------------------------------------------------
Vertex arrays submodule of the rendering module.

Provides rendering resources:
    VertexArray
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "resource_model/resource_model.h"

struct VertexArray : public IResourceType<VertexArray> {
    static bool load(void *data, std::istream &stream);
    static bool unload(void *data);

    GLenum index_type; // GL_UNSIGNED_{BYTE,SHORT,INT}
    uint32_t num_vertices;
    uint32_t vertices_starting_index;
    bool indexed;
    uint32_t num_indices;
    uint32_t indices_starting_index;

    GLuint gl_vao_id;
};

#endif // VERTEX_ARRAYS_H
