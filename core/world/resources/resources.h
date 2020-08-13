#ifndef RESOURCES_H
#define RESOURCES_H
#include <assert.h>
#include "core.h"
#include "data_structures/table_collection.h"


class Resources;
template <typename T>
class Resource {
    friend class Resources;
public:

    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;


private:
    Resources *resources; //---
    TableCollectionElement table_collection_element;

    Resource(Resources *_resources, TableCollectionElement _table_collection_element) :
        resources{_resources}, table_collection_element{_table_collection_element}
    {}
};



class Resources {
public:
    template <typename T>
    void register_resource_type();
    
    template <typename T>
    Resource<T> add();
    
    template <typename T>
    T *get(Resource<T> resource);

    void save(std::ostream &out);

private:
    TableCollection resource_tables;

    friend class PrimitiveTypeDescriptor<Resources>;
};
REFLECT_STRUCT(Resources);




template <typename T>
T &Resource<T>::operator*() {
    return *resources->get(*this);
}
template <typename T>
T *Resource<T>::operator->() {
    return &(operator*());
}
template <typename T>
const T &Resource<T>::operator*() const {
    return *resources->get(*this);
}
template <typename T>
const T *Resource<T>::operator->() const {
    return &(operator*());
}



template <typename T>
void Resources::register_resource_type()
{
    resource_tables.register_type<T>();
}

template <typename T>
Resource<T> Resources::add() {
    return Resource<T>(this, resource_tables.add<T>());
}

template <typename T>
T *Resources::get(Resource<T> resource) {
    return resource_tables.get<T>(resource.table_collection_element);
}


#endif // RESOURCES_H
