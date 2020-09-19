#version 420
layout (location = 0) out vec4 fb_color;

uniform vec4 color;

void main(void)
{
    fb_color = color;
}
