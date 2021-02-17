#include <time.h>
#include <functional>
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



struct ParametricSurface : public IBehaviour {
    std::function<vec3(float, float)> f;
    ParametricSurface(std::function<vec3(float, float)> _f) :
        f{_f}
    {}

    void update() {
        const int tes_w = 20;
        const int tes_h = 20;
        const float step_w = 1.f / (tes_w - 1);
        const float step_h = 1.f / (tes_h - 1);
        const vec4 color = vec4(0.2*vec3(1,1,1),1);
        const float line_width = 3;

        for (int i = 0; i < tes_h-1; i++) {
	    float y = i * step_h;
            for (int j = 0; j < tes_w-1; j++) {
                float x = j * step_w;
                vec3 a = f(x, y);
                vec3 b = f(x + step_w, y);
                vec3 c = f(x + step_w, y + step_h);
                vec3 d = f(x, y + step_h);
                world->graphics.paint.line(a, b, line_width, color);
                world->graphics.paint.line(a, d, line_width, color);
                if (i == tes_h-2) world->graphics.paint.line(d, c, line_width, color);
                if (j == tes_w-2) world->graphics.paint.line(b, c, line_width, color);
            }
        }
    }
};





App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity e = world.entities.add();
    world.add<ParametricSurface>(e, [&](float x, float y) {
        return vec3(3*x, 9*(x-0.5)*(y-0.5), 3*y);
    });
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
