#ifndef RESOURCES_H
#define RESOURCES_H
#include <assert.h>
#include "core.h"
#include "data_structures/table.h"


class Resources;
template <typename T>
class Resource {
    friend class Resources;
public:

    T &operator*();
    T *operator->();


private:
    Resources *resources; //---
    uint16_t resource_type_id;
    TableElement table_element;

    Resource(Resources *_resources, uint16_t _resource_type_id, TableElement _table_element) :
        resources{_resources}, table_element{_table_element}, resource_type_id{_resource_type_id}
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

private:
    std::vector<Table> resource_tables;
};






template <typename T>
T &Resource<T>::operator*() {
    return *resources->get(*this);
}
template <typename T>
T *Resource<T>::operator->() {
    return &(operator*());
}



template <typename T>
void Resources::register_resource_type()
{
    TypeHandle type(Reflector::get_descriptor<T>());
    resource_tables.push_back(Table(type, 16));
}

template <typename T>
Resource<T> Resources::add() {
    TypeHandle type(Reflector::get_descriptor<T>());
    int type_id = 0;
    for (auto &table : resource_tables) {
        if (type == table.type()) {
            return Resource<T>(this, type_id, table.add());
        }
        type_id++;
    }
    assert(0);
}

template <typename T>
T *Resources::get(Resource<T> resource) {
    return reinterpret_cast<T *>(resource_tables[resource.resource_type_id][resource.table_element]);
}


#endif // RESOURCES_H
