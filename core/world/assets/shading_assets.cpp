#include "world/assets/shading_assets.h"
#include <fstream>

Resource<GeometricMaterial> ShadingAssets::load_geometric_material(const std::string &path)
{
    auto found = geometric_material_cache.find(path);
    if (found != geometric_material_cache.end()) {
        // Found in cache.
        return found->second;
    }
    Resource<GeometricMaterial> handle = rm->new_resource<GeometricMaterial>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find GeometricMaterial asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    // Cache this.
    geometric_material_cache[path] = handle;
    handle->asset_backed = true;
    return handle;
}
Resource<Material> ShadingAssets::load_material(const std::string &path)
{
    auto found = material_cache.find(path);
    if (found != material_cache.end()) {
        // Found in cache.
        return found->second;
    }
    Resource<Material> handle = rm->new_resource<Material>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    // Cache this.
    material_cache[path] = handle;
    handle->asset_backed = true;
    return handle;
}
Resource<ShadingModel> ShadingAssets::load_shading_model(const std::string &path)
{
    auto found = shading_model_cache.find(path);
    if (found != shading_model_cache.end()) {
        // Found in cache.
        return found->second;
    }
    Resource<ShadingModel> handle = rm->new_resource<ShadingModel>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    // Cache this.
    shading_model_cache[path] = handle;
    handle->asset_backed = true;
    return handle;
}
