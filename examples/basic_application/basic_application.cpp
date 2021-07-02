#include "cg_sandbox.h"
#include "mesh_processing/mesh_processing.h"


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
    auto quad = SurfaceMesh();
    auto v1 = quad.add_vertex();
    auto v2 = quad.add_vertex();
    auto v3 = quad.add_vertex();
    auto v4 = quad.add_vertex();
    quad.add_triangle(v1, v3, v4);
    quad.add_triangle(v1, v4, v2);
    auto grid = Enmesh::grid_mesh(10, 10);

    std::cout << grid.num_vertices() << "\n";

    getchar();
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
