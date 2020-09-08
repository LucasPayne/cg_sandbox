#include "mesh_processing/surface_mesh/surface_mesh.h"


/*--------------------------------------------------------------------------------
    ElementPool implementations.
--------------------------------------------------------------------------------*/
ElementPool::ElementPool(size_t capacity) :
    active_flags(capacity),
    least_inactive_index{0}
{
    assert(capacity > 0);
    log("Creating new element pool of capacity %zu.", capacity);
}

size_t ElementPool::capacity() const
{
    return active_flags.size();
}


ElementIndex ElementPool::add()
{
    ElementIndex index = least_inactive_index;
    size_t n = capacity();
    for (; index < n; index++) {
        if (!is_active(index)) {
            break;
        }
    }
    assert(index != n); // note: An invariant maintained by ElementPool is that there is always at least one available entry.
    if (index == n - 1) {
        // The pool is full, grow it.
        size_t new_capacity = 2*n;
        active_flags.resize(new_capacity, 0);
        // Use the virtual resize() method to resize the attachments in the same way.
        // These new attachment entries will be value initialized, which uses the default constructor if available.
        for (auto attachment : attachments) {
            attachment->resize(new_capacity);
        }
    }
    for (auto attachment : attachments) {
        // Use the virtual create() method to create the default entry.
        attachment->create(index);
    }
    active_flags[index] = true;
    least_inactive_index = index+1;
    return index;
}


void ElementPool::remove(ElementIndex element_index)
{
    if (element_index < least_inactive_index) {
        least_inactive_index = element_index;
    }
    // Use the virtual destroy() method to tear down the entry.
    for (auto attachment : attachments) {
        attachment->destroy(element_index);
    }
}







ElementHandle::ElementHandle(SurfaceMesh &_mesh, ElementIndex _index) :
    mesh{_mesh}, m_index{_index}
{}



ElementAttachmentBase::ElementAttachmentBase(size_t _type_size) :
    type_size{_type_size}, raw_data{nullptr}
{}




Halfedge Vertex::halfedge() const
{
    return Halfedge(mesh, mesh.vertex_incidence_data[*this].halfedge_index);
}

Halfedge Edge::a() const
{
    return Halfedge(mesh, 2*m_index);
}
Halfedge Edge::b() const
{
    return Halfedge(mesh, 2*m_index + 1);
}

Halfedge Halfedge::next() const
{
    return Halfedge(mesh, mesh.edge_incidence_data[*this].halfedges[m_index % 2].next_index);
}
Vertex Halfedge::vertex() const
{
    return Vertex(mesh, mesh.edge_incidence_data[*this].halfedges[m_index % 2].vertex_index);
}
Face Halfedge::face() const
{
    return Face(mesh, mesh.edge_incidence_data[*this].halfedges[m_index % 2].face_index);
}

Halfedge Face::halfedge() const
{
    return Halfedge(mesh, mesh.face_incidence_data[*this].halfedge_index);
}



/*--------------------------------------------------------------------------------
    SurfaceMesh
--------------------------------------------------------------------------------*/
SurfaceMesh::SurfaceMesh() :
    vertex_incidence_data(*this),
    edge_incidence_data(*this),
    face_incidence_data(*this)
{
    log("Creating surface mesh.");
}


Vertex SurfaceMesh::add_vertex()
{
    log("Adding vertex.");
    return Vertex(*this, vertex_pool.add());
}
Face SurfaceMesh::add_triangle(Vertex u, Vertex v, Vertex w)
{

}
