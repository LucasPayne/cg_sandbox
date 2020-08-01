#include "core.h"
#include "serialization/serialization.h"

static const struct TYPE_int_s : TYPE_INFO {
    const char *name() const { return "int"; }
    size_t size() const { return sizeof(int); }
    void pack(const char *data, std::ostream &stream) const {
        stream.write(data, size());
    }
    void unpack(std::istream &stream, char *data) const {
        stream.read(data, size());
    }
} TYPE_int;
void type_tree(const char *root, int &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD(obj, TYPE_int);
}

struct TestStruct {
    int x;
    int y;
    int z;
};

static const struct TYPE_TestStruct_s : TYPE_INFO {
    const char *name() const { return "TestStruct"; }
    size_t size() const { return sizeof(TestStruct); }
    void pack(const char *data, std::ostream &stream) const {
        stream.write(data, size());
    }
    void unpack(std::istream &stream, char *data) const {
        stream.read(data, size());
    }
} TYPE_TestStruct;
void type_tree(const char *root, TestStruct &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD(obj, TYPE_TestStruct);
    TYPE_TREE_ADD(obj.x, TYPE_int);
    TYPE_TREE_ADD(obj.y, TYPE_int);
    TYPE_TREE_ADD(obj.z, TYPE_int);
}

int main(void)
{
    printf("i'm in.\n");
    TypeTree tree(0);
    TestStruct a;
    a.x = 2;
    a.y = 3;
    a.z = -1032;
    type_tree((const char *)&a, a, tree);
    print_type_tree(tree);
}
