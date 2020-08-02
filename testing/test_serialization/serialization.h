#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <vector>
#include <iostream>

struct TYPE_FUNCTIONS {
    virtual const char *name() const = 0;
    virtual size_t size() const = 0;
    virtual void pack(const char *data, std::ostream &stream) const = 0;
    virtual void unpack(std::istream &stream, char *data) const = 0;
};

template <typename T>
struct TYPE_INFO : TYPE_FUNCTIONS {
    static T instance;
};

struct TypeEntry {
    bool is_struct;
    size_t offset_in_struct;
    const TYPE_FUNCTIONS *type_functions;
    TypeEntry(size_t _offset_in_struct, const TYPE_FUNCTIONS *_type_functions, bool _is_struct = false) :
        offset_in_struct{_offset_in_struct}, type_functions{_type_functions}, is_struct{_is_struct}
    {}
    TypeEntry() {}
};
typedef std::vector<TypeEntry> TypeTree;
#define TYPE_TREE_ADD(ENTRY,TYPE_NAME)\
    type_tree.push_back(TypeEntry(((char *)&ENTRY) - root, &( TYPE_ ## TYPE_NAME  :: instance)))
#define TYPE_TREE_ADD_TEMPLATED(ENTRY,TYPE_NAME,TEMPLATED_TYPE_NAME)\
    type_tree.push_back(TypeEntry(((char *)&ENTRY) - root, &( TYPE_ ## TYPE_NAME<TEMPLATED_TYPE_NAME, TYPE_ ## TEMPLATED_TYPE_NAME>:: instance)))
#define TYPE_TREE_STRUCT(STRUCT,TYPE_NAME)\
    type_tree.push_back(TypeEntry(0, &( TYPE_ ## TYPE_NAME :: instance ), true))

void print_type_tree(TypeTree &tree);

#define FUNDAMENTAL_TYPE(TYPENAME)\
    struct TYPE_ ## TYPENAME : TYPE_INFO<TYPE_ ## TYPENAME> {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const {\
            stream.write(data, size());\
        }\
        void unpack(std::istream &stream, char *data) const {\
            stream.read(data, size());\
        }\
        static TYPE_ ## TYPENAME instance;\
    };\
    TYPE_ ## TYPENAME TYPE_ ## TYPENAME :: instance;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)\
    {\
        TYPE_TREE_ADD(obj, TYPE_ ## TYPENAME);\
    }

#define STRUCT_TYPE(TYPENAME)\
    struct TYPE_ ## TYPENAME : TYPE_INFO<TYPE_ ## TYPENAME> {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const {\
            stream.write(data, size());\
        }\
        void unpack(std::istream &stream, char *data) const {\
            stream.read(data, size());\
        }\
        static TYPE_ ## TYPENAME instance;\
    };\
    TYPE_ ## TYPENAME TYPE_ ## TYPENAME :: instance;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)

#define CUSTOM_TYPE(TYPENAME)\
    struct TYPE_ ## TYPENAME : TYPE_INFO<TYPE_ ## TYPENAME> {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const;\
        void unpack(std::istream &stream, char *data) const;\
        static TYPE_ ## TYPENAME instance;\
    };\
    TYPE_ ## TYPENAME TYPE_ ## TYPENAME :: instance;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)
#define CUSTOM_TYPE_PACK(TYPENAME,DATANAME,STREAMNAME)\
    void TYPE_ ## TYPENAME ::pack(const char *data, std::ostream &stream) const
#define CUSTOM_TYPE_UNPACK(TYPENAME,STREAMNAME,DATANAME)\
    void TYPE_ ## TYPENAME ::unpack(std::istream &stream, char *data) const



template <typename T>
void pack(T &obj, std::ostream &stream)
{
    TypeTree tree(0);
    type_tree((const char *)&obj, obj, tree);
    printf("packing\n");
    print_type_tree(tree);
    for (TypeEntry entry : tree) {
        if (entry.is_struct) continue;
        entry.type_functions->pack(((char*)&obj) + entry.offset_in_struct, stream);
    }
}
template <typename T>
void unpack(std::istream &stream, T &obj)
{
    TypeTree tree(0);
    type_tree((const char *)&obj, obj, tree);
    printf("unpacking\n");
    print_type_tree(tree);
    for (TypeEntry entry : tree) {
        if (entry.is_struct) continue;
        printf("Unpacking to offset %zu\n", entry.offset_in_struct);
        entry.type_functions->unpack(stream, ((char*)&obj) + entry.offset_in_struct);
    }
}

#endif // SERIALIZATION_H
