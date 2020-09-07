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

    float delta = 0.05;
    float alpha = 1-smoothstep(1-delta, 1, xy_length);

    if (xy_length > 1) discard;
    // Non-linearity of the depth value w/r/t change in eye-space z is handled by taking the point on the sphere
    // in eye-space, then projecting it and normalizing to extract the depth.
    // The computation of the point on the sphere in eye-space should work when depth is dependent
    // only on the z in eye-space, which I think is the case with the usual camera projection.
    float z = -sqrt(1 - xy_length);
    vec4 sphere_point = eye_position;
    sphere_point.z -= sphere_radius * z;
    vec4 sphere_point_h = projection_matrix * sphere_point;

    gl_FragDepth = 0.5*sphere_point_h.z/sphere_point_h.w + 0.5;

    #if 0
    // Flat color.
    color = vec4(sphere_color.rgb, alpha);
    #else
    // Basic lighting test.
    vec3 light_dir = vec3(1,1,1);
    vec3 n = normalize(vec3(x,y,z));
    color = vec4(max(0, dot(n, -light_dir)) * sphere_color.rgb, alpha);
    #endif
}
