#ifndef SURFACE_GEOMETRY_H
#define SURFACE_GEOMETRY_H
#include "core.h"
#include "surface_mesh.h"

class SurfaceGeometry {
public:
    SurfaceGeometry(MLModel &model);

    // Creation interface.
    add_edge

    // Mutation interface.

private:
    SurfaceMesh mesh;
    ElementAttachment<vec3> vertex_positions;
    ElementAttachment<vec3> vertex_normals;
    ElementAttachment<vec3> face_normals;
};


#endif // SURFACE_GEOMETRY_H

