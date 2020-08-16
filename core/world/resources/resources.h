#ifndef RESOURCES_H
#define RESOURCES_H
#include <assert.h>
#include <utility>//std::forward
#include "core.h"
#include "data_structures/table_collection.h"


class Resources;

template <typename T>
class Resource;
class GenericResource {
    friend class Resources;
public:
    GenericResource() :
        resources{nullptr}, table_collection_element()
    {} //default null

    GenericResource(Resources *_resources, TableCollectionElement _table_collection_element) :
        resources{_resources}, table_collection_element{_table_collection_element}
    {}


    bool operator==(const GenericResource &other) {
        return (resources == other.resources) && (table_collection_element == other.table_collection_element);
    }
    bool operator!=(const GenericResource &other) {
        return !(*this == other);
    }

    TypeHandle &type() const;

    // Unique runtime ID.
    TableElementID ID() const { return table_collection_element.ID(); }

    // Get the resource data as a generic byte-array.
    uint8_t *get_data();

    //...moved to public for pointer fixups...
    Resources *resources;
private:
    TableCollectionElement table_collection_element;


    friend class PrimitiveTypeDescriptor<GenericResource>;

    // Since friend classes are not inherited, here it would be wanted to be a friend of PrimitiveTypeDescriptor<Resource<T>> for all T. However, ...
    //
    // https://stackoverflow.com/questions/59111863/friend-template-function-instantiations-that-match-parameter
    // "If you want to have a friend template, you can make all the instatiations of the template a friend, like in your example,
    //  or you can make a full specialization a friend. There is nothing in between unfortunately."
    //
    // This seems like an arbitrary thing to not be able to do.

    // Solution: Why not just be friends with all PrimitiveTypeDescriptors? Wouldn't hurt.
    template <typename T>
    friend class PrimitiveTypeDescriptor;
};
REFLECT_STRUCT(GenericResource);


// This is purely a syntactic wrapper around GenericResource.
// (todo): Reflection should just treat this as a GenericResource.
template <typename T>
class Resource : public GenericResource {
    friend class Resources;
public:
    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;

    GenericResource &generic() { return *this; }

    Resource() : GenericResource()
    {} //default null
        
    Resource(GenericResource generic_resource) : GenericResource(generic_resource) {}

    Resource(Resources *resources, TableCollectionElement table_collection_element) :
        GenericResource(resources, table_collection_element)
    {}
private:
    friend class PrimitiveTypeDescriptor<Resource<T>>;
};
template <typename T>
REFLECT_STRUCT_TEMPLATED(Resource<T>);
template <typename T>
DESCRIPTOR_INSTANCE(Resource<T>);
template <typename T>
BEGIN_ENTRIES(Resource<T>)
    ENTRY(resources)
    ENTRY(table_collection_element)
END_ENTRIES()


class Resources {
    friend class GenericResource;
    template <typename T>
    friend class Resource;
public:
    template <typename T>
    void register_resource_type();
    
    template <typename T, typename... Args>
    Resource<T> add(Args&&... args);
    
    template <typename T>
    T *get(Resource<T> resource);

    void save(std::ostream &out);

private:
    TableCollection resource_tables;

    friend class PrimitiveTypeDescriptor<Resources>;
};
REFLECT_STRUCT(Resources);




template <typename T>
T &Resource<T>::operator*() {
    return *resources->get(*this);
}
template <typename T>
T *Resource<T>::operator->() {
    return &(operator*());
}
template <typename T>
const T &Resource<T>::operator*() const {
    return *resources->get(*this);
}
template <typename T>
const T *Resource<T>::operator->() const {
    return &(operator*());
}



template <typename T>
void Resources::register_resource_type()
{
    resource_tables.register_type<T>();
}

template <typename T, typename... Args>
Resource<T> Resources::add(Args&&... args) {
    return Resource<T>(this, resource_tables.add<T>(std::forward<Args>(args)...));
}

template <typename T>
T *Resources::get(Resource<T> resource) {
    return resource_tables.get<T>(resource.table_collection_element);
}


#endif // RESOURCES_H
