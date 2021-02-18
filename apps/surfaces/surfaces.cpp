/*--------------------------------------------------------------------------------
Some differential geometry of surfaces.
--------------------------------------------------------------------------------*/
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
    std::function<vec3(float, float)> ddfuu;
    std::function<vec3(float, float)> ddfuv;
    std::function<vec3(float, float)> ddfvv;

    vec2 param;

    ParametricSurface(std::function<vec3(float, float)> _f,
                      std::function<vec3(float, float)> _dfu,
                      std::function<vec3(float, float)> _dfv,
                      std::function<vec3(float, float)> _ddfuu,
                      std::function<vec3(float, float)> _ddfuv,
                      std::function<vec3(float, float)> _ddfvv)
    : f{_f}, dfu{_dfu}, dfv{_dfv},
      ddfuu{_ddfuu},
      ddfuv{_ddfuv},
      ddfvv{_ddfvv},
      param(0.5, 0.5)
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
        vec3 deru = dfu(param.x(), param.y());
        vec3 derv = dfv(param.x(), param.y());
        
        world->graphics.paint.line(point, point + 0.4*deru.normalized(), line_width * 2, vec4(1,0,0,1));
        world->graphics.paint.line(point, point + 0.4*derv.normalized(), line_width * 2, vec4(0,1,0,1));
        world->graphics.paint.line(point, point + 0.4 * normal, line_width * 2, vec4(0,0,1,1));

        // Calculate the first fundamental form.
        // E,F,G
        float E = vec3::dot(deru, deru);
        float F = vec3::dot(deru, derv);
        float G = vec3::dot(derv, derv);
        mat2x2 I = mat2x2(
            E, F,
            F, G
        );
        std::cout << I << "\n";

        // Calculate the second fundamental form.
        vec3 deruu = ddfuu(param.x(), param.y());
        vec3 deruv = ddfuv(param.x(), param.y());
        vec3 dervv = ddfvv(param.x(), param.y());
        float e = vec3::dot(normal, deruu);
        float f = vec3::dot(normal, deruv);
        float g = vec3::dot(normal, dervv);
        mat2x2 II = mat2x2(
            e, f,
            f, g
        );
        std::cout << II << "\n";
        mat2x2 M = I.inverse() * II;
        std::cout << M << "\n";

        mat2x2 V,D;
        std::tie(V,D) = M.diagonalize();
        std::cout << V << "\n";
        std::cout << D << "\n";

        vec2 e1 = V.column(0);
        vec2 e2 = V.column(1);
        std::cout << vec2::dot(e1, e2) << "\n";
        vec3 e1p = deru*e1.x() + derv*e1.y();
        vec3 e2p = deru*e2.x() + derv*e2.y();
        std::cout << vec3::dot(e1p, e2p) << "\n";

        world->graphics.paint.line(point, point + 0.4*e1p.normalized(), line_width * 2.5, vec4(1,0,1,1));
        world->graphics.paint.line(point, point + 0.4*e2p.normalized(), line_width * 2.5, vec4(1,0,1,1));

    }
};

struct Test1 : public IBehaviour {
    ParametricSurface *surface;
    Test1(ParametricSurface *_surface) : surface{_surface}
    {}

    void update() {
        surface->param = vec2(0.5 + 0.45 * cos(total_time), 0.5 + 0.45 * sin(total_time));
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
        // [](float u, float v) { // f
        //     return vec3(3*u, 4*u*u*v - 2*v*v, 4*v);
        // },
        // [](float u, float v) { // dfu
        //     return vec3(3, 8*u*v, 0);
        // },
        // [](float u, float v) { // dfv
        //     return vec3(0, 4*u*u - 4*v, 4);
        // },
        // [](float u, float v) { // ddfuu
        //     return vec3(0, 8*v, 0);
        // },
        // [](float u, float v) { // ddfuv
        //     return vec3(0, 8*u, 0);
        // },
        // [](float u, float v) { // ddfvv
        //     return vec3(0, -4, 0);
        // }
        [](float u, float v) { // f
            return vec3(u, u*u - 2*u*v + v*v, v);
        },
        [](float u, float v) { // dfu
            return vec3(1, 2*u - 2*v, 0);
        },
        [](float u, float v) { // dfv
            return vec3(0, 2*v - 2*u, 1);
        },
        [](float u, float v) { // ddfuu
            return vec3(0, 2, 0);
        },
        [](float u, float v) { // ddfuv
            return vec3(0, -2, 0);
        },
        [](float u, float v) { // ddfvv
            return vec3(0, 2, 0);
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
