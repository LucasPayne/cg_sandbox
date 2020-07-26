/*--------------------------------------------------------------------------------
    Rendering module implementations.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"

ShadingProgram *Renderer::shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm) {
    // First, try to find the program based on the IDs of the resource handles.
    ShadingProgramHash hash(gmat.id, mat.id, sm.id);
    ShadingProgramCache::const_iterator found = shading_program_cache.find(hash);
    if (found != shading_program_cache.end()) {
        // Found the program directly in the cache, just return it.
        return &(*(found->second)); //* dereferences handle to a reference, then & gets a regular pointer.
    }
    // If this doesn't work, the program might still be compiled, just with G/M/SM under a different ID (if they have been unloaded then reloaded).
    //    -todo
    // It is not cached, so compile the program and cache it.
    Resource<ShadingProgram> new_program = ShadingProgram::create(*rm, gmat, mat, sm);
    shading_program_cache[hash] = new_program;
    return &(*new_program);
}
