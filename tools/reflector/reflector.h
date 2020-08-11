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
#include <string>
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

    virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const = 0;
    virtual void pack(uint8_t &obj, std::ostream &out) const = 0;
    virtual void unpack(std::istream &in, uint8_t &obj) const = 0;
};


/*--------------------------------------------------------------------------------
TypeDescriptor_Struct
    This concrete type descriptor class describes a struct type, which consists
    of information about the names and offsets of its entries.

    There is a collection of macros to make it easy to define a new global
    TypeDescriptor_Struct instance for a specific type, which is obtainable through
    TypeDescriptorGiver<T>::get().
--------------------------------------------------------------------------------*/
struct TypeDescriptor_Struct : public TypeDescriptor {
    // reference: https://github.com/preshing/FlexibleReflection/blob/part1/Reflect.h

    struct StructEntry {
        const char *name;
        size_t offset;
        TypeDescriptor *type;
    };
    std::vector<StructEntry> entries;
    TypeDescriptor_Struct() {}

    virtual void print(uint8_t &obj, std::ostream &out, int indent_level = 0) const;
    virtual void pack(uint8_t &obj, std::ostream &out) const;
    virtual void unpack(std::istream &in, uint8_t &obj) const;
};



/*--------------------------------------------------------------------------------
The global type descriptor instance for e.g., vec3, is obtained through
   TypeDescriptorGiver<vec3>::get()->print,pack,unpack, etc.
note:
    This is a struct since template functions can't be partially specialized, and partial specialization is wanted
    for families of types such as std::vector<T>.
--------------------------------------------------------------------------------*/
template <typename TYPE>
struct TypeDescriptorGiver {
    // Specializations must implement get(). Can't think of a way to force this, so just using duck-typing.
    // "virtual static" TypeDescriptor *get();
};



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
        virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;\
        virtual void pack(uint8_t &obj, std::ostream &out) const;\
        virtual void unpack(std::istream &in, uint8_t &obj) const;\
    };
#define REFLECT_PRIMITIVE_TEMPLATED(TYPE)\
    struct PrimitiveTypeDescriptor<TYPE> : public TypeDescriptor {\
        PrimitiveTypeDescriptor() : TypeDescriptor{sizeof(TYPE), #TYPE} {}\
        virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;\
        virtual void pack(uint8_t &obj, std::ostream &out) const;\
        virtual void unpack(std::istream &in, uint8_t &obj) const;\
    };

#define REFLECT_PRIMITIVE_DECLARE_GETTER(TYPE)\
    template <>\
    struct TypeDescriptorGiver<TYPE> {\
        static TypeDescriptor *get();\
    }


// Implementations file.
#define REFLECT_PRIMITIVE_GETTER(TYPE)\
    TypeDescriptor *TypeDescriptorGiver<TYPE>::get()\
    {\
        static PrimitiveTypeDescriptor<TYPE> desc;\
        return &desc;\
    }
#define REFLECT_PRIMITIVE_GETTER_TEMPLATED(TYPE)\
    struct TypeDescriptorGiver<TYPE> {\
        static TypeDescriptor *get() {\
            static PrimitiveTypeDescriptor<TYPE> desc;\
            return &desc;\
        }\
    }


#define REFLECT_PRIMITIVE_PRINT(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::print(uint8_t &obj, std::ostream &out, int indent_level) const


#define REFLECT_PRIMITIVE_PACK(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::pack(uint8_t &obj, std::ostream &out) const


#define REFLECT_PRIMITIVE_UNPACK(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::unpack(std::istream &in, uint8_t &obj) const


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
    struct TypeDescriptorGiver<STRUCT_NAME> {\
        static TypeDescriptor *get()\
        {\
            static TypeDescriptor_Struct desc;\
            desc.name = #STRUCT_NAME;\
            using TYPE = STRUCT_NAME;\
            desc.size = sizeof(TYPE);\
            desc.entries = {\

#define STRUCT_ENTRY(ENTRY_NAME)\
                {#ENTRY_NAME, offsetof(TYPE, ENTRY_NAME), TypeDescriptorGiver<decltype(TYPE:: ENTRY_NAME)>::get()},

#define END_REFLECT_STRUCT()\
            };\
            return &desc;\
        }\
    };\




/*================================================================================
Reflection declarations for the basic C++ types.
These are included here for convenience, since they will most likely be needed.
================================================================================*/
REFLECT_PRIMITIVE(float);
REFLECT_PRIMITIVE_DECLARE_GETTER(float);
REFLECT_PRIMITIVE(bool);
REFLECT_PRIMITIVE_DECLARE_GETTER(bool);
REFLECT_PRIMITIVE(int);
REFLECT_PRIMITIVE_DECLARE_GETTER(int);
REFLECT_PRIMITIVE(uint8_t);
REFLECT_PRIMITIVE_DECLARE_GETTER(uint8_t);
REFLECT_PRIMITIVE(uint16_t);
REFLECT_PRIMITIVE_DECLARE_GETTER(uint16_t);
REFLECT_PRIMITIVE(uint32_t);
REFLECT_PRIMITIVE_DECLARE_GETTER(uint32_t);
REFLECT_PRIMITIVE(uint64_t);
REFLECT_PRIMITIVE_DECLARE_GETTER(uint64_t);


//--------------------------------------------------------------------------------




/*--------------------------------------------------------------------------------
    Helper functions for users of reflection.
--------------------------------------------------------------------------------*/
namespace Reflector {


// A family of template functions is defined for ease-of-use of the serialization functions available.


template <typename TYPE>
void print(TYPE &obj, std::ostream &out, int indent_level = 0)
{
    TypeDescriptorGiver<TYPE>::get()->print((uint8_t &)obj, out, indent_level);
}
// Convenient overload for printing to stdout.
template <typename TYPE>
void print(TYPE &obj, int indent_level = 0)
{
    TypeDescriptorGiver<TYPE>::get()->print((uint8_t &)obj, std::cout, indent_level);
}


template <typename TYPE>
void pack(TYPE &obj, std::ostream &out)
{
    TypeDescriptorGiver<TYPE>::get()->pack((uint8_t &)obj, out);
}


template <typename TYPE>
void unpack(std::istream &in, TYPE &obj)
{
    TypeDescriptorGiver<TYPE>::get()->unpack(in, (uint8_t &)obj);
}


} // end namespace Reflector

#endif // REFLECTOR_H
