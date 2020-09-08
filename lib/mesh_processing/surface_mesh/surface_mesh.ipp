/*--------------------------------------------------------------------------------
surface_mesh.ipp
    Template method implementations.
--------------------------------------------------------------------------------*/ 


/*--------------------------------------------------------------------------------
    ElementAttachment template methods.
--------------------------------------------------------------------------------*/
// Constructor
template <typename T>
ElementAttachment<T>::ElementAttachment(ElementPool &_pool) :
    ElementAttachmentBase(sizeof(T)),
    pool{_pool},
    data(_pool.capacity())
{
    // Set the base class's uint8_t pointer.
    raw_data = reinterpret_cast<uint8_t *>(&data[0]);

    pool.attachments.push_back(this);
}


// Destructor
template <typename T>
ElementAttachment<T>::~ElementAttachment()
{
    pool.attachments.erase(std::find(pool.attachments.begin(), pool.attachments.end(), this));
}


// Accessor.
template <typename T>
T &ElementAttachment<T>::get(ElementIndex element_index)
{
    assert(pool.is_active(element_index));
    return data[element_index];
}


// Virtual methods for shadowing the ElementPool.
template <typename T>
void ElementAttachment<T>::resize(size_t n)
{
    data.resize(n);
}


template <typename T>
void ElementAttachment<T>::create(ElementIndex element_index)
{
    // Default-initialize the entry.
    new (&data[element_index]) T;
}


template <typename T>
void ElementAttachment<T>::destroy(ElementIndex element_index)
{
    // Destroy the entry.
    data[element_index].~T();
}



/*--------------------------------------------------------------------------------
    Vertex, Edge, and Face element attachment template methods.
--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------
    VertexAttachment.
--------------------------------------------------------------------------------*/
template <typename T>
VertexAttachment<T>::VertexAttachment(SurfaceMesh &mesh) :
    ElementAttachment<T>(mesh.vertex_pool)
{}

template <typename T>
T &VertexAttachment<T>::operator[](const Vertex &vertex)
{
    return this->get(vertex.index());
}


/*--------------------------------------------------------------------------------
    EdgeAttachment.
--------------------------------------------------------------------------------*/
template <typename T>
EdgeAttachment<T>::EdgeAttachment(SurfaceMesh &mesh) :
    ElementAttachment<T>(mesh.edge_pool)
{}

template <typename T>
T &EdgeAttachment<T>::operator[](const Edge &edge)
{
    return this->get(edge.index());
}

template <typename T>
T &EdgeAttachment<T>::operator[](const Halfedge &halfedge)
{
    return this->get(halfedge.index() / 2);
}


/*--------------------------------------------------------------------------------
    FaceAttachment.
--------------------------------------------------------------------------------*/
template <typename T>
FaceAttachment<T>::FaceAttachment(SurfaceMesh &mesh) :
    ElementAttachment<T>(mesh.face_pool)
{}

template <typename T>
T &FaceAttachment<T>::operator[](const Face &face)
{
    return this->get(face.index());
}
