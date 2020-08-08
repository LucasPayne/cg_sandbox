#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"
#include "registry/registry.h"

#include "behaviours/CameraController.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"

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
    // Create a camera man.
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Aspect<Transform> t = cameraman.add<Transform>();
        t->init(0,0,0);
        CameraController *controller = world.add_behaviour<CameraController>(cameraman);
        controller->init();
    }
    // Create some objects.
    for (int i = 0; i < 3; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/nefertiti.obj");
        Entity dolphin = world.em.new_entity();
        Aspect<Transform> t = dolphin.add<Transform>();
        vec3 base(0,0,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
        Aspect<Drawable> drawable = dolphin.add<Drawable>();
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Dolphin *b = world.add_behaviour<Dolphin>(dolphin);
        b->velocity = vec3::random(-0.1,0.1);
    }
}
void App::close()
{
    printf("see ya\n");
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
    IGC::Context context("Dragons");
    printf("[main] Creating world...\n");
    Reference<World> world = World::new_world();
    printf("[main] Adding world callbacks...\n");
    context.add_callbacks(*world);
    context.add_callbacks(world->input);

    printf("[main] Creating app...\n");
    App app(*world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
