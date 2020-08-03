#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <vector>
#include <iostream>
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
// Marker so that it is easy for the tool to find entries.
#define ENTRY

/*--------------------------------------------------------------------------------
    Definitions
--------------------------------------------------------------------------------*/
BASIC_TYPE(int);
BASIC_TYPE(float);
BASIC_TYPE(double);
BASIC_TYPE(bool);
BASIC_TYPE(char);
// uint8_t is an exception, since iostream treats it as a char by default.
void pack(uint8_t &obj, std::ostream &out) {
    out.write((char *)&obj, 1);
}
void unpack(std::istream &in, uint8_t &obj) {
    in.read((char *)&obj, 1);
}
void print(uint8_t &obj) {
    std::cout << "uint8_t: " << (unsigned int)obj;
}
BASIC_TYPE(uint16_t);
BASIC_TYPE(uint32_t);
BASIC_TYPE(uint64_t);

// std::string
void pack(std::string &obj, std::ostream &out) {
    // The string length is packed at the start.
    size_t string_length = obj.length();
    out.write((char *)&string_length, sizeof(size_t));
    out.write((char *)obj.c_str(), string_length);
}
void unpack(std::istream &in, std::string &obj)
{
    size_t string_length;
    in.read((char *)&string_length, sizeof(size_t));
    obj = std::string(string_length, '\0');
    in.read((char *)obj.c_str(), string_length);
}
void print(std::string &obj)
{
    std::cout << "string<" << obj << ">";
}

#endif // SERIALIZATION_H
