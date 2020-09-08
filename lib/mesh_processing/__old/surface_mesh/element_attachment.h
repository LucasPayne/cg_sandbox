#ifndef ELEMENT_ATTACHMENT_H
#define ELEMENT_ATTACHMENT_H
// Included from surface_mesh.h


// Abstract non-templated base class.
class ElementAttachmentBase {
public:
    ElementType element_type() const { return m_element_type; }

    ElementAttachment(const ElementAttachment<T> &other); // Copy constructor.
    ElementAttachment<T>& operator=(const ElementAttachment<T> &other); // Copy assignment.
};


template <typename T>
class ElementAttachment : public ElementAttachmentBase {
public:
    ElementType element_type() const { return m_element_type; }

    ElementAttachment(const ElementAttachment<T> &other); // Copy constructor.
    ElementAttachment<T>& operator=(const ElementAttachment<T> &other); // Copy assignment.
    ~ElementAttachment(); // Destructor.
protected:
    ElementAttachment(SurfaceMesh &_mesh, ElementType _element_type);

    ElementPoolBase *element_pool;
    ElementType m_element_type;

    std::vector<T> data;
private:
    ElementAttachment(ElementPool *_element_pool, ElementType _element_type);
};


template <typename T>
struct VertexAttachment : public ElementAttachment<T> {
    VertexAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeVertex) {};
};
template <typename T>
struct HalfEdgeAttachment : public ElementAttachment<T> {
    HalfEdgeAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeHalfEdge) {};
};
template <typename T>
class FaceAttachment : public ElementAttachment<T> {
    FaceAttachment(SurfaceMesh &_mesh) : ElementAttachment(_mesh, ElementTypeFace) {};
};


/*--------------------------------------------------------------------------------
    Template method implementations.
--------------------------------------------------------------------------------*/
// Constructor
template <typename T>
ElementAttachment<T>::ElementAttachment(SurfaceMesh &_mesh, ElementType _element_type) :
    ElementAttachment(_mesh.element_pool(m_element_type), _element_type)
{}


template <typename T>
ElementAttachment<T>::ElementAttachment(ElementPoolBase *_element_pool, ElementType _element_type) :
    m_element_type{_element_type}
{
    // Initialize the attachment to the same capacity as the element pool.
    size_t capacity = element_pool->capacity();
    data = std::vector<T>(capacity);
    element_pool->attach(this);
}

// Destructor
template <typename T>
ElementAttachment<T>::~ElementAttachment()
{
    element_pool->detach(this);
}



#endif // ELEMENT_ATTACHMENT_H
