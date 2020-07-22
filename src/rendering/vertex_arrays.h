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

typedef uint16_t VertexAttributeBindingIndex;
#define MAX_VERTEX_SEMANTIC_NAME_LENGTH 31
struct VertexSemantic {
    char name[MAX_VERTEX_SEMANTIC_NAME_LENGTH + 1];
    GLenum type;
    GLint size;
    
    VertexAttributeBindingIndex get_binding_index();

    // Equality operator for searching lists to match semantics.
    inline bool operator==(VertexSemantic other) {
        return (type == other.type)
                && (size == other.size)
                && (strncmp(name, other.name, MAX_VERTEX_SEMANTIC_NAME_LENGTH) == 0);
    }
    // Returns the byte-length of a single attribute of this semantic.
    size_t type_size() const;
};

struct VertexArrayLayout {
    GLenum index_type; // GL_UNSIGNED_{BYTE,SHORT,INT}
    uint32_t num_vertices;
    uint32_t vertices_starting_index;
    bool indexed;
    uint32_t num_indices;
    uint32_t indices_starting_index;

    std::vector<VertexSemantic> semantics;
    size_t vertex_size() const;
    size_t index_type_size() const;
};
struct VertexArrayData {
    VertexArrayLayout layout;
    std::vector<std::vector<uint8_t>> attribute_buffers;
    std::vector<uint8_t> index_buffer; //note: uint8_t just signifies this is a byte-buffer.
};
struct VertexArray : public IResourceType<VertexArray> {
    
    static bool load(void *data, std::istream &stream);
    static bool unload(void *data);
    static Resource<VertexArray> from_vertex_array_data(ResourceModel &rm, VertexArrayData &data);

    VertexArrayLayout layout;
    // The OpenGL vertex array object must conform to the vertex concrete layout, determined by the semantics.
    GLuint gl_vao_id;
    // The vertices are stored in a single buffer, only containing these vertices.
    GLuint gl_buffer_id;
    // If the vertices are indexed, the index buffer is a separate buffer whose handle is stored here.
    GLuint gl_index_buffer_id;
};


#endif // VERTEX_ARRAYS_H
