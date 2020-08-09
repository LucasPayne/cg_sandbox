void pack(GeometricMaterialInstance &obj, std::ostream &out) {
    pack((GMSMInstance<GeometricMaterial> &)obj, out);
    pack(obj.vertex_array, out);
}
void unpack(std::istream &in, GeometricMaterialInstance &obj) {
    unpack(in, (GMSMInstance<GeometricMaterial> &)obj);
    unpack(in, obj.vertex_array);
}
void print(GeometricMaterialInstance &obj) {
    std::cout << "GeometricMaterialInstance {\n";
    std::cout << "    base GMSMInstance<GeometricMaterial> {\n";
    print((GMSMInstance<GeometricMaterial> &)obj);
    std::cout << "    }\n";
    std::cout << "    vertex_array: ";
    print(obj.vertex_array);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(MaterialInstance &obj, std::ostream &out) {
    pack((GMSMInstance<Material> &)obj, out);
}
void unpack(std::istream &in, MaterialInstance &obj) {
    unpack(in, (GMSMInstance<Material> &)obj);
}
void print(MaterialInstance &obj) {
    std::cout << "MaterialInstance {\n";
    std::cout << "    base GMSMInstance<Material> {\n";
    print((GMSMInstance<Material> &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}
void pack(ShadingModelInstance &obj, std::ostream &out) {
    pack((GMSMInstance<ShadingModel> &)obj, out);
}
void unpack(std::istream &in, ShadingModelInstance &obj) {
    unpack(in, (GMSMInstance<ShadingModel> &)obj);
}
void print(ShadingModelInstance &obj) {
    std::cout << "ShadingModelInstance {\n";
    std::cout << "    base GMSMInstance<ShadingModel> {\n";
    print((GMSMInstance<ShadingModel> &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}

