#include "world/resources/resources.h"


DESCRIPTOR_INSTANCE(Resources);
BEGIN_ENTRIES(Resources)
    ENTRY(resource_tables)
END_ENTRIES()


TypeHandle &GenericResource::type() const {
    return resources->resource_tables.type_of(table_collection_element);
}

DESCRIPTOR_INSTANCE(GenericResource);
BEGIN_ENTRIES(GenericResource)
    ENTRY(resources)
    ENTRY(table_collection_element)
END_ENTRIES()

