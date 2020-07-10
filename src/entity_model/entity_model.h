#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"

// Use this instead of writing out the struct definition directly.
// This hides the fact that this weird C++ template thing is happening behind the scenes.
#define DefineAspect(ASPECT_NAME) struct ASPECT_NAME : public AspectEntry<ASPECT_NAME>
// example:
// DefineAspect(TheAspectWithOneFloat) {
//     float the_float;
// }

// ID -1 == 255 is reserved for the null aspect type.
#define MAX_NUM_ASPECT_TYPES 255

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

typedef void (*AspectCreateFunction)(void);
typedef void (*AspectTeardownFunction)(void);

struct AspectInfo {
    AspectCreateFunction create;
    AspectTeardownFunction teardown;
    size_t size;

    static AspectType new_aspect_type(AspectCreateFunction create,
                                      AspectTeardownFunction teardown,
                                      size_t size);
    static AspectInfo type_info(AspectType type);
    //-----
    // Having problems with static initialization of std::vector.
    // Using an array instead.
    static AspectInfo aspect_infos[MAX_NUM_ASPECT_TYPES];
};
struct AspectEntryBase {
    Entity entity;
    Aspect next_aspect;
};
template<typename T>
struct AspectEntry : public AspectEntryBase
{
    static const AspectType type;
    static const size_t size;
    static const AspectCreateFunction create;
    static const AspectTeardownFunction teardown;
};
// Static initialization.
template<typename T>
const AspectType AspectEntry<T>::type(AspectInfo::new_aspect_type(
    T::create,
    T::teardown,
    sizeof(T)
));

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
