#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"
#include "data_structures/table.h"


/*--------------------------------------------------------------------------------
Aspect<TYPE>
    An Aspect is a handle to data associated to an entity.
    The data in an Aspect is the minimal data necessary for finding its data and
    related aspects.

    Aspects are a parameterized type, meaning that 
--------------------------------------------------------------------------------*/
struct Entity;
class EntityModel;
struct TypedAspect;
template <typename TYPE>
struct Aspect {
    friend class Entity;
    friend class EntityModel;
public:
    TYPE &operator*();
    TYPE *operator->();

    Entity entity();
    
    template <typename SIBLING_TYPE>
    Aspect<SIBLING_TYPE> sibling();

    void destroy();

    TableEntryID ID() const;

    Aspect(EntityModel *_em, TableHandle _handle);
    Aspect(EntityModel *_em, TableCollectionHandle<TYPE> _handle);
    Aspect(TypedAspect typed_aspect);
    Aspect();
private:
    EntityModel *em;
    TableCollectionHandle<TYPE> handle;
};


/*--------------------------------------------------------------------------------
Entity
    The Entity is a handle to a collection of aspects.
    The data in an Entity is the minimal data necessary for finding its aspects.
--------------------------------------------------------------------------------*/
struct EntityEntry;
class EntityModel;
struct Entity {
    friend class EntityModel;
    template <typename TYPE> friend class Aspect;
public:
    Entity() {}

    void destroy();
    template <typename TYPE>
    Aspect<TYPE> add();
    template <typename TYPE>
    Aspect<TYPE> get();

    TableEntryID ID() const;
private:
    Entity(EntityModel *_em, TableHandle _handle) :
        em{_em}, handle{_handle}
    {}

    EntityModel *em;
    TableHandle handle;
};


// namespace details {
// Non-API declarations. These are meaningful only to the implementation.
/*--------------------------------------------------------------------------------
TypedAspect
    Sometimes generic aspect handles are wanted, such as in the implementation
    of the aspect linked list.
--------------------------------------------------------------------------------*/
struct AspectBase;
struct TypedAspect {
    EntityModel *em;
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


/*--------------------------------------------------------------------------------
EntityEntry
    An entry in the entity table. The aspects can be traversed starting here.
--------------------------------------------------------------------------------*/
struct EntityEntry {
    TypedAspect first_aspect;
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


// } // end namespace details


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
struct IAspectType : AspectTypeStaticData<T>, public AspectBase {
};


/*================================================================================
    EntityModel
================================================================================*/
class EntityModel {
    template <typename T> friend class Aspect;
    friend class TypedAspect;
    friend class Entity;
public:
    EntityModel();

    template <typename TYPE>
    void register_aspect_type(const std::string &name);

    Entity new_entity();

    GenericTable::Iterator<Entity> entities();
    template <typename TYPE>
    GenericTable::Iterator<Aspect<TYPE>> aspects();
private:
    Table<EntityEntry> entity_table;
    TableCollection<AspectBase> aspect_tables;
};




//================================================================================
// Template implementations.
//================================================================================
// Entity
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE> Entity::add()
{
    TableCollectionHandle<TYPE> handle = em->aspect_tables.add<TYPE>();
    return Aspect<TYPE>(em, handle);
}


template <typename TYPE>
Aspect<TYPE> Entity::get()
{
    AspectType aspect_type = TYPE::type_id;
    EntityEntry *entry = em->entity_table.lookup(handle);

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


// Aspect<TYPE>
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE>::Aspect(EntityModel *_em, TableCollectionHandle<TYPE> _handle) :
    em{_em}, handle{_handle}
{}
template <typename TYPE>
Aspect<TYPE>::Aspect(EntityModel *_em, TableHandle _handle) :
    em{_em}, handle{_handle}
{}


template <typename TYPE>
Aspect<TYPE>::Aspect(TypedAspect typed_aspect) :
    em{typed_aspect.em}
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
    TYPE *asp = em->aspect_tables.lookup<TYPE>(handle);
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


template <typename TYPE>
Entity Aspect<TYPE>::entity()
{
    // The entity reference is not stored in the handle, but in the table.
    return (*this)->entity;
}


template <typename TYPE>
template <typename SIBLING_TYPE>
Aspect<SIBLING_TYPE> Aspect<TYPE>::sibling()
{
    // return entity().get<SIBLING_TYPE>();
    
}


template <typename TYPE>
void Aspect<TYPE>::destroy()
{
    //todo
}


template <typename TYPE>
TableEntryID Aspect<TYPE>::ID() const
{
    return handle.id;
}


// EntityModel
//--------------------------------------------------------------------------------
template <typename TYPE>
void EntityModel::register_aspect_type(const std::string &name)
{
    aspect_tables.add_type<TYPE>(name);
}


template <typename TYPE>
GenericTable::Iterator<Aspect<TYPE>> EntityModel::aspects()
{
    return aspect_tables.iterator<TYPE, Aspect<TYPE>>(
        [this](TableHandle handle)->Aspect<TYPE> {
            return Aspect<TYPE>(this, handle);
        }
    );
}


#endif // ENTITY_MODEL_H
