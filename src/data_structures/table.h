#ifndef TABLE_H
#define TABLE_H
/*--------------------------------------------------------------------------------
    Table data structure
----------------------------------------------------------------------------------
A Table is a container for objects of a certain size. When an object is added,
a handle to the object is returned. This handle can be used to lookup the same
object, retrieving a pointer to the data. Handles are always valid for as long as
the object is in the table. Returned pointers, however, cannot be trusted after a call
to add(). When a lookup is done with a handle given by add(), and the object has since
been removed, a null pointer will always be returned.

(Although this might not strictly be true, since the implementation uses a fixed-bit-size ID to achieve this.
 This will likely not be a problem.)

time complexity:
    add: O(1) in general (may trigger a buffer resize).
    remove: O(1).
    lookup from handle: O(1).

memory usage:
    The implementation, to achieve what is described above, uses a sparse array data structure.
    Entries are always added contiguously if there have been no removals.
    If the table is added to and removed from dynamically, this will lead to a non-optimal ratio
    of active entries to array length.

implementation notes:
    Currently, the underlying buffer resizes if there is not enough space. It never downsizes.
    This might be wanted, if for example, only very occasionally, many objects are added to the
    table then removed.
--------------------------------------------------------------------------------*/
#include <vector>
#include <stdint.h>
typedef uint32_t TableEntryID;


/*--------------------------------------------------------------------------------
A GenericTable is initialized with a type size. This means that tables
can be constructed from arbitrary types at runtime.

The table stores the correct size entries, for the given type size, but lookups
return a byte pointer which must be interpreted by the caller.
--------------------------------------------------------------------------------*/
struct GenericTableHandle {
    TableEntryID id;
    uint32_t index;
};
class GenericTable {
public:
    GenericTable(size_t entry_type_size, int length = 1);
    // Turn the next available slot in the table into an active entry,
    // then return a handle to it.
    GenericTableHandle add();
    // Remove the entry. If it is not there, nothing happens.
    void remove(GenericTableHandle handle);
    
    // Lookup the entry. If it is not there, return a null pointer.
    // The pointer is to the byte array that starts at the actual data, not including the header.
    uint8_t *lookup(GenericTableHandle handle);
private:
    struct Header {
        TableEntryID id;
        uint32_t next_free_index;
    };
    TableEntryID next_id();
    // Get the header of the entry/slot at the given index. This contains the ID and index of the next in the free list.
    inline Header *get_header(uint32_t index) {
        return reinterpret_cast<Header *>(&m_buffer[m_entry_size * index]);
    }
    std::vector<uint8_t> m_buffer;
    size_t m_entry_size; // This includes the Header size!
    uint32_t m_first_free_index;
    uint32_t m_length;
    TableEntryID m_next_id;
};


/*--------------------------------------------------------------------------------
    Templated table types. These are wrappers around an underlying generic
    table, with a custom handle type (that can have extra data, which won't be initialized
    by these methods), and for which lookups return a pointer to the actually stored type.
--------------------------------------------------------------------------------*/
template <typename T, typename HANDLE_TYPE>
class Table {
public:
    Table(int length = 1) : m_table(GenericTable(sizeof(T), length)) {}

    // These methods are the same as for the GenericTable, except each converts the custom handle
    // into a generic handle and passes it to the corresponding GenericTable method.
    // The lookup also casts to a pointer to the actual type.
    HANDLE_TYPE add() {
        // note: This could be faster if it is known that HANDLE_TYPE inherits from GenericTableHandle.
        //           HANDLE_TYPE handle;
        //           *((GenericTableHandle *) &handle) = m_table.add();
        GenericTableHandle generic_handle = m_table.add();
        HANDLE_TYPE handle;
        handle.id = generic_handle.id;
        handle.index = generic_handle.index;
        return handle;
    }
    void remove(HANDLE_TYPE handle) {
        GenericTableHandle generic_handle;
        generic_handle.id = handle.id;
        generic_handle.index = handle.index;
        m_table.remove(generic_handle);
    }
    T *lookup(HANDLE_TYPE handle) {
        GenericTableHandle generic_handle;
        generic_handle.id = handle.id;
        generic_handle.index = handle.index;
        return reinterpret_cast<T *>(m_table.lookup(generic_handle));
    }
private:
    GenericTable m_table;
};


#endif // TABLE_H
