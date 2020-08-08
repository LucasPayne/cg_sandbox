#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the resource model.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "data_structures/table.h"
#include "world/world_reference.h"


typedef TableCollectionType ResourceType;
template <typename T>
struct ResourceTypeStaticData {
    static ResourceType type_id;
};
// Statically initialize the global variable containing the type ID.
template <typename T>
ResourceType ResourceTypeStaticData<T>::type_id(NULL_TABLE_COLLECTION_TYPE_ID);


/*--------------------------------------------------------------------------------
ResourceBase
    Shared data every resource entry has.
    Currently this is nothing.
--------------------------------------------------------------------------------*/
struct ResourceBase {};


/*--------------------------------------------------------------------------------
IResourceType<T>
    When defining a resource type T, inherit from IResourceType<T>. In this way, static data for the resource type
    is initialized, and further non-shared struct data is defined in the body.
--------------------------------------------------------------------------------*/
template <typename T>
struct IResourceType : public ResourceTypeStaticData<T>, public ResourceBase {};


/*--------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
template <typename TYPE>
struct Resource {
    friend class ResourceModel;
public:
    Resource() {}

    TYPE &operator*();
    TYPE *operator->();

    TableEntryID ID() const;
private:
    Resource(WorldReference _world, TableHandle _handle);

    WorldReference world;
    TableHandle handle;
};


/*--------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
class ResourceModel {
    template <typename TYPE> friend class Resource;
public:
    ResourceModel(WorldReference _world);
    ResourceModel() {}

    template <typename TYPE>
    void register_resource_type(const std::string &name);
    
    template <typename TYPE>
    Resource<TYPE> new_resource();
private:
    WorldReference world;
    TableCollection<ResourceBase> resource_tables;
};

#endif // RESOURCE_MODEL_H
