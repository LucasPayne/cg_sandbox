void pack(GeometricMaterial &obj, std::ostream &out) {
    pack((ResourceBase &)obj, out);
}
void unpack(std::istream &in, GeometricMaterial &obj) {
    unpack(in, (ResourceBase &)obj);
}
void print(GeometricMaterial &obj) {
    std::cout << "GeometricMaterial {\n";
    std::cout << "    base ResourceBase {\n";
    print((ResourceBase &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}
void pack(Material &obj, std::ostream &out) {
    pack((ResourceBase &)obj, out);
}
void unpack(std::istream &in, Material &obj) {
    unpack(in, (ResourceBase &)obj);
}
void print(Material &obj) {
    std::cout << "Material {\n";
    std::cout << "    base ResourceBase {\n";
    print((ResourceBase &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}
void pack(ShadingModel &obj, std::ostream &out) {
    pack((ResourceBase &)obj, out);
}
void unpack(std::istream &in, ShadingModel &obj) {
    unpack(in, (ResourceBase &)obj);
}
void print(ShadingModel &obj) {
    std::cout << "ShadingModel {\n";
    std::cout << "    base ResourceBase {\n";
    print((ResourceBase &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}
void pack(ShadingProgram &obj, std::ostream &out) {
}
void unpack(std::istream &in, ShadingProgram &obj) {
}
void print(ShadingProgram &obj) {
    std::cout << "ShadingProgram {\n";
    std::cout << "}\n";
}

