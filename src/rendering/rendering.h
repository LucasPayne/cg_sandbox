#ifndef RENDERING_H
#define RENDERING_H
#include "gl/gl.h"
namespace Rendering {


enum class PrimitiveType {
    Triangles
};
class GeometricMaterial {
    PrimitiveType primitive_type;
};
class Material {

};
class ShadingModel {

};

static std::vector<GeometricMaterial> geometric_materials;
static std::vector<Material> materials;
static std::vector<ShadingModel> shading_models;


} // namespace Rendering
#endif // RENDERING_H

