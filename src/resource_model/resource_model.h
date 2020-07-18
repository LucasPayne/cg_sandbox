#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
#include "core.h"
typedef uint8_t ResourceType;
#define MAX_NUM_RESOURCE_TYPES 255 //-1 == 255 is reserved for the null resource type.
typedef uint32_t ResourceID;

template <typename TYPE>
struct Resource {
public:
    friend ResourceModel;
    TYPE *operator*() {
        if (m_readonly) {
            // error
        }
        //...
    }
    Resource<TYPE> fork() const {
        // Duplicate the resource. If the resource data has dependencies, this is handled.
        // For example, if a resource is backed by an asset, the new resource is not, it duplicates
        // all data (requiring a deep copy).
    }
    ResourceType type() const { return m_type; }
    ResourceID id() const { return m_id; }
private:
    bool m_readonly;
    ResourceType m_type;
    ResourceID m_id;
    uint32_t m_index;
};

struct AspectEntryBase {
    uint32_t id;
    union {
        Entity entity;
        // If id == 0, this stores the index of the free entry after this.
        uint32_t next_free_index;
    };
    // The entity has a linked list of its aspects,
    // which can be traversed from an aspect by using its entity handle to look up
    // its first aspect, and then following the next aspects.
    Aspect next_aspect;
};
template<typename T>
struct AspectEntry : public AspectEntryBase
{
    static const AspectType type;
    static const size_t size;
};
// Static initialization of run-time type information.
template<typename T>
const AspectType AspectEntry<T>::type(AspectInfo::new_aspect_type(
    T::name,
    sizeof(T)
));

struct ResourceEntry {
    ResourceID id;
};
template <typename TYPE>
struct ResourceTypeStaticData : public ResourceEntry {
    static const ResourceType type;
    static const size_t size;
};
template<typename TYPE>
const ResourceType ResourceTypeStaticData<TYPE>::type(AspectInfo::new_aspect_type(
    T::name,
    sizeof(T)
));
struct ResourceTypeInfo {
    size_t size;
    char *name;

    static int num_aspect_types;
    static ResourceType new_resource_type(char *name, size_t size);
    static ResourceType type_info(ResourceType type);
    static ResourceTypeInfo resource_type_infos[MAX_NUM_RESOURCE_TYPES];
};


class ResourceModel {
public:
private:
    std::vector<std::vector<uint8_t>> resource_tables;
};

#endif // RESOURCE_MODEL_H
