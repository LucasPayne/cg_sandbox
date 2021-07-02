#include "table/table.h"
#include <algorithm>//max
#include <assert.h>


/*--------------------------------------------------------------------------------
TableElement
--------------------------------------------------------------------------------*/
uint32_t TableElement::ID() const
{
    return id;
}


/*--------------------------------------------------------------------------------
Table
--------------------------------------------------------------------------------*/

Table::Table(TypeHandle _type, uint32_t start_capacity) :
    m_type{_type}, first_free_index{0}, next_id{1}, m_capacity{start_capacity}
{
    slot_size = std::max(m_type->size, sizeof(EmptySlotData)) + sizeof(SlotMetadata);

    data = std::vector<uint8_t>(slot_size * start_capacity);

    // All slots are empty.
    for (unsigned int i = 0; i < start_capacity; i++) {
        slot_metadata(i)->id = 0;
    }

    // Initialize the free list.
    for (unsigned int i = 0; i < start_capacity - 1; i++) {
        empty_slot(i)->next_free_index = i + 1;
    }
    empty_slot(start_capacity - 1)->next_free_index = 0;
}


size_t Table::capacity() const
{
    return m_capacity;
}
TypeHandle &Table::type()
{
    return m_type;
}


bool Table::slot_is_empty(uint32_t index)
{
    return slot_metadata(index)->id == 0;
}


TableElement Table::add()
{
    uint32_t new_id = next_id ++;
    TableElement element(new_id, first_free_index);
    // Set up the slot metadata.
    slot_metadata(first_free_index)->id = new_id;

    // Fix up the free list.
    first_free_index = empty_slot(first_free_index)->next_free_index;

    if (first_free_index == 0) {
        // If the free list is empty, increase the capacity of the table.
        size_t old_capacity = m_capacity;
        m_capacity *= 2;
        data.resize(slot_size * m_capacity, 0);

        // Initialize the new slots of the free list.
        first_free_index = old_capacity;
        for (unsigned int i = old_capacity; i < m_capacity - 1; i++) {
            empty_slot(i)->next_free_index = i + 1;
        }
        empty_slot(m_capacity - 1)->next_free_index = 0;
    }
    return element;
}


void Table::assert_valid_element(TableElement element)
{
    assert(element.id != 0);
    assert(slot_metadata(element.index)->id == element.id);
}


void Table::remove(TableElement element)
{
    assert_valid_element(element);
    slot_metadata(element.index)->id = 0;

    // Add this slot to the head of the free list.
    empty_slot(element.index)->next_free_index = first_free_index;
    first_free_index = element.index;
}


uint8_t *Table::operator[](TableElement element)
{
    assert_valid_element(element);
    return slot(element.index);
}


Table::SlotMetadata *Table::slot_metadata(uint32_t index)
{
    return reinterpret_cast<Table::SlotMetadata *>(&data[slot_size * index]);
}

Table::EmptySlotData *Table::empty_slot(uint32_t index)
{
    return reinterpret_cast<Table::EmptySlotData *>(slot(index));
}

uint8_t *Table::slot(uint32_t index)
{
    return &data[slot_size * index + sizeof(SlotMetadata)];
}



/*--------------------------------------------------------------------------------
Table forward iterator.
--------------------------------------------------------------------------------*/
TableIterator Table::begin()
{
    TableIterator iter(this);
    for (unsigned int i = 0; i < m_capacity; i++) {
        if (!slot_is_empty(i)) {
            iter.element = TableElement(slot_metadata(i)->id, i);
            return iter;
        }
    }
    return end();
}

TableIterator &TableIterator::operator++()
{
    for (unsigned int i = element.index+1; i < table->m_capacity; i++) {
        if (!table->slot_is_empty(i)) {
            element = TableElement(table->slot_metadata(i)->id, i);
            return *this;
        }
    }
    element = TableElement(0, 0);
    return *this;
}

TableIterator Table::end()
{
    TableIterator iter(this);
    iter.element = TableElement(0, 0);
    return iter;
}

