#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the entity model.

BUGS:
PROBLEMS:
TO DO:
    --- EntityModel destructor.

IDEAS/THINGS:
    Passing null handles to e.g. get_entity is not defined!
--------------------------------------------------------------------------------*/
#include <tuple>
#include <stdio.h> //error logging
#include "data_structures/table.h"
#include "core.h"
#include "reflector/serialization.h"
#include "world/world_reference.h"

/*================================================================================
    Table data
================================================================================*/
/*--------------------------------------------------------------------------------
    Entity and aspect handles.
    These are handles that conform to the Table data structure, having
    an index and id.
--------------------------------------------------------------------------------*/

/*REFLECTED*/ struct Entity {
    WorldReference world; // Not serialized.
    /*ENTRY*/ TableHandle handle;
    Entity(WorldReference _world, TableHandle _handle) :
        world{_world}, handle{_handle}
    {}
};
typedef TableCollectionType AspectType;

template <typename TYPE>
/*REFLECTED*/ struct Aspect {
    WorldReference world; // Not serialized.
    /*ENTRY*/ TableCollectionHandle<TYPE> handle;
    inline Aspect<TYPE> &operator*() {
        Aspect<TYPE> *asp = world->em.aspects.lookup<TYPE>(handle);
        if (asp == nullptr) {
            fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid aspect handle.\n");
            exit(EXIT_FAILURE);
        }
        return *asp;
    }
    inline Aspect<TYPE> *operator->() {
        return &(*(*this));
    }
};
/*REFLECTED*/ struct TypedAspect {
    WorldReference world; // Not serialized.
    /*ENTRY*/ TypedTableCollectionHandle handle;
    inline AspectBase &operator*() {
        AspectBase *asp_base = world->em.aspects.lookup(handle);
        if (asp == nullptr) {
            fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid aspect handle.\n");
            exit(EXIT_FAILURE);
        }
        return *asp_base;
    }
    inline AspectBase *operator->() {
        return &(*(*this));
    }
};

/*--------------------------------------------------------------------------------
    Entity and aspect table entries.
--------------------------------------------------------------------------------*/
// An entry in the entity table.
/*REFLECTED*/ struct EntityEntry {
    // The entity has a linked list of its aspects,
    // which can be traversed from an aspect by using its entity handle to look up
    // its first aspect, and then following the next aspects.
    /*ENTRY*/ TypedAspect first_aspect;
};

template <typename T>
struct AspectTypeStaticData {
    static AspectType type_id;
};
template <typename T> AspectType AspectTypeStaticData<T>::type_id
    (NULL_TABLE_COLLECTION_TYPE_ID);
// The base class of aspects in an aspect table.
// The AspectBase:: namespace also serves as the location of static type data -- the type_id,
// which templated methods need so they can get the relevant table from their type template-parameter.

/*REFLECTED*/ struct AspectBase {
    /*ENTRY*/ Entity entity;
    /*ENTRY*/ TypedAspect next_aspect;
};
// When defining an aspect type T, inherit from IAspectType<T>. In this way, static data for the aspect type is initialized,
// and the actual aspect-instance data struct is defined in the body.
template <typename T>
/*REFLECTED*/ struct IAspectType : AspectTypeStaticData<T>, public AspectBase {
};


/*REFLECTED*/ class EntityModel {
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
    //-begin iterator hack------------------------------------------------------------
    //    This is all just for overriding the dereference operator to match the syntax.
    //   -There really should just be two options for iterating a GenericTable, handle iterator and pointer iterator.
    template <typename TYPE>
    struct AspectIterator {
        struct AspectIteratorPosition {
            GenericTable::IteratorPosition pos;
            TableCollection<AspectBase> *aspect_table;
            inline void operator++() { ++pos; }
            inline TYPE *operator*() { return aspect_table->lookup<TYPE>(*pos); }
            inline bool operator!=(AspectIteratorPosition throwaway) { return pos != GenericTable::IteratorPosition(); }
            AspectIteratorPosition() {}
            AspectIteratorPosition(GenericTable::IteratorPosition _pos, TableCollection<AspectBase> *_aspect_table) :
                pos{_pos}, aspect_table{_aspect_table}
            {}
        };
        inline AspectIteratorPosition begin() {
            return AspectIteratorPosition(iter.begin(), aspect_table);
        }
        inline AspectIteratorPosition end() { return AspectIteratorPosition(); }

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
    //-end iterator hack--------------------------------------------------------------

    // Creation and destruction of aspects.
    template <typename TYPE>
    void destroy_aspect(Aspect<TYPE> aspect) {

        // Delink from entity linked list.
        AspectBase &entry = *aspect; // This gives an error if the aspect does not exist.

        // First, retrieve the entity.
        EntityEntry &entity_entry = *(entry.entity);

        // If this aspect is at the head of the list, remove it.
        if (entity_entry.first_aspect.type == TYPE::type_id && entity_entry.first_aspect.id == aspect.handle.id) {
            // Found the aspect. Removed from head.
            entity_entry.first_aspect = entry.next_aspect;
	    m_aspect_tables.remove<TYPE>(aspect.handle);
            return;
        } else {
            // Otherwise, find it then delink it.
            // AspectBase &prev_aspect = m_aspect_tables.lookup(entity->first_aspect);
            AspectBase &prev_aspect = *(entity_entry.first_aspect);
            TypedAspect cur_aspect_handle = prev_aspect->next_aspect;
            AspectBase *cur_aspect = m_aspect_tables.lookup(cur_aspect_handle);
            while (cur_aspect != nullptr) {
                if (cur_aspect_handle.type == TYPE::type_id && cur_aspect_handle.id == aspect_handle.id) {
                    // Found the aspect. Removed from middle or end.
                    prev_aspect->next_aspect = cur_aspect->next_aspect;
                    m_aspect_tables.remove<TYPE>(aspect_handle);
                    return;
                }
                prev_aspect = cur_aspect;
                cur_aspect_handle = cur_aspect->next_aspect;
                cur_aspect = m_aspect_tables.lookup(cur_aspect_handle);
            }
        }
        fprintf(stderr, "ERROR: This shouldn't happen.\n");
        exit(EXIT_FAILURE);
    }
    // This destroy_aspect searches for an aspect of the given type attached to the entity and destroys it.
    // template <typename TYPE>
    // void destroy_aspect(Entity entity_handle) {
    //     AspectBase *try_get_aspect
    // }

    template <typename TYPE>
    TYPE *add_aspect(Entity entity_handle) {
        EntityEntry *entity = get_entity(entity_handle); // Fail if the entity doesn't exist.
        Aspect<TYPE> new_aspect_handle = m_aspect_tables.add<TYPE>();
        TYPE *new_aspect = m_aspect_tables.lookup<TYPE>(new_aspect_handle);

        // Store the entity handle in the aspect entry.
        new_aspect->entity = entity_handle;

        // Link this aspect to the head of the entity's aspect linked list.
        TypedAspect prev_head_handle = entity->first_aspect;
        entity->first_aspect = m_aspect_tables.typed_handle<TYPE>(new_aspect_handle);
        new_aspect->next_aspect = prev_head_handle;
        
        return new_aspect;
    }

    // Retrieve sibling aspects. A sibling aspect is the first occurence of an aspect of a certain type
    // attached to the same entity.
    template <typename TYPE>
    inline TYPE *try_get_sibling(AspectBase *aspect) {
        return try_get_aspect<TYPE>(aspect->entity);
    }
    template <typename TYPE>
    inline TYPE *get_sibling(AspectBase *aspect) {
        TYPE *sibling = try_get_sibling<TYPE>(aspect);
        if (sibling == nullptr) {
            // error
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        return sibling;
    }

//-debugging
//private:
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

    /*ENTRY*/ Table<EntityEntry> m_entity_table;
    /*ENTRY*/ TableCollection<AspectBase> m_aspect_tables;
    WorldReference world; // Not serialized.
};

#include "/home/lucas/computer_graphics/cg_sandbox/core/entity_model/entity_model.serialize.h" /*SERIALIZE*/
#endif // ENTITY_MODEL_H
