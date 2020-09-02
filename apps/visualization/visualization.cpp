#include "cg_sandbox.h"
#include "gl/gl.h"

#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"

#include "objects/mesh_object.cpp"
// #include "objects/cameraman.cpp"
#include "objects/object_viewer_cameraman.cpp"

#include "behaviours/Trackball.cpp"



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
    mat4x4 M(0, 0, 8, 4,   2, 0, 9, 1,  3, 0, -3, 2,   4, 1, 2, 3);
    // mat4x4 M(1, 0, 2, 0,   2, 1, 9, 1,  3, 0, -3, 2,   4, 1, 2, 3);
    // for (int i = 0; i < 16; i++) {
    //     M.entries[i] = 2*frand() - 1;
    // }
    for (int i = 0; i < 5; i++) {
        vec4 v;
        for (int j = 0; j < 4; j++) v.entries[j] = (rand() % 15) - 7;
        vec4 b = M*v;
        std::cout << "v: " << v << "\n";
        std::cout << "b: " << b << "\n";
        getchar();
        std::cout << "solution should = v: " << M.solve(b) << "\n";
        getchar();
    }


    vec4 x = M.solve(vec4(0,1,2,3));
    std::cout << x << "\n";

    mat4x4 Minv = M.inverse();
    std::cout << M << "\n";
    std::cout << Minv << "\n";
    std::cout << M * Minv << "\n";
    std::cout << M.determinant() << "\n";
    getchar();
    


    Entity obj = create_mesh_object(world, "resources/models/large/buddha.obj", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    Trackball *tb = world.add<Trackball>(obj);
    tb->init();

    Entity cameraman = create_object_viewer_cameraman(world, obj);
    cameraman.get<Transform>()->position = vec3(0,0,2);
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
