#ifndef MESH_PROCESSING_H
#define MESH_PROCESSING_H
#include <vector>
#include <numeric_limits>
#include "model_loader/model_loader.h"
#include "spatial_algebra/spatial_algebra.h"


typedef uint32_t ElementIndex;
constexpr ElementIndex InvalidElementIndex = std::numeric_limits<ElementIndex>::max();


struct ElementHandle {
    SurfaceMesh *mesh;
    ElementIndex index;
    ElementHandle(SurfaceMesh *_mesh, ElementIndex _index) :
        mesh{_mesh}, index{_index}
    {}
};
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

    friend class Vertex;
    friend class HalfEdge;
    friend class Face;
};


class SurfaceGeometry {
public:
    SurfaceGeometry(MLModel &model);

private:
    SurfaceMesh mesh;
    std::vector<vec3> positions;
};



#endif // MESH_PROCESSING_H
