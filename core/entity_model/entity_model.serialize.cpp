void pack(AspectBase &obj, std::ostream &out) {
    pack(obj.entity, out);
    pack(obj.next_aspect, out);
}
void unpack(std::istream &in, AspectBase &obj) {
    unpack(in, obj.entity);
    unpack(in, obj.next_aspect);
}
void print(AspectBase &obj) {
    std::cout << "AspectBase {\n";
    std::cout << "    entity: ";
    print(obj.entity);
    std::cout << "\n";
    std::cout << "    next_aspect: ";
    print(obj.next_aspect);
    std::cout << "\n";
    std::cout << "}\n";
}

