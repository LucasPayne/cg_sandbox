#include "cg_sandbox.h"
#include "gl/gl.h"

#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"

#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"



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
    Entity e = create_cameraman(world);
    std::cout << e.num_aspects() << "\n";getchar();
    Entity obj = create_mesh_object(world, "resources/models/dragon.off", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
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
