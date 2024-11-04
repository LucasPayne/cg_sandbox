#version 420
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;
// layout (line_strip, max_vertices = 2) out;

in VS_OUT {
    vec3 position;
} gs_in[];

out GS_OUT {
    float quad_position;
    float extend_factor;
} gs_out;

uniform float half_width;
uniform float viewport_height_over_width;
uniform float inv_viewport_width_squared;
uniform float inv_viewport_height_squared;

uniform mat4x4 mvp_matrix;

void main(void)
{
    // gl_Position = mvp_matrix * vec4(gs_in[0].position + vec3(0,1,0), 1);
    // EmitVertex();
    // gl_Position = mvp_matrix * vec4(gs_in[1].position, 1);
    // EmitVertex();
    // EndPrimitive();

    vec4 pos_A_h = mvp_matrix * vec4(gs_in[0].position, 1);
    vec4 pos_B_h = mvp_matrix * vec4(gs_in[1].position, 1);
    vec3 pos_A = pos_A_h.xyz / pos_A_h.w;
    vec3 pos_B = pos_B_h.xyz / pos_B_h.w;
    vec2 A = pos_A.xy;
    vec2 B = pos_B.xy;

    vec2 X = normalize(B - A);
    vec2 Ybase = vec2(-X.y, X.x); //----!! aspect ratio stuff has gone wrong.
    float Ybase_length = length(Ybase);
    vec2 Yunit = Ybase / Ybase_length;

    float hw = half_width;

    float antialiasing_pixel_extent = 1;
    float antialiasing_extent = 2*antialiasing_pixel_extent
                                *sqrt(Yunit.x*Yunit.x*inv_viewport_width_squared + Yunit.y*Yunit.y*inv_viewport_height_squared);

    vec2 extend_vector = (hw*Ybase_length + antialiasing_extent) * Yunit;

    float extend_factor = (hw*Ybase_length + antialiasing_extent) / hw*Ybase_length - 1;

    gl_Position = vec4(A + extend_vector, pos_A.z,1);
    gs_out.quad_position = 1 + extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(A - extend_vector, pos_A.z,1);
    gs_out.quad_position = -extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(B + extend_vector, pos_B.z,1);
    gs_out.quad_position = 1 + extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    gl_Position = vec4(B - extend_vector, pos_B.z,1);
    gs_out.quad_position = -extend_factor;
    gs_out.extend_factor = extend_factor;
    EmitVertex();
    EndPrimitive();
}
