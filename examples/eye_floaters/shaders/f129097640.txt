#version 420

uniform sampler2D sprite;

in vec2 f_uv;
out vec4 color;

void main(void)
{
    color = vec4(texture(sprite, f_uv).rgb, 1);
}
