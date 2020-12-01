/*--------------------------------------------------------------------------------
    Depth of field first pass.
--------------------------------------------------------------------------------*/
#version 420

uniform sampler2D position; // G-buffer position
uniform vec3 camera_position;
uniform vec3 camera_forward;

// Camera parameters
uniform vec2 depth_of_field; // in-focus ranges from x to y
uniform float focus; // mid-point of depth of field

in vec2 uv;
out vec4 color;

void main(void)
{
    vec3 f_position = texture(position, uv).xyz;
    float alpha = texture(position, uv).a;
    float z = dot(f_position - camera_position, camera_forward);

    const float max_radius = 10.f;

    float r;
    if (z <= focus) {
        float lambda = 0.5 + depth_of_field.x / focus;
        r = 0.5 + (depth_of_field.x - z)/focus;
        r = min(r, max_radius);
        color = vec4(r,0,0,1);
    } else {
        r = 0.f;
        color = vec4(0,0,0,0);
        // color = vec4(0,r,0,1);
    }
    if (alpha == 0.f) color = vec4(0,0,0,0);
}
