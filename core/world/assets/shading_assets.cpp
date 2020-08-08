#include "world/assets/shading_assets.h"
#include <fstream>

Resource<GeometricMaterial> ShadingAssets::load_geometric_material(const std::string &path)
{
    Resource<GeometricMaterial> handle = rm->new_resource<GeometricMaterial>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    return handle;
}
Resource<Material> ShadingAssets::load_material(const std::string &path)
{
    Resource<Material> handle = rm->new_resource<Material>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    return handle;
}
Resource<ShadingModel> ShadingAssets::load_shading_model(const std::string &path)
{
    Resource<ShadingModel> handle = rm->new_resource<ShadingModel>();
    std::fstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "ERROR: Failed to find asset.\n");
        exit(EXIT_FAILURE);
    }
    handle->load(file);
    return handle;
}
