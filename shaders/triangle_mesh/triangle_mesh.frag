#version 420

uniform vec4 diffuse;

layout (location = 0) out vec3 gbuffer_position;
layout (location = 1) out vec3 gbuffer_normal;
layout (location = 2) out vec4 gbuffer_diffuse;

in VS_OUT {
    vec3 position;
    vec3 normal;
} fs_in;

void main(void)
{
    gbuffer_position = fs_in.position;
    gbuffer_normal = fs_in.normal;
    gbuffer_diffuse = diffuse;
}

