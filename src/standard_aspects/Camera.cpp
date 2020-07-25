#include "standard_aspects/standard_aspects.h"

void Camera::init_projective(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio)
{
    float n = near_plane_distance;
    float f = far_plane_distance;
    float w = near_half_width;
    float h = aspect_ratio * near_half_width;

    // The projection matrix maps the frustum defined by the four parameters into the canonical view volume, -1 <= x,y <= 1, 0 <= z <= 1.
    // This was derived with matrix algebra, proven correct!
    //---Details in projective geometry presentation.
    float projection_matrix_row_major[16] = {(f - n)/(f*w), 0,             0,              0,
                                             0,             (f - n)/(f*h), 0,              0,
                                             0,             0,             -1/n,          -1,
                                             0,             0,             (-f + n)/(f*n), 0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // The stored projection matrix is column-major, to match OpenGL/GLSL conventions.
            projection_matrix[4*j + i] = projection_matrix_row_major[4*i + j];
        }
    }
    // The default is the full viewport.
    bottom_left[0] = 0.0;
    bottom_left[1] = 0.0;
    top_right[0] = 1.0;
    top_right[0] = 1.0;
}
