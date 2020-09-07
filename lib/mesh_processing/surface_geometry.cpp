#include "surface_geometry.h"


SurfaceGeometry::SurfaceGeometry(MLModel &model) :
    mesh(model.num_vertices)
{
    log("Creating surface geometry.");
}



