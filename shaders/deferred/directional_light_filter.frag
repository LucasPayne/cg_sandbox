#version 420
uniform sampler2D lighting;

in vec2 uv;
out vec4 color;


void main(void)
{
    color = texture(lighting, uv);
}
