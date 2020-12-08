/*--------------------------------------------------------------------------------
    Deferred point light
--------------------------------------------------------------------------------*/
#version 420


// G-buffer
uniform sampler2D depth;
uniform sampler2D normal;
uniform sampler2D albedo;


// Camera
uniform mat4x4 inverse_vp_matrix;


// Light
uniform vec3 light_position;
uniform vec3 light_color;

// Shadowing
uniform samplerCubeShadow shadow_map;
uniform samplerCube shadow_map_raw;
uniform mat4x4 shadow_matrices[6];

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;


uniform float far_plane_distance;


// #include "shaders/gbuffer/decode.glsl"
vec3 decode_normal(vec4 encoded_normal)
{
    // taken from: https://knarkowicz.wordpress.com/2014/04/16/octahedron-normal-vector-encoding/
    vec2 f = 2*encoded_normal.xy - 1;
    vec3 n = vec3(f.x, f.y, 1 - abs(f.x) - abs(f.y));
    float t = clamp(-n.z, 0, 1);
    n.x += n.x >= 0 ? -t : t;
    n.y += n.y >= 0 ? -t : t;
    return normalize(n);
}


float shadowing(vec3 dpos, float compare_depth, vec3 normal)
{
    float bias = 0.005;
    return texture(shadow_map, vec4(dpos, compare_depth - bias));
}


void main(void)
{
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_vp_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));
    vec3 f_albedo = texture(albedo, gbuffer_uv).rgb;
    vec3 dpos = f_position - light_position;
    float compare_depth = length(dpos) / far_plane_distance;

    float shadow = shadowing(dpos, compare_depth, f_normal);

    vec3 col = (1 - shadow) * light_color * f_albedo * max(0, dot(-normalize(dpos), f_normal)) / dot(dpos, dpos);
    color = vec4(col, 1);

    // color = vec4(vec3(texture(shadow_map_raw, dpos).r), 1);
    // color = vec4(vec3(1.f/length(dpos)), 1);
}
