#ifndef MODEL_ASSETS_H
#define MODEL_ASSETS_H
#include "core.h"
#include "world/resource_model/resource_model.h"
#include "model_loader/model_loader.h"
#include "rendering/vertex_arrays.h"

class ModelAssets {
public:
    ModelAssets() {}
    Resource<VertexArray> load(const std::string &path);
    ResourceModel *rm;
private:
    // Models are shared after complete processing, as vertex arrays in graphics memory.
    std::unordered_map<std::string, Resource<VertexArray>> vertex_array_cache;
};

#endif // MODEL_ASSETS_H
