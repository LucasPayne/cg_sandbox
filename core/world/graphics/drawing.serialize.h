template <typename T>
void pack(GMSMInstance<T> &obj, std::ostream &out) {
    pack(obj.base, out);
}
template <typename T>
void unpack(std::istream &in, GMSMInstance<T> &obj) {
    unpack(in, obj.base);
}
template <typename T>
void print(GMSMInstance<T> &obj) {
    std::cout << "GMSMInstance<T> {\n";
    std::cout << "    base: ";
    print(obj.base);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(GeometricMaterialInstance &obj, std::ostream &out);
void unpack(std::istream &in, GeometricMaterialInstance &obj);
void print(GeometricMaterialInstance &obj);
void pack(MaterialInstance &obj, std::ostream &out);
void unpack(std::istream &in, MaterialInstance &obj);
void print(MaterialInstance &obj);
void pack(ShadingModelInstance &obj, std::ostream &out);
void unpack(std::istream &in, ShadingModelInstance &obj);
void print(ShadingModelInstance &obj);

