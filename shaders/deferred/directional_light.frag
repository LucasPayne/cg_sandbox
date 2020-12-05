/*--------------------------------------------------------------------------------
    Deferred directional light
        - Cascaded shadow maps
        - Percentage-closer soft shadows with percentage-closer filtering
--------------------------------------------------------------------------------*/
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
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS];
uniform mat4x4 shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];
uniform vec3 box_extents[MAX_NUM_FRUSTUM_SEGMENTS];
uniform sampler2DArrayShadow shadow_map;
uniform sampler2DArray shadow_map_raw;
uniform float shadow_map_width_inv;
uniform float shadow_map_height_inv;
uniform int shadow_map_width;
uniform int shadow_map_height;

in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;

#define PI 3.14159


float shadowing(vec3 shadow_coord, int segment)
{
    float bias = 0.005;
    // float shadow_depth = texture(shadow_map, vec3(shadow_coord.xy, segment)).r;
    // float shadow = shadow_coord.z < shadow_depth + bias ? 0.f : 1.f;

    float shadow = texture(shadow_map, vec4(shadow_coord.xy, segment, shadow_coord.z - bias)).r;

    if (shadow_coord.z > 1 ||
            shadow_coord.x < 0 || shadow_coord.x > 1 ||
            shadow_coord.y < 0 || shadow_coord.y > 1) {
        shadow = 0.f;
    }
    return shadow;
}


void main(void)
{
    #define DEBUG_COLOR(COLOR) color = vec4(vec3(COLOR), f_albedo.a); return;

    /*--------------------------------------------------------------------------------
        G-buffer fetching
    --------------------------------------------------------------------------------*/
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    vec3 f_normal = texture(normal, gbuffer_uv).xyz;
    vec3 f_position = texture(position, gbuffer_uv).xyz;

    /*--------------------------------------------------------------------------------
        Determine frustum segment (from cascaded shadow maps), and
        transform to light space.
    --------------------------------------------------------------------------------*/
    float eye_z = dot(f_position - camera_position, camera_forward);
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        if (eye_z >= frustum_segment_distances[i]) segment = i+1;
    }
    vec3 shadow_coord = 0.5*(shadow_matrices[segment] * vec4(f_position, 1)).xyz + 0.5;
    // Fade out shadows in the distance.
    float shadow_fading = 1.f;
    if (segment == num_frustum_segments - 1) {
        shadow_fading = 1 - (eye_z - frustum_segment_distances[num_frustum_segments-1])
                        /(frustum_segment_distances[num_frustum_segments-1] - frustum_segment_distances[num_frustum_segments-2]);
    }

    /*--------------------------------------------------------------------------------
        Random variables for sampling.
        A Poisson-disc randomly rotated in screen space is used.
    --------------------------------------------------------------------------------*/
    #define NUM_SAMPLES 12
    float inv_num_samples = 1.f / NUM_SAMPLES;
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
    float worldspace_searching_radius = 0.5 * width * shadow_coord.z * box_extents[segment].z;
    vec2 imagespace_searching_extents = vec2(worldspace_searching_radius / box_extents[segment].x,
                                             worldspace_searching_radius / box_extents[segment].y);
    float average_occluder_depth = 0.f;
    float num_occluded_samples = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
                                           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
        vec2 sample_uv = shadow_coord.xy + imagespace_searching_extents*rotated_poisson_sample;

        float shadow = shadowing(vec3(sample_uv, shadow_coord.z), segment);
        average_occluder_depth += shadow * texture(shadow_map_raw, vec3(sample_uv, segment)).r;
        num_occluded_samples += shadow;
    }
    if (num_occluded_samples != 0) average_occluder_depth /= num_occluded_samples;
    else average_occluder_depth = 1;


    /*--------------------------------------------------------------------------------
        Now the sampling width is determined such that, assuming all occluders
        are at the representative depth, and assuming the surface is faced toward the light,
        the occlusion would be correctly computed (with sufficient samples).
    --------------------------------------------------------------------------------*/
    float worldspace_sample_radius = abs(0.5 * width * (shadow_coord.z - average_occluder_depth)  * box_extents[segment].z);

    // Artificially harden shadows near the contact.
    //--------------------------------------------------------------------------------
    // float lim = 0.19;
    // if (worldspace_sample_radius < lim) worldspace_sample_radius = worldspace_sample_radius * sqrt(worldspace_sample_radius) / sqrt(lim);
    //--------------------------------------------------------------------------------
    
    vec2 imagespace_sample_extents = vec2(worldspace_sample_radius / box_extents[segment].x,
                                          worldspace_sample_radius / box_extents[segment].y);
    float shadow = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
                                           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
        vec2 sample_uv = shadow_coord.xy + imagespace_sample_extents * rotated_poisson_sample;
        shadow += inv_num_samples * shadowing(vec3(sample_uv, shadow_coord.z), segment);
    }
    if (shadow < 0) shadow = 0;

    color = vec4(shadow_fading * shadow, 0,0,1);

    /*--------------------------------------------------------------------------------
        Uncomment to visualize frustum segments.
    --------------------------------------------------------------------------------*/
    #if 0
    if (segment == 0) color += vec4(0.5,0,0,0);
    else if (segment == 1) color += vec4(0,0.5,0,0);
    else if (segment == 2) color += vec4(0,0,0.5,0);
    else if (segment == 3) color += vec4(0,0.5,0.5,0);
    return;
    #endif
}
