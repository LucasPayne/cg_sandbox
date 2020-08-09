template <typename TYPE>
void pack(Aspect<TYPE> &obj, std::ostream &out) {
    pack(obj.handle, out);
}
template <typename TYPE>
void unpack(std::istream &in, Aspect<TYPE> &obj) {
    unpack(in, obj.handle);
}
template <typename TYPE>
void print(Aspect<TYPE> &obj) {
    std::cout << "Aspect<TYPE> {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(Entity &obj, std::ostream &out);
void unpack(std::istream &in, Entity &obj);
void print(Entity &obj);
void pack(TypedAspect &obj, std::ostream &out);
void unpack(std::istream &in, TypedAspect &obj);
void print(TypedAspect &obj);
void pack(AspectBase &obj, std::ostream &out);
void unpack(std::istream &in, AspectBase &obj);
void print(AspectBase &obj);
void pack(EntityEntry &obj, std::ostream &out);
void unpack(std::istream &in, EntityEntry &obj);
void print(EntityEntry &obj);

