#ifndef MATHEMATICS_MAT4X4_H
#define MATHEMATICS_MAT4X4_H
#include "mathematics/mathematics.h"

// mat4x4 is column-major, as default in OpenGL/GLSL.
struct mat4x4 {
    float entries[16];
    // Constructor with column-major parameter order.
    mat4x4(float e00, float e10, float e20, float e30,
           float e01, float e11, float e21, float e31,
           float e02, float e12, float e22, float e32,
           float e03, float e13, float e23, float e33)
    : entries{e00,e10,e20,e30,
              e01,e11,e21,e31,
              e02,e12,e22,e32,
              e03,e13,e23,e33} {};
    // Constructor with column-major float array.
    mat4x4(float _entries[/*16*/]) {
        memcpy(entries, _entries, sizeof(entries));
    }
    // Constructor from four column vectors.
    mat4x4(vec4 c0, vec4 c1, vec4 c2, vec4 c3) {
        memcpy(entries, &c0, sizeof(vec4));
        memcpy(entries+sizeof(vec4), &c1, sizeof(vec4));
        memcpy(entries+2*sizeof(vec4), &c2, sizeof(vec4));
        memcpy(entries+3*sizeof(vec4), &c3, sizeof(vec4));
    }
    // Index with i+1'th row, j+1'th column, e.g.
    //     M.entry(2,3) is the entry at the third row, fourth column.
    inline float entry(int i, int j) const {
        return entries[4*j + i];
    }
    inline float &entry(int i, int j) {
        return entries[4*j + i];
    }

    // Extract columns.
    inline vec4 column(int j) const {
        // mat4x4 is column-major, so just return the column directly.
        return *((vec4 *) &entries[4*j]);
    }
    // Extract rows.
    inline vec4 row(int i) const {
        return vec4(entries[4*0 + i],
                    entries[4*1 + i],
                    entries[4*2 + i],
                    entries[4*3 + i]);
    }

    inline mat4x4 transpose() const {
        return mat4x4(entry(0,0),entry(0,1),entry(0,2),entry(0,3),
                      entry(1,0),entry(1,1),entry(1,2),entry(1,3),
                      entry(2,0),entry(2,1),entry(2,2),entry(2,3),
                      entry(3,0),entry(3,1),entry(3,2),entry(3,3));
    }
};
// Matrix vector multiplication.
inline vec4 operator*(mat4x4 M, vec4 v) {
    return vec4(M.entry(0,0)*v[0] + M.entry(0,1)*v[1] + M.entry(0,2)*v[2] + M.entry(0,3)*v[3],
                M.entry(1,0)*v[0] + M.entry(1,1)*v[1] + M.entry(1,2)*v[2] + M.entry(1,3)*v[3],
                M.entry(2,0)*v[0] + M.entry(2,1)*v[1] + M.entry(2,2)*v[2] + M.entry(2,3)*v[3],
                M.entry(3,0)*v[0] + M.entry(3,1)*v[1] + M.entry(3,2)*v[2] + M.entry(3,3)*v[3]);
}
// Matrix multiplication.
inline mat4x4 operator*(mat4x4 A, mat4x4 B) {
    return mat4x4(
        // A acting on B's first column.
        A.entry(0,0)*B.entry(0, 0) + A.entry(0,1)*B.entry(1, 0) + A.entry(0,2)*B.entry(2, 0) + A.entry(0,3)*B.entry(3, 0),
        A.entry(1,0)*B.entry(0, 0) + A.entry(1,1)*B.entry(1, 0) + A.entry(1,2)*B.entry(2, 0) + A.entry(1,3)*B.entry(3, 0),
        A.entry(2,0)*B.entry(0, 0) + A.entry(2,1)*B.entry(1, 0) + A.entry(2,2)*B.entry(2, 0) + A.entry(2,3)*B.entry(3, 0),
        A.entry(3,0)*B.entry(0, 0) + A.entry(3,1)*B.entry(1, 0) + A.entry(3,2)*B.entry(2, 0) + A.entry(3,3)*B.entry(3, 0),
        // A acting on B's second column.
        A.entry(0,0)*B.entry(0, 1) + A.entry(0,1)*B.entry(1, 1) + A.entry(0,2)*B.entry(2, 1) + A.entry(0,3)*B.entry(3, 1),
        A.entry(1,0)*B.entry(0, 1) + A.entry(1,1)*B.entry(1, 1) + A.entry(1,2)*B.entry(2, 1) + A.entry(1,3)*B.entry(3, 1),
        A.entry(2,0)*B.entry(0, 1) + A.entry(2,1)*B.entry(1, 1) + A.entry(2,2)*B.entry(2, 1) + A.entry(2,3)*B.entry(3, 1),
        A.entry(3,0)*B.entry(0, 1) + A.entry(3,1)*B.entry(1, 1) + A.entry(3,2)*B.entry(2, 1) + A.entry(3,3)*B.entry(3, 1),
        // A acting on B's third column.
        A.entry(0,0)*B.entry(0, 2) + A.entry(0,1)*B.entry(1, 2) + A.entry(0,2)*B.entry(2, 2) + A.entry(0,3)*B.entry(3, 2),
        A.entry(1,0)*B.entry(0, 2) + A.entry(1,1)*B.entry(1, 2) + A.entry(1,2)*B.entry(2, 2) + A.entry(1,3)*B.entry(3, 2),
        A.entry(2,0)*B.entry(0, 2) + A.entry(2,1)*B.entry(1, 2) + A.entry(2,2)*B.entry(2, 2) + A.entry(2,3)*B.entry(3, 2),
        A.entry(3,0)*B.entry(0, 2) + A.entry(3,1)*B.entry(1, 2) + A.entry(3,2)*B.entry(2, 2) + A.entry(3,3)*B.entry(3, 2),
        // A acting on B's fourth column.
        A.entry(0,0)*B.entry(0, 3) + A.entry(0,1)*B.entry(1, 3) + A.entry(0,2)*B.entry(2, 3) + A.entry(0,3)*B.entry(3, 3),
        A.entry(1,0)*B.entry(0, 3) + A.entry(1,1)*B.entry(1, 3) + A.entry(1,2)*B.entry(2, 3) + A.entry(1,3)*B.entry(3, 3),
        A.entry(2,0)*B.entry(0, 3) + A.entry(2,1)*B.entry(1, 3) + A.entry(2,2)*B.entry(2, 3) + A.entry(2,3)*B.entry(3, 3),
        A.entry(3,0)*B.entry(0, 3) + A.entry(3,1)*B.entry(1, 3) + A.entry(3,2)*B.entry(2, 3) + A.entry(3,3)*B.entry(3, 3)
    );
}
std::ostream &operator<<(std::ostream &os, const mat4x4 &M);

#endif // MATHEMATICS_MAT4X4_H
