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

static const struct TYPE_float_s : TYPE_INFO {
    const char *name() const { return "float"; }
    size_t size() const { return sizeof(float); }
    void pack(const char *data, std::ostream &stream) const {
        stream.write(data, size());
    }
    void unpack(std::istream &stream, char *data) const {
        stream.read(data, size());
    }
} TYPE_float;
void type_tree(const char *root, float &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD(obj, TYPE_float);
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
    TYPE_TREE_STRUCT(obj, TYPE_TestStruct);
    TYPE_TREE_ADD(obj.x, TYPE_int);
    TYPE_TREE_ADD(obj.y, TYPE_int);
    TYPE_TREE_ADD(obj.z, TYPE_int);
}


struct TestStruct2 {
    float a;
    TestStruct test;
    float b;
};
static const struct TYPE_TestStruct2_s : TYPE_INFO {
    const char *name() const { return "TestStruct2"; }
    size_t size() const { return sizeof(TestStruct2); }
    void pack(const char *data, std::ostream &stream) const {
        stream.write(data, size());
    }
    void unpack(std::istream &stream, char *data) const {
        stream.read(data, size());
    }
} TYPE_TestStruct2;
void type_tree(const char *root, TestStruct2 &obj, TypeTree &type_tree)
{
    TYPE_TREE_STRUCT(obj, TYPE_TestStruct2);
    TYPE_TREE_ADD(obj.a, TYPE_float);
    TYPE_TREE_ADD(obj.test, TYPE_TestStruct);
    TYPE_TREE_ADD(obj.b, TYPE_float);
}


struct Bytes {
    std::vector<uint8_t> buffer;
};
static const struct TYPE_Bytes_s : TYPE_INFO {
    const char *name() const { return "Bytes"; }
    size_t size() const { return sizeof(Bytes); }
    void pack(const char *data, std::ostream &stream) const {
        Bytes *bytes = (Bytes *)data;
        char size_buf[sizeof(Bytes)];
        ((size_t *)size_buf)[0] = bytes->buffer.size();
        stream.write(size_buf, size());
        stream.write((char *)&bytes->buffer[0], bytes->buffer.size());
    }
    void unpack(std::istream &stream, char *data) const {
        size_t buffer_size = *((size_t*)data);
        Bytes *bytes = (Bytes *) data;
        bytes->buffer = std::vector<uint8_t>(buffer_size);
        stream.read((char *)&bytes->buffer[0], buffer_size);
    }
} TYPE_Bytes;
void type_tree(const char *root, Bytes &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD(obj, TYPE_Bytes);
}

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

int main(void)
{
    TypeTree tree(0);
    TestStruct test;
    test.x = 2;
    test.y = 3;
    test.z = -1032;
    type_tree((const char *)&test, test, tree);
    print_type_tree(tree);

    TestStruct2 test2;
    test2.a = 0.3213;
    test2.test = test;
    test2.b = -0.123112;
    tree.clear();
    type_tree((const char *)&test2, test2, tree);
    print_type_tree(tree);

    {
        std::ofstream file;
        file.open("test.binary");
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        pack<TestStruct2>(test2, file);
        file.close();
    }
    {
        std::ifstream file;
        file.open("test.binary");
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        TestStruct2 r;
        unpack<TestStruct2>(file, r);
        printf("%.2f %.2f\n", r.a, r.b);
        file.close();
    }
}
