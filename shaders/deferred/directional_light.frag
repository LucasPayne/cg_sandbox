#version 420
// G-buffer
uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;

// Camera
uniform vec3 camera_position;
uniform vec3 camera_forward;

// Light
uniform vec3 direction;
uniform vec3 light_color;
uniform float width;

// Shadow mapping
#define MAX_NUM_FRUSTUM_SEGMENTS 4
uniform int num_frustum_segments;
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS-1];
uniform mat4x4 shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];
uniform sampler2DArray shadow_map;
uniform float shadow_map_width_inv;
uniform float shadow_map_height_inv;
uniform int shadow_map_width;
uniform int shadow_map_height;

in vec2 uv;
out vec4 color;

#define PI 3.14159


float shadowing(vec3 shadow_coord, int segment)
{
    float shadow_depth = texture(shadow_map, vec3(shadow_coord.xy, segment)).r;
    float bias = 0.005;
    float shadow = shadow_coord.z < shadow_depth + bias ? 0.f : 1.f;
    if (shadow_coord.z > 1 ||
            shadow_coord.x < 0 || shadow_coord.x > 1 ||
            shadow_coord.y < 0 || shadow_coord.y > 1) {
        shadow = 0.f;
    }
    return shadow;
}

// float bilinear_shadowing(vec3 shadow_coord, int segment) {
//     float x_frac = fract(shadow_coord.x * shadow_map_width + 0.5);
//     float y_frac = fract(shadow_coord.y * shadow_map_height + 0.5);
//     float a = shadowing(vec3(shadow_coord.x - shadow_map_width_inv, shadow_coord.y - shadow_map_height_inv, shadow_coord.z), segment);
//     float b = shadowing(vec3(shadow_coord.x - shadow_map_width_inv, shadow_coord.y, shadow_coord.z), segment);
//     float c = shadowing(vec3(shadow_coord.x, shadow_coord.y - shadow_map_height_inv, shadow_coord.z), segment);
//     float d = shadowing(vec3(shadow_coord.x, shadow_coord.y, shadow_coord.z), segment);
//     return mix(mix(a, b, y_frac),
//            mix(c, d, y_frac),
//            x_frac);
// }


void main(void)
{
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    vec3 f_position = texture(position, uv).rgb;


    // color = vec4(vec3(0.1*eye_z), 1); return;

    float eye_z = dot(f_position - camera_position, camera_forward);
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        if (eye_z >= frustum_segment_distances[i]) segment = i+1;
    }


    vec3 shadow_coord = 0.5*(shadow_matrices[segment] * vec4(f_position, 1)).xyz + 0.5;
    float shadow = 0.f;

    float sample_radius = 5.f * shadow_map_width_inv;
    #define NUM_SAMPLES 12
    float weight = 1.f / NUM_SAMPLES;

    const vec2 poisson_samples[NUM_SAMPLES] = {
        vec2(-0.3835597153857353, -0.7778487407064922),
        vec2(0.40130091048388405, 0.19374174659263033),
        vec2(-0.45187866361450846, -0.25544445301371344),
        vec2(-0.31441265317647504, 0.5091412445894341),
        vec2(-0.10533080746062273, 0.3357803156039252),
        vec2(-0.5155143691045783, 0.30967491037873374),
        vec2(-0.2969392791180032, 0.0010459758074339298),
        vec2(-0.16470787945426935, -0.37760477122852754),
        vec2(-0.056825134835887914, -0.9681567383908469),
        vec2(0.7031362634484448, 0.4255112306648199),
        vec2(-0.17933857483077387, 0.8697576875147421),
        vec2(-0.15206507065241204, -0.7761207861878452)
    };

    // Pseudo-random noise taken off of stackoverflow.
    float rand_theta = 2*PI*fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
    float cos_rand_theta = cos(rand_theta);
    float sin_rand_theta = sin(rand_theta);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
                                           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
        vec2 sample_uv = shadow_coord.xy + sample_radius * rotated_poisson_sample;
        shadow += weight * shadowing(vec3(sample_uv, shadow_coord.z), segment);
    }

    color = vec4((1.f - shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);

    // Uncomment to visualize frustum segments.
    #if 0
    if (segment == 0) color += vec4(0.5,0,0,0);
    else if (segment == 1) color += vec4(0,0.5,0,0);
    else if (segment == 2) color += vec4(0,0,0.5,0);
    else if (segment == 3) color += vec4(0,0.5,0.5,0);
    return;
    #endif
}
