#include "data_structures/table.h"
#include <algorithm>//max, for_each
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
    for (int i = 0; i < start_capacity; i++) {
        slot_metadata(i)->id = 0;
    }

    // Initialize the free list.
    for (int i = 0; i < start_capacity - 1; i++) {
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
        for (int i = old_capacity; i < m_capacity - 1; i++) {
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
Table reflection and serialization.
--------------------------------------------------------------------------------*/


// TableElement
//--------------------------------------------------------------------------------
BEGIN_ENTRIES(TableElement)
    ENTRY(id)
    ENTRY(index)
END_ENTRIES()
DESCRIPTOR_INSTANCE(TableElement);


// Table
//--------------------------------------------------------------------------------
DESCRIPTOR_INSTANCE(Table);


REFLECT_PRIMITIVE_PRINT(Table)
{
    Table &table = (Table &) obj;
    out << name() << "[\n";
    for (TableElement element : table) {
        out << std::string(4*(indent_level+1), ' ');
        table.type()->print(*table[element], out, indent_level + 1);
        out << ",\n";
    }
    out << std::string(4*indent_level, ' ') << "]";
}


REFLECT_PRIMITIVE_PACK(Table)
{
    Table &table = (Table &) obj;

    Reflector::pack(table.type(), out);

    uint32_t num_elements = 0;
    uint32_t min_capacity = 1;
    for (TableElement element : table) {
        // The minimum capacity the table must be initialized with when unpacked is two plus the maximum index of an element.
        if (element.index+2 > min_capacity) min_capacity = element.index+2;
        num_elements++;
    }
    Reflector::pack(num_elements, out);
    Reflector::pack(min_capacity, out);

    for (TableElement element : table) {
        Reflector::pack(element, out);
        table.type()->pack(*table[element], out);
    }
}


REFLECT_PRIMITIVE_UNPACK(Table)
{
    TypeHandle type;
    Reflector::unpack(in, type);

    uint32_t num_elements;
    Reflector::unpack(in, num_elements);
    uint32_t capacity;
    Reflector::unpack(in, capacity);

    Table table(type, capacity);
    
    // Unpack the elements into their slots.
    // This breaks the validity of the table, so it must be fixed after!
    for (int i = 0; i < num_elements; i++) {
        TableElement element;
        Reflector::unpack(in, element);
        table.slot_metadata(element.index)->id = element.id;

        table.type()->unpack(in, *table[element]);
    }
    // Fix up the table.
    // Initialize the free list.
    for (int i = 0; i < capacity; i++) {
        if (table.slot_metadata(i)->id == 0) {
            table.first_free_index = i;
            break;
        }
    }
    uint32_t connecting_index = table.first_free_index;
    for (int i = table.first_free_index + 1; i < capacity; i++) {
        if (table.slot_metadata(i)->id == 0) {
            table.empty_slot(connecting_index)->next_free_index = i;
            connecting_index = i;
        }
    }
    table.empty_slot(connecting_index)->next_free_index = 0;

    *((Table *) &obj) = table;
}


/*--------------------------------------------------------------------------------
Table forward iterator.
--------------------------------------------------------------------------------*/
TableIterator Table::begin()
{
    TableIterator iter(this);
    for (int i = 0; i < m_capacity; i++) {
        if (!slot_is_empty(i)) {
            iter.element = TableElement(slot_metadata(i)->id, i);
            return iter;
        }
    }
    assert(0);
}

TableIterator &TableIterator::operator++()
{
    for (int i = element.index+1; i < table->m_capacity; i++) {
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

