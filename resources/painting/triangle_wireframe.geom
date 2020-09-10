#version 420

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 position;
    vec2 screen_position;
} gs_in[];

out GS_OUT {
    noperspective vec3 distances;
    vec3 normal;
} gs_out;

uniform float half_width;
uniform mat4x4 vp_matrix;
uniform mat4x4 model_matrix;

void main(void)
{

    // Compute the vertices of the internal triangle whose boundary is distance half_width
    // away from this triangle.
    vec3 n = normalize(cross(gs_in[1].position - gs_in[0].position, gs_in[2].position - gs_in[0].position));
    vec2 screenspace_internal_triangle_vertices[3];
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        int k = (i + 2) % 3;
        vec3 pi = gs_in[i].position;
        vec3 pj = gs_in[j].position;
        vec3 pk = gs_in[k].position;

        vec3 h1 = pi + half_width * normalize(cross(n, pj - pi));
        vec3 h2 = pi + half_width * normalize(cross(pk - pi, n));
        vec3 d1 = normalize(pj - pi);
        vec3 d2 = normalize(pk - pi);

        vec3 d_diff = d1 - d2;
        float t = -dot(h1 - h2, d_diff) / dot(d_diff, d_diff); //possible issue: unstable for d1 near d2.
        vec3 p = h1 + t*d1; // Could alternatively use h2 + t*d2.
        
        // Transform p into screenspace.
        vec4 p_h = vp_matrix * model_matrix * vec4(p, 1);
        vec2 p_screen = p_h.xy / p_h.w;

        screenspace_internal_triangle_vertices[i] = p_screen;
    }


    // Output the new triangle vertex attributes.
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        int k = (i + 2) % 3;
        vec2 pi = gs_in[i].screen_position;
        vec2 pj = gs_in[j].screen_position;
        vec2 pk = gs_in[k].screen_position;

        vec2 e1 = screenspace_internal_triangle_vertices[j];
        vec2 e2 = screenspace_internal_triangle_vertices[k];

        // Compute the distance of the triangle vertex to the opposite internal triangle edge in screenspace.
        vec2 dir = normalize(e2 - e1);
        vec2 p_proj = e1 + dir*dot(pi - e1, dir);
        gs_out.distances[i] = length(pi - p_proj);
        // The other points, on the other side of the internal edge, have their negative distance to this internal edge computed.
        p_proj = e1 + dir*dot(pj - e1, dir);
        gs_out.distances[j] = -length(pj - p_proj);
        p_proj = e1 + dir*dot(pk - e1, dir);
        gs_out.distances[k] = -length(pk - p_proj);

        gl_Position = gl_in[i].gl_Position;
        gs_out.normal = n; // Give each vertex the triangle normal for flat shading.
        EmitVertex();
    }
    EndPrimitive();
}
