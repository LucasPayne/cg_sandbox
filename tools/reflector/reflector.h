#ifndef REFLECTOR_H
#define REFLECTOR_H
/*================================================================================
    Reflection
references:
    Very much based on ideas described in:
        https://preshing.com/20180116/a-primitive-reflection-system-in-cpp-part-1/
    with some modifications to the macros needed.
================================================================================*/
#include <iostream>
#include <vector>
#include <iomanip> // Input-output manipulators. Used to set decimal places in output floats.
#include <stdint.h>


/*--------------------------------------------------------------------------------
TypeDescriptor
    The abstract base class of all type descriptors. Type operations (such as print)
    are declared here.

    This is the interface through which types will be used at run-time.
--------------------------------------------------------------------------------*/
struct TypeDescriptor {
    size_t size;
    const char *name;

    TypeDescriptor(size_t _size, const char *_name) :
        size{_size}, name{_name}
    {}
    TypeDescriptor() {}

    virtual void print(uint8_t &obj) const = 0;
    virtual void pack(uint8_t &obj, std::ostream &out) const = 0;
    virtual void unpack(std::istream &in, uint8_t &obj) const = 0;
};


/*--------------------------------------------------------------------------------
TypeDescriptor_Struct
    This concrete type descriptor class describes a struct type, which consists
    of information about the names and offsets of its entries.

    There is a collection of macros to make it easy to define a new global
    TypeDescriptor_Struct instance for a specific type, which is obtainable through
    TypeDescriptorOf().
--------------------------------------------------------------------------------*/
struct TypeDescriptor_Struct : public TypeDescriptor {
    struct StructEntry {
        const char *name;
        size_t offset;
        TypeDescriptor *type;
    };
    std::vector<StructEntry> entries;
    TypeDescriptor_Struct() {}

    virtual void print(uint8_t &obj) const {
        std::cout << name << "{\n";
        for (const StructEntry &entry : entries) {
            entry.type->print((&obj)[entry.offset]);
        }
        std::cout << "}";
    }
    virtual void pack(uint8_t &obj, std::ostream &out) const {

    }
    virtual void unpack(std::istream &in, uint8_t &obj) const {

    }
};


/*--------------------------------------------------------------------------------
Get the type descriptor of the template parameter type.

Example usage:
    TypeDescriptorOf<int>()->print(...)
--------------------------------------------------------------------------------*/
// There is no generic implementation of this --- it must only be specialized for each primitive type.
template <typename TYPE>
TypeDescriptor *TypeDescriptorOf();




//================================================================================
// MACROS
//================================================================================
/*--------------------------------------------------------------------------------
Primitive reflection macros.
A "primitive" is anything that is not a struct. This means that it actually
needs specialized definitions for things such as printing.
Example:
    REFLECT_PRIMITIVE(float);
    REFLECT_PRIMITIVE_PRINT(float) {
        ... use the data in lvalue "obj" to print out a representation ...
    }
--------------------------------------------------------------------------------*/
// Dummy template that helps with these macro definitions.
template <typename TYPE>
struct PrimitiveTypeDescriptor;


// Header file.
#define REFLECT_PRIMITIVE(TYPE)\
    template <>\
    struct PrimitiveTypeDescriptor<TYPE> : public TypeDescriptor {\
        PrimitiveTypeDescriptor() : TypeDescriptor{sizeof(TYPE), #TYPE} {}\
        virtual void print(uint8_t &obj) const;\
        virtual void pack(uint8_t &obj, std::ostream &out) const;\
        virtual void unpack(std::istream &in, uint8_t &obj) const;\
    };\
    template <>\
    TypeDescriptor *TypeDescriptorOf<TYPE>();


// Implementations file.
#define REFLECT_PRIMITIVE_GETTER(TYPE)\
    template <>\
    TypeDescriptor *TypeDescriptorOf<TYPE>() {\
        static PrimitiveTypeDescriptor<TYPE> desc;\
        return &desc;\
    }


#define REFLECT_PRIMITIVE_PRINT(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::print(uint8_t &obj) const


// Many primitive types will be simple flat data types, meaning their binary pack/unpack functions
// just write and read the data as-is. 
#define REFLECT_PRIMITIVE_FLAT(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::pack(uint8_t &obj, std::ostream &out) const {\
        out.write((char *)&obj, sizeof(TYPE));\
    }\
    void PrimitiveTypeDescriptor<TYPE>::unpack(std::istream &in, uint8_t &obj) const {\
        in.read((char *)&obj, sizeof(TYPE));\
    }


/*--------------------------------------------------------------------------------
Struct reflection macros.
Example:
    REFLECT_STRUCT(vec3)
        STRUCT_ENTRY(x)
        STRUCT_ENTRY(y)
        STRUCT_ENTRY(z)
    END_REFLECT_STRUCT()
--------------------------------------------------------------------------------*/
#define REFLECT_STRUCT(STRUCT_NAME)\
    template <>\
    TypeDescriptor *TypeDescriptorOf<STRUCT_NAME>() {\
        static TypeDescriptor_Struct desc;\
        desc.name = #STRUCT_NAME;\
        using TYPE = STRUCT_NAME;\
        desc.size = sizeof(TYPE);\
        desc.entries = {\

#define STRUCT_ENTRY(ENTRY_NAME)\
            {#ENTRY_NAME, offsetof(TYPE, ENTRY_NAME), TypeDescriptorOf<decltype(TYPE:: ENTRY_NAME)>()},

#define END_REFLECT_STRUCT()\
        };\
        return &desc;\
    }




/*================================================================================
Declarations of the basic C++ types.
These are included here for convenience, since they will most likely be needed.
================================================================================*/
REFLECT_PRIMITIVE(float);
REFLECT_PRIMITIVE(bool);
REFLECT_PRIMITIVE(int);
REFLECT_PRIMITIVE(uint8_t);
REFLECT_PRIMITIVE(uint16_t);
REFLECT_PRIMITIVE(uint32_t);
REFLECT_PRIMITIVE(uint64_t);
//--------------------------------------------------------------------------------

#endif // REFLECTOR_H
