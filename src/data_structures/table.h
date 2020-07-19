#ifndef TABLE_H
#define TABLE_H
/*--------------------------------------------------------------------------------
    Table data structure
----------------------------------------------------------------------------------
time complexity:
    add: O(1) in general (may trigger a buffer resize).
    remove: O(1).
    lookup from handle: O(1).
--------------------------------------------------------------------------------*/
#include <vector>
typedef uint32_t TableEntryID;

template <typename T>
struct TableEntry {
    uint32_t next_free_index;
    TableEntryID id;
    T data;
};

class AspectTable {
    AspectType aspect_type;
    GenericTable table;
    AspectHandle
};


/*--------------------------------------------------------------------------------
A GenericTable is initialized with type information. This means that tables
can be constructed from arbitrary types at runtime, if there is some runtime
type information for them.

The table stores the correct size entries, for the given type size, but lookups
return a byte pointer which must be interpreted by the caller.
--------------------------------------------------------------------------------*/
struct GenericTableHandle {
    TableEntryID id;
    uint32_t index;
};
class GenericTable {
    struct Header {
        TableEntryID id;
        uint32_t next_free_index;
    };
    GenericTable(size_t entry_type_size, int length = 1) {
        // Length >= 1.
        m_entry_type_size = entry_type_size;
        m_length = length;
        m_first_free_index = 0;
        m_entries[0].next_free_index = 0;
        m_entry_size = sizeof(Header) + entry_type_size; // The size of per-entry metadata in the table must be accounted for.
        m_buffer = std::vector<uint8_t>(m_length * m_entry_size); // Allocate the buffer for the table. This must account for metadata size.
    }
    // Turn the next available slot in the table into an active entry,
    // then return a handle to it.
    GenericTableHandle add() {
        uint32_t index = m_first_free_index;
        Header *header = get_header(index);
        header->id = next_id();
        if (header->next_free_index == 0) {
            // Resize the table if needed.
            uint32_t old_length = m_length;
            m_length *= 2;
            m_entries.resize(m_length * m_entry_size);
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
        GenericTableHandle handle;
        handle.id = header->id;
        handle.index = index;
        return handle;
    }
    // Remove the entry. If it is not there, nothing happens.
    void remove(GenericTableHandle handle) {
        Header *header = get_header(handle.index);
        if (handle.id != header->id) return; // not there.
        // Nullify the entry.
        header->id = 0;
        // Link the slot back into the free list.
        header->next_free_index = m_first_free_index;
        m_first_free_index = handle.index;
    }
    
    // Lookup the entry. If it is not there, return a null pointer.
    // The pointer is to the byte array that starts at the actual data, not including the header.
    uint8_t *lookup(GenericTableHandle handle) {
        Header *header = get_header(handle.index);
        if (header->id != handle.id) return nullptr; // not there.
        return reinterpret_cast<uint8_t *>(header+1); // Adding one will move the pointer to the start of the data.
	      // -Is this always true? Is pointer arithmetic always +n*sizeof(T) or could structure padding affect this?
    }
private:
    ResourceID next_id() {
        return m_next_id ++;
    }
    // Get the header of the entry/slot at the given index. This contains the ID and index of the next in the free list.
    inline Header *get_header(uint32_t index) {
        return reinterpret_cast<Header *> &m_entries[m_entry_size * index];
    }

    std::vector<uint8_t> m_buffer;
    size_t m_entry_size; // This includes the GenericTableEntryHeader size!
    uint32_t m_first_free_index;
    uint32_t m_length;
};

// example: typedef Table<AspectEntry, Aspect> AspectTable;
template <typename T, typename HANDLE_TYPE>
class Table : public GenericTable {
public:
    Table(int length = 1) {
        // Length >= 1.
        m_length = length;
        m_first_free_index = 0;
        m_entries = std::vector<TableEntry<T>>(m_length);
        m_entries[0].next_free_index = 0;
    }
    // Turn the next available slot in the table into an active entry,
    // then return a handle to it.
    HANDLE_TYPE add() {
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

    // Remove the entry. If it is not there, nothing happens.
    void remove(HANDLE_TYPE handle) {
        TableEntry<T> &entry = m_entries[handle.index];
        if (entry.id != handle.id) return;
        entry.id = 0;
        // Link the slot back into the free list.
        entry.next_free_index = m_first_free_index;
        m_first_free_index = handle.index;
    }
    
    // Lookup the entry. If it is not there, return a null pointer.
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
