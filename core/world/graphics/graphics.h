#ifndef GRAPHICS_H
#define GRAPHICS_H
/*--------------------------------------------------------------------------------
The Graphics component of the world holds graphics state, such as compiled shaders,
and is the interface through which things are drawn.

The Graphics component also holds render loops.
--------------------------------------------------------------------------------*/
#include "core.h"

#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "world/graphics/painting/painting.h"
#include "world/graphics/shading_assets.h"
#include "world/standard_aspects/standard_aspects.h"

#include "world/resource_cache.h"



// Reflect opengl_utilities classes.
REFLECT_STRUCT(GLShader);
REFLECT_STRUCT(GLShaderProgram);


/*--------------------------------------------------------------------------------
    G-buffer
--------------------------------------------------------------------------------*/
struct GBufferComponent {
    std::string name;
    GLenum internal_format;
    GLenum external_format;
    GLenum type;
    GLuint texture; // The texture is initialized later.
    GBufferComponent(std::string _name, 
                     GLenum _internal_format,
                     GLenum _external_format,
                     GLenum _type)
        : name{_name}, internal_format{_internal_format}, external_format{_external_format}, type{_type}
    {}
    GBufferComponent() {}
};


/*--------------------------------------------------------------------------------
Lighting data
--------------------------------------------------------------------------------*/
struct DirectionalLightShadowMap {
    Aspect<Camera> camera;
    GLuint fbo;
    GLuint texture;
    GLuint sampler_comparison;
    GLuint sampler_raw; // this sampler object gives regular lookup with nearest-neighbour filtering.
    int width;
    int height; // resolution
    int num_frustum_segments;
    float distance; // Shadows are computed up to this distance, or the far plane distance if that is closer.

    // The shadow matrices transform points in world space into shadow coordinates (X and Y as texture coordinates, Z as the depth in the range
    // of the shadow map).
    std::vector<mat4x4> shadow_matrices;
    std::vector<vec3> box_extents;
    std::vector<float> frustum_segment_dividers;
};
struct DirectionalLightData {
    // Each light maintains shadow maps for each camera. This map is indexed by the camera's unique ID.
    std::map<uint64_t, DirectionalLightShadowMap> shadow_maps;
    // Retrieve this light's shadow map for a certain camera. If there isn't one, initialize it.
    DirectionalLightShadowMap &shadow_map(Aspect<Camera> camera);
};


/*--------------------------------------------------------------------------------
Graphics
--------------------------------------------------------------------------------*/
class World;
class Graphics {
public:
    Graphics(World &_world) :
        shaders(_world),
        shading{*this, _world},
        paint{*this, _world},
        post_flag{0},
        world{_world}
    {}

    void init();

    void render();
    void render(Aspect<Camera> camera);
    // Draw a vertex array (in the geometric material) using a GeometricMaterial+Material+ShadingModel triple.
    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);
    void render_drawables(ShadingModelInstance shading_model);
    // Lighting
    void update_lights();
    void lighting(Aspect<Camera> camera);
    void directional_lights(Aspect<Camera> camera);
    Resource<GLShaderProgram> directional_light_shader_program;
    Resource<GLShaderProgram> directional_light_filter_shader_program;
    // Post-processing
    void depth_of_field(Aspect<Camera> camera);
    Resource<GLShaderProgram> depth_of_field_confusion_radius_program;
    Resource<GLShaderProgram> depth_of_field_near_field_program;
    // Temporal anti-aliasing
    void temporal_antialiasing(Aspect<Camera> camera);
    Resource<GLShaderProgram> temporal_aa_program;


    // All raw OpenGL shader objects should be stored in this cache.
    //    note: Currently shading-system shaders are not, since they are generated.
    struct ShaderCache : public ResourceCache<GLShader> {
        ShaderCache(World &_world) : ResourceCache<GLShader>(_world) {};
        Resource<GLShader> compile(const std::string &path);
    };
    ShaderCache shaders;

    // "Shading" is the term for the surface-shading system with geometric materials, materials, and shading models.
    ShadingAssets shading;
    // The painting module is for immediate-mode drawing of vector graphics in 2D and 3D.
    Painting paint;

    void refresh_framebuffers();
    Viewport window_viewport; // The final screen buffer rendering is rendered onto the window framebuffer with this viewport.
                              // This can be set by the application, to, for example, fix the rendering to a fixed-aspect-ratio rectangle.
    Framebuffer screen_buffer;
    int framebuffer_res_x;
    int framebuffer_res_y; // minimum framebuffer size needed to account for all cameras being rendered to.
    // G-buffer
    GBufferComponent &gbuffer_component(std::string name);
    // G-buffer data
    GLuint gbuffer_fb; // G-buffer framebuffer
    GLuint gbuffer_depth_rbo; // Depth renderbuffer
    std::vector<GBufferComponent> gbuffer_components;

    //////////////////////////////////////////////////////////////////////////////////
    // dummy functions until painting module is updated
    inline void begin_camera_rendering(Aspect<Camera> &camera, bool clear = false) {};
    inline void end_camera_rendering(Aspect<Camera> &camera) {};


    // The postprocessing quad can be used at any time for postprocessing effects or deferred rendering.
    GLuint postprocessing_quad_vao;
    void begin_post(Resource<GLShaderProgram> &program,
                     Viewport read_viewport,
                     Viewport target_viewport);
    void begin_post(Resource<GLShaderProgram> &program);
    Viewport read_post();
    Viewport write_post();
    void set_post(Viewport &viewport);
    void swap_post();
    int post_flag;
    Framebuffer post_buffer;
    Viewport second_post_viewport;

    // Lighting graphics data. This is maintained for each light in the scene, and cleaned up when a light is removed from the scene.
    DirectionalLightData &directional_light_data(Aspect<DirectionalLight> light);
private:
    World &world;

    std::map<uint64_t, DirectionalLightData> directional_light_data_map;
};

#endif // GRAPHICS_H
