#ifndef SHADING_ASSETS_H
#define SHADING_ASSETS_H
#include "core.h"
#include "world/resources/resources.h"
#include "graphics_resources/shading.h"

#include "world/resource_cache.h"


// Shading programs, compiled from a GeometricMaterial+Material+ShadingModel, are cached.
struct ShadingProgramKey {
    TableElementID gmat_id;
    TableElementID mat_id;
    TableElementID sm_id;
    ShadingProgramKey(const Resource<GeometricMaterial> &gmat, const Resource<Material> &mat, const Resource<ShadingModel> &sm) :
        gmat_id{gmat.ID()}, mat_id{mat.ID()}, sm_id{sm.ID()}
    {}
    bool operator==(const ShadingProgramKey &other) const {
        return (gmat_id == other.gmat_id) && (mat_id == other.mat_id) && (sm_id == other.sm_id);
    }
};
struct ShadingProgramHasher {
    size_t operator()(const ShadingProgramKey &key) const {
        //--todo: Choose a good hash function for u32,u32,u32 -> u64
        return 310921*key.gmat_id + 313101*key.mat_id + 233011*key.sm_id;
    }
};
typedef std::unordered_map<ShadingProgramKey, Resource<ShadingProgram>, ShadingProgramHasher> ShadingProgramCache;


class ShadingAssets {
public:
    ShadingAssets(Graphics &_graphics, World &_world) :
        geometric_materials(_world),
        materials(_world),
        shading_models(_world),
        graphics{_graphics},
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


    ShadingProgram *get_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm);
private:
    ShadingProgramCache shading_program_cache;
    Graphics &graphics;
    World &world;
};


#endif // SHADING_ASSETS_H
