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

class ResourceModel;
typedef TableCollectionType ResourceType;
template <typename TYPE>
struct Resource; // Fully declared after ResourceModel.

typedef bool (*ResourceLoadFunction)(void *data, std::istream &stream);
typedef bool (*ResourceUnloadFunction)(void *data);

template <typename T>
struct ResourceTypeStaticData {
    static ResourceType type_id;
    static ResourceLoadFunction load_function;
    static ResourceUnloadFunction unload_function;
};
// Static initialization of type information. Defaults to null values.
template <typename T> ResourceType ResourceTypeStaticData<T>::type_id(NULL_TABLE_COLLECTION_TYPE_ID);
template <typename T> ResourceLoadFunction ResourceTypeStaticData<T>::load_function(nullptr);
template <typename T> ResourceUnloadFunction ResourceTypeStaticData<T>::unload_function(nullptr);
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
    inline void register_resource_type(const std::string &name,
                                       ResourceLoadFunction load_function,
                                       ResourceUnloadFunction unload_function) {
        m_resource_tables.add_type<TYPE>(name);
        TYPE::load_function = load_function;
        TYPE::unload_function = unload_function;
    }
    
    template <typename TYPE>
    Resource<TYPE> load_from_file(const std::string &filename) {
        //todo: caching

        Resource<TYPE> handle = new_resource<TYPE>();
        TYPE *data = m_resource_tables.lookup<TYPE>(handle);

        std::ifstream file;
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "ERROR: Attempted to load resource from file \"" << filename << "\", which does not exist.\n";
            exit(EXIT_FAILURE);
        }
        bool success = TYPE::load_function(data, file);
        if (!success) {
            std::cerr << "ERROR: Failed to load resource from file \"" << filename << "\".\n";
            exit(EXIT_FAILURE);
        }
        return handle;
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
struct Resource : TableCollectionHandle<TYPE> {
    // The resource model is passed as a pointer to each handle. This allows, without introducing a singleton resource model,
    // for a dereference operator to get a pointer to the actual data. I think this is convenient enough for the handle-size overhead.
    ResourceModel *rm;

    // Dereference operator. Returns a reference to the actual data.
    inline TYPE &operator*() {
        return *(rm->get_resource<TYPE>(*this));
    }
    inline TYPE *operator->() {
        return rm->get_resource<TYPE>(*this);
    }
};


#endif // RESOURCE_MODEL_H
