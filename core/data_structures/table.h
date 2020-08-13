#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <functional>
#include <string>//std::string
#include <stdint.h>
#include <stdio.h>//error logging
#include <stdlib.h>//exit

#include "reflector/reflector.h"
#include "reflector/type_handle.h"


class Table;
struct TableElement {
    friend class Table;
    friend class TableIterator;
public:
    uint32_t ID() const;
    TableElement() :
        id{0}, index{0}
    {}
    bool operator==(const TableElement &other) const {
        return (id == other.id) && (index == other.index);
    }
    bool operator!=(const TableElement &other) const {
        return !(*this == other);
    }

private:
    uint32_t id;
    uint32_t index;

    TableElement(uint32_t _id, uint32_t _index) :
        id{_id}, index{_index}
    {}

    // Allow serialization functions access to private data.
    friend class PrimitiveTypeDescriptor<Table>;
    friend class PrimitiveTypeDescriptor<TableElement>;
};
REFLECT_STRUCT(TableElement);




class TableIterator;
class Table {
    friend class TableIterator;
public:
    Table() {}

    TableElement add();
    void remove(TableElement element);
    uint8_t *operator[](TableElement element);

    size_t capacity() const; // The number of slots in the table.
    
    Table(TypeHandle _type, uint32_t start_capacity = 1);

    TableIterator begin();
    TableIterator end();

private:
    struct SlotMetadata {
        uint32_t id;
    };
    struct EmptySlotData {
        uint32_t next_free_index;
    };

    SlotMetadata *slot_metadata(uint32_t index);

    // Get the entry data (not including the metadata).
    uint8_t *slot(uint32_t index);

    // Get the data for an empty slot (the slot data cast to EmptySlotData).
    // This must only be used if the slot ID at this index is 0.
    EmptySlotData *empty_slot(uint32_t index);

    TypeHandle type;
    size_t slot_size;

    // First slot in the free list.
    uint32_t first_free_index;

    // The ID to give the next element added to the table.
    uint32_t next_id;

    size_t m_capacity;

    void assert_valid_element(TableElement element); // Helper function for error-checking.

    bool slot_is_empty(uint32_t index);

    std::vector<uint8_t> data;


    // Allow serialization functions access to private data.
    friend class PrimitiveTypeDescriptor<Table>;
};
REFLECT_PRIMITIVE(Table);



class TableIterator {
    friend class Table;
public:
    TableElement &operator*() {
        return element;
    }
    TableElement *operator->() {
        return &(operator*());
    }
    TableIterator &operator++();
    bool operator==(const TableIterator &other) {
        // The table pointer is assumed the same.
        return element == other.element;
    }
    bool operator!=(const TableIterator &other) {
        return !(*this == other);
    }
private:
    TableIterator(Table *_table) :
        table{_table}
    {}
    Table *table;
    TableElement element;
};




// template <typename ELEMENT_TYPE>
// class Table : public Table {
// public:
//     ELEMENT_TYPE *operator[](TableElement element) {
//         return reinterpret_cast<ELEMENT_TYPE *>();
//     }
// 
//     Table(uint32_t start_capacity = 1) :
//         Table(TypeHandle::from_type<ELEMENT_TYPE>(), start_capacity)
//     {}
// private:
// }



#endif // TABLE_H
