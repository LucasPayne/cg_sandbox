#include "mesh_processing/surface_mesh/surface_mesh.h"


/*--------------------------------------------------------------------------------
    ElementPool implementations.
--------------------------------------------------------------------------------*/
ElementPool::ElementPool(size_t capacity) :
    active_flags(capacity),
    least_inactive_index{0}
{
    assert(capacity > 0);
}

size_t ElementPool::capacity() const
{
    return active_flags.size();
}


ElementIndex ElementPool::add()
{
    ElementIndex index = least_inactive_index;
    size_t n = capacity();
    int i = index;
    for (; i < n; i++) {
        if (!is_active(i)) {
            break;
        }
    }
    assert(i != n); // note: An invariant maintained by ElementPool is that there is always at least one available entry.
    if (i == n - 1) {
        // The pool is full, grow it.
        size_t new_capacity = 2*n;
        active_flags.resize(new_capacity, 0);
        // Use the virtual resize() method to resize the attachments in the same way.
        // These new attachment entries will be value initialized, which uses the default constructor if available.
        for (auto attachment : attachments) {
            attachment->resize(new_capacity);
        }
    }
    // Use the virtual create() method to create the default entry.
    attachment->create(i);
    active_flags[i] = true;
    least_inactive_index = i+1;
}


void ElementPool::remove(ElementIndex element_index)
{
    if (element_index < least_inactive_index) {
        least_inactive_index = element_index;
    }
    // Use the virtual destroy() method to tear down the entry.
    attachment->destroy(element_index);
}




SurfaceMesh::SurfaceMesh() :
    vertex_incidence_data(*this),
    edge_incidence_data(*this),
    face_incidence_data(*this),
{
}




ElementHandle(SurfaceMesh &_mesh, ElementIndex _index) :
    mesh{_mesh}, index{_index}
{}



ElementAttachmentBase::ElementAttachmentBase(size_t _type_size, uint8_t *_data) :
    type_size{_type_size}, data{_data}
{}




Halfedge Vertex::halfedge() const
{
    return Halfedge(mesh, mesh.vertex_incidence_data[*this].halfedge_index);
}

Halfedge Edge::a() const
{
    return Halfedge(mesh, 2*index);
}
Halfedge Edge::b() const
{
    return Halfedge(mesh, 2*index + 1);
}

Halfedge Halfedge::next() const
{
    return Halfedge(mesh, mesh.edge_incidence_data[*this].halfedges[index % 2].next_index);
}
Vertex Halfedge::vertex() const
{
    return Vertex(mesh, mesh.edge_incidence_data[*this].halfedges[index % 2].vertex_index);
}
Face Halfedge::face() const
{
    return Face(mesh, mesh.edge_incidence_data[*this].halfedges[index % 2].face_index);
}

Halfedge Face::halfedge() const
{
    return Halfedge(mesh, mesh.face_incidence_data[*this].halfedge_index);
}
