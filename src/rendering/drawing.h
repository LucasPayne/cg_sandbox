#ifndef DRAWING_H
#define DRAWING_H
/*--------------------------------------------------------------------------------
Drawing submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "resource_model/resource_model.h"


template <typename T>
struct GMSMInstance {
    Resource<T> base;
    void bind() {
        if (in_sync) return;
        glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_id);
        glBufferSubData(GL_UNIFORM_BUFFER, (GLintptr) 0, (GLsizeiptr) uniform_buffer_size, &data[0]);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        in_sync = true;
    }

    GLuint uniform_buffer_id;
    size_t uniform_buffer_size;

    bool in_sync;
    std::vector<uint8_t> data;

    GMSMInstance(Resource<T> _base) : base{_base} {
        // Create the uniform buffer object. This is a handle for globally accessible constant data in graphics memory.
        glGenBuffers
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
