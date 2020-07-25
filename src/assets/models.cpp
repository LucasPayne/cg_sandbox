#include "assets/models.h"
namespace Models {

// fun fact: OFF was created for geomview, by the Geometry Center (Bill Thurston, John Conway, turning a sphere inside out without creasing...).
VertexArrayData load_OFF_model(const std::string &path)
{
    #define load_error(ERROR_STR) {\
        printf("OFF model load error: %s\n", ( ERROR_STR ));\
        exit(EXIT_FAILURE);\
    }
    // Macro to get the next line, skipping lines which are just spaces and commented lines.
    #define next_line(STREAM,LINE,ERROR_MESSAGE) {\
        while (true) {\
            if (!std::getline(STREAM, LINE)) {\
                fprintf(stderr, "OFF model load error: %s\n", ERROR_MESSAGE);\
                exit(EXIT_FAILURE);\
            }\
            if (strspn(( LINE ).c_str(), " ") == strlen(( LINE ).c_str())) continue;\
            if (strncmp("#", ( LINE ).c_str(), 1) != 0) break;\
        }\
    }
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) load_error("Failed to open file.");
    std::string line;
    next_line(file, line, "Empty file");
    if (line != "OFF") load_error("OFF files must start with the magic line, \"OFF\".");
    next_line(file, line, "No feature count declaration.");
    // Non-triangle faces are not supported.
    uint32_t num_vertices, num_triangles, num_edges;
    if (sscanf(line.c_str(), "%u %u %u", &num_vertices, &num_triangles, &num_edges) != 3) {
        load_error("Invalid num_vertices num_faces num_edges line.");
    }
    std::vector<uint8_t> vertex_data(3*num_vertices*sizeof(float));
    for (uint32_t i = 0; i < num_vertices; i++) {
        next_line(file, line, "Not enough vertex lines.");
        float x, y, z;
        if (sscanf(line.c_str(), "%f %f %f", &x, &y, &z) != 3) load_error("Invalid vertex line.");
        ((float *) &vertex_data[0])[3*i+0] = x;
        ((float *) &vertex_data[0])[3*i+1] = y;
        ((float *) &vertex_data[0])[3*i+2] = z;
    }
    // Use the most packed index format possible, from 8-bit, 16-bit, and 32-bit unsigned integers.
    int index_bytes;
    if (num_vertices <= std::numeric_limits<uint8_t>::max()) index_bytes = 1;
    else if (num_vertices <= std::numeric_limits<uint16_t>::max()) index_bytes = 2;
    else if (num_vertices <= std::numeric_limits<uint32_t>::max()) index_bytes = 4;
    else load_error("Too many vertices to index. Please use less than four billion vertices for one model.");
    std::vector<uint8_t> index_data(3*num_triangles*index_bytes);
    for (uint32_t i = 0; i < num_triangles; i++) {
        next_line(file, line, "Not enough triangle index lines.");
        uint32_t should_be_three, a,b,c;
        if (sscanf(line.c_str(), "%u %u %u %u", &should_be_three, &a, &b, &c) != 4) load_error("Invalid triangle index line.");
        if (should_be_three != 3) load_error("Non-triangle faces are not supported.");
        if (index_bytes == 1) {
            ((uint8_t *) &index_data[0])[3*i + 0] = (uint8_t) a;
            ((uint8_t *) &index_data[0])[3*i + 0] = (uint8_t) b;
            ((uint8_t *) &index_data[0])[3*i + 0] = (uint8_t) c;
        } else if (index_bytes == 2) {
            ((uint16_t *) &index_data[0])[3*i + 0] = (uint16_t) a;
            ((uint16_t *) &index_data[0])[3*i + 0] = (uint16_t) b;
            ((uint16_t *) &index_data[0])[3*i + 0] = (uint16_t) c;
        } else if (index_bytes == 4) {
            ((uint32_t *) &index_data[0])[3*i + 0] = (uint32_t) a;
            ((uint32_t *) &index_data[0])[3*i + 0] = (uint32_t) b;
            ((uint32_t *) &index_data[0])[3*i + 0] = (uint32_t) c;
        }
    }
    // Edge data is ignored.

    // Construct the VertexArrayData structure.
    VertexArrayData data;
    // Vertex data
    data.layout.num_vertices = num_vertices;
    data.layout.vertices_starting_index = 0;
    data.attribute_buffers = std::vector<std::vector<uint8_t>>(1);
    data.attribute_buffers[0] = vertex_data;
    // Indices
    data.layout.indexed = true;
    if (index_bytes == 1) data.layout.index_type = GL_UNSIGNED_BYTE;
    else if (index_bytes == 2) data.layout.index_type = GL_UNSIGNED_SHORT;
    else if (index_bytes == 4) data.layout.index_type = GL_UNSIGNED_INT;
    data.layout.num_indices = 3 * num_triangles;
    data.index_buffer = index_data;
    data.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_position"));

    return data;
}

}; // namespace Models
