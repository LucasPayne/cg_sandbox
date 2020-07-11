#include "core.h"
#include "entity_model/entity_model.h"

// std::vector<AspectInfo> AspectInfo::aspect_infos;
AspectInfo AspectInfo::aspect_infos[MAX_NUM_ASPECT_TYPES];

AspectType AspectInfo::new_aspect_type(AspectCreateFunction create,
                                       AspectTeardownFunction teardown,
                                       size_t size)
{
    static int num_aspect_types = 0;
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
    entity_list = new std::vector<EntityEntry>(ENTITY_LIST_START_LENGTH);
    for (int i = 0; i < ENTITY_LIST_START_LENGTH; i++) {
        entity_list[i].id = 0; // Mark each entry as null.
        entity_list[i].next_free_index = i + 1;
    }
    entity_list_first_free_index = 0;
    // This is never zero in any other case, so zero here signifies that there are no more free entries.
    entity_list[ENTITY_LIST_START_LENGTH - 1].next_free_index = 0;
}
EntityModel::~EntityModel()
{
    
}

Entity EntityModel::new_entity()
{
    static int next_entity_id = 1; // 0 is reserved for the null entity ID.
    Entity e;
    e.id = next_entity_id ++;
    // Get an index in the entity list.
    int index = entity_list_first_free_index;
    if (entity_list[index].next_free_index == 0) {
        // The entity list is full, resize it.
        size_t old_size = entity_list.size();
        entity_list.resize(old_size * 2);
        for (int i = old_size; i < old_size * 2; i++) {
            // Make sure the new entries are null.
            entity_list[i].id = 0;
        }
    }

    EntityEntry entry;
    entry.id = e.id;
    entry.num_aspects = 0;
    entity_list[index] = entry;

    return e;
}


