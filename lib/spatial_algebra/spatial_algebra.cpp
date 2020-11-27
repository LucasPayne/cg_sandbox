#include "spatial_algebra.h"
#include <iostream>



static void _print_matrix_3x3_4x4(std::ostream &os, const float *entries, int n)
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
    _print_matrix_3x3_4x4(os, M.entries, 4);
    return os;
}


std::ostream &operator<<(std::ostream &os, const mat3x3 &M)
{
    _print_matrix_3x3_4x4(os, M.entries, 3);
    return os;
}

std::ostream &operator<<(std::ostream &os, const vec2 &v)
{
    os << "(" << v.x() << ", " << v.y() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const vec4 &v)
{
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, const Quaternion &q)
{
    os << "Quaternion(" << q.scalar() << ", " << q.i() << ", " << q.j() << ", " << q.k() << ")";
    return os;
}


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
    // Maps the x and y ranges to [-1, 1] and the z range to [0, 1].
    // This orthogonal projection is axis aligned. Compose with a rigid transform to get an arbitrary orthogonal projection.
    return mat4x4::row_major(
        2.f / (max_x - min_x), 0, 0, 0,
        0, 2.f / (max_y - min_y), 0, 0,
        0, 0, 1.f / (max_z - min_z), 0,
        0,0,0,1
    ) * mat4x4::translation(vec3(-0.5*(min_x+max_x), -0.5*(min_y+max_y), -min_z));
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
