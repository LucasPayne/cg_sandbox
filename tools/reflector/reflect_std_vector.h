#ifndef REFLECT_STD_VECTOR_H
#define REFLECT_STD_VECTOR_H


template <typename T>
REFLECT_PRIMITIVE_TEMPLATED(std::vector<T>);


template <typename T>
REFLECT_PRIMITIVE_GETTER_TEMPLATED(std::vector<T>);


template <typename T>
REFLECT_PRIMITIVE_PRINT(std::vector<T>) {
    auto vec = (std::vector<T> &) obj;
    out << name << "[\n";
    for (T &entry : vec) {
        out << std::string(4*(indent_level+1), ' ');
        Reflector::print(entry, indent_level + 1);
        out << ",\n";
    }
    out << std::string(4*indent_level, ' ') << "]";
}


template <typename T>
REFLECT_PRIMITIVE_PACK(std::vector<T>) {
    auto vec = (std::vector<T> &) obj;
    size_t length = vec.size();
    printf("Writing length %zu\n", length);getchar();
    out.write((char *)&length, sizeof(size_t));
    for (T &entry : vec) {
        Reflector::pack(entry, out);
    }
}


template <typename T>
REFLECT_PRIMITIVE_UNPACK(std::vector<T>) {
    size_t length;
    in.read((char *)&length, sizeof(size_t));
    printf("Read length %zu\n", length);getchar();
    auto vec = std::vector<T>(length);

    for (T &entry : vec) {
        Reflector::unpack(in, entry);
    }

    *((std::vector<T> *) &obj) = vec;
}


#endif // REFLECT_STD_VECTOR_H
