#version 420

in vec2 f_curvatures;

out vec4 color;

void main(void)
{
    float g = f_curvatures.x;
    float m = f_curvatures.y;

    color = vec4(m, 0,0,1);
}
