#ifndef SPATIAL_ALGEBRA_VEC_H
#define SPATIAL_ALGEBRA_VEC_H
#include <math.h>
#include <ostream>
#include <stdlib.h>
#define frand() (rand() / (RAND_MAX * 1.0))


// Expansion macros helpful for parameter lists.
#define VEC2_EXPAND(VEC) ( VEC ).x(), ( VEC ).y()
#define VEC3_EXPAND(VEC) ( VEC ).x(), ( VEC ).y(), ( VEC ).z()
#define VEC4_EXPAND(VEC) ( VEC ).x(), ( VEC ).y(), ( VEC ).z(), ( VEC ).w()

struct mat3x3;

// vec3 and vec4 classes.
// references:
//    Peter Shirley, Ray Tracing in One Weekend, intro on vector classes
struct vec3 {
    float entries[3];
    vec3() {}
    static inline vec3 zero() { return vec3(0,0,0); }
    vec3(float x, float y, float z) : entries{x,y,z} {}
    vec3(float val) : vec3(val, val, val) {}

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
    static mat3x3 outer(vec3 a, vec3 b);

    static inline vec3 cross(vec3 a, vec3 b) {
        return vec3(a[1]*b[2] - a[2]*b[1],
                    a[2]*b[0] - a[0]*b[2],
                    a[0]*b[1] - a[1]*b[0]);
    }
    inline float length() {
        return sqrt(x()*x() + y()*y() + z()*z());
    }
    inline vec3 normalized() {
        float inv_length = 1.0 / length();
        return vec3(inv_length*x(), inv_length*y(), inv_length*z());
    }
    
    // Returns a random vector with entries in the range [a,b).
    static inline vec3 random(float a, float b) {
        return vec3(a + (b-a)*frand(), a + (b-a)*frand(), a + (b-a)*frand());
    }

    static inline vec3 lerp(vec3 a, vec3 b, float t) {
        return vec3((1-t)*a.x() + t*b.x(),
                    (1-t)*a.y() + t*b.y(),
                    (1-t)*a.z() + t*b.z());
    }

    inline vec3 abs() const {
        return vec3(fabs(x()), fabs(y()), fabs(z()));
    }

    
    static inline vec3 max(vec3 a, vec3 b) {
        return vec3(a.x() > b.x() ? a.x() : b.x(),
                    a.y() > b.y() ? a.y() : b.y(),
                    a.z() > b.z() ? a.z() : b.z());
    }
    static inline vec3 min(vec3 a, vec3 b) {
        return vec3(a.x() < b.x() ? a.x() : b.x(),
                    a.y() < b.y() ? a.y() : b.y(),
                    a.z() < b.z() ? a.z() : b.z());
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
// u == v
inline bool operator==(const vec3 &a, const vec3 &b) {
    return (a.x()==b.x()) && (a.y()==b.y()) && (a.z()==b.z());
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
inline vec3 operator/(const float &t, const vec3 &v) {
    return vec3(t/v[0], t/v[1], t/v[2]);
}

// Pairwise comparison.
inline bool operator>(const vec3 &a, const vec3 &b)
{
    return a.x() > b.x() && a.y() > b.y() && a.z() > b.z();
}
inline bool operator<(const vec3 &a, const vec3 &b)
{
    return a.x() < b.x() && a.y() < b.y() && a.z() < b.z();
}
inline bool operator>=(const vec3 &a, const vec3 &b)
{
    return a.x() >= b.x() && a.y() >= b.y() && a.z() >= b.z();
}
inline bool operator<=(const vec3 &a, const vec3 &b)
{
    return a.x() <= b.x() && a.y() <= b.y() && a.z() <= b.z();
}


struct vec4 {
    float entries[4];
    vec4() {}
    static inline vec4 zero() { return vec4(0,0,0,0); }
    static inline vec4 origin() { return vec4(0,0,0,1); }
    vec4(float x, float y, float z, float w) : entries{x,y,z,w} {}
    vec4(vec3 v3, float w) : entries{v3.entries[0], v3.entries[1], v3.entries[2], w} {}

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
    inline float length() {
        return sqrt(x()*x() + y()*y() + z()*z() + w()*w());
    }
    inline vec4 normalized() {
        float inv_length = 1.0 / length();
        return vec4(inv_length*x(), inv_length*y(), inv_length*z(), inv_length*w());
    }

    // Returns a random vector with entries in the range [a,b).
    static inline vec4 random(float a, float b) {
        return vec4(a + (b-a)*frand(), a + (b-a)*frand(), a + (b-a)*frand(), a + (b-a)*frand());
    }

    inline vec3 xyz() {
        // .xyz notation after glsl.
        return vec3(x(), y(), z());
    }

    inline vec4 abs() const {
        return vec4(fabs(x()), fabs(y()), fabs(z()), fabs(w()));
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
// u == v
inline bool operator==(const vec4 &a, const vec4 &b) {
    return (a.x()==b.x()) && (a.y()==b.y()) && (a.z()==b.z()) && (a.w()==b.w());
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
inline vec4 operator/(const float &t, const vec4 &v) {
    return vec4(t/v[0], t/v[1], t/v[2], t/v[3]);
}
// Pairwise comparison.
inline bool operator>(const vec4 &a, const vec4 &b)
{
    return a.x() > b.x() && a.y() > b.y() && a.z() > b.z() && a.w() > b.w();
}
inline bool operator<(const vec4 &a, const vec4 &b)
{
    return a.x() < b.x() && a.y() < b.y() && a.z() < b.z() && a.w() < b.w();
}
inline bool operator>=(const vec4 &a, const vec4 &b)
{
    return a.x() >= b.x() && a.y() >= b.y() && a.z() >= b.z() && a.w() >= b.w();
}
inline bool operator<=(const vec4 &a, const vec4 &b)
{
    return a.x() <= b.x() && a.y() <= b.y() && a.z() <= b.z() && a.w() <= b.w();
}

/*--------------------------------------------------------------------------------
    vec2
--------------------------------------------------------------------------------*/
struct vec2 {
    float entries[2];
    vec2() {}
    static inline vec2 zero() { return vec2(0,0); }
    vec2(float x, float y) : entries{x,y} {}

    // Entry accessors
    inline float x() const { return entries[0]; }
    inline float y() const { return entries[1]; }
    // Entry references, for assignment
    //    u.x() = 2.5;
    inline float &x() { return entries[0]; }
    inline float &y() { return entries[1]; }

    inline float &operator[](int index) { return entries[index]; }
    inline float operator[](int index) const { return entries[index]; }

    // 2D transformations. Angle theta gives the positive X axis anti-clockwise from the global X axis.
    inline vec2 rotate(float theta);
    inline vec2 transform(vec2 origin, float theta);
    inline vec2 inverse_transform(vec2 origin, float theta);

    // Operation and reassignment, e.g.
    //    u += vec2(1,1);
    inline vec2 &operator+=(const vec2 &b) {
        entries[0] += b[0];
        entries[1] += b[1];
        return *this;
    }
    inline vec2 &operator-=(const vec2 &b) {
        entries[0] -= b[0];
        entries[1] -= b[1];
        return *this;
    }
    inline vec2 &operator*=(const vec2 &b) {
        entries[0] *= b[0];
        entries[1] *= b[1];
        return *this;
    }
    inline vec2 &operator/=(const vec2 &b) {
        entries[0] /= b[0];
        entries[1] /= b[1];
        return *this;
    }
    // Scalar operation and reassignment, e.g.
    // u *= 3.0;
    inline vec2 &operator*=(float t) {
        entries[0] *= t;
        entries[1] *= t;
        return *this;
    }
    inline vec2 &operator/=(float t) {
        entries[0] /= t;
        entries[1] /= t;
        return *this;
    }

    // -u
    inline vec2 operator-() const {
        return vec2(-entries[0],-entries[1]);
    }

    static inline float dot(vec2 a, vec2 b) {
        return a[0]*b[0] + a[1]*b[1];
    }
    inline float length() {
        return sqrt(x()*x() + y()*y());
    }
    inline vec2 normalized() {
        float inv_length = 1.0 / length();
        return vec2(inv_length*x(), inv_length*y());
    }
    
    // Returns a random vector with entries in the range [a,b).
    static inline vec2 random(float a, float b) {
        return vec2(a + (b-a)*frand(), a + (b-a)*frand());
    }

    static inline vec2 lerp(vec2 a, vec2 b, float t) {
        return vec2((1-t)*a.x() + t*b.x(),
                    (1-t)*a.y() + t*b.y());
    }

    inline vec2 abs() const {
        return vec2(fabs(x()), fabs(y()));
    }

    static inline vec2 max(vec2 a, vec2 b) {
        return vec2(a.x() > b.x() ? a.x() : b.x(),
                    a.y() > b.y() ? a.y() : b.y());
    }
    static inline vec2 min(vec2 a, vec2 b) {
        return vec2(a.x() < b.x() ? a.x() : b.x(),
                    a.y() < b.y() ? a.y() : b.y());
    }

    // Scalar cross product (2D right-hand rule: x is right, y is up.)
    static inline float cross(vec2 a, vec2 b) {
        return a.x()*b.y() - b.x()*a.y();
    }
    // Anticlockwise 90 degree rotation w/r/t the 2D right-hand rule.
    inline vec2 perp() const {
        return vec2(-y(), x());
    }
};
// vec2-vec2 operations.
// u + v
inline vec2 operator+(const vec2 &a, const vec2 &b) {
    return vec2(a[0]+b[0],a[1]+b[1]);
}
// u - v
inline vec2 operator-(const vec2 &a, const vec2 &b) {
    return vec2(a[0]-b[0],a[1]-b[1]);
}
// u * v is the dot product
inline float operator*(const vec2 &a, const vec2 &b) {
    return vec2::dot(a,b);
}
// u / v
inline vec2 operator/(const vec2 &a, const vec2 &b) {
    return vec2(a[0]/b[0],a[1]/b[1]);
}
// u == v
inline bool operator==(const vec2 &a, const vec2 &b) {
    return (a.x()==b.x()) && (a.y()==b.y());
}

// scalar-vec2 operations.
inline vec2 operator*(const float &t, const vec2 &v) {
    return vec2(t*v[0], t*v[1]);
}
inline vec2 operator*(const vec2 &v, const float &t) {
    return vec2(t*v[0], t*v[1]);
}
inline vec2 operator/(const vec2 &v, const float &t) {
    return vec2(v[0]/t, v[1]/t);
}
inline vec2 operator/(const float &t, const vec2 &v) {
    return vec2(t/v[0], t/v[1]);
}

inline vec2 vec2::rotate(float theta) {
    float s = sin(theta);
    float c = cos(theta);
    return vec2(c*x() + s*y(), -s*x() + c*y());
}

inline vec2 vec2::transform(vec2 origin, float theta) {
    return origin + rotate(theta);
}
inline vec2 vec2::inverse_transform(vec2 origin, float theta) {
    return (*this - origin).rotate(-theta);
}

// Pairwise comparison.
inline bool operator>(const vec2 &a, const vec2 &b)
{
    return a.x() > b.x() && a.y() > b.y();
}
inline bool operator<(const vec2 &a, const vec2 &b)
{
    return a.x() < b.x() && a.y() < b.y();
}
inline bool operator>=(const vec2 &a, const vec2 &b)
{
    return a.x() >= b.x() && a.y() >= b.y();
}
inline bool operator<=(const vec2 &a, const vec2 &b)
{
    return a.x() <= b.x() && a.y() <= b.y();
}

//--------------------------------------------------------------------------------

// Printing
std::ostream &operator<<(std::ostream &os, const vec2 &v);
std::ostream &operator<<(std::ostream &os, const vec3 &v);
std::ostream &operator<<(std::ostream &os, const vec4 &v);


#endif // SPATIAL_ALGEBRA_VEC_H
