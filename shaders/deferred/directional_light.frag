#version 420
uniform vec3 direction;
uniform vec3 light_color;
uniform float width;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;

uniform mat4x4 shadow_matrix;
uniform sampler2D shadow_map;

in vec2 uv;

out vec4 color;



void main(void)
{
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    vec3 f_position = texture(position, uv).rgb;
    vec3 shadow_coord = 0.5*(shadow_matrix * vec4(f_position, 1)).xyz + 0.5;

    float shadow;
    if (shadow_coord.z > 1 || shadow_coord.x < 0 || shadow_coord.x > 1 || shadow_coord.y < 0 || shadow_coord.y > 1) {
        shadow = 0.f;
    } else {
        float shadow_depth = texture(shadow_map, shadow_coord.xy).r;
        float bias = 0.005;
        shadow = shadow_coord.z < shadow_depth + bias ? 0.f : 1.f;
    }
    color = vec4(vec3(1-shadow), 1);

    color = vec4((1.f - shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
}
