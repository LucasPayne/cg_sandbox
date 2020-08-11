#include "reflector.h"

/*--------------------------------------------------------------------------------
TypeDescriptor_Struct
--------------------------------------------------------------------------------*/
void TypeDescriptor_Struct::print(uint8_t &obj, std::ostream &out, int indent_level) const {
    out << name << "{\n";
    for (const StructEntry &entry : entries) {
        out << std::string(4*(indent_level+1), ' ') << entry.name << ": ";
        entry.type->print((&obj)[entry.offset], out, indent_level + 1);
        out << "\n";
    }
    out << std::string(4*indent_level, ' ') << "}";
}
void TypeDescriptor_Struct::pack(uint8_t &obj, std::ostream &out) const
{
    for (const StructEntry &entry : entries) {
        entry.type->pack((&obj)[entry.offset], out);
    }
}
void TypeDescriptor_Struct::unpack(std::istream &in, uint8_t &obj) const
{
    for (const StructEntry &entry : entries) {
        entry.type->unpack(in, (&obj)[entry.offset]);
    }
}



/*--------------------------------------------------------------------------------
Definitions for the basic C++ types.
--------------------------------------------------------------------------------*/
REFLECT_PRIMITIVE_GETTER(float);
REFLECT_PRIMITIVE_PRINT(float) {
    float val = *((float *) &obj);
    out << name << "{" << std::fixed << std::setprecision(6) << val << "}";
}
REFLECT_PRIMITIVE_FLAT(float);

REFLECT_PRIMITIVE_GETTER(bool);
REFLECT_PRIMITIVE_PRINT(bool) {
    bool val = *((bool *) &obj);
    out << name << "{" << (val ? "True" : "False") << "}";
}
REFLECT_PRIMITIVE_FLAT(bool);

REFLECT_PRIMITIVE_GETTER(int);
REFLECT_PRIMITIVE_PRINT(int) {
    int val = *((int *) &obj);
    out << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(int);

REFLECT_PRIMITIVE_GETTER(uint8_t);
REFLECT_PRIMITIVE_PRINT(uint8_t) {
    uint8_t val = *((uint8_t *) &obj);
    out << name << "{" << (unsigned int) val << "}"; // Needs to be cast or it will be treated as a char.
}
REFLECT_PRIMITIVE_FLAT(uint8_t);

REFLECT_PRIMITIVE_GETTER(uint16_t);
REFLECT_PRIMITIVE_PRINT(uint16_t) {
    uint16_t val = *((uint16_t *) &obj);
    out << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint16_t);

REFLECT_PRIMITIVE_GETTER(uint32_t);
REFLECT_PRIMITIVE_PRINT(uint32_t) {
    uint16_t val = *((uint32_t *) &obj);
    out << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint32_t);

REFLECT_PRIMITIVE_GETTER(uint64_t);
REFLECT_PRIMITIVE_PRINT(uint64_t) {
    uint16_t val = *((uint64_t *) &obj);
    out << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint64_t);



/*--------------------------------------------------------------------------------
Definitions for the standard non-basic primitive types.
--------------------------------------------------------------------------------*/
