#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <functional>
#include <string>//std::string
#include <utility>//std::forward
#include <stdint.h>
#include <stdio.h>//error logging
#include <stdlib.h>//exit
#include "reflector/reflector.h"


using TableElementID = uint32_t;


class Table;
struct TableElement {
    friend class Table;
    friend class TableIterator;
public:
    TableElementID ID() const;
    TableElement() :
        id{0}, index{0}
    {} //default null
    bool operator==(const TableElement &other) const {
        return (id == other.id) && (index == other.index);
    }
    bool operator!=(const TableElement &other) const {
        return !(*this == other);
    }

private:
    TableElementID id;
    uint32_t index;

    TableElement(TableElementID _id, uint32_t _index) :
        id{_id}, index{_index}
    {}
};




class TableIterator;
class Table {
    friend class TableIterator;
public:
    Table() {}

    // Reserves uninitialized memory for an object.
    TableElement add();

    // Construct a new object in the table.
    template <typename T, typename... Args>
    TableElement add(Args&&... args) {
        TableElement element = add();
        auto location = reinterpret_cast<T *>((*this)[element]);
        new (location) T(std::forward<Args>(args)...);
        return element;
    }

    void remove(TableElement element);
    uint8_t *operator[](TableElement element);

    size_t capacity() const; // The number of slots in the table.
    
    Table(TypeHandle _type, uint32_t start_capacity = 1);

    TableIterator begin();
    TableIterator end();

    TypeHandle &type();

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

    TypeHandle m_type;
    size_t slot_size;

    // First slot in the free list.
    uint32_t first_free_index;

    // The ID to give the next element added to the table.
    TableElementID next_id;

    size_t m_capacity;

    void assert_valid_element(TableElement element); // Helper function for error-checking.

    bool slot_is_empty(uint32_t index);

    std::vector<uint8_t> data;
};


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
    TableIterator() :
        table{nullptr}, element()
    {} //default null

private:
    TableIterator(Table *_table) :
        table{_table}
    {}
    Table *table;
    TableElement element;
};




#endif // TABLE_H
