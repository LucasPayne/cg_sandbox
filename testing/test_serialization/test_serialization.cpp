#include "core.h"
#include "serialization/serialization.h"

FUNDAMENTAL_TYPE(int);
FUNDAMENTAL_TYPE(float);
FUNDAMENTAL_TYPE(double);
FUNDAMENTAL_TYPE(bool);
FUNDAMENTAL_TYPE(char);
FUNDAMENTAL_TYPE(uint8_t);
FUNDAMENTAL_TYPE(uint16_t);
FUNDAMENTAL_TYPE(uint32_t);
FUNDAMENTAL_TYPE(uint64_t);

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
        char size_buf[sizeof(Bytes)];
        stream.read(size_buf, size());
        size_t buffer_size = *((size_t*)size_buf);
        Bytes *bytes = (Bytes *) data;
        bytes->buffer = std::vector<uint8_t>(buffer_size);
        stream.read((char *)&bytes->buffer[0], buffer_size);
    }
} TYPE_Bytes;
void type_tree(const char *root, Bytes &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD(obj, TYPE_Bytes);
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

    // Test byte vector.
    int n = 123;
    {
        Bytes bytes;
        bytes.buffer = std::vector<uint8_t>(n);
        for (int i = 0; i < n; i++) {
            bytes.buffer[i] = i+1;
        }

        std::ofstream file;
        file.open("test2.binary");
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        pack<Bytes>(bytes, file);
        file.close();
    }
    {
        std::ifstream file;
        file.open("test2.binary");
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        Bytes bytes;
        unpack<Bytes>(file, bytes);
        for (int i = 0; i < n; i++) {
            printf("%u ", bytes.buffer[i]);
        }
        printf("\n");
    }
}
