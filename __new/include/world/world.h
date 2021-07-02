#ifndef WORLD_H
#define WORLD_H
#include "core.h"
#include "interactive_graphics_context/interactive_graphics_context.h"
#include "world/entity_system/entity_system.h"


class World : public IGC::Callbacks {
public:
    World(IGC::Context &_context);

    IGC::Context &context;
    Entities entities;
    Resources resources;

    InputState input;

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);

    // Update information about screen size, which may have changed.
    void window_update(int width, int height);

    // Behaviours.
    // template <typename B>
    // B *add(Entity e);
    template <typename T, typename... Args>
    T *add(Entity e, Args&&... args);

    // Utilities.
    //todo: move this to a picker subsystem.
    bool screen_to_ray(float screen_x, float screen_y, Ray *ray);
    // Integer-valued vec2 for e.g. motion based on arrow keys.
    vec2 arrow_key_vector() const;
    vec2 wasd_key_vector() const;
    vec2 hjkl_key_vector() const;

private:
    World(const World &); // Delete the copy constructor.
};


// Behaviours.
// template <typename T>
// T *World::add(Entity e)
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
