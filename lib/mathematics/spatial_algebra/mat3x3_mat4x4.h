#ifndef SPATIAL_ALGEBRA_MAT4X4_H
#define SPATIAL_ALGEBRA_MAT4X4_H
#include <string.h>
#include <ostream>
#include <tuple>

// mat3x3 and mat4x4 are column-major, as default in OpenGL/GLSL.
struct mat3x3 {
    float entries[9];
    // Constructor with column-major parameter order.
    mat3x3(float e00, float e10, float e20,
           float e01, float e11, float e21,
           float e02, float e12, float e22)
    : entries{e00,e10,e20,
              e01,e11,e21,
              e02,e12,e22} {};
    // Constructor with column-major float array.
    mat3x3(float _entries[/*9*/]) {
        memcpy(entries, _entries, sizeof(entries));
    }
    // Constructor from three column vectors.
    mat3x3(vec3 c0, vec3 c1, vec3 c2) :
        mat3x3(c0.x(), c0.y(), c0.z(),
               c1.x(), c1.y(), c1.z(),
               c2.x(), c2.y(), c2.z())
    {}
    mat3x3() {}
    // Index with i+1'th row, j+1'th column, e.g.
    //     M.entry(2,3) is the entry at the third row, fourth column.
    inline float entry(int i, int j) const {
        return entries[3*j + i];
    }
    inline float &entry(int i, int j) {
        return entries[3*j + i];
    }

    // Extract columns.
    inline vec3 column(int j) const {
        // mat3x3 is column-major, so just return the column directly.
        return *((vec3 *) &entries[3*j]);
    }
    // Extract rows.
    inline vec3 row(int i) const {
        return vec3(entries[3*0 + i],
                    entries[3*1 + i],
                    entries[3*2 + i]);
    }

    inline mat3x3 transpose() const {
        return mat3x3(entry(0,0),entry(0,1),entry(0,2),
                      entry(1,0),entry(1,1),entry(1,2),
                      entry(2,0),entry(2,1),entry(2,2));
    }
    static mat3x3 identity() {
        return mat3x3(1,0,0, 0,1,0, 0,0,1);
    }

    inline float trace() const {
        return entry(0,0)+entry(1,1)+entry(2,2);
    }
};
// Matrix vector multiplication.
inline vec3 operator*(mat3x3 M, vec3 v) {
    return vec3(M.entry(0,0)*v[0] + M.entry(0,1)*v[1] + M.entry(0,2)*v[2],
                M.entry(1,0)*v[0] + M.entry(1,1)*v[1] + M.entry(1,2)*v[2],
                M.entry(2,0)*v[0] + M.entry(2,1)*v[1] + M.entry(2,2)*v[2]);
}
// Matrix multiplication.
inline mat3x3 operator*(mat3x3 A, mat3x3 B) {
    return mat3x3(
        // A acting on B's first column.
        A.entry(0,0)*B.entry(0, 0) + A.entry(0,1)*B.entry(1, 0) + A.entry(0,2)*B.entry(2, 0),
        A.entry(1,0)*B.entry(0, 0) + A.entry(1,1)*B.entry(1, 0) + A.entry(1,2)*B.entry(2, 0),
        A.entry(2,0)*B.entry(0, 0) + A.entry(2,1)*B.entry(1, 0) + A.entry(2,2)*B.entry(2, 0),
        // A acting on B's second column.
        A.entry(0,0)*B.entry(0, 1) + A.entry(0,1)*B.entry(1, 1) + A.entry(0,2)*B.entry(2, 1),
        A.entry(1,0)*B.entry(0, 1) + A.entry(1,1)*B.entry(1, 1) + A.entry(1,2)*B.entry(2, 1),
        A.entry(2,0)*B.entry(0, 1) + A.entry(2,1)*B.entry(1, 1) + A.entry(2,2)*B.entry(2, 1),
        // A acting on B's third column.
        A.entry(0,0)*B.entry(0, 2) + A.entry(0,1)*B.entry(1, 2) + A.entry(0,2)*B.entry(2, 2),
        A.entry(1,0)*B.entry(0, 2) + A.entry(1,1)*B.entry(1, 2) + A.entry(1,2)*B.entry(2, 2),
        A.entry(2,0)*B.entry(0, 2) + A.entry(2,1)*B.entry(1, 2) + A.entry(2,2)*B.entry(2, 2)
    );
}
inline mat3x3 operator+(mat3x3 A, mat3x3 B) {
    mat3x3 M;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M.entry(i, j) = A.entry(i, j) + B.entry(i, j);
        }
    }
    return M;
}
inline mat3x3 operator-(mat3x3 A, mat3x3 B) {
    mat3x3 M;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M.entry(i, j) = A.entry(i, j) - B.entry(i, j);
        }
    }
    return M;
}
inline mat3x3 operator*(float r, mat3x3 M) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M.entry(i, j) *= r;
        }
    }
    return M;
}
inline mat3x3 operator*(mat3x3 M, float r) {
    return r*M;
}


std::ostream &operator<<(std::ostream &os, const mat3x3 &M);


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
    static mat4x4 row_major(float e00, float e01, float e02, float e03,
                            float e10, float e11, float e12, float e13,
                            float e20, float e21, float e22, float e23,
                            float e30, float e31, float e32, float e33)
    {
        return mat4x4(e00,e10,e20,e30,
                      e01,e11,e21,e31,
                      e02,e12,e22,e32,
                      e03,e13,e23,e33);
    }
    // Constructor with column-major float array.
    mat4x4(float _entries[/*16*/]) {
        memcpy(entries, _entries, sizeof(entries));
    }
    // Constructor from four column vectors.
    mat4x4(vec4 c0, vec4 c1, vec4 c2, vec4 c3) :
        mat4x4(c0.x(), c0.y(), c0.z(), c0.w(),
               c1.x(), c1.y(), c1.z(), c1.w(),
               c2.x(), c2.y(), c2.z(), c2.w(),
               c3.x(), c3.y(), c3.z(), c3.w())
    {}
    // Constructor from position and orientation (giving a rigid frame-of-reference matrix).
    mat4x4(vec3 position, mat3x3 orientation) :
        mat4x4(orientation.entry(0,0), orientation.entry(1,0), orientation.entry(2, 0), 0,
               orientation.entry(0,1), orientation.entry(1,1), orientation.entry(2, 1), 0,
               orientation.entry(0,2), orientation.entry(1,2), orientation.entry(2, 2), 0,
               position.x(), position.y(), position.z(), 1)
    {}

    mat4x4() {}
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


    inline float determinant() const
    {
        return entry(0,0)*(entry(1,1)*(entry(2,2)*entry(3,3) - entry(2,3)*entry(3,2))
                          -entry(1,2)*(entry(2,1)*entry(3,3) - entry(2,3)*entry(3,1))
                          +entry(1,3)*(entry(2,1)*entry(3,2) - entry(2,2)*entry(3,1)))
              -entry(0,1)*(entry(1,0)*(entry(2,2)*entry(3,3) - entry(2,3)*entry(3,2))
                          -entry(1,2)*(entry(2,0)*entry(3,3) - entry(2,3)*entry(3,0))
                          +entry(1,3)*(entry(2,0)*entry(3,2) - entry(2,2)*entry(3,0)))
              +entry(0,2)*(entry(1,0)*(entry(2,1)*entry(3,3) - entry(2,3)*entry(3,1))
                          -entry(1,1)*(entry(2,0)*entry(3,3) - entry(2,3)*entry(3,0))
                          +entry(1,3)*(entry(2,0)*entry(3,1) - entry(2,1)*entry(3,0)))
              -entry(0,3)*(entry(1,0)*(entry(2,1)*entry(3,2) - entry(2,2)*entry(3,1))
                          -entry(1,1)*(entry(2,0)*entry(3,2) - entry(2,2)*entry(3,0))
                          +entry(1,2)*(entry(2,0)*entry(3,1) - entry(2,1)*entry(3,0)));
    }
    inline float trace() const {
        return entry(0,0)+entry(1,1)+entry(2,2)+entry(3,3);
    }

    // Solve for x in Ax = b.
    vec4 solve(vec4 b) const;

    static mat4x4 identity() {
        return mat4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    }

    // Transformations.
    static mat4x4 orthogonal_projection(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z);
    static mat4x4 to_rigid_frame(vec3 origin, vec3 X, vec3 Y, vec3 Z);
    static mat4x4 translation(vec3 amount);
    static mat4x4 translation(float x, float y, float z);
    static mat4x4 scale(float x, float y, float z);
    static mat4x4 scale(float x);

    mat4x4 inverse() const;

    // Extract the top left 3x3 matrix.
    inline mat3x3 top_left() const {
        return mat3x3(entry(0,0), entry(1,0), entry(2,0),
                      entry(0,1), entry(1,1), entry(2,1), 
                      entry(0,2), entry(1,2), entry(2,2));
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



struct mat2x2;
inline mat2x2 operator*(float x, mat2x2 M);
struct mat2x2 {
    float entries[4];
    // Constructor with column-major parameter order.
    mat2x2(float e00, float e10,
           float e01, float e11)
    : entries{e00,e10,
              e01,e11} {}
    // Constructor with column-major float array.
    mat2x2(float _entries[/*4*/]) {
        memcpy(entries, _entries, sizeof(entries));
    }
    // Constructor from three column vectors.
    mat2x2(vec2 c0, vec2 c1) :
        mat2x2(c0.x(), c0.y(),
               c1.x(), c1.y())
    {}
    mat2x2() {}
    inline float entry(int i, int j) const {
        return entries[2*j + i];
    }
    inline float &entry(int i, int j) {
        return entries[2*j + i];
    }

    // Extract columns.
    inline vec2 column(int j) const {
        return *((vec2 *) &entries[2*j]);
    }
    // Extract rows.
    inline vec2 row(int i) const {
        return vec2(entries[2*0 + i],
                    entries[2*1 + i]);
    }

    inline mat2x2 transpose() const {
        return mat2x2(entry(0,0),entry(0,1),
                      entry(1,0),entry(1,1));
    }
    static mat2x2 identity() {
        return mat2x2(1,0, 0,1);
    }

    inline float determinant() const {
        return entry(0,0)*entry(1,1) - entry(0,1)*entry(1,0);
    }
    inline float trace() const {
        return entry(0,0)+entry(1,1);
    }

    inline mat2x2 inverse() const {
        return (1.f / determinant()) * mat2x2(entry(1,1), -entry(0,1), -entry(1,0), entry(0,0));
    }

    std::pair<mat2x2,mat2x2> diagonalize() const;
};
// Matrix vector multiplication.
inline vec2 operator*(mat2x2 M, vec2 v) {
    return vec2(M.entry(0,0)*v[0] + M.entry(0,1)*v[1],
                M.entry(1,0)*v[0] + M.entry(1,1)*v[1]);
}
// Matrix multiplication.
inline mat2x2 operator*(mat2x2 A, mat2x2 B) {
    return mat2x2(
        // A acting on B's first column.
        A.entry(0,0)*B.entry(0, 0) + A.entry(0,1)*B.entry(1, 0),
        A.entry(1,0)*B.entry(0, 0) + A.entry(1,1)*B.entry(1, 0),
        // A acting on B's second column.
        A.entry(0,0)*B.entry(0, 1) + A.entry(0,1)*B.entry(1, 1),
        A.entry(1,0)*B.entry(0, 1) + A.entry(1,1)*B.entry(1, 1)
    );
}

inline mat2x2 operator*(float x, mat2x2 M) {
    M.entry(0,0) *= x;
    M.entry(0,1) *= x;
    M.entry(1,0) *= x;
    M.entry(1,1) *= x;
    return M;
}

std::ostream &operator<<(std::ostream &os, const mat2x2 &M);




#endif // SPATIAL_ALGEBRA_MAT4X4_H
