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
void pack(EntityModel &obj, std::ostream &out) {
    pack(obj.m_entity_table, out);
    pack(obj.m_aspect_tables, out);
}
void unpack(std::istream &in, EntityModel &obj) {
    unpack(in, obj.m_entity_table);
    unpack(in, obj.m_aspect_tables);
}
void print(EntityModel &obj) {
    std::cout << "EntityModel {\n";
    std::cout << "    m_entity_table: ";
    print(obj.m_entity_table);
    std::cout << "\n";
    std::cout << "    m_aspect_tables: ";
    print(obj.m_aspect_tables);
    std::cout << "\n";
    std::cout << "}\n";
}

