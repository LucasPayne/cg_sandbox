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
    vec3 shadow_coord = (shadow_matrix * vec4(f_position, 1)).xyz;
    float shadow_depth = texture(shadow_map, shadow_coord.xy).r;
    if (shadow_depth > shadow_coord.z) {
        color = vec4(max(0, dot(f_normal, -normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
    } else {
        color = vec4(0,0,0,1);
    }
}
