#ifndef DRAWING_H
#define DRAWING_H
/*--------------------------------------------------------------------------------
Drawing submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "resource_model/resource_model.h"

struct PropertySheet {

};

struct GeometricMaterialInstance {
    Resource<GeometricMaterial> base;
    Resource<VertexArray> vertex_array;
    PropertySheet properties;

    GeometricMaterialInstance(Resource<GeometricMaterial> _base, Resource<VertexArray> _vertex_array) :
        base{_base}, vertex_array{_vertex_array}
    {}
};


struct MaterialInstance {
    Resource<Material> base;
    PropertySheet properties;

    MaterialInstance(Resource<Material> _base) :
        base{_base}
    {}
};
struct ShadingModelInstance {
    Resource<ShadingModel> base;
    PropertySheet properties;

    ShadingModelInstance(Resource<ShadingModel> _base) :
        base{_base}
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
