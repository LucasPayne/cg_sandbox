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
uniform float frustum_segment_distances[MAX_NUM_FRUSTUM_SEGMENTS-1];
uniform mat4x4 shadow_matrices[MAX_NUM_FRUSTUM_SEGMENTS];
uniform sampler2DArray shadow_map;

in vec2 uv;
out vec4 color;


void main(void)
{
    vec4 f_albedo = texture(albedo, uv);
    vec3 f_normal = texture(normal, uv).rgb;
    vec3 f_position = texture(position, uv).rgb;


    // color = vec4(vec3(0.1*eye_z), 1); return;

    float eye_z = dot(f_position - camera_position, camera_forward);
    int segment = 0;
    for (int i = 0; i < num_frustum_segments-1; i++) {
        if (eye_z >= frustum_segment_distances[i]) segment = i+1;
    }

    // color = vec4(vec3(frustum_segment_distances[1]/20), f_albedo.a); return;
    // if (segment == 0) color = vec4(1,0,0,f_albedo.a);
    // else if (segment == 1) color = vec4(0,1,0,f_albedo.a);
    // else if (segment == 2) color = vec4(0,0,1,f_albedo.a);
    // else if (segment == 3) color = vec4(0,1,1,f_albedo.a);
    // return;


    vec3 shadow_coord = 0.5*(shadow_matrices[segment] * vec4(f_position, 1)).xyz + 0.5;
    float shadow_depth = texture(shadow_map, vec3(shadow_coord.xy, segment)).r;
    color = vec4(vec3(shadow_depth), f_albedo.a);

    float bias = 0.005;
    float shadow = shadow_coord.z < shadow_depth + bias ? 0.f : 1.f;
    if (shadow_coord.z > 1 ||
            shadow_coord.x < 0 || shadow_coord.x > 1 ||
            shadow_coord.y < 0 || shadow_coord.y > 1) {
        shadow = 0.f;
    }
    color = vec4(vec3(1-shadow), 1);

    color = vec4((1.f - shadow)*max(0, dot(f_normal, normalize(direction)))*f_albedo.rgb*light_color, f_albedo.a);
}
