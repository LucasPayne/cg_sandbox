void pack(vec3 &obj, std::ostream &out) {
    for (int i = 0; i < ( 3 ); i++) {
        pack(obj.entries[i], out);
    }
}
void unpack(std::istream &in, vec3 &obj) {
    for (int i = 0; i < ( 3 ); i++) {
        unpack(in, obj.entries[i]);
    }
}
void print(vec3 &obj) {
    std::cout << "vec3 {\n";
    std::cout << "    array entries [\n";
    for (int i = 0; i < ( 3 ); i++) {
        std::cout << "        ";
        print(obj.entries[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}
void pack(vec4 &obj, std::ostream &out) {
    for (int i = 0; i < ( 4 ); i++) {
        pack(obj.entries[i], out);
    }
}
void unpack(std::istream &in, vec4 &obj) {
    for (int i = 0; i < ( 4 ); i++) {
        unpack(in, obj.entries[i]);
    }
}
void print(vec4 &obj) {
    std::cout << "vec4 {\n";
    std::cout << "    array entries [\n";
    for (int i = 0; i < ( 4 ); i++) {
        std::cout << "        ";
        print(obj.entries[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}

