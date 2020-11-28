#ifndef MODEL_ASSETS_H
#define MODEL_ASSETS_H
#include "core.h"
#include "world/resources/resources.h"
#include "model_loader/model_loader.h"
#include "graphics_resources/vertex_arrays.h"
#include "world/resource_cache.h"

bool MLModel_to_VertexArrayData(MLModel &model, VertexArrayData &va);

#endif // MODEL_ASSETS_H
