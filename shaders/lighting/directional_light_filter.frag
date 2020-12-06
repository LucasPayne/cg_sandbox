/*--------------------------------------------------------------------------------
    Second pass of deferred directional light.
    This reads the shadowing signal and blurs it before using it to compute lighting.
--------------------------------------------------------------------------------*/
#version 420

// G-buffer
uniform sampler2D normal;
uniform sampler2D albedo;

// Light
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
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    if (f_albedo.a == 0) discard;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));

    DEBUG_COLOR(texture(shadow, uv));

    /*--------------------------------------------------------------------------------
        Shadow signal filtering
        (For denoising rotated-Poisson-disc PCF)
    --------------------------------------------------------------------------------*/
    // Some sort of filter...
    #define WEIGHT (1.f / 16.f)
    float average_shadow = 0.f;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            vec2 sample_uv = uv + vec2(inv_screen_width * i, inv_screen_height * j);
            // vec4 sample_shadow = textureGather(shadow, sample_uv).r;
            // average_shadow += WEIGHT * sample_shadow;
            vec4 sample_shadows = textureGather(shadow, sample_uv, 0);
            average_shadow += WEIGHT * (sample_shadows.x + sample_shadows.y + sample_shadows.z + sample_shadows.w);
        }
    }

    /*--------------------------------------------------------------------------------
        Lighting
    --------------------------------------------------------------------------------*/
    color = vec4((1.f - average_shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
}
