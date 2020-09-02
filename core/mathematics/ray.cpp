#include "mathematics/mathematics.h"



// Ray-sphere intersection.
// Return the point of intersection.
bool Ray::intersect(const Sphere &sphere, vec3 *intersection) const
{
    vec3 d = origin - sphere.origin;
    float A = vec3::dot(direction, direction);
    float B = 2*vec3::dot(direction, d);
    float C = vec3::dot(d, d) - sphere.radius;
    float discrim = B*B - 4*A*C;
    if (discrim >= 0) {
        float sqrt_discrim = sqrt(discrim);
        float inv_2a = 1.0 / (2 * A);
        float t1 = (-B + sqrt_discrim) * inv_2a;
        if (t1 < 0) {
            float t2 = (-B - sqrt_discrim) * inv_2a;
            if (t2 < 0) return false;
            *intersection = origin + t2*direction;
            return true;
        }
        *intersection = origin + t1*direction;
        return true;
    }
    return false;
}
