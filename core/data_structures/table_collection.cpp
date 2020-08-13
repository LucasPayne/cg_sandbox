#include "data_structures/table_collection.h"


DESCRIPTOR_INSTANCE(TableCollectionElement);
BEGIN_ENTRIES(TableCollectionElement)
    ENTRY(type_index)
    ENTRY(table_element)
END_ENTRIES()


DESCRIPTOR_INSTANCE(TableCollection);
BEGIN_ENTRIES(TableCollection)
    ENTRY(tables)
END_ENTRIES()
