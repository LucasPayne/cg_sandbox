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




BoundingBox::BoundingBox(std::vector<vec3> points) : BoundingBox()
{
    for (auto p : points) {
        for (int i = 0; i < 3; i++) {
            if (p[i] < mins[i]) mins[i] = p[i];
            if (p[i] > maxs[i]) maxs[i] = p[i];
        }
    }
}


vec3 Frustum::point(float x, float y, float z)
{
    float px = (x * half_w)*(1 - z) + (x * half_w * f / n)*z;
    float py = (y * half_h)*(1 - z) + (y * half_h * f / n)*z;
    float pz = -((1 - z)*n + z*f);
    return position + orientation * vec3(px, py, pz);
}


mat4x4 Frustum::view_matrix()
{
    return mat4x4(position, orientation);
}
mat4x4 Frustum::projection_matrix()
{
    // The projection matrix maps the frustum defined by the four parameters into the canonical view volume, -1 <= x,y <= 1, 0 <= z <= 1.
    // This was derived with matrix algebra, proven correct!
    return mat4x4((f - n)/(f*half_w), 0,0,0,
                  0, (f - n)/(f*half_h), 0,0,
                  0,0, -1/n, (-f + n)/(f*n),
                  0,0, -1, 0);
}
mat4x4 Frustum::matrix()
{
    return projection_matrix() * view_matrix();
}
