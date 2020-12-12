#version 420

uniform sampler2DArray image;
uniform int image_layer;
uniform ivec2 image_dimensions;

uniform int n;
uniform bool is_vertical;

in vec2 uv;
out vec4 color;

void main(void)
{
    if (is_vertical) {
        ivec2 pixel = ivec2(uv*image_dimensions);
        ivec2 add_pixel = ivec2(uv*image_dimensions - vec2(0,n));
        if (add_pixel.y < 0) color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy, 0, 1);
        else color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy + texelFetch(image, ivec3(add_pixel, image_layer), 0).xy, 0, 1);
    } else {
        ivec2 pixel = ivec2(uv*image_dimensions);
        ivec2 add_pixel = ivec2(uv*image_dimensions - vec2(n,0));
        if (add_pixel.x < 0) color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy, 0, 1);
        else color = vec4(texelFetch(image, ivec3(pixel, image_layer), 0).xy + texelFetch(image, ivec3(add_pixel, image_layer), 0).xy, 0, 1);
    }
    color = texelFetch(image, ivec3(uv*image_dimensions, image_layer), 0);
    // color = texture(image, vec3(uv, image_layer));
}


