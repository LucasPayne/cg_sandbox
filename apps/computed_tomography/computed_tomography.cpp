#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"

Aspect<Camera> main_camera;


struct Test : public IBehaviour {
    Image<vec3> image;
    Test(int m, int n) : image(m, n)
    {
    }

    void update() {
        image(rand() % image.height(), rand() % image.width()) = vec3::random(0,1);
        world->graphics.paint.bordered_sprite(main_camera, image.texture(), vec2(0.06,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
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
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity test = world.entities.add();
    world.add<Test>(test, 28, 28);
}


void App::close()
{
}
void App::loop()
{
    // std::vector<vec2> points = {vec2(0.2,0.2)};
    // world.graphics.paint.circles(main_camera, points, 0.2, vec4(0,0,1,1), 0.03, vec4(1,0,0,1));

    struct ellipse {
        vec2 origin;
        float theta;
        float a;
        float b;
        float density;
    };
    std::vector<ellipse> ellipses;
    ellipse e;
    e.origin = vec2(0.5,0.5);
    e.theta = 0;
    e.a = 0.1;
    e.b = 0.1;
    ellipses.push_back(e);

    vec2 c(0.5, 0.5);
    float r = 0.1;
    int s_n = 10;
    int theta_n = 10;
    for (int i = 0; i < theta_n; i++) {
        float theta = 2*M_PI*i*(1.0/theta_n);
        for (int j = 0; j < s_n; j++) {
            float s = -r + 2*r*j*(1.0/s_n);
            vec2 d1 = c + s*vec2(cos(theta), sin(theta)/0.566) + r*vec2(sin(theta), -cos(theta)/0.566);
            vec2 d2 = c + s*vec2(cos(theta), sin(theta)/0.566) - r*vec2(sin(theta), -cos(theta)/0.566);
            std::vector<vec2> points = {d1, d2};
            world.graphics.paint.chain_2D(main_camera, points, 1, vec4(0,0,1,1));

            vec2 origin = d1;
            vec2 dir = (d2 - d1).normalized();

            for (auto &el : ellipses) {
                float inv_a_squared = 1.0 / (el.a * el.a);
                float inv_b_squared = 1.0 / (el.b * el.b);

                std::cout << origin << "\n";
                vec2 origin_p = origin.inverse_transform(el.origin, el.theta);
                std::cout << "---> " << origin_p << "\n";
                vec2 dir_p = dir.rotate(el.theta);
                float A = dir_p.x()*dir_p.x() * inv_a_squared + dir_p.y()*dir_p.y() * inv_b_squared;
                float B = 2*origin_p.x()*dir_p.x() * inv_a_squared + 2*origin_p.y()*dir_p.y() * inv_b_squared;
                float C = origin_p.x()*origin_p.x() * inv_a_squared + origin_p.y()*origin_p.y() * inv_b_squared - 1;
                float discrim = B*B - 4*A*C;
                if (discrim >= 0) {
                    float sqrt_discrim = sqrt(discrim);
                    float inv_2A = 1.0 / 2*A;
                    float t1 = (B + sqrt_discrim)*inv_2A;
                    float t2 = (B - sqrt_discrim)*inv_2A;
                    vec2 p1 = origin + dir*t1;
                    vec2 p2 = origin + dir*t2;
                    std::vector<vec2> points = {p1, p2};
                    world.graphics.paint.circles(main_camera, points, 0.01, vec4(0,0,1,1), 0.01, vec4(1,0,0,1));
                }
            }
        }
    }

}

void App::window_handler(WindowEvent e)
{
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
