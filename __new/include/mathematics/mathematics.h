#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include "core.h"
// Include the spatial_algebra library for vectors, matrices, and quaternions.
#include "spatial_algebra/spatial_algebra.h"

template <typename T>
inline T max(T a, T b)
{
    if (a > b) return a;
    return b;
}

template <typename T>
inline T min(T a, T b)
{
    if (a < b) return a;
    return b;
}

template <typename T>
inline T clamp(T x, T a, T b)
{
    if (x < a) return a;
    if (x > b) return b;
    return x;
}


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

    Frustum() {}
    Frustum(vec3 _position, mat3x3 _orientation, float _n, float _f, float hw, float hh) :
        position{_position}, orientation{_orientation}, n{_n}, f{_f}, half_w{hw}, half_h{hh}
    {}

    // Get a point in "frustum coordinates", where z ranges from 0 at the near plane to 1 at the far plane,
    // and x,y range from -1 to 1 on the frustum quad at that depth.
    vec3 point(float x, float y, float z);

    // The below matrices are the usual camera matrices, for a projective camera with this frustum.
    mat4x4 view_matrix();
    mat4x4 projection_matrix();
    // Full view-projection matrix
    mat4x4 matrix();
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

    for (int i = 0; i < 6; i++) {
        if (vec3::dot(origin - points[i], normals[i]) > radius) {
	    return false;
        }
    }
    return true;
}


#endif // MATHEMATICS_H
