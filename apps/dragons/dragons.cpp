#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"

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
        Transform *t = world->em.get_aspect<Transform>(entity);
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
        strafe_speed = 1;
        forward_speed = 1;
        lift_speed = 1;
        key_view_speed_horizontal = 2;
        key_view_speed_vertical = 1.5;
        azimuth = 0;
        angle = 0;
        min_angle = -M_PI/3.0;
        max_angle = M_PI/3.0;
        view_with_mouse = false;
        mouse_sensitivity = 1;
    }
};


struct Dolphin : public IBehaviour {
    vec3 velocity;
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        if (world->input.keyboard.down(KEY_DOWN_ARROW)) t->position.y() -= dt;
        if (world->input.keyboard.down(KEY_UP_ARROW)) t->position.y() += dt;
        if (world->input.keyboard.down(KEY_LEFT_ARROW)) t->position.x() -= dt;
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) t->position.x() += dt;
    }
};
struct Bunny : public IBehaviour {
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        t->rotation = Quaternion::from_axis_angle(total_time * vec3(1,0,0));
    }
};

class App : public IGC::Callbacks {
    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e) {}
    void mouse_handler(MouseEvent e) {}
};
App::App(CGS_World &world)
{
    world.assets.models.load("resources/models/dragon.off");

    // Create a camera man.
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = world.em.add_aspect<Transform>(cameraman);
        t->init(0,0,0);

        CameraController *controller = world.add_behaviour<CameraController>(cameraman);
        controller->init();
    }

    // Create a dolphin.

    // Resource<GeometricMaterial> gmat = assets.GeometricMaterial("resources/model_test/model_test.gmat");
    // Resource<Material> gmat = assets.Material("resources/model_test/model_test.mat");
    // Resource<ShadingModel> gmat = assets.ShadingModel("resources/model_test/model_test.sm");

#if 0
    Resource<GeometricMaterial> gmat = world.rm.load_from_file<GeometricMaterial>("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.rm.load_from_file<Material>("resources/model_test/model_test.mat");
#if 1
{
    for (int i = 0; i < 25; i++) {
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dolphins.off", true, 0.0003);
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/stanford_bunny_low.off");
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dragon.off", true, 0.3);
        VertexArrayData dolphin_data;
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/icosahedron.off", true, -0.00025);
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(world.rm, dolphin_data);
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(2*(frand()-0.5),2*(frand()-0.5),-2);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Dolphin *b = world.add_behaviour<Dolphin>(dolphin);
        b->velocity = vec3::random(-0.1,0.1);
    }
}
#endif
    {
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/bunny.off", true, 1);
        VertexArrayData dolphin_data;
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(world.rm, dolphin_data);
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(0,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Bunny *b = world.add_behaviour<Bunny>(dolphin);
    }
#endif
}
void App::close()
{
    printf("see ya\n");
}
void App::loop()
{
    for (Transform *t : world.em.aspects<Transform>()) {
        if (t->position == vec3(0,0,-3)) continue;
        t->lookat(vec3(0,0,-3));
        // t->lookat(t->position + vec3(cos(total_time),1,sin(total_time)));
        // t->rotation = Quaternion::from_axis_angle(vec3(0, total_time, 0));
    }
    // for (Dolphin *dolphin : world.behaviours<Dolphin>()) {
    //     Transform *t = world.em.get_aspect<Transform>(dolphin->entity);
    //     t->position += dolphin->velocity * dt;
    // }
}

// Force the application to its constant-aspect-ratio subrectangle of the actual viewport.
void force_aspect_ratio(int width, int height, double wanted_aspect_ratio)
{
    double aspect_ratio = ((double) height) / width;
    if (aspect_ratio > wanted_aspect_ratio) {
        glViewport(0, (height - wanted_aspect_ratio * width)/2.0, width, wanted_aspect_ratio * width);
    }
    else {
        glViewport((width - height / wanted_aspect_ratio)/2.0, 0, height / wanted_aspect_ratio,  height);
    }
}
void reshape(int width, int height)
{
    float aspect_ratio = 0.566;
    force_aspect_ratio(width, height, aspect_ratio);
}

int main(int argc, char *argv[])
{
    IGC::Context context("Dragons");
    CGS::World world;
    context.add_callbacks(world);

    App app(world);
    context.add_callbacks(app);

    context.loop();
    context.close();
}
