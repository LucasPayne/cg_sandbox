#include "mesh_processing/surface_geometry/surface_geometry.h"
#include <iomanip>


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

void SurfaceGeometry::write_OFF(std::ostream &out)
{
    // Vertex indices in the ElementPool sense are not necessarily contiguous.
    // So, a temporary attachment is used to give contiguous indices to the vertices.
    auto vertex_indices = VertexAttachment<uint32_t>(mesh);

    out << "OFF\n";
    out << mesh.num_vertices() << " " << mesh.num_faces() << " 0\n";
    int index = 0;
    for (auto vertex : mesh.vertices()) {
        vertex_indices[vertex] = index; // Give the vertices contiguous indices.
        vec3 position = vertex_positions[vertex];
        out << std::fixed << std::setprecision(6) << position.x() << " " << position.y() << " " << position.z() << "\n";
        index ++;
    }
    for (auto face : mesh.faces()) {
        out << face.num_vertices();
        auto start = face.halfedge();
        auto he = start;
        do {
            uint32_t vertex_index = vertex_indices[he.vertex()];
            out << " " << vertex_index;
            he = he.next();
        } while (start != he);
        out << "\n";
    }
}
