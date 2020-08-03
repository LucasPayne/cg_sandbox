#include "core.h"
#include "serialization/serialization.h"

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
