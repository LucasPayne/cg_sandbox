#ifndef DRAWING_H
#define DRAWING_H
/*--------------------------------------------------------------------------------
Drawing submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "resource_model/resource_model.h"
#include "mathematics/mathematics.h"

struct PropertySheet {
    ShadingBlock *block;
    std::vector<uint8_t> data;
    size_t size;
    bool in_sync;
    GLuint buffer_id;

    // Create a property sheet for a specific block. This matches the size of the block.
    static PropertySheet instantiate_from(ShadingBlock &properties);

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
        *(((float *) &data[offset]) + 0) = a;
        *(((float *) &data[offset]) + 1) = b;
        *(((float *) &data[offset]) + 2) = c;
        in_sync = false;
    }
    inline void set_vec3(const std::string &name, const vec3 &v) {
        size_t offset = block->entry_layout[name].offset;
        *((vec3 *) &data[offset]) = v;
        in_sync = false;
    }
    inline void set_vec4(const std::string &name, float a, float b, float c, float d) {
        size_t offset = block->entry_layout[name].offset;
        *(((float *) &data[offset]) + 0) = a;
        *(((float *) &data[offset]) + 1) = b;
        *(((float *) &data[offset]) + 2) = c;
        *(((float *) &data[offset]) + 3) = d;
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
};

template <typename T>
struct GMSMInstance {
    Resource<T> base;
    PropertySheet properties;
    GMSMInstance(Resource<T> _base) : base{_base} {
        // Instantiate a property sheet if the base material has any properties.
        if (base->has_properties) {
            properties = PropertySheet::instantiate_from(base->properties);
        } else {
            properties.size = 0;
            properties.buffer_id = 0;
            properties.block = nullptr;
        }
    }
};
struct GeometricMaterialInstance : public GMSMInstance<GeometricMaterial> {
    Resource<VertexArray> vertex_array;

    GeometricMaterialInstance(Resource<GeometricMaterial> _base, Resource<VertexArray> _vertex_array) :
        GMSMInstance<GeometricMaterial>(_base), vertex_array{_vertex_array}
    {}
};
struct MaterialInstance : public GMSMInstance<Material> {
    MaterialInstance(Resource<Material> _base) :
        GMSMInstance<Material>(_base)
    {}
};
struct ShadingModelInstance : public GMSMInstance<ShadingModel> {
    ShadingModelInstance(Resource<ShadingModel> _base) :
        GMSMInstance<ShadingModel>(_base)
    {}
};

#endif // DRAWING_H
