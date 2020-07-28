/*--------------------------------------------------------------------------------
    Rendering module implementations.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"

ShadingProgram *Graphics::get_shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm) {
    // First, try to find the program based on the IDs of the resource handles.
    ShadingProgramKey key(gmat, mat, sm);
    ShadingProgramCache::iterator found = shading_program_cache.find(key);
    if (found != shading_program_cache.end()) {
        // Found the program directly in the cache, just return it.
        return &(*(found->second)); //* dereferences handle to a reference, then & gets a regular pointer.
    }
    // If this doesn't work, the program might still be compiled, just with G/M/SM under a different ID (if they have been unloaded then reloaded).
    //    -todo
    // It is not cached, so compile the program and cache it.
    Resource<ShadingProgram> new_program = ShadingProgram::create(*rm, gmat, mat, sm);
    shading_program_cache[key] = new_program;
    return &(*new_program);
}

void Graphics::draw(GeometricMaterialInstance &geometric_material_instance,
                    MaterialInstance &material_instance,
                    ShadingModelInstance &shading_model_instance)
{
    ShadingProgram *shading_program = get_shading_program(geometric_material_instance.base,
                                                          material_instance.base,
                                                          shading_model_instance.base);
    GeometricMaterial &geometric_material = *(geometric_material_instance.base);
    Material &material = *(material_instance.base);
    ShadingModel &shading_model = *(shading_model_instance.base);

    glUseProgram(shading_program->program_id);
    glBindVertexArray(geometric_material_instance.vertex_array->gl_vao_id);

    // Bind property sheets.
    // First, make sure that the data in graphics memory is up-to-date.
    // Then, bind the property sheet buffers to the reserved binding points, 0, 1, and 2.
    //     0: GeometricMaterial properties
    //     1: Material properties
    //     2: ShadingModel properties
    if (geometric_material.has_properties) {
        geometric_material_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, geometric_material_instance.properties.buffer_id);
    }
    if (material.has_properties) {
        material_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, material_instance.properties.buffer_id);
    }
    if (shading_model.has_properties) {
        shading_model_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, shading_model_instance.properties.buffer_id);
    }

    GLenum primitive_type = geometric_material_instance.base->primitive;
    VertexArrayLayout &layout = geometric_material_instance.vertex_array->layout;
    if (layout.indexed) {
        glDrawElements(primitive_type,
                       (GLsizei) layout.num_indices,
                       layout.index_type,
                       (const void *) 0);
    } else {
        glDrawArrays(primitive_type,
                     (GLint) 0,
                     (GLsizei) layout.num_vertices);
    }
    // Unbind OpenGL state.
    glUseProgram(0);
    
}
