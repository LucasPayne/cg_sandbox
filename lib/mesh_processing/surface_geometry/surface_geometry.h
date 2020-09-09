#ifndef SURFACE_GEOMTRY_H
#define SURFACE_GEOMTRY_H
#include "spatial_algebra/spatial_algebra.h"
#include "mesh_processing/surface_mesh/surface_mesh.h"


class SurfaceGeometry {
private:
    SurfaceMesh mesh;
public:
    Vertex add_vertex(vec3 position);
    Vertex add_vertex(float x, float y, float z);
    Face add_triangle(Vertex v1, Vertex v2, Vertex v3);

    SurfaceGeometry() :
        mesh(),
        vertex_positions(mesh),
        vertex_normals(mesh),
        face_normals(mesh)
    {}

    void printout();

    VertexAttachment<vec3> vertex_positions;
    VertexAttachment<vec3> vertex_normals;
    FaceAttachment<vec3> face_normals;
};


#endif // SURFACE_GEOMTRY_H
