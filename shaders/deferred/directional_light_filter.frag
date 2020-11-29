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
uniform sampler2DArrayShadow shadow_map;
uniform sampler2DArray shadow_map_raw;
uniform float shadow_map_width_inv;
uniform float shadow_map_height_inv;
uniform int shadow_map_width;
uniform int shadow_map_height;
uniform vec3 box_extents;


uniform sampler2D shadow;
uniform float inv_screen_width;
uniform float inv_screen_height;

in vec2 uv;
out vec4 color;

void main(void)
{
    /*--------------------------------------------------------------------------------
        G-buffer fetching
    --------------------------------------------------------------------------------*/
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    vec3 f_position = texture(position, uv).rgb;


    /*--------------------------------------------------------------------------------
        Shadow signal filtering
        (For denoising rotated-Poisson-disc PCF)
    --------------------------------------------------------------------------------*/
    int size = 3;
    float weight = 1.f / ((2*size+1)*(2*size+1));
    float average_shadow = 0.f;
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            average_shadow += weight * texture(shadow, uv + vec2(inv_screen_width * i, inv_screen_height * j)).r;
        }
    }
    color = average;

    /*--------------------------------------------------------------------------------
        Lighting
    --------------------------------------------------------------------------------*/
    color = vec4((1.f - shadow_fading*shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
    // Ambient lighting
    vec3 ambient = vec3(0.28);
    color += vec4(ambient*f_albedo.rgb, 0);


    /*--------------------------------------------------------------------------------
        Uncomment to visualize frustum segments.
    --------------------------------------------------------------------------------*/
    #if 0
    if (segment == 0) color += vec4(0.5,0,0,0);
    else if (segment == 1) color += vec4(0,0.5,0,0);
    else if (segment == 2) color += vec4(0,0,0.5,0);
    else if (segment == 3) color += vec4(0,0.5,0.5,0);
    return;
}
