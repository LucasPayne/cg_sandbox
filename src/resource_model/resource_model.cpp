#include "resource_model/resource_model.h"

// Initialize the resource model.
ResourceModel::ResourceModel()
{
    m_resource_tables = TableCollection<ResourceBase>();
}
