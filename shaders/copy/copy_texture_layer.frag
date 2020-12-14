#version 420

uniform sampler2DArray image;
uniform ivec2 image_dimensions;
uniform int image_layer;

uniform vec2 average_moments;

in vec2 uv;
out vec4 color;

void main(void)
{
    vec2 moments = texelFetch(image, ivec3(ivec2(uv * image_dimensions), image_layer), 0).xy;
    color = vec4(moments - average_moments, 0, 1);
}


