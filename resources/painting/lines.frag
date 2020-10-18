#version 420

uniform vec4 color;

layout (location = 0) out vec4 fb_color;

void main(void)
{
    fb_color = color;
}
