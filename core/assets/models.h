#ifndef ASSETS_MODELS_H
#define ASSETS_MODELS_H
#include "core.h"
#include "resource_model/resource_model.h"
#include "model_loader/model_loader.h"
#include "rendering/vertex_arrays.h"

class ModelAssets {
public:
    Resource<VertexArray> load(const std::string &path);

private:
    // Models are shared after complete processing, as vertex arrays in graphics memory.
    std::unordered_map<std::string, VertexArray> vertex_array_cache;
};

#endif // ASSETS_MODELS_H
