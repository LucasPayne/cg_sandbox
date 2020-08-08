#ifndef ENTITY_MODEL_TEMPLATE_IMPLEMENTATIONS_H
#define ENTITY_MODEL_TEMPLATE_IMPLEMENTATIONS_H
//================================================================================
// Template implementations.
//================================================================================
// Entity
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE> Entity::add()
{
    TableCollectionHandle<TYPE> handle = world->em.aspect_tables.add<TYPE>();
    return Aspect<TYPE>(world, handle);
}
template <typename TYPE>
Aspect<TYPE> Entity::get()
{
    AspectType aspect_type = TYPE::type_id;
    EntityEntry *entry = get_entry();

    // Search this entity's aspects.
    TypedAspect cur = entry->first_aspect;
    while (cur.handle.id != 0) {
        if (cur.handle.type == aspect_type) {
            return Aspect<TYPE>(cur); // Convert the typed handle into a regular handle.
        }
        cur = cur->next_aspect;
    }
    fprintf(stderr, "[entity_model] ERROR: Attempted to get non-existent aspect from entity.\n");
    exit(EXIT_FAILURE);
}


// Aspect<TYPE>
//--------------------------------------------------------------------------------
template <typename TYPE>
Aspect<TYPE>::Aspect<TYPE>(WorldReference _world, TableCollectionHandle<TYPE> _handle) :
    world{_world}, handle{_handle}
{}


template <typename TYPE>
Aspect<TYPE>::Aspect<TYPE>(TypedAspect typed_aspect) :
    world{typed_aspect.world}
{
    // Assert that this conversion is valid.
    if (typed_aspect.handle.type != TYPE::type_id) {
        fprintf(stderr, "[entity_model] ASSERTION ERROR: Something went wrong. Invalid aspect handle conversion was attempted.\n");
        exit(EXIT_FAILURE);
    }
    // This conversion drops the type ID.
    handle.id = typed_aspect.handle.id;
    handle.index = typed_aspect.handle.index;
}


template <typename TYPE>
TYPE &Aspect<TYPE>::operator*()
{
    TYPE *asp = world->em.aspects.lookup<TYPE>(handle);
    if (asp == nullptr) {
        fprintf(stderr, "[entity_model] ERROR: Attempted to dereference an invalid aspect handle.\n");
        exit(EXIT_FAILURE);
    }
    return *asp;
}


template <typename TYPE>
TYPE *Aspect<TYPE>::operator->()
{
    return &(*(*this));
}


template <typename TYPE, typename SIBLING_TYPE>
Aspect<SIBLING_TYPE> Aspect<TYPE>::sibling()
{
    return entity()->get<SIBLING_TYPE>();
}


template <typename TYPE>
Entity Aspect<TYPE>::entity()
{
    // The entity reference is not stored in the handle, but in the table.
    return (*this)->entity;
}


template <typename TYPE>
void Aspect<TYPE>::destroy()
{
    //todo
}


// EntityModel
//--------------------------------------------------------------------------------
template <typename TYPE>
void register_aspect_type(const std::string &name)
{
    aspect_tables.add_type<TYPE>(name);
}


template <typename TYPE>
GenericTable::Iterator EntityModel::aspects()
{
    return aspect_tables.iterator<TYPE>();
}
#endif // ENTITY_MODEL_TEMPLATE_IMPLEMENTATIONS_H
