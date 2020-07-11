#include "core.h"
#include "entity_model/entity_model.h"

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

// std::vector<AspectInfo> AspectInfo::aspect_infos;
AspectInfo AspectInfo::aspect_infos[MAX_NUM_ASPECT_TYPES];
// Aspect types (should) only be registered at static initialization, fixed at compile time.
// So, this can be used to e.g. create arrays of aspects for each aspect type, indexed by the type.
int AspectInfo::num_aspect_types = 0;
AspectType AspectInfo::new_aspect_type(AspectCreateFunction create,
                                       AspectTeardownFunction teardown,
                                       size_t size)
{
    if (num_aspect_types + 1 >  MAX_NUM_ASPECT_TYPES) {
        std::cerr << "ERROR: Too many aspect types.\n";
        exit(EXIT_FAILURE);
    }

    AspectInfo &info = aspect_infos[num_aspect_types];
    info.size = size;
    info.create = create;
    info.teardown = teardown;

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

    // Initialize the aspect lists. The aspect types should by now be constant, none being added at (non static-initialization)
    // runtime.
    aspect_lists = std::vector<std::vector<uint8_t>>(AspectInfo::num_aspect_types);
    for (int i = 0; i < AspectInfo::num_aspect_types; i++) {
        const AspectInfo &info = AspectInfo::type_info(i);
        aspect_lists[i] = std::vector<uint8_t>(info.size * ASPECT_LIST_START_LENGTH, 0);
        std::vector<uint8_t> &list = aspect_lists[i];
        // Initialize this aspect list, connecting a free list in the same way done for the entity list.
        
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
        // The next free entry is now the first.
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


