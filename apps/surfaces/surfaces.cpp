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
    std::function<vec3(float, float)> dfu;
    std::function<vec3(float, float)> dfv; // Jacobian

    vec2 param;

    ParametricSurface(std::function<vec3(float, float)> _f,
                      std::function<vec3(float, float)> _dfu,
                      std::function<vec3(float, float)> _dfv)
    : f{_f}, dfu{_dfu}, dfv{_dfv}, param(0.5, 0.5)
    {}

    vec3 surface_normal(float u, float v) {
        return -vec3::cross(dfu(u, v), dfv(u, v)).normalized();
    }

    void update() {
        const int tes_w = 20;
        const int tes_h = 20;
        const float step_w = 1.f / (tes_w - 1);
        const float step_h = 1.f / (tes_h - 1);
        const vec4 color = vec4(0.2*vec3(1,1,1),1);
        const float line_width = 3;

        auto t = entity.get<Transform>();
        auto p = t->position;

        for (int i = 0; i < tes_h-1; i++) {
	    float y = i * step_h;
            for (int j = 0; j < tes_w-1; j++) {
                float x = j * step_w;
                vec3 a = f(x, y);
                vec3 b = f(x + step_w, y);
                vec3 c = f(x + step_w, y + step_h);
                vec3 d = f(x, y + step_h);
                world->graphics.paint.line(p + a, p + b, line_width, color);
                world->graphics.paint.line(p + a, p + d, line_width, color);
                if (i == tes_h-2) world->graphics.paint.line(p + d, p + c, line_width, color);
                if (j == tes_w-2) world->graphics.paint.line(p + b, p + c, line_width, color);
            }
        }

        const vec4 sphere_color = vec4(1,0,0,1);
        const float sphere_size = 0.05;

        vec3 point = f(param.x(), param.y());
        vec3 normal = surface_normal(param.x(), param.y());
        world->graphics.paint.sphere(point, sphere_size, sphere_color);
        world->graphics.paint.line(point, point + 0.4*dfu(param.x(), param.y()).normalized(), line_width * 2, vec4(1,0,0,1));
        world->graphics.paint.line(point, point + 0.4*dfv(param.x(), param.y()).normalized(), line_width * 2, vec4(0,1,0,1));
        world->graphics.paint.line(point, point + 0.4 * normal, line_width * 2, vec4(0,0,1,1));

        mat2x2 m;
    }
};

struct Test1 : public IBehaviour {
    ParametricSurface *surface;
    Test1(ParametricSurface *_surface) : surface{_surface}
    {}

    void update() {
        surface->param = vec2(0.5 + 0.25 * cos(total_time), 0.5 + 0.25 * sin(total_time));
    }
};





App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity e = world.entities.add();
    e.add<Transform>(0,0,0);
    world.add<Test1>(e, world.add<ParametricSurface>(e,
        [](float u, float v) {
            return vec3(3*u, 9*(u-0.5)*(v-0.5), 3*v);
        },
        [](float u, float v) {
            return vec3(3, 9*(v-0.5), 0);
        },
        [](float u, float v) {
            return vec3(0, 9*(u-0.5), 3);
        }
    ));
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
