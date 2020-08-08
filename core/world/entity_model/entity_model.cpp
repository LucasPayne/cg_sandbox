#include "world/entity_model/entity_model.h"


// Entity
//--------------------------------------------------------------------------------
void Entity::destroy()
{
    //todo
}


TableEntryID Entity::ID() const
{
    return handle.id;
}


// EntityModel
//--------------------------------------------------------------------------------
EntityModel::EntityModel()
{
    // Initialize the entity model.
    const size_t entity_table_start_length = 16;
    entity_table = Table<EntityEntry>(entity_table_start_length);
    aspect_tables = TableCollection<AspectBase>();
}


Entity EntityModel::new_entity()
{
    TableHandle handle = entity_table.add();
    Entity entity(this, handle);
    // Initialize the entry in the table.
    EntityEntry *entry = entity_table.lookup(handle);
    entry->first_aspect.handle.id = 0; // Nullify the head of the aspect linked list.
    return entity;
}


GenericTable::Iterator<Entity> EntityModel::entities()
{
    return entity_table.iterator<Entity>(
        [this](TableHandle handle)->Entity {
            return Entity(this, handle);
        }
    );
}


// namespace details {
// TypedAspect
//--------------------------------------------------------------------------------
AspectBase &TypedAspect::operator*()
{
    AspectBase *asp_base = em->aspect_tables.lookup(handle);
    if (asp_base == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid TypedAspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp_base;
}


AspectBase *TypedAspect::operator->()
{
    return &(*(*this));
}


// } // end namespace details