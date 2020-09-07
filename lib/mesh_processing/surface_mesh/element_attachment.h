#ifndef ELEMENT_ATTACHMENT_H
#define ELEMENT_ATTACHMENT_H

class SurfaceMesh; // forward-declare SurfaceMesh

template <typename T>
class ElementAttachment {
public:
    ElementAttachment(SurfaceMesh &_mesh, ElementType _element_type);
    ElementType element_type() const { return m_element_type; }

    ElementAttachment(const ElementAttachment &other); // Copy constructor.
    ElementAttachment& operator=(const ElementAttachment &other); // Copy assignment.
    ~ElementAttachment(); // Destructor.
private:
    SurfaceMesh *mesh;
    ElementType m_element_type;
};


#endif // ELEMENT_ATTACHMENT_H
