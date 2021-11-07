#include "spatial_algebra.h"
#include <iostream>
#include <math.h>
#include <assert.h>
#include <iomanip>

static void _print_matrix(std::ostream &os, const float *entries, int n)
{
    int max_entry_len = 0;
    for (int i = 0; i < n*n; i++) {
        int len = std::to_string(entries[i]).length();
        if (len > max_entry_len) max_entry_len = len;
    }
    for (int i = 0; i < n; i++) {
        os << "|";
        for (int j = 0; j < n; j++) {
            std::string str = std::to_string(entries[n*j + i]);
            int len = str.length();
            os << str;
            if (j < n-1) os << ",";
            for (int k = 0; k < max_entry_len - len; k++) os << " ";
        }
        os << "|\n";
    }
}


std::ostream &operator<<(std::ostream &os, const mat4x4 &M)
{
    _print_matrix(os, M.entries, 4);
    return os;
}


std::ostream &operator<<(std::ostream &os, const mat3x3 &M)
{
    _print_matrix(os, M.entries, 3);
    return os;
}

std::ostream &operator<<(std::ostream &os, const mat2x2 &M)
{
    _print_matrix(os, M.entries, 2);
    return os;
}

std::ostream &operator<<(std::ostream &os, const vec2 &v)
{
    os << std::setprecision(4) << "(" << v.x() << ", " << v.y() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    os << std::setprecision(4) << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const vec4 &v)
{
    os << std::setprecision(4) << "(" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const Quaternion &q)
{
    os << std::setprecision(4) << "Quaternion(" << q.scalar() << ", " << q.i() << ", " << q.j() << ", " << q.k() << ")";
    return os;
}

// note: I do not think this is stable.
vec4 mat4x4::solve(vec4 b) const
{
    #define SINGULAR() {\
        fprintf(stderr, "[spatial_algebra] ERROR: Singular matrix in mat4x4::solve.\n");\
        exit(EXIT_FAILURE);\
    }

    mat4x4 M = *this;

    for (int col = 0; col < 3; col++) {
        // Find the element with greatest absolute value to pivot on.
        float biggest = 0.f;
        int pivot_row = -1;
        for (int row = 0; row < 4; row++) {
            if (fabs(M.entry(row, col)) > biggest) {
                biggest = fabs(M.entry(row, col));
                pivot_row = row;
            }
        }
        if (pivot_row < 0) SINGULAR();
        // Swap rows to put this pivot on the diagonal.
        if (pivot_row != col) {
            std::swap(b.entries[pivot_row], b.entries[col]);
            for (int j = 0; j < 4; j++) {
                std::swap(M.entry(pivot_row, j), M.entry(col, j));
            }
        }

        // Scale this row to make the pivot element 1.
        float inv_pivot = 1.f / M.entry(col, col);
        b.entries[col] *= inv_pivot;
        M.entry(col, col) = 1.f;
        for (int j = col+1; j < 4; j++) {
            M.entry(col, j) *= inv_pivot;
        }

        // Nullify the entries in this column below the diagonal.
        for (int row = col+1; row < 4; row++) {
	    float x = M.entry(row, col);
            M.entry(row, col) = 0.f;
            b.entries[row] -= x * b.entries[col];
            for (int j = col+1; j < 4; j++) {
                M.entry(row, j) -= x * M.entry(col, j);
            }
        }
    }
    if (M.entry(3,3) == 0) SINGULAR();
    float inv_last_pivot = 1.f / M.entry(3,3);
    M.entry(3,3) = 1.f;
    b.entries[3] *= inv_last_pivot;

    // Solve by back-substitution.
    vec4 solution;
    solution.entries[3] = b.entries[3];
    solution.entries[2] = b.entries[2] - M.entry(2,3) * solution.entries[3];
    solution.entries[1] = b.entries[1] - M.entry(1,2) * solution.entries[2] - M.entry(1,3) * solution.entries[3];
    solution.entries[0] = b.entries[0] - M.entry(0,1) * solution.entries[1] - M.entry(0,2) * solution.entries[2] - M.entry(0,3) * solution.entries[3];

    return solution;
}


mat4x4 mat4x4::inverse() const {
    // Not very efficient.
    mat4x4 inv;
    for (int i = 0; i < 4; i++) {
        vec4 e = vec4::zero();
        e.entries[i] = 1;
        vec4 col = solve(e);
        for (int j = 0; j < 4; j++) {
            inv.entry(j, i) = col.entries[j];
        }
    }
    return inv;
}



mat4x4 mat4x4::translation(vec3 amount)
{
    return mat4x4::row_major(1,0,0,amount.x(),
                             0,1,0,amount.y(),
                             0,0,1,amount.z(),
                             0,0,0,1);
}
mat4x4 mat4x4::translation(float x, float y, float z)
{
    return mat4x4::row_major(1,0,0,x,
                             0,1,0,y,
                             0,0,1,z,
                             0,0,0,1);
}


mat4x4 mat4x4::to_rigid_frame(vec3 origin, vec3 X, vec3 Y, vec3 Z)
{
    // X,Y,Z must be orthonormal.
    return mat4x4::row_major(
        X.x(), X.y(), X.z(), 0,
        Y.x(), Y.y(), Y.z(), 0,
        Z.x(), Z.y(), Z.z(), 0,
        0,0,0,1
    ) * mat4x4::translation(-origin);
}

mat4x4 mat4x4::orthogonal_projection(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z)
{
    // Maps the x, y, z ranges to [-1, 1].
    // This orthogonal projection is axis aligned. Compose with a rigid transform to get an arbitrary orthogonal projection.
    return mat4x4::row_major(
        2.f / (max_x - min_x), 0, 0, 0,
        0, 2.f / (max_y - min_y), 0, 0,
        0, 0, 2.f / (max_z - min_z), 0,
        0,0,0,1
    ) * mat4x4::translation(vec3(-0.5*(min_x+max_x), -0.5*(min_y+max_y), -0.5*(min_z+max_z)));
}

mat4x4 mat4x4::scale(float x, float y, float z)
{
    return mat4x4::row_major(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0,0,0,1
    );
}
mat4x4 mat4x4::scale(float x)
{
    return mat4x4::row_major(
        x, 0, 0, 0,
        0, x, 0, 0,
        0, 0, x, 0,
        0,0,0,1
    );
}

mat4x4 Quaternion::matrix()
{
    auto inv = inverse();
    Quaternion q1 = *this * Quaternion(0,1,0,0) * inv;
    Quaternion q2 = *this * Quaternion(0,0,1,0) * inv;
    Quaternion q3 = *this * Quaternion(0,0,0,1) * inv;

    return mat4x4(q1.i(), q1.j(), q1.k(),0,
                  q2.i(), q2.j(), q2.k(),0,
                  q3.i(), q3.j(), q3.k(),0,
                  0,0,0,1);
};



std::pair<mat2x2,mat2x2> mat2x2::diagonalize() const
{
    const float A = entry(0,0);
    const float B = entry(0,1);
    const float C = entry(1,0);
    const float D = entry(1,1);

    float discrim = (A + D)*(A + D) - 4*(A*D - B*C);
    assert(discrim >= 0);
    float half_sqrt_discrim = 0.5 * sqrt(discrim);
    float base_root = 0.5 * (A + D);
    float l1 = base_root - half_sqrt_discrim;
    float l2 = base_root + half_sqrt_discrim;
    mat2x2 Vals = mat2x2(l1, 0, 0, l2);
    mat2x2 Vecs = mat2x2(vec2(B, l1 - A).normalized(),
                         vec2(B, l2 - A).normalized());
    return std::pair<mat2x2,mat2x2>(Vecs, Vals);
}


mat3x3 vec3::outer(vec3 a, vec3 b)
{
    return mat3x3(
        a.x()*b.x(), a.y()*b.x(), a.z()*b.x(),
        a.x()*b.y(), a.y()*b.y(), a.z()*b.y(),
        a.x()*b.z(), a.y()*b.z(), a.z()*b.z()
    );
}

