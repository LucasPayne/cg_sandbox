#ifndef VERTEX_ARRAYS_H
#define VERTEX_ARRAYS_H
/*--------------------------------------------------------------------------------
Vertex arrays submodule of the rendering module.

Provides rendering resources:
    VertexArray
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"

#include "world/resource_model/resource_model.h"


typedef uint16_t VertexAttributeBindingIndex;
struct VertexSemantic {
    std::string name;
    GLenum type;
    GLint size;
    
    VertexAttributeBindingIndex get_binding_index();

    // Equality operator for searching lists to match semantics.
    inline bool operator==(VertexSemantic other) {
        return (type == other.type)
                && (size == other.size)
                && (name == other.name);
    }
    // Returns the byte-length of a single attribute of this semantic.
    size_t type_size() const;

    VertexSemantic(GLenum _type, GLint _size, const std::string &_name) :
        type{_type}, size{_size}, name{_name}
    {}

    VertexSemantic() {}//testing
};
REFLECT_STRUCT(VertexSemantic)
    STRUCT_ENTRY(name)
    STRUCT_ENTRY(type)
    STRUCT_ENTRY(size)
END_REFLECT_STRUCT()


struct VertexArrayLayout {
    GLenum index_type;
        // GL_UNSIGNED_{BYTE,SHORT,INT}
    uint32_t num_vertices;
    bool indexed;
    uint32_t num_indices;

    std::vector<VertexSemantic> semantics;
    size_t vertex_size() const;
    size_t index_type_size() const;
};
REFLECT_STRUCT(VertexArrayLayout)
    STRUCT_ENTRY(index_type)
    STRUCT_ENTRY(num_vertices)
    STRUCT_ENTRY(indexed)
    STRUCT_ENTRY(num_indices)
    STRUCT_ENTRY(semantics)
END_REFLECT_STRUCT()


struct VertexArrayData {
    VertexArrayLayout layout;
    std::vector<std::vector<uint8_t>> attribute_buffers;
    std::vector<uint8_t> index_buffer;
        //note: uint8_t just signifies this is a byte-buffer.

    // Since index data can be packed in 1 or 2 or 4 bytes, this function is here for access to the i'th index.
    inline uint32_t index(uint32_t i) const {
        if (layout.index_type == GL_UNSIGNED_BYTE) {
            return ((uint8_t *) &index_buffer[0])[i];
        } else if (layout.index_type == GL_UNSIGNED_SHORT) {
            return ((uint16_t *) &index_buffer[0])[i];
        } else if (layout.index_type == GL_UNSIGNED_INT) {
            return ((uint32_t *) &index_buffer[0])[i];
        }
    }
};
REFLECT_STRUCT(VertexArrayData)
    STRUCT_ENTRY(layout)
    STRUCT_ENTRY(attribute_buffers)
    STRUCT_ENTRY(index_buffer)
END_REFLECT_STRUCT()


struct VertexArray : public ResourceBase {
    static VertexArray from_vertex_array_data(VertexArrayData &data);

    VertexArrayLayout layout;
    // The OpenGL vertex array object must conform to the vertex concrete layout, determined by the semantics.
    GLuint gl_vao_id;
    // The vertices are stored in a single buffer, only containing these vertices.
    GLuint gl_buffer_id;
    // If the vertices are indexed, the index buffer is a separate buffer whose handle is stored here.
    GLuint gl_index_buffer_id;
};

#endif // VERTEX_ARRAYS_H
