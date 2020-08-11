void pack(ResourceBase &obj, std::ostream &out) {
    pack(obj.asset_backed, out);
}
void unpack(std::istream &in, ResourceBase &obj) {
    unpack(in, obj.asset_backed);
}
void print(ResourceBase &obj) {
    std::cout << "ResourceBase {\n";
    std::cout << "    asset_backed: ";
    print(obj.asset_backed);
    std::cout << "\n";
    std::cout << "}\n";
}

