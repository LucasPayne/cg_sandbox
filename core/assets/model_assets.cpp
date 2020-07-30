#include <limits>//numeric_limits
#include "assets/model_assets.h"
#include "gl/gl.h"

Resource<VertexArray> ModelAssets::load(const std::string &path)
{
    //todo: caching
    MLModel model = MLModel::load(path, ML_COMPUTE_PHONG_NORMALS);

    // Convert the MLModel into VertexArrayData.
    VertexArrayData va;
    va.layout.num_vertices = model.num_vertices;
    std::vector<uint8_t> positions_buffer(sizeof(float)*3*va.layout.num_vertices);
    for (int i = 0; i < va.layout.num_vertices; i++) {
        ((vec3 *) &positions_buffer[0])[i] = model.positions[i];
    }
    va.attribute_buffers.push_back(positions_buffer);
    va.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_position"));

    va.layout.indexed = model.has_triangles;
    if (model.has_triangles) {
        va.layout.num_indices = 3*model.num_triangles;

        int index_num_bytes;
        // Pack the indices into the smallest type possible out of 8,16, and 32-bit unsigned ints.
        if (va.layout.num_indices <= std::numeric_limits<uint8_t>::max()) {
            index_num_bytes = 1;
            va.layout.index_type = GL_UNSIGNED_BYTE;
        } else if (va.layout.num_indices <= std::numeric_limits<uint16_t>::max()) {
            index_num_bytes = 2;
            va.layout.index_type = GL_UNSIGNED_SHORT;
        } else {
            index_num_bytes = 4;
            va.layout.index_type = GL_UNSIGNED_INT;
        }
        std::vector<uint8_t> index_buffer(index_num_bytes * 3*model.num_triangles);
        for (int i = 0; i < model.num_triangles; i++) {
            MLModelTriangle &triangle = model.triangles[i];
            for (int j = 0; j < 3; j++) {
                if (index_num_bytes == 1) {
                    ((uint8_t *) &index_buffer[0])[3*i + j] = (uint8_t) triangle[j];
                } else if (index_num_bytes == 2) {
                    ((uint16_t *) &index_buffer[0])[3*i + j] = (uint16_t) triangle[j];
                } else if (index_num_bytes == 4) {
                    ((uint32_t *) &index_buffer[0])[3*i + j] = (uint32_t) triangle[j];
                }
            }
        }
        va.index_buffer = index_buffer;
    }
    // Normals.
    if (model.has_normals) {
        std::vector<uint8_t> normals_buffer(sizeof(float)*3*va.layout.num_vertices);
        for (int i = 0; i < va.layout.num_vertices; i++) {
            ((vec3 *) &normals_buffer[0])[i] = model.normals[i];
        }
        va.attribute_buffers.push_back(normals_buffer);
        va.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_normal"));
    }
    return VertexArray::from_vertex_array_data(*rm, va);
}

