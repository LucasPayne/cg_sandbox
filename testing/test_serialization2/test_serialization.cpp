#include "core.h"
#include "serialization/serialization.h"

#define SERIALIZE
#define ENTRY

SERIALIZE struct SomeBase {
    ENTRY uint8_t p;
};
void pack(SomeBase &obj, std::ostream &out) {
    pack(obj.p, out);
}
void unpack(std::istream &in, SomeBase &obj) {
    unpack(in, obj.p);
}
void print(SomeBase &obj) {
    print(obj.p);
}

SERIALIZE struct Test1 : public SomeBase {
    ENTRY float x;
    ENTRY float y;
    ENTRY int a;
    ENTRY std::string some_string;
    ENTRY uint16_t b;
};
void pack(Test1 &obj, std::ostream &out) {
    pack((SomeBase &)obj, out);
    pack(obj.x, out);
    pack(obj.y, out);
    pack(obj.a, out);
    pack(obj.some_string, out);
    pack(obj.b, out);
}
void unpack(std::istream &in, Test1 &obj) {
    unpack(in, (SomeBase &)obj);
    unpack(in, obj.x);
    unpack(in, obj.y);
    unpack(in, obj.a);
    unpack(in, obj.some_string);
    unpack(in, obj.b);
}
void print(Test1 &obj) {
    std::cout << "Test1: ";
    std::cout << "BASE{";
    print((SomeBase &)obj);
    std::cout << "} {";
    print(obj.x);
    std::cout << ", ";
    print(obj.y);
    std::cout << ", ";
    print(obj.a);
    std::cout << ", ";
    print(obj.some_string);
    std::cout << ", ";
    print(obj.b);
    std::cout << "}";
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
    t1.some_string = "beam me";
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

    int n2 = 5;
    std::vector<Test1> vec2(n2);
    for (int i = 0; i < n2; i++) {
        vec2[i].x = i+0.1;
        vec2[i].y = -2*i-0.1;
        vec2[i].a = -10;
        vec2[i].some_string = "nice-" + std::to_string(i);
        vec2[i].b = i % 2;
    }
    print(vec2);
    printf("\n");
    std::vector<Test1> vec2_t = transporter(vec2);
    print(vec2_t);
    printf("\n");
}
