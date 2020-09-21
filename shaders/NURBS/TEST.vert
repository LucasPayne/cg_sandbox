#version 420
layout(location = 0) in vec3 position;

uniform mat4x4 mvp_matrix;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
}



