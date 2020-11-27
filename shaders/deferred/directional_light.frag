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


float shadowing(vec3 shadow_coord)
{
    vec2 shadow_uv = 0.5*shadow_coord.xy + 0.5;
    float shadow_depth = texture(shadow_map, shadow_uv).r;
    float shadow = shadow_coord.z > shadow_depth ? 1.f : 0.f;
    return shadow;
}


void main(void)
{
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    vec3 f_position = texture(position, uv).rgb;

    vec3 shadow_coord = (shadow_matrix * vec4(f_position, 1)).xyz;
    float shadow = shadowing(shadow_coord);
    color = vec4((1.f - shadow)*max(0, dot(f_normal, -normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);

    if (!(shadow_coord.x < 0 || shadow_coord.x > 1 || shadow_coord.y < 0 || shadow_coord.y > 1)) {
        color = vec4(shadow_coord.x, shadow_coord.y, 0, 1);
    } else {
        color = vec4(1,0,1,1);
    }
}
