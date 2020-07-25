#ifndef MATHEMATICS_VEC3_VEC4_H
#define MATHEMATICS_VEC3_VEC4_H
#include "mathematics/mathematics.h"

// vec3 and vec4 classes.
// references:
//    Peter Shirley, Ray Tracing in One Weekend, intro on vector classes
struct vec3 {
    float entries[3];
    vec3() {}
    static inline vec3 zero() { return vec3(0,0,0); }
    vec3(float x, float y, float z) : entries{x,y,z} {}

    // Entry accessors
    inline float x() const { return entries[0]; }
    inline float y() const { return entries[1]; }
    inline float z() const { return entries[2]; }
    inline float r() const { return entries[0]; }
    inline float g() const { return entries[1]; }
    inline float b() const { return entries[2]; }
    // Entry references, for assignment
    //    u.x() = 2.5;
    inline float &x() { return entries[0]; }
    inline float &y() { return entries[1]; }
    inline float &z() { return entries[2]; }
    inline float &r() { return entries[0]; }
    inline float &g() { return entries[1]; }
    inline float &b() { return entries[2]; }

    inline float &operator[](int index) { return entries[index]; }
    inline float operator[](int index) const { return entries[index]; }

    // Operation and reassignment, e.g.
    //    u += vec3(1,1,1);
    inline vec3 &operator+=(const vec3 &b) {
        entries[0] += b[0];
        entries[1] += b[1];
        entries[2] += b[2];
        return *this;
    }
    inline vec3 &operator-=(const vec3 &b) {
        entries[0] -= b[0];
        entries[1] -= b[1];
        entries[2] -= b[2];
        return *this;
    }
    inline vec3 &operator*=(const vec3 &b) {
        entries[0] *= b[0];
        entries[1] *= b[1];
        entries[2] *= b[2];
        return *this;
    }
    inline vec3 &operator/=(const vec3 &b) {
        entries[0] /= b[0];
        entries[1] /= b[1];
        entries[2] /= b[2];
        return *this;
    }
    // Scalar operation and reassignment, e.g.
    // u *= 3.0;
    inline vec3 &operator*=(float t) {
        entries[0] *= t;
        entries[1] *= t;
        entries[2] *= t;
        return *this;
    }
    inline vec3 &operator/=(float t) {
        entries[0] /= t;
        entries[1] /= t;
        entries[2] /= t;
        return *this;
    }
    // -u
    inline vec3 operator-() const {
        return vec3(-entries[0],-entries[1],-entries[2]);
    }

    static inline float dot(vec3 a, vec3 b) {
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    }
    static inline vec3 cross(vec3 a, vec3 b) {
        return vec3(a[1]*b[2] - a[2]*b[1],
                    a[2]*b[0] - a[0]*b[2],
                    a[0]*b[1] - a[1]*b[0]);
    }
};

// vec3-vec3 operations.
// u + v
inline vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a[0]+b[0],a[1]+b[1],a[2]+b[2]);
}
// u - v
inline vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a[0]-b[0],a[1]-b[1],a[2]-b[2]);
}
// u * v
inline vec3 operator*(const vec3 &a, const vec3 &b) {
    return vec3(a[0]*b[0],a[1]*b[1],a[2]*b[2]);
}
// u / v
inline vec3 operator/(const vec3 &a, const vec3 &b) {
    return vec3(a[0]/b[0],a[1]/b[1],a[2]/b[2]);
}
// scalar-vec3 operations.
inline vec3 operator*(const float &t, const vec3 &v) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}
inline vec3 operator*(const vec3 &v, const float &t) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}
inline vec3 operator/(const vec3 &v, const float &t) {
    return vec3(v[0]/t, v[1]/t, v[2]/t);
}


struct vec4 {
    float entries[4];
    vec4() {}
    static inline vec4 zero() { return vec4(0,0,0,0); }
    static inline vec4 origin() { return vec4(0,0,0,1); }
    vec4(float x, float y, float z, float w) : entries{x,y,z,w} {}

    // Entry accessors
    inline float x() const { return entries[0]; }
    inline float y() const { return entries[1]; }
    inline float z() const { return entries[2]; }
    inline float w() const { return entries[3]; }
    inline float r() const { return entries[0]; }
    inline float g() const { return entries[1]; }
    inline float b() const { return entries[2]; }
    inline float a() const { return entries[3]; }
    // Entry references, for assignment
    //    u.x() = 2.5;
    inline float &x() { return entries[0]; }
    inline float &y() { return entries[1]; }
    inline float &z() { return entries[2]; }
    inline float &w() { return entries[3]; }
    inline float &r() { return entries[0]; }
    inline float &g() { return entries[1]; }
    inline float &b() { return entries[2]; }
    inline float &a() { return entries[3]; }

    inline float &operator[](int index) { return entries[index]; }
    inline float operator[](int index) const { return entries[index]; }

    // Operation and reassignment, e.g.
    //    u += vec4(1,1,1);
    inline vec4 &operator+=(const vec4 &b) {
        entries[0] += b[0];
        entries[1] += b[1];
        entries[2] += b[2];
        entries[3] += b[3];
        return *this;
    }
    inline vec4 &operator-=(const vec4 &b) {
        entries[0] -= b[0];
        entries[1] -= b[1];
        entries[2] -= b[2];
        entries[3] -= b[3];
        return *this;
    }
    inline vec4 &operator*=(const vec4 &b) {
        entries[0] *= b[0];
        entries[1] *= b[1];
        entries[2] *= b[2];
        entries[3] *= b[3];
        return *this;
    }
    inline vec4 &operator/=(const vec4 &b) {
        entries[0] /= b[0];
        entries[1] /= b[1];
        entries[2] /= b[2];
        entries[3] /= b[3];
        return *this;
    }
    // Scalar operation and reassignment, e.g.
    // u *= 3.0;
    inline vec4 &operator*=(float t) {
        entries[0] *= t;
        entries[1] *= t;
        entries[2] *= t;
        entries[3] *= t;
        return *this;
    }
    inline vec4 &operator/=(float t) {
        entries[0] /= t;
        entries[1] /= t;
        entries[2] /= t;
        entries[3] /= t;
        return *this;
    }
    // -u
    inline vec4 operator-() const {
        return vec4(-entries[0],-entries[1],-entries[2],-entries[3]);
    }

    static inline float dot(vec4 a, vec4 b) {
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
    }
};

// vec4-vec4 operations.
// u + v
inline vec4 operator+(const vec4 &a, const vec4 &b) {
    return vec4(a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3]);
}
// u - v
inline vec4 operator-(const vec4 &a, const vec4 &b) {
    return vec4(a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3]);
}
// u * v
inline vec4 operator*(const vec4 &a, const vec4 &b) {
    return vec4(a[0]*b[0],a[1]*b[1],a[2]*b[2],a[3]*b[3]);
}
// u / v
inline vec4 operator/(const vec4 &a, const vec4 &b) {
    return vec4(a[0]/b[0],a[1]/b[1],a[2]/b[2],a[3]/b[3]);
}
// scalar-vec4 operations.
inline vec4 operator*(const float &t, const vec4 &v) {
    return vec4(t*v[0], t*v[1], t*v[2], t*v[3]);
}
inline vec4 operator*(const vec4 &v, const float &t) {
    return vec4(t*v[0], t*v[1], t*v[2], t*v[3]);
}
inline vec4 operator/(const vec4 &v, const float &t) {
    return vec4(v[0]/t, v[1]/t, v[2]/t, v[3]/t);
}

#endif // MATHEMATICS_VEC3_VEC4_H
