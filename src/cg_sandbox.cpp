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
#include "mathematics/mathematics.h"
#include "rendering/rendering.h"
#include "standard_aspects/standard_aspects.h"
#include "assets/models.h"
#include <math.h>

//testing global
ShadingModelInstance *shading_model_model_testing;

void test_world(EntityModel &em, ResourceModel &rm)
{
    // Create a camera man.
    {
        Entity cameraman = em.new_entity();
        Camera *camera = em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = em.add_aspect<Transform>(cameraman);
        t->init(0,0,0);
    }

    // Create a dolphin.
    {
        Resource<GeometricMaterial> gmat = rm.load_from_file<GeometricMaterial>("resources/model_testing/model_testing.gmat");
        Resource<Material> mat = rm.load_from_file<Material>("resources/model_testing/model_testing.mat");
        Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/model_testing/model_testing.sm");
        shading_model_model_testing = new ShadingModelInstance(sm); // create a global shading model instance for testing.

        VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dolphins.off");
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(rm, dolphin_data);
        Entity dolphin = em.new_entity();
        Transform *t = em.add_aspect<Transform>(dolphin);
        t->init(0,0,1);
        Drawable *drawable = em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
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

    test_world(em, rm);
}
void CGSandbox::close()
{
}


void CGSandbox::loop()
{
    EntityModel &em = entity_model;
    ResourceModel &rm = resource_model;

    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

#if 0
    for (Camera *camera : em.aspects<Camera>()) {
        Transform *camera_transform = em.get_sibling<Transform>(camera);
        mat4x4 vp_matrix = camera_transform->inverse_model_matrix();
        vp_matrix.left_multiply(camera->projection_matrix);
        shading_model_model_testing.properties.set_mat4x4("vp_matrix", vp_matrix);

        for (Drawable *drawable : em.aspects<Drawable>()) {
            Transform *t = em.get_sibling<Transform>(drawable);
            mat4x4 model_matrix = t->model_matrix();
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);
            
            Draw draw(rm, drawable->geometric_material, drawable->material, shading_model_model_testing);
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
