/*--------------------------------------------------------------------------------
    Deferred directional light
--------------------------------------------------------------------------------*/
#version 420
#define FADE_OUT 0
#define VISUALIZE_FRUSTUM_SEGMENTS 0

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

// G-buffer
uniform sampler2D depth;
uniform sampler2D normal;
uniform sampler2D albedo;

// Camera
uniform mat4x4 inverse_projection_matrix;
uniform mat4x4 camera_matrix; //from camera space to world space

// Light
uniform vec3 light_direction;
uniform vec3 light_color;
uniform float light_width;

// Shadow mapping
#define MAX_NUM_FRUSTUM_SEGMENTS 4
uniform int num_frustum_segments;
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS];
// Shadow matrices transform from camera space.
uniform mat4x4 shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];

// from world space
uniform mat4x4 world_shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];
uniform vec3 box_extents[MAX_NUM_FRUSTUM_SEGMENTS];
uniform vec3 inv_box_extents[MAX_NUM_FRUSTUM_SEGMENTS];
uniform sampler2DArray shadow_map;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;

#define PI 3.14159


/*--------------------------------------------------------------------------------
    Pre-computed values. These are uploaded as uniforms purely for efficiency.
--------------------------------------------------------------------------------*/
// _pre_1[i] : 0.5*light_width*box_extents[i].z * inv_box_extents[i].xy
uniform vec2 _pre_1[MAX_NUM_FRUSTUM_SEGMENTS];


void main(void)
{
    /*--------------------------------------------------------------------------------
        G-buffer fetching
    --------------------------------------------------------------------------------*/
    vec3 f_albedo = texture(albedo, gbuffer_uv).rgb;
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_projection_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));
    vec3 f_world_position = (camera_matrix * vec4(f_position,1)).xyz;

    /*--------------------------------------------------------------------------------
        Determine frustum segment (from cascaded shadow maps), and
        transform to light space.
    --------------------------------------------------------------------------------*/
    float eye_z = -f_position.z;
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        // NOTE: Unsure if avoiding branching here is worth it.
        segment = max(segment, (i+1)*int(clamp(ceil(eye_z - frustum_segment_distances[i]), 0, 1)));
    }
    // Get box-space position.
    vec3 shadow_coord = (shadow_matrices[segment] * vec4(f_position, 1)).xyz;


    /*================================================================================
        Percentage-closer soft shadows
    ================================================================================*/
    /*--------------------------------------------------------------------------------
        The far away area-light subtends a certain solid angle, determined by input parameters.
        The true occlusion is the proportion of this solid angle that is occluded.
        PCSS approximates this by first finding a good representative occluder depth
        (from the perspective of the light) by sampling the shadow map.
        The searched ellipse in texture space is chosen such that it ranges over all possible occluders,
        with respect to the solid angle of the incoming light (e.g. the sun).
    --------------------------------------------------------------------------------*/
    // Average the occluder depths from the (orthogonal) perspective of the light.

    //    float worldspace_searching_radius = 0.5 * light_width * shadow_coord.z * box_extents[segment].z;
    //    vec2 imagespace_searching_extents = vec2(worldspace_searching_radius * inv_box_extents[segment].x,
    //                                             worldspace_searching_radius * inv_box_extents[segment].y);
    // _pre_1[i] : 0.5*light_width*box_extents[i].z * inv_box_extents[i].xy
    // vec2 imagespace_searching_extents = shadow_coord.z * _pre_1[segment];

    // #define NUM_SAMPLES 8
    // #define INV_NUM_SAMPLES (1.f / NUM_SAMPLES)
    // const vec2 poisson_samples[NUM_SAMPLES] = {
    //     vec2(0.6335993243840425, -0.6967535351798042),
    //     vec2(-0.7182862546442992, -0.642927819093875),
    //     vec2(-0.5563761183188973, 0.43390075575370024),
    //     vec2(0.34963833473625483, -0.9058096377630869),
    //     vec2(-0.9013261469881237, 0.33460599045108164),
    //     vec2(0.4801163765028016, 0.5981512731780383),
    //     vec2(-0.9313199714350133, 0.0345017666150762),
    //     vec2(-0.3387566044621402, -0.8496373910192114),
    // };
    // #if 1
    // // Pseudo-random noise taken off of stackoverflow.
    // float rand_theta = 2*PI*fract(sin(dot(f_world_position.xy+f_world_position.z, vec2(12.9898, 78.233))) * 43758.5453);
    // float cos_rand_theta = cos(rand_theta);
    // float sin_rand_theta = sin(rand_theta);
    // #else
    // float rand_theta = 0;
    // float cos_rand_theta = 1;
    // float sin_rand_theta = 0;
    // #endif

    // // NOTE: Unsure if storing these in an array is more efficient than just computing them twice.
    // vec2 rotated_poisson_samples[NUM_SAMPLES];
    // for (int i = 0; i < NUM_SAMPLES; i++) {
    //     rotated_poisson_samples[i] = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
    //                                        -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
    // }
    // float average_occluder_depth = 0.f;
    // float num_occluded_samples = 0.f;
    // for (int i = 0; i < NUM_SAMPLES; i++) {
    //     vec2 d_uv = imagespace_searching_extents * rotated_poisson_samples[i];
    //     vec2 sample_uv = shadow_coord.xy + d_uv;

    //     float shadow = shadowing(vec3(sample_uv, shadow_coord.z), segment, f_normal);
    //     vec3 p = (inverse(world_shadow_matrices[segment]) * vec4(sample_uv, texture(shadow_map_raw, vec3(sample_uv, segment)).r, 1)).xyz;
    //     // Do not detect an occluder if this point is too close to the facet.
    //     if (dot(p - f_world_position, f_normal) < 0.1) shadow = 0;

    //     average_occluder_depth += shadow * texture(shadow_map_raw, vec3(sample_uv, segment)).r;
    //     num_occluded_samples += shadow;
    // }
    // average_occluder_depth /= num_occluded_samples + 0.001;
    // // If there are no occluders, set the depth such that the imagespace sample extent becomes 0.
    // if (num_occluded_samples == 0) average_occluder_depth = shadow_coord.z;

    // /*--------------------------------------------------------------------------------
    //     Now the sampling width is determined such that, assuming all occluders
    //     are at the representative depth, and assuming the surface is faced toward the light,
    //     the occlusion would be correctly computed (with sufficient samples).
    // --------------------------------------------------------------------------------*/
    // //    float worldspace_sample_radius = 0.5 * light_width * (shadow_coord.z - average_occluder_depth)  * box_extents[segment].z;
    // //    vec2 imagespace_sample_extents = vec2(worldspace_sample_radius / box_extents[segment].x,
    // //                                          worldspace_sample_radius / box_extents[segment].y);
    // vec2 imagespace_sample_extents = (shadow_coord.z - average_occluder_depth) * _pre_1[segment];

    float visibility = 1.f;
    vec2 moments = textureLod(shadow_map, vec3(shadow_coord.xy, segment), 3).xy;
    float mean = moments[0];
    if (shadow_coord.z >= mean) {
        float variance = moments[1] - mean*mean;
        visibility = variance / (variance + (shadow_coord.z - mean)*(shadow_coord.z - mean));
    }
    color = vec4(visibility * light_color * max(0, dot(f_normal, -light_direction))*f_albedo.rgb, 1);
}
