#ifndef GRAPHICS_RESOURCES_H
#define GRAPHICS_RESOURCES_H
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
--------------------------------------------------------------------------------*/
#include "core.h"
#include "opengl_utilities/gl.h"

#include "graphics_resources/shading.h"
#include "graphics_resources/vertex_arrays.h"


#endif // GRAPHICS_RESOURCES_H
