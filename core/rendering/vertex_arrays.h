#ifndef VERTEX_ARRAYS_H
#define VERTEX_ARRAYS_H
/*--------------------------------------------------------------------------------
Vertex arrays submodule of the rendering module.

Provides rendering resources:
    VertexArray
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "world/world.h"

#include "reflector/serialization.h"

typedef uint16_t VertexAttributeBindingIndex;
#define MAX_VERTEX_SEMANTIC_NAME_LENGTH 31
/*REFLECTED*/struct VertexSemantic {
    /*ENTRY*/ char name[MAX_VERTEX_SEMANTIC_NAME_LENGTH + 1];
    /*ENTRY*/ GLenum type;
    /*ENTRY*/ GLint size;
    
    VertexAttributeBindingIndex get_binding_index();

    // Equality operator for searching lists to match semantics.
    inline bool operator==(VertexSemantic other) {
        return (type == other.type)
                && (size == other.size)
                && (strncmp(name, other.name, MAX_VERTEX_SEMANTIC_NAME_LENGTH) == 0);
    }
    // Returns the byte-length of a single attribute of this semantic.
    size_t type_size() const;

    VertexSemantic(GLenum _type, GLint _size, const std::string &_name) :
        type{_type}, size{_size}
    {
        if (_name.length() > MAX_VERTEX_SEMANTIC_NAME_LENGTH) {
            fprintf(stderr, "ERROR: Vertex semantic name too long.\n");
            exit(EXIT_FAILURE);
        }
        snprintf(name, MAX_VERTEX_SEMANTIC_NAME_LENGTH+1, "%s", _name.c_str());
    }

    VertexSemantic() {}//testing
};

/*REFLECTED*/ struct VertexArrayLayout {
    /*ENTRY*/ GLenum index_type;
        // GL_UNSIGNED_{BYTE,SHORT,INT}
    /*ENTRY*/ uint32_t num_vertices;
    /*ENTRY*/ bool indexed;
    /*ENTRY*/ uint32_t num_indices;

    std::vector<VertexSemantic> semantics;
    size_t vertex_size() const;
    size_t index_type_size() const;
};
/*REFLECTED*/ struct VertexArrayData {
    /*ENTRY*/ VertexArrayLayout layout;
    /*ENTRY*/ std::vector<std::vector<uint8_t>> attribute_buffers;
    /*ENTRY*/ std::vector<uint8_t> index_buffer;
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
struct VertexArray : public IResourceType<VertexArray> {
    
    static Resource<VertexArray> from_vertex_array_data(ResourceModel &rm, VertexArrayData &data);

    VertexArrayLayout layout;
    // The OpenGL vertex array object must conform to the vertex concrete layout, determined by the semantics.
    GLuint gl_vao_id;
    // The vertices are stored in a single buffer, only containing these vertices.
    GLuint gl_buffer_id;
    // If the vertices are indexed, the index buffer is a separate buffer whose handle is stored here.
    GLuint gl_index_buffer_id;
};

#include "/home/lucas/computer_graphics/cg_sandbox/core/rendering/vertex_arrays.serialize.h" /*SERIALIZE*/
#endif // VERTEX_ARRAYS_H
