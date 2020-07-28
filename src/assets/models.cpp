#include "assets/models.h"
namespace Models {

// fun fact: OFF was created for geomview, by the Geometry Center (Bill Thurston, John Conway, turning a sphere inside out without creasing...).
VertexArrayData load_OFF_model(const std::string &path, bool compute_normals, float scale)
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
    // Vertices
    std::vector<uint8_t> position_data(3*num_vertices*sizeof(float));
    for (uint32_t i = 0; i < num_vertices; i++) {
        next_line(file, line, "Not enough vertex lines.");
        float x, y, z;
        if (sscanf(line.c_str(), "%f %f %f", &x, &y, &z) != 3) load_error("Invalid vertex line.");
        ((float *) &position_data[0])[3*i+0] = x * scale;
        ((float *) &position_data[0])[3*i+1] = y * scale;
        ((float *) &position_data[0])[3*i+2] = z * scale;
    }
    // Triangle indices
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
            ((uint8_t *) &index_data[0])[3*i + 1] = (uint8_t) b;
            ((uint8_t *) &index_data[0])[3*i + 2] = (uint8_t) c;
        } else if (index_bytes == 2) {
            ((uint16_t *) &index_data[0])[3*i + 0] = (uint16_t) a;
            ((uint16_t *) &index_data[0])[3*i + 1] = (uint16_t) b;
            ((uint16_t *) &index_data[0])[3*i + 2] = (uint16_t) c;
        } else if (index_bytes == 4) {
            ((uint32_t *) &index_data[0])[3*i + 0] = (uint32_t) a;
            ((uint32_t *) &index_data[0])[3*i + 1] = (uint32_t) b;
            ((uint32_t *) &index_data[0])[3*i + 2] = (uint32_t) c;
        }
    }
    // Edge data is ignored.

    // Construct the VertexArrayData structure.
    VertexArrayData data;
    // Vertex data
    data.layout.num_vertices = num_vertices;
    data.attribute_buffers.push_back(position_data);
    data.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_position"));
    // Indices
    data.layout.indexed = true;
    if (index_bytes == 1) data.layout.index_type = GL_UNSIGNED_BYTE;
    else if (index_bytes == 2) data.layout.index_type = GL_UNSIGNED_SHORT;
    else if (index_bytes == 4) data.layout.index_type = GL_UNSIGNED_INT;
    data.layout.num_indices = 3 * num_triangles;
    data.index_buffer = index_data;

    vec3 *positions = (vec3 *) &position_data[0];
    // Optional computed normals.
    if (compute_normals) {

        std::vector<uint8_t> normal_data(3*num_vertices*sizeof(float));
        memset(&normal_data[0], 0, 3*num_vertices*sizeof(float));
        vec3 *normals = (vec3 *) &normal_data[0];
        for (uint32_t i = 0; i < num_triangles; i++) {
            uint32_t ai = data.index(3*i + 0);
            uint32_t bi = data.index(3*i + 1);
            uint32_t ci = data.index(3*i + 2);
            const vec3 &a = positions[ai];
            const vec3 &b = positions[bi];
            const vec3 &c = positions[ci];
            vec3 n = vec3::cross(b - a, c - a).normalized();
            normals[ai] += n;
            normals[bi] += n;
            normals[ci] += n;
        }
        for (uint32_t i = 0; i < num_vertices; i++) {
            normals[i] = normals[i].normalized();
        }

        data.attribute_buffers.push_back(normal_data);
        data.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_normal"));
    }

    return data;
}

enum ModelFileFormats {
    MODEL_FILE_FORMAT_OFF,
    MODEL_FILE_FORMAT_OBJ,
};
static const ModelFileFormatLoader model_file_format_loaders[] = {
    load_OFF_model,
    load_OBJ_model,
};

Model load(const std::string &path)
{
    // Select a format based on the file suffix.
    const char *c_path = path.c_str();
    int file_format;
    #define FORMAT(FORMAT_NAME,DOT_SUFFIX)\
        if (strncmp(strchr(c_path, '\0')-strlen(FORMAT_NAME), DOT_SUFFIX, strlen(FORMAT_NAME)) == 0) {\
            file_format = MODEL_FILE_FORMAT_ ## FORMAT_NAME;\
            goto continue_here_when_format_selected;\
        }
    FORMAT(OFF, ".off");
    FORMAT(OBJ, ".obj");
    fprintf(stderr, "ERROR: Could not interpret model file format for file \"%s\".\n", path.c_str());
    exit(EXIT_FAILURE);
continue_here_when_format_selected:
    
}


}; // namespace Models
