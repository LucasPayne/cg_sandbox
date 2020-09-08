#include "surface_mesh.h"


SurfaceMesh::SurfaceMesh(size_t num_vertices) :
    vertex_data(num_vertices)
{
    log("Creating surface mesh with %zu vertices.");
    element_pools[ElementTypeVertex] = &vertex_data;
    element_pools[ElementTypeHalfEdge] = &half_edge_data;
    element_pools[ElementTypeFace] = &face_data;
}

HalfEdge HalfEdge::next()
{
    return HalfEdge(mesh, mesh->halfedge_data.get(index)->next);
}
HalfEdge HalfEdge::flip()
{
    // HalfEdge indices come in pairs for each edge.
    // ^ 1 flips the last bit, meaning odd indices are decremented, even indices are incremented.
    return HalfEdge(mesh, index ^ 1);
}
Vertex HalfEdge::vertex()
{
    return Vertex(mesh, mesh->halfedge_data.get(index)->vertex);
}
Face HalfEdge::face()
{
    return Face(mesh, mesh->halfedge_data.get(index)->face);
}

HalfEdge Face::halfedge()
{
    return HalfEdge(mesh, mesh->face_data.get(index)->halfedge);
}
HalfEdge Vertex::halfedge()
{
    return HalfEdge(mesh, mesh->vertex_data.get(index)->halfedge);
}



ElementPoolBase *element_pool(ElementPoolType element_type)
{
    if (element_type == ElementTypeVertex) return &vertex_data;
    if (element_type == ElementTypeHalfEdge) return &halfedge_data;
    if (element_type == ElementTypeFace) return &face_data;
    return nullptr;
}