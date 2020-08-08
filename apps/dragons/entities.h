


/*--------------------------------------------------------------------------------
Entity
    The Entity is a handle to a collection of aspects.
    The data in an Entity is the minimal data necessary for finding its aspects.
--------------------------------------------------------------------------------*/
struct Entity {
public:
    Entity(WorldReference _world, TableHandle _handle) :
        world{_world}, handle{_handle}
    {}
    void destroy();
    template <typename TYPE>
    Aspect<TYPE> add();
    template <typename TYPE>
    Aspect<TYPE> get();
private:
    WorldReference world;
    TableHandle handle;
};


/*--------------------------------------------------------------------------------
Aspect<TYPE>
    An Aspect is a handle to data associated to an entity.
    The data in an Aspect is the minimal data necessary for finding its data and
    related aspects.

    Aspects are a parameterized type, meaning that 
--------------------------------------------------------------------------------*/
template <typename TYPE>
struct Aspect {
    friend Entity;
public:
    TYPE &operator*();
    TYPE *operator->();

    Entity entity();
    
    template <typename SIBLING_TYPE>
    Aspect<SIBLING_TYPE> sibling();

    void destroy();
private:
    Aspect(WorldReference _world, TableCollectionHandle<TYPE> _handle);

    TableCollectionHandle<TYPE> handle;
    WorldReference world;
};


namespace details {
// Non-API declarations. These are meaningful only to the implementation.
/*--------------------------------------------------------------------------------
TypedAspect
    Sometimes generic aspect handles are wanted, such as in the implementation
    of the aspect linked list.
--------------------------------------------------------------------------------*/
struct TypedAspect {
    WorldReference world;
    TypedTableCollectionHandle handle;
    AspectBase &operator*();
    AspectBase *operator->();
};


/*--------------------------------------------------------------------------------
AspectBase
    Each entry in the aspect tables has a common base of data, given here.
--------------------------------------------------------------------------------*/
struct AspectBase {
    Entity entity;
    TypedAspect next_aspect;
};
} // end namespace details


class EntityModel {
    template <typename T> friend Aspect<T>;
    friend Entity;
public:
    template <typename TYPE>
    void register_aspect_type(const std::string &name);

    Entity new_entity();
    EntityModel(WorldReference _world);

    EntityIterator entities();
    template <typename TYPE>
    AspectIterator<TYPE> aspects();
private:
    WorldReference world;
    Table<Entity> entity_table;
    TableCollection<details::AspectBase> aspect_tables;
};


// Template implementations.
//--------------------------------------------------------------------------------

// Entity
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE> Entity::add()
{
    TableCollectionHandle<TYPE> handle = world->em.aspect_tables.add<TYPE>();
    return Aspect<TYPE>
}
template <typename TYPE>
Aspect<TYPE> Entity::get()
{

}
// Aspect<TYPE>
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE>::Aspect<TYPE>(WorldReference _world, TableCollectionHandle<TYPE> _handle) :
    world{_world}, handle{_handle}
{}

template <typename TYPE>
TYPE &Aspect<TYPE>::operator*()
{
    TYPE *asp = world->em.aspects.lookup<TYPE>(handle);
    if (asp == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid aspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp;
}
template <typename TYPE>
TYPE *Aspect<TYPE>::operator->()
{
    return &(*(*this));
}

template <typename TYPE, typename SIBLING_TYPE>
Aspect<SIBLING_TYPE> Aspect<TYPE>::sibling()
{

}


// EntityModel
//--------------------------------------------------------------------------------
EntityModel::EntityModel(WorldReference _world) :
    world{_world}
{
    // Initialize the entity model for a new world.
    const size_t entity_table_start_length = 16;
    entity_table = Table<Entity>(entity_table_start_length);
    aspect_tables = TableCollection<AspectBase>(1);
}
template <typename TYPE>
void register_aspect_type(const std::string &name)
{

}


// AspectBase
//--------------------------------------------------------------------------------
AspectBase &AspectBase::operator*()
{
    AspectBase *asp_base = world->em.aspects.lookup(handle);
    if (asp == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid aspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp_base;
}
AspectBase *AspectBase::operator->()
{
    return &(*(*this));
}

