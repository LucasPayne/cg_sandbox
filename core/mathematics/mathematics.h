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
struct Frustum;

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
    // Approximate frustum intersection.
    inline bool approx_intersects(Frustum frustum);
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


struct Frustum {
    vec3 position;
    // The frustum extends in the local negative Z direction.
    mat3x3 orientation; // assumed orthonormal
    float n;
    float f;
    float half_w;
    float half_h; // at the near plane

    Frustum(vec3 _position, mat3x3 _orientation, float n, float f, float hw, float hh) :
        position{_position}, orientation{_orientation}, half_w{hw}, half_h{hh}
    {}

    // Get a point in "frustum coordinates", where z ranges from 0 at the near plane to 1 at the far plane,
    // and x,y range from -1 to 1 on the frustum quad at that depth.
    inline vec3 point(float x, float y, float z) {
        float pz = (1 - z)*n + z*f;
        float px = x * pz * half_w / n;
        float py = y * pz * half_h / n;
        return position + orientation * vec3(px, py, pz);
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


inline bool Sphere::approx_intersects(Frustum frustum)
{
    // Set up plane equations.
    vec3 far_quad[4];
    far_quad[0] = frustum.point(-1,-1,1);
    far_quad[1] = frustum.point(1,-1,1);
    far_quad[2] = frustum.point(1,1,1);
    far_quad[3] = frustum.point(-1,1,1);
    vec3 points[6];
    vec3 normals[6];
    points[0] = frustum.point(-1,-1,0);
    points[1] = frustum.point(1,-1,0);
    points[2] = frustum.point(1,1,0);
    points[3] = frustum.point(-1,1,0);
    for (int i = 0; i < 4; i++) {
        normals[i] = vec3::cross(far_quad[i] - points[i], points[(i+1)%4] - points[i]).normalized();
    }
    vec3 forward = frustum.orientation * vec3(0,0,1);
    points[4] = points[0];
    normals[4] = forward;
    points[5] = far_quad[0];
    normals[5] = -forward;

        bool culled = false;
        for (int i = 0; i < 6; i++) {
            if (vec3::dot(sphere.origin - points[i], normals[i]) > sphere.radius) {
                culled = true;
                break;
            }
        }
        if (culled) continue;
}


#endif // MATHEMATICS_H
