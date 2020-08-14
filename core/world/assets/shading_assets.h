#ifndef SHADING_ASSETS_H
#define SHADING_ASSETS_H
#include "core.h"
#include "world/resources/resources.h"
#include "graphics_resources/shading.h"

class ShadingAssets {
public:
    Resource<GeometricMaterial> load_geometric_material(const std::string &path);
    Resource<Material> load_material(const std::string &path);
    Resource<ShadingModel> load_shading_model(const std::string &path);
    Resources *resources;
private:
    std::unordered_map<std::string, Resource<GeometricMaterial>> geometric_material_cache;
    std::unordered_map<std::string, Resource<Material>> material_cache;
    std::unordered_map<std::string, Resource<ShadingModel>> shading_model_cache;
};

#endif // SHADING_ASSETS_H
