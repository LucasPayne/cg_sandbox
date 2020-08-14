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
    entity_table{Table(TypeHandle(Reflector::get_descriptor<EntityEntry>()), 16)},
    aspect_tables{TableCollection(16)}
{}



Entity Entities::add()
{
    return Entity(this, entity_table.add<EntityEntry>());
}
EntityEntry *Entities::get_entry(Entity entity)
{
    return reinterpret_cast<EntityEntry *>(entity_table[entity.table_element]);
}



IAspectType *GenericAspect::metadata()
{
    return reinterpret_cast<IAspectType *>(entities->aspect_tables[table_collection_element]);
}


AspectIterator Entity::begin()
{
    return AspectIterator(entities->get_entry(*this)->first_aspect);
}

AspectIterator &AspectIterator::operator++()
{
    aspect = aspect.metadata()->next_aspect;
    return *this;
}

AspectIterator Entity::end()
{
    return AspectIterator(GenericAspect());
}

