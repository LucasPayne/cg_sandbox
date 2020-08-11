#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"
#include "data_structures/table.h"


class World; // Classes here are a friend of World, only so World can handle saving the entity model.
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
/*REFLECTED*/ struct Aspect {
    friend class Entity;
    friend class EntityModel;
    friend class World;
public:
    TYPE &operator*();
    TYPE *operator->();

    Entity entity();
    
    template <typename SIBLING_TYPE>
    Aspect<SIBLING_TYPE> sibling();

    void destroy();

    TableEntryID ID() const;

    Aspect(EntityModel *_em, TableCollectionHandle<TYPE> _handle) :
        em{_em}, handle{_handle}
    {}
    Aspect(EntityModel *_em, TableHandle _handle) :
        em{_em}, handle{_handle}
    {}
    Aspect() {};
    Aspect(TypedAspect typed_aspect);
// private:
    EntityModel *em; // Not serialized. This _must_ be set manually when an EntityModel is loaded.
    /*ENTRY*/ TableCollectionHandle<TYPE> handle;
};


/*--------------------------------------------------------------------------------
Entity
    The Entity is a handle to a collection of aspects.
    The data in an Entity is the minimal data necessary for finding its aspects.
--------------------------------------------------------------------------------*/
struct EntityEntry;
class EntityModel;

/*REFLECTED*/ struct Entity {
    friend class EntityModel;
    template <typename TYPE> friend class Aspect;
    friend class World;
public:
    Entity() {}

    void destroy();
    template <typename TYPE>
    Aspect<TYPE> add();
    template <typename TYPE>
    Aspect<TYPE> get();

    TableEntryID ID() const;
// private:
    Entity(EntityModel *_em, TableHandle _handle) :
        em{_em}, handle{_handle}
    {}

    EntityModel *em;
    /*ENTRY*/ TableHandle handle;
};


// namespace details {
// Non-API declarations. These are meaningful only to the implementation.
/*--------------------------------------------------------------------------------
TypedAspect
    Sometimes generic aspect handles are wanted, such as in the implementation
    of the aspect linked list.
--------------------------------------------------------------------------------*/
struct AspectBase;

/*REFLECTED*/ struct TypedAspect {
    EntityModel *em;
    /*ENTRY*/ TypedTableCollectionHandle handle;
    AspectBase &operator*();
    AspectBase *operator->();

    TypedAspect(EntityModel *_em, TypedTableCollectionHandle _handle) :
        em{_em}, handle{_handle}
    {}
};


/*--------------------------------------------------------------------------------
AspectBase
    Each entry in the aspect tables has a common base of data, given here.
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct AspectBase {
    /*ENTRY*/ Entity entity;
    /*ENTRY*/ TypedAspect next_aspect;
};


/*--------------------------------------------------------------------------------
EntityEntry
    An entry in the entity table. The aspects can be traversed starting here.
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct EntityEntry {
    /*ENTRY*/ TypedAspect first_aspect;
};



/*--------------------------------------------------------------------------------
AspectTypeStaticData
--------------------------------------------------------------------------------*/
typedef TableCollectionType AspectType;


// } // end namespace details


/*================================================================================
    EntityModel
================================================================================*/
class EntityModel {
    template <typename T> friend class Aspect;
    friend class TypedAspect;
    friend class Entity;
    friend class World;
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
// Add an aspect to the entity.
template <typename TYPE>
Aspect<TYPE> Entity::add()
{
    EntityEntry *entry = em->entity_table.lookup(handle);

    TableCollectionHandle<TYPE> aspect_handle = em->aspect_tables.add<TYPE>();
    Aspect<TYPE> aspect(em, aspect_handle);
    aspect->entity = *this; // Give a reference to this entity (Entity is a referential type, so just give it the whole thing). 


    TypedAspect typed_aspect(em, TypedTableCollectionHandle::create(aspect_handle));

    // Add this aspect to the head of the linked list.
    TypedAspect temp = entry->first_aspect;
    entry->first_aspect = typed_aspect;
    typed_aspect->next_aspect = temp;

    return aspect;
}


// Get an aspect from an entity.
template <typename TYPE>
Aspect<TYPE> Entity::get()
{
    AspectType aspect_type = TableCollectionTypeData<TYPE>::data.type_id;
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
Aspect<TYPE>::Aspect(TypedAspect typed_aspect) :
    em{typed_aspect.em}
{
    // Assert that this conversion is valid.
    if (typed_aspect.handle.type != TableCollectionTypeData<TYPE>::data.type_id) {
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
    AspectBase *aspect_entry = reinterpret_cast<AspectBase *>(em->aspect_tables.lookup<TYPE>(handle));
    return aspect_entry->entity;
}


template <typename TYPE>
template <typename SIBLING_TYPE>
Aspect<SIBLING_TYPE> Aspect<TYPE>::sibling()
{
    Entity e = entity();
    return e.get<SIBLING_TYPE>();
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
