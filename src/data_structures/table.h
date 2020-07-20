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
struct TableHandle {
    TableEntryID id;
    uint32_t index;
};
class GenericTable {
public:
    GenericTable() {} //empty constructor, appears to be needed for std::vector.
    GenericTable(size_t entry_type_size, int length = 1);
    // Turn the next available slot in the table into an active entry,
    // then return a handle to it.
    TableHandle add();
    // Remove the entry. If it is not there, nothing happens.
    void remove(TableHandle handle);
    
    // Lookup the entry. If it is not there, return a null pointer.
    // The pointer is to the byte array that starts at the actual data, not including the header.
    uint8_t *lookup(TableHandle handle);
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

reasons for extensions:
    Having a BASE_TYPE template parameter, as well as TypedTableCollectionHandle,
    was originally for linked lists of "aspects" - Each table entry holds
    the typed handle to the next aspect in its header. This header is declared
    in the common BASE_TYPE.
----------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
typedef uint8_t TableCollectionType;
#define TABLE_COLLECTION_MAX_NUM_TYPES ( std::numeric_limits<TableCollectionType>::max() )

/*--------------------------------------------------------------------------------
    Handles into the TableCollection are templated. This is purely a type variant,
    and adds no extra data. This means the user of the TableCollection will
    declare things such as TableCollectionHandle<Thing>.
--------------------------------------------------------------------------------*/
template <typename TYPE>
struct TableCollectionHandle : public TableHandle {};
// A "typed" handle is not templated, and instead stores the type ID. When it is used with the TableCollection interface,
// the type ID is used for dispatching to the relevant table.
struct TypedTableCollectionHandle : public TableHandle {
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

template<typename BASE_TYPE> // BASE_TYPE: All types in the collection, at least logically, inherit from this.
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

    // These methods are simple wrappers around the GenericTable interface, instead dispatching the call
    // to the relevant table.
    // A TYPE pointer is returned instead of the byte pointer returned by GenericTable, since the type is known.

    // Interface taking a templated handle.
    template <typename TYPE>
    TableCollectionHandle<TYPE> add() {
        TableHandle handle = get_table<TYPE>()->add();
        return *reinterpret_cast<TableCollectionHandle<TYPE> *>(&handle);
    }
    template <typename TYPE>
    void remove(TableCollectionHandle<TYPE> handle) {
        TableHandle table_handle = *reinterpret_cast<TableHandle *>(&handle);
        get_table<TYPE>()->remove(table_handle);
    }
    template <typename TYPE>
    TYPE *lookup(TableHandle handle) {
        TableHandle table_handle = *reinterpret_cast<TableHandle *>(&handle);
        return reinterpret_cast<TYPE *>(get_table<TYPE>()->lookup(table_handle));
    }

    // Convert a templated handle into a "typed" handle, which contains the type ID.
    template <typename TYPE>
    TypedTableCollectionHandle typed_handle(TableCollectionHandle<TYPE> handle) const {
        TypedTableCollectionHandle typed_handle;
        typed_handle.id = handle.id;
        typed_handle.index = handle.index;
        typed_handle.type = TYPE::type_id;
        return typed_handle;
    }
    // A typed handle can be used for lookup. The relevant table is searched,
    // and a pointer to the common base class between all types in the collection is returned.
    // This gives a common base of data for the entries in each table in the collection.
    BASE_TYPE *lookup(TypedTableCollectionHandle typed_handle) {
        TableHandle handle;
        handle.id = typed_handle.id;
        handle.index = typed_handle.index;
        return reinterpret_cast<BASE_TYPE *>(m_tables[typed_handle.type].lookup(handle));
    }
private:
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
        // note: This could be faster if it is known that HANDLE_TYPE inherits from TableHandle.
        //           HANDLE_TYPE handle;
        //           *((TableHandle *) &handle) = m_table.add();
        TableHandle generic_handle = m_table.add();
        HANDLE_TYPE handle;
        handle.id = generic_handle.id;
        handle.index = generic_handle.index;
        return handle;
    }
    void remove(HANDLE_TYPE handle) {
        TableHandle generic_handle;
        generic_handle.id = handle.id;
        generic_handle.index = handle.index;
        m_table.remove(generic_handle);
    }
    T *lookup(HANDLE_TYPE handle) {
        TableHandle generic_handle;
        generic_handle.id = handle.id;
        generic_handle.index = handle.index;
        return reinterpret_cast<T *>(m_table.lookup(generic_handle));
    }
private:
    GenericTable m_table;
};


#endif // TABLE_H
