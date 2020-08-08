#ifndef ASSETS_H
#define ASSETS_H
#include "core.h"

#include "world/assets/model_assets.h"
#include "world/assets/shading_assets.h"

class Assets {
public:
    Assets() {}

    ModelAssets models;
    ShadingAssets shading;

    ResourceModel *rm;
private:
}; 

#endif // ASSETS_H
