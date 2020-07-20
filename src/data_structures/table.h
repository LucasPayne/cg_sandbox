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
#include <limits>//numeric_limits
#include <string>//std::string
#include <stdint.h>
#include <stdio.h>//error logging
#include <stdlib.h>//exit
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
    GenericTable() {} //empty constructor, appears to be needed for std::vector.
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
    TableCollection data structure.
----------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
typedef uint8_t TableCollectionType;
#define TABLE_COLLECTION_MAX_NUM_TYPES ( std::numeric_limits<TableCollectionType>::max() )

///*--------------------------------------------------------------------------------
//All types which will be stored in a TableCollection _must_ derive from this class.
//This allows that type to store its own static data, which holds the type ID. This type
//ID is then available to templated methods, which can then retrieve the relevant table from
//their type template-parameter.
//--------------------------------------------------------------------------------*/
//struct TableCollectionTypeEntry {
//    static TableCollectionType type_id;
//};
// A handle to a member of a table in a TableCollection contains the type ID, so the
// interface can switch the table used depending on this ID.
struct TypedTableHandle : public GenericTableHandle {
    TableCollectionType type;
};

// this class should only be usable by TableCollection. ---
class MemberTable : public GenericTable {
public:
    MemberTable() {} //empty constructor, appears to be needed for std::vector.
    MemberTable(TableCollectionType _type, size_t _size, const std::string &_name, int length = 1) :
        GenericTable(_size, length),
        m_type{_type}, m_name{_name}
    {}
    TableCollectionType type() const { return m_type; }
    std::string name() const { return m_name; }
private:
    TableCollectionType m_type;
    size_t m_type_size;
    std::string m_name;
};
class TableCollection {
public:
    std::vector<MemberTable> m_tables;
    TableCollection() {
        m_tables = std::vector<MemberTable>(0);
    }
    template <typename TYPE> // TYPE must contain a static member "type_id". todo: require this with concepts?
    void add_type(const std::string &name) {
        #define TABLE_COLLECTION_TABLE_START_LENGTH 16
        int num_types = m_tables.size();
        if (num_types >= TABLE_COLLECTION_MAX_NUM_TYPES) {
            fprintf(stderr, "ERROR: Exceeded the maximum number of types in a TableCollection.\n");
            exit(EXIT_FAILURE);
        }
        TableCollectionType next_type_id = num_types;
        // Set the type ID so that templated methods can access it.
        TYPE::type_id = next_type_id;
        m_tables.push_back(MemberTable(next_type_id, sizeof(TYPE), name, TABLE_COLLECTION_TABLE_START_LENGTH));
    }

    // This provides the table interface, but switches the table based on the type id.
    // lookup() is templated only.
    TypedTableHandle add(TableCollectionType type) {
        return to_typed_table_handle(m_tables[type].add(), type);
    }
    void remove(TypedTableHandle handle) {
        m_tables[handle.type].remove(to_generic_table_handle(handle));
    }

    // Templated table interface. remove() is not templated.
    template <typename TYPE>
    TypedTableHandle add() {
        MemberTable *table = get_table<TYPE>();
        return to_typed_table_handle(table->add(), TYPE::type_id);
    }
    template <typename TYPE>
    TYPE *lookup(TypedTableHandle handle) {
        MemberTable *table = get_table<TYPE>();
        return reinterpret_cast<TYPE *>(table->lookup(to_generic_table_handle(handle)));
    }
private:
    // Decay the typed handle to a regular GenericTableHandle.
    inline GenericTableHandle to_generic_table_handle(const TypedTableHandle &handle) const {
        GenericTableHandle generic_handle;
        generic_handle.id = handle.id;
        generic_handle.index = handle.index;
        return generic_handle;
    }
    // Upgrade the regular GenericTableHandle to include the type ID.
    inline TypedTableHandle to_typed_table_handle(const GenericTableHandle &generic_handle, TableCollectionType type) const {
        TypedTableHandle handle;
        handle.id = generic_handle.id;
        handle.index = generic_handle.index;
        handle.type = type;
        return handle;
    }
    // Helper method for templated methods to retrieve the relevant table for the type template-parameter.
    template <typename TYPE>
    inline MemberTable *get_table() {
        return &m_tables[TYPE::type_id];
    }
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
