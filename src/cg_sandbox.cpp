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

#define TESTING_SM 0


define_aspect(Transform)
    float position[3];
    float orientation[3];
    uint32_t flags;
end_define_aspect(Transform)

define_aspect(Camera)
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    float projection_matrix[16];
end_define_aspect(Camera)

define_aspect(Drawable)
    // GeometryInstance geometry_instance;
    // MaterialInstance material_instance;
end_define_aspect(Drawable)

void create_dude(EntityModel &em)
{
    Entity e = em.new_entity();
    Transform *t = em.add_aspect<Transform>(e);
    t->position[0] = 1;
    t->position[1] = 2;
    t->position[2] = 3;
    Drawable *d = em.add_aspect<Drawable>(e);
}

void CGSandbox::init()
{
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

#if TESTING_SM == 1
struct Geometry {
    GLenum primitive;
};
struct PropertySheet {
    //...
};
struct VAO {
    GLuint vao_id;
    bool indexed;
    uint32_t num_vertices;
    uint32_t vertex_starting_index;
    GLenum indices_type; // GL_UNSIGNED{BYTE,SHORT,INT}
    uint32_t num_indices;
    uint32_t indices_starting_index;
};
struct GeometryInstance {
    Geometry &geometry; //instance of this
    VAO vao;
    PropertySheet properties;
};
struct Material {

};
struct MaterialInstance {

};
struct ShadingModel {

};
struct ShadingModelInstance {

};

#include <unordered_map>
// https://en.cppreference.com/w/cpp/container/unordered_map
struct GMSMHash {
    uint32_t g;
    uint32_t m;
    uint32_t sm;
    GMSMHash(uint32_t _g, uint32_t _m, uint32_t _sm) : g{_g}, m{_m}, sm{_sm} {}
};
class ShadingProgram {
    // Other than construction and caching, this class just holds data. All usage interface goes through
    // the Draw class, which could be thought of as a ShadingProgram "instance".
public:
    ShadingProgram(Geometry g, Material m, ShadingModel sm) {
        GMSMHash hash(g.id, m.id, sm.id);
        for (auto &found : cache.find(hash)) {
            *this = found;
            return;
        }
        // Not cached.
        cache[hash] = new_shading_program(g, m, sm);
        *this = cache[hash];
    }
private:
    ShadingProgram new_shading_program(Geometry g, Material m, ShadingModel sm) {
        // Construct a new shading program. This is where all of the code generation starts.
        //...
    }
    //-Global cache. Maybe should not be global.
    static std::unordered_map<GMSMHash, ShadingProgram> cache;

    // OpenGL-related data
    GLuint program_id;
    //... State interface information.
    //... Vertex attribute bindings stuff.
    //... Rendertarget bindings stuff.
};
std::vector<ShadingProgram> ShadingProgram::cache(0);

class Draw {
public:
    Draw(GeometryInstance &gi, MaterialInstance &mi, ShadingModelInstance &smi) {
        g_instance = gi;
        m_instance = mi;
        sm_instance = smi;

        shading_program = ShadingProgram(g_instance.geometry, m_instance.material, sm_instance.shading_model);
    };
    void bind() {
        glUseProgram(shading_program.program_id);
        glBindVertexArray(g_instance.vao.id); //-Make sure this binds the element buffer as well.
    }
    void upload_properties() {
        //...
        // Instances could have dirty flags.
        // UBOs, samplers with glUniform1i, 
    }
    void draw() {
        if (g_instance.indexed) {
            glDrawElements(g_instance.geometry.primitive, //mode
                           g_instance.vao.num_indices, // count
                           g_instance.vao.indices_type, // type (GL_UNSIGNED_{BYTE,SHORT,INT})
                           (const void *) g_instance.vao.indices_starting_index);
        } else {
            glDrawArrays(g_instance.geometry.primitive, //mode
                         g_instance.vao.vertex_starting_index //first
                         g_instance.vao.num_vertices); // count
        }
    }
private:
    GeometryInstance g_instance;
    MaterialInstance m_instance;
    ShadingModelInstance sm_instance;

    ShadingProgram shading_program;
};
#endif // TESTING_SM == 1

void CGSandbox::loop()
{
    printf("================================================================================\n");
    printf("Frame start\n");
    printf("================================================================================\n");
    EntityModel &em = entity_model;

    for (auto [camera, camera_transform] : em.aspects<Camera, Transform>()) {
        printf("Camera\n");
        printf("bottom left: %.2f %.2f\n", camera.bottom_left[0], camera.bottom_left[1]);
        printf("top right: %.2f %.2f\n", camera.top_right[0], camera.top_right[1]);

#if TESTING_SM == 1
        ShadingModelInstance sm_instance = new_sm_instance("color_shading");
        sm_instance.set_property("vp_matrix", camera.vp_matrix);

        // Render with this camera.
        for (auto [drawable, transform] : em.aspects<Drawable, Transform>()) {
            printf("Drawable\n");

            // Constructor looks up precompiled shading program in cache, if its not there, it is created and cached.
            //-renamed Draw, rather than ShadingProgram, since that will be the instance-independent thing.
            Draw draw(drawable.geometry_instance,
                      drawable.material_instance,
                      sm_instance);
            // Binding the draw prepares the GPU pipeline for rendering with the G+M+SM.
            draw.bind();

            // Synchronize pipeline state with the properties.
            draw.upload_properties();

            // Draw. The Draw encapsulates one drawable geometry vertex array (in whatever format), pipelined through
            // the ShadingProgram associated to the Geometry, Material, and ShadingModel.
            draw.draw();
        }
#endif
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
