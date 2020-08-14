#ifndef RESOURCES_H
#define RESOURCES_H
#include <assert.h>
#include <utility>//std::forward
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

    // Unique runtime ID.
    TableElementID ID() const { return table_collection_element.ID(); }

    Resource() :
        resources{nullptr}, table_collection_element()
    {} //default null

private:
    Resources *resources; //---
    TableCollectionElement table_collection_element;

    Resource(Resources *_resources, TableCollectionElement _table_collection_element) :
        resources{_resources}, table_collection_element{_table_collection_element}
    {}

    friend class PrimitiveTypeDescriptor<Resource<T>>;
};
template <typename T>
REFLECT_STRUCT_TEMPLATED(Resource<T>);
template <typename T>
DESCRIPTOR_INSTANCE(Resource<T>);



class Resources {
public:
    template <typename T>
    void register_resource_type();
    
    template <typename T, typename... Args>
    Resource<T> add(Args&&... args);
    
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

template <typename T, typename... Args>
Resource<T> Resources::add(Args&&... args) {
    return Resource<T>(this, resource_tables.add<T>(std::forward<Args>(args)...));
}

template <typename T>
T *Resources::get(Resource<T> resource) {
    return resource_tables.get<T>(resource.table_collection_element);
}



template <typename T>
BEGIN_ENTRIES(Resource<T>)
    ENTRY(table_collection_element)
END_ENTRIES()

#endif // RESOURCES_H
