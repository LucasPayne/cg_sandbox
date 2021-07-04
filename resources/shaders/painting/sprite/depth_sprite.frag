#version 420

uniform sampler2D depth_map;

in vec2 f_uv;
out vec4 color;

void main(void)
{
    float depth = texture(depth_map, f_uv).r;
    color = vec4(vec3(depth), 1);
}

