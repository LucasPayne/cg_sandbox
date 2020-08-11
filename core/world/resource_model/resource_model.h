#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the resource model.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "data_structures/table.h"

#include "reflector/serialization.h"


typedef TableCollectionType ResourceType;

/*--------------------------------------------------------------------------------
ResourceBase
    All resources must derive from this class.
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct ResourceBase {
    // If this flag is true, then the resource data is not serialized,
    // as it will be reloaded from asset files.
    /*ENTRY*/ bool asset_backed;
};


/*--------------------------------------------------------------------------------
Resource
--------------------------------------------------------------------------------*/
class ResourceModel;

template <typename TYPE>
/*REFLECTED*/ struct Resource {
    friend class ResourceModel;
public:
    Resource() {}

    TYPE &operator*();
    TYPE *operator->();

    TableEntryID ID() const;
// private:
    Resource(ResourceModel *_rm, TableHandle _handle) :
        rm{_rm}, handle{_handle}
    {}

    ResourceModel *rm; // Not reflected, this must be recomputed on load.
    /*ENTRY*/ TableHandle handle;
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
    TableCollection<ResourceBase> resource_tables;
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

#include "/home/lucas/computer_graphics/cg_sandbox/core/world/resource_model/resource_model.serialize.h" /*SERIALIZE*/
#endif // RESOURCE_MODEL_H
