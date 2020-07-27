#include "mathematics/mathematics.h"

std::ostream &operator<<(std::ostream &os, const mat4x4 &M)
{
    int max_entry_len = 0;
    for (int i = 0; i < 16; i++) {
        int len = std::to_string(M.entries[i]).length();
        if (len > max_entry_len) max_entry_len = len;
    }
    for (int i = 0; i < 4; i++) {
        os << "|";
        for (int j = 0; j < 4; j++) {
            std::string str = std::to_string(M.entry(i,j));
            int len = str.length();
            os << str;
            if (j < 3) os << ",";
            for (int k = 0; k < max_entry_len - len; k++) os << " ";
        }
        os << "|\n";
    }
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
