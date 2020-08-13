#ifndef TABLE_COLLECTION_H
#define TABLE_COLLECTION_H
#include <assert.h>
#include "data_structures/table.h"


class TableCollectionElement {
    friend class TableCollection;
private:
    uint16_t type_index;
    TableElement table_element;

    TableCollectionElement(uint16_t _type_index, TableElement _table_element) :
        type_index{_type_index}, table_element{_table_element}
    {}
};


class TableCollection {
public:
    template <typename T>
    void register_type();
    
    template <typename T>
    TableCollectionElement add();
    
    template <typename T>
    T *get(TableCollectionElement element);

private:
    std::vector<Table> tables;

    friend class PrimitiveTypeDescriptor<TableCollection>;
};
REFLECT_STRUCT(TableCollection);




template <typename T>
void TableCollection::register_type()
{
    TypeHandle type(Reflector::get_descriptor<T>());
    tables.push_back(Table(type, 16));
}

template <typename T>
TableCollectionElement TableCollection::add() {
    TypeHandle type(Reflector::get_descriptor<T>());
    int type_index = 0;
    for (auto &table : tables) {
        if (type == table.type()) {
            return TableCollectionElement(type_index, table.add());
        }
        type_index++;
    }
    assert(0);
}

template <typename T>
T *TableCollection::get(TableCollectionElement element) {
    return reinterpret_cast<T *>(tables[element.type_index][element.table_element]);
}





#endif // TABLE_COLLECTION_H
