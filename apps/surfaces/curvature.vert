#version 420

uniform mat4x4 mvp_matrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 curvatures;

out vec2 f_curvatures;

void main(void)
{
    f_curvatures = curvatures;
    gl_Position = mvp_matrix * vec4(position, 1);
}
