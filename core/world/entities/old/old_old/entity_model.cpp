/*--------------------------------------------------------------------------------
    Entity model implementations.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "entity_model/entity_model.h"
#include "entity_model/entity_model.serialize.cpp"

EntityModel::EntityModel()
{
    #define ENTITY_TABLE_START_LENGTH 16
    m_entity_table = Table<EntityEntry>(ENTITY_TABLE_START_LENGTH);
    m_aspect_tables = TableCollection<AspectBase>();
}

Entity EntityModel::new_entity()
{
    TableHandle handle = m_entity_table.add();
    Entity entity(world, handle);

    EntityEntry *entity = get_entity(handle);
    entity->first_aspect.id = 0; // Nullify the head of the aspect linked list.
    return handle;
}
void EntityModel::destroy_entity(Entity entity_handle)
{
    EntityEntry *entity = m_entity_table.lookup(entity_handle);
    if (entity == nullptr) return; // Do nothing if the entity does not exist.

    // Destroy the entity's aspects.
    TypedAspect cur_aspect_handle = entity->first_aspect;
    AspectBase *cur_aspect = m_aspect_tables.lookup(cur_aspect_handle);
    while (cur_aspect != nullptr) {
        TypedAspect next_aspect = cur_aspect->next_aspect;
        // Destroy the aspect.
        m_aspect_tables.remove(cur_aspect_handle);
        // ---teardown here, once that is a thing.

        cur_aspect_handle = next_aspect;
        cur_aspect = m_aspect_tables.lookup(cur_aspect_handle);
    }

    m_entity_table.remove(entity_handle);
}

