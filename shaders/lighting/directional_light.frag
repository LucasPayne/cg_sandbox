/*--------------------------------------------------------------------------------
    Deferred directional light
        - Cascaded shadow maps
        - Percentage-closer soft shadows with percentage-closer filtering
--------------------------------------------------------------------------------*/
#version 420
#define FADE_OUT 0
#define VISUALIZE_FRUSTUM_SEGMENTS 0


// G-buffer
uniform sampler2D depth;

// Camera
uniform mat4x4 inverse_projection_matrix;

// Light
uniform vec3 direction;
uniform vec3 light_color;
uniform float width;

// Shadow mapping
#define MAX_NUM_FRUSTUM_SEGMENTS 4
uniform int num_frustum_segments;
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS];
// Shadow matrices transform from camera space.
uniform mat4x4 shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];
uniform vec3 box_extents[MAX_NUM_FRUSTUM_SEGMENTS];
uniform vec3 inv_box_extents[MAX_NUM_FRUSTUM_SEGMENTS];
// NOTE: Is it worth the double bandwidth just to use a shadow sampler? Can a shadow sampler be accessed normally?
// TODO: Try texelFetch.
uniform sampler2DArrayShadow shadow_map;
uniform sampler2DArray shadow_map_raw;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;

#define PI 3.14159


/*--------------------------------------------------------------------------------
    Pre-computed values. These are uploaded as uniforms purely for efficiency.
--------------------------------------------------------------------------------*/
// _pre_1[i] : 0.5*width*box_extents[i].z * inv_box_extents[i].xy
uniform vec2 _pre_1[MAX_NUM_FRUSTUM_SEGMENTS];


float shadowing(vec3 shadow_coord, int segment)
{
    #define BIAS 0.005
    float shadow = texture(shadow_map, vec4(shadow_coord.xy, segment, shadow_coord.z - BIAS)).r;
    if (shadow_coord.z > 1 ||
            shadow_coord.x < 0 || shadow_coord.x > 1 ||
            shadow_coord.y < 0 || shadow_coord.y > 1) {
        shadow = 0.f;
    }
    return shadow;
    #undef BIAS
}


void main(void)
{
    #define DEBUG_COLOR(COLOR) color = vec4(vec3(COLOR), 1); return;

    /*--------------------------------------------------------------------------------
        G-buffer fetching
    --------------------------------------------------------------------------------*/
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_projection_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;

    /*--------------------------------------------------------------------------------
        Determine frustum segment (from cascaded shadow maps), and
        transform to light space.
    --------------------------------------------------------------------------------*/
    float eye_z = -f_position.z;
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        // NOTE: Unsure if avoiding brancing here is worth it.
        segment = max(segment, (i+1)*int(clamp(ceil(eye_z - frustum_segment_distances[i]), 0, 1)));
    }
    // Get texture-space shadow coordinate.
    vec3 shadow_coord = (shadow_matrices[segment] * vec4(f_position, 1)).xyz;


    /*--------------------------------------------------------------------------------
        Fade out shadows in the distance.
    --------------------------------------------------------------------------------*/
    #if FADE_OUT == 1
    float shadow_fading = 1.f;
    if (segment == num_frustum_segments - 1) {
        shadow_fading = 1 - (eye_z - frustum_segment_distances[num_frustum_segments-1])
                        /(frustum_segment_distances[num_frustum_segments-1] - frustum_segment_distances[num_frustum_segments-2]);
        shadow_fading = clamp(shadow_fading, 0, 1); //---fix this
    }
    #endif


    /*--------------------------------------------------------------------------------
        Random variables for sampling.
        A Poisson-disc randomly rotated in screen space is used.
    --------------------------------------------------------------------------------*/
    #define NUM_SAMPLES 8
    #define INV_NUM_SAMPLES (1.f / NUM_SAMPLES)
    const vec2 poisson_samples[NUM_SAMPLES] = {
        vec2(0.6335993243840425, -0.6967535351798042),
        vec2(-0.7182862546442992, -0.642927819093875),
        vec2(-0.5563761183188973, 0.43390075575370024),
        vec2(0.34963833473625483, -0.9058096377630869),
        vec2(-0.9013261469881237, 0.33460599045108164),
        vec2(0.4801163765028016, 0.5981512731780383),
        vec2(-0.9313199714350133, 0.0345017666150762),
        vec2(-0.3387566044621402, -0.8496373910192114),
    };
    // Pseudo-random noise taken off of stackoverflow.
    #if 1
    float rand_theta = 2*PI*fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
    float cos_rand_theta = cos(rand_theta);
    float sin_rand_theta = sin(rand_theta);
    #else
    float rand_theta = 0;
    float cos_rand_theta = 1;
    float sin_rand_theta = 0;
    #endif

    // NOTE: Unsure if storing these in an array is more efficient than just computing them twice.
    vec2 rotated_poisson_samples[NUM_SAMPLES];
    for (int i = 0; i < NUM_SAMPLES; i++) {
        rotated_poisson_samples[i] = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
                                           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
    }

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

    //    float worldspace_searching_radius = 0.5 * width * shadow_coord.z * box_extents[segment].z;
    //    vec2 imagespace_searching_extents = vec2(worldspace_searching_radius * inv_box_extents[segment].x,
    //                                             worldspace_searching_radius * inv_box_extents[segment].y);
    // _pre_1[i] : 0.5*width*box_extents[i].z * inv_box_extents[i].xy
    vec2 imagespace_searching_extents = shadow_coord.z * _pre_1[segment];

    float average_occluder_depth = 0.f;
    float num_occluded_samples = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 sample_uv = shadow_coord.xy + imagespace_searching_extents*rotated_poisson_samples[i];
        float shadow = shadowing(vec3(sample_uv, shadow_coord.z), segment);
        average_occluder_depth += shadow * texture(shadow_map_raw, vec3(sample_uv, segment)).r;
        num_occluded_samples += shadow;
    }
    average_occluder_depth /= num_occluded_samples + 0.001;

    /*--------------------------------------------------------------------------------
        Now the sampling width is determined such that, assuming all occluders
        are at the representative depth, and assuming the surface is faced toward the light,
        the occlusion would be correctly computed (with sufficient samples).
    --------------------------------------------------------------------------------*/
    //    float worldspace_sample_radius = 0.5 * width * (shadow_coord.z - average_occluder_depth)  * box_extents[segment].z;
    //    vec2 imagespace_sample_extents = vec2(worldspace_sample_radius / box_extents[segment].x,
    //                                          worldspace_sample_radius / box_extents[segment].y);
    vec2 imagespace_sample_extents = (shadow_coord.z - average_occluder_depth) * _pre_1[segment];

    float shadow = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 sample_uv = shadow_coord.xy + imagespace_sample_extents * rotated_poisson_samples[i];
        shadow += INV_NUM_SAMPLES * shadowing(vec3(sample_uv, shadow_coord.z), segment);
    }
    #if FADE_OUT == 1
    color = vec4(shadow_fading * shadow, 0,0,1);
    #else
    color = vec4(shadow, 0,0,1);
    #endif


    /*--------------------------------------------------------------------------------
        Visualize frustum segments.
    --------------------------------------------------------------------------------*/
    #if VISUALIZE_FRUSTUM_SEGMENTS == 1
    if (segment == 0) color.x += 0;
    else if (segment == 1) color.x += 0.2;
    else if (segment == 2) color.x += 0.4;
    else if (segment == 3) color.x += 0.6;
    #endif
}
