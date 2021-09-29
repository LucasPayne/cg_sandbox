#version 420

in GS_OUT {
    noperspective vec3 distances;
    vec3 normal;
    flat ivec3 edge_is_boundary;
} fs_in;

out vec4 color;

uniform float half_width;

uniform int viewport_width;
uniform int viewport_height;

void main(void)
{
    vec3 light_dir = normalize(vec3(0.4,-1,0.4));
    vec3 n = fs_in.normal;

    vec3 face_diffuse = vec3(1);
    const float lightness = 0.5;
    vec4 face_color = vec4(face_diffuse * (lightness + (1-lightness)*max(0, dot(light_dir, n))), 1);

    vec4 edge_color = vec4(0,0,0,1);

    float distance = 99999999;
    for (int i = 0; i < 3; i++) {
        if (fs_in.edge_is_boundary[(i+1)%3] != 0 && fs_in.distances[i] < distance) distance = fs_in.distances[i];
    }

    // This causes very bad aliasing.
    // if (distance < 0) {
    //     color = edge_color;
    // } else {
    //     color = face_color;
    // }
    // Rough heuristic to reduce aliasing.
    color = mix(edge_color, face_color, smoothstep(-0.002, 0.002, distance));
}
