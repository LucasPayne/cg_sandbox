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


float saturate(float x, float minimum = 0.f, float maximum = 1.f);


struct Sphere {
    vec3 origin;
    float radius;

    Sphere() {}
    Sphere(vec3 _origin, float _radius) :
        origin{_origin}, radius{_radius}
    {}
};

struct BoundingBox {
    vec3 mins;
    vec3 maxs;
    BoundingBox() :
        mins{vec3(INFINITY)}, maxs{vec3(-INFINITY)}
    {}
    BoundingBox(vec3 _mins, vec3 _maxs) :
        mins{_mins}, maxs{_maxs}
    {}
    BoundingBox(std::vector<vec3> points);

    inline vec3 extents() const {
        return vec3(maxs.x() - mins.x(), maxs.y() - mins.y(), maxs.z() - mins.z());
    }

    inline Sphere bounding_sphere() const {
        vec3 origin = 0.5*mins + 0.5*maxs;
        float radius = (0.5*extents()).length();
        return Sphere(origin, radius);
    }

    inline vec3 contains(vec3 p) {
        return p >= mins && p <= maxs;
    }
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
