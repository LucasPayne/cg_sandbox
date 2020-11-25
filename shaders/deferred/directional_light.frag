#version 420
uniform vec3 direction;
uniform vec3 light_color;
uniform float width;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;

in vec2 uv;

out vec4 color;

void main(void)
{
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    color = vec4(max(0, dot(f_normal, -normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
}
