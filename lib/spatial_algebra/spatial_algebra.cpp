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


vec4 mat4x4::solve(vec4 b) const {

    std::cout << "Solving:\n" << *this << "\n";
    getchar();

    // Keep track of the row permutations so the solution vector can be permuted at the end.
    int row_permutation[4] = {0,1,2,3};

    mat4x4 M = *this;
    for (int col = 0; col < 4; col++) {
        // Permute the rows with non-zeroes on this column to the top.
        int last_non_zero_row = -1;
        bool update_last_non_zero_row = true;
        for (int row = 3; row >= 0; --row) {
            if (M.entry(row, col) != 0) {
                // Initialize last_non_zero_row.
                if (update_last_non_zero_row) {
                    last_non_zero_row = row;
                    update_last_non_zero_row = false;
                }
            } else if (last_non_zero_row >= 0) {
                // Swap the last non-zero row with this row. The end of this process should leave
                // the non-zero rows at the top.
                vec4 temp = M.row(last_non_zero_row);
                std::cout << temp << "\n";
                for (int j = 0; j < 4; j++) M.entry(last_non_zero_row, j) = M.entry(row, j);
                for (int j = 0; j < 4; j++) M.entry(row, j) = temp.entries[j];
                std::swap(row_permutations[last_non_zero_row, row]);
                last_non_zero_row -= 1;
            }
        }
        std::cout << "Sorted:\n" << M << "\n";
        getchar();

        float inv_pivot = 1.0 / M.entry(col, col);
        for (int row = col; row <= last_non_zero_row; row++) {
            
        }
    }

    return vec4::zero();
}


// vec4 mat4x4::solve(vec4 b) const {
//     // Uses Cramer's rule.
//     vec4 solution;
//     mat4x4 new_matrix = *this;
//     float inv_det = 1.0 / determinant();
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             new_matrix.entry(i, j) = b.entries[j];
//         }
//         // Put back the original column that the previous iteration replaced.
//         if (i > 0) {
//             for (int j = 0; j < 4; j++) {
//                 new_matrix.entry(i-1, j) = entry(i-1, j);
//             }
//         }
//         float x = new_matrix.determinant();
//         solution.entries[i] = x * inv_det;
//     }
//     return solution;
// }
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

