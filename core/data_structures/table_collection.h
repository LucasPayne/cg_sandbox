#ifndef TABLE_COLLECTION_H
#define TABLE_COLLECTION_H
#include <assert.h>
#include "data_structures/table.h"


class TableCollectionElement {
    friend class TableCollection;
public:
    bool operator==(const TableCollectionElement &other) {
        return (type_index == other.type_index) && (table_element == other.table_element);
    }
    bool operator!=(const TableCollectionElement &other) {
        return !(*this == other);
    }

    TableCollectionElement() :
        type_index{0}, table_element()
    {} // default null

    // Unique run-time ID for this element in this table.
    TableElementID ID() const { return table_element.ID(); }


    TableCollectionElement(uint16_t _type_index, TableElement _table_element) :
        type_index{_type_index}, table_element{_table_element}
    {}

private:
    uint16_t type_index;
    TableElement table_element;

    friend class PrimitiveTypeDescriptor<TableCollectionElement>;
};
REFLECT_STRUCT(TableCollectionElement);


class TableCollection {
public:
    template <typename T>
    void register_type();
    
    template <typename T, typename... Args>
    TableCollectionElement add(Args&&... args);
    
    // Get an object with the given type from the tables.
    template <typename T>
    T *get(TableCollectionElement element);

    TypeHandle &type_of(TableCollectionElement element);

    // Get a generic byte-array pointer from the handle.
    uint8_t *operator[](TableCollectionElement element);

    TableCollection(size_t _table_start_capacity = 16) :
        table_start_capacity{_table_start_capacity}
    {}

    template <typename T>
    Table *get_table();

    template <typename T>
    uint32_t get_type_index();

private:
    size_t table_start_capacity; // Capacity that each new table is created with.
    std::vector<Table> tables;

    friend class PrimitiveTypeDescriptor<TableCollection>;
};
REFLECT_STRUCT(TableCollection);




template <typename T>
void TableCollection::register_type()
{
    TypeHandle type(Reflector::get_descriptor<T>());
    tables.push_back(Table(type, table_start_capacity));
}

template <typename T, typename... Args>
TableCollectionElement TableCollection::add(Args&&... args) {
    Table *table = get_table<T>();
    size_t type_index = table - &tables[0]; //...
    return TableCollectionElement(type_index, table->add<T>(std::forward<Args>(args)...));
}

template <typename T>
T *TableCollection::get(TableCollectionElement element) {
    return reinterpret_cast<T *>(tables[element.type_index][element.table_element]);
}


template <typename T>
Table *TableCollection::get_table()
{
    return &tables[get_type_index<T>()];
}

template <typename T>
uint32_t TableCollection::get_type_index()
{
    // Maps the type symbol to an index through string comparison. Not very efficient...
    TypeHandle type(Reflector::get_descriptor<T>());
    int type_index = 0;
    for (Table &table : tables) {
        if (type == table.type()) {
            return type_index;
        }
        type_index++;
    }
    assert(0);
}

#endif // TABLE_COLLECTION_H
