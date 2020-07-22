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
    bool operator==(VertexSemantic other) {
        return (type == other.type)
                && (strncmp(name, other.name, MAX_VERTEX_SEMANTIC_NAME_LENGTH) == 0);
    }
    size_t type_size() const;
};

// Returns the byte-length of a single attribute of this semantic.
size_t VertexSemantic::type_size() {
    #define CASE(TYPE,SIZE) if (type == ( TYPE )) return size * ( SIZE );
    CASE(GL_BYTE, 1);
    CASE(GL_UNSIGNED_BYTE, 1);
    CASE(GL_SHORT, 2);
    CASE(GL_UNSIGNED_SHORT, 2);
    CASE(GL_INT, 4);
    CASE(GL_UNSIGNED_INT, 4);
    CASE(GL_HALF_FLOAT, 2);
    CASE(GL_FLOAT, 4);
    CASE(GL_DOUBLE, 8);
    fprintf(stderr, "ERROR: Vertex attribute type size unaccounted for.\n");
    exit(EXIT_FAILURE);
}

VertexAttributeBindingIndex VertexSemantic::get_binding_index()
{
    static std::vector<VertexSemantic> encountered_semantics(0);
    
    for (int i = 0; i < encountered_semantics.length(); i++) {
        if (*this == encountered_semantics[i]) {
            // Semantic has already been encountered, return the index (which is the binding index).
            return i;
        }
    }
    // This semantic has not been encountered yet. Add it to the list.
    encountered_semantics.push_back(*this);
    return encountered_semantics.length() - 1;
}

// struct VertexArchetype : public IResourceType<VertexArchetype> {
//     static bool load(void *data, std::istream &stream); // no loading from stream
//     static bool unload(void *data);
//     std::vector<VertexSemantic> semantics;
//     // Concrete layout information.
//     
// };


struct VertexArrayLayout {
    GLenum index_type; // GL_UNSIGNED_{BYTE,SHORT,INT}
    uint32_t num_vertices;
    uint32_t vertices_starting_index;
    bool indexed;
    uint32_t num_indices;
    uint32_t indices_starting_index;

    std::vector<VertexSemantic> semantics;
    size_t vertex_size() const;
};
size_t VertexArrayLayout::vertex_size() const {
    size_t total = 0;
    for (VertexSemantic &semantic : semantics) {
        total += semantic.type_size();
    }
    return total;
}

struct VertexArrayData {
    VertexArrayLayout layout;
    std::vector<uint8_t *> attribute_buffers;
};
struct VertexArray : public IResourceType<VertexArray> {
    
    static bool load(void *data, std::istream &stream);
    static bool unload(void *data);
    static Resource<VertexArray> from_vertex_array_data(VertexArrayData &data);

    VertexArrayLayout layout;
    // The OpenGL vertex array object must conform to the vertex concrete layout, determined by the semantics.
    GLuint gl_vao_id;
    // The vertices are stored in a single buffer, only containing these vertices.
    GLuint gl_buffer_id;
    // If the vertices are indexed, the index buffer is a separate buffer whose handle is stored here.
    GLuint gl_index_buffer_id;
};

Resource<VertexArray> VertexArray::from_vertex_array_data(ResourceModel &rm, VertexArrayData &data)
{
    //-----pointer to resource model stored in all resources.

    GLuint vao_id;
    glCreateVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    // Create a single buffer, and interleave vertex attributes.
    size_t vertex_size = data.layout.vertex_size();
    int num_attributes = data.layout.semantics.length();
    size_t buffer_size = vertex_size * data.layout.num_vertices;
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER,
                 reinterpret_cast<GLsizeiptr>(buffer_size),
                 nullptr,         // Data pointer is null so nothing is uploaded.
                 GL_STATIC_DRAW); // Supposedly this was created for some sort of model, so this hint makes sense.
    // Map the buffer into accessible memory.
    uint8_t *mapped_buffer = reinterpret_cast<uint8_t *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    // The VertexArrayData has separate buffers for each attribute.
    // Interleave these into the single mapped buffer.
    for (int i = 0; i < data.layout.num_vertices; i++) {
        size_t interleaved_offset = 0;
        for (int j = 0; j < num_attributes; j++) {
            size_t attribute_size = data.layout.semantics[j].type_size();
            memcpy(&mapped_buffer[i*vertex_size + interleaved_offset],
                   &data.layout.attributes[j][i*attribute_size],
                   attribute_size);
            interleaved_offset += attribute_size;
        }
    }

    // Release the buffer. The pointer can no longer be used.
    glUnmapBuffer(GL_ARRAY_BUFFER);



    for (int i = 0; i < num_attributes; i++) {
        VertexSemantic &semantic = data.semantics[i];
        VertexAttributeBindingIndex index = semantic.get_binding_index();
    }

    Resource<VertexArray> vertex_array = rm.new_resource<VertexArray>();

    return vertex_array;
}

#endif // VERTEX_ARRAYS_H
