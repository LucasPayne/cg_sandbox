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


uint8_t *TableCollection::operator[](TableCollectionElement element)
{
    return tables[element.type_index][element.table_element];
}


TypeHandle &TableCollection::type_of(TableCollectionElement element)
{
    // Must be a valid element, or else this breaks!
    return tables[element.type_index].type();
}
