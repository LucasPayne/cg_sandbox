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
    std::vector<vec3> positions;
};


#endif // SURFACE_GEOMETRY_H

