#ifndef SURFACE_MESH_H
#define SURFACE_MESH_H
#include "core.h"

typedef uint32_t ElementIndex;



class ElementPool {
public:
    ElementPool(size_t capacity = 1);

    size_t capacity() const;
    ElementIndex add();
    void remove(ElementIndex element_index);

    inline bool is_active(ElementIndex element_index) const {
        // Check if a slot is active. It useful to use this check for debugging.
        return element_index >= 0 && element_index < capacity() && active_flags[element_index];
    }
    
private:
    std::vector<bool> active_flags;
    std::vector<ElementAttachmentBase *> attachments;
};


class ElementAttachmentBase {
protected:
    ElementAttachmentBase(size_t _type_size, uint8_t *_data);
    size_t type_size;
    uint8_t *data;
private:
    
};


template <typename T>
class ElementAttachment : public ElementAttachmentBase {
public:
    ~ElementAttachment();
protected:
    ElementAttachment(ElementPool &_pool);
    T &get(ElementIndex element_index); // [] overload isn't used here since the only users are derived classes.
private:
    std::vector<T> data;
    ElementPool &pool;
};



template <typename T>
class VertexAttachment : public ElementAttachment<T> {
public:
    VertexAttachment(SurfaceMesh &mesh);
    T &operator[](const Vertex &vertex);
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
protected:
    ElementHandle(SurfaceMesh &_mesh, ElementIndex _index);
    SurfaceMesh &mesh;
    ElementIndex index;
    friend class SurfaceMesh;
};

class Vertex : public ElementHandle {
public:
    Halfedge halfedge() const;
private:
    using ElementHandle::ElementHandle;
    friend class SurfaceMesh;
};

class Edge : public ElementHandle {
public:
    Halfedge a() const;
    Halfedge b() const;
private:
    using ElementHandle::ElementHandle;
    friend class SurfaceMesh;
};


class Halfedge : public ElementHandle {
public:
    Halfedge next() const;
    Vertex vertex() const;
    Face face() const;
private:
    using ElementHandle::ElementHandle;
    friend class SurfaceMesh;
};


class Face : public ElementHandle {
public:
    Halfedge halfedge() const;
private:
    using ElementHandle::ElementHandle;
    friend class SurfaceMesh;
};


class SurfaceMesh {
public:
    SurfaceMesh();

private:
    ElementPool vertex_pool;
    ElementPool edge_pool;
    ElementPool face_pool;
    VertexAttachment<VertexIncidenceData> vertex_incidence_data;
    EdgeAttachment<EdgeIncidenceData> edge_incidence_data;
    FaceAttachment<FaceIncidenceData> face_incidence_data;
};




#include "surface_mesh.ipp"

#endif // SURFACE_MESH_H