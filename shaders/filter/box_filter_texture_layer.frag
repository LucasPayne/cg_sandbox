#version 420

uniform sampler2DArray image;
uniform int image_layer;
uniform ivec2 image_dimensions;
uniform int n;
uniform float inv_2n_plus_1;
uniform int axis;

in vec2 uv;
out vec4 color;

void main(void)
{
    ivec2 shift = axis == 0 ? ivec2(1,0) : ivec2(0,1);
    vec4 total = vec4(0);
    for (int i = -n; i <= n; i++) {
        ivec2 sample_texel = clamp(ivec2(uv * image_dimensions) + i*shift, ivec2(0), image_dimensions-1);
        total += inv_2n_plus_1 * texelFetch(image, ivec3(sample_texel, image_layer), 0);
    }
    color = total;
}


