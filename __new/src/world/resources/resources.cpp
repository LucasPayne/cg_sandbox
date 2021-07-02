#include "world/resources/resources.h"


TypeHandle &GenericResource::type() const {
    return resources->resource_tables.type_of(table_collection_element);
}
