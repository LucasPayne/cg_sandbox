#version 420


uniform vec4 color;
out vec4 fb_color;

in GS_OUT {
    float quad_position;
    float extend_factor;
} fs_in;

void main(void)
{
    #if 0 // debug
    if (fs_in.quad_position < 0 || fs_in.quad_position > 1) {
        fb_color = vec4(1,0,1,1);
    } else {
        fb_color = color;
    }
    #else

    float alpha = min(1-smoothstep(1, 1+fs_in.extend_factor, fs_in.quad_position),
                      smoothstep(-fs_in.extend_factor, 0, fs_in.quad_position));

    fb_color = vec4(color.rgb, alpha);

    #endif
}
