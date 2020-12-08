/*--------------------------------------------------------------------------------
    Deferred point light
--------------------------------------------------------------------------------*/
#version 420


// G-buffer
uniform sampler2D depth;
uniform sampler2D normal;
uniform sampler2D albedo;


// Camera
uniform mat4x4 inverse_vp_matrix;


// Light
uniform vec3 light_position;
uniform vec3 light_color;
uniform float light_radius;


// Shadowing
uniform samplerCubeShadow shadow_map;
uniform samplerCube shadow_map_raw;
uniform mat4x4 shadow_matrices[6];

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;
out vec4 color;


uniform float far_plane_distance;

#define PI 3.1415926535


// #include "shaders/gbuffer/decode.glsl"
vec3 decode_normal(vec4 encoded_normal)
{
    // taken from: https://knarkowicz.wordpress.com/2014/04/16/octahedron-normal-vector-encoding/
    vec2 f = 2*encoded_normal.xy - 1;
    vec3 n = vec3(f.x, f.y, 1 - abs(f.x) - abs(f.y));
    float t = clamp(-n.z, 0, 1);
    n.x += n.x >= 0 ? -t : t;
    n.y += n.y >= 0 ? -t : t;
    return normalize(n);
}


float shadowing(vec3 ray_dir, float compare_depth, vec3 normal)
{
    float bias = 0.005;
    return texture(shadow_map, vec4(ray_dir, compare_depth - bias));
}


void main(void)
{
    vec4 f_albedo = texture(albedo, gbuffer_uv);
    if (f_albedo.a == 0.f) discard;
    float f_depth = texture(depth, gbuffer_uv).r;
    vec4 f_position_h = inverse_vp_matrix * vec4(screen_pos, 2*f_depth-1, 1);
    vec3 f_position = f_position_h.xyz / f_position_h.w;
    vec3 f_normal = decode_normal(texture(normal, gbuffer_uv));
    vec3 dpos = f_position - light_position;
    vec3 ray_dir = normalize(dpos);


    #define NUM_SAMPLES 8
    #define INV_NUM_SAMPLES (1.f / ( NUM_SAMPLES ))
    #define INV_NUM_SAMPLES_MINUS_ONE (1.f / (( NUM_SAMPLES ) - 1))
    const vec2 axes[NUM_SAMPLES] = {
        vec2(-0.08520956964103771, 0.9963630509214947),
        vec2(-0.4505432949693625, -0.8927545795783688),
        vec2(0.7469336787634822, -0.6648985482980475),
        vec2(-0.9412593479393807, -0.3376845272095421),
        vec2(-0.06524912550872923, -0.9978690052408413),
        vec2(0.6497215417335966, 0.7601722950800813),
        vec2(-0.7794633446208609, 0.6264478385248536),
        vec2(0.7221049235206832, -0.6917835495494153),
    };
    const float angles[NUM_SAMPLES] = {
        0.5354357084763649,
        0.7208390096794479,
        -0.22535678440633422,
        0.9745844839469925,
        0.7607677210646531,
        -0.2319187544731745,
        -0.41889900013082704,
        0.4953900680275539,
    };



    vec3 X = vec3(1,0,0);
    X -= ray_dir * dot(X, ray_dir);
    X = normalize(X);
    vec3 Y = cross(ray_dir, X);

    float sample_cone_radius = 0.05f;
    float cos_sample_cone_radius = cos(sample_cone_radius);

    float average_shadow = 0.f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float z = (1 - i*INV_NUM_SAMPLES_MINUS_ONE)*cos_sample_cone_radius + (i*INV_NUM_SAMPLES_MINUS_ONE);
        float theta = i*INV_NUM_SAMPLES_MINUS_ONE * 2*PI;
        float h = sqrt(1 - z);
        vec3 sample_dir = z * ray_dir + h*(cos(theta) * X + sin(theta) * Y);

        float compare_depth = length(dpos) / far_plane_distance;
        float shadow = shadowing(sample_dir, compare_depth, f_normal);
        average_shadow += INV_NUM_SAMPLES * shadow;
    }
    vec3 col = (1 - average_shadow) * light_color * f_albedo.rgb * max(0, dot(-ray_dir, f_normal)) / dot(dpos, dpos);
    color = vec4(col, 1);

    // color = vec4(0.3*vec3(texture(shadow_map_raw, dpos).r), 1);
    // color = vec4(vec3(1.f/length(dpos)), 1);
}
