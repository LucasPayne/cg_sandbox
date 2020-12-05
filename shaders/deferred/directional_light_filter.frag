/*--------------------------------------------------------------------------------
    Second pass of deferred directional light.
    This reads the shadowing signal and blurs it before using it to compute lighting.
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
        Determine frustum segment (from cascaded shadow maps)
    --------------------------------------------------------------------------------*/
    float eye_z = dot(f_position - camera_position, camera_forward);
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        if (eye_z >= frustum_segment_distances[i]) segment = i+1;
    }

    /*--------------------------------------------------------------------------------
        Shadow signal filtering
        (For denoising rotated-Poisson-disc PCF)
    --------------------------------------------------------------------------------*/
    #define size 3
    const float gaussian_kernel[(2*size+1)*(2*size+1)] = {
        0.0004360337163160857, 0.0019541675407126887, 0.004806476562858854, 0.0064880647217826605, 0.004806476562858854, 0.0019541675407126887, 0.0004360337163160857,
        0.0019541675407126887, 0.008757971308821473, 0.021541133478600594, 0.02907748875125932, 0.021541133478600594, 0.008757971308821473, 0.0019541675407126887,
        0.004806476562858854, 0.021541133478600594, 0.052982638921813145, 0.07151908179722863, 0.052982638921813145, 0.021541133478600594, 0.004806476562858854,
        0.0064880647217826605, 0.02907748875125932, 0.07151908179722863, 0.09654066247373766, 0.07151908179722863, 0.02907748875125932, 0.0064880647217826605,
        0.004806476562858854, 0.021541133478600594, 0.052982638921813145, 0.07151908179722863, 0.052982638921813145, 0.021541133478600594, 0.004806476562858854,
        0.0019541675407126887, 0.008757971308821473, 0.021541133478600594, 0.02907748875125932, 0.021541133478600594, 0.008757971308821473, 0.0019541675407126887,
        0.0004360337163160857, 0.0019541675407126887, 0.004806476562858854, 0.0064880647217826605, 0.004806476562858854, 0.0019541675407126887, 0.0004360337163160857
    };
    float average_shadow = 0.f;
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            float weight = gaussian_kernel[(2*size+1)*(i+size) + j+size];
            vec2 sample_uv = uv + vec2(inv_screen_width * i, inv_screen_height * j);
            float sample_shadow = texture(shadow, sample_uv).r;
            average_shadow += weight * sample_shadow;
        }
    }

    // DEBUG_COLOR(average_shadow);

    /*--------------------------------------------------------------------------------
        Lighting
    --------------------------------------------------------------------------------*/
    color = vec4((1.f - average_shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
    // Ambient lighting
    vec3 ambient = vec3(0.28);
    color += vec4(ambient*f_albedo.rgb, 0);
}
