#version 420

uniform sampler2DArray sprite;
uniform int layer;

in vec2 f_uv;
out vec4 color;

void main(void)
{
    color = vec4(texture(sprite, vec3(f_uv, layer)).rgb, 1);
}
