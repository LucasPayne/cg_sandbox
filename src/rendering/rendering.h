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
#include "resource_model/resource_model.h"

#include "rendering/glsl.h"
#include "rendering/shading.h"
#include "rendering/vertex_arrays.h"
#include "rendering/drawing.h"

// Rendering state is kept in the "Renderer" class.
typedef std::tuple<TableEntryID,TableEntryID,TableEntryID> ShadingProgramHash;
typedef std::unordered_map<ShadingProgramHash, Resource<ShadingProgram>> ShadingProgramCache;
class Renderer {
public:
    ShadingProgram *shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm);
private:
    ResourceModel *rm;
    ShadingProgramCache shading_program_cache;
};

#endif // RENDERING_H

