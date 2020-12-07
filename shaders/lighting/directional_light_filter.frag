/*--------------------------------------------------------------------------------
    Second pass of deferred directional light.
    This reads the shadowing signal and blurs it before using it to compute lighting.
--------------------------------------------------------------------------------*/
#version 420

// G-buffer
uniform sampler2D depth;
uniform sampler2D normal;
uniform sampler2D albedo;

// Light
// note: Light direction is assumed to be normalized.
uniform vec3 direction;
uniform vec3 light_color;

// Shadow map cascades
#define MAX_NUM_FRUSTUM_SEGMENTS 4
uniform int num_frustum_segments;
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS];

uniform sampler2D shadow;
uniform float inv_screen_width;
uniform float inv_screen_height;

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
    #define DEBUG_COLOR(COLOR) color = vec4(vec3(COLOR), 1); return;
    /*--------------------------------------------------------------------------------
        G-buffer fetching
    --------------------------------------------------------------------------------*/
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    if (f_albedo.a == 0) discard;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));

    // DEBUG_COLOR(texture(shadow, uv));

    /*--------------------------------------------------------------------------------
        Shadow signal filtering
        (For denoising rotated-Poisson-disc PCF)
    --------------------------------------------------------------------------------*/
    float average_shadow = 0.f;
    // Some sort of filter...
    // #define WEIGHT (1.f / 36.f)
    // for (int i = -2; i <= 2; i += 2) {
    //     for (int j = -2; j <= 2; j += 2) {
    //         //-----------NOTE: This is incorrect, fix this. Subrectangles of textures are accessed. Should use a uniform vec2 for texel size.
    //         vec2 sample_uv = uv + vec2(inv_screen_width * i, inv_screen_height * j);
    //         // vec4 sample_shadow = textureGather(shadow, sample_uv).r;
    //         // average_shadow += WEIGHT * sample_shadow;
    //         vec4 sample_shadows = textureGather(shadow, sample_uv, 0);
    //         average_shadow += WEIGHT * (sample_shadows.x + sample_shadows.y + sample_shadows.z + sample_shadows.w);
    //     }
    // }


    // bilateral box filter
    float total_weights = 0.f;
    for (int i = -5; i <= 5; i += 1) {
        for (int j = -5; j <= 5; j += 1) {
            vec2 sample_uv = uv + vec2(inv_screen_width * i, inv_screen_height * j);
            if (abs(texture(depth, gbuffer_uv + vec2(inv_screen_width * i, inv_screen_height * j)).r - f_depth) < 0.001) {
                float sample_shadow = texture(shadow, sample_uv).r;
                average_shadow += sample_shadow;
                total_weights += 1;
            }
        }
    }
    average_shadow /= total_weights + 0.001;

    /*--------------------------------------------------------------------------------
        Lighting
    --------------------------------------------------------------------------------*/
    color = vec4((1.f - average_shadow)*max(0, dot(f_normal, -direction))*f_albedo.rgb*light_color, f_albedo.a);
}
