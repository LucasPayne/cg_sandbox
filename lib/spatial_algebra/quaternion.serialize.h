void pack(Quaternion &obj, std::ostream &out) {
    for (int i = 0; i < ( 4 ); i++) {
        pack(obj.entries[i], out);
    }
}
void unpack(std::istream &in, Quaternion &obj) {
    for (int i = 0; i < ( 4 ); i++) {
        unpack(in, obj.entries[i]);
    }
}
void print(Quaternion &obj) {
    std::cout << "Quaternion {\n";
    std::cout << "    array entries [";
    for (int i = 0; i < ( 4 ); i++) {
        std::cout << "    ";
        print(obj.entries[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}

