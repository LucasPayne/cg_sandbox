#version 420

in vec2 f_uv;

out vec4 color;

uniform sampler2D image;
uniform float brightness;

void main()
{
    color = texture(image, vec2(1-f_uv.x, 1-f_uv.y));
    color.rgb *= brightness;
}
