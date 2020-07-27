#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"
World world;

struct Dolphin : public IBehaviour {
    vec3 velocity;
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        if (world->input.keyboard.down(KEY_S)) t->position.y() -= dt;
        if (world->input.keyboard.down(KEY_W)) t->position.y() += dt;
        if (world->input.keyboard.down(KEY_A)) t->position.x() -= dt;
        if (world->input.keyboard.down(KEY_D)) t->position.x() += dt;
    }
};

class App : public InputListener, public Looper {
    void init();
    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e) {}
    void mouse_handler(MouseEvent e) {}
};
void App::init()
{
    // Create a camera man.
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = world.em.add_aspect<Transform>(cameraman);
        t->init(0,0,0);
    }

    // Create a dolphin.

    // Resource<GeometricMaterial> gmat = assets.GeometricMaterial("resources/model_test/model_test.gmat");
    // Resource<Material> gmat = assets.Material("resources/model_test/model_test.mat");
    // Resource<ShadingModel> gmat = assets.ShadingModel("resources/model_test/model_test.sm");

    Resource<GeometricMaterial> gmat = world.rm.load_from_file<GeometricMaterial>("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.rm.load_from_file<Material>("resources/model_test/model_test.mat");
#if 1
{
    for (int i = 0; i < 10; i++) {
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dolphins.off", true, 0.0003);
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/stanford_bunny_low.off");
        VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dragon.off", true, 0.3);
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/icosahedron.off", true, -0.00025);
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(world.rm, dolphin_data);
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(-0.5 + frand(),-0.5 + frand(),-1);
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
        VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/bunny.off", true, 1);
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(world.rm, dolphin_data);
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(0,0,-1);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }
}
void App::close()
{
    printf("see ya\n");
}
void App::loop()
{
    for (Transform *t : world.em.aspects<Transform>()) {
        if (t->position == vec3(0,0,-1)) continue;
        t->lookat(vec3(0,0,-1));
        // t->lookat(t->position + vec3(cos(total_time),0,sin(total_time)));
        // t->rotation = Quaternion::from_axis_angle(vec3(0, total_time, 0));
    }
}

// Force the application to its constant-aspect-ratio subrectangle of the actual viewport.
void force_aspect_ratio(int width, int height, double wanted_aspect_ratio)
{
    double aspect_ratio = ((double) height) / width;
    if (aspect_ratio > wanted_aspect_ratio) {
        glViewport(0, (height - wanted_aspect_ratio * width)/2.0, width, wanted_aspect_ratio * width);
    }
    else {
        glViewport((width - height / wanted_aspect_ratio)/2.0, 0, height / wanted_aspect_ratio,  height);
    }
}
void reshape(int width, int height)
{
    float aspect_ratio = 0.566;
    force_aspect_ratio(width, height, aspect_ratio);
}

int main(int argc, char *argv[])
{
    world = World();
    App app = App();
    
    int window_width = 512;
    int window_height = 512;
    OpenGLContext context("Dragons", window_width, window_height);
    context.set_bg_color(0,0,0.3,1);
    context.set_fg_color(1,0.9,0.96,1);
    context.open();

    world = World();
    context.add_looper(&world);
    context.add_input_listener(&world);
    context.add_reshape_callback(reshape);
    world.input = InputState();
    context.add_input_listener(&world.input);

    context.add_looper(&app);
    context.add_input_listener(&app);

    context.enter_loop();
    context.close();
}

