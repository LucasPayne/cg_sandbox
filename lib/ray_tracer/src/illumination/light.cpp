#include "light.hpp"
#include "primitives.hpp"

// Test if this ray (or ray segment) intersects a primitive.
// Most likely this will be the scene or possibly some other aggregate primitive.

// return a float in [0,1], 0 being not occluded. This is so a hack can be used to give lighter shadows for transparent objects.
// This does not really make sense at all though.
float VisibilityTester::occlusion(Primitive *primitive)
{
    if (primitive->does_intersect(ray)) {
        Intersection inter;
        // do it again ...
        if (!primitive->intersect(ray, &inter)) return 0;
        if (inter.primitive->refractive_index > 0) return 1 - inter.primitive->refraction_amount;
        return 1;
    }
    return 0;
}
