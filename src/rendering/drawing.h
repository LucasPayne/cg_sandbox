#ifndef DRAWING_H
#define DRAWING_H
/*--------------------------------------------------------------------------------
Drawing submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "resource_model/resource_model.h"

struct PropertySheet {
    std::vector<uint8_t> data;
    size_t size;
    bool in_sync;
    GLuint buffer_id;

    // Create a property sheet for a specific block. This matches the size of the block.
    static PropertySheet instantiate_from(ShadingBlock properties);

    // Synchronize application data with graphics data. This only uploads if a property changes.
    void synchronize();

    //todo: interface for setting properties.
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

struct Draw {
    Draw() {}//testing

    Draw(ResourceModel &rm, GeometricMaterialInstance &gi, MaterialInstance &mi, ShadingModelInstance &smi) :
        g_instance{&gi}, m_instance{&mi}, sm_instance{&smi}
    {
        resource_model = &rm;
        shading_program = ShadingProgram::create(rm, gi.base, mi.base, smi.base);
    }
    void draw();
private:
    GeometricMaterialInstance *g_instance;
    MaterialInstance *m_instance;
    ShadingModelInstance *sm_instance;

    Resource<ShadingProgram> shading_program;
    ResourceModel *resource_model;
};

#endif // DRAWING_H
