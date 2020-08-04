/*--------------------------------------------------------------------------------
The registry is a global stash of tables. Whenever a table is created, it should be
created in the registry if serializable shared references are wanted (probably always).

A Reference<T> contains all information needed to access the underlying object, without
relying on memory addresses. This is because the Reference contains a handle
to the global registry, which can be anywhere in memory, and a handle to the underlying entry in that table.

notes:
    The registry contains tables, but users of the registry should not know or care
    that the registry is itself a table.
--------------------------------------------------------------------------------*/
#ifndef REGISTRY_H
#define REGISTRY_H
#include "stdio.h"
#include "stdlib.h"
#include "data_structures/table.h"

// TableReference<T> is a wrapper of TableHandle which gives it a type. The underlying generic table
// in the registry is never accessed directly, and type-safe functions through the reference are used instead.
template <typename T>
struct TableReference {
public:
    TableHandle handle;
    TableReference(TableHandle &table_handle) {
        *this = table_handle;
    }
    Reference<T> add() {
        TableHandle entry_handle = registry.add();
        return Reference<T>(handle, entry_handle);
    }
    void remove(Reference<T> ref) {
        if (ref.table != handle) {
            // There can be multiple tables in the registry for the same type.
            // This means the type system allows Reference<T>s to be passed to the wrong TableReference<T>,
            // so this error is handled here.
            fprintf(stderr, "ERROR: Attempted to remove underlying object of Reference<T> from the wrong TableReference<T> table.\n");
            exit(EXIT_FAILURE);
        }
        registry.lookup(handle)
    }
private:
    // Helper function to access the underlying table.
    // Table<T> does not add any data or virtual methods to GenericTable, so this cast should be safe.
    Table<T> &underlying_table() {
        return *reinterpret_cast<Table<T> *>(registry.lookup(handle));
    }
}

template <typename T>
struct Reference {
public:
    friend TableReference<T>; // The TableReference constructs References and needs access to the private data.
    TableHandle handle;
    TableReference<T> table;

    inline T &operator*() {
        GenericTable *table_ptr = registry.lookup(table);
        if (table_ptr == nullptr) {
            fprintf(stderr, "ERROR: Attempted to dereference Reference into table not found in the global registry.\n");
            exit(EXIT_FAILURE);
        }
        T *ptr = reinterpret_cast<T *>(table_ptr->lookup(*this));
        if (ptr == nullptr) {
            fprintf(stderr, "ERROR: Attempted to dereference invalid Reference.\n");
            exit(EXIT_FAILURE);
        }
        return *ptr;
    }
    inline T *operator->() {
        return &(*this);
    }
private:
    // Constructor used only by TableReference<T> for returning Reference<T>s to entries in its underlying table.
    Reference(TableReference<T> &_table, TableHandle &_handle) :
        table{_table}, handle{_handle}
    {}
}

//--------------------------------------------------------------------------------
namespace Registry {

static Table<GenericTable> registry;


// e.g.
//     TableReference<World> worlds = Registry::add<World>();
template <typename T>
TableReference<T> add() {
    TableHandle new_table_handle = registry.add();
    GenericTable &new_table = *registry.lookup(new_table_handle);
    const size_t new_table_start_length = 1;
    new_table = GenericTable(sizeof(T), new_table_start_length);
    return TableReference<T>(new_table_handle);
}
} // end namespace Registry
//--------------------------------------------------------------------------------

#endif // REGISTRY_H
