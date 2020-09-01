#include "behaviours/CameraController.cpp"

Entity create_cameraman(World &world)
{
    Entity cameraman = world.entities.add();
    auto camera = cameraman.add<Camera>(0.1, 300, 0.1, 0.566);
    auto t = cameraman.add<Transform>();
    t->init(0,0,0);
    CameraController *controller = world.add<CameraController>(cameraman);
    controller->init();
    return cameraman;
}

