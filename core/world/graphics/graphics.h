#ifndef GRAPHICS_H
#define GRAPHICS_H
/*--------------------------------------------------------------------------------
The Graphics component of the world holds graphics state, such as compiled shaders,
and is the interface through which things are drawn.
--------------------------------------------------------------------------------*/
#include "core.h"

#include "world/resource_model/resource_model.h"
#include "world/graphics/drawing.h"

// Shading programs, compiled from a GeometricMaterial+Material+ShadingModel, are cached.
struct ShadingProgramKey {
    TableEntryID gmat_id;
    TableEntryID mat_id;
    TableEntryID sm_id;
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


/*--------------------------------------------------------------------------------
Graphics
--------------------------------------------------------------------------------*/
class Graphics {
public:
    Graphics(ResourceModel *_rm) :
        rm{_rm}
    {}
    Graphics() {}

    ShadingProgram *get_shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm);

    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);

private:
    ResourceModel *rm;
    ShadingProgramCache shading_program_cache;
};



#endif // GRAPHICS_H
