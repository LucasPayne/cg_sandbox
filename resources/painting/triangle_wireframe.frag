#version 420

in GS_OUT {
    noperspective vec3 distances;
    vec3 normal;
} fs_in;

out vec4 color;

uniform float half_width;

uniform int viewport_width;
uniform int viewport_height;

void main(void)
{
    vec3 light_dir = normalize(vec3(1,1,1));
    vec3 n = fs_in.normal;

    // vec3 face_diffuse = vec3(0.9);
    // vec3 cool = 0.6*face_diffuse + 0.4*vec3(0,0,1);
    // vec3 warm = 0.6*face_diffuse + 0.4*vec3(1,1,0);
    // float l_dot_n = max(0, dot(light_dir, fs_in.normal));
    // vec4 face_color = vec4(((1 + l_dot_n)/2)*cool + (1 - (1 + l_dot_n)/2)*warm, 1);

    vec3 face_diffuse = vec3(0.9);
    vec4 face_color = vec4(face_diffuse * (0.5 + 0.5*max(0, dot(light_dir, n))), 1);

    vec4 edge_color = vec4(0,0,0,1);

    float distance = min(fs_in.distances[0], min(fs_in.distances[1], fs_in.distances[2]));

    // This causes very bad aliasing.
    // if (distance < 0) {
    //     color = edge_color;
    // } else {
    //     color = face_color;
    // }
    
    // Rough heuristic to reduce aliasing.
    color = mix(edge_color, face_color, smoothstep(half_width - 0.001, half_width + 0.001, distance));
}
