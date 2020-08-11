/*--------------------------------------------------------------------------------
Declarations and interface for the World class.

The World consists of components which contain some part of the state of the world,
such as the entity and resource models.
--------------------------------------------------------------------------------*/
#ifndef WORLD_H
#define WORLD_H
#include "core.h"
#include "data_structures/table.h"
#include "interactive_graphics_context/interactive_graphics_context.h"
#include "graphics_resources/graphics_resources.h"

#include "world/entity_model/entity_model.h"
#include "world/resource_model/resource_model.h"
#include "world/assets/assets.h"
#include "world/graphics/graphics.h"


/*--------------------------------------------------------------------------------
Behaviour aspect
--------------------------------------------------------------------------------*/
class World;
// Specific Behaviours must be defined in a class which derives from IBehaviour.
struct IBehaviour {
    World *world;
    Entity entity;
        // Each Behaviour attached to an entity is given a reference to the entity.
    bool updating;
    virtual void update() {
        // After one call, signify that this virtual function has not been overridden,
        // and that it is a no-op.
        updating = false;
    }
    bool handling_mouse;
    virtual void mouse_handler(MouseEvent e) {
        handling_mouse = false;
    }
    bool handling_keyboard;
    virtual void keyboard_handler(KeyboardEvent e) {
        handling_keyboard = false;
    }
};


struct Behaviour : public AspectBase {
    size_t object_size;
    IBehaviour *object;
};


/*--------------------------------------------------------------------------------
World
--------------------------------------------------------------------------------*/
class World : public IGC::Callbacks {
public:
    World();
    void save(std::string &path);
    static World load_world(std::string &path);

    // Callbacks.
    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    // Component subsystems.
    EntityModel em;
    ResourceModel rm;
    Graphics graphics; // Graphics state, such as cached compiled shaders.
    InputState input;
    Assets assets;

    
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
    B *add(Entity e) {
        auto behaviour = e.add<Behaviour>();
        behaviour->object_size = sizeof(B);
        behaviour->object = new B();

        behaviour->object->world = this;
        behaviour->object->entity = e;
        behaviour->object->updating = true;
        behaviour->object->handling_keyboard = true;
        behaviour->object->handling_mouse = true;

        return reinterpret_cast<B *>(behaviour->object);
    }

    // Entities are copied by packing to a buffer then unpacking from that buffer.
    // Entities can also be exported to disk and loaded from disk.
    void pack_entity(Entity entity, std::ostream &out);
    Entity unpack_entity(std::istream &in);

    Entity copy_entity(Entity entity);

    void export_entity(Entity entity, std::string &path);
    Entity import_entity(std::string &path);

private:
};


#endif // WORLD_H
