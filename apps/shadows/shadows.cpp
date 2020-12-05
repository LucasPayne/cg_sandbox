#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"
#include "world/graphics/image.h"

Aspect<Camera> main_camera;
Aspect<DirectionalLight> main_light;

struct LightRotate : public IBehaviour {
    Aspect<DirectionalLight> light;
    float theta;
    float height;
    LightRotate(Aspect<DirectionalLight> _light) :
        light{_light}
    {
        theta = 0;
        height = 0.3;
    }
    void update() {
        auto sm = world->graphics.directional_light_data(light).shadow_map(main_camera);
        // world->graphics.paint.bordered_depth_sprite(main_camera, sm.texture, vec2(0,0), 0.25,0.25, 3, vec4(0,0,0,1));

        if (world->input.keyboard.down(KEY_LEFT_ARROW)) {
            theta -= 1.f * dt;
        }
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) {
            theta += 1.f * dt;
        }
        if (world->input.keyboard.down(KEY_UP_ARROW)) {
            height += 0.5f * dt;
        }
        if (world->input.keyboard.down(KEY_DOWN_ARROW)) {
            height -= 0.5f * dt;
        }
        light->direction = vec3(cos(theta), -height, sin(theta)).normalized();
    }
};

struct Rotator : public IBehaviour {
    float theta;
    Rotator() : theta{0} {}
    void update() {
        theta += dt;
        auto t = entity.get<Transform>();
        t->rotation = Quaternion::from_axis_angle(vec3(0,1,0), theta);
    }
};


class App : public IGC::Callbacks {
public:
    World &world;
    App(World &world);

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);
};


std::vector<vec3> points;
float omega = 0.25;

App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,3,0);
    main_camera = cameraman.get<Camera>();
    cameraman.get<Camera>()->bottom_left = vec2(0.1, 0.1);
    cameraman.get<Camera>()->top_right = vec2(0.9, 0.9);
    cameraman.get<Camera>()->background_color = vec4(0.83,0.82,1,1);

    world.graphics.background_color = vec4(1,1,1,1);
    world.graphics.window_background_color = vec4(0,0,0,1);

    cameraman.get<Camera>()->bottom_left = vec2(0, 0.25);
    cameraman.get<Camera>()->top_right = vec2(0.5, 0.75);
    cameraman = create_cameraman(world);
    cameraman.get<Camera>()->bottom_left = vec2(0.5, 0.25);
    cameraman.get<Camera>()->top_right = vec2(0.8, 0.66);
    cameraman.get<Transform>()->position = vec3(0,6,0);
    cameraman.get<Camera>()->background_color = vec4(0.86,0.93,0.8,1);
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            Entity obj = create_mesh_object(world, "resources/models/bunny.off", "shaders/uniform_color.mat");
            obj.get<Transform>()->position = vec3(1.8*i, 0, 1.8*j);
            obj.get<Transform>()->scale = 5;
            obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.2,0.8,1);
        }
    }
    int n = 20;
    for (int i = 0; i < n; i++) {
        float r = 5;
        float theta = 2*M_PI*i*1.f/n;
        Entity obj = create_mesh_object(world, "resources/models/bunny.off", "shaders/uniform_color.mat");
        obj.get<Transform>()->position = r*vec3(cos(theta), 0, sin(theta));
        obj.get<Transform>()->position.y() -= 0.05;
        obj.get<Transform>()->rotation = Quaternion::from_axis_angle(vec3(0,1,0), theta);
        obj.get<Transform>()->scale = 5;
        obj.get<Drawable>()->material.properties.set_vec4("albedo", frand(),frand(),frand(),1);
    }
    Entity obj = create_mesh_object(world, "resources/models/dragon.off", "shaders/uniform_color.mat");
    obj.get<Transform>()->position.y() -= 0.45;
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.8,0.8,1);
    world.add<Rotator>(obj);

    obj = create_mesh_object(world, "resources/models/dragon.off", "shaders/uniform_color.mat");
    obj.get<Transform>()->position = vec3(10,0,10);;
    obj.get<Transform>()->position.y() -= 12 * 0.45;
    obj.get<Transform>()->scale = 10;
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.4,0,1);

    // obj = create_mesh_object(world, "resources/models/20mm_cube.stl", "shaders/uniform_color.mat");
    // obj.get<Transform>()->position = vec3(0,0,0);
    // obj.get<Transform>()->scale = 10;
    // obj.get<Drawable>()->material.properties.set_vec4("albedo", 1,0,0,1);
    // obj.get<Drawable>()->shadow_caster = false;
    SurfaceGeometry floor;
    auto a = floor.add_vertex(-1,0,-1);
    auto b = floor.add_vertex(1,0,-1);
    auto c = floor.add_vertex(1,0,1);
    auto d = floor.add_vertex(-1,0,1);
    floor.add_triangle(a, b, c);
    floor.add_triangle(a, c, d);
    auto floor_model = floor.to_model();
    obj = create_mesh_object(world, floor_model, "shaders/uniform_color.mat");
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 1,1,1,1);
    // obj.get<Drawable>()->shadow_caster = false;
    obj.get<Transform>()->scale = 10;
    obj.get<Transform>()->position = vec3(0,0.15,0);
    
    
    {
    Entity light = world.entities.add();
    // float sun_w = 0.005235999718313886; // computed for the 2D sun subtending 0.3 degrees.
    float sun_w = 0.07;
    light.add<DirectionalLight>(vec3(0,-1,0.5), vec3(0.7,0.7,0.7), sun_w);
    world.add<LightRotate>(light, light.get<DirectionalLight>());
    main_light = light.get<DirectionalLight>();
    }

    if (0) {
    Entity light = world.entities.add();
    // float sun_w = 0.005235999718313886; // computed for the 2D sun subtending 0.3 degrees.
    float sun_w = 0.07;
    light.add<DirectionalLight>(vec3(0,-1,0.5), vec3(0.3,0.3,0.3), sun_w);
    }
}


void App::close()
{
}

void App::loop()
{
    // View the G-buffer.
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("position").texture, vec2(0.25,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("normal").texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("albedo").texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("velocity").texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(0,0,0,1));

    world.graphics.paint.bordered_sprite(main_camera, world.graphics.screen_buffer.texture, vec2(0.25,0), 0.25,0.25, 3, vec4(1,1,1,1));
    world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("position").texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(1,1,1,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.read_post().framebuffer->texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(1,1,1,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.write_post().framebuffer->texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(1,1,1,1));
}

void App::window_handler(WindowEvent e)
{
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_G) world.graphics.update_lights();
        if (e.key.code == KEY_P) main_camera->top_right.y() += 0.025;
        if (e.key.code == KEY_O) main_camera->top_right.y() -= 0.025;
    }
    
}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    srand(time(0));

    printf("[main] Creating context...\n");
    IGC::Context context("Shadows");
    printf("[main] Creating world...\n");
    World world(context);

    context.enable_raw_mouse();

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
