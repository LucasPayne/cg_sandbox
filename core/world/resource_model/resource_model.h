#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
#include "core.h"
#include "data_structures/table.h"


template <typename T>
class Resource {
public:
    Resource(World *_world) :
        world{_world}
    {
        world->
    }


private:
    World *world; //---
    uint16_t resource_type_id;
    TableElement table_element;
    
};



#endif // RESOURCE_MODEL_H
