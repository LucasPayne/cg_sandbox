/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"
#include "entity_model/entity_model.h"

DefineAspect(SomeValues) {
    float x;
    int nums[16];
    bool flag;

    static void create() {

    }
    static void teardown() {

    }
};

DefineAspect(SomeMoreStuff) {
    float x;
    int nums[23];

    static void create() {

    }
    static void teardown() {

    }
};

void CGSandbox::init()
{
    AspectType type1 = SomeValues::type;
    AspectType type = SomeMoreStuff::type;
    printf("type: %d\n", type);
    AspectInfo info = AspectInfo::type_info(type);
    std::cout << "size: " << info.size << "\n";

    #define N 480
    Entity entities[N];

    for (int i = 0; i < N; i++) {
        Entity e = entity_model.new_entity();
        SomeValues *sv = entity_model.add_aspect<SomeValues>(e);
        sv->x = 12.31;
        SomeMoreStuff *sms = entity_model.add_aspect<SomeMoreStuff>(e);
        // entity_model.print_entity(e);

        SomeValues *_sv = entity_model.get_aspect<SomeValues>(e);
        printf("x: %.2f\n", _sv->x);
        entities[i] = e;
    }
    for (int i = 0; i < N; i++) {
        if (frand() > 0.5) entity_model.destroy_entity(entities[i]);
    }
    entity_model.print_entity_ids();
    

    // e.add<SomeValues>(1.3, 32, true);
    // e.add<SomeMoreStuff>(1.66, 12);
    // e.remove<SomeValues>();
    // Aspect a = e.add<SomeValues>(2.87, 10, false);
    // a.x = 87.13;
    // a.print();
}
void CGSandbox::close()
{
}
void CGSandbox::loop()
{
}

void CGSandbox::key_callback(int key, int action)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
        }
    }
}
void CGSandbox::cursor_position_callback(double x, double y)
{
}
void CGSandbox::cursor_move_callback(double x, double y)
{
}
void CGSandbox::mouse_button_callback(int button, int action)
{
}
