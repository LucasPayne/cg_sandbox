#ifndef DRAWING_H
#define DRAWING_H
#include "mathematics/mathematics.h"

#include "graphics_resources/graphics_resources.h"

#include "world/resources/resources.h"


// note: This is currently being passed around by value, so the underlying buffer cannot be freed in the destructor.
//       So, this has an explicit destroy() function.
struct PropertySheet {
    Resource<ShadingBlock> block;
    std::vector<uint8_t> data;
    size_t size;
    bool in_sync;
    GLuint buffer_id;

    PropertySheet() : size{0}, buffer_id{0} {} // null

    // Create a property sheet for a specific block. This matches the size of the block.
    PropertySheet(Resource<ShadingBlock> properties);

    // Synchronize application data with graphics data. This only uploads if a property changes.
    void synchronize();

    // Interface for setting properties.
    // These functions use a string hash, which might not be ideal for properties which change a lot.
    // -----!-IMPORTANT-! todo: make sure that the entry is the correct type!
    inline void set_float(const std::string &name, float val) {
        size_t offset = block->entry_layout[name].offset;
        *((float *) &data[offset]) = val;
        in_sync = false;
    }
    inline void set_vec3(const std::string &name, float a, float b, float c) {
        size_t offset = block->entry_layout[name].offset;
        ((float *) &data[offset])[0] = a;
        ((float *) &data[offset])[1] = b;
        ((float *) &data[offset])[2] = c;
        in_sync = false;
    }
    inline void set_vec3(const std::string &name, const vec3 &v) {
        size_t offset = block->entry_layout[name].offset;
        *((vec3 *) &data[offset]) = v;
        in_sync = false;
    }
    inline void set_vec4(const std::string &name, float a, float b, float c, float d) {
        size_t offset = block->entry_layout[name].offset;
        ((float *) &data[offset])[0] = a;
        ((float *) &data[offset])[1] = b;
        ((float *) &data[offset])[2] = c;
        ((float *) &data[offset])[3] = d;
        in_sync = false;
    }
    inline void set_vec4(const std::string &name, const vec4 &v) {
        size_t offset = block->entry_layout[name].offset;
        *((vec4 *) &data[offset]) = v;
        in_sync = false;
    }
    inline void set_mat4x4(const std::string &name, const mat4x4 &M) {
        size_t offset = block->entry_layout[name].offset;
        *((mat4x4 *) &data[offset]) = M;
        in_sync = false;
    }
    inline void set_mat3x3(const std::string &name, const mat3x3 &M) {
        size_t offset = block->entry_layout[name].offset;
        *((mat3x3 *) &data[offset]) = M;
        in_sync = false;
    }

    inline void destroy() {
        glDeleteBuffers(1, &buffer_id);
    }
};
REFLECT_STRUCT(PropertySheet)


template <typename T>
struct GMSMInstance {
    Resource<T> base;
    PropertySheet properties;

    GMSMInstance() {}

    GMSMInstance(Resource<T> _base) : base{_base} {
        // Instantiate a property sheet if the base material has any properties.
        if (base->has_properties) {
            properties = PropertySheet(base->properties);
        } else {
            properties.size = 0;
            properties.buffer_id = 0;
        }
    }
};


struct GeometricMaterialInstance : public GMSMInstance<GeometricMaterial> {
    Resource<VertexArray> vertex_array;

    GeometricMaterialInstance() {}

    GeometricMaterialInstance(Resource<GeometricMaterial> _base, Resource<VertexArray> _vertex_array) :
        GMSMInstance<GeometricMaterial>(_base), vertex_array{_vertex_array}
    {}
};
REFLECT_STRUCT(GeometricMaterialInstance);

struct MaterialInstance : public GMSMInstance<Material> {

    MaterialInstance() {}

    MaterialInstance(Resource<Material> _base) :
        GMSMInstance<Material>(_base)
    {}
};
REFLECT_STRUCT(MaterialInstance);


struct ShadingModelInstance : public GMSMInstance<ShadingModel> {

    ShadingModelInstance() {}

    ShadingModelInstance(Resource<ShadingModel> _base) :
        GMSMInstance<ShadingModel>(_base)
    {}
};
REFLECT_STRUCT(ShadingModelInstance);


#endif // DRAWING_H
