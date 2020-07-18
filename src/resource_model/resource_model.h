#ifndef RESOURCE_MODEL_H
#define RESOURCE_MODEL_H
#include "core.h"
typedef uint8_t ResourceType;
#define MAX_NUM_RESOURCE_TYPES 255 //-1 == 255 is reserved for the null resource type.
typedef uint32_t ResourceID;
class ResourceModel;

/*--------------------------------------------------------------------------------
Macro delimiters for defining a new resource type. This is quite ugly, but is here
since static initialization is being used to get type information, and with this syntax,
all that is needed to add a type is in one place. Every resource type encountered on
compilation will have type information available at runtime.

define_resource(GeometricMaterial)
    ...
end_define_resource(GeometricMaterial)
->
struct GeometricMaterial : public ResourceTypeStaticData<GeometricMaterial> {
    ...
};
char *GeometricMaterial::name("GeometricMaterial");
--------------------------------------------------------------------------------*/
#define define_resource(RESOURCE_TYPE_NAME)\
    struct RESOURCE_TYPE_NAME : public ResourceTypeStaticData<RESOURCE_TYPE_NAME> {
#define end_define_resource(RESOURCE_TYPE_NAME)\
    }\
    char * RESOURCE_TYPE_NAME ::name(#RESOURCE_TYPE_NAME);


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
        // The fork is not readonly.
        // -This means that the handle needs access to the resource model state.
        // -Maybe do this separately, such as resourc_model.fork(handle).
    }
    ResourceType type() const { return m_type; }
    ResourceID id() const { return m_id; }
private:
    bool m_readonly;
    ResourceType m_type;
    ResourceID m_id;
    uint32_t m_index;
};


struct ResourceEntry {
    friend ResourceModel;
private:
    ResourceID id;
    uint32_t next_free_index;
};


template <typename TYPE>
struct ResourceTypeStaticData : public ResourceEntry {
    static const ResourceType type;
    static const size_t size;
    static const char *name;
};
template<typename TYPE>
const ResourceType ResourceTypeStaticData<TYPE>::type(AspectInfo::new_aspect_type(
    T::name,
    sizeof(T)
));


struct ResourceTypeInfo {
    size_t size() const { return m_size; }
    const char *name() const { return m_name; }

    static int num_aspect_types() const { return m_num_aspect_types; }
private:
    size_t m_size;
    const char *m_name;
    static int m_num_aspect_types;
    static ResourceType new_resource_type(char *name, size_t size);
    static ResourceType type_info(ResourceType type);
    static ResourceTypeInfo resource_type_infos[MAX_NUM_RESOURCE_TYPES];
};


struct TestResource : public ResourceTypeStaticData<TestResource> {
    int some_value;
}
const char *TestResource::name("TestResource");


#define RESOURCE_TABLE_START_LENGTH 4
struct GenericResourceTable {
    uint32_t first_free_index;
    std::vector<uint8_t> data;
    ResourceID next_id() {
        return m_next_id ++;
    }
    GenericResourceTable() :
        first_free_index{0},
        m_next_id{1},
        data{std::vector<uint8_t>(RESOURCE_TABLE_START_LENGTH)}
    {}
private:
    ResourceID m_next_id;
}
template <typename TYPE>
struct ResourceTable : GenericResourceTable {
    // !-IMPORTANT-! This class must have no data.

    Resource<TYPE> add_resource() {
        // Turn the next available slot in the table into an active resource entry,
        // then return a handle to it.
        uint32_t index = first_free_index;
        TYPE *slot = next_slot();
        Resource<TYPE> res;
        res.id = slot->id;
        res.index = index;
        res.type = TYPE::type_id;
        return res;
    }

private:
    TYPE *next_slot() {
        // !-IMPORTANT-! Only call this if a resource entry is being initialized.
        TYPE *slot = &entries()[first_free_index];
        slot->id = next_id();
        if (slot->next_free_index == 0) {
            // Resize the table if needed.
            grow();
        }
        // Delink this slot from the free list.
        first_free_index = slot->next_free_index;
        return slot;
    }
    void grow() {
        // !-IMPORTANT-! Only call this if the table _needs_ to grow, as in, it has one free slot left which is being filled.
        size_t old_length = data.size() / TYPE::SIZE;
        data.resize(2 * old_length * TYPE::size);
        entries()[first_free_index].next_free_index = old_length;
        // Link the new slots into the free list.
        for (int i = old_length; i < 2*old_length-1; i++) {
            entries()[i] = i + 1; // the next slot is also free.
        }
        entries()[2*old_length-1] = 0; // no free slots past here.
    }
    inline TYPE *entries() const {
        return (TYPE *) &data[0];
    }
    
};

class ResourceModel {
public:
    template <typename TYPE>
    Resource<TYPE> new_resource() {
        ResourceTable<TYPE> &table = get_resource_table<TYPE>();
        Resource<TYPE> res = table.add_resource();
        return res;
    }

private:
    template <typename TYPE>
    inline ResourceTable<TYPE> *get_resource_table<TYPE>() const {
        return &dynamic_cast<ResourceTable<TYPE>>(resource_tables[TYPE::type_id]);
    }
    std::vector<GenericResourceTable> resource_tables;
};


#endif // RESOURCE_MODEL_H
