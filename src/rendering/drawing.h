#ifndef DRAWING_H
#define DRAWING_H
/*--------------------------------------------------------------------------------
Drawing submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"

struct PropertySheet {

};

struct GeometricMaterialInstance {
    Resource<GeometricMaterial> base;
    Resource<VertexArray> vertex_array;
    PropertySheet properties;
};
struct MaterialInstance {
    Resource<Material> base;
    PropertySheet properties;
};
struct ShadingModelInstance {
    Resource<ShadingModel> base;
    PropertySheet properties;
};

#if 0
struct Draw {
    Draw(ResourceModel &rm, GeometricMaterialInstance &gi, MaterialInstance &mi, ShadingModelInstance &smi) :
        g_instance{&gi}, m_instance{&mi}, sm_instance{&smi}
    {
        resource_model = &rm;
        shading_program = ShadingProgram::create(rm, gi, mi, smi);
        g_instance = rm.get_resource<GeometricMaterial>(
    }
    void draw() {
        VertexArray *vertex_array = resource_model->get_resource<VertexArray>(g_instance->vertex_array);
        GeometricMaterial *gmat = resource_model->get_resource<GeometricMaterial>(g_instance->base);
        if (g_instance->indexed) {
            glDrawElements(gmat->primitive, //mode
                           g_instance->vertex_array.num_indices, // count
                           g_instance->vertex_array.index_type, // type (GL_UNSIGNED_{BYTE,SHORT,INT})
                           (const void *) g_instance->vertex_array.indices_starting_index);
        } else {
            glDrawArrays(g_instance->primitive, //mode
                         g_instance->vertex_array.vertices_starting_index //first
                         g_instance->vertex_array.num_vertices); // count
        }
    }
private:
    GeometricMaterialInstance *g_instance;
    MaterialInstance *m_instance;
    ShadingModelInstance *sm_instance;

    Resource<ShadingProgram> shading_program;
    ResourceModel *resource_model;
};
#endif

#endif // DRAWING_H
