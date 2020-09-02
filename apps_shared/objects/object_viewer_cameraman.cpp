
#include "behaviours/CameraController.cpp"


struct ObjectViewer : public IBehaviour {
    Aspect<Behaviour> free_controller; // CameraController
    Entity target;
    int mode;
    ObjectViewer() {};

    // State stuff.
    float timer; // Time since mode change.
    // Trackball.
    vec3 start_lookat; // What the camera was looking at when the mode changed to Trackball.

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

        // State stuff.
        timer = 0.f;
        start_lookat = entity.get<Transform>()->position;
    }

    void mouse_handler(MouseEvent e) {
    }

    void update() {
        if (mode == Trackball) {
            // Interpolate view direction to look at the object.
            const float time_to_snap = 0.3;
            if (timer < time_to_snap) {
                entity.get<Transform>()->lookat(vec3::lerp(start_lookat, target_position(), timer / time_to_snap));
            } else {
                entity.get<Transform>()->lookat(target_position());
            }
        }
        timer += dt;
    }
    
    void keyboard_handler(KeyboardEvent e) {
        const KeyboardKeyCode mode_key = KEY_M;
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == mode_key) {
                // Leaving mode.
                if (mode == Free) {
                    free_controller->enabled = false;
                }
                timer = 0.f;
                mode = (mode+1) % NUM_MODES;
                // Entering mode.

	        vec3 looking_at = (entity.get<Transform>()->matrix() * vec4(0,0,-1,1)).xyz();
                if (mode == Free) {
                    free_controller->enabled = true;

                    // Extract azimuth and angle.
                    auto transform = entity.get<Transform>();

                    vec3 look_dir = looking_at - transform->position;
                    // note: 90 degree turn fixes the arithmetic here for some reason.
                    //    (atan2 quadrant stuff?)
                    float azimuth = atan2(-look_dir.z(), look_dir.x()) - M_PI/2;
                    float horizontal_length = sqrt(look_dir.x()*look_dir.x() + look_dir.z()*look_dir.z());
                    float angle = atan2(look_dir.y(), horizontal_length);

                    CameraController *cc = free_controller->object_as<CameraController>();
                    cc->azimuth = azimuth;
                    cc->angle = angle;
                } else if (mode == Trackball) {
                    start_lookat = looking_at;
                }
            }
        }
    }

    // Helper methods.
    vec3 target_position() {
        return target.get<Transform>()->position;
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
