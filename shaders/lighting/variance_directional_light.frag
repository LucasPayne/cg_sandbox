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



float get_average_occluder_depth(float search_width, vec3 shadow_coord, int segment)
{
    float mip = log2(search_width);
    vec2 moments = textureLod(shadow_map, vec3(shadow_coord.xy, segment), mip).xy;
    float variance = moments[1] - moments[0]*moments[0];
    float p = variance / (variance + (shadow_coord.z - moments[0])*(shadow_coord.z - moments[0]));
    return (moments[0] - p*shadow_coord.z) / (1 - p);
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

    float average_occluder_depth = get_average_occluder_depth(dot(imagespace_searching_extents, shadow_map_resolution),
                                                              shadow_coord, segment);

    /*--------------------------------------------------------------------------------
        Now the sampling width is determined such that, assuming all occluders
        are at the representative depth, and assuming the surface is faced toward the light,
        the occlusion would be correctly computed (with sufficient samples).
    --------------------------------------------------------------------------------*/
    vec2 imagespace_sample_extents = (shadow_coord.z - average_occluder_depth) * _pre_1[segment];

    vec2 texel = 1.f / shadow_map_resolution;
    vec2 tr = clamp(shadow_coord.xy + imagespace_sample_extents, vec2(0), vec2(1));
    vec2 bl = clamp(shadow_coord.xy - imagespace_sample_extents - texel, vec2(0), vec2(1));

    #define NUM_SAMPLES 12
    #define INV_NUM_SAMPLES (1.f / NUM_SAMPLES)
    #define POISSON_SAMPLE_MIN_DISTANCE 0.2
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

    vec2 moments = vec2(0);
    float sample_mip = log2(POISSON_SAMPLE_MIN_DISTANCE * dot(shadow_map_resolution, imagespace_sample_extents));
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
				           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
        moments += INV_NUM_SAMPLES * textureLod(shadow_map, vec3(shadow_coord.xy + imagespace_sample_extents*rotated_poisson_sample, segment), sample_mip).xy;
    }

    float mean = moments[0];
    float variance = moments[1] - mean*mean;

    visibility = variance / (variance + (shadow_coord.z - mean)*(shadow_coord.z - mean));
    visibility = clamp(visibility, 0, 1);

    // Remap visibility range to ameliorate light bleeding.
    const float x = 0.2;
    visibility = max(0, (visibility - x)/(1-x));
    visibility = max(visibility, float(mean > shadow_coord.z));

    } // endif range check
    float light_falloff = max(0, dot(f_normal, -light_direction));
    vec3 col = visibility * light_color * light_falloff*f_albedo.rgb;
    color = vec4(col, 1);
}
