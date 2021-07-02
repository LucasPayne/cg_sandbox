#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/cameraman.cpp"

struct WaveDomain : public IBehaviour {
    float radius;
    int n;
    std::vector<float> values;
    std::vector<float> velocities;

    void init(float _radius, int _n) {
        radius = _radius;
        n = _n;
        values = std::vector<float>(n);
        velocities = std::vector<float>(n);
        float k = 4.2;
        for (int i = 0; i < n; i++) {
            // values[i] = exp(-0.1*abs(i - n/2));
            values[i] = sin(k * 2*M_PI*i/n);
        }
        
    }
    void update() {

        float dx = 2*M_PI*radius/n;
        float inv_dx = 1.0 / dx;
        
        for (int i = 0; i < n; i++) {
            int prev = (i-1)%n;
            int next = (i+1)%n;
            float ddf = inv_dx*inv_dx * (values[prev] + values[next] - 2*values[i]);
            velocities[i] += 0.1 * dt * ddf;
        }
        for (int i = 0; i < n; i++) {
            values[i] += dt * velocities[i];
        }

        vec3 position = entity.get<Transform>()->position;
        std::vector<vec3> points;
        std::vector<vec3> ground_points;
        float inv_n = 1.0 / n;
        for (int i = 0; i < n+1; i++) {
            vec3 p = vec3(position.x() + radius*cos(2*M_PI*inv_n*i), position.y() + values[i%n], position.z() + radius*sin(2*M_PI*inv_n*i));
            points.push_back(p);
            ground_points.push_back(vec3(p.x(), position.y(), p.z()));
        }

        world->graphics.paint.chain(points, 10, vec4(0,0,0,1));
        world->graphics.paint.chain(ground_points, 10, vec4(0.8,0.8,1,1));
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
void App::loop()
{
}
void App::close()
{
}
App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,1,3);

    Entity domain = world.entities.add();
    domain.add<Transform>(0,0,0);
    WaveDomain *wd = world.add<WaveDomain>(domain);
    wd->init(1, 500);

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
