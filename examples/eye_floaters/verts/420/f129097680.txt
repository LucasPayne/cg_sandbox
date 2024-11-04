#version 420

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

out vec2 uv;

void main(void)
{
    gl_Position = vec4(v_position, 0,1);
    uv = v_uv;
}


