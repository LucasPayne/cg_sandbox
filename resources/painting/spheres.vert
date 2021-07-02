#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in float radius;
layout (location = 2) in vec4 color;

out vertex {
    vec4 sphere_color;
    float sphere_radius;

    vec4 ndc_position;
    float ndc_y_extent;
    vec4 eye_position;
};

uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;

void main(void)
{
    eye_position = view_matrix * vec4(position, 1);
    /*--------------------------------------------------------------------------------
    The sphere imposter is only an approximation. The radius in NDC is approximated by transforming a point expected to become
    approximately on the circumference in NDC, then taking its length. This is used when transforming the single vertex patch into
    a quad with the tessellator.
    This appears to work well, at least with a regular camera projection.
    --------------------------------------------------------------------------------*/
    vec4 sphere_approximating_position = eye_position + vec4(0,radius,0,0);
    vec4 clip_position = projection_matrix * eye_position;
    vec4 sphere_approximating_clip_position = projection_matrix * sphere_approximating_position;
    vec4 approx_on_circumference = sphere_approximating_clip_position / sphere_approximating_clip_position.w;

    ndc_position = clip_position / clip_position.w;
    ndc_y_extent = length(approx_on_circumference - ndc_position);

    sphere_color = color;
    sphere_radius = radius;
}
