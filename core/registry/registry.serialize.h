template <typename T>
void pack(TableReference<T> &obj, std::ostream &out) {
    pack(obj.handle, out);
}
template <typename T>
void unpack(std::istream &in, TableReference<T> &obj) {
    unpack(in, obj.handle);
}
template <typename T>
void print(TableReference<T> &obj) {
    std::cout << "TableReference<T> {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "}\n";
}
template <typename T>
void pack(Reference<T> &obj, std::ostream &out) {
    pack(obj.handle, out);
    pack(obj.table, out);
}
template <typename T>
void unpack(std::istream &in, Reference<T> &obj) {
    unpack(in, obj.handle);
    unpack(in, obj.table);
}
template <typename T>
void print(Reference<T> &obj) {
    std::cout << "Reference<T> {\n";
    std::cout << "    handle: ";
    print(obj.handle);
    std::cout << "\n";
    std::cout << "    table: ";
    print(obj.table);
    std::cout << "\n";
    std::cout << "}\n";
}

