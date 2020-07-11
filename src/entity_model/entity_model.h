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

#define MAX_ASPECT_TYPE_NAME_LENGTH 63
struct AspectInfo {
    AspectCreateFunction create;
    AspectTeardownFunction teardown;
    size_t size;
    //----
    // I would like the name, but it appears that templating parameters cannot be stringified,
    // but there might be some trick to get the static initialization stuff to work and retrieve the name. But also maybe not.
    // The macro solution could do this easily, but initialization of RTTI had to be called manually.
    // char name[MAX_ASPECT_TYPE_NAME_LENGTH + 1];

    static int num_aspect_types;
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
    uint32_t id;
    union {
        Entity entity;
        // If id == 0, this stores the index of the free entry after this.
        uint32_t next_free_index;
    };
    // The entity has a linked list of its aspects,
    // which can be traversed from an aspect by using its entity handle to look up
    // its first aspect, and then following the next aspects.
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
// Static initialization of run-time type information.
template<typename T>
const AspectType AspectEntry<T>::type(AspectInfo::new_aspect_type(
    T::create,
    T::teardown,
    sizeof(T)
));

struct EntityEntry {
    uint32_t id;
    union {
        uint32_t num_aspects;
        // If id == 0, this stores the index of the free entry after this.
        uint32_t next_free_index;
    };
    Aspect first_aspect;
    //-- Will probably put very common things here, such as transform, instead of in an aspect.
    // I tried that, and a large portion of functions had to get the sibling transform aspect.
};

// Per-EntityModel aspect type metadata (doesn't need to be constant throughout runtime).
struct RuntimeAspectInfo {
    uint32_t next_aspect_id; // init to 1. The null aspect id is 0.
};

#define ENTITY_LIST_START_LENGTH 256
#define ASPECT_LIST_START_LENGTH 32
class EntityModel {
private:
    // entity list data structure
    // --------------------------
    uint32_t entity_list_first_free_index;
    std::vector<EntityEntry> entity_list;
    // --------------------------
    std::vector<std::vector<uint8_t>> aspect_lists;
    // This is tracked here instead of in AspectInfo RTTI, since that should be constant through runtime,
    // and ids don't need to be unique across EntityModel instances.
    std::vector<RuntimeAspectInfo> runtime_aspect_infos;
    
    // Retrieve the next available entry in the aspect list for the given aspect type.
    // It then has metadata filled and a pointer is returned, for the caller to do further initialization.
    template <typename A>
    A *new_aspect_entry() {
        const AspectInfo &info = AspectInfo::type_info(A::type);
        std::vector<uint8_t> &list = aspect_lists[A::type];
    }

public:
    EntityModel();
    ~EntityModel();

    Entity new_entity();

    //- Templated methods must be defined in the header.
    template <typename A>
    A *add_aspect(Entity e) {
        const AspectInfo &info = AspectInfo::type_info(A::type);
        A *entry = new_aspect_entry<A>();

        return entry;
    }
};

#endif // ENTITY_MODEL_H
