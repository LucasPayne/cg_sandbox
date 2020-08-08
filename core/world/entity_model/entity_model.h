#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"
#include "data_structures/table.h"
#include "world/world_reference.h"

/*--------------------------------------------------------------------------------
Aspect<TYPE>
    An Aspect is a handle to data associated to an entity.
    The data in an Aspect is the minimal data necessary for finding its data and
    related aspects.

    Aspects are a parameterized type, meaning that 
--------------------------------------------------------------------------------*/
struct Entity;
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

    Aspect(WorldReference _world, TableHandle _handle);
    Aspect(WorldReference _world, TableCollectionHandle<TYPE> _handle);
    Aspect(TypedAspect typed_aspect);
    Aspect();
private:

    TableCollectionHandle<TYPE> handle;
    WorldReference world;
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
    Entity(WorldReference _world, TableHandle _handle) :
        world{_world}, handle{_handle}
    {}

    WorldReference world;
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
    EntityModel(WorldReference _world);
    EntityModel() {}

    template <typename TYPE>
    void register_aspect_type(const std::string &name);

    Entity new_entity();

    GenericTable::Iterator<Entity> entities();
    template <typename TYPE>
    GenericTable::Iterator<Aspect<TYPE>> aspects();
private:
    WorldReference world;
    Table<EntityEntry> entity_table;
    TableCollection<AspectBase> aspect_tables;
};


#endif // ENTITY_MODEL_H
