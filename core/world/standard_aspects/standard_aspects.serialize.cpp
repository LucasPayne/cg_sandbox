void pack(Transform &obj, std::ostream &out) {
    pack((AspectBase &)obj, out);
    pack(obj.position, out);
    pack(obj.rotation, out);
}
void unpack(std::istream &in, Transform &obj) {
    unpack(in, (AspectBase &)obj);
    unpack(in, obj.position);
    unpack(in, obj.rotation);
}
void print(Transform &obj) {
    std::cout << "Transform {\n";
    std::cout << "    base AspectBase {\n";
    print((AspectBase &)obj);
    std::cout << "    }\n";
    std::cout << "    position: ";
    print(obj.position);
    std::cout << "\n";
    std::cout << "    rotation: ";
    print(obj.rotation);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(Camera &obj, std::ostream &out) {
    pack((AspectBase &)obj, out);
    pack(obj.projection_matrix, out);
    for (int i = 0; i < ( 2 ); i++) {
        pack(obj.bottom_left[i], out);
    }
    for (int i = 0; i < ( 2 ); i++) {
        pack(obj.top_right[i], out);
    }
}
void unpack(std::istream &in, Camera &obj) {
    unpack(in, (AspectBase &)obj);
    unpack(in, obj.projection_matrix);
    for (int i = 0; i < ( 2 ); i++) {
        unpack(in, obj.bottom_left[i]);
    }
    for (int i = 0; i < ( 2 ); i++) {
        unpack(in, obj.top_right[i]);
    }
}
void print(Camera &obj) {
    std::cout << "Camera {\n";
    std::cout << "    base AspectBase {\n";
    print((AspectBase &)obj);
    std::cout << "    }\n";
    std::cout << "    projection_matrix: ";
    print(obj.projection_matrix);
    std::cout << "\n";
    std::cout << "    array bottom_left [\n";
    for (int i = 0; i < ( 2 ); i++) {
        std::cout << "        ";
        print(obj.bottom_left[i]);
        std::cout << ",\n";
    }
    std::cout << "    array top_right [\n";
    for (int i = 0; i < ( 2 ); i++) {
        std::cout << "        ";
        print(obj.top_right[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}
void pack(Drawable &obj, std::ostream &out) {
    pack((AspectBase &)obj, out);
    pack(obj.geometric_material, out);
    pack(obj.material, out);
}
void unpack(std::istream &in, Drawable &obj) {
    unpack(in, (AspectBase &)obj);
    unpack(in, obj.geometric_material);
    unpack(in, obj.material);
}
void print(Drawable &obj) {
    std::cout << "Drawable {\n";
    std::cout << "    base AspectBase {\n";
    print((AspectBase &)obj);
    std::cout << "    }\n";
    std::cout << "    geometric_material: ";
    print(obj.geometric_material);
    std::cout << "\n";
    std::cout << "    material: ";
    print(obj.material);
    std::cout << "\n";
    std::cout << "}\n";
}

