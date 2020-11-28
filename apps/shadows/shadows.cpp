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
    vec3 axis;
    vec3 X;
    vec3 Z;
    float theta;
    LightRotate(Aspect<DirectionalLight> _light, vec3 _axis) :
        light{_light},
        axis{_axis.normalized()}
    {
        theta = M_PI;
    }
    void update() {
        auto t = light.sibling<Transform>();
        t->rotation = Quaternion::from_axis_angle(axis, theta);

        auto sm = world->graphics.directional_light_data(light).shadow_map(main_camera);
        world->graphics.paint.bordered_depth_sprite(main_camera, sm.texture, vec2(0.5,0.5), 0.28,0.28, 3, vec4(0,0,0,1));
        if (world->input.keyboard.down(KEY_LEFT_ARROW)) {
            theta -= 1.f * dt;
        }
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) {
            theta += 1.f * dt;
        }
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
    cameraman.get<Transform>()->position = vec3(0,0,0);
    main_camera = cameraman.get<Camera>();
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            Entity obj = create_mesh_object(world, "resources/models/bunny.off", "shaders/uniform_color.mat");
            obj.get<Transform>()->position = vec3(1.8*i, 0, 1.8*j);
            obj.get<Transform>()->scale = 5;
            obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.2,0.8,1);
        }
    }
    Entity obj = create_mesh_object(world, "resources/models/dragon.off", "shaders/uniform_color.mat");
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 0.8,0.8,0.8,1);

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
    obj.get<Drawable>()->material.properties.set_vec4("albedo", 1,0,0,1);
    obj.get<Drawable>()->shadow_caster = false;
    obj.get<Transform>()->scale = 100;
    obj.get<Transform>()->position = vec3(0,0.15,0);
    
    
    Entity light = world.entities.add();
    light.add<Transform>(0,0,0);
    light.add<DirectionalLight>(vec3(1,1,1), 1.5);
    world.add<LightRotate>(light, light.get<DirectionalLight>(), vec3(0.2,-1,0.3));
    main_light = light.get<DirectionalLight>();
}


void App::close()
{
}

vec3 frustum_points[8];
void App::loop()
{
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("position").texture, vec2(0.06,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("normal").texture, vec2(0.36,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
    // world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_component("albedo").texture, vec2(0.66,0.09), 0.28,0.28, 3, vec4(0,0,0,1));

    for (int i = 0; i < 2; i++) {
        std::vector<vec3> plane_points = {frustum_points[4*i+0],frustum_points[4*i+1],frustum_points[4*i+2],frustum_points[4*i+3],frustum_points[4*i+0]};
        world.graphics.paint.chain(plane_points, plane_points.size(), vec4(0,0,0,1));
    }
    for (int i = 0; i < 4; i++) {
        std::vector<vec3> ps = {frustum_points[i], frustum_points[i+4]};
        world.graphics.paint.chain(ps, ps.size(), vec4(0,0,0,1));
    }

    auto light_transform = main_light.sibling<Transform>();
    vec3 X = light_transform->right();
    vec3 Y = light_transform->up();
    vec3 Z = light_transform->forward();
    {std::vector<vec3> line = {light_transform->position, light_transform->position+X};
    world.graphics.paint.chain(line, line.size(), vec4(1,0,0,1));}
    {std::vector<vec3> line = {light_transform->position, light_transform->position+Y};
    world.graphics.paint.chain(line, line.size(), vec4(0,1,0,1));}
    {std::vector<vec3> line = {light_transform->position, light_transform->position+Z};
    world.graphics.paint.chain(line, line.size(), vec4(0,0,1,1));}

    vec3 transformed_frustum[8];
    for (int i = 0; i < 8; i++) {
        vec3 d = frustum_points[i];
        transformed_frustum[i] = vec3(vec3::dot(d, X), vec3::dot(d, Y), vec3::dot(d, Z));
    }
    vec3 mins = transformed_frustum[0];
    vec3 maxs = transformed_frustum[0];
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (transformed_frustum[i][j] < mins[j]) {
                mins[j] = transformed_frustum[i][j];
            } else if (transformed_frustum[i][j] > maxs[j]) {
                maxs[j] = transformed_frustum[i][j];
            }
        }
    }
    vec3 bounding_box[8];
    vec3 minsmaxs[2] = {mins, maxs};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                vec3 p = X*minsmaxs[i].x() + Y*minsmaxs[j].y() + Z*minsmaxs[k].z();
                bounding_box[4*i + 2*j + k] = p;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        world.graphics.paint.sphere(bounding_box[i], 0.1, vec4(0,1,1,1));
    }
    for (int i = 0; i < 4; i++) {
        std::vector<vec3> ps = {bounding_box[i], bounding_box[i+4]};
        world.graphics.paint.chain(ps, ps.size(), vec4(0,0.5,0.5,1));
    }
}

void App::window_handler(WindowEvent e)
{
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        float extent_a = 0.f;
        float extent_b = 0.05f;
        if (e.key.code == KEY_O) {
            vec3 _frustum_points[8] = {
                main_camera->frustum_point(-1,-1,extent_a),
                main_camera->frustum_point(1,-1,extent_a),
                main_camera->frustum_point(1,1,extent_a),
                main_camera->frustum_point(-1,1,extent_a),
                main_camera->frustum_point(-1,-1,extent_b),
                main_camera->frustum_point(1,-1,extent_b),
                main_camera->frustum_point(1,1,extent_b),
                main_camera->frustum_point(-1,1,extent_b),
            };
            for (int i = 0; i < 8; i++) {
                frustum_points[i] = _frustum_points[i];
            }
        }
        if (e.key.code == KEY_G) world.graphics.update_lights();
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
    World world;
    printf("[main] Adding world callbacks...\n");
    context.add_callbacks(&world);
    context.add_callbacks(&world.input);

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
