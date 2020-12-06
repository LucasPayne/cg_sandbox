// Vertex shader for post-processing quads.
// This quad is always formed by vertices 0,0,  1,0,  1,1,  0,1.

// The uv quad is the quad read from for standard full-size textures (the read-post-buffer).
// The gbuffer uv quad gives the quad to read from the gbuffer.


#version 420

uniform vec4 uv_quad;
uniform vec4 gbuffer_uv_quad;

layout (location = 0) in vec2 position; // 0,0,  1,0,  1,1,  0,1

out vec2 screen_pos;
out vec2 uv;
out vec2 gbuffer_uv;

void main(void)
{
    gl_Position = vec4(2*position - 1, 0,1);
    screen_pos = gl_Position.xy;
    uv = uv_quad.xy + uv_quad.zw * position;
    gbuffer_uv = gbuffer_uv_quad.xy + gbuffer_uv_quad.zw * position;
}
