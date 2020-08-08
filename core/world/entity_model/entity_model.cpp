#include "world/world.h"

// Entity
//--------------------------------------------------------------------------------
Entity::Entity(WorldReference _world, TableHandle _handle) :
    world{_world}, handle{_handle}
{}


void Entity::destroy()
{
    //todo
}


// EntityModel
//--------------------------------------------------------------------------------
EntityModel::EntityModel(WorldReference _world) :
    world{_world}
{
    // Initialize the entity model for a new world.
    const size_t entity_table_start_length = 16;
    entity_table = Table<Entity>(entity_table_start_length);
    aspect_tables = TableCollection<details::AspectBase>(1);
}


Entity EntityModel::new_entity()
{
    TableHandle handle = entity_table.add();
    Entity entity(world, handle);
    // Initialize the entry in the table.
    entity.get_entry()->first_aspect.id = 0; // Nullify the head of the aspect linked list.
    return entity;
}


GenericTable::Iterator EntityModel::entities()
{
    return entity_table.iterator();
}


// namespace details {
// TypedAspect
//--------------------------------------------------------------------------------
AspectBase &TypedAspect::operator*()
{
    AspectBase *asp_base = world->em.aspects.lookup(handle);
    if (asp == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid TypedAspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp_base;
}
AspectBase *TypedAspect::operator->()
{
    return &(*(*this));
// }


} // end namespace details
