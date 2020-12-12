#version 420

layout (location = 0) in vec2 position; // 0,0,  1,0,  1,1,  0,1

out vec2 uv;

void main(void)
{
    gl_Position = vec4(2*position-1, 0,1);
    uv = position;
}


