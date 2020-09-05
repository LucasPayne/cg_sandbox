#ifndef ASSETS_H
#define ASSETS_H
#include "core.h"
#include "world/assets/model_assets.h"


class Assets {
public:
    Assets(World &_world) :
        models(_world),
        world{_world}
    {}
    struct ModelCache : public ResourceCache<VertexArray> {
        ModelCache(World &_world) : ResourceCache<VertexArray>(_world) {}
        Resource<VertexArray> compile(const std::string &path);
    };
    ModelCache models;
private:
    World &world;
}; 


#endif // ASSETS_H
