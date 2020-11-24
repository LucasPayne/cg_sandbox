#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in int edge_is_boundary;

uniform mat4x4 vp_matrix;
uniform mat4x4 model_matrix;

out VS_OUT {
    vec3 position;
    vec2 screen_position;
    int edge_is_boundary;
} vs_out;

uniform int viewport_width;
uniform int viewport_height;

void main(void)
{
    gl_Position = vp_matrix * model_matrix * vec4(position, 1);
    vs_out.position = position; // Pass position to the geometry shader.

    vs_out.screen_position = gl_Position.xy / gl_Position.w;
    vs_out.edge_is_boundary = edge_is_boundary;
}
