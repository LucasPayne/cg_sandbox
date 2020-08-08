void pack(EntityEntry &obj, std::ostream &out);
void unpack(std::istream &in, EntityEntry &obj);
void print(EntityEntry &obj);
void pack(AspectBase &obj, std::ostream &out);
void unpack(std::istream &in, AspectBase &obj);
void print(AspectBase &obj);
template <typename T>
void pack(IAspectType<T> &obj, std::ostream &out) {
    pack((AspectBase &)obj, out);
}
template <typename T>
void unpack(std::istream &in, IAspectType<T> &obj) {
    unpack(in, (AspectBase &)obj);
}
template <typename T>
void print(IAspectType<T> &obj) {
    std::cout << "IAspectType<T> {\n";
    std::cout << "    base AspectBase {\n";
    print((AspectBase &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}

