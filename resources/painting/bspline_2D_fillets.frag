#version 420


uniform vec4 color;
out vec4 fb_color;


in GS_OUT {
    vec2 quad_position;
} fs_in;


void main(void)
{
    //todo: antialiasing that matches the line segments.
    if (dot(fs_in.quad_position, fs_in.quad_position) > 1) discard;
    fb_color = color;
}
