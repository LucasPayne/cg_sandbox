#ifndef SURFACE_MESH_H
#define SURFACE_MESH_H
#include "core.h"
#include "element_pool.h"



enum ElementTypes {
    ElementTypeVertex,
    ElementTypeHalfEdge,
    ElementTypeFace,
    NUM_ELEMENT_TYPES
};
typedef uint8_t ElementType;




class SurfaceMesh;
struct ElementHandle {
    SurfaceMesh *mesh;
    ElementIndex index;
    ElementHandle(SurfaceMesh *_mesh, ElementIndex _index) :
        mesh{_mesh}, index{_index}
    {}
};
struct HalfEdge;
struct Face; // forward-declare elements.
struct Vertex : public ElementHandle {
    HalfEdge halfedge();
    using ElementHandle::ElementHandle;
};
struct HalfEdge : public ElementHandle {
    HalfEdge next();
    HalfEdge flip();
    Vertex vertex();
    Face face();
    using ElementHandle::ElementHandle;
};
struct Face : public ElementHandle {
    HalfEdge halfedge();
    using ElementHandle::ElementHandle;
};

struct HalfEdgeData {
    ElementIndex next;
    ElementIndex vertex;
    ElementIndex face;
};
struct VertexData {
    ElementIndex halfedge;
};
struct FaceData {
    ElementIndex halfedge;
};



class SurfaceMesh {
public:
    SurfaceMesh(size_t num_vertices);

private:
    ElementPool<HalfEdgeData> halfedge_data;
    ElementPool<VertexData> vertex_data;
    ElementPool<FaceData> face_data;
    // Get the pool for the given element type at runtime.
    ElementPoolBase *element_pool(ElementPoolType element_type);

    friend class Vertex;
    friend class HalfEdge;
    friend class Face;
    template <typename T>
    friend class ElementAttachment;
};

#include "element_attachment.h"

#endif // SURFACE_MESH_H
