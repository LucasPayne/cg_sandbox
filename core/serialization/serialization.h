#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <vector>
#include <iostream>

struct TYPE_INFO {
    virtual const char *name() const = 0;
    virtual size_t size() const = 0;
    virtual void pack(const char *data, std::ostream &stream) const = 0;
    virtual void unpack(std::istream &stream, char *data) const = 0;
};

struct TypeEntry {
    bool is_struct;
    size_t offset_in_struct;
    const TYPE_INFO *type_info;
    TypeEntry(size_t _offset_in_struct, const TYPE_INFO *_type_info, bool _is_struct = false) :
        offset_in_struct{_offset_in_struct}, type_info{_type_info}, is_struct{_is_struct}
    {}
    TypeEntry() {}
};
typedef std::vector<TypeEntry> TypeTree;
#define TYPE_TREE_ADD(ENTRY, TYPE_INFO_STRUCT) type_tree.push_back(TypeEntry(((char *)&ENTRY) - root, &TYPE_INFO_STRUCT))
#define TYPE_TREE_STRUCT(STRUCT, TYPE_INFO_STRUCT) type_tree.push_back(TypeEntry(0, &TYPE_INFO_STRUCT, true))

void print_type_tree(TypeTree &tree);

#define FUNDAMENTAL_TYPE(TYPENAME)\
    static const struct TYPE_ ## TYPENAME ## _s : TYPE_INFO {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const {\
            stream.write(data, size());\
        }\
        void unpack(std::istream &stream, char *data) const {\
            stream.read(data, size());\
        }\
    } TYPE_ ## TYPENAME;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)\
    {\
        TYPE_TREE_ADD(obj, TYPE_ ## TYPENAME);\
    }

#define STRUCT_TYPE(TYPENAME)\
    static const struct TYPE_ ## TYPENAME ## _s : TYPE_INFO {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const {\
            stream.write(data, size());\
        }\
        void unpack(std::istream &stream, char *data) const {\
            stream.read(data, size());\
        }\
    } TYPE_ ## TYPENAME;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)

#define CUSTOM_TYPE(TYPENAME)\
    static const struct TYPE_ ## TYPENAME ## _s : TYPE_INFO {\
        const char *name() const { return #TYPENAME; }\
        size_t size() const { return sizeof(TYPENAME); }\
        void pack(const char *data, std::ostream &stream) const;\
        void unpack(std::istream &stream, char *data) const;\
    } TYPE_ ## TYPENAME;\
    void type_tree(const char *root, TYPENAME &obj, TypeTree &type_tree)
#define CUSTOM_TYPE_PACK(TYPENAME,DATANAME,STREAMNAME)\
    void TYPE_ ## TYPENAME ## _s ::pack(const char *data, std::ostream &stream) const
#define CUSTOM_TYPE_UNPACK(TYPENAME,STREAMNAME,DATANAME)\
    void TYPE_ ## TYPENAME ## _s ::unpack(std::istream &stream, char *data) const



template <typename T>
void pack(T &obj, std::ostream &stream)
{
    TypeTree tree(0);
    type_tree((const char *)&obj, obj, tree);
    printf("packing\n");
    print_type_tree(tree);
    for (TypeEntry entry : tree) {
        if (entry.is_struct) continue;
        entry.type_info->pack(((char*)&obj) + entry.offset_in_struct, stream);
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
        entry.type_info->unpack(stream, ((char*)&obj) + entry.offset_in_struct);
    }
}

#endif // SERIALIZATION_H
