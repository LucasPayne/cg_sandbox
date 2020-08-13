#ifndef TYPE_HANDLE_H
#define TYPE_HANDLE_H
#include "reflector/reflector.h"

class TypeHandle {
public:
    TypeDescriptor &operator*();
    TypeDescriptor *operator->();

    // A TypeHandle can be constructed from a pointer to a TypeDescriptor, the name of a reflected type,
    // or from the reflected type symbol through from_type<T>().
    TypeHandle() : type_descriptor{nullptr} {}
    TypeHandle(TypeDescriptor *_type_descriptor) : type_descriptor{_type_descriptor} {};
    TypeHandle(const std::string &type_name);

    template <typename T>
    static TypeHandle from_type() {
        return TypeHandle(Reflector::get_descriptor<T>());
    }

private:
    TypeDescriptor *type_descriptor;
};
REFLECT_PRIMITIVE(TypeHandle);


#endif // TYPE_HANDLE_H
