#include "world/world.h"


// Initialize the resource model.
ResourceModel::ResourceModel(WorldReference _world) :
    world{_world}
{
    resource_tables = TableCollection<ResourceBase>();
}
