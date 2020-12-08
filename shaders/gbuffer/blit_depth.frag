#version 420

// G-buffer
uniform sampler2D depth;

in vec2 screen_pos;
in vec2 uv;
in vec2 gbuffer_uv;

out vec4 color;

void main(void)
{
    gl_FragDepth = texture(depth, gbuffer_uv).r;
    color = vec4(1,0,1,1);
}

