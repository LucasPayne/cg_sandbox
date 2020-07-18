#ifndef ASSETS_H
#define ASSETS_H
#include "resource_model/resource_model.h"

class AssetLoader;
struct AssetLoaderBase;
class AssetLibrary {
public:
    template <typename TYPE>
    Resource<TYPE> load_asset(const std::string &name) {
        // Lookup in cache, if its not there, load and compile the asset.
    }
private:
    std::vector<AssetLoaderBase *> asset_loaders;
};

struct Asset;
struct AssetLoaderBase {
};
template <typename TYPE>
struct AssetLoader : AssetLoaderBase {
    std::vector<Asset<TYPE>> loaded_assets;
};
template <typename TYPE>
struct Asset {
    Resource<TYPE> resource; // Handle to the unique resource of this asset.
};

#endif // ASSETS_H
