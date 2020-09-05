#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H
#include "core.h"
class World;

template <typename T>
class ResourceCache {
public:
    ResourceCache(World &_world) : world{_world} {}
    Resource<T> load(const std::string &path);
protected:
    // Compiling a resource creates the resource from the asset file.
    // virtual Resource<T> compile(const std::string &path) {
    //     // Not pure-virtual so template specialization can be used to implement a new resource cache.
    //     fprintf(stderr, "ERROR: Unimplemented ResourceCache compile().\n");
    //     exit(EXIT_FAILURE);
    // }
    virtual Resource<T> compile(const std::string &path) = 0;
    std::unordered_map<std::string, Resource<T>> cache;
    World &world;
};


template <typename T>
Resource<T> ResourceCache<T>::load(const std::string &path)
{
    auto found = cache.find(path);
    if (found == cache.end()) {
        auto resource = compile(path);
        cache[path] = resource;
        return resource;
    }
    return found->second;
}

#endif // RESOURCE_CACHE_H
