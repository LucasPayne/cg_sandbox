#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include "core.h"


// Include the spatial_algebra library for vectors, matrices, and quaternions.
#include "spatial_algebra/spatial_algebra.h"
// This library knows nothing about serialization, so serialization of mathematical objects is declared here.
REFLECT_PRIMITIVE(vec3);
REFLECT_PRIMITIVE_DECLARE_GETTER(vec3);
REFLECT_PRIMITIVE(vec4);
REFLECT_PRIMITIVE_DECLARE_GETTER(vec4);
REFLECT_PRIMITIVE(mat4x4);
REFLECT_PRIMITIVE_DECLARE_GETTER(mat4x4);
REFLECT_PRIMITIVE(Quaternion);
REFLECT_PRIMITIVE_DECLARE_GETTER(Quaternion);


#endif // MATHEMATICS_H
