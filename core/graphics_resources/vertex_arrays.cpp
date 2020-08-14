/*--------------------------------------------------------------------------------
Implementations for the vertex arrays submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "graphics_resources/vertex_arrays.h"


size_t VertexSemantic::type_size() const
{
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
    #undef CASE
}


size_t VertexArrayLayout::vertex_size() const
{
    size_t total = 0;
    for (const VertexSemantic &semantic : semantics) {
        total += semantic.type_size();
    }
    return total;
}


size_t VertexArrayLayout::index_type_size() const
{
    #define CASE(TYPE,SIZE) if (index_type == ( TYPE )) return ( SIZE )
    CASE(GL_UNSIGNED_BYTE, 1);
    CASE(GL_UNSIGNED_SHORT, 2);
    CASE(GL_UNSIGNED_INT, 4);
    fprintf(stderr, "ERROR: Index type size not accounted for.\n");
    exit(EXIT_FAILURE);
    #undef CASE
}


VertexAttributeBindingIndex VertexSemantic::get_binding_index()
{
    //!-WARNING-! This is a global list. Something will go wrong.
    // todo: Think of a better implementation for this.
    static std::vector<VertexSemantic> encountered_semantics(0);
    
    for (unsigned int i = 0; i < encountered_semantics.size(); i++) {
        if (*this == encountered_semantics[i]) {
            // Semantic has already been encountered, return the index (which is the binding index).
            return i;
        }
    }
    // This semantic has not been encountered yet. Add it to the list and return this newly used binding index.
    encountered_semantics.push_back(*this);
    VertexAttributeBindingIndex new_binding_index = encountered_semantics.size() - 1;
    return new_binding_index;
}


VertexArray VertexArray::from_vertex_array_data(VertexArrayData &data)
{
    GLuint vao_id;
    glCreateVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    // Create a single buffer, and interleave vertex attributes.
    size_t vertex_size = data.layout.vertex_size();
    int num_attributes = data.layout.semantics.size();
    size_t buffer_size = vertex_size * data.layout.num_vertices;
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER,
                 (GLsizeiptr) buffer_size,
                 nullptr,         // Data pointer is null so nothing is uploaded.
                 GL_STATIC_DRAW); // Supposedly this was created for some sort of model, so this hint makes sense.
    // Map the buffer into accessible memory.
    uint8_t *mapped_buffer = reinterpret_cast<uint8_t *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    // The VertexArrayData has separate buffers for each attribute.
    // Interleave these into the single mapped buffer.
    for (unsigned int i = 0; i < data.layout.num_vertices; i++) {
        size_t interleaved_offset = 0;
        for (int j = 0; j < num_attributes; j++) {
            size_t attribute_size = data.layout.semantics[j].type_size();
            memcpy(&mapped_buffer[i*vertex_size + interleaved_offset],
                   &data.attribute_buffers[j][i*attribute_size],
                   attribute_size);
            interleaved_offset += attribute_size;
        }
    }
    // Release the buffer. The pointer can no longer be used.
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Index buffer.
    GLuint index_buffer_id = 0;
    if (data.layout.indexed) {
        size_t index_type_size = data.layout.index_type_size();
        size_t index_buffer_size = index_type_size * data.layout.num_indices;
        glGenBuffers(1, &index_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     (GLsizeiptr) index_buffer_size,
                     (const void *) &data.index_buffer[0],
                     GL_STATIC_DRAW);
    }

    size_t interleaved_offset = 0;
    for (int i = 0; i < num_attributes; i++) {
        VertexSemantic &semantic = data.layout.semantics[i];
        VertexAttributeBindingIndex index = semantic.get_binding_index();
        glVertexAttribPointer(index,
                              semantic.size,
                              semantic.type,
                              false, //don't normalize
                              vertex_size, //stride
                              (const void *) interleaved_offset); // start at the first of this attribute in the interleaved buffer.
        glEnableVertexAttribArray(index);
        interleaved_offset += semantic.type_size(); // shift the interleaving offset so the next attributes have the correct starting position.
    }

    VertexArray vertex_array;
    vertex_array.layout = data.layout; //---copy?
    vertex_array.layout.semantics = std::vector<VertexSemantic>(0);
            //----- doing this to copy
            for (VertexSemantic semantic : data.layout.semantics) vertex_array.layout.semantics.push_back(semantic);
    vertex_array.gl_vao_id = vao_id;
    vertex_array.gl_buffer_id = buffer_id;
    vertex_array.gl_index_buffer_id = index_buffer_id;

    // Unbind OpenGL state.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return vertex_array;
}

/*================================================================================
    Reflection
================================================================================*/
DESCRIPTOR_INSTANCE(VertexSemantic);
BEGIN_ENTRIES(VertexSemantic)
    ENTRY(name)
    ENTRY(type)
    ENTRY(size)
END_ENTRIES()


DESCRIPTOR_INSTANCE(VertexArrayLayout);
BEGIN_ENTRIES(VertexArrayLayout)
    ENTRY(index_type)
    ENTRY(num_vertices)
    ENTRY(indexed)
    ENTRY(num_indices)
    ENTRY(semantics)
END_ENTRIES()


DESCRIPTOR_INSTANCE(VertexArrayData);
BEGIN_ENTRIES(VertexArrayData)
    ENTRY(layout)
    ENTRY(attribute_buffers)
    ENTRY(index_buffer)
END_ENTRIES()


DESCRIPTOR_INSTANCE(VertexArray);
BEGIN_ENTRIES(VertexArray)
    ENTRY(layout)
    ENTRY(gl_vao_id)
    ENTRY(gl_buffer_id)
    ENTRY(gl_index_buffer_id)
END_ENTRIES()
