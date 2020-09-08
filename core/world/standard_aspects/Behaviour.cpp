#include "world/standard_aspects/standard_aspects.h"


// Non-virtual Behaviour interface.
// It may be useful to wrap all behaviour callbacks for debugging.
void Behaviour::update()
{
    object()->update();
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
    // ENTRY(world) //todo: problems with pointer to incomplete type.
    ENTRY(entity)
END_ENTRIES()


DESCRIPTOR_INSTANCE(Behaviour);
BEGIN_ENTRIES(Behaviour)
    ENTRY(data)
END_ENTRIES()


