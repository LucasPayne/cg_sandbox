#version 420

uniform sampler2DArray image;
uniform int image_layer;

in vec2 uv;
out vec4 color;

void main(void)
{
    color = texture(image, vec3(uv, image_layer));
}


