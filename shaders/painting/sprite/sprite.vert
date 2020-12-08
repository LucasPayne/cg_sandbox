#version 420

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
out vec2 f_uv;

void main(void)
{
    gl_Position = vec4(2*position - vec2(1,1), 0, 1);
    f_uv = uv;
}
