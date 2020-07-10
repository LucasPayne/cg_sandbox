#include "core.h"
#include "entity_model/entity_model.h"

// std::vector<AspectInfo> AspectInfo::aspect_infos;
AspectInfo AspectInfo::aspect_infos[MAX_NUM_ASPECT_TYPES];

AspectType AspectInfo::new_aspect_type(AspectCreateFunction create,
                                            AspectTeardownFunction teardown,
                                            size_t size)
{
    static int num_aspect_types = 0;
    if (num_aspect_types + 1 >  MAX_NUM_ASPECT_TYPES) {
        std::cerr << "ERROR: Too many aspect types.\n";
        exit(EXIT_FAILURE);
    }

    AspectInfo &info = aspect_infos[num_aspect_types];
    info.size = size;
    info.create = create;
    info.teardown = teardown;
    std::cout << "Added, now size: " << num_aspect_types + 1 << "\n";

    return num_aspect_types ++;
}
AspectInfo AspectInfo::type_info(AspectType type)
{
    return aspect_infos[type];
}

EntityModel::EntityModel()
{

}
EntityModel::~EntityModel()
{

}
