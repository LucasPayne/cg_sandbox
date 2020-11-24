#version 420

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out VS_OUT {
    vec3 position;
    vec3 normal;
} vs_out;

uniform mat4x4 mvp_matrix;

void main(void)
{
    vs_out.position = position;
    vs_out.normal = normal;

    gl_Position = mvp_matrix * position;
}
