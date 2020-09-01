
#include "behaviours/CameraController.cpp"


struct ObjectViewer : public IBehaviour {
    Aspect<Behaviour> free_controller; // CameraController
    Entity target;
    int mode;
    ObjectViewer() {};

    enum ModeType {
        Trackball,
        Free,
        NUM_MODES
    };

    void init(Aspect<Behaviour> _free_controller, Entity _target) {
        free_controller = _free_controller;
        target = _target;
        mode = Trackball;
        free_controller->enabled = false;
    }

    void mouse_handler(MouseEvent e) {
        if (mode == Trackball) {

        }
    }
    
    void keyboard_handler(KeyboardEvent e) {
        const KeyboardKeyCode mode_key = KEY_M;
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == mode_key) {
                // Leaving mode.
                if (mode == Free) {
                    free_controller->enabled = false;
                }
                mode = (mode+1) % NUM_MODES;
                // Entering mode.
                if (mode == Free) {
                    free_controller->enabled = true;
                }
            }
        }
    }
};
REFLECT_STRUCT(ObjectViewer)
BEGIN_ENTRIES(ObjectViewer)
    // Base IBehaviour
    ENTRY(world)
    ENTRY(entity)

    // ENTRY(free_controller)
    // ENTRY(target)
    // ENTRY(mode)
END_ENTRIES()
DESCRIPTOR_INSTANCE(ObjectViewer);



Entity create_object_viewer_cameraman(World &world, Entity target)
{
    Entity cameraman = world.entities.add();
    auto camera = cameraman.add<Camera>(0.1, 300, 0.1, 0.566);
    auto t = cameraman.add<Transform>();
    t->init(0,0,0);
    CameraController *controller = world.add<CameraController>(cameraman);
    Aspect<Behaviour> controller_b = cameraman.get<Behaviour>(); // Since this is the only behaviour, this will be the CameraController.
    controller->init();
    ObjectViewer *object_viewer = world.add<ObjectViewer>(cameraman);
    object_viewer->init(controller_b, target);
    return cameraman;
}
