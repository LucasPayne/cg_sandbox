#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in float radius;
layout (location = 2) in vec4 color;

out vec4 f_color;

uniform mat4x4 vp_matrix;

void main(void)
{
    gl_Position = vp_matrix * vec4(position, 1);
    // gl_Position = vec4(position, 1);
    f_color = color;
}
