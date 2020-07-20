/*--------------------------------------------------------------------------------
    Declarations and interface for the entity model.
--------------------------------------------------------------------------------*/
#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include <tuple>
#include "data_structures/table.h"
#include "core.h"
#include <stdio.h> //error logging

/*================================================================================
    Table data
================================================================================*/
/*--------------------------------------------------------------------------------
    Entity and aspect handles.
    These are handles that conform to the Table data structure, having
    an index and id.
--------------------------------------------------------------------------------*/
struct Entity : public GenericTableHandle;
struct Aspect : public GenericTableHandle {
    AspectType type;
};

/*--------------------------------------------------------------------------------
    Entity and aspect table entries.
    AspectEntry is a base class. All aspect types derive from this class.
--------------------------------------------------------------------------------*/
// An entry in the entity table.
struct EntityEntry {
    // The entity has a linked list of its aspects,
    // which can be traversed from an aspect by using its entity handle to look up
    // its first aspect, and then following the next aspects.
    Aspect first_aspect;
};

struct AspectTypeStaticData {
    static AspectType type_id;
};
// The base class of aspects in an aspect table.
// The AspectEntry:: namespace also serves as the location of static type data - the type_id,
// which templated methods need so they can get the relevant table from their type template-parameter.
struct AspectEntry : public AspectTypeStaticData {
    Entity entity;
    Aspect next_aspect;
};


// class EntityModel {
// public: // Usage interface
//     EntityModel();
// 
//     // Creation and destruction of entities.
//     Entity new_entity();
//     void destroy_entity(Entity entity);
// 
//     void destroy_aspect(AspectEntry *aspect_entry);
//     //todo
//     // void destroy_aspect(Aspect aspect);
//     // template <typename A>
//     // void destroy_aspect(Entity entity);
// 
//     // Printing and debug helper functions.
//     void print_aspect_ids(AspectType aspect_type);
//     void print_entity_ids();
//     void fprint_entity(FILE *file, Entity entity);
//     inline void print_entity(Entity entity) {
//         fprint_entity(stdout, entity);
//     };
// 
//     /*--------------------------------------------------------------------------------
//     Aspect-templated methods, in header for compilation reasons. Summarized here (!-keep this synchronized-!).
//     A is the aspect type name.
//     
//     // Iteration over aspects of a certain type.
//     AspectIterator<A> aspects();
// 
//     // Retrieve the first aspect found of the given type in the entity's aspect list.
//     A *get_aspect(Entity entity);
//     
//     // Add a new aspect to the entity.
//     A *add_aspect(Entity entity);
//     --------------------------------------------------------------------------------*/
// //public implementation details
//     /*--------------------------------------------------------------------------------
//     AspectIterator is defined purely so range-based for works, assuming it expands as:
//         for (auto &a : entity_model.aspects<TheAspectWithOneFloat>()) {
//             ...
//         }
//         ->
//         for (auto __begin = begin_expr, __end = end_expr; __begin != __end; ++__begin) { 
//             range_declaration = *__begin; 
//             ...
//         }
//     as described in
//         https://en.cppreference.com/w/cpp/language/range-for
// -
//     This is probably the only way aspect lists will be accessed, so further iterator-compatible
//     things don't seem necessary.
//     --------------------------------------------------------------------------------*/
//     template <typename A>
//     class AspectIterator {
//         A *list_start;
//         A *list_end;
//         inline void seek_to_next() {
//             // Skip over null aspects.
//             while (list_start != list_end && list_start->id == 0) {
//                 ++list_start;
//             }
//         }
//     public:
//         AspectIterator(A *_start, A *_end)
//         : list_start{_start}, list_end{_end}
//         {}
//         void operator++() {
// 	    ++list_start;
//             seek_to_next();
//         }
//         bool operator!=(AspectIterator other) { return list_start != other.list_start; }
//         A &operator*() { return *list_start; }
//         AspectIterator begin() {
//             //-Remember to begin the iterator at a valid position!
//             seek_to_next();
//             return AspectIterator(list_start, list_end);
//         }
//         AspectIterator end() {
//             return AspectIterator(list_end, list_end);
//         }
//     };
//     template <typename A>
//     AspectIterator<A> aspects() {
//         return AspectIterator<A>(
//              (A *) &aspect_lists[A::type][0],
//              ((A *) &aspect_lists[A::type][0]) + (aspect_lists[A::type].size() / AspectInfo::type_info(A::type).size)
//         );
//     }
// 
//     // Iterate over aspect pairs, attached to the same entity. This is a lot of extra code but I think the syntax is convenient.
//     // example:
//     //    for (auto [t, v] : em.aspects<Transform, Velocity>()) {
//     //        ...
//     //    }
//     //-A lot of the implementation is just to get this to work with what C++ seemingly expands range-based for loops into.
//     // It really is in essence a macro trick.
//     template <typename A, typename Required>
//     struct DoubleAspectIterator {
//         DoubleAspectIterator(EntityModel &em) : entity_model{em} {}
// 
//         struct IteratorPosition {
//             IteratorPosition(A *_position, A *_end, EntityModel &em) : position{_position}, end{_end}, entity_model{em} {
//                 current_required = nullptr;
//                 seek_to_next();
//             }
//             inline void seek_to_next() {
//                 //-note: This does not shift first! This will stay in place unless the position is shifted before calling.
//                 while (true) {
//                     if (position == end) {
//                         return;
//                     }
//                     if (position->id == 0) {
//                         ++position;
//                     } else {
//                         current_required = entity_model.try_get_sibling_aspect<Required>(position);
//                         if (current_required != nullptr) {
//                             return;
//                         }
//                         ++position;
//                     }
//                 }
//             }
//             void operator++() {
//                 ++position;
//                 seek_to_next();
//             }
//             bool operator!=(int throwaway) {
//                 return position != end;
//             }
//             std::tuple<A&, Required&> operator*() {
//                 return std::tuple<A&, Required &>(*position, *current_required);
//             }
//         private:
//             A *position;
//             A *end;
//             Required *current_required;
//             EntityModel &entity_model;
//         };
//         IteratorPosition begin() {
//             return IteratorPosition(
//                 (A *) &entity_model.aspect_lists[A::type][0],
//                 ((A *) &entity_model.aspect_lists[A::type][0]) + (entity_model.aspect_lists[A::type].size() / AspectInfo::type_info(A::type).size),
//                 entity_model
//             );
//         }
//         int end() {
//             return 0;
//         }
//     private:
//         EntityModel &entity_model;
//     };
//     template <typename A, typename Required>
//     DoubleAspectIterator<A, Required> aspects() {
//         return DoubleAspectIterator<A, Required>(*this);
//     }
// 
//     // Get aspects from entities.
//     template <typename A>
//     A *try_get_aspect(Entity entity) {
//         EntityEntry *entity_entry = get_entity_entry(entity);
// 
//         // Search through the aspect linked list for the first one with the relevant id.
//         if (entity_entry->num_aspects > 0) {
//             Aspect cur_handle = entity_entry->first_aspect;
//             AspectEntryBase *cur = get_aspect_base(cur_handle);
//             while (cur_handle.id != 0) {
//                 if (cur_handle.type == A::type) {
//                     // Found one.
//                     return (A *) cur;
//                 }
//                 cur_handle = cur->next_aspect;
//                 cur = get_aspect_base(cur_handle);
//             }
//         }
//         return nullptr;
//     }
//     template <typename A>
//     inline A *get_aspect(Entity entity) {
//         A *aspect_entry = try_get_aspect<A>(entity);
//         if (aspect_entry == nullptr) {
//             fprintf(stderr, "ERROR: Could not find aspect on entity.\n");
//             exit(EXIT_FAILURE);
//         }
//         return aspect_entry;
//     }
//     // Get aspects from their aspect handles.
//     template <typename A>
//     A *try_get_aspect(Aspect aspect) {
//         AspectEntryBase *base = try_get_aspect_base(aspect);
//         return (A *) base;
//     }
//     template <typename A>
//     A *get_aspect(Aspect aspect) {
//         AspectEntryBase *base = get_aspect_base(aspect);
//         return (A *) base;
//     }
// 
//     // Sibling aspects.
//     //-Should overload to use aspect handle.
//     template <typename A>
//     A *try_get_sibling_aspect(AspectEntryBase *aspect_entry) {
//         for (Aspect sibling : entity_aspects(aspect_entry->entity)) {
//             if (sibling.type == A::type) return (A *) try_get_aspect_base(sibling);
//         }
//         return nullptr;
//     }
//     template <typename A>
//     inline A *get_sibling_aspect(AspectEntryBase *aspect_entry) {
//         A *sibling = try_get_sibling_aspect<A>(aspect_entry);
//         if (sibling == nullptr) {
//             fprintf(stderr, "ERROR: Could not find sibling %s aspect on entity.\n", AspectInfo::type_info(A::type).name);
//             exit(EXIT_FAILURE);
//         }
//         return sibling;
//     }
// 
//     template <typename A>
//     A *add_aspect(Entity entity) {
//         const AspectInfo &info = AspectInfo::type_info(A::type);
//         uint32_t index;
//         AspectEntryBase *entry = new_aspect_entry(entity, A::type, &index);
//         A *aspect = (A *) entry;
// 
//         // !-IMPORTANT-! Remember to initialize this properly here. A public constructor doesn't make sense, and handles are only created here anyway.
//         Aspect aspect_handle;
//         aspect_handle.id = entry->id;
//         aspect_handle.index = index;
//         aspect_handle.type = A::type;
// 
//         EntityEntry *entity_entry = get_entity_entry(entity);
// 
//         if (entity_entry->num_aspects == 0) {
//             // This is the first aspect, at the head of the list.
//             entity_entry->first_aspect = aspect_handle;
//         } else {
//             // Get the last aspect in the entity's aspect list.
//             AspectEntryBase *last = get_aspect_base(entity_entry->first_aspect);
//             while (last->next_aspect.id != 0) {
//                 last = get_aspect_base(last->next_aspect);
//             }
//             // Add this to the end.
//             last->next_aspect = aspect_handle;
//         }
//         entity_entry->num_aspects ++;
// 
//         return aspect;
//     }
// private: // implementation details
// 
//     Table<EntityEntry, Entity> m_entity_table;
//     TableCollection m_aspect_tables;
// 
//     
//     // Retrieve the next available entry in the aspect list for the given aspect type.
//     // It then has metadata filled and a pointer is returned, for the caller to do further initialization.
//     // The index is also filled out, since this will be needed by add_aspect.
//     // - This is purely a separated function to be used only by add_aspect.
//     AspectEntryBase *new_aspect_entry(Entity entity, AspectType aspect_type, uint32_t *index_out);
// 
//     // Use the aspect handle to lookup the pointer to the base aspect class in the relevant aspect list/table.
//     // This is private, as applications will use the templated get_aspect.
//     AspectEntryBase *try_get_aspect_base(Aspect aspect);
//     inline AspectEntryBase *get_aspect_base(Aspect aspect) {
//         AspectEntryBase *entry = try_get_aspect_base(aspect);
//         if (entry == nullptr) {
//             // This aspect doesn't exist, at least not anymore.
//             fprintf(stderr, "ERROR: Attempted to lookup aspect that doesn't exist.\n");
//             fprintf(stderr, "    aspect id: %u, aspect index: %u, aspect type: %u\n", aspect.id, aspect.index, aspect.type);
//             fprintf(stderr, "    entry id:  %u\n", entry->id);
//             print_aspect_ids(aspect.type);
//             exit(EXIT_FAILURE);
//         }
//         return entry;
//     }
// 
//     // Use the entity handle to lookup the pointer to the entity entry in the entity list/table.
//     // This is private, as applications probably shouldn't need to use it.
//     EntityEntry *get_entity_entry(Entity entity);
// 
//     // Iterator for aspects of a given entity. This iterates the internal linked list.
//     //-Private, since the application probably shouldn't need to treat aspects generically.
//     //-Note: it is important for this to be efficient! At least as efficient as the verbose way that depends on understanding the underlying data structure.
//     // !-NOTE-!
//     //     Using an iterator for entity's aspect lists seems like a good idea, even if this iteration is only internally used by the entity model implementation.
//     //     However, the implementation here is a mess, and there is definite uneccessary overhead in getting the iterator interface to match.
//     //     (todo: Learn how to properly create custom iterators.)
//     struct EntityAspectIterator {
//         struct IteratorPosition {
//             IteratorPosition() {
//                 // Empty constructor flags this position as the end.
//                 current_aspect.id = 0;
//                 //-entity_model state is not needed, so is not given here.
//             }
//             IteratorPosition(Aspect aspect, EntityModel *_entity_model) : current_aspect{aspect}, entity_model{_entity_model} {}
// 
//             bool operator!=(int throwaway) {
//                 //-This doesn't need to make sense as a "!=" operator, it just needs to work for the "macro expansion" described in
//                 //    https://en.cppreference.com/w/cpp/language/range-for
//                 return current_aspect.id != 0;
//             }
//             void operator++() {
//                 // Lookup the current aspect entry to find the next one. This is how the internal linked list has to be traversed.
//                 // If this is the last aspect, the next will had id 0, causing the iteration to stop.
//                 AspectEntryBase *aspect_entry = entity_model->get_aspect_base(current_aspect);
//                 current_aspect = aspect_entry->next_aspect;
//             }
//             Aspect operator*() { return current_aspect; }
//         private:
//             Aspect current_aspect;
//             // This state is needed ...
//             EntityModel *entity_model;
//         };
//         EntityAspectIterator(Entity _entity, EntityModel *_entity_model) : entity{_entity}, entity_model{_entity_model} {}
// 
//         IteratorPosition begin() {
//             EntityEntry *entity_entry = entity_model->get_entity_entry(entity);
//             if (entity_entry->num_aspects == 0) {
//                 // Flag this to exit immediately.
//                 //-This is a result of the (bad) decision to use num_aspects == 0 to signify none, instead of id == 0.
//                 return IteratorPosition();
//             }
//             else {
//                 return IteratorPosition(entity_entry->first_aspect, entity_model);
//             }
//         }
//         int end() {
//             //-Hopefully the compiler optimizes this stuff away somehow.
//             return 0;
//         }
//     private:
//         // The iterator needs this state.
//         Entity entity;
//         EntityModel *entity_model;
//     };
//     //-Defined here since the struct definition is here. Maybe it shouldn't be defined here.
//     EntityAspectIterator entity_aspects(Entity entity) {
//         //-The user doesn't use the constructor directly.
//         return EntityAspectIterator(entity, this);
//     }
// };

#endif // ENTITY_MODEL_H
