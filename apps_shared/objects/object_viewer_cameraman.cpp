
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
        Free,    // Fly around.
        Rotate, // Rotate around the object
        Lookat, // Look at the object.
        NUM_MODES
    };
    // Mode state.
    bool mode_rotate_dragging;
    float mode_rotate_last_x;
    float mode_rotate_last_y;
    float mode_rotate_radius;

    void extract_azimuth_and_angle(vec3 look_dir, float *azimuth, float *angle) {
        // note: 90 degree turn fixes the arithmetic here for some reason.
        //    (atan2 quadrant stuff?)
        *azimuth = atan2(-look_dir.z(), look_dir.x()) - M_PI/2;
        float horizontal_length = sqrt(look_dir.x()*look_dir.x() + look_dir.z()*look_dir.z());
        *angle = atan2(look_dir.y(), horizontal_length);
    }

    void init(Aspect<Behaviour> _free_controller, Entity _target) {
        free_controller = _free_controller;
        target = _target;
        mode = Lookat;
        free_controller->enabled = false;

        // State stuff.
        timer = 0.f;
        start_lookat = entity.get<Transform>()->position;
    }


    void mouse_handler(MouseEvent e) {
        auto transform = entity.get<Transform>();
        if (mode == Rotate) {
            if (e.button.code == MOUSE_LEFT) {
                if (e.action == MOUSE_BUTTON_PRESS) {
                    mode_rotate_dragging = true;
                    mode_rotate_last_x = e.cursor.x;
                    mode_rotate_last_y = e.cursor.y;
                } else if (e.action == MOUSE_BUTTON_RELEASE) {
                    mode_rotate_dragging = false;
                }
            }
            if (mode_rotate_dragging) {
                if (e.action == MOUSE_MOVE) {
                    // Move along the tangent plane of the sphere the camera is locked to.
                    float dx = e.cursor.x - mode_rotate_last_x;
                    float dy = e.cursor.y - mode_rotate_last_y;
                    printf("%.6f, %.6f\n", dx, dy);
                    vec3 p = (transform->matrix() * vec4(-10*dx, -10*dy, 0, 1)).xyz();
                    // Reproject to the sphere.
                    transform->position = target_position() + (p - target_position()).normalized() * mode_rotate_radius;

                    mode_rotate_last_x = e.cursor.x;
                    mode_rotate_last_y = e.cursor.y;
                }
            }
            if (e.action == MOUSE_SCROLL) {
                const float min_radius = 0.1;
                mode_rotate_radius -= e.scroll_y * dt;
                if (mode_rotate_radius < min_radius) mode_rotate_radius = min_radius;
                transform->position = target_position() + (transform->position - target_position()).normalized() * mode_rotate_radius;
            }
        }
        //todo: scroll wheel zoom in Rotate
    }


    void update() {

        auto transform = entity.get<Transform>();
        if (mode == Lookat || mode == Rotate) {
            // Interpolate view direction to look at the object.
            const float time_to_snap = 0.3;
            if (timer < time_to_snap) {
                transform->lookat(vec3::lerp(start_lookat, target_position(), timer / time_to_snap));
            } else {
                transform->lookat(target_position());
            }
        } else if (mode == Free) {

        }
        timer += dt;
    }
    
    void keyboard_handler(KeyboardEvent e) {

        if (e.action == KEYBOARD_PRESS) {
	    vec3 looking_at = (entity.get<Transform>()->matrix() * vec4(0,0,-1,1)).xyz();

            
            bool state_change = true;
            if (e.key.code == KEY_E) {
                mode = Free;
                free_controller->enabled = true;

                // Extract azimuth and angle.
                auto transform = entity.get<Transform>();

                vec3 look_dir = looking_at - transform->position;
                float azimuth, angle;
                extract_azimuth_and_angle(look_dir, &azimuth, &angle);

                CameraController *cc = free_controller->object_as<CameraController>();
                cc->azimuth = azimuth;
                cc->angle = angle;
            } else if (e.key.code == KEY_R) {
                mode = Rotate;
                start_lookat = looking_at;
	        mode_rotate_radius = (target_position() - entity.get<Transform>()->position).length();
	        mode_rotate_dragging = false;
                free_controller->enabled = false;
            } else if (e.key.code == KEY_T) {
                mode = Lookat;
                start_lookat = looking_at;
                free_controller->enabled = false;
            } else {
                state_change = false;
            }
            if (state_change) timer = 0.f;
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
