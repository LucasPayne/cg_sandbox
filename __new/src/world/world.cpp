#include "world/world.h"


World::World(IGC::Context &_context) :
    // Initialize subsystems and possibly pass them a World reference.
    context{_context},
    entities(),
    resources(),
    input()
{
    printf("[world] Creating world...\n");

    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) {\
        resources.register_resource_type<NAME>();\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering resource types...\n");
    REGISTER_RESOURCE_TYPE(GLShader);
    REGISTER_RESOURCE_TYPE(GLShaderProgram);
    printf("[world] Resource system initialized.\n");

    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) {\
        entities.register_aspect_type<NAME>();\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering aspect types...\n");
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Behaviour);
    printf("[world] Entity system initialized.\n");

    // Initialize the screen size information for the initial window size.
    int width, height;
    context.get_screen_size(&width, &height);
    window_update(width, height);

    // Connect to the system windowing/graphics context.
    context.add_callbacks(this);
    context.add_callbacks(&input);
}



void World::loop()
{
    printf("================================================================================\n");
    printf("[world] Frame start.\n");
    printf("--------------------------------------------------------------------------------\n");

    /*--------------------------------------------------------------------------------
        Wake up newly created entity behaviours.
    --------------------------------------------------------------------------------*/
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->waiting_to_be_initialized) {
            b->waiting_to_be_initialized = false;
            b->enabled = true;
            b->init(); // Initialize the behaviour.
        }
    }

    /*--------------------------------------------------------------------------------
        Update entity behaviours.
    --------------------------------------------------------------------------------*/
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->update();
    }

    // graphics.render();

    /*--------------------------------------------------------------------------------
        Post-render update entities.
    --------------------------------------------------------------------------------*/
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->post_render_update();
    }

    printf("Frame-rate: %d\n", (int) floor(1.f / dt + 0.5f));
}

void World::close()
{
    printf("[world] Closing.\n");
}


void World::keyboard_handler(KeyboardEvent e)
{
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) {
            b->keyboard_handler(e);
        }
    }
}


void World::mouse_handler(MouseEvent e)
{
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->mouse_handler(e);
    }
}


void World::window_handler(WindowEvent e)
{
    if (e.type == WINDOW_EVENT_FRAMEBUFFER_SIZE) {
        window_update(e.framebuffer.width, e.framebuffer.height);
    }
}
void World::window_update(int width, int height)
{
    const float wanted_aspect_ratio = 0.566;
    double aspect_ratio = ((double) height) / width;

    int x, y, w, h;
    if (aspect_ratio > wanted_aspect_ratio) {
        x = 0;
        y = (height - wanted_aspect_ratio * width)/2.0;
        w = width;
        h = wanted_aspect_ratio * width;
    }
    else {
        x = (width - height / wanted_aspect_ratio)/2.0;
        y = 0;
        w = height / wanted_aspect_ratio;
        h = height;
    }
    // graphics.screen_buffer.resolution_x = w;
    // graphics.screen_buffer.resolution_y = h;
    // graphics.window_viewport = Viewport(x, y, w, h);
    // graphics.window_width = width;
    // graphics.window_height = height;
}




// Utilities.
bool World::screen_to_ray(float screen_x, float screen_y, Ray *ray)
{
    // Get the highest-priority (lowest layer) camera which has its viewport overlapping this screen position.
    bool any = false;
    Aspect<Camera> used_camera;
    for (auto &camera : entities.aspects<Camera>()) {
        if (camera->in_viewport(screen_x, screen_y)) {
            if (!any) {
                any = true;
                used_camera = camera;
            } else {
                if (camera->layer < used_camera->layer) used_camera = camera;
            }
        }
    }
    if (!any) return false;

    float camera_x, camera_y;
    used_camera->to_viewport(screen_x, screen_y, &camera_x, &camera_y);
    *ray = used_camera->ray(camera_x, camera_y);
    // printf("screen_x: %.2f, screen_y: %.2f\n", screen_x, screen_y);
    // printf("camera_x: %.2f, camera_y: %.2f\n", camera_x, camera_y);
    // getchar();
    return true;
}


inline vec2 _key_vector_helper(const World &world, KeyboardKeys left, KeyboardKeys right, KeyboardKeys down, KeyboardKeys up)
{
    int dx = 0;
    int dy = 0;
    if (world.input.keyboard.down(left)) {
        dx --;
    }
    if (world.input.keyboard.down(right)) {
        dx ++;
    }
    if (world.input.keyboard.down(down)) {
        dy --;
    }
    if (world.input.keyboard.down(up)) {
        dy ++;
    }
    return vec2(dx, dy);
}
vec2 World::arrow_key_vector() const
{
    return _key_vector_helper(*this, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW);
}
vec2 World::wasd_key_vector() const
{
    return _key_vector_helper(*this, KEY_A, KEY_D, KEY_S, KEY_W);
}
vec2 World::hjkl_key_vector() const
{
    return _key_vector_helper(*this, KEY_H, KEY_L, KEY_J, KEY_K);
}
