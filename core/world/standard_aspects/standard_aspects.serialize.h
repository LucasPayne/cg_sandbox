void pack(Transform &obj, std::ostream &out) {
    pack((IAspectType<Transform> &)obj, out);
    pack(obj.position, out);
    pack(obj.rotation, out);
}
void unpack(std::istream &in, Transform &obj) {
    unpack(in, (IAspectType<Transform> &)obj);
    unpack(in, obj.position);
    unpack(in, obj.rotation);
}
void print(Transform &obj) {
    std::cout << "Transform {\n";
    std::cout << "    base IAspectType<Transform> {\n";
    print((IAspectType<Transform> &)obj);
    std::cout << "    }}\n";
    std::cout << "    position: ";
    print(obj.position);
    std::cout << "\n";
    std::cout << "    rotation: ";
    print(obj.rotation);
    std::cout << "\n";
    std::cout << "}\n";
}

