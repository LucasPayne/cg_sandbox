#ifndef TABLE_H
#define TABLE_H
#include <vector>
typedef uint32_t TableEntryID;

template <typename T>
struct TableEntry {
    uint32_t next_free_index;
    TableEntryID id;
    T data;
};

// example: typedef Table<AspectEntry, Aspect> AspectTable
template <typename T, typename HANDLE_TYPE>
class Table {
    Table() {
        m_length = 1;
        m_first_free_index = 0;
        m_entries = std::vector<TableEntry<T>>(m_length);
        m_entries[0].next_free_index = 0;
    }
    HANDLE_TYPE add() {
        // Turn the next available slot in the table into an active entry,
        // then return a handle to it.
        uint32_t index = m_first_free_index;

        TableEntry<T> &slot = m_entries[m_first_free_index];
        slot.id = next_id();
        if (slot->next_free_index == 0) {
            // Resize the table if needed.
            uint32_t old_length = m_length;
            m_length *= 2;
            m_entries.resize(m_length);
            m_entries[m_first_free_index].next_free_index = old_length;
            // Link the new slots into the free list.
            for (int i = old_length; i < m_length-1; i++) {
                m_entries[i].next_free_index = i + 1; // the next slot is also free.
            }
            m_entries[m_length-1].next_free_index = 0; // no free slots past here.
        }
        // Delink this slot from the free list.
        m_first_free_index = slot->next_free_index;

        HANDLE_TYPE handle;
        handle.id = slot->id;
        handle.index = index;
        return handle;
    }
    T *lookup(HANDLE_TYPE handle) {
        TableEntry<T> &entry = m_entries[handle.index];
        if (entry.id != handle.id) return nullptr;
        return &entry.data;
    }

private:
    ResourceID next_id() {
        return m_next_id ++;
    }
    std::vector<TableEntry<T>> m_entries;
    uint32_t m_first_free_index;
    uint32_t m_length;
};


#endif // TABLE_H
