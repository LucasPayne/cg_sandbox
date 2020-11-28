#include "mathematics/mathematics.h"
#include <iomanip>

// spatial_algebra serialization implementations.
//--------------------------------------------------------------------------------
DESCRIPTOR_INSTANCE(vec3);
REFLECT_PRIMITIVE_PRINT(vec3) {
    vec3 val = *((vec3 *) &obj);
    out << std::fixed << std::setprecision(2);
    out << name() << "(" << val.x() << ", " << val.y() << ", " << val.z() << ")";
}
REFLECT_PRIMITIVE_FLAT(vec3);
REFLECT_PRIMITIVE_APPLY_TRIVIAL(vec3);


DESCRIPTOR_INSTANCE(vec4);
REFLECT_PRIMITIVE_PRINT(vec4) {
    vec4 val = *((vec4 *) &obj);
    out << std::fixed << std::setprecision(2);
    out << name() << "(" << val.x() << ", " << val.y() << ", " << val.z() << ", " << val.w() << ")";
}
REFLECT_PRIMITIVE_FLAT(vec4);
REFLECT_PRIMITIVE_APPLY_TRIVIAL(vec4);


DESCRIPTOR_INSTANCE(mat4x4);
REFLECT_PRIMITIVE_PRINT(mat4x4) {
    mat4x4 matrix = *((mat4x4 *) &obj);
    out << name() << "{\n";
    out << std::fixed << std::setprecision(2);
    for (int i = 0; i < 4; i++) {
        out << std::string(4*(indent_level+1), ' ') << "[";
        for (int j = 0; j < 4; j++) {
            out << matrix.entry(i, j);
            if (j < 3) out << "  ";
        }
        out << "]\n";
    }
    out << std::string(4*indent_level, ' ') << "}";
}
REFLECT_PRIMITIVE_FLAT(mat4x4);
REFLECT_PRIMITIVE_APPLY_TRIVIAL(mat4x4);


DESCRIPTOR_INSTANCE(Quaternion);
REFLECT_PRIMITIVE_PRINT(Quaternion) {
    Quaternion val = *((Quaternion *) &obj);
    out << std::fixed << std::setprecision(2);
    out << name() << "(" << val.scalar() << ", " << val.i() << ", " << val.j() << ", " << val.k() << ")";
}
REFLECT_PRIMITIVE_FLAT(Quaternion);
REFLECT_PRIMITIVE_APPLY_TRIVIAL(Quaternion);


std::ostream &operator<<(std::ostream &os, const Ray &ray)
{
    os << "Ray(" << ray.origin << " -> " << ray.direction << ")";
    return os;
}


float saturate(float x, float minimum, float maximum)
{
    if (x < minimum) return minimum;
    if (x > maximum) return maximum;
    return x;
}



BoundingBox::BoundingBox(std::vector<vec3> points) : BoundingBox()
{
    for (auto p : points) {
        for (int i = 0; i < 3; i++) {
            if (p[i] < mins[i]) mins[i] = p[i];
            if (p[i] > maxs[i]) maxs[i] = p[i];
        }
    }
}
