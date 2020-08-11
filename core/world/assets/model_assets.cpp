/*--------------------------------------------------------------------------------
notes:
    Messy serialization stuff here.
--------------------------------------------------------------------------------*/
#include <limits>//numeric_limits
#include "gl/gl.h"
#include "utils/file_utils.h"

#include "world/assets/model_assets.h"


// Logging for this module.
static void log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[Assets/ModelAssets]: ");
    vprintf(format, args);
    va_end(args);
}

bool MLModel_to_VertexArrayData(MLModel &model, VertexArrayData &va)
{
    // Convert the MLModel into VertexArrayData.

    va.layout.num_vertices = model.num_vertices;
    std::vector<uint8_t> positions_buffer(sizeof(float)*3*va.layout.num_vertices);
    for (unsigned int i = 0; i < va.layout.num_vertices; i++) {
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
        for (unsigned int i = 0; i < model.num_triangles; i++) {
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
        for (unsigned int i = 0; i < va.layout.num_vertices; i++) {
            ((vec3 *) &normals_buffer[0])[i] = model.normals[i];
        }
        va.attribute_buffers.push_back(normals_buffer);
        va.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_normal"));
    }

    return true;
}



Resource<VertexArray> ModelAssets::load(const std::string &path)
{
    log("Getting model from path \"%s\"...\n", path.c_str());
    // Look up the compiled model in the cache.
    // std::unordered_map<std::string, Resource<VertexArray>>::iterator found = vertex_array_cache.find(path);
    auto found = vertex_array_cache.find(path);
    if (found != vertex_array_cache.end()) {
        // The model is already loaded. Return the already-compiled vertex array.
        log("Model is already loaded.\n");
        return found->second;
    }
    log("Model is not loaded, loading model...\n");

    VertexArrayData va;
    std::string compiled_path = path + ".compiled";
    std::ifstream compiled_file(compiled_path, std::ios::binary | std::ios::in);
    if (compiled_file.is_open() && file_last_modification_time(compiled_path) > file_last_modification_time(path)) {
        // The source asset has not changed since the last time it was compiled.
        // Read in the compiled file.
        log("Model has an up-to-date compiled version, loading that...\n");
        Reflector::unpack(compiled_file, va);
    } else {
        // Either a compiled asset does not exist (or it failed to open), or the source asset has changed since the last time it was compiled.
        // Compile the asset, and save it on disk.
        log("Model has no compiled version, compiling model and saving to disk...\n");
        std::ofstream new_compiled_file(compiled_path, std::ios::binary | std::ios::out);
        if (!new_compiled_file.is_open()) {
            fprintf(stderr, "ERROR: Failed to create new file \"%s\" when compiling model.\n", compiled_path.c_str());
            exit(EXIT_FAILURE);
        }
        MLModel model = MLModel::load(path, ML_COMPUTE_PHONG_NORMALS);
        MLModel_to_VertexArrayData(model, va);
        Reflector::pack(va, new_compiled_file);
    }
    auto vertex_array_resource = rm->new_resource<VertexArray>();
    *vertex_array_resource = VertexArray::from_vertex_array_data(va);
    // Cache this.
    vertex_array_cache[path] = vertex_array_resource;
    vertex_array_resource->asset_backed = true;
    log("Model found successfully.\n");
    return vertex_array_resource;
}

