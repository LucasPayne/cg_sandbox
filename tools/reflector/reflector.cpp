#include "reflector.h"


/*--------------------------------------------------------------------------------
Definitions for the basic C++ types.
--------------------------------------------------------------------------------*/
REFLECT_PRIMITIVE_GETTER(float);
REFLECT_PRIMITIVE_PRINT(float) {
    float val = *((float *) &obj);
    std::cout << name << "{" << std::fixed << std::setprecision(6) << val << "}";
}
REFLECT_PRIMITIVE_GETTER(bool);
REFLECT_PRIMITIVE_PRINT(bool) {
    bool val = *((bool *) &obj);
    std::cout << name << "{" << (val ? "True" : "False") << "}";
}
REFLECT_PRIMITIVE_GETTER(int);
REFLECT_PRIMITIVE_PRINT(int) {
    int val = *((int *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_GETTER(uint8_t);
REFLECT_PRIMITIVE_PRINT(uint8_t) {
    uint8_t val = *((uint8_t *) &obj);
    std::cout << name << "{" << (unsigned int) val << "}"; // Needs to be cast or it will be treated as a char.
}
REFLECT_PRIMITIVE_GETTER(uint16_t);
REFLECT_PRIMITIVE_PRINT(uint16_t) {
    uint16_t val = *((uint16_t *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_GETTER(uint32_t);
REFLECT_PRIMITIVE_PRINT(uint32_t) {
    uint16_t val = *((uint32_t *) &obj);
    std::cout << name << "{" << val << "}";
}
REFLECT_PRIMITIVE_GETTER(uint64_t);
REFLECT_PRIMITIVE_PRINT(uint64_t) {
    uint16_t val = *((uint64_t *) &obj);
    std::cout << name << "{" << val << "}";
}
