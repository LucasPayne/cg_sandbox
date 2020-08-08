void pack(VertexArrayLayout &obj, std::ostream &out) {
    pack(obj.index_type, out);
    pack(obj.num_vertices, out);
    pack(obj.indexed, out);
    pack(obj.num_indices, out);
}
void unpack(std::istream &in, VertexArrayLayout &obj) {
    unpack(in, obj.index_type);
    unpack(in, obj.num_vertices);
    unpack(in, obj.indexed);
    unpack(in, obj.num_indices);
}
void print(VertexArrayLayout &obj) {
    std::cout << "VertexArrayLayout {\n";
    std::cout << "    index_type: ";
    print(obj.index_type);
    std::cout << "\n";
    std::cout << "    num_vertices: ";
    print(obj.num_vertices);
    std::cout << "\n";
    std::cout << "    indexed: ";
    print(obj.indexed);
    std::cout << "\n";
    std::cout << "    num_indices: ";
    print(obj.num_indices);
    std::cout << "\n";
    std::cout << "}\n";
}
void pack(VertexArrayData &obj, std::ostream &out) {
    pack(obj.layout, out);
    pack(obj.attribute_buffers, out);
    pack(obj.index_buffer, out);
}
void unpack(std::istream &in, VertexArrayData &obj) {
    unpack(in, obj.layout);
    unpack(in, obj.attribute_buffers);
    unpack(in, obj.index_buffer);
}
void print(VertexArrayData &obj) {
    std::cout << "VertexArrayData {\n";
    std::cout << "    layout: ";
    print(obj.layout);
    std::cout << "\n";
    std::cout << "    attribute_buffers: ";
    print(obj.attribute_buffers);
    std::cout << "\n";
    std::cout << "    index_buffer: ";
    print(obj.index_buffer);
    std::cout << "\n";
    std::cout << "}\n";
}

