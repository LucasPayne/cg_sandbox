#version 420

uniform vec4 color;
out vec4 fb_color;

in GS_OUT {
    float quad_position;
    float extend_factor;
} fs_in;

float alpha_curve(float x)
{
    x = 2*x - 1;
    return 0.3*exp(-100*pow(x-0.8, 2)) + 0.3*exp(-100*pow(x+0.8, 2)) + 0.3*exp(-80*pow(x-0.5,2)) + 0.3*exp(-80*pow(x+0.5,2)) + 0.25*exp(-10*x*x);
}

void main(void)
{
    #if 0 // debug
    if (fs_in.quad_position < 0 || fs_in.quad_position > 1) {
        fb_color = vec4(1,0,1,1);
    } else {
        fb_color = color;
    }
    #else

    float alpha = (alpha_curve(fs_in.quad_position-0.03)+alpha_curve(fs_in.quad_position)+alpha_curve(fs_in.quad_position+0.03))/3;

    float coverage_multiplier = min(1-smoothstep(1, 1+fs_in.extend_factor, fs_in.quad_position),
                      smoothstep(-fs_in.extend_factor, 0, fs_in.quad_position));
    fb_color = vec4(color.rgb, color.a * alpha * coverage_multiplier);


    #endif
    
    fb_color = vec4(1,0,0,1);
}
