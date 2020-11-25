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
Graphics
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


class World;
class Graphics {
public:
    Graphics(World &_world) :
        shaders(_world),
        shading{*this, _world},
        paint{*this, _world},
        world{_world}
    {}

    void init();


    void clear_cameras();
    // When rendering into a camera (whether it is attached to a framebuffer or a texture),
    // use these draw calls at the start and end.
    void begin_camera_rendering(Aspect<Camera> &camera, bool clear = false);
    void end_camera_rendering(Aspect<Camera> &camera);

    // Draw a vertex array (in the geometric material) using a GeometricMaterial+Material+ShadingModel triple.
    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);

    // Clear to the default screen.
    void clear(vec4 bg_color, vec4 fg_color);
    // Render the Drawables into each camera, using the given shading model.
    void render_drawables(std::string sm_name);


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

    // G-buffer
    void refresh_gbuffer_textures();
    GBufferComponent &gbuffer_component(std::string name);
    // G-buffer data
    GLuint gbuffer_fb; // G-buffer framebuffer
    GLuint depth_rbo; // Depth renderbuffer
    std::vector<GBufferComponent> gbuffer_components;

    // Deferred rendering using the G-buffer.
    void deferred_lighting();
    Resource<GLShaderProgram> directional_light_shader_program;

    // The postprocessing quad can be used at any time for postprocessing effects or deferred rendering.
    GLuint postprocessing_quad_vao;

    void set_viewport(int _viewport_x, int _viewport_y, int _viewport_width, int _viewport_height);
    void subviewport_begin(vec2 bottom_left, vec2 top_right);
    void subviewport_end();
private:
    World &world;

    GLint viewport_x;
    GLint viewport_y;
    GLsizei viewport_width;
    GLsizei viewport_height;
};



#endif // GRAPHICS_H
