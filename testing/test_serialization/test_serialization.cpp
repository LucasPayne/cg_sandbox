#include "core.h"
#include "serialization/serialization.h"

// Macro parsing messes up when encountering commas in template parameters.
// Use macro COMMA instead. This is terrible, but is a solution.
#define COMMA ,

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
STRUCT_TYPE(TestStruct) {
    TYPE_TREE_STRUCT(obj, TestStruct);
    TYPE_TREE_ADD(obj.x, int);
    TYPE_TREE_ADD(obj.y, int);
    TYPE_TREE_ADD(obj.z, int);
}
std::ostream &operator<<(std::ostream &os, const TestStruct &obj) {
    os << "(x: "<<obj.x<<", y: "<<obj.y<<", z: "<<obj.z<<")";
    return os;
}

struct TestStruct2 {
    float a;
    TestStruct test;
    float b;
};
STRUCT_TYPE(TestStruct2) {
    TYPE_TREE_STRUCT(obj, TestStruct2);
    TYPE_TREE_ADD(obj.a, float);
    TYPE_TREE_ADD(obj.test, TestStruct);
    TYPE_TREE_ADD(obj.b, float);
}


struct Bytes {
    std::vector<uint8_t> buffer;
};

CUSTOM_TYPE(Bytes) {
    TYPE_TREE_ADD(obj, Bytes);
}
CUSTOM_TYPE_PACK(Bytes, data, stream) {
    Bytes *bytes = (Bytes *)data;
    char size_buf[sizeof(Bytes)];
    ((size_t *)size_buf)[0] = bytes->buffer.size();
    stream.write(size_buf, size());
    stream.write((char *)&bytes->buffer[0], bytes->buffer.size());
}
CUSTOM_TYPE_UNPACK(Bytes, stream, data) {
    char size_buf[sizeof(Bytes)];
    stream.read(size_buf, size());
    size_t buffer_size = *((size_t*)size_buf);
    Bytes *bytes = (Bytes *) data;
    bytes->buffer = std::vector<uint8_t>(buffer_size);
    stream.read((char *)&bytes->buffer[0], buffer_size);
}

template <typename T, typename TYPE_T>
struct TYPE_vector : TYPE_INFO<TYPE_vector<T, TYPE_T>> {
    const char *name() const { return "vector"; }
    size_t size() const { return sizeof(std::vector<T>); }
    void pack(const char *data, std::ostream &stream) const;
    void unpack(std::istream &stream, char *data) const;
    static TYPE_vector<T> instance;
};
template <typename T, typename TYPE_T>
TYPE_vector<T> TYPE_vector<T>::instance;
template <typename T, typename TYPE_T>
void type_tree(const char *root, std::vector<T> &obj, TypeTree &type_tree)
{
    TYPE_TREE_ADD_TEMPLATED(obj, vector, T);
}
template <typename T, typename TYPE_T>
void TYPE_vector<T>::pack(const char *data, std::ostream &stream) const
{
    std::vector<T> *vec = (std::vector<T> *)data;
    size_t vec_length = vec->size();
    stream.write((char *)&vec_length, sizeof(size_t));
    for (int i = 0; i < vec_length; i++) {
        TYPE_T::pack((const char *)&(*vec)[i], stream);
    }
    // stream.write((char *)&(*vec)[0], sizeof(T)*vec_length);

    // std::vector<T> *vec = (std::vector<T> *)data;
    // for (int i = 0; i < vec->size(); i++) {
    //     std::cout << "writing: " << (*vec)[i] << "\n";
    // }
    // char size_buf[sizeof(std::vector<T>)];
    // ((size_t *)size_buf)[0] = vec->size();
    // stream.write(size_buf, size());
    // size_t buffer_size = sizeof(T)*vec->size();
    // stream.write((char *)&(*vec)[0], buffer_size);
    // printf("%zu, %zu\n", vec->size(), buffer_size);
}
template <typename T, typename TYPE_T>
void TYPE_vector<T>::unpack(std::istream &stream, char *data) const
{
    size_t vec_length;
    stream.read((char *)&vec_length, sizeof(size_t));
    std::vector<T> *vec = (std::vector<T> *) data;
    size_t buffer_size = sizeof(T) * vec_length;
    *vec = std::vector<T>(buffer_size);
    for (int i = 0; i < vec_length; i++) {
        TYPE_T::unpack(stream, (char *)&(*vec)[i]);
    }

    // stream.read((char *)&(*vec)[0], buffer_size);

 //   char size_buf[sizeof(std::vector<T>)];
 //   stream.read(size_buf, size());
 //   size_t vec_length = *((size_t *)size_buf);
 //   size_t buffer_size = sizeof(T) * vec_length;
 //   printf("Found buffer size: %zu\n", buffer_size);
 //   std::vector<T> *vec = (std::vector<T> *) data;
 //   *vec = std::vector<T>(buffer_size);
 //   stream.read((char *)&(*vec)[0], buffer_size);
 //   for (int i = 0; i < vec_length; i++) {
 //       std::cout << "got: " << (*vec)[i] << "\n";
 //   }
}

struct TestStruct3 {
    uint64_t u;
    float x;
    float y;
    // Bytes bytes;
    std::vector<uint16_t> vec;
    float z;
};
STRUCT_TYPE(TestStruct3) {
    TYPE_TREE_STRUCT(obj, TestStruct2);
    TYPE_TREE_ADD(obj.u, uint64_t);
    TYPE_TREE_ADD(obj.x, float);
    TYPE_TREE_ADD(obj.y, float);
    // TYPE_TREE_ADD(obj.bytes, TYPE_Bytes);
    // TYPE_TREE_ADD(obj.vec, TYPE_vector<uint16_t COMMA TYPE_uint16_t>);
    TYPE_TREE_ADD_TEMPLATED(obj.vec, TYPE_vector, uint16_t);
    TYPE_TREE_ADD(obj.z, float);
}
std::ostream &operator<<(std::ostream &os, const TestStruct3 &obj) {
    os << "(u: "<<obj.u<<", x: "<<obj.x<<", y: "<<obj.y<<", z: "<<obj.z<<", bytes: ";
    // for (int i = 0; i < obj.bytes.buffer.size(); i++) {
    //     std::cout << obj.bytes.buffer[i] << ", ";
    // }
    for (int i = 0; i < obj.vec.size(); i++) {
        std::cout << obj.vec[i] << ", ";
    }
    ")";
    return os;
}



template <typename T>
void test_vector(int n) {
    printf("Testing vector\n");
    {
        std::vector<T> vec(n);
        for (int i = 0; i < n; i++) {
            // vec[i] = 3*(i+1);
            //   vec[i].x = i;
            //   vec[i].y = 2*i;
            //   vec[i].z = 3*i;
            vec[i].u = (i+1)*(i+1);
            vec[i].x = 0.2 + i;
            vec[i].y = 0.83;
            vec[i].z = -0.2 + i;
            vec[i].vec = std::vector<uint16_t>(i+1);
            for (int j = 0; j < i+1; j++) {
                vec[i].vec[j] = j+1;
            }
            // vec[i].bytes.buffer = std::vector<uint8_t>(i+1);
            // for (int j = 0; j < i+1; j++) {
            //     vec[i].bytes.buffer[j] = j+1;
            // }
        }
        std::ofstream file;
        file.open("test_vec.binary", std::ofstream::trunc | std::ofstream::out | std::ofstream::binary);
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        pack<std::vector<T>>(vec, file);
        file.close();
    }
    {
        std::ifstream file;
        file.open("test_vec.binary", std::ifstream::in | std::ifstream::binary);
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        std::vector<T> vec;
        unpack<std::vector<T>>(file, vec);
        for (int i = 0; i < n; i++) {
            std::cout << vec[i] << " ";
        }
        printf("\n");
        file.close();
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
    // // Test struct with Bytes.
    // {
    //     TestStruct3 t3;
    //     t3.u = 93102;
    //     t3.x = 0.1;
    //     t3.y = 0.1;
    //     t3.z = 0.1;
    //     t3.bytes.buffer = std::vector<uint8_t>(n);
    //     for (int i = 0; i < n; i++) {
    //         t3.bytes.buffer[i] = 2*(i+1);
    //     }

    //     std::ofstream file;
    //     file.open("test3.binary");
    //     if (!file.is_open()) {
    //         printf("hmm.\n");
    //         exit(1);
    //     }
    //     pack<TestStruct3>(t3, file);
    //     file.close();
    // }
    {
        std::ifstream file;
        file.open("test3.binary");
        if (!file.is_open()) {
            printf("hmm.\n");
            exit(1);
        }
        TestStruct3 t3;
        unpack<TestStruct3>(file, t3);
        printf("u: %zu\n", t3.u);
        // for (int i = 0; i < n; i++) {
        //     printf("%u ", t3.bytes.buffer[i]);
        // }
        printf("\n");
        printf("x: %.2f\n", t3.x);
        printf("y: %.2f\n", t3.y);
        printf("z: %.2f\n", t3.z);
        file.close();
    }
    // Test std::vector.
    test_vector<TestStruct3>(5);
}
