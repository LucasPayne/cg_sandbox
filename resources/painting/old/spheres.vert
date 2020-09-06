#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in float radius;
layout (location = 2) in vec4 color;

out vertex {
    vec3 f_position;
    float f_radius;
    vec4 f_color;
    float sphere_radius;
};

uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;

void main(void)
{
    vec4 view_position = view_matrix * vec4(position, 1);
    /*--------------------------------------------------------------------------------
    The sphere imposter is only an approximation. The radius in NDC is approximated by transforming a point expected to become
    approximately on the circumference in NDC, then taking its length. This is used when transforming the single vertex patch into
    a quad with the tessellator.
    This appears to work well, at least with a regular camera projection.
    --------------------------------------------------------------------------------*/
    vec4 sphere_approximating_position = view_position + vec4(0,radius,0,0);
    vec4 position_homogeneous = projection_matrix * view_position;
    vec4 sphere_approximating_position_homogeneous = projection_matrix * sphere_approximating_position;
    vec3 approx_on_circumference = sphere_approximating_position_homogeneous.xyz / sphere_approximating_position_homogeneous.w;

    f_position = position_homogeneous.xyz / position_homogeneous.w;
    f_radius = length(approx_on_circumference - f_position);
    f_color = color;
    sphere_radius = radius;
}
