/*--------------------------------------------------------------------------------
surface_mesh.ipp
    Template method implementations.
--------------------------------------------------------------------------------*/ 


/*--------------------------------------------------------------------------------
    ElementAttachment template methods.
--------------------------------------------------------------------------------*/
// Constructor
template <typename T>
ElementAttachment::ElementAttachment(ElementPool &_pool) :
    data(_pool.capacity()),
    ElementAttachmentBase(sizeof(T), reinterpret_cast<uint8_t *>(&data[0])),
    pool{_pool}
{
    pool.attachments.push_back(this);
}


// Destructor
template <typename T>
ElementAttachment::~ElementAttachment()
{
    pool.attachments.erase(pool.attachments.find(this));
}


// Accessor.
template <typename T>
T &ElementAttachment::get(ElementIndex element_index)
{
    assert(pool.is_active(element_index));
    return data[element_index];
}


// Virtual methods for shadowing the ElementPool.
template <typename T>
virtual void ElementAttachment::resize(size_t n) final
{

}


template <typename T>
virtual void ElementAttachment::create(ElementIndex element_index) final
{

}


template <typename T>
virtual void ElementAttachment::destroy(ElementIndex element_index) final
{

}



/*--------------------------------------------------------------------------------
    Vertex, Edge, and Face element attachment template methods.
--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------
    VertexAttachment.
--------------------------------------------------------------------------------*/
template <typename T>
VertexAttachment::VertexAttachment(SurfaceMesh &mesh) :
    ElementAttachment<T>(mesh.vertex_pool)
{}

template <typename T>
T &VertexAttachment::operator[](const Vertex &vertex)
{
    return get(vertex.index);
}
