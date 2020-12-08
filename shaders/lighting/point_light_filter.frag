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


uniform sampler2D shadow;
uniform float inv_screen_width;
uniform float inv_screen_height;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;


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
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    if (f_albedo.a == 0.f) discard;
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_vp_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));
    vec3 dpos = f_position - light_position;
    float dist = length(dpos);
    vec3 ray_dir = dpos / dist;

    float average_shadow = 0.f;
    // Some sort of filter...
    #define WEIGHT (1.f / 36.f)
    for (int i = -2; i <= 2; i += 2) {
        for (int j = -2; j <= 2; j += 2) {
            vec2 sample_uv = uv + vec2(inv_screen_width * i, inv_screen_height * j);
            vec4 sample_shadows = textureGather(shadow, sample_uv, 0);
            average_shadow += WEIGHT * (sample_shadows.x + sample_shadows.y + sample_shadows.z + sample_shadows.w);
        }
    }
    
    vec3 col = (1 - average_shadow) * light_color * f_albedo.rgb * max(0, dot(-ray_dir, f_normal)) / dot(dpos, dpos);
    color = vec4(5 * col, 1);
}
