#ifndef WORLD_REFERENCE_H
#define WORLD_REFERENCE_H
// This is separated so the World's component subsystems can include it instead of the full world.h

class World;

struct WorldReference {
    WorldReference(TableHandle _handle) : handle{_handle} {}
    TableHandle handle;
    World &operator*();
    World *operator->();
};

#endif // WORLD_REFERENCE_H
