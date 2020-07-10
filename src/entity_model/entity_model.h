#ifndef ENTITY_MODEL_AspectEntryH
#define ENTITY_MODEL_H
#include "core.h"

// A null Entity has id 0.
struct Entity {
    uint32_t index;
    uint32_t id;
};

// A null Aspect has type -1 (== 255).
typedef uint8_t AspectType;
struct Aspect {
    uint32_t id;
    uint16_t index;
    AspectType type;
};

struct AspectEntryBase {
    Entity entity;
    Aspect next_aspect;
    static AspectType next_type();
};
template<typename T>
struct AspectEntry : public AspectEntryBase
{
    //--Creation and teardown functions.
    static const AspectType type;
    static const size_t size;
};
template<typename T>
const AspectType AspectEntry<T>::type(AspectEntryBase::next_type());
template<typename T>
const size_t AspectEntry<T>::size(sizeof(T));

/*
Example aspect:

struct SomeValues : public AspectEntry<SomeValues> {
    float x;
    int nums[16];
    bool flag;
};

*/

class EntityModel {
private:
    struct EntityEntry {
        uint32_t id;
        uint8_t num_aspects;
        Aspect first_aspect;
    };
    EntityEntry *entity_list;

    std::vector<uint8_t *> aspect_lists;
public:
    EntityModel();
    ~EntityModel();
};

#endif // ENTITY_MODEL_H
