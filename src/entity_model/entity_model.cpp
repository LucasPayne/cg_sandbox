#include "core.h"
#include "entity_model/entity_model.h"

AspectType AspectEntryBase::next_type()
{
    static AspectType _next_type = 0;
    return _next_type ++;
}

EntityModel::EntityModel()
{

}
EntityModel::~EntityModel()
{

}
