#version 420


uniform float inv_screen_width;
uniform float inv_screen_height;

uniform sampler2D image;
uniform sampler2D prev_image;
uniform sampler2D velocity;


in vec2 uv;
out vec4 color;


void main(void)
{
    vec2 f_velocity = texture(velocity, uv).xy;

    vec2 reproj = uv + (0.5*f_velocity+0.5);
    color = 0.5*texture(prev_image, reproj) + 0.5*texture(image, uv);
}


