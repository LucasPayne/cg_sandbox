/*--------------------------------------------------------------------------------
Declarations and interface for the World class.

The World consists of components which contain some part of the state of the world,
such as the entity and resource models.

This also contains methods for "creating the world" at a higher level than the component subsystems,
such as the creation of game objects.
--------------------------------------------------------------------------------*/
#ifndef CG_SANDBOX_H
#define CG_SANDBOX_H
#include "core.h"
#include "resource_model/resource_model.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"
#include "world/standard_aspects/standard_aspects.h"

class World : public Looper, public InputListener {
public:
    World() {}

    // Looper stuff.
    void init();
    void close();
    void loop();
    // InputListener stuff.
    void key_callback(int key, int action);
    void cursor_position_callback(double x, double y);
    void cursor_move_callback(double x, double y);
    void mouse_button_callback(int button, int action);

    // Testing and debugging.
    void test_init();
    void test_loop();

    // "World creation" functions.
    //----------------------------
    /*--------------------------------------------------------------------------------
    A "Logic" is a standard aspect which allows an entity to have its own loop and input callbacks.
    Logic should be added to entities through this function, and in this case, be defined as, for example,
    
    struct Dolphin : ObjectLogic {
        int num_flippers;
        void update() {
            printf("I have %d flippers.\n", num_flippers);
        }
    };
    --------------------------------------------------------------------------------*/
    template <typename L>
    L *add_logic(Entity e) {
        Logic *logic = em.add_aspect<Logic>(e);
        L *object_logic = logic->init<L>();
        // Logic aspects in the World should derive from ObjectLogic (which has ILogic base class) rather than ILogic.
        // This simple wrapper gives the Logic a reference to the World it is in.
        object_logic->world = *this;
        return object_logic;
    }

    // Component subsystems.
    EntityModel em;
    ResourceModel rm;
    Graphics graphics; // Graphics state, such as cached compiled shaders.
};

#endif // CG_SANDBOX_H
