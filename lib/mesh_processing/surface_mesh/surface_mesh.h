#ifndef SURFACE_MESH_H
#define SURFACE_MESH_H
#include "mesh_processing/core.h"


// typedefs
typedef uint32_t ElementIndex;

// forward declarations
class SurfaceMesh;
class ElementPool;
template <typename T> class ElementAttachment;
class ElementAttachmentBase;
class Vertex;
class Halfedge;
class Edge;
class Face;



/*--------------------------------------------------------------------------------
    ElementPool
--------------------------------------------------------------------------------*/
class ElementPool {
public:
    ElementPool(size_t capacity = 1);

    size_t capacity() const;
    ElementIndex add();
    void remove(ElementIndex element_index);

    inline bool is_active(ElementIndex element_index) const {
        return active_flags[element_index];
    }
    
private:
    std::vector<bool> active_flags;
    std::vector<ElementAttachmentBase *> attachments;

    // implementation details.
    ElementIndex least_inactive_index;

    template <typename T>
    friend class ElementAttachment;
};


class ElementAttachmentBase {
protected:
    ElementAttachmentBase(size_t _type_size);
    size_t type_size;
    uint8_t *raw_data;
    
private:
    // Virtual shadowing methods. These provide a generic interface to update the templated ElementAttachment's vector<T>
    // to match the layout of the ElementPool.
    virtual void resize(size_t n) = 0;
    virtual void create(ElementIndex element_index) = 0;
    virtual void destroy(ElementIndex element_index) = 0;

    friend class ElementPool; // ElementPool needs access to the virtual shadowing methods.
};


template <typename T>
class ElementAttachment : public ElementAttachmentBase {
public:
    ~ElementAttachment();
protected:
    ElementAttachment(ElementPool &_pool);
    T &get(ElementIndex element_index); // [] overload isn't used here since the only users are derived classes.
private:
    virtual void resize(size_t n) final;
    virtual void create(ElementIndex element_index) final;
    virtual void destroy(ElementIndex element_index) final;

    ElementPool &pool;
    std::vector<T> data;
};



/*--------------------------------------------------------------------------------
    Vertex, edge, and face attachments.
--------------------------------------------------------------------------------*/
template <typename T>
class VertexAttachment : public ElementAttachment<T> {
public:
    VertexAttachment(SurfaceMesh &mesh);
    T &operator[](const Vertex &vertex);
};


template <typename T>
class EdgeAttachment : public ElementAttachment<T> {
public:
    EdgeAttachment(SurfaceMesh &mesh);
    T &operator[](const Edge &edge);
    T &operator[](const Halfedge &halfedge); // Both halfedges map to the same edge attachment entry.
};


template <typename T>
class FaceAttachment : public ElementAttachment<T> {
public:
    FaceAttachment(SurfaceMesh &mesh);
    T &operator[](const Face &face);
};






struct VertexIncidenceData {
    // A halfedge index is 2*edge_index + subindex, where subindex is 0 or 1 according to the choice of halfedge.
    ElementIndex halfedge_index;
};
struct FaceIncidenceData {
    ElementIndex halfedge_index;
};
struct HalfedgeIncidenceData {
    ElementIndex next_index;
    ElementIndex vertex_index;
    ElementIndex face_index;
};
struct EdgeIncidenceData {
    HalfedgeIncidenceData halfedges[2];
};



class ElementHandle {
public:
    inline ElementIndex index() const { return m_index; }
protected:
    ElementHandle(SurfaceMesh &_mesh, ElementIndex _index);
    SurfaceMesh &mesh;
    ElementIndex m_index;
    friend class SurfaceMesh;
};

class Vertex : public ElementHandle {
public:
    Halfedge halfedge() const;
    Vertex(SurfaceMesh &_mesh, ElementIndex _index) :
        ElementHandle(_mesh, _index)
    {}
private:
    friend class SurfaceMesh;
};

class Edge : public ElementHandle {
public:
    Halfedge a() const;
    Halfedge b() const;
    Edge(SurfaceMesh &_mesh, ElementIndex _index) :
        ElementHandle(_mesh, _index)
    {}
private:
    friend class SurfaceMesh;
};


class Halfedge : public ElementHandle {
public:
    Halfedge next() const;
    Vertex vertex() const;
    Face face() const;
    Halfedge(SurfaceMesh &_mesh, ElementIndex _index) :
        ElementHandle(_mesh, _index)
    {}
private:
    friend class SurfaceMesh;
};


class Face : public ElementHandle {
public:
    Halfedge halfedge() const;
    Face(SurfaceMesh &_mesh, ElementIndex _index) :
        ElementHandle(_mesh, _index)
    {}
private:
    friend class SurfaceMesh;
};


class SurfaceMesh {
public:
    SurfaceMesh();

    
    // Creation methods.
    // These do not necessarily maintain invariants.
    Vertex add_vertex();
    Face add_triangle(Vertex u, Vertex v, Vertex w);

private:
    ElementPool vertex_pool;
    ElementPool edge_pool;
    ElementPool face_pool;
    VertexAttachment<VertexIncidenceData> vertex_incidence_data;
    EdgeAttachment<EdgeIncidenceData> edge_incidence_data;
    FaceAttachment<FaceIncidenceData> face_incidence_data;


    template <typename T>
    friend class ElementAttachment;
    template <typename T>
    friend class VertexAttachment;
    template <typename T>
    friend class EdgeAttachment;
    template <typename T>
    friend class FaceAttachment;

    friend class Vertex;
    friend class Edge;
    friend class Halfedge;
    friend class Face;
};




#include "surface_mesh.ipp"

#endif // SURFACE_MESH_H
