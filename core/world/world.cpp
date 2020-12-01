#include "world/world.h"


World::World() :
    // Initialize subsystems and possibly pass them a World reference.
    entities(),
    resources(),
    assets(*this),
    graphics(*this),
    input(),
    screen_has_resized_this_frame{false}
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
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingBlock); //Data layout description for material properties.
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);
    printf("[world] Resource system initialized.\n");

    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) {\
        entities.register_aspect_type<NAME>();\
        printf("[world]   Registered \"%s\".\n", #NAME);\
    }
    printf("[world]  Registering aspect types...\n");
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);
    REGISTER_ASPECT_TYPE(Behaviour);
    REGISTER_ASPECT_TYPE(DirectionalLight);
    printf("[world] Entity system initialized.\n");

    // Order-sensitive subsystem initialization.
    graphics.init();
}



void World::loop()
{
    printf("================================================================================\n");
    printf("[world] Frame start.\n");
    printf("--------------------------------------------------------------------------------\n");

    /*--------------------------------------------------------------------------------
        Update entity behaviours.
    --------------------------------------------------------------------------------*/
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->update();
    }

    graphics.render();

    /*--------------------------------------------------------------------------------
        Post-render update entities.
    --------------------------------------------------------------------------------*/
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->post_render_update();
    }
}

void World::close()
{
    printf("[world] Closing.\n");
}


void World::keyboard_handler(KeyboardEvent e)
{
    for (auto b : entities.aspects<Behaviour>()) {
        if (b->enabled) b->keyboard_handler(e);
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
        const float wanted_aspect_ratio = 0.566;
        float width = e.framebuffer.width;
        float height = e.framebuffer.height;
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
        graphics.screen_buffer.resolution_x = w;
        graphics.screen_buffer.resolution_y = h;
        graphics.window_viewport = Viewport(x, y, w, h);
    }
}


DESCRIPTOR_INSTANCE(World);
BEGIN_ENTRIES(World)
    //...unfinished
END_ENTRIES()




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
