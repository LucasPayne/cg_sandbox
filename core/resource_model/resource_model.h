#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
/*--------------------------------------------------------------------------------
    Declarations and interface for the resource model.

BUGS:
PROBLEMS:
TO DO:
IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "data_structures/table.h"
#include "world/world_reference.h"

class ResourceModel;
typedef TableCollectionType ResourceType;
template <typename TYPE>
struct Resource; // Fully declared after ResourceModel.

template <typename T>
struct ResourceTypeStaticData {
    static ResourceType type_id;
};
// Static initialization of type information. Defaults to null values.
template <typename T> ResourceType ResourceTypeStaticData<T>::type_id(NULL_TABLE_COLLECTION_TYPE_ID);
// ResourceBase: Shared data every resource entry has.
struct ResourceBase {};
// When defining a resource type T, inherit from IResourceType<T>. In this way, static data for the resource type
// is initialized, and further non-shared struct data is defined in the body.
template <typename T>
struct IResourceType : public ResourceTypeStaticData<T>, public ResourceBase {};

class ResourceModel {
public:
    ResourceModel();
    template <typename TYPE>
    inline void register_resource_type(const std::string &name) {
        m_resource_tables.add_type<TYPE>(name);
    }
    
    // Lookup resources.
    template <typename TYPE>
    inline TYPE *try_get_resource(Resource<TYPE> handle) {
        return m_resource_tables.lookup<TYPE>(handle);
    }
    template <typename TYPE>
    inline TYPE *get_resource(Resource<TYPE> handle) {
        TYPE *found = try_get_resource<TYPE>(handle);
        if (found == nullptr) {
            std::cerr << "ERROR\n";
            exit(EXIT_FAILURE);
        }
        return found;
    }
    
    // Create new resources (which the caller will initialize).
    template <typename TYPE>
    inline Resource<TYPE> new_resource() {
        // The handle type has been extended, using the HANDLE_TYPE TableCollection template parameter.
        // This is uninitialized by the TableCollection, so make sure to initialize that extra data here.
        Resource<TYPE> handle = m_resource_tables.add<TYPE>();
        // Give the handle a pointer to the resource model.
        handle.rm = this;
        return handle;
    }

private:
    TableCollection<ResourceBase, Resource> m_resource_tables;
};

template <typename TYPE>
struct Resource {
    WorldReference world;
    TableHandle handle;
    inline TYPE &operator*() {
        TYPE *res =  world->rm.m_resource_tables.lookup<TYPE>(handle);
        if (res == nullptr) {
            fprintf(stderr, "[resource_model] ERROR, dereferenced invalid resource.\n");
            exit(EXIT_FAILURE);
        }
        return *res;
    }
    inline TYPE *operator->() {
        return &(*(*this));
    }
};

#endif // RESOURCE_MODEL_H
