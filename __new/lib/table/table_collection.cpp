#include "table/table_collection.h"

uint8_t *TableCollection::operator[](TableCollectionElement element)
{
    return tables[element.type_index][element.table_element];
}


TypeHandle &TableCollection::type_of(TableCollectionElement element)
{
    // Must be a valid element, or else this breaks!
    return tables[element.type_index].type();
}


// Run-time generic add.
TableCollectionElement TableCollection::add(TypeHandle type)
{
    Table *table = get_table(type);
    size_t type_index = table - &tables[0]; //...
    return TableCollectionElement(type_index, table->add());
}


// Run-time generic version.
Table *TableCollection::get_table(TypeHandle type)
{
    return &tables[get_type_index(type)];
}


uint32_t TableCollection::get_type_index(TypeHandle type)
{
    // Maps the type symbol to an index through string comparison. Not very efficient...
    int type_index = 0;
    for (Table &table : tables) {
        if (type == table.type()) {
            return type_index;
        }
        type_index++;
    }
    assert(0);
}
