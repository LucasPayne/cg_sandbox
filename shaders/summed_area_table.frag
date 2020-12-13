#version 420

uniform sampler2DArray image;
uniform int image_layer;
uniform ivec2 image_dimensions;

uniform int n;
uniform int is_vertical;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;

void main(void)
{
    ivec2 pixel = ivec2(uv*image_dimensions);
    ivec2 shift = is_vertical == 1 ? ivec2(0,-n) : ivec2(-n,0);
    ivec2 add_pixel = ivec2(uv*image_dimensions) + shift;
    if (add_pixel.x < 0 || add_pixel.y < 0) color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy, 0, 1);
    else color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy + texelFetch(image, ivec3(add_pixel, image_layer), 0).xy, 0, 1);
}


