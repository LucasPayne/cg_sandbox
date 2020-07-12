#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"

// Use this instead of writing out the struct definition directly.
// This hides the fact that this weird C++ template thing is happening behind the scenes.
//-A lot of this complication is due to static initialization wanting the name of the templated type as a string...
// It can access T::name, and if that itself has static initialization, written out for each and every aspect type definition, then this works.
#define define_aspect(ASPECT_NAME)\
    struct ASPECT_NAME : public AspectEntry<ASPECT_NAME> {\
        static char *name;
#define end_define_aspect(ASPECT_NAME)\
    };\
    char * ASPECT_NAME ::name( #ASPECT_NAME );

// example:
// define_aspect(TheAspectWithOneFloat) {
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
    uint32_t index;
    AspectType type;
    Aspect() {}
    Aspect(uint32_t _id, uint32_t _index, AspectType _type) :
        id{_id}, index{_index}, type{_type}
    {}
};

struct AspectInfo {
    size_t size;
    //----
    // I would like the name, but it appears that templating parameters cannot be stringified,
    // but there might be some trick to get the static initialization stuff to work and retrieve the name. But also maybe not.
    // The macro solution could do this easily, but initialization of RTTI had to be called manually.
    // char name[MAX_ASPECT_TYPE_NAME_LENGTH + 1];
    char *name;

    static int num_aspect_types;
    static AspectType new_aspect_type(char *name, size_t size);
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
};
// Static initialization of run-time type information.
template<typename T>
const AspectType AspectEntry<T>::type(AspectInfo::new_aspect_type(
    T::name,
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
// ---is the naming here fine?
struct RuntimeAspectInfo {
    uint32_t next_aspect_id; // init to 1. The null aspect id is 0.
    uint32_t first_free_index; // First index free in the relevant aspect list.
};

#define ENTITY_LIST_START_LENGTH 16
#define ASPECT_LIST_START_LENGTH 16
#define ALL_PUBLIC 1
class EntityModel {
//private:
public:
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
    // The index is also filled out, since this will be needed by add_aspect.
    // - This is purely a separated function to be used only by add_aspect.
    AspectEntryBase *new_aspect_entry(Entity entity, AspectType aspect_type, uint32_t *index_out);

    // Use the aspect handle to lookup the pointer to the base aspect class in the relevant aspect list/table.
    // This is private, as applications will use the templated get_aspect.
    AspectEntryBase *get_aspect_base(Aspect aspect);

    // Use the entity handle to lookup the pointer to the entity entry in the entity list/table.
    // This is private, as applications probably shouldn't need to use it.
    EntityEntry *get_entity_entry(Entity entity);
// public:
    EntityModel();
    ~EntityModel();

    Entity new_entity();
    void destroy_entity(Entity entity);

    void fprint_entity(FILE *file, Entity entity);
    inline void print_entity(Entity entity) {
        fprint_entity(stdout, entity);
    };

    //-Templating here is just for the syntax. A macro could be used instead.
    template <typename A>
    A *get_aspect(Entity entity) {
        EntityEntry *entity_entry = get_entity_entry(entity);

        // Search through the aspect linked list for the first one with the relevant id.
        if (entity_entry->num_aspects > 0) {
            Aspect cur_handle = entity_entry->first_aspect;
            AspectEntryBase *cur = get_aspect_base(cur_handle);
            while (cur_handle.id != 0) {
                if (cur_handle.type == A::type) {
                    // Found one.
                    return (A *) cur;
                }
                cur_handle = cur->next_aspect;
                cur = get_aspect_base(cur_handle);
            }
        }
        fprintf(stderr, "ERROR: Could not find aspect on entity.\n");
        exit(EXIT_FAILURE);
    }

    //- Templated methods must (?) be defined in the header.
    //- Templating is only here for the syntax, this could easily be done with a macro that expands to the type id.
    template <typename A>
    A *add_aspect(Entity entity) {
        const AspectInfo &info = AspectInfo::type_info(A::type);
        uint32_t index;
        AspectEntryBase *entry = new_aspect_entry(entity, A::type, &index);
        A *aspect = (A *) entry;

        // Create an aspect handle and use it to link this aspect into the entity's aspect list.
        // !-IMPORTANT-! Remember the order of parameters in the constructor, or else bugs will occur.
        //    id, index, type
        Aspect aspect_handle(entry->id, index, A::type);

        EntityEntry *entity_entry = get_entity_entry(entity);

        if (entity_entry->num_aspects == 0) {
            // This is the first aspect, at the head of the list.
            entity_entry->first_aspect = aspect_handle;
        } else {
            // Get the last aspect in the entity's aspect list.
            AspectEntryBase *last = get_aspect_base(entity_entry->first_aspect);
            while (last->next_aspect.id != 0) {
                last = get_aspect_base(last->next_aspect);
            }
            // Add this to the end.
            last->next_aspect = aspect_handle;
        }
        entity_entry->num_aspects ++;

        //---initialization stuff?

        return aspect;
    }
    // Aspect data derives from AspectEntryBase, so this function can be used to destroy given the pointer.
    void destroy_aspect(AspectEntryBase *aspect_entry);
    //todo
    // void destroy_aspect(Aspect aspect);
    // template <typename A>
    // void destroy_aspect(Entity entity);

    // Debug helper functions.
    void print_aspect_ids(AspectType aspect_type);
    void print_entity_ids();
};

#endif // ENTITY_MODEL_H
