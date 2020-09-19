#version 420

out vec4 fb_color;

uniform vec4 color;
uniform float antialiasing_extent;

in TES_OUT {
    vec2 quad_position;
} fs_in;

void main(void)
{
    float len = length(fs_in.quad_position);

    float alpha = 1-smoothstep(1 - antialiasing_extent, 1 + antialiasing_extent, len);
    fb_color = vec4(color.rgb, alpha);
}
