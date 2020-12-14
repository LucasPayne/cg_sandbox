#version 420

uniform sampler2DArray image;
uniform ivec2 image_dimensions;
uniform int image_layer;

in vec2 uv;
out vec4 color;

void main(void)
{
    color = texelFetch(image, ivec3(ivec2(uv * image_dimensions), image_layer), 0);
}


