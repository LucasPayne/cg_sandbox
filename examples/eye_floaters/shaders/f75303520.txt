#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4x4 mvp_matrix;

out vec2 f_uv;

void main()
{
    f_uv = uv;
    gl_Position = mvp_matrix * vec4(position, 1);
}
