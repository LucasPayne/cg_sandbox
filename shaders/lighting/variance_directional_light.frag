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
uniform float light_radius;

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
uniform sampler2DArray shadow_map_summed_area_table;
uniform ivec2 shadow_map_resolution;
uniform vec2 average_moments[MAX_NUM_FRUSTUM_SEGMENTS];

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;

#define PI 3.14159


/*--------------------------------------------------------------------------------
    Pre-computed values. These are uploaded as uniforms purely for efficiency.
--------------------------------------------------------------------------------*/
// _pre_1[i] : light_radius*box_extents[i].z * inv_box_extents[i].xy
uniform vec2 _pre_1[MAX_NUM_FRUSTUM_SEGMENTS];


vec2 sat(vec2 uv, int segment)
{
    vec2 moments = texture(shadow_map_summed_area_table, vec3(uv, segment)).xy;
    return moments + shadow_map_resolution.x*shadow_map_resolution.y*uv.x*uv.y*average_moments[segment];
}

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

    float visibility = 1.f;
    if (!(shadow_coord.x < -1 || shadow_coord.x < -1 || shadow_coord.x < -1 || shadow_coord.x < -1)) { //...


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
    // _pre_1[i] : light_radius*box_extents[i].z * inv_box_extents[i].xy
    vec2 imagespace_searching_extents = shadow_coord.z * _pre_1[segment];

    #define NUM_SAMPLES 12
    #define INV_NUM_SAMPLES (1.f / NUM_SAMPLES)
    const vec2 poisson_samples[NUM_SAMPLES] = {
        // vec2(0,0)
        vec2(0.21764400125830896, 0.7329012601480431),
        vec2(0.739415450061329, -0.29786769528902846),
        vec2(0.036639230720399985, -0.5349366920560421),
        vec2(0.009930998135024627, 0.24011767676345386),
        vec2(0.6376321352825092, -0.010191626834496148),
        vec2(-0.4740184550187583, 0.31080697860807094),
        vec2(-0.3178208674656333, -0.43228994302740786),
        vec2(0.38733257257670983, -0.518058116562061),
        vec2(0.41411944920682475, 0.41129234022075956),
        vec2(-0.6570547676188283, -0.6300829978796914),
        vec2(-0.44797571151440163, -0.7303464410200005),
        vec2(0.18498613971237865, -0.2840144420975712),
    };
    #if 1
    // Pseudo-random noise taken off of stackoverflow.
    float rand_theta = 2*PI*fract(sin(dot(f_world_position.xy+f_world_position.z, vec2(12.9898, 78.233))) * 43758.5453);
    float cos_rand_theta = cos(rand_theta);
    float sin_rand_theta = sin(rand_theta);
    #else
    float rand_theta = 0;
    float cos_rand_theta = 1;
    float sin_rand_theta = 0;
    #endif


    float average_occluder_depth = 0.f;
    float num_occluded_samples = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
				           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);

        vec2 d_uv = imagespace_searching_extents * rotated_poisson_sample;
        vec2 sample_uv = shadow_coord.xy + d_uv;
        if (sample_uv.x >= 0 && sample_uv.x <= 1 && sample_uv.y >= 0 && sample_uv.y <= 1) {
            float sample_depth = textureLod(shadow_map, vec3(sample_uv, segment), 0).x;
            // Account for the plane.
            vec3 sample_point = (inverse(world_shadow_matrices[segment]) * vec4(sample_uv, 0, 1)).xyz;
            float t = dot(f_world_position - sample_point, f_normal) / dot(light_direction, f_normal);
            if (sample_depth != 0.f && sample_depth < t/box_extents[segment].z - max(0.005, 0.025 * dot(f_normal, -light_direction))) {
                average_occluder_depth += sample_depth;
                num_occluded_samples += 1.f;
            }

            // Detect occluders within the cone of incoming light directions.
            // ---Possibly the cone calculation was incorrect.

            // float projected_radius = light_radius * shadow_coord.z * box_extents[segment].z;
            // float cone_slice_radius = max(0, projected_radius * (shadow_coord.z - sample_depth)/shadow_coord.z);
            // vec3 sample_point = (inverse(world_shadow_matrices[segment]) * vec4(sample_uv, sample_depth, 1)).xyz;
            // float dist_to_primary_line = length((sample_point - f_world_position) + light_direction * dot(sample_point - f_world_position, -light_direction));
            // if (dist_to_primary_line <= 5 * cone_slice_radius) { //---
            //     average_occluder_depth += sample_depth;
            //     num_occluded_samples += 1.f;
            // }
        }
    }
    // if (num_occluded_samples != 0.f) {
    average_occluder_depth /= num_occluded_samples + 0.001;
    /*--------------------------------------------------------------------------------
        Now the sampling width is determined such that, assuming all occluders
        are at the representative depth, and assuming the surface is faced toward the light,
        the occlusion would be correctly computed (with sufficient samples).
    --------------------------------------------------------------------------------*/
    vec2 imagespace_sample_extents = (shadow_coord.z - average_occluder_depth) * _pre_1[segment];
    // imagespace_sample_extents = 10.f / shadow_map_resolution;
    imagespace_sample_extents = 0.f / shadow_map_resolution;

    vec2 texel = 1.f / shadow_map_resolution;
    vec2 tr = clamp(shadow_coord.xy + imagespace_sample_extents, vec2(0), vec2(1));
    vec2 bl = clamp(shadow_coord.xy - imagespace_sample_extents - texel, vec2(0), vec2(1));

    vec2 moments = sat(tr, segment);
    moments -= sat(vec2(max(bl.x, 0), tr.y), segment);
    moments -= sat(vec2(tr.x, max(bl.y, 0)), segment);
    moments += sat(max(bl, 0), segment);
    moments /= (shadow_map_resolution.y*(tr.y - bl.y)) * (shadow_map_resolution.x*(tr.x - bl.x));


    // moments = texture(shadow_map, vec3(tr, segment)).xy;

    float mean = moments[0];
    float variance = moments[1] - mean*mean;
    // #define MIN_VARIANCE 0.005
    // variance = max(MIN_VARIANCE, abs(variance));

    visibility = variance / (variance + (shadow_coord.z - mean)*(shadow_coord.z - mean));
    visibility = clamp(visibility, 0, 1);

    // Remap visibility range to ameliorate light bleeding.
    // const float x = 0.1;
    // visibility = max(0, (visibility - x)/(1-x));

    visibility = max(visibility, float(mean > shadow_coord.z));

    // color = vec4(vec3(variance * 1000), 1); return;

    // } // endif shadow check
    // else {
    //     color = vec4(1,1,0,0);return;
    // }
    } // endif range check
    float light_falloff = max(0, dot(f_normal, -light_direction));
    color = vec4(visibility * light_color * light_falloff*f_albedo.rgb, 1);
        
    // color = vec4(visibility * light_color * f_albedo.rgb, 1);
    // color = vec4(vec3(f_world_position), 1);
}
