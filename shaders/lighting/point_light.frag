/*--------------------------------------------------------------------------------
    Deferred point light
--------------------------------------------------------------------------------*/
#version 420


// G-buffer
uniform sampler2D depth;
uniform sampler2D normal;


// Camera
uniform mat4x4 inverse_projection_matrix;


// Light
vec3 light_position;
vec3 light_color;



in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;


// #include "shaders/gbuffer/decode.glsl"
vec3 decode_normal(vec4 encoded_normal)
{
    // reference: https://knarkowicz.wordpress.com/2014/04/16/octahedron-normal-vector-encoding/
    vec2 f = 2*encoded_normal.xy - 1;
    vec3 n = vec3(f.x, f.y, 1 - abs(f.x) - abs(f.y));
    float t = clamp(-n.z, 0, 1);
    n.x += n.x >= 0 ? -t : t;
    n.y += n.y >= 0 ? -t : t;
    return normalize(n);
}



void main(void)
{
    vec4 f_position_h = inverse_projection_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));

    vec3 dpos = f_position - light_position;
    color = max(0, dot(-normalize(dpos), f_normal)) * light_color / dot(dpos, dpos);
}
