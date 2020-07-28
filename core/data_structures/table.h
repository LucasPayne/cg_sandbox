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

reasons for extensions:
    A templated template parameter for passing the templated (for the type, not any change in data) extension class of handles
    was added to allow the table to directly return handles with space for extra data, so that conversions don't have to be made.
    This was done for the resource system, since each handle needs a reference to the resource model it is a part of.
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

    //-begin iterator hack------------------------------------------------------------
    // This iterator is implemented _only_ so that range-based-for works.
    //    https://en.cppreference.com/w/cpp/language/range-for
    struct IteratorPosition {
        inline void seek_to_next() {
            while (true) {
                if (handle.index == table->m_length) {
                    done = true;
                    return;
                }
                if (table->get_header(handle.index)->id != 0) return;
                ++handle.index;
            }
        }
        IteratorPosition() {}
        IteratorPosition(GenericTable *_table) :
            done{false}, table{_table}
        {
            handle.index = 0;
            seek_to_next();
        }
        bool done;
        TableHandle handle;
        GenericTable *table;
        inline void operator++() {
            ++handle.index;
            seek_to_next();
        }
        inline TableHandle operator*() {
            handle.id = table->get_header(handle.index)->id;
            return handle;
        }
        inline bool operator!=(IteratorPosition throwaway) {
            return !done;
        }
    };
    friend IteratorPosition;
    struct Iterator {
        GenericTable *table;
        Iterator(GenericTable *_table) : table{_table} {}
        inline IteratorPosition begin() {
            return IteratorPosition(table);
        }
        inline IteratorPosition end() { return IteratorPosition(); }
    };
    inline Iterator iterator() {
        return Iterator(this);
    }
    //-end iterator hack--------------------------------------------------------------

//private:
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
#define NULL_TABLE_COLLECTION_TYPE_ID ( std::numeric_limits<TableCollectionType>::max() )

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

// BASE_TYPE: All types in the collection, at least logically, inherit from this.
// HANDLE_TYPE: Must inherit from TableCollectionHandle. Optionally overridden to allow extra data in handles, to be initialized by
//              something which wraps the underlying table.
template<typename BASE_TYPE, template<typename> typename HANDLE_TYPE = TableCollectionHandle>
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
    // Unregistered types are statically initialized to -1. This macro is used by the templated methods, so that
    // the probably common bug of forgetting to register a type is easily discovered. However, this is a slight overhead
    // every call to a templated method.
    #define CHECK_IF_REGISTERED(TYPE) {\
        if (TYPE::type_id == NULL_TABLE_COLLECTION_TYPE_ID) {\
            fprintf(stderr, "ERROR: Forgot to register a type in a TableCollection!\n");\
            exit(EXIT_FAILURE);\
        }\
    }
    // These methods are simple wrappers around the GenericTable interface, instead dispatching the call
    // to the relevant table.
    // A TYPE pointer is returned instead of the byte pointer returned by GenericTable, since the type is known.
    //
    // Interface taking a templated handle.
    template <typename TYPE>
    HANDLE_TYPE<TYPE> add() {
        CHECK_IF_REGISTERED(TYPE);
        TableHandle handle = get_table<TYPE>()->add();
        return *reinterpret_cast<HANDLE_TYPE<TYPE> *>(&handle);
    }
    template <typename TYPE>
    void remove(HANDLE_TYPE<TYPE> handle) {
        CHECK_IF_REGISTERED(TYPE);
        TableHandle table_handle = *reinterpret_cast<TableHandle *>(&handle);
        get_table<TYPE>()->remove(table_handle);
    }
    template <typename TYPE>
    TYPE *lookup(TableHandle handle) {
        CHECK_IF_REGISTERED(TYPE);
        TableHandle table_handle = *reinterpret_cast<TableHandle *>(&handle);
        return reinterpret_cast<TYPE *>(get_table<TYPE>()->lookup(table_handle));
    }

    // Convert a templated handle into a "typed" handle, which contains the type ID.
    template <typename TYPE>
    TypedTableCollectionHandle typed_handle(HANDLE_TYPE<TYPE> handle) const {
        CHECK_IF_REGISTERED(TYPE);
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
        return reinterpret_cast<BASE_TYPE *>(get_table(typed_handle.type)->lookup(handle));
    }
    // A typed handle can also be used for removal.
    void remove(TypedTableCollectionHandle typed_handle) {
        TableHandle handle;
        handle.id = typed_handle.id;
        handle.index = typed_handle.index;
        get_table(typed_handle.type)->remove(handle);
    }

    // Templated iterator. Iterate over a certain type.
    template <typename TYPE>
    inline GenericTable::Iterator iterator() {
        CHECK_IF_REGISTERED(TYPE);
        return get_table<TYPE>()->iterator();
    }

private:
    // Helper method for templated methods to retrieve the relevant table for the type template-parameter.
    template <typename TYPE>
    inline MemberTable *get_table() {
        return &m_tables[TYPE::type_id];
    }
    inline MemberTable *get_table(TableCollectionType type) {
        return &m_tables[type];
    }
};


/*--------------------------------------------------------------------------------
    Templated table types. These are wrappers around an underlying generic
    table and for which lookups return a pointer to the actually stored type.
--------------------------------------------------------------------------------*/
template <typename T>
class Table {
public:
    Table(int length = 1) : m_table(GenericTable(sizeof(T), length)) {}

    // These methods are the same as for the GenericTable, except each converts the custom handle
    // into a generic handle and passes it to the corresponding GenericTable method.
    // The lookup also casts to a pointer to the actual type.
    inline TableHandle add() {
        // note: This could be faster if it is known that HANDLE_TYPE inherits from TableHandle.
        //           HANDLE_TYPE handle;
        //           *((TableHandle *) &handle) = m_table.add();
        return m_table.add();
    }
    void remove(TableHandle handle) {
        m_table.remove(handle);
    }
    T *lookup(TableHandle handle) {
        return reinterpret_cast<T *>(m_table.lookup(handle));
    }

    inline GenericTable::Iterator iterator() {
        return m_table.iterator();
    }
private:
    GenericTable m_table;
};


#endif // TABLE_H
