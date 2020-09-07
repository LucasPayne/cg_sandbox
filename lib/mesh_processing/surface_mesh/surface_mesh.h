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



template <typename T>
using VertexAttachment = ElementAttachment<Vertex, T>;
template <typename T>
using HalfEdgeAttachment = ElementAttachment<HalfEdge, T>;
template <typename T>
using FaceAttachment = ElementAttachment<Face, T>;


class SurfaceMesh {
public:
    SurfaceMesh(size_t num_vertices);
private:
    ElementPool<HalfEdgeData> halfedge_data;
    ElementPool<VertexData> vertex_data;
    ElementPool<FaceData> face_data;

    std::vector<std::shared_ptr<ElementAttachment>> attachments;

    friend class Vertex;
    friend class HalfEdge;
    friend class Face;
};

#include "element_attachment.h"

#endif // SURFACE_MESH_H
