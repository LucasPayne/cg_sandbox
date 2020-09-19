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
#include "world/standard_aspects/standard_aspects.h"


class World : public IGC::Callbacks {
public:
    World();

    Entities entities;
    Resources resources;
    Assets assets;
    Graphics graphics;

    InputState input;

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);

    // Behaviours.
    // template <typename B>
    // B *add(Entity e);
    template <typename T, typename... Args>
    T *add(Entity e, Args&&... args);

    // Utilities.
    //todo: move this to a picker subsystem.
    bool screen_to_ray(float screen_x, float screen_y, Ray *ray);

private:
    World(const World &); // Delete the copy constructor.
};
REFLECT_STRUCT(World);


// Behaviours.
// template <typename T>
// T *World::add(Entity e)
template <typename T, typename... Args>
T *World::add(Entity e, Args&&... args)
{
    auto behaviour = e.add<Behaviour>();
    behaviour->data = new T(std::forward<Args>(args)...);
    behaviour->enabled = true;

    behaviour->object()->world = this;
    behaviour->object()->entity = e;

    return dynamic_cast<T *>(behaviour->object());
}


#endif // WORLD_H
