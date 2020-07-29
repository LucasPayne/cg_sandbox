#include "assets/models.h"

Resource<VertexArray> ModelAssets::load(const std::string &path)
{
    MLModel model = MLModel::load(path);
}
