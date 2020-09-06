#version 420

in tessellated {
    vec2 uv;

    vec4 sphere_color;
    float sphere_radius;

    vec4 eye_position;
};


out vec4 color;

uniform float aspect_ratio;
uniform mat4x4 projection_matrix;

void main(void)
{
    float x = 2*uv.x - 1;
    float y = 2*uv.y - 1;

    float xy_length = sqrt(x*x + y*y);
    float depth;
    if (xy_length > 1) {
        // depth = 0.5*sphere_origin.z + 0.5;
        discard;
    } else {
        float z = -sqrt(1 - xy_length);
        vec4 sphere_point = eye_position;
        sphere_point.z -= sphere_radius * z;
        vec4 sphere_point_h = projection_matrix * sphere_point;
        
        depth = 0.5*sphere_point_h.z/sphere_point_h.w + 0.5;
    }
    color = vec4(vec3(depth), 1);
    gl_FragDepth = depth;
}
