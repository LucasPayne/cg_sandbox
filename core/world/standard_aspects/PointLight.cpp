#include "world/standard_aspects/standard_aspects.h"


DESCRIPTOR_INSTANCE(PointLight);
BEGIN_ENTRIES(PointLight)
    ENTRY(color)
    ENTRY(radius)
END_ENTRIES()


float PointLight::extent()
{
    //---todo
    return 3.f;
}
