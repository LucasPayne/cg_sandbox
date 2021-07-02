#include "mathematics/mathematics.h"
#include <iomanip>


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
    return mat4x4(position, orientation).inverse(); //----could do this faster and more stably since it is a rigid matrix.
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
