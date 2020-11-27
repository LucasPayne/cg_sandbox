#include "world/standard_aspects/standard_aspects.h"

DESCRIPTOR_INSTANCE(Drawable);
BEGIN_ENTRIES(Drawable)
    ENTRY(geometric_material)
    ENTRY(material)
END_ENTRIES()





mat4x4 Drawable::model_matrix()
{
    mat4x4 matrix = entity.get<Transform>()->matrix();
    // Since the model matrix is affine it is easy to shift its transformation for recentering.
    matrix.entry(0,3) -= center.x();
    matrix.entry(1,3) -= center.y();
    matrix.entry(2,3) -= center.z();
    return matrix;
}


mat3x3 Drawable::normal_matrix()
{
    return entity.get<Transform>()->rotation.matrix();
}
