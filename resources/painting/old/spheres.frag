#version 420

uniform float aspect_ratio;

in tessellated {
    vec2 uv;
    vec4 f_color;
    float y_radius;

    vec3 sphere_origin;
    float sphere_radius;

    vec3 eye_space_sphere_origin;
};

out vec4 color;

uniform mat4x4 projection_matrix;

void main(void)
{
    float x = 2*uv.x - 1;
    float y = 2*uv.y - 1;

    float xy_length = sqrt(x*x + y*y);
    float depth;
    if (xy_length > 1) {
        depth = 0.5*sphere_origin.z + 0.5;
    } else {
        float z = -sqrt(1 - xy_length);
        vec3 eye_space_sphere_point = eye_space_sphere_origin;
        eye_space_sphere_point.z += sphere_radius * z;
        vec4 sphere_point_h = projection_matrix * vec4(eye_space_sphere_point,1);
        
        depth = 0.5*sphere_point_h.z/sphere_point_h.w + 0.5;
    }
    color = vec4(vec3(depth), 1);
    gl_FragDepth = depth;

    /*
    // Sphere origin: 0,0,0
    // Sphere radius: 1
    // Ray origin: x,y,-2
    // Ray direction: 0,0,1
    float discrim = 16 - 4*(x*x + y*y + 3);
    if (discrim < 0) {
        // discard;
        color = vec4(vec3(gl_FragCoord.z), 1);
        gl_FragDepth = gl_FragCoord.z;
    } else {
        float t = 0.5 * (4 - sqrt(discrim));
        vec3 intersection = vec3(x,y,-2 + t);

        vec3 n = normalize(intersection);
        vec3 light_dir = vec3(1,1,1);
        color = f_color * max(0, dot(n, -light_dir));

        // gl_FragDepth = gl_FragCoord.z - pos.z*f_radius;
        // gl_FragDepth = sphere_origin.z;
        // gl_FragDepth = gl_FragCoord.z;

        float intersection_ndc_z = sphere_origin.z + y_radius*intersection.z;

        // gl_FragDepth = 0.5*intersection_ndc_z + 0.5;

        float depth = 0.5*(sphere_origin.z + y_radius*intersection.z) + 0.5;
        color = vec4(vec3(depth),1);
        gl_FragDepth = depth;
    }
    */
}
