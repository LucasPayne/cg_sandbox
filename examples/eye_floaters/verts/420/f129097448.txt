#version 420
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float half_width;
uniform float viewport_height_over_width;
uniform float inv_viewport_width_squared;
uniform float inv_viewport_height_squared;

out GS_OUT {
    vec2 quad_position;
} gs_out;

void main(void)
{
    vec2 p = gl_in[0].gl_Position.xy;

    gl_Position = vec4(p + vec2(-half_width, half_width), -1,1);
    gs_out.quad_position = vec2(-1, 1);
    EmitVertex();
    gl_Position = vec4(p + vec2(-half_width, -half_width), -1,1);
    gs_out.quad_position = vec2(-1, -1);
    EmitVertex();
    gl_Position = vec4(p + vec2(half_width, half_width), -1,1);
    gs_out.quad_position = vec2(1, 1);
    EmitVertex();
    gl_Position = vec4(p + vec2(half_width, -half_width), -1,1);
    gs_out.quad_position = vec2(1, -1);
    EmitVertex();
    EndPrimitive();
}
