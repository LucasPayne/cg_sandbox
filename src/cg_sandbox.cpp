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
ShadingModelInstance *shading_model_model_test;

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
    Resource<GeometricMaterial> gmat = rm.load_from_file<GeometricMaterial>("resources/model_test/model_test.gmat");
    Resource<Material> mat = rm.load_from_file<Material>("resources/model_test/model_test.mat");
    Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/model_test/model_test.sm");
    shading_model_model_test = new ShadingModelInstance(sm); // create a global shading model instance for testing.
    for (int i = 0; i < 100; i++) {
        VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/dolphins.off", true, 0.0003);
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/stanford_bunny_low.off");
        // VertexArrayData dolphin_data = Models::load_OFF_model("resources/models/icosahedron.off", true, -0.00025);
        Resource<VertexArray> dolphin_model = VertexArray::from_vertex_array_data(rm, dolphin_data);
        Entity dolphin = em.new_entity();
        Transform *t = em.add_aspect<Transform>(dolphin);
        t->init(-0.5 + frand(),-0.5 + frand(),-1);
        Drawable *drawable = em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }
#if 0
    VertexArrayData vad;
    vad.layout.num_vertices = 3;
    vad.layout.vertices_starting_index = 0;
    vad.layout.indexed = false;
    vad.attribute_buffers = std::vector<std::vector<uint8_t>>(2);
    vad.attribute_buffers[0] = std::vector<uint8_t>(3*sizeof(float)*3);
    vad.attribute_buffers[1] = std::vector<uint8_t>(3*sizeof(float)*3);
    float *positions = (float *) &(vad.attribute_buffers[0][0]);
    float *colors = (float *) &(vad.attribute_buffers[1][0]);
    float _positions[3*3] = {
        -0.5,-0.5,  0.5,
        0.5,-0.5,  0.5,
        0, 1.0/sqrt(2),  0.5
    };
    float _colors[3*3] = {
        1,0,0,
        0,1,0,
        0,0,1,
    };
    memcpy(positions, _positions, sizeof(_positions));
    memcpy(colors, _colors, sizeof(_colors));
    vad.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_position"));
    vad.layout.semantics.push_back(VertexSemantic(GL_FLOAT, 3, "v_color"));

    Resource<VertexArray> va = VertexArray::from_vertex_array_data(rm, vad);

        drawable->geometric_material = GeometricMaterialInstance(gmat, va);
#endif
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

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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

    for (Camera *camera : em.aspects<Camera>()) {
        Transform *camera_transform = em.get_sibling<Transform>(camera);
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        printf("vp_matrix\n");
        std::cout << vp_matrix << "\n";
        shading_model_model_test->properties.set_mat4x4("vp_matrix", vp_matrix);

        for (Drawable *drawable : em.aspects<Drawable>()) {
            Transform *t = em.get_sibling<Transform>(drawable);
            mat4x4 model_matrix = t->matrix();
            printf("model_matrix\n");
            std::cout << model_matrix << "\n";
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);
            
            Draw draw(rm, drawable->geometric_material, drawable->material, *shading_model_model_test);
            draw.draw();
        }
    }
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
