#ifndef ENTITIES_H
#define ENTITIES_H
#include "core.h"
#include "data_structures/table.h"
#include "data_structures/table_collection.h"



class Entities;
class GenericAspect {
    friend class Entities;
private:
    Entities *entities; //---
    TableCollectionElement table_collection_element;

    GenericAspect(Entities *_entities, TableCollectionElement _table_collection_element) :
        entities{_entities}, table_collection_element{_table_collection_element}
    {}

    friend class PrimitiveTypeDescriptor<GenericAspect>;
};
REFLECT_STRUCT(GenericAspect);


template <typename T>
class Aspect : public GenericAspect {
public:
    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;

    Aspect(Entities *entities, TableCollectionElement table_collection_element) :
        GenericAspect(entities, table_collection_element)
    {}
};




class Entities;
struct Entity {
    friend class Entities;
public:

    void destroy();

    template <typename T>
    Aspect<T> add();

    template <typename T>
    Aspect<T> get();

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
    int aspect_table_start_capacity = 16;
    aspect_tables.register_type<T>(aspect_table_start_capacity);
}



template <typename T>
Aspect<T> Entity::add()
{
    auto aspect = entities->aspect_tables.add<T>();
}

template <typename T>
Aspect<T> Entity::get()
{
}


#endif // ENTITIES_H
