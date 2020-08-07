#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"
#include "registry/registry.h"

#include "behaviours/CameraController.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"


// Transporter for testing serialization.
template <typename T>
T transporter(T &obj) {
    std::ofstream outfile;
    outfile.open("test.binary", std::ios::trunc);
    pack(obj, outfile);
    outfile.close();
    
    std::ifstream infile;
    T transportered_obj;
    infile.open("test.binary");
    unpack(infile, transportered_obj);
    infile.close();
    return transportered_obj;
}
template <typename T>
void transporter_test(T &obj) {
    printf("Testing transporter...\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(" PRE-TRANSPORTED\n");
    printf("--------------------------------------------------------------------------------\n");
    print(obj);
    T obj_t = transporter(obj);
    printf("--------------------------------------------------------------------------------\n");
    printf(" TRANSPORTED\n");
    printf("--------------------------------------------------------------------------------\n");
    print(obj_t);
    getchar();
}

struct Dolphin : public IBehaviour {
    vec3 velocity;
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        if (world->input.keyboard.down(KEY_DOWN_ARROW)) t->position.y() -= dt;
        if (world->input.keyboard.down(KEY_UP_ARROW)) t->position.y() += dt;
        if (world->input.keyboard.down(KEY_LEFT_ARROW)) t->position.x() -= dt;
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) t->position.x() += dt;
    }
};
struct Bunny : public IBehaviour {
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        t->rotation = Quaternion::from_axis_angle(total_time * vec3(1,0,0));
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
    // Create a camera man.
#if 1
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = world.em.add_aspect<Transform>(cameraman);
        //-test serialization
        t->init(vec3(2,1,8.3232), Quaternion(1,2,3,-4.5));
        // print(*t);getchar();
        transporter_test(*t);

        t->init(0,0,0);

        CameraController *controller = world.add_behaviour<CameraController>(cameraman);
        controller->init();
    }


#endif 

    // Create a dolphin.

    // Resource<GeometricMaterial> gmat = assets.GeometricMaterial("resources/model_test/model_test.gmat");
    // Resource<Material> gmat = assets.Material("resources/model_test/model_test.mat");
    // Resource<ShadingModel> gmat = assets.ShadingModel("resources/model_test/model_test.sm");

    Resource<GeometricMaterial> gmat = world.assets.shading.load_geometric_material("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.assets.shading.load_material("resources/model_test/model_test.mat");
#if 1
{
    for (int i = 0; i < 25; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/dragon.off");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        vec3 base(3,3,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Dolphin *b = world.add_behaviour<Dolphin>(dolphin);
        b->velocity = vec3::random(-0.1,0.1);
    }
}
#endif
#if 1
    {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/nefertiti.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(0,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }
#endif
#if 1
    for (int i = 0; i < 2; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/buddha.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(1,i,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
        Bunny *b = world.add_behaviour<Bunny>(dolphin);
    }
#endif

    // transporter_test(world.em.m_entity_table);

    // Teleport the entity table out to disk and read it back.
    world.em.m_entity_table = transporter(world.em.m_entity_table);
    for (int i = 0; i < 3; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/nefertiti.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        vec3 base(0,0,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
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
    for (Transform *t : world.em.aspects<Transform>()) {
        if (t->position == vec3(0,0,-3)) continue;
        // t->lookat(vec3(0,0,-3));
        t->rotation = Quaternion::from_axis_angle(t->position.x()*0.2*t->position.y()*sin(total_time*0.2)*vec3(total_time, total_time, 0));
    }
    /* for (Dolphin *dolphin : world.behaviours<Dolphin>()) { */
    /*     Transform *t = world.em.get_aspect<Transform>(dolphin->entity); */
    /*     t->position += dolphin->velocity * dt; */
    /* } */
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
