/*--------------------------------------------------------------------------------
    Entity model implementations.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "entity_model/entity_model.h"

EntityModel::EntityModel()
{
    #define ENTITY_TABLE_START_LENGTH 16
    m_entity_table = Table<EntityEntry>(ENTITY_TABLE_START_LENGTH);
    m_aspect_tables = TableCollection<AspectBase>();
}

Entity EntityModel::new_entity()
{
    Entity handle = m_entity_table.add();
    EntityEntry *entity = get_entity(handle);
    entity->first_aspect.id = 0; // Nullify the head of the aspect linked list.
    return handle;
}
void EntityModel::destroy_entity(Entity entity)
{
    m_entity_table.remove(entity);
}

