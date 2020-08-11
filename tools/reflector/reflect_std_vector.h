#ifndef REFLECT_STD_VECTOR_H
#define REFLECT_STD_VECTOR_H


template <typename T>
struct PrimitiveTypeDescriptor<std::vector<T>> : public TypeDescriptor {
    PrimitiveTypeDescriptor() :
        TypeDescriptor{sizeof(std::vector<T>), "std::vector"}
    {
        element_type = TypeDescriptorGiver<T>::get();
    }
    virtual void print(uint8_t &obj, std::ostream &out, int indent_level) const;
    virtual void pack(uint8_t &obj, std::ostream &out) const;
    virtual void unpack(std::istream &in, uint8_t &obj) const;

    TypeDescriptor *element_type;

    virtual std::string name() const {
        return std::string(base_name) + "<" + element_type->name() + ">";
    }
};
template <typename T>
struct TypeDescriptorGiver<std::vector<T>> {
public:
    static TypeDescriptor *get() { return &desc; }
private:
    static PrimitiveTypeDescriptor<std::vector<T>> desc;
};
template <typename T>
PrimitiveTypeDescriptor<std::vector<T>> TypeDescriptorGiver<std::vector<T>>::desc;

// DESCRIPTOR_INSTANCE(std::vector<T>)();

template <typename T>
REFLECT_PRIMITIVE_PRINT(std::vector<T>) {
    auto vec = (std::vector<T> &) obj;
    out << name() << "[\n";
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
    out.write((char *)&length, sizeof(size_t));
    for (T &entry : vec) {
        Reflector::pack(entry, out);
    }
}


template <typename T>
REFLECT_PRIMITIVE_UNPACK(std::vector<T>) {
    size_t length;
    in.read((char *)&length, sizeof(size_t));
    auto vec = std::vector<T>(length);

    for (T &entry : vec) {
        Reflector::unpack(in, entry);
    }

    *((std::vector<T> *) &obj) = vec;
}


#endif // REFLECT_STD_VECTOR_H
