#version 420

layout (location = 0) in vec3 position;

uniform mat4x4 vp_matrix;

void main(void)
{
    gl_Position = vp_matrix * vec4(position, 1);
}
