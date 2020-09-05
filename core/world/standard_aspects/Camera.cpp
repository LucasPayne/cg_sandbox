#include "world/standard_aspects/standard_aspects.h"


Camera::Camera(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio)
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
    rendering_to_framebuffer = true;
    bottom_left[0] = 0.0;
    bottom_left[1] = 0.0;
    top_right[0] = 1.0;
    top_right[1] = 1.0;
    layer = 0; // Default to highest-priority layer.

    background_color = vec4(0,0,1,1);
}

bool Camera::in_viewport(float screen_x, float screen_y)
{
    if (!rendering_to_framebuffer) return false;
    return screen_x >= bottom_left[0] && screen_x <= top_right[0] &&
           screen_y >= bottom_left[1] && screen_y <= top_right[1];
}

void Camera::to_viewport(float screen_x, float screen_y, float *camera_x, float *camera_y)
{
    *camera_x = (screen_x - bottom_left[0]) / (top_right[0] - bottom_left[0]);
    *camera_y = (screen_y - bottom_left[1]) / (top_right[1] - bottom_left[1]);
}

mat4x4 Camera::view_projection_matrix()
{
    return projection_matrix * entity.get<Transform>()->inverse_matrix();
}



Ray Camera::ray(float camera_x, float camera_y)
{
    // Use the inverse projection matrix to find the ray directed toward (camera_x, camera_y) on the near plane.
    // The near plane is mapped to x,y -1 to 1 and z = 0.

    // bl, br, tr, tl
    float xs[4] = {-1, 1, 1, -1};
    float ys[4] = {-1, -1, 1, 1};
    vec3 near_plane[4];
    for (int i = 0; i < 4; i++) {
        vec4 corner_h = projection_matrix.solve(vec4(xs[i],ys[i],0, 1));
        near_plane[i] = corner_h.xyz() / corner_h.w();
    }
    // Bilinearly interpolate the "near plane" quad.
    vec3 A = vec3::lerp(near_plane[0], near_plane[1], camera_x);
    vec3 B = vec3::lerp(near_plane[3], near_plane[2], camera_x);

    vec3 P = vec3::lerp(A, B, camera_y);

    auto transform = entity.get<Transform>();
    mat4x4 matrix = transform->matrix();

    auto ray = Ray(transform->position, (matrix * vec4(P, 1)).xyz() - transform->position);
    ray.normalize();
    return ray;
}



DESCRIPTOR_INSTANCE(Camera);
BEGIN_ENTRIES(Camera)
    ENTRY(projection_matrix)
END_ENTRIES()
