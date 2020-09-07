#ifndef ELEMENT_ATTACHMENT_H
#define ELEMENT_ATTACHMENT_H
// Included from surface_mesh.h



enum ElementTypes {
    ElementTypeVertex,
    ElementTypeHalfEdge,
    ElementTypeFace,
    NUM_ELEMENT_TYPES
};
typedef uint8_t ElementType;


template <typename T>
class ElementAttachment {
public:
    ElementType element_type() const { return m_element_type; }

    ElementAttachment(const ElementAttachment &other); // Copy constructor.
    ElementAttachment& operator=(const ElementAttachment &other); // Copy assignment.
protected:
    ElementAttachment(SurfaceMesh &_mesh, ElementType _element_type);

    SurfaceMesh *mesh;
    ElementType m_element_type;
};


template <typename T>
struct VertexAttachment : public ElementAttachment<T> {
    VertexAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeVertex) {};
};
template <typename T>
struct HalfEdgeAttachment : public ElementAttachment<T> {
    HalfEdgeAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeVertex) {};
};
template <typename T>
class FaceAttachment : public ElementAttachment<T> {
    FaceAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeFace) {};
};




#endif // ELEMENT_ATTACHMENT_H
