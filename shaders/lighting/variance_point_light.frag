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
uniform float light_radius;

// Shadowing
uniform samplerCube shadow_map;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;


uniform float far_plane_distance;

#define PI 3.1415926535


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


void main(void)
{
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    if (f_albedo.a == 0.f) discard;
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_vp_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));
    vec3 dpos = f_position - light_position;
    float dist = length(dpos);
    vec3 ray_dir = dpos / dist;
    
    float t = dist / far_plane_distance;
    vec2 moments = texture(shadow_map, ray_dir).xy;
    float variance = moments[1] - moments[0]*moments[0];
    float pmax = variance / (variance + (t - moments[0])*(t - moments[0]));
    float visibility = pmax;

    vec3 col = visibility * PI * light_radius * light_radius * light_color * f_albedo.rgb * max(0, dot(-ray_dir, f_normal)) / dot(dpos, dpos);
    color = vec4(col, 1);
}
