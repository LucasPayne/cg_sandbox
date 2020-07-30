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
#include "resource_model/resource_model.h"
#include "assets/assets.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"
#include "world/standard_aspects/standard_aspects.h"
#include "interactive_graphics_context/interactive_graphics_context.h"

class World : public IGC::Callbacks {
public:
    // Looper stuff.
    void close();
    void loop();
    // InputListener stuff.
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);

    // Testing and debugging.
    void test_init();
    void test_loop();

    World();

    // "World creation" functions.
    //----------------------------
    /*--------------------------------------------------------------------------------
    A "Behaviour" is a standard aspect which allows an entity to have its own loop and input callbacks.
    Behaviour should be added to entities through this function, and in this case, be defined as, for example,
    
    struct Dolphin : IBehaviour {
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
    template <typename L>
    L *add_behaviour(Entity e) {
        Behaviour *behaviour = em.add_aspect<Behaviour>(e);
        behaviour->object_size = sizeof(L);
        behaviour->object = new L();
        behaviour->object->world = this;
        behaviour->object->entity = e;
        behaviour->object->updating = true;
        behaviour->object->handling_keyboard = true;
        behaviour->object->handling_mouse = true;

        return reinterpret_cast<L *>(behaviour->object);
    }

    // Component subsystems.
    EntityModel em;
    ResourceModel rm;
    Graphics graphics; // Graphics state, such as cached compiled shaders.
    InputState input;
    Assets assets;
};

#endif // WORLD_H
