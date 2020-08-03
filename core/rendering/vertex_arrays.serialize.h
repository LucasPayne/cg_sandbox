void pack(VertexSemantic &obj, std::ostream &out) {
    pack(obj.name[31, out);
    pack(obj.type, out);
    pack(obj.size, out);
    pack(obj."ERROR:, out);
}
void unpack(std::ostream &in, VertexSemantic &obj) {
    unpack(in, obj.name[31);
    unpack(in, obj.type);
    unpack(in, obj.size);
    unpack(in, obj."ERROR:);
}
void print(VertexSemantic &obj) {
    std::cout << "VertexSemantic {\n";
    std::cout << "    name[31: ";
    print(obj.name[31);
    std::cout << "    \n";
    std::cout << "    type: ";
    print(obj.type);
    std::cout << "    \n";
    std::cout << "    size: ";
    print(obj.size);
    std::cout << "    \n";
    std::cout << "    "ERROR:: ";
    print(obj."ERROR:);
    std::cout << "    \n";
    std::cout << "}";
}
void pack(VertexArrayData &obj, std::ostream &out) {
    pack(obj.layout, out);
    pack(obj.attribute_buffers, out);
    pack(obj.index_buffer, out);
}
void unpack(std::ostream &in, VertexArrayData &obj) {
    unpack(in, obj.layout);
    unpack(in, obj.attribute_buffers);
    unpack(in, obj.index_buffer);
}
void print(VertexArrayData &obj) {
    std::cout << "VertexArrayData {\n";
    std::cout << "    layout: ";
    print(obj.layout);
    std::cout << "    \n";
    std::cout << "    attribute_buffers: ";
    print(obj.attribute_buffers);
    std::cout << "    \n";
    std::cout << "    index_buffer: ";
    print(obj.index_buffer);
    std::cout << "    \n";
    std::cout << "}";
}

