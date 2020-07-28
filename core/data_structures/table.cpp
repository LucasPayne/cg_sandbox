#include "data_structures/table.h"
#include <stdio.h>

// public methods
//--------------------------------------------------------------------------------
GenericTable::GenericTable(size_t entry_type_size, int length)
{
    // Length >= 1.
    m_next_id = 1; // 0 is the null ID.
    m_length = length;
    m_first_free_index = 0;
    m_entry_size = sizeof(Header) + entry_type_size; // The size of per-entry metadata in the table must be accounted for.
    m_buffer = std::vector<uint8_t>(m_length * m_entry_size); // Allocate the buffer for the table. This must account for metadata size.
    // Initialize the free list.
    for (int index = 0; index < m_length-1; index++) {
        get_header(index)->next_free_index = index + 1;
    }
    if (m_length >= 1) {
        get_header(m_length-1)->next_free_index = 0;
    }
}

TableHandle GenericTable::add()
{
    uint32_t index = m_first_free_index;
    Header *header = get_header(index);
    header->id = next_id();
    if (header->next_free_index == 0) {
        // Resize the table if needed.
        uint32_t old_length = m_length;
        m_length *= 2;
        m_buffer.resize(m_length * m_entry_size);
        // Remember to recompute the header pointer!
        header = get_header(index);
        // Link the new slots into the free list.
        header->next_free_index = old_length;
        for (int i = old_length; i < m_length-1; i++) {
            get_header(i)->next_free_index = i + 1; // the next slot is also free.
        }
        get_header(m_length-1)->next_free_index = 0; // no free slots past here.
    }
    // Delink this slot from the free list.
    m_first_free_index = header->next_free_index;
    // Construct and return a handle to the new entry.
    TableHandle handle;
    handle.id = header->id;
    handle.index = index;

    //printf("added new entity at index %u, id %u\n", handle.index, header->id);getchar();
    return handle;
}

void GenericTable::remove(TableHandle handle)
{
    Header *header = get_header(handle.index);
    if (handle.id != header->id) return; // not there.
    // Nullify the entry.
    header->id = 0;
    // Link the slot back into the free list.
    header->next_free_index = m_first_free_index;
    m_first_free_index = handle.index;
}

uint8_t *GenericTable::lookup(TableHandle handle)
{
    Header *header = get_header(handle.index);
    if (header->id == 0) return nullptr; // ID 0 represents null, so the entry is not there.
    if (header->id != handle.id) return nullptr; // Not there.
    return reinterpret_cast<uint8_t *>(header+1); // Adding one will move the pointer to the start of the data.
          // -Is this always true? Is pointer arithmetic always +n*sizeof(T) or could structure padding affect this?
}


// private methods
//--------------------------------------------------------------------------------
TableEntryID GenericTable::next_id()
{
    return m_next_id ++;
}
