#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include "core.h"


// Include the spatial_algebra library for vectors, matrices, and quaternions.
#include "spatial_algebra/spatial_algebra.h"
// This library knows nothing about serialization, so serialization of these objects is declared here.
REFLECT_PRIMITIVE(vec3);
REFLECT_PRIMITIVE(vec4);
REFLECT_PRIMITIVE(mat4x4);
REFLECT_PRIMITIVE(Quaternion);


struct Sphere {
    vec3 origin;
    float radius;

    Sphere() {}
    Sphere(vec3 _origin, float _radius) :
        origin{_origin}, radius{_radius}
    {}
};


struct Ray {
    vec3 origin;
    vec3 direction;

    Ray() {}
    Ray(vec3 _origin, vec3 _direction) :
        origin{_origin}, direction{_direction}
    {}
    
    inline void normalize() {
        direction = direction.normalized();
    }

    bool intersect(const Sphere &sphere, vec3 *intersection) const;
};

std::ostream &operator<<(std::ostream &os, const Ray &ray);


#endif // MATHEMATICS_H
