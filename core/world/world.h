/*--------------------------------------------------------------------------------
Declarations and interface for the World class.

The World consists of components which contain some part of the state of the world,
such as the entity and resource models.

This also contains methods for "creating the world" at a higher level than the component subsystems,
such as the creation of game objects with Behaviours.
--------------------------------------------------------------------------------*/
#ifndef WORLD_H
#define WORLD_H
#include "core.h"
#include "data_structures/table.h"
#include "interactive_graphics_context/interactive_graphics_context.h"
#include "graphics_resources/graphics_resources.h"

#include "world/world_reference.h"
#include "world/entity_model/entity_model.h"
#include "world/resource_model/resource_model.h"
#include "world/assets/assets.h"
#include "world/graphics/graphics.h"


class World : public IGC::Callbacks {
    friend class WorldReference;
public:
    static WorldReference new_world();
    static void save_world(std::string &path);
    static WorldReference load_world(std::string &path);

    // Callbacks.
    void close();
    void loop();
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
        void keyboard_handler(KeyboardEvent e) {
            ...
        }
    };
    --------------------------------------------------------------------------------*/
    // template <typename B>
    // B *add_behaviour(Entity e) {
    //     auto behaviour = e.add<Behaviour>();
    //     behaviour->object_size = sizeof(B);
    //     behaviour->object = new B();

    //     behaviour->object->world = reference;
    //     behaviour->object->entity = e;
    //     behaviour->object->updating = true;
    //     behaviour->object->handling_keyboard = true;
    //     behaviour->object->handling_mouse = true;

    //     return reinterpret_cast<B *>(behaviour->object);
    // }
    // Component subsystems.
    EntityModel em;
    ResourceModel rm;
    Graphics graphics; // Graphics state, such as cached compiled shaders.
    InputState input;
    Assets assets;

private:
    WorldReference reference;

    static bool created_table;
    static Table<World> table; // Global table which contains Worlds.

    World() {}
};


#endif // WORLD_H
