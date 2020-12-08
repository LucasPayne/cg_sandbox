#version 420

uniform sampler2DArray depth_map;
uniform int layer;

in vec2 f_uv;
out vec4 color;

void main(void)
{
    float depth = texture(depth_map, vec3(f_uv, layer)).r;
    color = vec4(vec3(depth), 1);
}

