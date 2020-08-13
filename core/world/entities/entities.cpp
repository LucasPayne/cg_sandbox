#include "world/entities/entities.h"



DESCRIPTOR_INSTANCE(GenericAspect);
BEGIN_ENTRIES(GenericAspect)
    ENTRY(table_collection_element)
END_ENTRIES()


DESCRIPTOR_INSTANCE(Entities);
BEGIN_ENTRIES(Entities)
    ENTRY(entity_table)
    ENTRY(aspect_tables)
END_ENTRIES()


DESCRIPTOR_INSTANCE(EntityEntry);
BEGIN_ENTRIES(EntityEntry)
    ENTRY(first_aspect)
END_ENTRIES()


Entities::Entities() :
    entity_table{Table(TypeHandle(Reflector::get_descriptor<EntityEntry>()), 16)}
{}



Entity Entities::add()
{
    return Entity(this, entity_table.add());
}
EntityEntry *Entities::get_entry(Entity entity)
{
    return reinterpret_cast<EntityEntry *>(entity_table[entity.table_element]);
}
