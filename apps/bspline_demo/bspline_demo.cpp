#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/object_viewer_cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"


struct BSplineDemo : public IBehaviour {
    Aspect<Camera> main_camera;
    std::vector<vec2> positions;
    std::vector<float> knots;
    float width;
    vec4 color;
    
    float point_radius;
    bool dragging_point;
    int dragging_point_index;

    BSplineDemo(Aspect<Camera> _main_camera, int n) :
        dragging_point{false}
    {
        main_camera = _main_camera;
        color = vec4(1,0.4,0.4,1);
        width = 0.008;
        point_radius = 0.005;
        positions = std::vector<vec2>(n);
        knots = std::vector<float>(n + 3);
        for (int i = 0; i < n; i++) {
            positions[i] = vec2::random(0.1, 0.9);
        }
        for (int i = 0; i < n+3; i++) {
            knots[i] = i;
        }
    }

    void update() {
        world->graphics.paint.quadratic_bspline(main_camera, positions, knots, width, color);
        world->graphics.paint.circles(main_camera, positions, point_radius, vec4(1,1,1,1), 0.333, vec4(0,0,0,1));
        // world->graphics.paint.lines(main_camera, positions, 0.001, vec4(0,0,0,1));
    }

    void mouse_handler(MouseEvent e) {
        if (e.action == MOUSE_BUTTON_PRESS) {
            for (int i = 0; i < positions.size(); i++) {
                if (vec2::dot(vec2(e.cursor.x, e.cursor.y) - positions[i],
                              vec2(e.cursor.x, e.cursor.y) - positions[i]) <= point_radius * point_radius) {
                    dragging_point = true;
                    dragging_point_index = i;
                }
            }
        } else if (e.action == MOUSE_BUTTON_RELEASE) {
            dragging_point = false;
        } else if (e.action == MOUSE_MOVE) {
            if (dragging_point) {
                positions[dragging_point_index] = vec2(e.cursor.x, e.cursor.y);
            }
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_I) {
                for (int i = 0; i < knots.size(); i++) {
                    knots[i] += (2*((i+1)%2)-1)*0.1;
                }
            }
            if (e.key.code == KEY_O) {
                for (int i = 0; i < knots.size(); i++) {
                    knots[i] -= (2*((i+1)%2)-1)*0.1;
                }
            }
            if (e.key.code == KEY_P) {
                for (int i = 0; i < positions.size(); i++) {
                    positions[i] = vec2::random(0.1, 0.9);
                }
            }
            float width_grow_factor = 1.25;
            if (e.key.code == KEY_Y) {
                width /= width_grow_factor;
            }
            if (e.key.code == KEY_U) {
                width *= width_grow_factor;
            }
        }
    }
};



struct WireframeDemo : public IBehaviour {
    SurfaceGeometry geom;

    WireframeDemo(const std::string &model_path, float scale = 1.f) {
        auto model = MLModel::load(model_path);
        geom.add_model(model);
        for (auto v : geom.vertices()) {
            geom.vertex_positions[v] *= scale;
        }
    }

    void update() {
        auto t = entity.get<Transform>();
        t->rotation = Quaternion::from_axis_angle(vec3(0,1,0), 0.2*total_time);
        world->graphics.paint.wireframe(geom, t->matrix(), 0.001);
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
    auto obj = create_mesh_object(world, "resources/models/large/buddha.obj", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    Entity cameraman = create_object_viewer_cameraman(world, obj);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    
    auto demo = world.entities.add();
    world.add<BSplineDemo>(demo, cameraman.get<Camera>(), 9);

    auto dragon = world.entities.add();
    dragon.add<Transform>(vec3(1,0,0));
    world.add<WireframeDemo>(dragon, "resources/models/dragon.off");
}


void App::close()
{
}
void App::loop()
{
}

void App::window_handler(WindowEvent e)
{
    force_aspect_ratio(e);
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    srand(time(0));

    printf("[main] Creating context...\n");
    IGC::Context context("A world");
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
