#ifndef ENTITIES_H
#define ENTITIES_H
#include "core.h"
#include "data_structures/table.h"
#include "data_structures/table_collection.h"



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

private:
    Entities *entities; //---
    TableCollectionElement table_collection_element;

    GenericAspect(Entities *_entities, TableCollectionElement _table_collection_element) :
        entities{_entities}, table_collection_element{_table_collection_element}
    {}

    friend class PrimitiveTypeDescriptor<GenericAspect>;
};
REFLECT_STRUCT(GenericAspect);


// Metadata for each aspect, stored with the aspect.
// Named "IAspectType" since all aspects must inherit from this.
struct IAspectType {
    GenericAspect next_aspect;
    IAspectType() :
        next_aspect()
    {} //default null
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

private:
    Aspect(Entities *entities, TableCollectionElement table_collection_element) :
        GenericAspect(entities, table_collection_element)
    {}
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





class Entities;
struct Entity {
    friend class Entities;
public:

    void destroy();

    template <typename T, typename... Args>
    Aspect<T> add(Args&&... args);

    template <typename T>
    Aspect<T> get();

    
    AspectIterator begin();
    AspectIterator end();


private:
    Entity(Entities *_entities, TableElement _table_element) :
        entities{_entities}, table_element{_table_element}
    {}

    Entities *entities;
    TableElement table_element;
};




struct EntityEntry {
    GenericAspect first_aspect;
};
REFLECT_STRUCT(EntityEntry);


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

private:

    EntityEntry *get_entry(Entity entity);

    Table entity_table;
    TableCollection aspect_tables;

    friend class PrimitiveTypeDescriptor<Entities>;
};
REFLECT_STRUCT(Entities);


template <typename T>
void Entities::register_aspect_type()
{
    aspect_tables.register_type<T>();
}



template <typename T, typename... Args>
Aspect<T> Entity::add(Args&&... args)
{
    std::cout << "Adding aspect " << Reflector::get_descriptor<T>()->name() << "\n";

    auto aspect = Aspect<T>(entities, entities->aspect_tables.add<T>(std::forward<Args>(args)...));
    EntityEntry *entry = entities->get_entry(*this);
    printf("Got entry\n");
    if (entry->first_aspect == GenericAspect()) {
        printf("Setting up head\n");
        entry->first_aspect = aspect.generic();
    } else {
        printf("Appending\n");
        GenericAspect last = entry->first_aspect;
        for (auto a : *this) {
            last = a;
        }
        last.metadata()->next_aspect = aspect;
    }
    return aspect;
}


template <typename T>
Aspect<T> Entity::get()
{
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

#endif // ENTITIES_H
