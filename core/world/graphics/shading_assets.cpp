#include "world/world.h"
#include <fstream>


ShadingProgram *ShadingAssets::get_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm) {
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
    auto new_program = world.resources.add<ShadingProgram>();
    *new_program = ShadingProgram::create(*gmat, *mat, *sm);
    shading_program_cache[key] = new_program;
    return &(*new_program);
}

Resource<GeometricMaterial> ShadingAssets::GeometricMaterialCache::compile(const std::string &path)
{
    Resource<GeometricMaterial> handle = world.resources.add<GeometricMaterial>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find GeometricMaterial asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(world.resources, file);
    return handle;
}

Resource<Material> ShadingAssets::MaterialCache::compile(const std::string &path)
{
    Resource<Material> handle = world.resources.add<Material>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(world.resources, file);
    return handle;
}

Resource<ShadingModel> ShadingAssets::ShadingModelCache::compile(const std::string &path)
{
    Resource<ShadingModel> handle = world.resources.add<ShadingModel>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(world.resources, file);
    return handle;
}
