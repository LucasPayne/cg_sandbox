#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/object_viewer_cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"


Aspect<Camera> main_camera;
std::vector<vec2> bspline_positions;
std::vector<float> bspline_knots;


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
    Entity obj = create_mesh_object(world, "resources/models/large/buddha.obj", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    Entity cameraman = create_object_viewer_cameraman(world, obj);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    
    main_camera = cameraman.get<Camera>();

    int n = 10;
    bspline_positions = std::vector<vec2>(n);
    bspline_knots = std::vector<float>(n + 3);
    for (int i = 0; i < n; i++) {
        bspline_positions[i] = vec2::random(0.1, 0.9);
    }
    for (int i = 0; i < n+3; i++) {
        bspline_knots[i] = i;
    }
}


void App::close()
{
}
void App::loop()
{
    world.graphics.paint.quadratic_bspline(main_camera, bspline_positions, bspline_knots, 0.1, vec4(1,0,1,1));
}

void App::window_handler(WindowEvent e)
{
    force_aspect_ratio(e);
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_I) {
            for (int i = 0; i < bspline_knots.size(); i++) {
                bspline_knots[i] += (2*((i+1)%2)-1)*0.1;
            }
        }
        if (e.key.code == KEY_O) {
            for (int i = 0; i < bspline_knots.size(); i++) {
                bspline_knots[i] -= (2*((i+1)%2)-1)*0.1;
            }
        }
    }
}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
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
