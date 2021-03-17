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

struct FluidDemo : public IBehaviour {
    int m;
    int n;

    vec2 bl;
    vec2 tr;

    FluidDemo(int _m, int _n) : m{_m}, n{_n}
    {
        bl = vec2(0.2, 0.2);
        tr = vec2(0.8, 0.8);
    }
    vec2 grid_pos(int i, int j) {
        return vec2(bl.x() + (tr.x()-bl.x())*j/n,
                    bl.y() + (tr.y()-bl.y())*i/m);
    }
    
    void post_render_update() {
        auto &paint = world->graphics.paint;
        vec4 grid_color = vec4(1,0,0,1);
        for (int i = 0; i <= m; i++) {
            std::vector<vec2> points = { grid_pos(i, 0), grid_pos(i, n) };
	    paint.chain_2D(points, 0.5, grid_color);
        }
        for (int i = 0; i <= n; i++) {
            std::vector<vec2> points = { grid_pos(0, i), grid_pos(m, i) };
	    paint.chain_2D(points, 0.5, grid_color);
        }
    }

};

App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity fluid_e = world.entities.add();
    auto fluid = world.add<FluidDemo>(fluid_e, 20, 20);
}


void App::close()
{
}

void App::loop()
{
}

void App::window_handler(WindowEvent e)
{
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        // if (e.key.code == KEY_R) world.graphics.compile_shaders();
    }
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
    World world(context);
    printf("[main] Adding world callbacks...\n");

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
