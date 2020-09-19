#ifndef SPATIAL_ALGEBRA_QUATERNION_H
#define SPATIAL_ALGEBRA_QUATERNION_H
/*--------------------------------------------------------------------------------
some references:
https://www.gamasutra.com/view/feature/131686/rotating_objects_using_quaternions.php
https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Using_quaternion_as_rotations
--------------------------------------------------------------------------------*/
#include "vec.h"
#include <math.h>
#include <ostream>


struct Quaternion {
    Quaternion(float scalar, float i, float j, float k) :
        entries{scalar,i,j,k}
    {}
    Quaternion() {}
    static inline Quaternion identity() { return Quaternion(1,0,0,0); }

    float entries[4];
    inline float scalar() const { return entries[0]; }
    inline float &scalar() { return entries[0]; }
    inline float i() const { return entries[1]; }
    inline float &i() { return entries[1]; }
    inline float j() const { return entries[2]; }
    inline float &j() { return entries[2]; }
    inline float k() const { return entries[3]; }
    inline float &k() { return entries[3]; }

    inline float length() const {
        return sqrt(scalar()*scalar() + i()*i() + j()*j() + k()*k());
    }
    inline Quaternion normalized() const {
        float inv_length = 1.0 / length();
        return Quaternion(scalar() * inv_length, i() * inv_length, j() * inv_length, k() * inv_length);
    }

    inline Quaternion operator-() const {
        return Quaternion(-scalar(), -i(), -j(), -k());
    }


    /*--------------------------------------------------------------------------------
        Quaternion inverse.
        [a b c d]^-1 = q^-1 = [a -b -c -d]/(a^2 + b^2 + c^2 + d^2)
    --------------------------------------------------------------------------------*/
    inline Quaternion inverse() const {
        float inv_square_length = 1.0 / (scalar()*scalar() + i()*i() + j()*j() + k()*k());
        return Quaternion(scalar() * inv_square_length,
                          -i() * inv_square_length,
                          -j() * inv_square_length,
                          -k() * inv_square_length);
    }

    // Quaternion for an axis angle rotation described by vector along the axis with length equal to theta.
    //https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Using_quaternion_as_rotations
    static inline Quaternion from_axis_angle(vec3 axis) {
        float theta = axis.length();
        if (theta == 0) return Quaternion::identity();
        float inv_length = 1.0 / theta;
        float sin_half_theta = sin(0.5 * theta);
        return Quaternion(cos(0.5*theta), axis.x()*sin_half_theta*inv_length,
                                          axis.y()*sin_half_theta*inv_length,
                                          axis.z()*sin_half_theta*inv_length);
    }
    static inline Quaternion from_axis_angle(vec3 axis, float angle) {
        float sin_half_angle = sin(0.5 * angle);
        return Quaternion(cos(0.5*angle), axis.x()*sin_half_angle,
                                          axis.y()*sin_half_angle,
                                          axis.z()*sin_half_angle);
    }

    // This is not spherical interpolation. Intermediate quaternions are not rotation quaternions, and should be normalized by the caller,
    // if this is being used as an approximation to slerp.
    static inline Quaternion lerp(const Quaternion &A, const Quaternion &B, float t) {
        return Quaternion((1-t)*A.scalar() + t*B.scalar(),
                          (1-t)*A.i() + t*B.i(),
                          (1-t)*A.j() + t*B.j(),
                          (1-t)*A.k() + t*B.k());
    }

    // Returns a quaternion representing the same rotation (if these are unit quaternions),
    // which is contained in the hemisphere defined by the input quaternion.
    inline Quaternion to_hemisphere(const Quaternion &q) {
        if (scalar()*q.scalar() + i()*q.i() + j()*q.j() + k()*q.k() < 0) return -(*this);
        return *this;
    }
};

/*--------------------------------------------------------------------------------
Hamilton product of two quaternions.
(a b c d)(a' b' c' d') = (aa' - bb' - cc' - dd'
                          ab' + a'b + cd' - c'd
                          ac' + a'c - bd' + b'd
                          ad' + a'd + bc' - b'c)
--------------------------------------------------------------------------------*/
inline Quaternion operator*(const Quaternion &A, const Quaternion &B) {
    return Quaternion(A.scalar()*B.scalar() - A.i()*B.i() - A.j()*B.j() - A.k()*B.k(),
                      A.scalar()*B.i() + B.scalar()*A.i() + A.j()*B.k() - B.j()*A.k(),
                      A.scalar()*B.j() + B.scalar()*A.j() - A.i()*B.k() + B.i()*A.k(),
                      A.scalar()*B.k() + B.scalar()*A.k() + A.i()*B.j() - B.i()*A.j());
}
std::ostream &operator<<(std::ostream &os, const Quaternion &q);



#endif // SPATIAL_ALGEBRA_QUATERNION_H
