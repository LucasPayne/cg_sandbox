#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"

#include "behaviours/CameraController.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"


CameraController *cc = nullptr;
Entity cameraman;


// Test packing/unpacking by writing an object to disk and reading it back.
template <typename T>
T transporter(T &obj)
{
    {
    std::ofstream file;
    file.open("tmp/transporter_tempfile.binary", std::ios::trunc | std::ios::out | std::ios::binary);
    Reflector::pack(obj, file);
    file.close();
    }

    std::ifstream file;
    T transportered_obj;
    file.open("tmp/transporter_tempfile.binary", std::ios::in | std::ios::binary);
    Reflector::unpack(file, transportered_obj);
    file.close();

    return transportered_obj;
}


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
#if 1
    // Create a camera man.
    {
        cameraman = world.em.new_entity();
        auto camera = cameraman.add<Camera>();
        camera->init_projective(0.1, 300, 0.1, 0.566);

        auto t = cameraman.add<Transform>();
        t->init(0,0,0);
        CameraController *controller = world.add<CameraController>(cameraman);
        controller->init();    

        controller->test_vector = {{1,2,3}, {2,9,8}, {-3,0,0}, {1,23,45}};
        controller->test_string = "hello, world";


        cc = controller; //make globally available.

        // printf("Testing...\n");
        // printf("Camera\n");
        // auto cc = cameraman.get<Camera>();
        // cc->bottom_left[0] = 0.1;
        // printf("Transform\n");
        // auto tt = cameraman.get<Transform>();
        // tt->position = vec3(1,1,1);
        // printf("Done\n");
    }
#endif
#if 1
    Resource<GeometricMaterial> gmat = world.assets.shading.load_geometric_material("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.assets.shading.load_material("resources/model_test/model_test.mat");

    // Create some objects.
    for (int i = 0; i < 1; i++) {
        // Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/buddha.obj");
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/venus_de_milo.obj");
        Entity dolphin = world.em.new_entity();
        auto t = dolphin.add<Transform>();
        vec3 base(0,0,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
        t->rotation = Quaternion::from_axis_angle(vec3(0,1,0), M_PI);
        // t->scale = 2;
        t->scale = 0.001;
        auto drawable = dolphin.add<Drawable>();
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }
#endif
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

    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_I) {
            Reflector::print(*cc);
            CameraController cc_t = transporter(*cc);
            Reflector::print(cc_t);

            // printf("Exporting prefab...\n");
            // world.export_prefab(cameraman, "resources/prefabs/cameraman.prefab");

            getchar();
        }
    }
}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    // Test basic serialization.
    // Quaternion q(0.3, -12, 31, 0.3222);
    // Reflector::print(q);
    // getchar();

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
