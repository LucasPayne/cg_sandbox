#include "world/world.h"


// Initialize the resource model.
ResourceModel::ResourceModel()
{
    m_resource_tables = TableCollection<ResourceBase, Resource>();
}
