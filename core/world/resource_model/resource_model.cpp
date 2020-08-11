#include "world/resource_model/resource_model.h"
#include "world/resource_model/resource_model.serialize.cpp"


// Initialize the resource model.
ResourceModel::ResourceModel()
{
    resource_tables = TableCollection<ResourceBase>();
}
