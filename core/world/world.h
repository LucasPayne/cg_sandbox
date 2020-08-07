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
#include "registry/registry.h"
#include "resource_model/resource_model.h"
#include "assets/assets.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"
#include "world/standard_aspects/standard_aspects.h"
#include "interactive_graphics_context/interactive_graphics_context.h"

class World : public IGC::Callbacks {
public:
    World() {}
    static Reference<World> new_world();
    static void save_world(std::string &path);
    static Reference<World> load_world(std::string &path);

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
    template <typename B>
    B *add_behaviour(Entity e) {
        Behaviour *behaviour = em.add_aspect<Behaviour>(e);
        behaviour->object_size = sizeof(B);
        behaviour->object = new B();

        behaviour->object->world = reference;
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

private:
    Reference<World> reference;

    static bool created_table;
    static TableReference<World> table; // Table in the global registry which contains Worlds.
};

#endif // WORLD_H
