#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <vector>
#include <iostream>
#include <functional>
/*--------------------------------------------------------------------------------
    Typedefs for serialization functions.
--------------------------------------------------------------------------------*/
template <typename T>
using PackFunction = void (*)(T &, std::ostream &);
template <typename T>
using UnpackFunction = void (*)(std::istream &, T &);
template <typename T>
using PrintFunction = void (*)(T &);


// To dynamically serialize different types, a generic interface is needed.
// Serialization functions can be converted to a generic byte-serializing function
// with the methods below.
typedef std::function<void(uint8_t &, std::ostream &)> GenericPackFunction;
typedef std::function<void(std::istream &, uint8_t &)> GenericUnpackFunction;
typedef std::function<void(uint8_t &)> GenericPrintFunction;

// These methods are used to convert a serialization function into a generic version that
// serializes bytes.
template <typename T>
GenericPackFunction generic_pack()
{
    return [](uint8_t &bytes, std::ostream &out) {
        pack(reinterpret_cast<T &>(bytes), out);
    };
}
template <typename T>
GenericUnpackFunction generic_unpack()
{
    return [](std::istream &in, uint8_t &bytes) {
        unpack(in, reinterpret_cast<T &>(bytes));
    };
}
template <typename T>
GenericPrintFunction generic_print()
{
    return [](uint8_t &bytes) {
        print(reinterpret_cast<T &>(bytes));
    };
}


/*--------------------------------------------------------------------------------
    Declarations
--------------------------------------------------------------------------------*/
#define DECLARE_TYPE(TYPENAME)\
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

DECLARE_TYPE(int);
DECLARE_TYPE(float);
DECLARE_TYPE(double);
DECLARE_TYPE(bool);
DECLARE_TYPE(char);
DECLARE_TYPE(uint8_t);
DECLARE_TYPE(uint16_t);
DECLARE_TYPE(uint32_t);
DECLARE_TYPE(uint64_t);

// Standard non-basic types.
using std::string;
DECLARE_TYPE(string);

// Templated container types.
// std::vector
template <typename T>
void pack(std::vector<T> &obj, std::ostream &out) {
    // Pack the vector length at the start.
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

// Dummy struct used to flag struct/class declarations for the code generator.
// Serialized structs/classes must derive from this.
struct SERIALIZE {};


#endif // SERIALIZATION_H
