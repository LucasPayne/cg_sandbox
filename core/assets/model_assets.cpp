#include <limits>//numeric_limits
#include "assets/model_assets.h"
#include "gl/gl.h"
#include <sys/stat.h>

typedef std::vector<uint8_t> ByteArray;

size_t file_size(const std::string &path)
{
    //reference: https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
    struct stat stat_buffer;
    int return_code = stat(path.c_str(), &stat_buffer);
    if (return_code != 0) {
        fprintf(stderr, "ERROR: Failed to stat file size for file \"%s\".\n", path.c_str());
        exit(EXIT_FAILURE);
    }
    return stat_buffer.st_size;
}

bool load_bytes_from_file(const std::string &path, ByteArray &bytes)
{
    size_t size = file_size(path);
    bytes = ByteArray(size);
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);
    if (!file.is_open()) return false;
    file.read((char *) &bytes[0], size);
    file.close();
    return true;
}

bool MLModel_to_VertexArrayData(MLModel &model, VertexArrayData &va)
{
    // Convert the MLModel into VertexArrayData.
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
}

struct PODSArrayPtr {
    uint32_t offset;
    uint32_t size;
    PODSArrayPtr(uint32_t _offset, uint32_t _size) :
        offset{_offset}, size{_size}
    {}
};

struct PODS {
    // Using a PODS for serializing an object.
    template <typename T>
    static PODS object(const T &obj) {
        PODS pods;
        pods.buffer = std::vector<uint8_t>(sizeof(T));
        memcpy(&pods.buffer[0], &obj, sizeof(T));
        return pods;
    }
    // Deserialize a binary file by reading it into the PODS buffer.
    PODS() {}

    std::vector<uint8_t> buffer;

    template <typename VECTOR_OF>
    size_t pack_vector(size_t vector_entry_offset, const std::vector<VECTOR_OF> &vec) {
        size_t vector_data_offset = buffer.size();
        size_t vector_data_size = sizeof(VECTOR_OF) * vec.size();
        buffer.resize(vector_data_offset + vector_data_size);
        PODSArrayPtr array_ptr(vector_data_offset, vector_data_size);
        *((PODSArrayPtr *) &buffer[vector_entry_offset]) = array_ptr;
        memcpy(&buffer[vector_data_offset], &vec[0], vector_data_size);
        return vector_data_offset;
    }

    template <typename VECTOR_OF>
    std::vector<VECTOR_OF> unpack_vector(size_t vector_entry_offset, size_t *packed_offset = nullptr) {
        PODSArrayPtr array_ptr = *((PODSArrayPtr *) &buffer[vector_entry_offset]);
        if (packed_offset != nullptr) *packed_offset = array_ptr.offset;
        // printf("Unpacking offset:%zu, size:%zu\n", array_ptr.offset, array_ptr.size);getchar();
        // printf("%zu\n", array_ptr.size / sizeof(VECTOR_OF));
        std::vector<VECTOR_OF> vec = std::vector<VECTOR_OF>(array_ptr.size / sizeof(VECTOR_OF));
        // for (int i = 0; i < vec.size(); i++) {
        //     vec[i] = ((VECTOR_OF *) &buffer[array_ptr.offset])[i];
        // }
        if (packed_offset == nullptr) memcpy(&vec[0], &buffer[array_ptr.offset], array_ptr.size);
        return vec;
    }
};

bool VertexArrayData_compile(const VertexArrayData &vertex_array, std::ofstream &file)
{
    // Pack the vertex array data into a contiguous file.
    PODS pods = PODS::object<VertexArrayData>(vertex_array);
    pods.pack_vector<VertexSemantic>
        ((uint8_t *)&vertex_array.layout.semantics - (uint8_t *)&vertex_array, vertex_array.layout.semantics);
    size_t attribute_buffers_offset = pods.pack_vector<std::vector<uint8_t>>
        ((uint8_t *)&vertex_array.attribute_buffers - (uint8_t *)&vertex_array, vertex_array.attribute_buffers);
    pods.pack_vector<uint8_t>
        ((uint8_t *)&vertex_array.index_buffer - (uint8_t *)&vertex_array, vertex_array.index_buffer);

    // Deeper array references (e.g. arrays of arrays) are laid out in breadth first order.
    // First, array references in the flat struct, then in the members of those arrays, etc.
    for (int i = 0; i < vertex_array.attribute_buffers.size(); i++) {
        pods.pack_vector<uint8_t>(attribute_buffers_offset + i*sizeof(std::vector<uint8_t>), vertex_array.attribute_buffers[i]);
    }
    file.write((char *)&pods.buffer[0], pods.buffer.size());

    return true;
}
bool VertexArrayData_decompile(ByteArray &bytes, VertexArrayData &vertex_array)
{
    PODS pods;
    pods.buffer = bytes; //--does this copy?

    // VertexArrayData pods_vertex_array = *((VertexArrayData *) &pods.buffer[0]);
    VertexArrayData *pods_vertex_array = ((VertexArrayData *) &pods.buffer[0]);
    // printf("%u\n", pods_vertex_array->layout.num_vertices);
    vertex_array.layout.index_type = pods_vertex_array->layout.index_type;
    vertex_array.layout.num_vertices = pods_vertex_array->layout.num_vertices;
    vertex_array.layout.indexed = pods_vertex_array->layout.indexed;
    vertex_array.layout.num_indices = pods_vertex_array->layout.num_indices;
    vertex_array.layout.semantics = pods.unpack_vector<VertexSemantic>
        ((uint8_t *)&vertex_array.layout.semantics - (uint8_t *)&vertex_array);
    size_t attribute_buffers_offset;
    vertex_array.attribute_buffers = pods.unpack_vector<std::vector<uint8_t>>
        ((uint8_t *)&vertex_array.attribute_buffers - (uint8_t *)&vertex_array, &attribute_buffers_offset);
    vertex_array.index_buffer = pods.unpack_vector<uint8_t>
        ((uint8_t *)&vertex_array.index_buffer - (uint8_t *)&vertex_array);

    for (int i = 0; i < vertex_array.attribute_buffers.size(); i++) {
        vertex_array.attribute_buffers[i] = pods.unpack_vector<uint8_t>(attribute_buffers_offset + i*sizeof(std::vector<uint8_t>));
    }

    // size_t attribute_buffers_offset = pods.vector<std::vector<uint8_t>>
    //     ((uint8_t *)&vertex_array.attribute_buffers - (uint8_t *)&vertex_array, vertex_array.attribute_buffers);
    // pods.vector<uint8_t>
    //     ((uint8_t *)&vertex_array.index_buffer - (uint8_t *)&vertex_array, vertex_array.index_buffer);

    return true;
}

/*
struct VertexArrayLayout {
    GLenum index_type; // GL_UNSIGNED_{BYTE,SHORT,INT}
    uint32_t num_vertices;
    bool indexed;
    uint32_t num_indices;

    std::vector<VertexSemantic> semantics;
    size_t vertex_size() const;
    size_t index_type_size() const;
};
struct VertexArrayData {
    VertexArrayLayout layout;
    std::vector<std::vector<uint8_t>> attribute_buffers;
    std::vector<uint8_t> index_buffer; //note: uint8_t just signifies this is a byte-buffer.
*/

Resource<VertexArray> ModelAssets::load(const std::string &path)
{
    std::unordered_map<std::string, Resource<VertexArray>>::iterator found = vertex_array_cache.find(path);
    if (found != vertex_array_cache.end()) {
        // The model is already loaded. Return the already-compiled vertex array.
        return found->second;
    }

    VertexArrayData va;
    std::string compiled_path = path + ".compiled";
    ByteArray compiled_bytes;
    if (load_bytes_from_file(compiled_path, compiled_bytes)) {
        // Model is compiled, load it.
        VertexArrayData_decompile(compiled_bytes, va);
    } else {
        // Compile the asset.
        std::ofstream new_compiled_file(compiled_path, std::ios::binary | std::ios::out);
        MLModel model = MLModel::load(path, ML_COMPUTE_PHONG_NORMALS);
        MLModel_to_VertexArrayData(model, va);
        VertexArrayData_compile(va, new_compiled_file);
    }
    Resource<VertexArray> vertex_array_resource = VertexArray::from_vertex_array_data(*rm, va);
    // Cache this.
    vertex_array_cache[path] = vertex_array_resource;
    return vertex_array_resource;
}

