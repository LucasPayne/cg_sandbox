#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the entity model.

BUGS:
PROBLEMS:
TO DO:
    --- EntityModel destructor.

IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include <tuple>
#include <stdio.h> //error logging
#include "data_structures/table.h"
#include "core.h"

/*================================================================================
    Table data
================================================================================*/
/*--------------------------------------------------------------------------------
    Entity and aspect handles.
    These are handles that conform to the Table data structure, having
    an index and id.
--------------------------------------------------------------------------------*/
typedef TableHandle Entity;
typedef TableCollectionType AspectType;
template <typename TYPE>
using Aspect = TableCollectionHandle<TYPE>;
typedef TypedTableCollectionHandle TypedAspect;

/*--------------------------------------------------------------------------------
    Entity and aspect table entries.
--------------------------------------------------------------------------------*/
// An entry in the entity table.
struct EntityEntry {
    // The entity has a linked list of its aspects,
    // which can be traversed from an aspect by using its entity handle to look up
    // its first aspect, and then following the next aspects.
    TypedAspect first_aspect;
};

struct AspectTypeStaticData {
    static AspectType type_id;
};
// The base class of aspects in an aspect table.
// The AspectBase:: namespace also serves as the location of static type data -- the type_id,
// which templated methods need so they can get the relevant table from their type template-parameter.
struct AspectBase : public AspectTypeStaticData {
    Entity entity;
    TypedAspect next_aspect;
};


class EntityModel {
public: // Usage interface
    EntityModel();

    // Registration of aspect types. Aspect types cannot be unregistered.
    template <typename TYPE>
    void register_aspect_type(const std::string &name) {
        m_aspect_tables.add_type<TYPE>(name);
    }

    // Creation and destruction of entities.
    Entity new_entity();
    void destroy_entity(Entity entity);

    // Iterators. Iterate over entities, or aspects of a certain type.
    inline GenericTable::Iterator entities() {
        return m_entity_table.iterator();
    }

    template <typename TYPE>
    struct AspectIterator {
        struct AspectIteratorPosition {
            GenericTable::IteratorPosition pos;
            TableCollection<AspectBase> *aspect_table;
            inline void operator++() { ++pos; }
            inline TYPE *operator*() { return aspect_table->lookup<TYPE>(*pos); }
            inline bool operator!=(int throwaway) { return pos != 0; }
            AspectIteratorPosition(GenericTable::IteratorPosition _pos, TableCollection<AspectBase> *_aspect_table) :
                pos{_pos}, aspect_table{_aspect_table}
            {}
        };
        inline AspectIteratorPosition begin() {
            return AspectIteratorPosition(iter.begin(), aspect_table);
        }
        inline int end() { return 0; }

        GenericTable::Iterator iter;
        TableCollection<AspectBase> *aspect_table;
        AspectIterator(GenericTable::Iterator _iter, TableCollection<AspectBase> *_aspect_table) :
            iter{_iter}, aspect_table{_aspect_table}
        {}
    };
    template <typename TYPE>
    inline AspectIterator<TYPE> aspects() {
        return AspectIterator<TYPE>(m_aspect_tables.iterator<TYPE>(), &m_aspect_tables);
    }

    // Creation and destruction of aspects.
    template <typename TYPE>
    void destroy_aspect(Aspect<TYPE> aspect) {
        //-todo: Delink from entity linked list.
        m_aspect_tables.remove<TYPE>(aspect);
    }
    template <typename TYPE>
    TYPE *add_aspect(Entity entity_handle) {
        Aspect<TYPE> new_aspect_handle = m_aspect_tables.add<TYPE>();
        TYPE *new_aspect = m_aspect_tables.lookup<TYPE>(new_aspect_handle);
        EntityEntry *entity = try_get_entity(entity_handle);

        // Link this aspect to the head of the entity's aspect linked list.
        TypedAspect prev_head_handle = entity->first_aspect;
        entity->first_aspect = m_aspect_tables.typed_handle<TYPE>(new_aspect_handle);
        new_aspect->next_aspect = prev_head_handle;
        
        return new_aspect;
    }
    template <typename TYPE>
    TYPE *try_get_aspect(Entity entity_handle) {
        // Search the entity's aspect linked list for an aspect of the given type.
        EntityEntry *entity = m_entity_table.lookup(entity_handle);

        TypedAspect cur_aspect_handle = entity->first_aspect;
        AspectBase *cur_aspect = m_aspect_tables.lookup(entity->first_aspect);
        while (cur_aspect != nullptr) {
            if (cur_aspect_handle.type == TYPE::type_id) {
                return reinterpret_cast<TYPE *>(cur_aspect);
            }
            cur_aspect_handle = cur_aspect->next_aspect;
            cur_aspect = m_aspect_tables.lookup(cur_aspect_handle);
        }
        return nullptr;
    }
    template <typename TYPE>
    TYPE *get_aspect(Entity entity) {
        TYPE *aspect = try_get_aspect<TYPE>(entity);
        if (aspect == nullptr) {
            // error
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        return aspect;
    }

/*
    template <typename TYPE>
    TYPE *try_get_sibling(TableHandle aspect_handle) const {
        
    }
    template <typename TYPE>
    inline TYPE *get_sibling(TableHandle aspect_handle) const {
        TYPE *sibling = try_get_sibling(aspect_handle);
        if (sibling == nullptr) {
            // error
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        return sibling;
    }
*/

private:
    EntityEntry *try_get_entity(Entity entity_handle) {
        // This is private, since only the implementation will know what an "EntityEntry" is.
        return m_entity_table.lookup(entity_handle);
    }
    inline EntityEntry *get_entity(Entity entity_handle) {
        EntityEntry *entity = try_get_entity(entity_handle);
        if (entity == nullptr) {
            // error
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        return entity;
    }

    Table<EntityEntry> m_entity_table;
    TableCollection<AspectBase> m_aspect_tables;
};


#endif // ENTITY_MODEL_H
