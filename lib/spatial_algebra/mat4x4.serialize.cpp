void pack(mat4x4 &obj, std::ostream &out) {
    for (int i = 0; i < ( 16 ); i++) {
        pack(obj.entries[i], out);
    }
}
void unpack(std::istream &in, mat4x4 &obj) {
    for (int i = 0; i < ( 16 ); i++) {
        unpack(in, obj.entries[i]);
    }
}
void print(mat4x4 &obj) {
    std::cout << "mat4x4 {\n";
    std::cout << "    array entries [\n";
    for (int i = 0; i < ( 16 ); i++) {
        std::cout << "        ";
        print(obj.entries[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}

