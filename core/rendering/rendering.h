#ifndef RENDERING_H
#define RENDERING_H
/*--------------------------------------------------------------------------------
Rendering module.
Submodules:
    Shading:
        Provides rendering resources:
            GeometricMaterial - Describes geometry-processing dataflow, taking a vertex array
                                and global data and giving outputs (for example, a triangle mesh).
            Material          - Describes per-fragment outputs, which can be understood by ShadingModels
                                (for example, modulated diffuse from a texture).
            ShadingModel      - Describes geometry-post-processing (such as a screenspace transformation),
                                definition of clip position, and final fragment processing.
            ShadingProgram    - Encapsulates a GPU rasterization dataflow resolved from a GM+M+SM triple.
    Vertex arrays:
        Provides rendering resources:
            VertexArray
    Drawing:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"


#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "rendering/drawing.h"


// Graphics state is kept in the "Graphics" class, which uses the resource model.
//--------------------------------------------------------------------------------
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

class Graphics {
public:
    ShadingProgram *get_shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm);

    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);
    ResourceModel *rm;
private:
    ShadingProgramCache shading_program_cache;
};

#endif // RENDERING_H
