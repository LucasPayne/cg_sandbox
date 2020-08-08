#ifndef RESOURCE_MODEL_TEMPLATE_IMPLEMENTATIONS
#define RESOURCE_MODEL_TEMPLATE_IMPLEMENTATIONS
// Template implementations
//--------------------------------------------------------------------------------
/*--------------------------------------------------------------------------------
    ResourceModel
--------------------------------------------------------------------------------*/
template <typename TYPE>
void ResourceModel::register_resource_type(const std::string &name) {
    resource_tables.add_type<TYPE>(name);
}


template <typename TYPE>
Resource<TYPE> ResourceModel::new_resource() {
    TableHandle handle = resource_tables.add<TYPE>();
    return Resource<TYPE>(world, handle);
}


/*--------------------------------------------------------------------------------
    Resource<TYPE>
--------------------------------------------------------------------------------*/
template <typename TYPE>
TYPE &Resource<TYPE>::operator*() {
    TYPE *res =  world->rm.resource_tables.lookup<TYPE>(handle);
    if (res == nullptr) {
        fprintf(stderr, "[resource_model] ERROR, dereferenced invalid resource.\n");
        exit(EXIT_FAILURE);
    }
    return *res;
}


template <typename TYPE>
TYPE *Resource<TYPE>::operator->() {
    return &(*(*this));
}


template <typename TYPE>
Resource<TYPE>::Resource(WorldReference _world, TableHandle _handle) :
    world{_world}, handle{_handle}
{}


template <typename TYPE>
TableEntryID Resource<TYPE>::ID() const
{
    return handle.id;
}


#endif // RESOURCE_MODEL_TEMPLATE_IMPLEMENTATIONS
