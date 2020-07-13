/*--------------------------------------------------------------------------------
    Declarations and interface for the entity model.
--------------------------------------------------------------------------------*/
#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "core.h"

// !-TERRIBLE-! subject to change, hopefully.
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
// define_aspect(TheAspectWithOneFloat)
//     float the_float;
// end_define_aspect(TheAspectWithOneFloat)

/*--------------------------------------------------------------------------------
    Handles.
    These are what application objects will hold instead of, e.g., pointers.
-
    Entity and aspect indices are constant across those objects' lifetimes.
    The index lookup is fast, and the id is unique across the program lifetime,
    allowing lookup validation.
--------------------------------------------------------------------------------*/
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
};


// ID -1 == 255 is reserved for the null aspect type.
#define MAX_NUM_ASPECT_TYPES 255
struct AspectInfo {
    size_t size;
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
public: // Usage interface
    EntityModel();
    ~EntityModel();

    // Creation and destruction of entities.
    Entity new_entity();
    void destroy_entity(Entity entity);

    // Aspect data derives from AspectEntryBase, so this function can be used to destroy given the pointer.
    //-maybe this function shouldn't be available, and rather ID-based functions only.
    void destroy_aspect(AspectEntryBase *aspect_entry);
    //todo
    // void destroy_aspect(Aspect aspect);
    // template <typename A>
    // void destroy_aspect(Entity entity);

    // Printing and debug helper functions.
    void print_aspect_ids(AspectType aspect_type);
    void print_entity_ids();
    void fprint_entity(FILE *file, Entity entity);
    inline void print_entity(Entity entity) {
        fprint_entity(stdout, entity);
    };

    /*--------------------------------------------------------------------------------
    Aspect-templated methods, in header for compilation reasons. Summarized here (!-keep this synchronized-!).
    A is the aspect type name.
    
    // Iteration over aspects of a certain type.
    AspectIterator<A> aspects();

    // Retrieve the first aspect found of the given type in the entity's aspect list.
    A *get_aspect(Entity entity);
    
    // Add a new aspect to the entity.
    A *add_aspect(Entity entity);
    --------------------------------------------------------------------------------*/

//public implementation details
    /*--------------------------------------------------------------------------------
    AspectIterator is defined purely so range-based for works, assuming it expands as:
        for (auto &a : entity_model.aspects<TheAspectWithOneFloat>()) {
            ...
        }
        ->
        for (auto __begin = begin_expr, __end = end_expr; __begin != __end; ++__begin) { 
            range_declaration = *__begin; 
            ...
        }
    as described in
        https://en.cppreference.com/w/cpp/language/range-for
-
    This is probably the only way aspect lists will be accessed, so further iterator-compatible
    things don't seem necessary.
    --------------------------------------------------------------------------------*/
    template <typename A>
    class AspectIterator {
        A *list_start;
        A *list_end;
        inline void seek_to_next() {
            // Skip over null aspects.
            while (list_start != list_end && list_start->id == 0) {
                ++list_start;
            }
        }
    public:
        AspectIterator(A *_start, A *_end)
        : list_start{_start}, list_end{_end}
        {}
        void operator++() {
	    ++list_start;
            seek_to_next();
        }
        bool operator!=(AspectIterator other) { return list_start != other.list_start; }
        A &operator*() { return *list_start; }
        AspectIterator begin() {
            //-Remember to begin the iterator at a valid position!
            seek_to_next();
            return AspectIterator(list_start, list_end);
        }
        AspectIterator end() {
            return AspectIterator(list_end, list_end);
        }
    };
    template <typename A>
    AspectIterator<A> aspects() {
        return AspectIterator<A>(
             (A *) &aspect_lists[A::type][0],
             ((A *) &aspect_lists[A::type][0]) + (aspect_lists[A::type].size() / AspectInfo::type_info(A::type).size)
        );
    }
#if 0
    //-There is probably a way to avoid this code duplication.
    template <typename A, typename Required>
    class DoubleAspectIterator {
        A *list_start;
        Required *list_start_required; // Stores the required aspect at this iterator position, so begin() doesn't need to refind it.
        A *list_end;

        inline void get_required() {
            // Update the list_start_required pointer. To the relevant sibling of list_start. If there is none, this is set to nullptr.
            //-Don't do this if list_start is at the end!
            if (list_start->id == 0) {
                list_start_required = nullptr;
            } else {
                list_start_required = try_get_sibling_aspect<Required>(list_start);
            }
        }
        inline void seek_to_next() {
            // Skip over null aspects and aspects that don't have the required sibling.
            while (list_start != list_end && (list_start->id == 0 || list_start_required == nullptr)) {
                ++list_start;
                get_required();
            }
        }
    public:
        DoubleAspectIterator(A *_start, A *_end)
        : list_start{_start}, list_end{_end}
        {}
        void operator++() {
	    ++list_start;
            seek_to_next();
        }
        bool operator!=(DoubleAspectIterator other) { return list_start != other.list_start; }

        std::tuple<A&, Required&>operator*() {
            return std::tuple<A&, Required&>(*list_start, *list_start_required);
        }

        DoubleAspectIterator begin() {
            //-Remember to begin the iterator at a valid position!
            seek_to_next();
            if (list_start != list_end) {
                //-Make sure not to do this if there is the position is at the end!
                get_required();
            }
            return DoubleAspectIterator(list_start, list_end);
        }
        DoubleAspectIterator end() {
            return DoubleAspectIterator(list_end, list_end);
        }
    };
    #endif

    // This variant returns a null pointer if an aspect of the given type isn't found.
    // Presumably the caller will handle the null pointer case.
    template <typename A>
    A *try_get_aspect(Entity entity) {
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
        return nullptr;
    }
    template <typename A>
    inline A *get_aspect(Entity entity) {
        A *aspect_entry = try_get_aspect<A>(entity);
        if (aspect_entry == nullptr) {
            fprintf(stderr, "ERROR: Could not find aspect on entity.\n");
            exit(EXIT_FAILURE);
        }
        return aspect_entry;
    }
    // Get aspects from their aspect handles.
    template <typename A>
    A *try_get_aspect(Aspect aspect) {
        AspectEntryBase *base = try_get_aspect_base(aspect);
        return (A *) base;
    }
    template <typename A>
    A *get_aspect(Aspect aspect) {
        AspectEntryBase *base = get_aspect_base(aspect);
        return (A *) base;
    }

    // Sibling aspects.
    //-Should overload to use aspect handle.
    template <typename A>
    A *try_get_sibling_aspect(AspectEntryBase *aspect_entry) {
        for (Aspect sibling : entity_aspects(aspect_entry->entity)) {
            if (sibling.type == A::type) return (A *) try_get_aspect_base(sibling);
        }
        return nullptr;
    }

    template <typename A>
    A *add_aspect(Entity entity) {
        const AspectInfo &info = AspectInfo::type_info(A::type);
        uint32_t index;
        AspectEntryBase *entry = new_aspect_entry(entity, A::type, &index);
        A *aspect = (A *) entry;

        // !-IMPORTANT-! Remember to initialize this properly here. A public constructor doesn't make sense, and handles are only created here anyway.
        Aspect aspect_handle;
        aspect_handle.id = entry->id;
        aspect_handle.index = index;
        aspect_handle.type = A::type;

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

        return aspect;
    }
private: // implementation details
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
    AspectEntryBase *try_get_aspect_base(Aspect aspect);
    inline AspectEntryBase *get_aspect_base(Aspect aspect) {
        AspectEntryBase *entry = try_get_aspect_base(aspect);
        if (entry == nullptr) {
            // This aspect doesn't exist, at least not anymore.
            fprintf(stderr, "ERROR: Attempted to lookup aspect that doesn't exist.\n");
            fprintf(stderr, "    aspect id: %u, aspect index: %u, aspect type: %u\n", aspect.id, aspect.index, aspect.type);
            fprintf(stderr, "    entry id:  %u\n", entry->id);
            print_aspect_ids(aspect.type);
            exit(EXIT_FAILURE);
        }
        return entry;
    }

    // Use the entity handle to lookup the pointer to the entity entry in the entity list/table.
    // This is private, as applications probably shouldn't need to use it.
    EntityEntry *get_entity_entry(Entity entity);

    // Iterator for aspects of a given entity. This iterates the internal linked list.
    //-Private, since the application probably shouldn't need to treat aspects generically.
    //-Note: it is important for this to be efficient! At least as efficient as the verbose way that depends on understanding the underlying data structure.
    struct EntityAspectIterator {
        struct IteratorPosition {
            IteratorPosition() {
                // Empty constructor flags this position as the end.
                current_aspect.id = 0;
                //-entity_model state is not needed, so is not given here.
            }
            IteratorPosition(Aspect aspect, EntityModel *_entity_model) : current_aspect{aspect}, entity_model{_entity_model} {}

            bool operator!=(int throwaway) {
                //-This doesn't need to make sense as a "!=" operator, it just needs to work for the "macro expansion" described in
                //    https://en.cppreference.com/w/cpp/language/range-for
                return current_aspect.id != 0;
            }
            void operator++() {
                // Lookup the current aspect entry to find the next one. This is how the internal linked list has to be traversed.
                // If this is the last aspect, the next will had id 0, causing the iteration to stop.
                AspectEntryBase *aspect_entry = entity_model->get_aspect_base(current_aspect);
                current_aspect = aspect_entry->next_aspect;
            }
            Aspect operator*() { return current_aspect; }
        private:
            Aspect current_aspect;
            // This state is needed ...
            EntityModel *entity_model;
        };
        EntityAspectIterator(Entity _entity, EntityModel *_entity_model) : entity{_entity}, entity_model{_entity_model} {}

        IteratorPosition begin() {
            EntityEntry *entity_entry = entity_model->get_entity_entry(entity);
            if (entity_entry->num_aspects == 0) {
                // Flag this to exit immediately.
                //-This is a result of the (bad) decision to use num_aspects == 0 to signify none, instead of id == 0.
                return IteratorPosition();
            }
            else {
                return IteratorPosition(entity_entry->first_aspect, entity_model);
            }
        }
        int end() {
            //-Hopefully the compiler optimizes this stuff away somehow.
            return 0;
        }
    private:
        // The iterator needs this state.
        Entity entity;
        EntityModel *entity_model;
    };
    //-Defined here since the struct definition is here. Maybe it shouldn't be defined here.
    EntityAspectIterator entity_aspects(Entity entity) {
        //-The user doesn't use the constructor directly.
        return EntityAspectIterator(entity, this);
    }
};

#endif // ENTITY_MODEL_H
