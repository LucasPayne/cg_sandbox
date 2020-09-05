#ifndef SHADING_ASSETS_H
#define SHADING_ASSETS_H
#include "core.h"
#include "world/resources/resources.h"
#include "graphics_resources/shading.h"

#include "world/resource_cache.h"


class ShadingAssets {
public:
    ShadingAssets(World &_world) :
        geometric_materials(_world),
        materials(_world),
        shading_models(_world),
        world{_world}
    {}

    struct GeometricMaterialCache : public ResourceCache<GeometricMaterial> {
        GeometricMaterialCache(World &_world) : ResourceCache<GeometricMaterial>(_world) {}
        Resource<GeometricMaterial> compile(const std::string &path);
    };
    GeometricMaterialCache geometric_materials;
    struct MaterialCache : public ResourceCache<Material> {
        MaterialCache(World &_world) : ResourceCache<Material>(_world) {}
        Resource<Material> compile(const std::string &path);
    };
    MaterialCache materials;
    struct ShadingModelCache : public ResourceCache<ShadingModel> {
        ShadingModelCache(World &_world) : ResourceCache<ShadingModel>(_world) {}
        Resource<ShadingModel> compile(const std::string &path);
    };
    ShadingModelCache shading_models;
private:
    World &world;
};


#endif // SHADING_ASSETS_H
