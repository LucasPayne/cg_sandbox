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
void pack(Camera &obj, std::ostream &out) {
    pack((IAspectType<Camera> &)obj, out);
    pack(obj.projection_matrix, out);
    for (int i = 0; i < ( 2 ); i++) {
        pack(obj.bottom_left[i], out);
    }
    for (int i = 0; i < ( 2 ); i++) {
        pack(obj.top_right[i], out);
    }
}
void unpack(std::istream &in, Camera &obj) {
    unpack(in, (IAspectType<Camera> &)obj);
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
    std::cout << "    base IAspectType<Camera> {\n";
    print((IAspectType<Camera> &)obj);
    std::cout << "    }}\n";
    std::cout << "    projection_matrix: ";
    print(obj.projection_matrix);
    std::cout << "\n";
    std::cout << "    array bottom_left [";
    for (int i = 0; i < ( 2 ); i++) {
        std::cout << "    ";
        print(obj.bottom_left[i]);
        std::cout << ",\n";
    }
    std::cout << "    array top_right [";
    for (int i = 0; i < ( 2 ); i++) {
        std::cout << "    ";
        print(obj.top_right[i]);
        std::cout << ",\n";
    }
    std::cout << "}\n";
}
void pack(IBehaviour &obj, std::ostream &out) {
    pack(obj.entity, out);
    pack(obj.updating, out);
}
void unpack(std::istream &in, IBehaviour &obj) {
    unpack(in, obj.entity);
    unpack(in, obj.updating);
}
void print(IBehaviour &obj) {
    std::cout << "IBehaviour {\n";
    std::cout << "    entity: ";
    print(obj.entity);
    std::cout << "\n";
    std::cout << "    updating: ";
    print(obj.updating);
    std::cout << "\n";
    std::cout << "}\n";
}

