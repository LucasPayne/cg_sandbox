#include "world/standard_aspects/standard_aspects.h"

void Camera::init_projective(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio)
{
    float n = near_plane_distance;
    float f = far_plane_distance;
    float w = near_half_width;
    float h = aspect_ratio * near_half_width;

    // The projection matrix maps the frustum defined by the four parameters into the canonical view volume, -1 <= x,y <= 1, 0 <= z <= 1.
    // This was derived with matrix algebra, proven correct!
    //---Details in projective geometry presentation.
    // note: Matrix given in column-major order.
    projection_matrix = mat4x4((f - n)/(f*w), 0,0,0,
                               0, (f - n)/(f*h), 0,0,
                               0,0, -1/n, (-f + n)/(f*n),
                               0,0, -1, 0);
    // The default is the full viewport.
    bottom_left[0] = 0.0;
    bottom_left[1] = 0.0;
    top_right[0] = 1.0;
    top_right[0] = 1.0;
}
