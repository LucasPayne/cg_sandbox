#include "cg_sandbox.h"
#include "mesh_processing/mesh_processing.h"
#include "CameraController.cpp"


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
    auto mesh = SurfaceMesh();
    auto v1 = mesh.add_vertex();
    auto v2 = mesh.add_vertex();
    auto v3 = mesh.add_vertex();
    auto v4 = mesh.add_vertex();
    mesh.add_triangle(v1, v3, v4);
    mesh.add_triangle(v1, v4, v2);

    mesh.lock();
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
}

void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    printf("[main] Creating context...\n");
    IGC::Context context("A world");
    printf("[main] Creating world...\n");
    World world(context);

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
