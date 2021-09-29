#include "world/entity_system/entity_system.h"


Entities::Entities() :
    entity_table{Table(TypeHandle(Reflector::get_descriptor<EntityEntry>()), 16)},
    aspect_tables{TableCollection(16)}
{}


DESCRIPTOR_INSTANCE(EntityEntry);
BEGIN_ENTRIES(EntityEntry)
    //...not reflected
END_ENTRIES()



Entity Entities::add()
{
    return Entity(this, entity_table.add<EntityEntry>());
}
EntityEntry *Entities::get_entry(Entity entity)
{
    return reinterpret_cast<EntityEntry *>(entity_table[entity.table_element]);
}

void Entity::destroy()
{
    //--------------------------------------------------------------------------------
    // TODO
    //--------------------------------------------------------------------------------
    // for (auto aspect : aspects()) {
    //     aspect.destroy();
    // }
    entities->entity_table.remove(table_element);
}



IAspectType *GenericAspect::metadata()
{
    return reinterpret_cast<IAspectType *>(get_data());
}


AspectIterator Entity::begin()
{
    auto first_aspect = entities->get_entry(*this)->first_aspect;
    return AspectIterator(first_aspect);;
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


TypeHandle &GenericAspect::type() const {
    return entities->aspect_tables.type_of(table_collection_element);
}


uint8_t *GenericAspect::get_data()
{
    return entities->aspect_tables[table_collection_element];
}

int Entity::num_aspects()
{
    int n = 0;
    for ([[maybe_unused]] auto &a : *this) {
        n++;
    }
    return n;
}


GenericAspect Entity::add(TypeHandle type)
{
    auto aspect = GenericAspect(entities, entities->aspect_tables.add(type));
    init_added(aspect);
    return aspect;
}


void Entity::init_added(GenericAspect aspect)
{
    // Add the aspect to the entity's linked list.
    EntityEntry *entry = entities->get_entry(*this);
    if (entry->first_aspect == GenericAspect()) {
        // Add at the head.
        entry->first_aspect = aspect;
    } else {
        // Add to the end.
        GenericAspect last = entry->first_aspect;
        for (auto a : *this) {
            last = a;
        }
        last.metadata()->next_aspect = aspect;
    }
    aspect.metadata()->entity = *this; // Give the aspect a handle to this entity.
}

Entity GenericAspect::entity() {
    return metadata()->entity;
}
