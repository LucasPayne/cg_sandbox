/*--------------------------------------------------------------------------------
    Entity model implementations.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "entity_model/entity_model.h"
/*--------------------------------------------------------------------------------
BUGS:
    --- Past length 8192, list resize gives a segfault.
PROBLEMS:
    --- Iteration over the aspect linked lists is too verbose.
        - Working on with iterators (could be better).
    --- Multithreading.
    --- Interaction with entity model is broken! Double buffering?
TO DO:
    --- Aspect creation and teardown.
    --- EntityModel destructor.

IDEAS/THINGS:
--------------------------------------------------------------------------------*/

//-Helper functions---------------------------------------------------------------
#include <stdarg.h>
#define DEBUG 0
// http://www.cplusplus.com/reference/cstdio/vsprintf/
// http://www.cplusplus.com/reference/cstdio/vprintf/
//--Empty inlines will still definitely have side-effect parameters evaluated.
static inline void dprint(const char *format, ...)
{
#if DEBUG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}
//--------------------------------------------------------------------------------

EntityModel::EntityModel()
{
    #define ENTITY_TABLE_START_LENGTH 16
    entity_table = EntityTable(ENTITY_TABLE_START_LENGTH);
    aspect_tables = AspectTables();
}

Entity EntityModel::new_entity()
{
    dprint("Creating new entity\n");
    return m_entity_table.add();
}

AspectEntryBase *EntityModel::new_aspect_entry(Entity entity, AspectType aspect_type, uint32_t *index_out)
{
    // Use the aspect type information and the list of aspects.
    const AspectInfo &info = AspectInfo::type_info(aspect_type);
    RuntimeAspectInfo &rt_info = runtime_aspect_infos[aspect_type];
    std::vector<uint8_t> &list = aspect_lists[aspect_type];

    //-Problem here with %s if aspect name is broken!
    dprint("Creating new aspect-%u %s entry\n", aspect_type, info.name);
    
    //-The first free index always has to be valid. Resizes are triggered when this would not
    // have any options.
    uint32_t index = rt_info.first_free_index;
    dprint("    index: %u\n", index);
    AspectEntryBase *entry = (AspectEntryBase *) &list[index * info.size];
    if (entry->next_free_index == 0) {
        // !-IMPORTANT-! After resizing, the AspectEntryBase entry pointer _must_ be recalculated.
        dprint("------------------------------------------------------------\n");
        dprint("Resizing aspect-%u list\n", aspect_type);
        //--- Code duplication here, this is the same logic as the resizing of the entity list.
        //    Some of it is different since this handles contiguous arrays of derived types.
        // This aspect list is full, resize it.
        size_t old_length = list.size() / info.size; // This not the array size in bytes, but the length when considered containing the derived type.
        list.resize(old_length * 2 * info.size);
        dprint("    %zu -> %zu\n", old_length, old_length * 2);
        dprint("------------------------------------------------------------\n");
        for (int new_index = old_length; new_index < old_length * 2; new_index ++) {
            // Make sure the new entries are null and connect to the free list.
            AspectEntryBase *new_entry = (AspectEntryBase *) &list[new_index * info.size];
            new_entry->id = 0;
            if (new_index == old_length * 2 - 1) {
                // The last new entry is the last in the free list.
                new_entry->next_free_index = 0;
            } else {
                new_entry->next_free_index = new_index + 1;
            }
        }
        // The list has been resized, the next free entry is at the start of the expanded part of the list.
        rt_info.first_free_index = old_length;
        // !-IMPORTANT-! Recalculating entry pointer here.
        entry = (AspectEntryBase *) &list[index * info.size];
    } else {
        // Update the first free index to the next available entry.
        // (!-IMPORTANT-! Do this first, since unions are used in the entry struct.)
        rt_info.first_free_index = entry->next_free_index;
    }

    // Fill in metadata.
    entry->id = rt_info.next_aspect_id ++;
    entry->entity = entity;
    //-The caller (add_aspect) will integrate this into the entity's aspect list.
    entry->next_aspect.id = 0;

    dprint("    id: %u\n", entry->id);
    dprint("    entity id: %u\n", entry->entity.id);
    dprint("    entity index: %u\n", entry->entity.index);
    
    // Give the caller the index of this new entry.
    *index_out = index;

    return entry;
}

AspectEntryBase *EntityModel::try_get_aspect_base(Aspect aspect)
{
    const AspectInfo &info = AspectInfo::type_info(aspect.type);
    const std::vector<uint8_t> &list = aspect_lists[aspect.type];

    //- Could do a bounds check here, in case the handle is corrupt.
    AspectEntryBase *entry = (AspectEntryBase *) &list[aspect.index * info.size];
    if (aspect.id != entry->id) {
        return nullptr;
    }
    return entry;
}

EntityEntry *EntityModel::get_entity_entry(Entity entity)
{
    EntityEntry *entry = &entity_list[entity.index];

    if (entity.id != entry->id) {
        // This entity doesn't exist, at least not anymore.
        fprintf(stderr, "ERROR: Attempted to lookup entity that doesn't exist.\n");
        fprintf(stderr, "    entity id: %u, entity index: %u\n", entity.id, entity.index);
        fprintf(stderr, "    entry id:  %u\n", entry->id);
        exit(EXIT_FAILURE);
    }
    return entry;
}

void EntityModel::destroy_entity(Entity entity)
{
    dprint("Destroying entity %u\n", entity.id);
    EntityEntry *entity_entry = m_entity_table.lookup(entity);
    if (entity_entry == nullptr) return; // don't do anything if the entity doesn't exist.
    // Destroy the entity's aspects.
    Aspect cur_aspect = entity_entry->first_aspect;
    AspectEntry *cur_aspect_entry = m_aspect_tables.lookup(cur_aspect);
    while (cur_aspect_entry != nullptr) {
        m_aspect_tables.remove(cur_aspect);
        cur_aspect = cur_aspect_entry->next_aspect;
        cur_aspect_entry = m_aspect_tables.lookup(cur_aspect);
    }
    // Destroy the entity.
    m_entity_table.remove(entity);
}

void EntityModel::destroy_aspect(AspectEntryBase *aspect_entry)
{
    dprint("Destroying aspect\n");
    //-This does not take a handle, so does not validate anything.
    // The aspect entry handed in must be a valid pointer to an active entry!

    // Delink this from the entity's aspect linked list.
    EntityEntry *entity_entry = get_entity_entry(aspect_entry->entity);
    if (aspect_entry->id == entity_entry->first_aspect.id) {
        // Remove from the head of the linked list.
        entity_entry->first_aspect = aspect_entry->next_aspect;
    } else {
        // It is either in the middle or at the end.
        // Find this aspect in the linked list.
        Aspect prev_handle = entity_entry->first_aspect;
        AspectEntryBase *prev = get_aspect_base(entity_entry->first_aspect);
        while (true) {
            if (prev->next_aspect.id == 0) {
                // It wasn't found on the entity, give an error. This shouldn't happen.
                fprintf(stderr, "ERROR: Attempted to remove aspect from entity which doesn't have that aspect. Is it being destroyed more than once?\n");
                exit(EXIT_FAILURE);
            }
            if (prev->next_aspect.id == aspect_entry->id) {
                // Found it.
                //-Setting the next aspect to the removed one's next aspect will
                // work whether or not this is in the middle or at the end.
                prev->next_aspect = aspect_entry->next_aspect;
                break;
            }
            prev_handle = prev->next_aspect;
            prev = get_aspect_base(prev_handle);
        }
    }
    // Nullify this entry.
    aspect_entry->id = 0;
    entity_entry->num_aspects --;

    //------- teardown stuff.
}

void EntityModel::fprint_entity(FILE *file, Entity entity)
{
    EntityEntry *entry = get_entity_entry(entity);
    fprintf(file, "printing entity at index %u\n", entity.index);
    fprintf(file, "    id: %u\n", entry->id);
    fprintf(file, "    num_aspects: %u\n", entry->num_aspects);
    if (entry->num_aspects > 0) {
        Aspect cur_handle = entry->first_aspect;
        AspectEntryBase *cur = get_aspect_base(cur_handle);
        int i = 0;
        while (true) {
            fprintf(file, "    aspect %d:\n", i);
            fprintf(file, "        type: %u\n", cur_handle.type);
            fprintf(file, "        id: %u\n", cur_handle.id);
            fprintf(file, "        index: %u\n", cur_handle.index);

            cur_handle = cur->next_aspect;
            if (cur_handle.id == 0) break;
            cur = get_aspect_base(cur_handle);
            i++;
        }
    }
}

// Debug helper functions.
void EntityModel::print_aspect_ids(AspectType aspect_type)
{
    const AspectInfo &info = AspectInfo::type_info(aspect_type);
    //----%s could be a problem if the name is buggy and invalid!
    printf("Aspect-%d %s IDs\n", aspect_type, info.name);
    const RuntimeAspectInfo &rt_info = runtime_aspect_infos[aspect_type];
    const std::vector<uint8_t> &list = aspect_lists[aspect_type];
    
    for (int index = 0; index < list.size() / info.size; index++) {
        AspectEntryBase *entry = (AspectEntryBase *) &list[index * info.size];
        printf("%d: %u\n", index, entry->id);
    }
}
void EntityModel::print_entity_ids()
{
    printf("Entity IDs\n");
    for (int i = 0; i < entity_list.size(); i++) {
        printf("%d: %u\n", i, entity_list[i].id);
    }
}


