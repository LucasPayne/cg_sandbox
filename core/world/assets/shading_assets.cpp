#include "world/world.h"
#include <fstream>

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
