#include "reflector/type_handle.h"

TypeHandle::TypeHandle(const std::string &type_name)
{
    type_descriptor = Reflector::DescriptorMap::get(type_name);
}


TypeDescriptor &TypeHandle::operator*()
{
    return *type_descriptor;
}
TypeDescriptor *TypeHandle::operator->()
{
    return type_descriptor;
}
const TypeDescriptor &TypeHandle::operator*() const
{
    return *type_descriptor;
}
const TypeDescriptor *TypeHandle::operator->() const
{
    return type_descriptor;
}



bool TypeHandle::operator==(const TypeHandle &other) const
{
    //todo: Names are unique, but a comparing unique IDs computed at static initialization would be better.
    return type_descriptor->name() == other->name();
}
bool TypeHandle::operator!=(const TypeHandle &other) const
{
    return !(*this == other);
}


DESCRIPTOR_INSTANCE(TypeHandle);


REFLECT_PRIMITIVE_PRINT(TypeHandle)
{
    TypeHandle &handle = (TypeHandle &) obj;
    TypeDescriptor &desc = *handle;
    
    out << name() << "(" << desc.name() << ")";
}


REFLECT_PRIMITIVE_PACK(TypeHandle)
{
    TypeHandle &handle = (TypeHandle &) obj;
    TypeDescriptor &desc = *handle;
    
    std::string type_name = desc.name();

    // Pack the type name only.
    Reflector::pack(type_name, out);
}


REFLECT_PRIMITIVE_UNPACK(TypeHandle)
{
    std::string type_name;
    Reflector::unpack(in, type_name);
    TypeHandle handle(type_name);
    *((TypeHandle *) &obj) = handle;
}
