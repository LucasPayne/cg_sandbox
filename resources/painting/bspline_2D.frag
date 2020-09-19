#version 420


uniform vec4 color;
out vec4 fb_color;

in GS_OUT {
    vec2 quad_position;
} fs_in;

void main(void)
{
    fb_color = color;
}
