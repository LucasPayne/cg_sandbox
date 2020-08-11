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
template <typename PRIMITIVE_TYPE>
TypeDescriptor *TypeDescriptorOf();

// Some specializations for descriptors of primitive types.
template <>
TypeDescriptor *TypeDescriptorOf<bool>() {
    static struct Desc : public TypeDescriptor {
        Desc() : TypeDescriptor{sizeof(bool), "bool"} {}
        virtual void print(uint8_t &obj) const {
            bool val = *((bool *) &obj);
            std::cout << name << "{" << (val ? "True" : "False") << "}";
        }
    } desc;
    return &desc;
}
template <>
TypeDescriptor *TypeDescriptorOf<float>() {
    static struct Desc : public TypeDescriptor {
        Desc() : TypeDescriptor{sizeof(float), "float"} {}
        virtual void print(uint8_t &obj) const {
            float val = *((float *) &obj);
            std::cout << name << "{" << std::fixed << std::setprecision(6) << val << "}";
        }
    } desc;
    return &desc;
}


struct vec3_info {
    // Contrived example of struct within a struct.
    bool flag1;
    bool flag2;
};
template <>
TypeDescriptor *TypeDescriptorOf<vec3_info>() {
    static TypeDescriptor_Struct desc;
    desc.name = "vec3_info";
    using TYPE = vec3_info;
    desc.size = sizeof(TYPE);
    desc.entries = {
        {"flag1", offsetof(TYPE, flag1), TypeDescriptorOf<decltype(TYPE::flag1)>()},
        {"flag2", offsetof(TYPE, flag2), TypeDescriptorOf<decltype(TYPE::flag2)>()},
    };
    return &desc;
}

struct vec3 {
    float x;
    float y;
    float z;
    vec3_info info;
};
template <>
TypeDescriptor *TypeDescriptorOf<vec3>() {
    static TypeDescriptor_Struct desc;
    desc.name = "vec3";
    using TYPE = vec3;
    desc.size = sizeof(TYPE);
    desc.entries = {
        {"x", offsetof(TYPE, x), TypeDescriptorOf<decltype(TYPE::x)>()},
        {"y", offsetof(TYPE, y), TypeDescriptorOf<decltype(TYPE::y)>()},
        {"z", offsetof(TYPE, z), TypeDescriptorOf<decltype(TYPE::z)>()},
        {"info", offsetof(TYPE, info), TypeDescriptorOf<decltype(TYPE::info)>()},
    };
    return &desc;
}



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
