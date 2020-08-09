void pack(IBehaviour &obj, std::ostream &out) {
    pack(obj.entity, out);
    pack(obj.updating, out);
    pack(obj.handling_mouse, out);
    pack(obj.handling_keyboard, out);
}
void unpack(std::istream &in, IBehaviour &obj) {
    unpack(in, obj.entity);
    unpack(in, obj.updating);
    unpack(in, obj.handling_mouse);
    unpack(in, obj.handling_keyboard);
}
void print(IBehaviour &obj) {
    std::cout << "IBehaviour {\n";
    std::cout << "    entity: ";
    print(obj.entity);
    std::cout << "\n";
    std::cout << "    updating: ";
    print(obj.updating);
    std::cout << "\n";
    std::cout << "    handling_mouse: ";
    print(obj.handling_mouse);
    std::cout << "\n";
    std::cout << "    handling_keyboard: ";
    print(obj.handling_keyboard);
    std::cout << "\n";
    std::cout << "}\n";
}

