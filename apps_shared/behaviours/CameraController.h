
struct TestStruct {
    int a;
    int b;
    int c;
};
REFLECT_STRUCT(TestStruct);
BEGIN_ENTRIES(TestStruct)
    ENTRY(a)
    ENTRY(b)
    ENTRY(c)
END_ENTRIES()
DESCRIPTOR_INSTANCE(TestStruct);


struct CameraController : public IBehaviour {
    float azimuth;
    float angle;

    float strafe_speed;
    float forward_speed;
    float lift_speed;

    bool view_with_mouse;
    float key_view_speed_horizontal;
    float key_view_speed_vertical;

    float min_angle;
    float max_angle;

    #define BASE_MOUSE_SENSITIVITY 1.22
    // mouse_sensitivity multiplies the base sensitivity.
    float mouse_sensitivity;

    std::vector<TestStruct> test_vector;
    std::string test_string;

    CameraController() {}

    inline void lock_angle() {
        if (angle < min_angle) angle = min_angle;
        if (angle > max_angle) angle = max_angle;
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_E) {
                view_with_mouse = !view_with_mouse;
            }
        }
    }
    void mouse_handler(MouseEvent e) {
        if (view_with_mouse) {
            if (e.action == MOUSE_MOVE) {
                azimuth -= BASE_MOUSE_SENSITIVITY * mouse_sensitivity * e.cursor.dx;
                angle += BASE_MOUSE_SENSITIVITY * mouse_sensitivity * e.cursor.dy;
                lock_angle();
            }
        }
    }
    void update() {
        auto t = entity.get<Transform>();
        const KeyboardKeyCode up = KEY_W;
        const KeyboardKeyCode down = KEY_S;
        const KeyboardKeyCode left = KEY_A;
        const KeyboardKeyCode right = KEY_D;
        const KeyboardKeyCode view_up = KEY_K;
        const KeyboardKeyCode view_down = KEY_J;
        const KeyboardKeyCode view_left = KEY_H;
        const KeyboardKeyCode view_right = KEY_L;

        float forward_movement = 0;
        float side_movement = 0;
        float lift = 0;
        if (world->input.keyboard.down(up)) forward_movement += forward_speed;
        if (world->input.keyboard.down(down)) forward_movement -= forward_speed;
        if (world->input.keyboard.down(left)) side_movement -= strafe_speed;
        if (world->input.keyboard.down(right)) side_movement += strafe_speed;

        if (!view_with_mouse) {
            if (world->input.keyboard.down(view_left)) azimuth += key_view_speed_horizontal * dt;
            if (world->input.keyboard.down(view_right)) azimuth -= key_view_speed_horizontal * dt;
            if (world->input.keyboard.down(view_down)) angle -= key_view_speed_vertical * dt;
            if (world->input.keyboard.down(view_up)) angle += key_view_speed_vertical * dt;
        }

        if (world->input.keyboard.down(KEY_SPACE)) lift += lift_speed;
        if (world->input.keyboard.down(KEY_LEFT_SHIFT)) lift -= lift_speed;

        lock_angle();
        float cos_azimuth = cos(azimuth);
        float sin_azimuth = sin(azimuth);
        vec3 forward = vec3(-sin_azimuth, 0, -cos_azimuth);
        vec3 side = vec3(cos_azimuth, 0, -sin_azimuth);

        t->position += dt*(side_movement*side + forward_movement*forward);
        t->position.y() += dt*lift;

        Quaternion q1 = Quaternion::from_axis_angle(vec3(0,1,0), azimuth);
        Quaternion q2 = Quaternion::from_axis_angle(side, angle);
        t->rotation = q2 * q1;
    }
    void init() {
        printf("CAMERACONTROLLER INIT\n");
        strafe_speed = 1;
        forward_speed = 1;
        lift_speed = 1;
        key_view_speed_horizontal = 2;
        key_view_speed_vertical = 1.5;
        azimuth = 0;
        angle = 0;
        min_angle = -M_PI/2.0 + 0.15;
        max_angle = M_PI/2.0 - 0.15;
        view_with_mouse = false;
        mouse_sensitivity = 1;
    }
};
REFLECT_STRUCT(CameraController)
BEGIN_ENTRIES(CameraController)
    ENTRY(azimuth)
    ENTRY(angle)
    ENTRY(strafe_speed)
    ENTRY(forward_speed)
    ENTRY(lift_speed)
    ENTRY(view_with_mouse)
    ENTRY(key_view_speed_horizontal)
    ENTRY(key_view_speed_vertical)
    ENTRY(min_angle)
    ENTRY(max_angle)
    ENTRY(mouse_sensitivity)
    ENTRY(test_vector)
    ENTRY(test_string)
END_ENTRIES()
DESCRIPTOR_INSTANCE(CameraController);
