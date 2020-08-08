#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the resource model.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "data_structures/table.h"


typedef TableCollectionType ResourceType;


/*--------------------------------------------------------------------------------
Resource
--------------------------------------------------------------------------------*/
class ResourceModel;
template <typename TYPE>
struct Resource {
    friend class ResourceModel;
public:
    Resource() {}

    TYPE &operator*();
    TYPE *operator->();

    TableEntryID ID() const;
private:
    Resource(ResourceModel *_rm, TableHandle _handle) :
        rm{_rm}, handle{_handle}
    {}

    ResourceModel *rm;
    TableHandle handle;
};


/*--------------------------------------------------------------------------------
ResourceModel
--------------------------------------------------------------------------------*/
class ResourceModel {
    template <typename TYPE> friend class Resource;
public:
    ResourceModel();

    template <typename TYPE>
    void register_resource_type(const std::string &name);
    
    template <typename TYPE>
    Resource<TYPE> new_resource();
private:
    TableCollection<> resource_tables;
};




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
    return Resource<TYPE>(this, handle);
}


/*--------------------------------------------------------------------------------
    Resource<TYPE>
--------------------------------------------------------------------------------*/
template <typename TYPE>
TYPE &Resource<TYPE>::operator*() {
    TYPE *res =  rm->resource_tables.lookup<TYPE>(handle);
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
TableEntryID Resource<TYPE>::ID() const
{
    return handle.id;
}


#endif // RESOURCE_MODEL_H
