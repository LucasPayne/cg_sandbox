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
#include <functional>
#include <limits>//numeric_limits
#include <string>//std::string
#include <stdint.h>
#include <stdio.h>//error logging
#include <stdlib.h>//exit
typedef uint32_t TableEntryID;

#include "reflector/serialization.h"


/*--------------------------------------------------------------------------------
A GenericTable is initialized with a type size. This means that tables
can be constructed from arbitrary types at runtime.

The table stores the correct size entries, for the given type size, but lookups
return a byte pointer which must be interpreted by the caller.
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct TableHandle {
    /*ENTRY*/ TableEntryID id;
    /*ENTRY*/ uint32_t index;
    static const TableHandle null() {
        TableHandle handle;
        handle.index = 0;
        handle.id = 0; // id of zero signifies this is a null handle.
        return handle;
    }
    TableHandle() {}
};


// An IterateeFunction transforms a TableHandle into another type.
// This allows custom table iterators to be defined easily, such as
// an iterator over raw pointers to table entries, or an iterator
// which adjoins more data to the handles.
template <typename ITERATED>
using IterateeFunction = std::function<ITERATED(TableHandle)>;


class GenericTable {
public:
    GenericTable() {}
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

    template <typename ITERATED>
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
        IteratorPosition(GenericTable *_table, IterateeFunction<ITERATED> _iteratee_function) :
            done{false}, table{_table}, iteratee_function{_iteratee_function}
        {
            handle.index = 0;
            seek_to_next();
        }
        bool done;
        TableHandle handle;

        GenericTable *table;
        IterateeFunction<ITERATED> iteratee_function;

        inline void operator++() {
            ++handle.index;
            seek_to_next();
        }
        inline ITERATED operator*() {
            handle.id = table->get_header(handle.index)->id;
            return iteratee_function(handle);
        }
        inline bool operator!=(IteratorPosition<ITERATED> throwaway) {
            return !done;
        }
    };

    template <typename ITERATED>
    struct Iterator {
        GenericTable *table;
        IterateeFunction<ITERATED> iteratee_function;
        Iterator(GenericTable *_table, IterateeFunction<ITERATED> _iteratee_function) :
            table{_table}, iteratee_function{_iteratee_function}
        {}
        inline IteratorPosition<ITERATED> begin() {
            return IteratorPosition<ITERATED>(table, iteratee_function);
        }
        inline IteratorPosition<ITERATED> end() {
            return IteratorPosition<ITERATED>();
        }
    };

    template <typename ITERATED>
    Iterator<ITERATED> iterator(IterateeFunction<ITERATED> iteratee_function) {
        return Iterator<ITERATED>(this, iteratee_function);
    }

    // Default iterator has identity IterateeFunction, so it just iterates TableHandles.
    Iterator<TableHandle> iterator() {
        return Iterator<TableHandle>(this,
            [](TableHandle handle)->TableHandle {
                return handle;
            }
        );
    }

    //-end iterator hack--------------------------------------------------------------

//private:
    struct Header {
        TableEntryID id;
        uint32_t next_free_index;
    };
    TableEntryID next_id();
    // Get the header of the entry/slot at the given index. This contains the ID and index of the next in the free list.
    Header *get_header(uint32_t index) {
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
typedef uint16_t TableCollectionType;
#define TABLE_COLLECTION_MAX_NUM_TYPES ( std::numeric_limits<TableCollectionType>::max() )
#define NULL_TABLE_COLLECTION_TYPE_ID ( std::numeric_limits<TableCollectionType>::max() )


// When a type is registered to a table collection, in code, this static data is instantiated,
// which will contain the type ID.
template <typename TYPE>
struct TableCollectionTypeData {
    static TableCollectionType type_id;
};
// Statically initialize all of these IDs to null.
template <typename TYPE>
TableCollectionType TableCollectionTypeData<TYPE>::type_id(NULL_TABLE_COLLECTION_TYPE_ID);


/*--------------------------------------------------------------------------------
    Handles into the TableCollection are templated. This is purely a type variant,
    and adds no extra data. This means the user of the TableCollection will
    declare things such as TableCollectionHandle<Thing>.
--------------------------------------------------------------------------------*/
template <typename TYPE>
/*REFLECTED*/ struct TableCollectionHandle : public TableHandle {
};
// A "typed" handle is not templated, and instead stores the type ID. When it is used with the TableCollection interface,
// the type ID is used for dispatching to the relevant table.

/*REFLECTED*/ struct TypedTableCollectionHandle : public TableHandle {
    /*ENTRY*/ TableCollectionType type;

    // Create a typed handle from handle for a certain type. This puts the type ID in the handle.
    template <typename TYPE>
    static TypedTableCollectionHandle create(TableCollectionHandle<TYPE> &handle) {
        TypedTableCollectionHandle typed_handle;
        typed_handle.index = handle.index;
        typed_handle.id = handle.id;
        typed_handle.type = TableCollectionTypeData<TYPE>::type_id;
        return typed_handle;
    }
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
struct TableCollectionEmptyBaseType {};
template<typename BASE_TYPE = TableCollectionEmptyBaseType>
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
        TableCollectionTypeData<TYPE>::type_id = next_type_id;
        m_tables.push_back(MemberTable(next_type_id, sizeof(TYPE), name, TABLE_COLLECTION_TABLE_START_LENGTH));
    }
    // Unregistered types are statically initialized to -1. This macro is used by the templated methods, so that
    // the probably common bug of forgetting to register a type is easily discovered. However, this is a slight overhead
    // every call to a templated method.
    #define CHECK_IF_REGISTERED(TYPE) {\
        if (TableCollectionTypeData<TYPE>::type_id == NULL_TABLE_COLLECTION_TYPE_ID) {\
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
    TableCollectionHandle<TYPE> add() {
        CHECK_IF_REGISTERED(TYPE);
        TableHandle handle = get_table<TYPE>()->add();
        return *reinterpret_cast<TableCollectionHandle<TYPE> *>(&handle);
    }
    template <typename TYPE>
    void remove(TableCollectionHandle<TYPE> handle) {
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
    TypedTableCollectionHandle typed_handle(TableCollectionHandle<TYPE> handle) const {
        CHECK_IF_REGISTERED(TYPE);
        TypedTableCollectionHandle typed_handle;
        typed_handle.id = handle.id;
        typed_handle.index = handle.index;
        typed_handle.type = TableCollectionTypeData<TYPE>::type_id;
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
    template <typename TYPE, typename ITERATED>
    GenericTable::Iterator<ITERATED> iterator(IterateeFunction<ITERATED> iteratee_function) {
        CHECK_IF_REGISTERED(TYPE);
        MemberTable *table = get_table<TYPE>();
        return table->iterator<ITERATED>(iteratee_function);
    }

private:
    // Helper method for templated methods to retrieve the relevant table for the type template-parameter.
    template <typename TYPE>
    inline MemberTable *get_table() {
        return &m_tables[TableCollectionTypeData<TYPE>::type_id];
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
        return m_table.add();
    }
    void remove(TableHandle handle) {
        m_table.remove(handle);
    }
    T *lookup(TableHandle handle) {
        return reinterpret_cast<T *>(m_table.lookup(handle));
    }

    template <typename ITERATED>
    inline GenericTable::Iterator<ITERATED> iterator(IterateeFunction<ITERATED> iteratee_function) {
        return m_table.iterator<ITERATED>(iteratee_function);
    }

    inline GenericTable::Iterator<TableHandle> iterator() {
        return m_table.iterator();
    }
//-debugging
// private:
    GenericTable m_table;
};


// Table serialization functions.
// These are not auto-generated since a table is a container which needs its own custom serialization.
template <typename T>
void pack(Table<T> &obj, std::ostream &out) {
    // length : uint32_t
    // next ID : TableEntryID
    // computed first_free_index : uint32_t
    // number of active entries : uint32_t
    // for each active entry:
    //    entry index : uint32_t
    //    entry ID : TableEntryID
    //    entry object : T

    // Pack the metadata first.
    // Recomputing the first free index, since the free list will be different on reconstruction.
    pack(obj.m_table.m_length, out);
    pack(obj.m_table.m_next_id, out);

    // Pack the first free index, which is recomputed to be the least such index, so that a free list can be constructed
    // on unpack.
    uint32_t first_free_index; // A table always has at least one free slot, so find the free slot with least index.
    for (int i = 0; i < obj.m_table.m_length; i++) {
        if (obj.m_table.get_header(i)->id == 0) {
            first_free_index = i;
            break;
        }
    }
    pack(first_free_index, out);

    // Pack the number of active entries in the table, since the unpacker will need to know when to stop.
    uint32_t num_active_entries = 0;
    {
        for (TableHandle handle : obj.iterator()) {
            num_active_entries++;
        }
    }
    pack(num_active_entries, out);

    // Densely pack the entries.
    for (TableHandle handle : obj.iterator()) {
        // pack index, id, object entry.

        // For each entry, store its index, so this can be unpacked into the sparse array.
        pack(handle.index, out);

        // Pack the entry ID.
        pack(handle.id, out);

        // Pack the actual entry object.
        T *entry_pointer = obj.lookup(handle);
        pack(*entry_pointer, out);
    }
}
template <typename T>
void unpack(std::istream &in, Table<T> &obj) {
    // length : uint32_t
    // next ID : TableEntryID
    // computed first_free_index : uint32_t
    // number of active entries : uint32_t
    // for each active entry:
    //    entry index : uint32_t
    //    entry ID : TableEntryID
    //    entry object : T

    uint32_t table_length;
    unpack(in, table_length);
    obj = Table<T>(table_length);

    unpack(in, obj.m_table.m_next_id);
    unpack(in, obj.m_table.m_first_free_index);

    uint32_t num_active_entries;
    unpack(in, num_active_entries);
    for (int i = 0; i < num_active_entries; i++) {
        // Unpack index, ID, object entry.
        TableHandle handle;
        unpack(in, handle.index);
        unpack(in, handle.id);
        // Set the ID in the header of this slot to flag that this slot is active.
        GenericTable::Header *header = obj.m_table.get_header(handle.index);
        header->id = handle.id;
        // Unpack the object.
        T *entry_pointer = obj.lookup(handle);
        unpack(in, *entry_pointer);
    }
    
    // Construct the free list.
    uint32_t connecting_index = obj.m_table.m_first_free_index;
    for (uint32_t i = connecting_index+1; i < obj.m_table.m_length; i++) {
        if (obj.m_table.get_header(i)->id == 0) {
            // Connect the free list to this index.
            obj.m_table.get_header(connecting_index)->next_free_index = i;
            // Proceed to connect this index further into the free list.
            connecting_index = i;
        }
    }
    obj.m_table.get_header(connecting_index)->next_free_index = 0; // Signify that this empty slot is at the end of the free list.
}
template <typename T>
void print(Table<T> &obj) {
    std::cout << "Table<T> {\n";
    std::cout << "    m_first_free_index: " << obj.m_table.m_first_free_index << "\n";
    std::cout << "    m_length: " << obj.m_table.m_length << "\n";
    std::cout << "    m_next_id: " << obj.m_table.m_next_id << "\n";
    std::cout << "    table: [\n";
    for (TableHandle handle : obj.iterator()) {
        std::cout << "        ";
        print(*obj.lookup(handle));
        std::cout << "\n";
    }
    std::cout << "    ]\n";
    std::cout << "}\n";
}

#include "/home/lucas/computer_graphics/cg_sandbox/core/data_structures/table.serialize.h" /*SERIALIZE*/
#endif // TABLE_H
