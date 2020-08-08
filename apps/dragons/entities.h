#include "data_structures/table.h"
#include "world/world_reference.h"


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
EntityEntry
    An entry in the entity table. The aspects can be traversed starting here.
--------------------------------------------------------------------------------*/
struct EntityEntry {
    TypedAspect first_aspect;
};
} // end namespace details


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
    details::EntityEntry *get_entry();

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
    Aspect();

    TableCollectionHandle<TYPE> handle;
    WorldReference world;
};


namespace details {
/*--------------------------------------------------------------------------------
AspectBase
    Each entry in the aspect tables has a common base of data, given here.
--------------------------------------------------------------------------------*/
struct AspectBase {
    Entity entity;
    TypedAspect next_aspect;
};


/*--------------------------------------------------------------------------------
AspectTypeStaticData
--------------------------------------------------------------------------------*/
typedef TableCollectionType AspectType;


template <typename T>
struct AspectTypeStaticData {
    static AspectType type_id;
};


// Statically initialize the aspect type ID to null.
template <typename T>
AspectType AspectTypeStaticData<T>::type_id(NULL_TABLE_COLLECTION_TYPE_ID);


} // end namespace details


/*--------------------------------------------------------------------------------
IAspectType<T>
    When defining an aspect type T, inherit from IAspectType<T>. In this way,
    static data for the aspect type is initialized, and the actual aspect-instance
    data struct is defined in the body.

    This global variable for the ID allows aspect type template parameters to be convertible
    to actual type IDs, through TYPE::type_id. For example, entity.add<Transform>() will
    internally use Transform::type_id.
--------------------------------------------------------------------------------*/
template <typename T>
struct IAspectType : details::AspectTypeStaticData<T>, public AspectBase {
};


class EntityModel {
    template <typename T> friend Aspect<T>;
    friend Entity;
public:
    template <typename TYPE>
    void register_aspect_type(const std::string &name);

    Entity new_entity();
    EntityModel(WorldReference _world);

    GenericTable::Iterator entities();
    template <typename TYPE>
    GenericTable::Iterator aspects();
private:
    WorldReference world;
    Table<Entity> entity_table;
    TableCollection<details::AspectBase> aspect_tables;
};


// Template implementations.
//--------------------------------------------------------------------------------

// Entity
//--------------------------------------------------------------------------------
Entity::Entity(WorldReference _world, TableHandle _handle) :
    world{_world}, handle{_handle}
{}


template <typename TYPE>
Aspect<TYPE> Entity::add()
{
    TableCollectionHandle<TYPE> handle = world->em.aspect_tables.add<TYPE>();
    return Aspect<TYPE>(world, handle);
}


template <typename TYPE>
Aspect<TYPE> Entity::get()
{
    AspectType aspect_type = TYPE::type_id;
    details::EntityEntry *entry = get_entry();

    // Search this entity's aspects.
    TypedAspect cur = entry->first_aspect;
    while (cur.handle.id != 0) {
        if (cur.handle.type == aspect_type) {
            return Aspect<TYPE>(cur); // Convert the typed handle into a regular handle.
        }
        cur = cur->next_aspect;
    }
    fprintf(stderr, "[entity_model] ERROR: Attempted to get non-existent aspect from entity.\n");
    exit(EXIT_FAILURE);
}


void Entity::destroy()
{
    //todo
}


// Aspect<TYPE>
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE>::Aspect<TYPE>(WorldReference _world, TableCollectionHandle<TYPE> _handle) :
    world{_world}, handle{_handle}
{}


template <typename TYPE>
Aspect<TYPE>::Aspect<TYPE>(TypedAspect typed_aspect) :
    world{typed_aspect.world}
{
    // Assert that this conversion is valid.
    if (typed_aspect.handle.type != TYPE::type_id) {
        fprintf(stderr, "[entity_model] ASSERTION ERROR: Something went wrong. Invalid aspect handle conversion was attempted.\n");
        exit(EXIT_FAILURE);
    }
    // This conversion drops the type ID.
    handle.id = typed_aspect.handle.id;
    handle.index = typed_aspect.handle.index;
}


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
    return entity()->get<SIBLING_TYPE>();
}


template <typename TYPE>
Entity Aspect<TYPE>::entity()
{
    // The entity is not stored in the handle, but in the table.
    return (*this)->entity;
}


template <typename TYPE>
void Aspect<TYPE>::destroy()
{
    //todo
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
    aspect_tables.add_type<TYPE>(name);
}


Entity EntityModel::new_entity()
{
    TableHandle handle = entity_table.add();
    Entity entity(world, handle);
    // Initialize the entry in the table.
    entity.get_entry()->first_aspect.id = 0; // Nullify the head of the aspect linked list.
    return entity;
}


GenericTable::Iterator EntityModel::entities()
{
    return entity_table.iterator();
}


template <typename TYPE>
GenericTable::Iterator EntityModel::aspects()
{
    return aspect_tables.iterator<TYPE>();
}


namespace details {
// TypedAspect
//--------------------------------------------------------------------------------
AspectBase &TypedAspect::operator*()
{
    AspectBase *asp_base = world->em.aspects.lookup(handle);
    if (asp == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid TypedAspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp_base;
}
AspectBase *TypedAspect::operator->()
{
    return &(*(*this));
}


} // end namespace details
