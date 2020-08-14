#include "reflector.h"
#include <iomanip> // Input-output manipulators. Used to set decimal places in output floats.
#include <map>


/*--------------------------------------------------------------------------------
TypeDescriptor_Struct
--------------------------------------------------------------------------------*/
void TypeDescriptor_Struct::print(uint8_t &obj, std::ostream &out, int indent_level) const
{
    out << name() << "{\n";
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
DESCRIPTOR_INSTANCE(float);
REFLECT_PRIMITIVE_PRINT(float)
{
    float val = *((float *) &obj);
    out << name() << "{" << std::fixed << std::setprecision(6) << val << "}";
}
REFLECT_PRIMITIVE_FLAT(float);

DESCRIPTOR_INSTANCE(bool);
REFLECT_PRIMITIVE_PRINT(bool)
{
    bool val = *((bool *) &obj);
    out << name() << "{" << (val ? "True" : "False") << "}";
}
REFLECT_PRIMITIVE_FLAT(bool);

DESCRIPTOR_INSTANCE(int);
REFLECT_PRIMITIVE_PRINT(int)
{
    int val = *((int *) &obj);
    out << name() << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(int);

DESCRIPTOR_INSTANCE(uint8_t);
REFLECT_PRIMITIVE_PRINT(uint8_t)
{
    uint8_t val = *((uint8_t *) &obj);
    out << name() << "{" << (unsigned int) val << "}"; // Needs to be cast or it will be treated as a char.
}
REFLECT_PRIMITIVE_FLAT(uint8_t);

DESCRIPTOR_INSTANCE(uint16_t);
REFLECT_PRIMITIVE_PRINT(uint16_t)
{
    uint16_t val = *((uint16_t *) &obj);
    out << name() << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint16_t);

DESCRIPTOR_INSTANCE(uint32_t);
REFLECT_PRIMITIVE_PRINT(uint32_t)
{
    uint32_t val = *((uint32_t *) &obj);
    out << name() << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint32_t);

DESCRIPTOR_INSTANCE(uint64_t);
REFLECT_PRIMITIVE_PRINT(uint64_t)
{
    uint64_t val = *((uint64_t *) &obj);
    out << name() << "{" << val << "}";
}
REFLECT_PRIMITIVE_FLAT(uint64_t);




/*--------------------------------------------------------------------------------
Definitions for the standard non-basic primitive types.
--------------------------------------------------------------------------------*/
DESCRIPTOR_INSTANCE(std::string);
REFLECT_PRIMITIVE_PRINT(std::string)
{
    std::string &str = (std::string &) obj;
    out << name() << "(\"" << str << "\")";
}
REFLECT_PRIMITIVE_PACK(std::string)
{
    std::string &str = (std::string &) obj;
    size_t length = str.length();
    out.write((char *)&length, sizeof(size_t));
    out.write(str.c_str(), sizeof(char)*length);
}
REFLECT_PRIMITIVE_UNPACK(std::string)
{
    size_t length;
    in.read((char *)&length, sizeof(size_t));
    std::string str(length, '\0');
    in.read(&str[0], sizeof(char)*length);

    *((std::string *) &obj) = str;
}


/*--------------------------------------------------------------------------------
Type descriptor registration.
--------------------------------------------------------------------------------*/
namespace Reflector {


std::map<std::string, TypeDescriptor *> &DescriptorMap::name_to_type()
{
    static std::map<std::string, TypeDescriptor *> _name_to_type;
    return _name_to_type;
}

TypeDescriptor *DescriptorMap::get(const std::string &name)
{
    auto found = DescriptorMap::name_to_type().find(name);
    if (found == DescriptorMap::name_to_type().end()) {
        std::cerr << "ERROR: Searched for non-registered type \"" << name << "\"\n";
        exit(EXIT_FAILURE);
    }
    return found->second;
}

void DescriptorMap::register_descriptor(TypeDescriptor *desc)
{
    // Order of static initialization is arbitrary, so initialize the global map when the first descriptor
    // is registered. This ensures it exists before all registrations.
        
    std::string name = desc->name();
    printf("[reflector] Registering type \"%s\".\n", name.c_str());
    auto found = name_to_type().find(name);
    if (found != name_to_type().end()) {
        printf("[reflector] Type \"%s\" is already registered.\n", name.c_str());
        return;
    }
    name_to_type()[name] = desc;
}



} // end namespace Reflector
