#ifndef MODEL_ASSETS_H
#define MODEL_ASSETS_H
#include "core.h"
#include "world/resources/resources.h"
#include "model_loader/model_loader.h"
#include "graphics_resources/vertex_arrays.h"

class ModelAssets {
public:
    ModelAssets() {}
    Resource<VertexArray> load(const std::string &path);
    Resources *resources;
private:
    std::unordered_map<std::string, Resource<VertexArray>> vertex_array_cache;
};

#endif // MODEL_ASSETS_H
