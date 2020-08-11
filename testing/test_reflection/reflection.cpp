/*--------------------------------------------------------------------------------
references:
    https://preshing.com/20180116/a-primitive-reflection-system-in-cpp-part-1/


Language features such as C++'s templates and static initialization are used as tools to tell the compiler
to inject its knowledge of type structure into runtime.

This could be done without the full compiler, through code generation or data generation. However,
the compiler is the easiest and most reliable way to get information about how it actually treats the types -
a full generation solution will essentially require reimplementing a large part of the compiler.

So, a background of "meta" C++ source code can be provided that lets declarative code be generated
to describe type structure. Then an external tool can automatically produce, say, the macros
which will then expand to some sort of data declaration that will become a statically initialized
TypeDescriptor.
------------------------------------------------------------

Is there a good reason to put the static TypeDescriptor in the class?
Does the struct declaration need to be changed at all?
What about using templates which are specialized to primitives, then specialized to structs which
then cast back to a TypeDescriptor *?


Function template specialization is used to define descriptors for primitive types.
Class template speciailization could also be used, since the wanted mechanism is the instantiation
of one piece of global data.

------------------------------------------------------------
A lot of this stuff is _just_, in some way, telling the compiler to store this information globally.


--------------------------------------------------------------------------------*/
#include "core.h"
#include <iomanip> // Input-output manipulators. Used to set decimal places in output floats.


struct TypeDescriptor {
    size_t size;
    const char *name;

    TypeDescriptor(size_t _size, const char *_name) :
        size{_size}, name{_name}
    {}
    TypeDescriptor() {}

    virtual void print(uint8_t &obj) const = 0;
};
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
};


// There is no generic implementation of this --- it must only be specialized for each primitive type.
template <typename TYPE>
TypeDescriptor *TypeDescriptorOf();

template <typename TYPE>
struct TypeDescription;

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
#define REFLECT_PRIMITIVE(TYPE)\
    template <>\
    struct TypeDescription<TYPE> : public TypeDescriptor {\
        TypeDescription() : TypeDescriptor{sizeof(TYPE), #TYPE} {}\
        virtual void print(uint8_t &obj) const;\
    };\
    template <>\
    TypeDescriptor *TypeDescriptorOf<TYPE>() {\
        static TypeDescription<TYPE> desc;\
        return &desc;\
    }
#define REFLECT_PRIMITIVE_PRINT(TYPE)\
    void TypeDescription<TYPE>::print(uint8_t &obj) const

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


//--------------------------------------------------------------------------------
REFLECT_PRIMITIVE(float);
REFLECT_PRIMITIVE_PRINT(float) {
    float val = *((float *) &obj);
    std::cout << name << "{" << std::fixed << std::setprecision(6) << val << "}";
}
REFLECT_PRIMITIVE(bool);
REFLECT_PRIMITIVE_PRINT(bool) {
    bool val = *((bool *) &obj);
    std::cout << name << "{" << (val ? "True" : "False") << "}";
}
REFLECT_PRIMITIVE(int);
REFLECT_PRIMITIVE_PRINT(int) {
    int val = *((int *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE(uint8_t);
REFLECT_PRIMITIVE_PRINT(uint8_t) {
    uint8_t val = *((uint8_t *) &obj);
    std::cout << name << "{" << (unsigned int) val << "}"; // Needs to be cast or it will be treated as a char.
}
REFLECT_PRIMITIVE(uint16_t);
REFLECT_PRIMITIVE_PRINT(uint16_t) {
    uint16_t val = *((uint16_t *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE(uint32_t);
REFLECT_PRIMITIVE_PRINT(uint32_t) {
    uint16_t val = *((uint32_t *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE(uint64_t);
REFLECT_PRIMITIVE_PRINT(uint64_t) {
    uint16_t val = *((uint64_t *) &obj);
    std::cout << name << "{" << val << "}";
}
//--------------------------------------------------------------------------------

struct vec3_info {
    // Contrived example of struct within a struct.
    bool flag1;
    bool flag2;
};



REFLECT_STRUCT(vec3_info)
    STRUCT_ENTRY(flag1)
    STRUCT_ENTRY(flag2)
END_REFLECT_STRUCT()
    

struct vec3 {
    float x;
    float y;
    float z;
    vec3_info info;
};

REFLECT_STRUCT(vec3)
    STRUCT_ENTRY(x)
    STRUCT_ENTRY(y)
    STRUCT_ENTRY(z)
    STRUCT_ENTRY(info)
END_REFLECT_STRUCT()


struct Quaternion {
    float entries[4];
};

struct Transform {
    vec3 position;
    Quaternion rotation;

};


int main(void)
{
    vec3 v;
    v.x = 1;
    v.y = 2;
    v.z = -3.28131;
    v.info.flag1 = true;
    v.info.flag2 = false;

    TypeDescriptorOf<vec3>()->print((uint8_t &)v);
    
}
