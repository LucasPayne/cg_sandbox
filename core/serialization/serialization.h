#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <vector>
#include <iostream>

#define DECLARE_BASIC_TYPE(TYPENAME)\
    void pack(TYPENAME &obj, std::ostream &out);\
    void unpack(std::istream &in, TYPENAME &obj);\
    void print(TYPENAME &obj);

#define BASIC_TYPE(TYPENAME)\
    void pack(TYPENAME &obj, std::ostream &out) {\
        out.write((char *)&obj, sizeof(TYPENAME));\
    }\
    void unpack(std::istream &in, TYPENAME &obj) {\
        in.read((char *)&obj, sizeof(TYPENAME));\
    }\
    void print(TYPENAME &obj) {\
        std::cout << #TYPENAME ": " << obj;\
    }

DECLARE_BASIC_TYPE(int);
DECLARE_BASIC_TYPE(float);
DECLARE_BASIC_TYPE(double);
DECLARE_BASIC_TYPE(bool);
DECLARE_BASIC_TYPE(char);
DECLARE_BASIC_TYPE(uint8_t);
DECLARE_BASIC_TYPE(uint16_t);
DECLARE_BASIC_TYPE(uint32_t);
DECLARE_BASIC_TYPE(uint64_t);

#endif // SERIALIZATION_H
