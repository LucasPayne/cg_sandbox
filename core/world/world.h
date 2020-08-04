/*--------------------------------------------------------------------------------
Declarations and interface for the World class.

The World consists of components which contain some part of the state of the world,
such as the entity and resource models.

This also contains methods for "creating the world" at a higher level than the component subsystems,
such as the creation of game objects.
--------------------------------------------------------------------------------*/
#ifndef WORLD_H
#define WORLD_H
#include "core.h"
#include "data_structures/table.h"

typedef TableHandle WorldHandle;

#include "resource_model/resource_model.h"
#include "assets/assets.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"
#include "world/standard_aspects/standard_aspects.h"
#include "interactive_graphics_context/interactive_graphics_context.h"


static Table<GenericTable> g_table_registry;

template <typename T>
struct Reference : public TableHandle {
    TableHandle table; // Handle into the global table-registry table.
    
    //!-IMPORTANT-! If the table is for the wrong type, then something will go very wrong.

    inline T &operator*() {
        GenericTable *table_ptr = g_table_registry.lookup(table);
        if (table_ptr == nullptr) {
            fprintf(stderr, "ERROR: Attempted to dereference Reference into table not found in the global registry.\n");
            exit(EXIT_FAILURE);
        }
        T *ptr = reinterpret_cast<T *>(table_ptr->lookup(*this));
        if (ptr == nullptr) {
            fprintf(stderr, "ERROR: Attempted to dereference invalid Reference.\n");
            exit(EXIT_FAILURE);
        }
        return *ptr;
    }
    inline T *operator->() {
        return &(*this);
    }
    Reference(TableHandle &_table, TableHandle &_handle) :
        table{_table}
    {
        (TableHandle &) *this = _handle;
    }
};

class World : public IGC::Callbacks {
public:
    static TableHandle table; // Table in the global registry which contains Worlds.
    static Reference<World> new_world();
    Reference<World> ref;

    // Looper stuff.
    void close();
    void loop();
    // InputListener stuff.
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);

    // "World creation" functions.
    //----------------------------
    /*--------------------------------------------------------------------------------
    A "Behaviour" is a standard aspect which allows an entity to have its own loop and input callbacks.
    Behaviour should be added to entities through this function, and in this case, be defined as, for example,
    
    struct Dolphin : public IBehaviour {
        int num_flippers;
        void update() {
            printf("I have %d flippers.\n", num_flippers);
        }
        void mouse_handler(MouseEvent e) {
            ...
        }
        void keyboard_handler(MouseEvent e) {
            ...
        }
    };
    --------------------------------------------------------------------------------*/
    template <typename B>
    B *add_behaviour(Entity e) {
        Behaviour *behaviour = em.add_aspect<Behaviour>(e);
        behaviour->object_size = sizeof(B);
        behaviour->object = new B();
        behaviour->object->world = handle;
        behaviour->object->entity = e;
        behaviour->object->updating = true;
        behaviour->object->handling_keyboard = true;
        behaviour->object->handling_mouse = true;

        return reinterpret_cast<B *>(behaviour->object);
    }

    // Component subsystems.
    EntityModel em;
    ResourceModel rm;
    Graphics graphics; // Graphics state, such as cached compiled shaders.
    InputState input;
    Assets assets;
};

#endif // WORLD_H
