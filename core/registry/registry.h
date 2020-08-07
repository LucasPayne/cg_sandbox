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
#include <iostream>
#include "data_structures/table.h"

// TableReference<T> is a wrapper of TableHandle which gives it a type. The underlying generic table
// in the registry is never accessed directly, and type-safe functions through the TableReference<T> are used instead.
template <typename T> struct Reference; // Forward declare Reference<T> so it can be befriended.
template <typename T>
/*REFLECTED*/ struct TableReference {
    friend Reference<T>; // Reference<T>s want access to the underlying table for dereferencing.
public:
    /*ENTRY*/ TableHandle handle;
    TableReference(TableHandle &_handle) :
        handle{_handle}
    {}
    TableReference() {}
    Reference<T> add();
    void remove(Reference<T> ref);
};

template <typename T>
/*REFLECTED*/ struct Reference {
    friend TableReference<T>; // The TableReference constructs References and needs access to the private data.
public:
    /*ENTRY*/ TableReference<T> table;
    /*ENTRY*/ TableHandle handle;

    T &operator*();
    T *operator->();

    Reference() : handle{TableHandle::null()} {} // Empty constructor gives a null reference, signified by a null handle.
private:
    // Constructor used only by TableReference<T> for returning Reference<T>s to entries in its underlying table.
    Reference(TableReference<T> _table, TableHandle _handle) :
        table{_table}, handle{_handle}
    {}
};

//--------------------------------------------------------------------------------

// struct RegistryTable {
//     ITable *table_pointer;
//     GenericTable table;
// }


class Registry {
public:
    // e.g.
    //     TableReference<World> worlds = Registry::add<World>();
    template <typename T>
    static TableReference<T> add() {
        printf("[registry] Adding new table to registry...\n");
        TableHandle new_table_handle = registry.add();
        GenericTable &new_table = *registry.lookup(new_table_handle);
        const size_t new_table_start_length = 1;
        new_table = GenericTable(sizeof(T), new_table_start_length);
        printf("[registry] Added new table.\n");
        return TableReference<T>(new_table_handle);
    }

    // Get the actual underlying table from the TableReference<T>.
    template <typename T>
    static Table<T> *get_table(TableReference<T> table_ref) {
        GenericTable *generic_table = registry.lookup(table_ref.handle);
        if (generic_table == nullptr) {
            fprintf(stderr, "[registry] ERROR: Attempted to get get unknown table in the registry.\n");
            exit(EXIT_FAILURE);
        }
        // Table<T> does not add any data or virtual methods to GenericTable, which it derives from,
        // so this should work.
        return reinterpret_cast<Table<T> *>(generic_table);
    }

    // // The Registry is not serializable like a regular object, as it is not an object type, just global a global table.
    // // Serialization functions are namespaced in Registry:: and do not take an object argument.
    // void pack(std::ostream &out);
    // void unpack(std::istream &in);

private:
    static Table<GenericTable> registry;

    // static Table<RegistryTable> registry;
    // static Table<ITable *> table_pointers;
};

//--------------------------------------------------------------------------------

// Implementations for TableReference<T> and Reference<T>.
//--------------------------------------------------------------------------------

// TableReference<T>
//--------------------------------------------------------------------------------
template <typename T>
Reference<T> TableReference<T>::add() {
    // Get a handle to the underlying table, then combine it with a handle to this table to create a Reference<T>.
    Table<T> *table_t = Registry::get_table<T>(handle);
    if (table_t == nullptr) {
        fprintf(stderr, "[registry] ERROR: Attempted to add to table not found in the registry.\n");
        exit(EXIT_FAILURE);
    }
    TableHandle entry_handle = table_t->add();
    return Reference<T>(handle, entry_handle);
}
template <typename T>
void TableReference<T>::remove(Reference<T> ref) {
    if (ref.table != handle) {
        // There can be multiple tables in the registry for the same type.
        // This means the type system allows Reference<T>s to be passed to the wrong TableReference<T>,
        // so this error is handled here.
        fprintf(stderr, "[registry] ERROR: Attempted to remove underlying object of Reference<T> from the wrong TableReference<T> table.\n");
        exit(EXIT_FAILURE);
    }
    Table<T> *table_t = Registry::get_table<T>(handle);
    if (table_t == nullptr) {
        fprintf(stderr, "[registry] ERROR: Attempted to remove from table not found in the registry.\n");
        exit(EXIT_FAILURE);
    }
    table_t->remove(ref.handle);
}

// Reference<T>
//--------------------------------------------------------------------------------
template <typename T>
T &Reference<T>::operator*() {
    Table<T> *table_t = Registry::get_table<T>(table);
    T *t = table_t->lookup(handle);
    if (t == nullptr) {
        fprintf(stderr, "[registry] ERROR: Attempted to dereference invalid Reference.\n");
        exit(EXIT_FAILURE);
    }
    return *t;
}
template <typename T>
T *Reference<T>::operator->() {
    Table<T> *table_t = Registry::get_table<T>(table);
    T *t = table_t->lookup(handle);
    if (t == nullptr) {
        fprintf(stderr, "[registry] ERROR: Attempted to dereference invalid Reference.\n");
        exit(EXIT_FAILURE);
    }
    return t;
}

#include "/home/lucas/computer_graphics/cg_sandbox/core/registry/registry.serialize.h" /*SERIALIZE*/
#endif // REGISTRY_H
