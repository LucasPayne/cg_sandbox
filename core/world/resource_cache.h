#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H
#include "core.h"
class World;


// ResourceCaches derive from this class and implement the compile() method.
template <typename T>
class ResourceCache {
public:
    ResourceCache(World &_world) : world{_world} {}
    Resource<T> load(const std::string &path);
protected:
    // Compiling a resource creates the resource from the asset file.
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
