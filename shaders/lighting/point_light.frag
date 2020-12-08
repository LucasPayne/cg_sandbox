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
uniform samplerCubeShadow shadow_map;
uniform samplerCube shadow_map_raw;
uniform mat4x4 shadow_matrices[6];

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


float shadowing(vec3 ray_dir, float compare_depth, vec3 normal)
{
    float bias = 0.005;
    return texture(shadow_map, vec4(ray_dir, compare_depth - bias));
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


    #define NUM_SAMPLES 8
    #define INV_NUM_SAMPLES (1.f / ( NUM_SAMPLES ))
    #define INV_NUM_SAMPLES_MINUS_ONE (1.f / (( NUM_SAMPLES ) - 1))
    vec3 X = vec3(1,0,0);
    X -= ray_dir * dot(X, ray_dir);
    X = normalize(X);
    vec3 Y = cross(ray_dir, X);



    float search_cone_radius = 0.15f;
    float cos_search_cone_radius = cos(search_cone_radius);
    float average_occluder_depth = 0.f;
    float num_occluded_samples = 0.f;
    for (int i = 0; i < 8; i++) {
        float z = (1 - i*INV_NUM_SAMPLES_MINUS_ONE)*cos_search_cone_radius + (i*INV_NUM_SAMPLES_MINUS_ONE);

        // Pseudo-random noise taken off of stackoverflow.
        float theta = 2*PI*fract(sin(dot(f_position.xy+f_position.z, vec2(12.9898, 78.233))) * 43758.5453);

        float h = sqrt(1 - z);
        vec3 sample_dir = z * ray_dir + h*(cos(theta) * X + sin(theta) * Y);

        float compare_depth = length(dpos) / far_plane_distance;
        float shadow = shadowing(sample_dir, compare_depth, f_normal);

        average_occluder_depth += shadow * texture(shadow_map_raw, sample_dir).r;
        num_occluded_samples += shadow;
    }
    average_occluder_depth /= num_occluded_samples;

    float sample_cone_radius = light_radius * (1 - average_occluder_depth / (dist / far_plane_distance));
    float cos_sample_cone_radius = cos(sample_cone_radius);
    float average_shadow = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float z = (1 - i*INV_NUM_SAMPLES_MINUS_ONE)*cos_sample_cone_radius + (i*INV_NUM_SAMPLES_MINUS_ONE);

        // Pseudo-random noise taken off of stackoverflow.
        float theta = 2*PI*fract(sin(dot(f_position.xy+f_position.z, vec2(12.9898, 78.233))) * 43758.5453);

        float h = sqrt(1 - z);
        vec3 sample_dir = z * ray_dir + h*(cos(theta) * X + sin(theta) * Y);

        //---compared depth should rather be computed by intersecting the sample ray with the plane of this fragment.
        float compare_depth = length(dpos) / far_plane_distance;
        float shadow = shadowing(sample_dir, compare_depth, f_normal);
        average_shadow += INV_NUM_SAMPLES * shadow;
    }
    vec3 col = (1 - average_shadow) * light_color * f_albedo.rgb * max(0, dot(-ray_dir, f_normal)) / dot(dpos, dpos);
    // vec3 col = (1 - average_shadow) * f_albedo.rgb;
    color = vec4(col, 1);

    // color = vec4(0.3*vec3(texture(shadow_map_raw, dpos).r), 1);
    // color = vec4(vec3(1.f/length(dpos)), 1);
}
