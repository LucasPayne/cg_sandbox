#include "mesh_processing/surface_geometry/surface_geometry.h"


Vertex SurfaceGeometry::add_vertex(vec3 position)
{
    auto vertex = mesh.add_vertex();
    vertex_positions[vertex] = position;
    return vertex;
}

Vertex SurfaceGeometry::add_vertex(float x, float y, float z)
{
    return add_vertex(vec3(x, y, z));
}

Face SurfaceGeometry::add_triangle(Vertex v1, Vertex v2, Vertex v3)
{
    vec3 a = vertex_positions[v1];
    vec3 b = vertex_positions[v2];
    vec3 c = vertex_positions[v3];
    vec3 n = vec3::cross(b - a, c - a).normalized();
    auto face = mesh.add_triangle(v1, v2, v3);
    face_normals[face] = n;
    return face;
}


void SurfaceGeometry::printout()
{
    mesh.printout();
    printf("SurfaceGeometry attachments\n");
    printf("------------------------------------------------------------\n");
    for (auto vertex : mesh.vertices()) {
        std::cout << vertex_positions[vertex] << "\n";
    }
    printf("------------------------------------------------------------\n");
    getchar();
}
