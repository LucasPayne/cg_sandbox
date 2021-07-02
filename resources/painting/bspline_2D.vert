#version 420

layout(location = 0) in vec2 position;

out VS_OUT {
    vec2 position;
} vs_out;

void main(void)
{
    vs_out.position = vec2(2 * position.x - 1, 2 * position.y - 1);
}
