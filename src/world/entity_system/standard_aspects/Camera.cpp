#include "world/entity_system/entity_system.h"


Camera::Camera(float _near_plane_distance, float _far_plane_distance, float _near_half_width, float _aspect_ratio) :
    near_plane_distance{_near_plane_distance},
    far_plane_distance{_far_plane_distance},
    near_half_width{_near_half_width},
    m_aspect_ratio{_aspect_ratio},
    rendering_to_screen{true},
    has_taa_buffer{false}
{
    float n = near_plane_distance;
    float f = far_plane_distance;
    float w = near_half_width;
    float h = m_aspect_ratio * near_half_width;

    projection_matrix = mat4x4((f - n)/(f*w), 0,0,0,
                               0, (f - n)/(f*h), 0,0,
                               0,0, -1/n, (-f + n)/(f*n),
                               0,0, -1, 0);
    bottom_left = vec2(0,0);
    top_right = vec2(1,1);
    layer = 0; // Default to highest-priority layer.

    background_color = vec4(0.9,0.9,0.9,1);

    depth_of_field = vec2(3.4, 10);
    enabled = true;
}

bool Camera::in_viewport(float screen_x, float screen_y)
{
    if (!rendering_to_screen) return false;
    return screen_x >= bottom_left.x() && screen_x <= top_right.x() &&
           screen_y >= bottom_left.y() && screen_y <= top_right.y();
}

float Camera::aspect_ratio() const
{
    return m_aspect_ratio;

    //----
    // width over height
    // float global_aspect_ratio = 0.566; //----This is just the current aspect ratio of the window subrectangle.
    // float sub_aspect_ratio = (top_right.y() - bottom_left.y()) / (top_right.x() - bottom_left.x());
    // return global_aspect_ratio * sub_aspect_ratio;
}

void Camera::to_viewport(float screen_x, float screen_y, float *camera_x, float *camera_y)
{
    *camera_x = (screen_x - bottom_left.x()) / (top_right.x() - bottom_left.x());
    *camera_y = (screen_y - bottom_left.y()) / (top_right.y() - bottom_left.y());
}

mat4x4 Camera::view_matrix()
{
    return entity.get<Transform>()->inverse_matrix();
}
mat4x4 Camera::view_projection_matrix()
{
    return projection_matrix * view_matrix();
}


vec3 Camera::frustum_point(float x, float y, float z)
{
    auto transform = entity.get<Transform>();
    float local_z = near_plane_distance + z*(far_plane_distance - near_plane_distance);
    return (transform->matrix() * vec4(local_z * vec3(x*near_half_width/near_plane_distance, y*near_half_width*m_aspect_ratio/near_plane_distance, -1), 1)).xyz();
}

Frustum Camera::frustum()
{
    auto transform = entity.get<Transform>();
    return Frustum(transform->position, transform->orientation(), near_plane_distance, far_plane_distance, near_half_width, m_aspect_ratio * near_half_width);
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
        vec4 corner_h = projection_matrix.solve(vec4(xs[i], ys[i], 0, 1));
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
    //...
END_ENTRIES()
