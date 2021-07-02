#ifndef ENTITIES_H
#define ENTITIES_H
#include "core.h"
#include "data_structures/table/table.h"
#include "data_structures/table/table_collection.h"


class IAspectType;
class Entities;
class Entity;
class GenericAspect {
    friend class Entities;
    friend class Entity;
    template <typename T>
    friend class Aspect;
public:
    GenericAspect() :
        entities{nullptr}, table_collection_element()
    {} //default null

    bool operator==(const GenericAspect &other) {
        return (entities == other.entities) && (table_collection_element == other.table_collection_element);
    }
    bool operator!=(const GenericAspect &other) {
        return !(*this == other);
    }

    // It is important that _all_ aspects derive from IAspectType, or this will break.
    IAspectType *metadata();

    Entity entity();

    TypeHandle &type() const;

    // Get the aspect data as a generic byte-array.
    uint8_t *get_data();

    GenericAspect(Entities *_entities, TableCollectionElement _table_collection_element) :
        entities{_entities}, table_collection_element{_table_collection_element}
    {}

private:
    Entities *entities;
    TableCollectionElement table_collection_element;


    friend class PrimitiveTypeDescriptor<GenericAspect>;
};



template <typename T>
class Aspect : public GenericAspect {
    friend class Entities;
    friend class Entity;
public:
    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;

    GenericAspect &generic() { return *this; }

    template <typename SIBLING_TYPE>
    Aspect<SIBLING_TYPE> sibling();

    Aspect() : GenericAspect()
    {} //default null
        
    Aspect(GenericAspect generic_aspect) : GenericAspect(generic_aspect) {}

    inline uint64_t ID() const {
        // Returns a unique ID for this certain type of aspect.
        // This ID is unique over the lifetime of the entity system.
        return static_cast<uint64_t>(table_collection_element.ID());
    }

    Aspect(Entities *entities, TableCollectionElement table_collection_element) :
        GenericAspect(entities, table_collection_element)
    {}
private:
};


/*--------------------------------------------------------------------------------
Iterating over aspects is unusual except for things such as serialization
and the implementation of basic entity-system methods. They must be treated generically
(as GenericAspect). The type descriptor of each aspect is accessible.
--------------------------------------------------------------------------------*/
class AspectIterator {
public:
    GenericAspect &operator*() {
        return aspect;
    }
    GenericAspect *operator->() {
        return &(operator*());
    }
    AspectIterator &operator++();
    bool operator==(const AspectIterator &other) {
        return aspect == other.aspect;
    }
    bool operator!=(const AspectIterator &other) {
        return !(*this == other);
    }
    AspectIterator(GenericAspect _aspect) :
        aspect{_aspect}
    {}
private:
    GenericAspect aspect;
};

template <typename T>
class AspectsIterator {
public:
    Aspect<T> &operator*() {
        return aspect;
    }
    Aspect<T> *operator->() {
        return &(operator*());
    }
    AspectsIterator<T> &operator++();
    bool operator==(const AspectsIterator<T> &other) {
        return aspect == other.aspect;
    }
    bool operator!=(const AspectsIterator<T> &other) {
        return !(*this == other);
    }

    AspectsIterator<T> &begin();
    AspectsIterator<T> &end();

    AspectsIterator(Entities *_entities, uint32_t _type_index, Table *_table) :
        entities{_entities}, table{_table},
        table_iterator(), aspect(),
        type_index{_type_index}
    {}
private:
    void update_aspect();

    Entities *entities;
    Table *table;
    TableIterator table_iterator;
    Aspect<T> aspect;
    uint32_t type_index;
};



class Entities;
struct Entity {
    friend class Entities;
public:

    void destroy();

    // Add an aspect, forward the arguments to an aspect constructor.
    template <typename T, typename... Args>
    Aspect<T> add(Args&&... args);

    // Run-time generic add.
    GenericAspect add(TypeHandle type);


    template <typename T>
    Aspect<T> get();

    
    AspectIterator begin();
    AspectIterator end();
    int num_aspects();

    Entity() :
        entities{nullptr}, table_element()
    {} //default null

    //Not private, since needs to be able to be fixed up...
    Entities *entities;
private:
    Entity(Entities *_entities, TableElement _table_element) :
        entities{_entities}, table_element{_table_element}
    {}

    // The common component to both the templated and run-time-generic add() functions.
    void init_added(GenericAspect aspect);

    TableElement table_element;

    friend class PrimitiveTypeDescriptor<Entity>;
};




struct EntityEntry {
    GenericAspect first_aspect;
};




// Metadata for each aspect, stored with the aspect.
// Named "IAspectType" since all aspects must inherit from this.
struct IAspectType {
    Entity entity;
    GenericAspect next_aspect;
    IAspectType() :
        entity(), next_aspect()
    {} //default null
};



class Entities {
    friend class Entity;
    friend class GenericAspect;
    template <typename T>
    friend class Aspect;
public:
    Entities();

    template <typename T>
    void register_aspect_type();

    Entity add();

    template <typename T>
    AspectsIterator<T> aspects();

private:

    EntityEntry *get_entry(Entity entity);

    Table entity_table;
    TableCollection aspect_tables;

    friend class PrimitiveTypeDescriptor<Entities>;
};


template <typename T>
void Entities::register_aspect_type()
{
    aspect_tables.register_type<T>();
}


// Add an aspect to the entity.
template <typename T, typename... Args>
Aspect<T> Entity::add(Args&&... args)
{
    // Initialize the aspect by forwarding the arguments to its constructor.
    auto aspect = Aspect<T>(entities, entities->aspect_tables.add<T>(std::forward<Args>(args)...));
    init_added(aspect.generic());
    return aspect;
}


template <typename T>
Aspect<T> Entity::get()
{
    for (auto a : *this) {
        if (a.type() == TypeHandle(Reflector::get_descriptor<T>())) {
            return Aspect<T>(a);
        }
    }
    assert(0);
}




template <typename T>
const T &Aspect<T>::operator*() const
{
    return *entities->aspect_tables.get<T>(table_collection_element);
}

template <typename T>
const T *Aspect<T>::operator->() const
{
    return &(operator*());
}

template <typename T>
T &Aspect<T>::operator*()
{
    return *entities->aspect_tables.get<T>(table_collection_element);
}

template <typename T>
T *Aspect<T>::operator->()
{
    return &(operator*());
}



template <typename T>
template <typename SIBLING_TYPE>
Aspect<SIBLING_TYPE> Aspect<T>::sibling()
{
    return metadata()->entity.get<SIBLING_TYPE>();
}


template <typename T>
AspectsIterator<T> Entities::aspects()
{
    return AspectsIterator<T>(this, aspect_tables.get_type_index<T>(), aspect_tables.get_table<T>());
}



template <typename T>
void AspectsIterator<T>::update_aspect()
{
    aspect = Aspect<T>(entities, TableCollectionElement(type_index, *table_iterator));
}

template <typename T>
AspectsIterator<T> &AspectsIterator<T>::begin()
{
    table_iterator = table->begin();
    update_aspect();
    return *this;
}

template <typename T>
AspectsIterator<T> &AspectsIterator<T>::operator++()
{
    ++table_iterator;
    update_aspect();
    return *this;
}

template <typename T>
AspectsIterator<T> &AspectsIterator<T>::end()
{
    table_iterator = table->end();
    update_aspect();
    return *this;
}


#include "entity_system/standard_aspects/standard_aspects.h"


#endif // ENTITIES_H
