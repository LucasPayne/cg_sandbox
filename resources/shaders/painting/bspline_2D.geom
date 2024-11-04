#version 420
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

out GS_OUT {
    float quad_position;
    float extend_factor;
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
    // vec2 Ybase = vec2(-X.y * viewport_height_over_width, X.x);
    vec2 Ybase = vec2(-X.y, X.x); //----!! aspect ratio stuff has gone wrong.
    float Ybase_length = length(Ybase);
    vec2 Yunit = Ybase / Ybase_length;

    float antialiasing_pixel_extent = 1;
    float antialiasing_extent = 2*antialiasing_pixel_extent
                                *sqrt(Yunit.x*Yunit.x*inv_viewport_width_squared + Yunit.y*Yunit.y*inv_viewport_height_squared);

    vec2 extend_vector = (half_width*Ybase_length + antialiasing_extent) * Yunit;

    float extend_factor = (half_width*Ybase_length + antialiasing_extent) / half_width*Ybase_length - 1;

    gl_Position = vec4(A + extend_vector, -1,1);
    gs_out.quad_position = 1 + extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(A - extend_vector, -1,1);
    gs_out.quad_position = -extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(B + extend_vector, -1,1);
    gs_out.quad_position = 1 + extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(B - extend_vector, -1,1);
    gs_out.quad_position = -extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    EndPrimitive();
}
