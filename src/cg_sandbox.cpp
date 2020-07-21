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
// #include "rendering/rendering.h"
#include "standard_aspects/standard_aspects.h"

struct Texture : public IResourceType<Texture> {
    static bool load(void *data, const std::istream &stream);
    static bool unload(void *data);

    int a;
};
bool Texture::load(void *data, const std::istream &stream)
{
}
bool Texture::unload(void *data)
{
}


void create_dude(EntityModel &em)
{
    Entity e = em.new_entity();
    Transform *t = em.add_aspect<Transform>(e);
    t->position[0] = 1;
    t->position[1] = 2;
    t->position[2] = 3;
    // Drawable *d = em.add_aspect<Drawable>(e);
    // d->geometric_material = load_asset<GeometricMaterial>("triangle_mesh");
    // d->material = load_asset<GeometricMaterial>("color");
    // d->material.properties.set("uniform_color", vec4(1,0,1,1));
    // d->vertex_array = load_asset<VertexArray>("models/dragon");
    // d->vertex_array = new_resource<VertexArray>();
}

void CGSandbox::init()
{
    // // parse_shading_file("resources/triangle_mesh.gmat");
    // GeometricMaterial gmat = parse_geometric_material_file("resources/triangle_mesh2.gmat");
    // // GeometricMaterial gmat = parse_geometric_material_file("resources/triangle_mesh.gmat");
    // //Material mat = parse_material_file("resources/color.mat");
    // Material mat = parse_material_file("resources/color2.mat");
    // ShadingModel sm = parse_shading_model_file("resources/color_shading.sm");
    // // ShadingProgram program = new_shading_program(gmat, mat, sm);
    // ShadingProgram program(gmat, mat, sm);

    // Initialize the resource model.
    resource_model = ResourceModel();
    ResourceModel &rm = resource_model;
    // Register resource types. Remember to do this!
    #define REGISTER_RESOURCE_TYPE(NAME) rm.register_resource_type<NAME>(#NAME, NAME ::load, NAME ::unload)
    REGISTER_RESOURCE_TYPE(Texture);
    // REGISTER_RESOURCE_TYPE(Material);
    // REGISTER_RESOURCE_TYPE(GeometricMaterial);
    // REGISTER_RESOURCE_TYPE(ShadingModel);

    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;
    // Register aspect types. Remember to do this!
    em.register_aspect_type<Transform>("Transform");
    em.register_aspect_type<Camera>("Camera");

    // Entity cameraman = em.new_entity();
    // Camera *camera = em.add_aspect<Camera>(cameraman);
    // camera->bottom_left[0] = 0;
    // camera->bottom_left[1] = 0;
    // camera->top_right[0] = 1;
    // camera->top_right[1] = 1;
    // Transform *camera_transform = em.add_aspect<Transform>(cameraman);
    // camera_transform->position[0] = 0;
    // camera_transform->position[1] = 0;
    // camera_transform->position[2] = 0;

    // for (int i = 0; i < 8; i++) create_dude(em);

    for (int i = 0; i < 1000000; i++) {
        Entity e = em.new_entity();
        if (frand() > 0.3) {
            em.add_aspect<Transform>(e);
            // if (frand() > 0.3) em.destroy_aspect<Transform>(e);
        }
        if (frand() > 0.6) em.add_aspect<Camera>(e);
        if (frand() > 0.5) em.destroy_entity(e);
    }


}
void CGSandbox::close()
{
}


void CGSandbox::loop()
{
    // test_shading_dataflow();
    // test_new_shading_program();
    // getchar();

    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");
    EntityModel &em = entity_model;

    int num = 0;
    for (Entity e : em.entities()) {
        num++;
    };
    printf("entities: %d\n", num);

    
#if 1
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
