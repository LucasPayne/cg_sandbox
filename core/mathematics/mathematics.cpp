#include "mathematics/mathematics.h"


// spatial_algebra serialization implementations.
//--------------------------------------------------------------------------------
DESCRIPTOR_INSTANCE(vec3);
REFLECT_PRIMITIVE_PRINT(vec3) {
    vec3 val = *((vec3 *) &obj);
    out << name() << "(" << val.x() << ", " << val.y() << ", " << val.z() << ")";
}
REFLECT_PRIMITIVE_FLAT(vec3);


DESCRIPTOR_INSTANCE(vec4);
REFLECT_PRIMITIVE_PRINT(vec4) {
    vec4 val = *((vec4 *) &obj);
    out << name() << "(" << val.x() << ", " << val.y() << ", " << val.z() << ", " << val.w() << ")";
}
REFLECT_PRIMITIVE_FLAT(vec4);


DESCRIPTOR_INSTANCE(mat4x4);
REFLECT_PRIMITIVE_PRINT(mat4x4) {
    mat4x4 val = *((mat4x4 *) &obj);
    //todo
}
REFLECT_PRIMITIVE_FLAT(mat4x4);


DESCRIPTOR_INSTANCE(Quaternion);
REFLECT_PRIMITIVE_PRINT(Quaternion) {
    Quaternion val = *((Quaternion *) &obj);
    out << name() << "(" << val.scalar() << ", " << val.i() << ", " << val.j() << ", " << val.k() << ")";
}
REFLECT_PRIMITIVE_FLAT(Quaternion);
