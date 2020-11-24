#version 420
uniform vec3 direction;
uniform float width;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;

in vec2 uv;

out vec4 color;

void main(void)
{
    color = vec4(texture(albedo, uv).rgb, 1);
}
