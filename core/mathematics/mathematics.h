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


inline bool between(float x, float minimum, float maximum) {
    return x >= minimum && x <= maximum;
}
inline bool strictly_between(float x, float minimum, float maximum) {
    return x > minimum && x < maximum;
}
inline float saturate(float x, float minimum, float maximum)
{
    if (x < minimum) return minimum;
    if (x > maximum) return maximum;
    return x;
}


struct BoundingBox;
struct OrientedBox;

struct Sphere {
    vec3 origin;
    float radius;

    Sphere() {}
    Sphere(vec3 _origin, float _radius) :
        origin{_origin}, radius{_radius}
    {}

    // Approximate AABB intersection for culling (for example, when rendering orthogonally projected shadow maps).
    inline bool approx_intersects(BoundingBox box);
    // Approximate OBB intersection.
    inline bool approx_intersects(OrientedBox box);
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

struct OrientedBox {
    vec3 mins;
    vec3 maxs;
    mat3x3 orientation;

    OrientedBox() :
        mins{vec3(INFINITY)}, maxs{vec3(-INFINITY)}
    {}
    OrientedBox(vec3 _mins, vec3 _maxs) :
        mins{_mins}, maxs{_maxs}, orientation{mat3x3::identity()}
    {}
    OrientedBox(vec3 _mins, vec3 _maxs, mat3x3 _orientation) :
        mins{_mins}, maxs{_maxs}, orientation{_orientation}
    {}

    inline vec3 extents() const {
        return vec3(maxs.x() - mins.x(), maxs.y() - mins.y(), maxs.z() - mins.z());
    }
    inline vec3 contains(vec3 p) {
        vec3 pp = orientation.transpose() * p;
        return pp >= mins && pp <= maxs;
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



inline bool Sphere::approx_intersects(BoundingBox box)
{
    return between(origin.x(), box.mins.x() - radius, box.maxs.x() + radius)
        && between(origin.y(), box.mins.y() - radius, box.maxs.y() + radius)
        && between(origin.z(), box.mins.z() - radius, box.maxs.z() + radius);
}


inline bool Sphere::approx_intersects(OrientedBox box)
{
    vec3 o = box.orientation.transpose() * origin;
    return between(o.x(), box.mins.x() - radius, box.maxs.x() + radius)
        && between(o.y(), box.mins.y() - radius, box.maxs.y() + radius)
        && between(o.z(), box.mins.z() - radius, box.maxs.z() + radius);
}




#endif // MATHEMATICS_H
