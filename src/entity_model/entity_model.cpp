#include "core.h"
#include "entity_model/entity_model.h"
/*--------------------------------------------------------------------------------
BUGS:
    --- Past length 8192, list resize gives a segfault.
PROBLEMS:
    --- Iteration over the aspect linked lists is too verbose.
    --- Multithreading.
    --- Interaction with entity model is broken! Double buffering?
TO DO:
    --- Aspect creation and teardown.
    --- EntityModel destructor.
    --- More efficient entity destruction.
    --- try_get_aspect, try_get_entity kind of stuff.
    --- Getting sibling aspects.
--------------------------------------------------------------------------------*/

#include <stdarg.h>
#define DEBUG 1
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

AspectInfo AspectInfo::aspect_infos[MAX_NUM_ASPECT_TYPES];
// Aspect types (should) only be registered at static initialization, fixed at compile time.
// So, this can be used to e.g. create arrays of aspects for each aspect type, indexed by the type.
int AspectInfo::num_aspect_types = 0;
AspectType AspectInfo::new_aspect_type(char *name, size_t size)
{
    if (num_aspect_types + 1 >  MAX_NUM_ASPECT_TYPES) {
        std::cerr << "ERROR: Too many aspect types.\n";
        exit(EXIT_FAILURE);
    }

    AspectInfo &info = aspect_infos[num_aspect_types];
    info.name = name;
    info.size = size;

    return num_aspect_types ++;
}
AspectInfo AspectInfo::type_info(AspectType type)
{
    return aspect_infos[type];
}

EntityModel::EntityModel()
{
    //---The entity list uses a data structure that uses a std::vector for the storage. This should
    //   be a separate implementation.

    // Place the entity list on the heap somewhere.
    entity_list = std::vector<EntityEntry>(ENTITY_LIST_START_LENGTH);
    for (int i = 0; i < ENTITY_LIST_START_LENGTH; i++) {
        entity_list[i].id = 0; // Mark each entry as null.
        entity_list[i].next_free_index = i + 1;
    }
    entity_list_first_free_index = 0;
    // This is never zero in any other case, so zero here signifies that there are no more free entries.
    entity_list[ENTITY_LIST_START_LENGTH - 1].next_free_index = 0;

    //-The aspect types should by now be constant, none being added at (non static-initialization) runtime.
    // Initialize the runtime aspect type metadata.
    runtime_aspect_infos = std::vector<RuntimeAspectInfo>(AspectInfo::num_aspect_types);
    for (RuntimeAspectInfo &rt_info : runtime_aspect_infos) {
        rt_info.next_aspect_id = 1;
        rt_info.first_free_index = 0;
    }
    
    // Initialize the aspect lists.
    aspect_lists = std::vector<std::vector<uint8_t>>(AspectInfo::num_aspect_types);
    for (int i = 0; i < AspectInfo::num_aspect_types; i++) {
        const AspectInfo &info = AspectInfo::type_info(i);
        aspect_lists[i] = std::vector<uint8_t>(info.size * ASPECT_LIST_START_LENGTH, 0);
        std::vector<uint8_t> &list = aspect_lists[i];
        // Initialize this aspect list, connecting a free list in the same way done for the entity list.
        for (int entry_index = 0; entry_index < ASPECT_LIST_START_LENGTH; entry_index ++) {
            // This is a contiguous array of derived types, so iterate over the full entries and cast
            // them to the AspectEntryBase class, so common metadata can be filled.
            AspectEntryBase *entry = (AspectEntryBase *) &list[entry_index * info.size];
            entry->id = 0;
            if (entry_index == ASPECT_LIST_START_LENGTH - 1) {
                // The last free entry has next_free_index zero, meaning there are no more free entries.
                entry->next_free_index = 0;
            } else {
                entry->next_free_index = entry_index + 1;
            }
        }
    }
}
EntityModel::~EntityModel()
{
    
}

Entity EntityModel::new_entity()
{
    dprint("Creating new entity\n");

    // Get an index in the entity list.
    int index = entity_list_first_free_index;
    if (entity_list[index].next_free_index == 0) {
        dprint("Resizing entity list\n");
        // The entity list is full, resize it.
        size_t old_size = entity_list.size();
        entity_list.resize(old_size * 2);
        for (int i = old_size; i < old_size * 2; i++) {
            // Make sure the new entries are null and connect to the free list.
            entity_list[i].id = 0;
            entity_list[i].next_free_index = i + 1;
        }
        // The last new entry is the last in the free list.
        entity_list[entity_list.size() - 1].next_free_index = 0;
        // The list has been resized, the next free entry is at the start of the expanded part of the list.
        entity_list_first_free_index = old_size;
        dprint("    %zu -> %zu\n", old_size, entity_list.size());
    } else {
        // Update the first free index to the next available entry.
        entity_list_first_free_index = entity_list[index].next_free_index;
    }

    static int next_entity_id = 1; // 0 is reserved for the null entity ID.

    // Create the Entity handle that will be returned.
    Entity e;
    e.id = next_entity_id ++;
    e.index = index;
    dprint("    id: %u\n", e.id);
    dprint("    index: %u\n", e.index);

    // Fill the entry in the entity list.
    EntityEntry entry;
    entry.id = e.id;
    entry.num_aspects = 0;
    entity_list[index] = entry;

    return e;
}

AspectEntryBase *EntityModel::new_aspect_entry(Entity entity, AspectType aspect_type, uint32_t *index_out)
{
    dprint("Creating new aspect-%u entry\n", aspect_type);

    // Use the aspect type information and the list of aspects.
    const AspectInfo &info = AspectInfo::type_info(aspect_type);
    RuntimeAspectInfo &rt_info = runtime_aspect_infos[aspect_type];
    std::vector<uint8_t> &list = aspect_lists[aspect_type];
    
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

AspectEntryBase *EntityModel::get_aspect_base(Aspect aspect)
{
    const AspectInfo &info = AspectInfo::type_info(aspect.type);
    const std::vector<uint8_t> &list = aspect_lists[aspect.type];

    //- Could do a bounds check here, in case the handle is corrupt.
    AspectEntryBase *entry = (AspectEntryBase *) &list[aspect.index * info.size];
    if (aspect.id != entry->id) {
        // This aspect doesn't exist, at least not anymore.
        fprintf(stderr, "ERROR: Attempted to lookup aspect that doesn't exist.\n");
        fprintf(stderr, "    aspect id: %u, aspect index: %u, aspect type: %u\n", aspect.id, aspect.index, aspect.type);
        fprintf(stderr, "    entry id:  %u\n", entry->id);
        print_aspect_ids(aspect.type);
        exit(EXIT_FAILURE);
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
    EntityEntry *entry = get_entity_entry(entity);
    // Destroy all its aspects.
    //---Probably destroying all the aspects at once should be cheaper, since
    //   the linked list doesn't need to be maintained.
    if (entry->num_aspects > 0) {
        AspectEntryBase *destroy_this = get_aspect_base(entry->first_aspect);
        while (true) {
            Aspect destroy_this_next_handle = destroy_this->next_aspect;
            AspectEntryBase *destroy_this_next = get_aspect_base(destroy_this_next_handle);
            destroy_aspect(destroy_this);
            if (destroy_this_next_handle.id == 0) break;
            destroy_this = destroy_this_next;
        }
    }

    // Nullify this entry.
    entry->id = 0;
    // Link this space back into the free list.
    uint32_t prev_free_index = entity_list_first_free_index;
    entity_list_first_free_index = entity.index;
    entry->next_free_index = prev_free_index;
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
    //----could be a problem if the name is buggy and invalid!
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


