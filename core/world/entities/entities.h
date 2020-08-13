#ifndef ENTITIES_H
#define ENTITIES_H
#include "core.h"
#include "data_structures/table.h"



class Entities;
template <typename T>
class Aspect {
    friend class Entities;
public:

    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;

private:
    Entities *entities; //---
    uint16_t aspect_type_id;
    TableElement table_element;

    Resource(Resources *_resources, uint16_t _resource_type_id, TableElement _table_element) :
        resources{_resources}, table_element{_table_element}, resource_type_id{_resource_type_id}
    {}
};



class Entities {
public:

private:


};


#endif // ENTITIES_H
