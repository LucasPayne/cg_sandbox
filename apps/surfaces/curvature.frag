#version 420

in vec2 f_curvatures;
uniform vec2 max_abs_curvatures;
uniform int mode;

out vec4 color;


void main(void)
{
    float g = f_curvatures.x;
    float m = f_curvatures.y;

    if (mode == 0) {
        // mean
        if (m > 0) color = vec4(m / max_abs_curvatures.y, 0,0,1);
        else color = vec4(0, 0, abs(m) / max_abs_curvatures.y,1);
    } else {
        // gaussian
        float max_abs_g = max_abs_curvatures.x;
        color = vec4(vec3(0.5 - 0.5*g/max_abs_g), 1);
    }
}
