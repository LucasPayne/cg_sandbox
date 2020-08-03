void pack(TableHandle &obj, std::ostream &out) {
    pack(obj.id, out);
    pack(obj.index, out);
}
void unpack(std::istream &in, TableHandle &obj) {
    unpack(in, obj.id);
    unpack(in, obj.index);
}
void print(TableHandle &obj) {
    std::cout << "TableHandle {\n";
    std::cout << "    id: ";
    print(obj.id);
    std::cout << "\n";
    std::cout << "    index: ";
    print(obj.index);
    std::cout << "\n";
    std::cout << "}\n";
}

