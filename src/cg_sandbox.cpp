/*--------------------------------------------------------------------------------
    This is the main entry point for "engine" behaviour, through a single
    loop and event callbacks.

BUGS:
PROBLEMS:
IDEAS/THINGS:
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "cg_sandbox.h"
#include "rendering/rendering.h"
#include "standard_aspects/standard_aspects.h"
#include "assets/models.h"
#include <math.h>

void test_world(EntityModel &em, ResourceModel &rm)
{
    // Create a camera man.
    Entity cameraman = em.new_entity();
    Camera *camera = em.add_aspect<Camera>(cameraman);
    camera->bottom_left[0] = 0;
    camera->bottom_left[1] = 0;
    camera->top_right[0] = 1;
    camera->top_right[1] = 1;
    Transform *camera_transform = em.add_aspect<Transform>(cameraman);
    camera_transform->position[0] = 0;
    camera_transform->position[1] = 0;
    camera_transform->position[2] = 0;

    // Create a dolphin.
    {
        VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dolphins.off");
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(rm, dolphin_data);
        Entity dolphin = em.new_entity();
        Transform *t = em.add_aspect<Transform>(dolphin);
        Drawable *drawable = em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material->properties.set_float(
    }
}

void CGSandbox::init()
{
    // Initialize the resource model.
    resource_model = ResourceModel();
    ResourceModel &rm = resource_model;
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) rm.register_resource_type<NAME>(#NAME, NAME ::load, NAME ::unload)
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);

    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) em.register_aspect_type<NAME>(#NAME)
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);

    // Resource<GeometricMaterial> gmat = rm.load_from_file<GeometricMaterial>("resources/simple_shading/simple.gmat");
    // Resource<Material> mat = rm.load_from_file<Material>("resources/simple_shading/simple.mat");
    // Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/simple_shading/simple.sm");


    test_world(em, rm);
}
void CGSandbox::close()
{
}


void CGSandbox::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

    static int frame_number = 0;
    frame_number ++;
    gi->properties.set_float("color_multiplier", 1+0.5*sin(total_time));
    gi->properties.set_vec3("add_to_color", 0.3*((frame_number / 8) % 2), 0, 0.3*((frame_number / 8) % 2));

    // int num_drawable = 0;
    // for (Drawable *drawable : em.aspects<Drawable>()) {
    //     Transform *t = em.try_get_sibling<Transform>(drawable);
    //     if (t == nullptr) continue;
    //     num_drawable++;
    //     
    // }
    // printf("num Drawable with Transform: %d\n", num_drawable);

    draw.draw();


    int num_drawable = 0;
    for (Drawable *drawable : em.aspects<Drawable>()) {
        Transform *t = em.try_get_sibling<Transform>(drawable);
        if (t == nullptr) continue;
        num_drawable++;
        
    }
    printf("num Drawable with Transform: %d\n", num_drawable);



#if 0
    EntityModel &em = entity_model;

    int num = 0;
    for (Entity e : em.entities()) {
        num++;
    };
    printf("entities: %d\n", num);

    
    int num_transforms = 0;
    for (Transform *t : em.aspects<Transform>()) {
        num_transforms++;
    }
    printf("transforms: %d\n", num_transforms);

    int num_cameras = 0;
    int num_cameras_with_transforms = 0;
    for (Camera *c : em.aspects<Camera>()) {
        num_cameras++;
        if (em.try_get_sibling<Transform>(c) != nullptr) num_cameras_with_transforms++;
    }
    printf("cameras: %d\n", num_cameras);
    printf("cameras with transforms: %d\n", num_cameras_with_transforms);
#endif


#if 0
    ShadingModelInstance shading_model("color_shading");
    for (auto [camera, camera_transform] : em.aspects<Camera, Transform>()) {
        printf("Camera\n");
        printf("bottom left: %.2f %.2f\n", camera.bottom_left[0], camera.bottom_left[1]);
        printf("top right: %.2f %.2f\n", camera.top_right[0], camera.top_right[1]);

        shading_model.properties.set("vp_matrix", camera.vp_matrix());

        // Render with this camera.
        for (auto [drawable, transform] : em.aspects<Drawable, Transform>()) {
            printf("Drawable\n");

            drawable.geometric_material.properties.set("model_matrix", transform.model_matrix());

            Draw draw(drawable.geometric_material,
                      drawable.material,
                      shading_model);
            // Binding the draw prepares the GPU pipeline for rendering with the G+M+SM.
            draw.bind();

            // Synchronize pipeline state with the properties.
            draw.upload_properties();

            // Draw. The Draw encapsulates one drawable geometry vertex array (in whatever format), pipelined through
            // the ShadingProgram associated to the Geometry, Material, and ShadingModel.
            draw.draw();
        }
    }
#endif
}

void CGSandbox::key_callback(int key, int action)
{
    EntityModel &em = entity_model;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q && g_context_active) {
            g_opengl_context->close();
            exit(EXIT_SUCCESS);
        }

        if (key == GLFW_KEY_K) {
            // for (auto &t : em.aspects<Transform>()) {
            //     t.position[1] += 2.3;
            // }
        }
        if (key == GLFW_KEY_C) {
            create_dude(em);
        }
        if (key == GLFW_KEY_M) {
            // for (auto &t : em.aspects<Transform>()) {
            //     // if (frand() > 0.8) em.destroy_entity(t.entity);
            //     em.destroy_entity(t.entity);
            //     break;
            // }
        }
        // This is broken!
        // if (key == GLFW_KEY_V) {
        //     for (auto &v : em.aspects<Velocity>()) {
        //         em.destroy_aspect(&v);
        //         break;
        //     }
        // }
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
