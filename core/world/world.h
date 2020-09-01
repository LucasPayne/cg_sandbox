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

#include "world/entities/entities.h"
#include "world/resources/resources.h"
#include "world/assets/assets.h"
#include "world/graphics/graphics.h"




class World;


/*--------------------------------------------------------------------------------
Behaviour aspect
--------------------------------------------------------------------------------*/
struct Behaviour;
// Specific Behaviours must be defined in a class which derives from IBehaviour.
struct IBehaviour {
public:
    World *world;
    Entity entity;
        // Each Behaviour attached to an entity is given a reference to the entity.

private:
    virtual void update() {
        //no-op
    }
    virtual void mouse_handler(MouseEvent e) {
        //no-op
    }
    virtual void keyboard_handler(KeyboardEvent e) {
        //no-op
    }
    // Behaviour routes calls to the IBehaviour's virtual functions, so needs access to private methods.
    friend class Behaviour;
};
REFLECT_STRUCT(IBehaviour);

struct Behaviour : public IAspectType {
    IBehaviour *object() {
        return data.as<IBehaviour>();
    }
    // Interpet as known IBehaviour-deriving type.
    template <typename T>
    T *object_as() {
        return reinterpret_cast<T *>(data.as<IBehaviour>());
    }

    GenericOwned data;
    bool enabled;

    void update();
    void mouse_handler(MouseEvent e);
    void keyboard_handler(KeyboardEvent e);
    
};
REFLECT_STRUCT(Behaviour);



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
    Entities entities;
    Resources resources;
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
    B *add(Entity e);

    // Entities are copied by packing to a buffer then unpacking from that buffer.
    // Entities can also be exported to disk and loaded from disk.

    void print_entity(Entity entity, int indent_level = 0);

    void pack_entity(Entity entity, std::ostream &out);
    Entity unpack_entity(std::istream &in);

    Entity copy_entity(Entity entity);

    void export_entity(Entity entity, const std::string &path);
    Entity import_entity(const std::string &path);

    void export_aspect(GenericAspect aspect, std::ostream &out);
    void import_aspect(std::istream &in, GenericAspect aspect);
    void print_aspect(GenericAspect aspect, std::ostream &out, int indent_level = 0);

private:
    friend class PrimitiveTypeDescriptor<World>;

    World(const World &); // Delete the copy constructor.
};
REFLECT_STRUCT(World);



template <typename T>
T *World::add(Entity e)
{   
    auto behaviour = e.add<Behaviour>();
    behaviour->data = make_owned<T>();
    behaviour->enabled = true;

    behaviour->object()->world = this;
    behaviour->object()->entity = e;

    return dynamic_cast<T *>(behaviour->object());
}


#endif // WORLD_H
