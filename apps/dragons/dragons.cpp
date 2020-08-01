#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"

#include "behaviours/CameraController.cpp"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"

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
<<<<<<< HEAD
        // t->rotation = Quaternion::from_axis_angle(total_time * vec3(1,0,0));
        t->rotation = Quaternion::from_axis_angle(0.2*total_time * vec3(0,1,0));
=======
        t->rotation = Quaternion::from_axis_angle(total_time * vec3(1,0,0));
>>>>>>> 408ed837dda892930c013f01098f3fd5e3442225
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
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = world.em.add_aspect<Transform>(cameraman);
        t->init(0,0,0);

        CameraController *controller = world.add_behaviour<CameraController>(cameraman);
        controller->init();
    }

    // Create a dolphin.

    // Resource<GeometricMaterial> gmat = assets.GeometricMaterial("resources/model_test/model_test.gmat");
    // Resource<Material> gmat = assets.Material("resources/model_test/model_test.mat");
    // Resource<ShadingModel> gmat = assets.ShadingModel("resources/model_test/model_test.sm");

#if 1
    Resource<GeometricMaterial> gmat = world.assets.shading.load_geometric_material("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.assets.shading.load_material("resources/model_test/model_test.mat");
#if 1
{
    for (int i = 0; i < 25; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/dragon.off");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
<<<<<<< HEAD
        vec3 base(3,3,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
=======
        t->init(2*(frand()-0.5),2*(frand()-0.5),-2);
>>>>>>> 408ed837dda892930c013f01098f3fd5e3442225
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Dolphin *b = world.add_behaviour<Dolphin>(dolphin);
        b->velocity = vec3::random(-0.1,0.1);
    }
}
#endif
    {
<<<<<<< HEAD
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/nefertiti.obj");
=======
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/bunny.off");
>>>>>>> 408ed837dda892930c013f01098f3fd5e3442225
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(0,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
<<<<<<< HEAD
    }
    {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/buddha.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(1,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
=======

>>>>>>> 408ed837dda892930c013f01098f3fd5e3442225
        Bunny *b = world.add_behaviour<Bunny>(dolphin);
    }
#endif
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
    IGC::Context context("Dragons");
    World world;
    context.add_callbacks(world);
    context.add_callbacks(world.input);

    App app(world);
    context.add_callbacks(app);

    context.enter_loop();
    context.close();
}
