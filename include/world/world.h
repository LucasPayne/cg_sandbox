#ifndef WORLD_H
#define WORLD_H
#include "core.h"
#include "opengl_utilities/gl.h"
#include "interactive_graphics_context/interactive_graphics_context.h"
#include "world/entity_system/entity_system.h"
#include "world/graphics/graphics.h"



class World : public IGC::Callbacks {
public:
    World(IGC::Context &_context);

    IGC::Context &context;
    Entities entities;
    Resources resources;
    Graphics graphics;
    
    InputState input;
    // Input utilities. TODO: Put these under input.
    // Integer-valued vec2 for e.g. motion based on arrow keys.
    vec2 arrow_key_vector() const;
    vec2 wasd_key_vector() const;
    vec2 hjkl_key_vector() const;
    
    // Graphics graphics;

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);

    // Behaviours.
    template <typename T, typename... Args>
    T *add(Entity e, Args&&... args);
private:
    World(const World &); // Delete the copy constructor.
};


// Behaviours.
template <typename T, typename... Args>
T *World::add(Entity e, Args&&... args)
{
    auto behaviour = e.add<Behaviour>();
    behaviour->data = new T(std::forward<Args>(args)...);
    behaviour->enabled = false; // Initially disabled, to prevent problems when behaviours create other instances of their own type.
                                // Behaviours are enabled at the start of frame.
    behaviour->waiting_to_be_initialized = true;

    behaviour->object()->world = this;
    behaviour->object()->entity = e;

    return dynamic_cast<T *>(behaviour->object());
}


#endif // WORLD_H
