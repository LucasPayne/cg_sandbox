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
#include <map>
#include <functional>
#include <stdint.h>


class TypeDescriptor;
class TypeHandle {
public:
    TypeDescriptor &operator*();
    TypeDescriptor *operator->();
    const TypeDescriptor &operator*() const;
    const TypeDescriptor *operator->() const;

    bool operator==(const TypeHandle &other) const;
    bool operator!=(const TypeHandle &other) const;

    // A TypeHandle can be constructed from a pointer to a TypeDescriptor, the name of a reflected type,
    // or from the reflected type symbol through from_type<T>().
    TypeHandle() : type_descriptor{nullptr} {}
    TypeHandle(TypeDescriptor *_type_descriptor) : type_descriptor{_type_descriptor} {};
    TypeHandle(const TypeDescriptor *_type_descriptor) : type_descriptor{const_cast<TypeDescriptor *>(_type_descriptor)} {};
    TypeHandle(const std::string &type_name);

    template <typename T>
    static TypeHandle from_type();

private:
    TypeDescriptor *type_descriptor;
};



/*--------------------------------------------------------------------------------
TypeDescriptor
    The abstract base class of all type descriptors. Type operations (such as print)
    are declared here.

    This is the interface through which types will be used at run-time.
--------------------------------------------------------------------------------*/
struct TypeDescriptor {
    size_t size;
    const char *base_name;

    TypeDescriptor(size_t _size, const char *_base_name) :
        size{_size}, base_name{_base_name}
    {}
    TypeDescriptor() {}

    virtual void print(uint8_t &obj, std::ostream &out = std::cout, int indent_level = 0) const = 0;
    virtual void pack(uint8_t &obj, std::ostream &out) const = 0;
    virtual void unpack(std::istream &in, uint8_t &obj) const = 0;
    virtual void apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const = 0;
    
    // name() is overridable so, for example, each instantiation of a template class can have a different name.
    virtual std::string name() const { return std::string(base_name); }
};


namespace Reflector {


struct DescriptorMap {
    // Register a type in the global map.
    static void register_descriptor(TypeDescriptor *desc);
    // Get a registered type from its name.
    static TypeDescriptor *get(const std::string &name);

    static std::map<std::string, TypeDescriptor *> &name_to_type();
};


} // end namespace Reflector


struct TypeDescriptor_Struct : public TypeDescriptor {
    TypeDescriptor_Struct(size_t _size, const char *_base_name) :
        TypeDescriptor{_size, _base_name}
    {}
    TypeDescriptor_Struct() {}

    struct StructEntry {
        const char *name;
        size_t offset;
        TypeDescriptor *type;
    };
    std::vector<StructEntry> entries;

    virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;
    virtual void pack(uint8_t &obj, std::ostream &out) const;
    virtual void unpack(std::istream &in, uint8_t &obj) const;
    virtual void apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const;
};


// All concrete type descriptors are of type PrimitiveTypeDescriptor<SOME_TYPE>.
template <typename TYPE>
struct PrimitiveTypeDescriptor;


// Define the global instance of the type descriptor.
#define DESCRIPTOR_INSTANCE(TYPE)\
    PrimitiveTypeDescriptor<TYPE> PrimitiveTypeDescriptor<TYPE>::desc(PrimitiveTypeDescriptor<TYPE>::init(true))




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


// Header file.
#define REFLECT_PRIMITIVE(TYPE)\
    template <>\
    struct PrimitiveTypeDescriptor<TYPE> : public TypeDescriptor {\
    public:\
        PrimitiveTypeDescriptor() : TypeDescriptor{sizeof(TYPE), #TYPE} {}\
        virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;\
        virtual void pack(uint8_t &obj, std::ostream &out) const;\
        virtual void unpack(std::istream &in, uint8_t &obj) const;\
        virtual void apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const;\
        static TypeDescriptor *get() { return &desc; }\
        static PrimitiveTypeDescriptor<TYPE> init(bool register_type) {\
            auto desc = PrimitiveTypeDescriptor<TYPE>();\
            if (register_type) Reflector::DescriptorMap::register_descriptor(&desc);\
            return desc;\
        };\
        static PrimitiveTypeDescriptor<TYPE> desc;\
    };\


// For trivial primitives, apply() applies the functor to the object only.
#define REFLECT_PRIMITIVE_APPLY_TRIVIAL(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const\
    {\
        functor(TypeHandle(this), obj);\
    }

#define REFLECT_PRIMITIVE_APPLY(TYPE)\
    void PrimitiveTypeDescriptor<TYPE>::apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const

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
header file
    REFLECT_STRUCT(vec3);
    BEGIN_ENTRIES(vec3)
        ENTRY(x)
        ENTRY(y)
        ENTRY(z)
    END_ENTRIES()
implementations file
    DESCRIPTOR_INSTANCE(vec3);
--------------------------------------------------------------------------------*/
#define REFLECT_STRUCT(STRUCT_NAME)\
    template <>\
    struct PrimitiveTypeDescriptor<STRUCT_NAME> : public TypeDescriptor_Struct {\
    public:\
        PrimitiveTypeDescriptor() : TypeDescriptor_Struct{sizeof(STRUCT_NAME), #STRUCT_NAME} {}\
        static TypeDescriptor *get() { return &desc; };\
        static PrimitiveTypeDescriptor<STRUCT_NAME> desc;\
        static PrimitiveTypeDescriptor<STRUCT_NAME> init(bool register_type);\
    };\


// helper macro removes the template line.
#define REFLECT_STRUCT_TEMPLATED(STRUCT_NAME)\
    struct PrimitiveTypeDescriptor<STRUCT_NAME> : public TypeDescriptor_Struct {\
    public:\
        PrimitiveTypeDescriptor() : TypeDescriptor_Struct{sizeof(STRUCT_NAME), #STRUCT_NAME} {}\
        static TypeDescriptor *get() { return &desc; };\
        static PrimitiveTypeDescriptor<STRUCT_NAME> desc;\
        static PrimitiveTypeDescriptor<STRUCT_NAME> init(bool register_type);\
    };\


#define BEGIN_ENTRIES(STRUCT_NAME)\
    PrimitiveTypeDescriptor<STRUCT_NAME> PrimitiveTypeDescriptor<STRUCT_NAME>::init(bool register_type) {\
        PrimitiveTypeDescriptor<STRUCT_NAME> desc;\
        desc.base_name = #STRUCT_NAME;\
        using TYPE = STRUCT_NAME;\
        desc.size = sizeof(TYPE);\
        desc.entries = {\

#define ENTRY(ENTRY_NAME)\
	    {#ENTRY_NAME, offsetof(TYPE, ENTRY_NAME), PrimitiveTypeDescriptor<decltype(TYPE:: ENTRY_NAME)>::get()},
    
#define END_ENTRIES()\
        };\
        if (register_type) Reflector::DescriptorMap::register_descriptor(&desc);\
        return desc;\
    }\




/*================================================================================
Reflection declarations for the basic C++ types.
These are included here for convenience, since they will most likely be needed.
================================================================================*/
REFLECT_PRIMITIVE(float);
REFLECT_PRIMITIVE(bool);
REFLECT_PRIMITIVE(int);
REFLECT_PRIMITIVE(uint8_t);
REFLECT_PRIMITIVE(uint16_t);
REFLECT_PRIMITIVE(uint32_t);
REFLECT_PRIMITIVE(uint64_t);

/*--------------------------------------------------------------------------------
Reflection for raw pointers.
--------------------------------------------------------------------------------*/
template <typename T>
struct PrimitiveTypeDescriptor<T *> : public TypeDescriptor {
public:
    PrimitiveTypeDescriptor() :
        TypeDescriptor{sizeof(T *), "__RAW_POINTER__"}
    {}
    virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;
    virtual void pack(uint8_t &obj, std::ostream &out) const;
    virtual void unpack(std::istream &in, uint8_t &obj) const;
    virtual void apply(std::function<void(const TypeHandle &, uint8_t &)> functor, uint8_t &obj) const;

    virtual std::string name() const {
        // The element type must be registered already. Ensure this.
        PrimitiveTypeDescriptor<T> element_desc = PrimitiveTypeDescriptor<T>::init(false);
        return std::string(base_name) + "<" + element_desc.name() + ">";
    }
    static PrimitiveTypeDescriptor<T *> init(bool register_type) {
        auto desc = PrimitiveTypeDescriptor<T *>();
        if (register_type) Reflector::DescriptorMap::register_descriptor(&desc);
        return desc;
    }
    static TypeDescriptor *get() {
        return &desc;
    }
// private:
    static PrimitiveTypeDescriptor<T *> desc;
};
template <typename T>
PrimitiveTypeDescriptor<T *> PrimitiveTypeDescriptor<T *>::desc(PrimitiveTypeDescriptor<T *>::init(true));

template <typename T>
REFLECT_PRIMITIVE_PRINT(T *) {
    void *ptr = *((void **) &obj);
    out << name() << "{" << ptr << "}";
}
template <typename T>
REFLECT_PRIMITIVE_PACK(T *) {
    out.write((char *)&obj, sizeof(void *));
}
template <typename T>
REFLECT_PRIMITIVE_UNPACK(T *) {
    in.read((char *)&obj, sizeof(void *));
}
template <typename T>
REFLECT_PRIMITIVE_APPLY_TRIVIAL(T *);
//--------------------------------------------------------------------------------


/*--------------------------------------------------------------------------------
    Helper functions for users of reflection.
--------------------------------------------------------------------------------*/
namespace Reflector {


// Type descriptors should be looked up through the type through this family of methods.
template <typename T>
TypeDescriptor *get_descriptor()
{
    return PrimitiveTypeDescriptor<T>::get();
}

template <typename T>
TypeDescriptor *get_descriptor(T &obj)
{
    return PrimitiveTypeDescriptor<T>::get();
}



// A family of template functions is defined for ease-of-use of the serialization functions available.
template <typename TYPE>
void print(TYPE &obj, std::ostream &out, int indent_level = 0)
{
    PrimitiveTypeDescriptor<TYPE>::get()->print((uint8_t &)obj, out, indent_level);
}
// Convenient overload for printing to stdout.
template <typename TYPE>
void print(TYPE &obj, int indent_level = 0)
{
    PrimitiveTypeDescriptor<TYPE>::get()->print((uint8_t &)obj, std::cout, indent_level);
}

// Purely a helper function for printing with a newline (convenient for testing with prints).
template <typename TYPE>
void printl(TYPE &obj)
{
    print(obj, 0);
    std::cout << "\n";
}


template <typename TYPE>
void pack(TYPE &obj, std::ostream &out)
{
    PrimitiveTypeDescriptor<TYPE>::get()->pack((uint8_t &)obj, out);
}


template <typename TYPE>
void unpack(std::istream &in, TYPE &obj)
{
    PrimitiveTypeDescriptor<TYPE>::get()->unpack(in, (uint8_t &)obj);
}


} // end namespace Reflector




// Non-basic, but common C++ types have reflection declared here.
REFLECT_PRIMITIVE(std::string);
// std::vector is templated, and has reflections organized in its own header file.
#include "reflector/reflect_std_vector.h"


/*--------------------------------------------------------------------------------
    TypeHandle template methods.
--------------------------------------------------------------------------------*/



REFLECT_PRIMITIVE(TypeHandle);

template <typename T>
TypeHandle TypeHandle::from_type() {
    return TypeHandle(Reflector::get_descriptor<T>());
}


#endif // REFLECTOR_H
