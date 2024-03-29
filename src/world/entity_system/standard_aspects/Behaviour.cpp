#include "world/entity_system/entity_system.h"


// Non-virtual Behaviour interface.
// It may be useful to wrap all behaviour callbacks for debugging.
void Behaviour::init()
{
    object()->init();
}
void Behaviour::update()
{
    object()->update();
}
void Behaviour::post_render_update()
{
    object()->post_render_update();
}
void Behaviour::mouse_handler(MouseEvent e)
{
    object()->mouse_handler(e);
}
void Behaviour::keyboard_handler(KeyboardEvent e)
{
    object()->keyboard_handler(e);
}

DESCRIPTOR_INSTANCE(IBehaviour);
BEGIN_ENTRIES(IBehaviour)
    //...
END_ENTRIES()


DESCRIPTOR_INSTANCE(Behaviour);
BEGIN_ENTRIES(Behaviour)
    //...
END_ENTRIES()



