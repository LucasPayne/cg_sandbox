void pack(ResourceBase &obj, std::ostream &out);
void unpack(std::istream &in, ResourceBase &obj);
void print(ResourceBase &obj);
template <typename TYPE>
void pack(Resource<TYPE> &obj, std::ostream &out) {
    pack(obj.handle, out);
}
template <typename TYPE>
void unpack(std::istream &in, Resource<TYPE> &obj) {
    unpack(in, obj.handle);
}
template <typename TYPE>
void print(Resource<TYPE> &obj) {
    std::cout << "Resource<TYPE> {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "}\n";
}

