#include "core.h"
#include "serialization/serialization.h"

struct Test1 {
    float x;
    float y;
    int a;
    uint16_t b;
};
void pack(Test1 &obj, std::ostream &out) {
    pack(obj.x, out);
    pack(obj.y, out);
    pack(obj.a, out);
    pack(obj.b, out);
}
void unpack(std::istream &in, Test1 &obj) {
    unpack(in, obj.x);
    unpack(in, obj.y);
    unpack(in, obj.a);
    unpack(in, obj.b);
}
void print(Test1 &obj) {
    std::cout << "Test1: {";
    print(obj.x);
    std::cout << ", ";
    print(obj.y);
    std::cout << ", ";
    print(obj.a);
    std::cout << ", ";
    print(obj.b);
    std::cout << "}";
}

template <typename T>
void pack(std::vector<T> &obj, std::ostream &out) {
    size_t vector_length = obj.size();
    out.write((char *)&vector_length, sizeof(size_t));
    for (T &entry : obj) {
        pack(entry, out);
    }
}
template <typename T>
void unpack(std::istream &in, std::vector<T> &obj) {
    size_t vector_length;
    in.read((char *)&vector_length, sizeof(size_t));
    obj = std::vector<T>(vector_length);
    for (T &entry : obj) {
        unpack(in, entry);
    }
}
template <typename T>
void print(std::vector<T> &obj) {
    std::cout << "vector[";
    for (T &entry : obj) {
        print(entry);
        std::cout << ", ";
    }
    std::cout << "]";
}



template <typename T>
T transporter(T &obj) {
    std::ofstream outfile;
    outfile.open("test.binary", std::ios::trunc);
    pack(obj, outfile);
    outfile.close();
    
    std::ifstream infile;
    T transportered_obj;
    infile.open("test.binary");
    unpack(infile, transportered_obj);
    infile.close();
    return transportered_obj;
}

int main(void)
{
    Test1 t1;
    t1.x = 0.3;
    t1.y = -0.89;
    t1.a = -32;
    t1.b = 7;
    print(t1);
    printf("\n");
    Test1 t1_t = transporter(t1);
    print(t1_t);
    printf("\n");

    int n1 = 8;
    std::vector<int> vec1(n1);
    for (int i = 0; i < n1; i++) {
        vec1[i] = 5*(i+1);
    }
    print(vec1);
    printf("\n");
    std::vector<int> vec1_t = transporter(vec1);
    print(vec1_t);
    printf("\n");

}
