#version 420
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

out GS_OUT {
    vec2 quad_position;
} gs_out;

uniform float half_width;
uniform float viewport_height_over_width;
uniform float inv_viewport_width_squared;
uniform float inv_viewport_height_squared;

void main(void)
{
    vec2 A = gl_in[0].gl_Position.xy;
    vec2 B = gl_in[1].gl_Position.xy;

    vec2 X = normalize(B - A);
    vec2 Y = half_width*vec2(-X.y * viewport_height_over_width, X.x);
    vec2 Yunit = normalize(vec2(-X.y * viewport_height_over_width, X.x));

    float antialiasing_pixel_extent = 2;
    float antialiasing_extent = 2*antialiasing_pixel_extent*sqrt(Yunit.x*Yunit.x*inv_viewport_width_squared + Yunit.y*Yunit.y*inv_viewport_height_squared);

    gl_Position = vec4(A + Y, -1,1);
    gs_out.quad_position = vec2(0,0);
    EmitVertex();
    gl_Position = vec4(A - Y, -1,1);
    gs_out.quad_position = vec2(0,1);
    EmitVertex();
    gl_Position = vec4(B + Y, -1,1);
    gs_out.quad_position = vec2(1,0);
    EmitVertex();
    gl_Position = vec4(B - Y, -1,1);
    gs_out.quad_position = vec2(1,1);
    EmitVertex();
    EndPrimitive();
}
