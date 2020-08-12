#ifndef TYPE_HANDLE_H
#define TYPE_HANDLE_H
#include "reflector/reflector.h"

class TypeHandle {
public:
    TypeDescriptor &operator*();
    TypeDescriptor *operator->();

    TypeHandle() : type_descriptor{nullptr} {}
    TypeHandle(const std::string &type_name);

private:
    TypeDescriptor *type_descriptor;
};
REFLECT_PRIMITIVE(TypeHandle);


#endif // TYPE_HANDLE_H
