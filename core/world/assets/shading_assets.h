#ifndef SHADING_ASSETS_H
#define SHADING_ASSETS_H
#include "core.h"
#include "world/resource_model/resource_model.h"
#include "rendering/shading.h"

class ShadingAssets {
public:
    Resource<GeometricMaterial> load_geometric_material(const std::string &path);
    Resource<Material> load_material(const std::string &path);
    Resource<ShadingModel> load_shading_model(const std::string &path);
    ResourceModel *rm;
private:
};

#endif // SHADING_ASSETS_H
