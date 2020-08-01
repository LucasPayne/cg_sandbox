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
    size_t offset_in_struct;
    const TYPE_INFO *type_info;
    TypeEntry(size_t _offset_in_struct, const TYPE_INFO *_type_info) :
        offset_in_struct{_offset_in_struct}, type_info{_type_info}
    {}
    TypeEntry() {}
};
typedef std::vector<TypeEntry> TypeTree;
#define TYPE_TREE_ADD(OBJ, TYPE_INFO_STRUCT) type_tree.push_back(TypeEntry((char *)&obj - root, &TYPE_INFO_STRUCT))

void print_type_tree(TypeTree &tree);

#endif // SERIALIZATION_H
