#ifndef MODEL_ASSETS_H
#define MODEL_ASSETS_H
#include "core.h"
#include "resource_model/resource_model.h"
#include "model_loader/model_loader.h"
#include "rendering/vertex_arrays.h"

class ModelAssets {
public:
    ModelAssets() {}
    Resource<VertexArray> load(const std::string &path);
    ResourceModel *rm;
private:
    // Models are shared after complete processing, as vertex arrays in graphics memory.
<<<<<<< HEAD
    std::unordered_map<std::string, Resource<VertexArray>> vertex_array_cache;
=======
    std::unordered_map<std::string, VertexArray> vertex_array_cache;
>>>>>>> 408ed837dda892930c013f01098f3fd5e3442225
};

#endif // MODEL_ASSETS_H
