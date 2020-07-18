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
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"


define_aspect(Transform)
    float position[3];
    float orientation[3];
    uint32_t flags;

    // mat4x4 model_matrix() const {
    //     //construct it
    // }
end_define_aspect(Transform)

define_aspect(Camera)
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    float projection_matrix[16];

    // mat4x4 vp_matrix() const {
    //     Transform *t = entity_model.get_aspect<Transform>(entity);
    //     return projection_matrix * t->model_matrix.inverse();
    // }

end_define_aspect(Camera)

template <typename TYPE>
struct Resource {
    uint8_t type;
    uint32_t index;
    uint32_t id;
    // readonly
    const TYPE *operator*() {
        //...
    }
    Resource fork() const {
        // Duplicate the resource. If the resource data has dependencies, this is handled.
        // For example, if a resource is backed by an asset, the new resource is not, it duplicates
        // all data (requiring a deep copy).
    }
};

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
    // parse_shading_file("resources/triangle_mesh.gmat");
    GeometricMaterial gmat = parse_geometric_material_file("resources/triangle_mesh2.gmat");
    // GeometricMaterial gmat = parse_geometric_material_file("resources/triangle_mesh.gmat");
    //Material mat = parse_material_file("resources/color.mat");
    Material mat = parse_material_file("resources/color2.mat");
    ShadingModel sm = parse_shading_model_file("resources/color_shading.sm");
    // ShadingProgram program = new_shading_program(gmat, mat, sm);
    ShadingProgram program(gmat, mat, sm);

    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;

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

    for (int i = 0; i < 8; i++) create_dude(em);

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
            for (auto &t : em.aspects<Transform>()) {
                t.position[1] += 2.3;
            }
        }
        if (key == GLFW_KEY_C) {
            create_dude(em);
        }
        if (key == GLFW_KEY_M) {
            for (auto &t : em.aspects<Transform>()) {
                // if (frand() > 0.8) em.destroy_entity(t.entity);
                em.destroy_entity(t.entity);
                break;
            }
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
