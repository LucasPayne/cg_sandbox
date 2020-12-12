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
SurfaceGeometry *model_geom;

Aspect<PointLight> test_point_light;

struct Follower : public IBehaviour {
    Entity follows;
    bool following;
    int key;
    Follower(Entity e, int _key) {
        follows = e;
        following = false;
        key = _key;
    }
    void update() {
        auto ft = follows.get<Transform>();
        auto t = entity.get<Transform>();
        auto light = entity.get<PointLight>();
        if (following) t->position = ft->position - ft->forward() * 4;

        vec3 p = t->position;
        world->graphics.paint.sphere(p, light->radius, vec4(1,1,1,1));
        float r = 0.76;
        world->graphics.paint.line(p, p + r*vec3(1,0,0), 3, vec4(1,0,0,1));
        world->graphics.paint.line(p, p + r*vec3(0,1,0), 3, vec4(0,1,0,1));
        world->graphics.paint.line(p, p + r*vec3(0,0,1), 3, vec4(0,0,1,1));

        if (following) {
            float s = 0.8;
            if (world->input.keyboard.down(KEY_M)) {
                light->radius *= 1.f + s * dt;
            }
            if (world->input.keyboard.down(KEY_N)) {
                light->radius *= 1.f - s * dt;
            }
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == key) following = !following;
        }
    }
};


struct LightRotate : public IBehaviour {
    Aspect<DirectionalLight> light;
    float theta;
    float height;
    bool on;
    LightRotate(Aspect<DirectionalLight> _light, float _height = 0.3, float _theta = 0, bool _on = true) :
        light{_light}
    {
        theta = _theta;
        height = _height;
        on = _on;
    }
    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_O) light->active = !light->active;
        }
    }
    void update() {
        auto sm = world->graphics.directional_light_data(light).shadow_map(main_camera);
        // world->graphics.paint.bordered_depth_sprite(sm.texture, vec2(0,0), 0.25,0.25, 3, vec4(0,0,0,1));

        if (on) {
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
            if (world->input.keyboard.down(KEY_M)) {
                light->width += 0.01;
            }
            if (world->input.keyboard.down(KEY_N)) {
                light->width -= 0.01;
            }
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


App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    // cameraman.get<Transform>()->position = vec3(0,3,0);
    main_camera = cameraman.get<Camera>();
    cameraman.get<Camera>()->bottom_left = vec2(0.02, 0.02);
    cameraman.get<Camera>()->top_right = vec2(0.98, 0.98);
    // cameraman.get<Camera>()->background_color = vec4(0.83,0.82,1,1);
    cameraman.get<Camera>()->background_color = vec4(0,0,0,1);

    world.graphics.background_color = vec4(1,1,1,1);
    world.graphics.window_background_color = vec4(0,0,0,1);

    if (0) {
        cameraman.get<Camera>()->bottom_left = vec2(0, 0.25);
        cameraman.get<Camera>()->top_right = vec2(0.5, 0.75);
        Entity cameraman2 = create_cameraman(world);
        cameraman2.get<Camera>()->bottom_left = vec2(0.5, 0.25);
        cameraman2.get<Camera>()->top_right = vec2(0.8, 0.66);
        cameraman2.get<Transform>()->position = vec3(0,6,0);
        cameraman2.get<Camera>()->background_color = vec4(0.86,0.93,0.8,1);
    }
    if (0) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                Entity obj = create_mesh_object(world, "resources/models/bunny.off", "shaders/uniform_color.mat");
                obj.get<Transform>()->position = vec3(1.8*i, 0, 1.8*j);
                obj.get<Transform>()->scale = 5;
                float r = frand();
                obj.get<Drawable>()->material.properties.set_vec4("albedo", r,r,r,1);
            }
        }
    }
    int n = 0;
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
    obj.get<Transform>()->position.y() -= 0.45;
    obj.get<Transform>()->position.x() = 2.4;
    obj.get<Transform>()->position.z() = 2.4;
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.3,0.3,0.8,1);
    world.add<Rotator>(obj);
    obj = create_mesh_object(world, "resources/models/dragon.off", "shaders/uniform_color.mat");
    obj.get<Transform>()->position.y() -= 0.45;
    obj.get<Transform>()->position.x() = -2.4;
    obj.get<Transform>()->position.z() = 2.4;
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.9,0.83,1,1);
    world.add<Rotator>(obj);

    if (0) {
        obj = create_mesh_object(world, "resources/models/dragon.off", "shaders/uniform_color.mat");
        obj.get<Transform>()->position = vec3(10,0,10);;
        obj.get<Transform>()->position.y() -= 12 * 0.45;
        obj.get<Transform>()->scale = 10;
        obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.4,0,1);
    }

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
    floor.add_triangle(c, b, a);
    floor.add_triangle(d, c, a);
    auto floor_model = floor.to_model();
    obj = create_mesh_object(world, floor_model, "shaders/uniform_color.mat");
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.5,0.5,1,1);
    // obj.get<Drawable>()->shadow_caster = false;
    obj.get<Transform>()->scale = 10;
    obj.get<Transform>()->position = vec3(0,0.15,0);

    if (0) {
        auto pillar = MLModel::load("resources/models/20mm_cube.stl");
        for (int i = 0; i < pillar.num_vertices; i++) {
            pillar.positions[i].x() *= 0.0003;
            pillar.positions[i].z() *= 0.0003;
        }
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                obj = create_mesh_object(world, pillar, "shaders/uniform_color.mat");
                obj.get<Drawable>()->material.properties.set_vec4("albedo", 1,1,1,1);
                obj.get<Transform>()->position = vec3(-1-0.015*i,1.5,-1-0.015*j);
            }
        }
    }
    
    
    if (1) {
        Entity light = world.entities.add();
        // float sun_w = 0.5 * 0.008726618569493142; // computed for the 2D sun subtending 0.5 degrees.
        float sun_w = 4 * 0.5 * 0.008726618569493142;
        light.add<DirectionalLight>(vec3(0,-1,0.5), vec3(1,1,1), sun_w);
        world.add<LightRotate>(light, light.get<DirectionalLight>());
        main_light = light.get<DirectionalLight>();
    }

    if (0) {
        Entity light = world.entities.add();
        // float sun_w = 0.005235999718313886; // computed for the 2D sun subtending 0.3 degrees.
        float sun_w = 0.07;
        light.add<DirectionalLight>(vec3(0,-1,0.5), vec3(0.8,0.8,0.8), sun_w);
        world.add<LightRotate>(light, light.get<DirectionalLight>(), 0.2, M_PI/3, false);
    }
    if (0) {
        Entity light = world.entities.add();
        // float sun_w = 0.005235999718313886; // computed for the 2D sun subtending 0.3 degrees.
        float sun_w = 0.07;
        light.add<DirectionalLight>(vec3(0,-1,0.5), vec3(0.8,0.8,0.8), sun_w);
        world.add<LightRotate>(light, light.get<DirectionalLight>(), 0.3, M_PI/3+1.31451, false);
    }

    if (0) {
        Entity light = world.entities.add();
        float intensity = 20;
        test_point_light = light.add<PointLight>(vec3(intensity), 0.2);
        light.add<Transform>(1.8,1,1.8);
        world.add<Follower>(light, cameraman, KEY_P);
    }
    if (0) {
        Entity light = world.entities.add();
        float intensity = 10;
        light.add<PointLight>(vec3(intensity), 0.03);
        light.add<Transform>(3,2,3);
        world.add<Follower>(light, cameraman, KEY_I);
    }

    // auto model = MLModel::load("resources/models/20mm_cube.stl");
    auto model = MLModel::load("resources/models/dragon.off");
    model_geom = new SurfaceGeometry(); //global
    model_geom->add_model(model);
    for (auto v : model_geom->vertices()) {
        model_geom->vertex_positions[v] *= 1.3;
    }
}


void App::close()
{
}

void App::loop()
{
    // View the G-buffer.
    // world.graphics.paint.bordered_sprite(world.graphics.gbuffer_component("position").texture, vec2(0.25,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(world.graphics.gbuffer_component("normal").texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // // world.graphics.paint.bordered_sprite(world.graphics.gbuffer_component("albedo").texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(world.graphics.gbuffer_component("velocity").texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(0,0,0,1));

    // world.graphics.paint.bordered_sprite(world.graphics.screen_buffer.texture, vec2(0.25,0), 0.25,0.25, 3, vec4(1,1,1,1));
    // world.graphics.paint.bordered_sprite(world.graphics.gbuffer_component("position").texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(1,0,0,1));

    auto &paint = world.graphics.paint;

if (1) {
#if 1
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            paint.array_depth_sprite(world.graphics.directional_light_data(main_light).shadow_map(main_camera).texture, vec2(0.25*i,0.25*j), 0.25, 0.25, 2*i + j);
        }
    }
#else
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            paint.cube_map_depth_sprite(world.graphics.point_light_data(test_point_light).shadow_map(main_camera).cube_map, vec2(0.125*i,0.125*j), 0.125, 0.125, 2*i + j);
        }
    }
#endif
}

    // std::vector<vec2> ps(2);
    // ps[0] = vec2(0,0);
    // ps[1] = vec2(1,1);
    // paint.chain_2D(ps, 10, vec4(0,1,0,1));
    // world.graphics.paint.bordered_sprite(world.graphics.read_post().framebuffer->texture, vec2(0.25*2,0), 0.25,0.25, 3, vec4(1,1,1,1));
    // world.graphics.paint.bordered_sprite(world.graphics.write_post().framebuffer->texture, vec2(0.25*3,0), 0.25,0.25, 3, vec4(1,1,1,1));

    // int i = 0;
    // for (auto light : world.entities.aspects<DirectionalLight>()) {
    //     auto &shadow_map = world.graphics.directional_light_data(light).shadow_map(main_camera);
    //     for (int j = 0; j < 2; j++) {
    //         for (int k = 0; k < 2; k++) {
    //             world.graphics.paint.bordered_depth_sprite_layer(shadow_map.texture, vec2(j*0.25/2,0.25*i+k*0.25/2), 0.25/2,0.25/2, 3, vec4(1,0,0,1), 2*j+k);
    //         }
    //     }
    //     i++;
    // }

    // paint.depth_sprite(world.graphics.gbuffer_component("depth").texture, vec2(0.75,0.75), 0.25, 0.25);
    // paint.depth_sprite(world.graphics.screen_buffer.depth_texture, vec2(0.5,0.75), 0.25, 0.25);

    // world.graphics.paint.wireframe(*model_geom, mat4x4::translation(vec3(4,-0.7,4)), 0.001);

    paint.array_depth_sprite(world.graphics.directional_light_data(main_light).shadow_map(main_camera).summed_area_table_texture, vec2(0.5,0.75), 0.25, 0.25, 0);
}

void App::window_handler(WindowEvent e)
{
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_R) world.graphics.compile_shaders();
        // if (e.key.code == KEY_P) main_camera->top_right.y() += 0.025;
        // if (e.key.code == KEY_O) main_camera->top_right.y() -= 0.025;
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
