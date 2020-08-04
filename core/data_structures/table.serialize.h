void pack(TableHandle &obj, std::ostream &out);
void unpack(std::istream &in, TableHandle &obj);
void print(TableHandle &obj);
template <typename TYPE>
void pack(TableCollectionHandle<TYPE> &obj, std::ostream &out) {
    pack((TableHandle &)obj, out);
}
template <typename TYPE>
void unpack(std::istream &in, TableCollectionHandle<TYPE> &obj) {
    unpack(in, (TableHandle &)obj);
}
template <typename TYPE>
void print(TableCollectionHandle<TYPE> &obj) {
    std::cout << "TableCollectionHandle<TYPE> {\n";
    std::cout << "    base TableHandle {\n";
    print((TableHandle &)obj);
    std::cout << "    }\n";
    std::cout << "}\n";
}
void pack(TypedTableCollectionHandle &obj, std::ostream &out);
void unpack(std::istream &in, TypedTableCollectionHandle &obj);
void print(TypedTableCollectionHandle &obj);

