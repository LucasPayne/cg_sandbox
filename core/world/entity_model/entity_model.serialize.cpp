void pack(Entity &obj, std::ostream &out) {
    pack(obj.handle, out);
}
void unpack(std::istream &in, Entity &obj) {
    unpack(in, obj.handle);
}
void print(Entity &obj) {
    std::cout << "Entity {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(TypedAspect &obj, std::ostream &out) {
    pack(obj.handle, out);
}
void unpack(std::istream &in, TypedAspect &obj) {
    unpack(in, obj.handle);
}
void print(TypedAspect &obj) {
    std::cout << "TypedAspect {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "}\n";
}
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
void pack(EntityEntry &obj, std::ostream &out) {
    pack(obj.first_aspect, out);
}
void unpack(std::istream &in, EntityEntry &obj) {
    unpack(in, obj.first_aspect);
}
void print(EntityEntry &obj) {
    std::cout << "EntityEntry {\n";
    std::cout << "    first_aspect: ";
    print(obj.first_aspect);
    std::cout << "\n";
    std::cout << "}\n";
}

