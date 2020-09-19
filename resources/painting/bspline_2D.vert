#version 420

layout(location = 0) in vec2 position;

void main(void)
{
    gl_Position = vec4(2 * position.x - 1, 2 * position.y - 1, 1,1);
}
