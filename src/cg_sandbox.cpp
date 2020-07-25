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
#include <math.h>

struct Texture : public IResourceType<Texture> {
    static bool load(void *data, std::istream &stream);
    static bool unload(void *data);

    int a;
};
bool Texture::load(void *data, std::istream &stream)
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

//testing global
Draw draw;

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
    REGISTER_RESOURCE_TYPE(Material);
    REGISTER_RESOURCE_TYPE(GeometricMaterial);
    REGISTER_RESOURCE_TYPE(ShadingModel);
    REGISTER_RESOURCE_TYPE(ShadingProgram);
    REGISTER_RESOURCE_TYPE(VertexArray);
    // #define PRINT_ID(NAME) printf(#NAME ": %u\n", NAME ::type_id);
    // PRINT_ID(Texture);
    // PRINT_ID(Material);
    // PRINT_ID(GeometricMaterial);
    // PRINT_ID(ShadingModel);
    // PRINT_ID(ShadingProgram);

    // Resource<GeometricMaterial> gmat = rm.load_from_file<GeometricMaterial>("resources/triangle_mesh2.gmat");
    // Resource<Material> mat = rm.load_from_file<Material>("resources/color.mat");
    // Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/color_shading.sm");
    Resource<GeometricMaterial> gmat = rm.load_from_file<GeometricMaterial>("resources/simple_shading/simple.gmat");
    Resource<Material> mat = rm.load_from_file<Material>("resources/simple_shading/simple.mat");
    Resource<ShadingModel> sm = rm.load_from_file<ShadingModel>("resources/simple_shading/simple.sm");

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

    GeometricMaterialInstance *gi = new GeometricMaterialInstance(gmat, va);
    gi->properties.set_float("color_multiplier", 3);
    MaterialInstance *mi = new MaterialInstance(mat);
    ShadingModelInstance *smi = new ShadingModelInstance(sm);
    // Resource<ShadingProgram> program = ShadingProgram::create(rm, gmat, mat, sm);
    draw = Draw(rm, *gi, *mi, *smi);

    // Initialize the entity model, with no entities.
    entity_model = EntityModel(); 
    EntityModel &em = entity_model;
    // Register aspect types. Remember to do this!
    #define REGISTER_ASPECT_TYPE(NAME) em.register_aspect_type<NAME>(#NAME)
    REGISTER_ASPECT_TYPE(Transform);
    REGISTER_ASPECT_TYPE(Camera);
    REGISTER_ASPECT_TYPE(Drawable);

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

    /*
    for (int i = 0; i < 1000000; i++) {
        Entity e = em.new_entity();
        if (frand() > 0.3) {
            em.add_aspect<Transform>(e);
            // if (frand() > 0.3) em.destroy_aspect<Transform>(e);
        }
        if (frand() > 0.6) em.add_aspect<Camera>(e);
        if (frand() > 0.5) em.destroy_entity(e);
    }
    */

    #if 0
    for (int i = 0; i < 10; i++) {
        Entity e = em.new_entity();
        Transform *t = em.add_aspect<Transform>(e);
        t->position[0] = 3*frand();
        t->position[1] = 3*frand();
        t->position[2] = 3*frand();
        Drawable *d = em.add_aspect<Drawable>(e);
        d->geometric_material = gmat->new_instance();
        d->material = mat->new_instance();
        d->material.properties.set("vec4 uniform_color", vec4(0,1,1,1));
    }
    #endif
}
void CGSandbox::close()
{
}


void CGSandbox::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");

    // int num_drawable = 0;
    // for (Drawable *drawable : em.aspects<Drawable>()) {
    //     Transform *t = em.try_get_sibling<Transform>(drawable);
    //     if (t == nullptr) continue;
    //     num_drawable++;
    //     
    // }
    // printf("num Drawable with Transform: %d\n", num_drawable);

    draw.draw();

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
