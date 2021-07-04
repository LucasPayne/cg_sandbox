#ifndef WORLD_GRAPHICS_H
#define WORLD_GRAPHICS_H
#include "opengl_utilities/gl.h"
#include "reflector/reflector.h"
#include "world/entity_system/entity_system.h"

#include "world/graphics/painting/painting.h"

REFLECT_STRUCT(GLShader);
REFLECT_STRUCT(GLShaderProgram);


/*--------------------------------------------------------------------------------
Graphics
--------------------------------------------------------------------------------*/
class World;
class Graphics {
public:
    Graphics(World &_world) :
        paint{*this, _world},
        world{_world}
    {}

    void init();

    void render();
    void render(Aspect<Camera> camera);

    // The painting module is for immediate-mode drawing of vector graphics in 2D and 3D.
    Painting paint;

    void refresh_framebuffers();

    Viewport window_viewport; // The final screen buffer is placed onto the window framebuffer with this viewport.
                              // This can be set by the application, to, for example, fix the rendering to a fixed-aspect-ratio rectangle.
    Viewport prev_window_viewport; // Changes to the window dimensions are detected so that the screen framebuffer can be resized.
    vec4 background_color; // When there is empty space in the screen buffer, it will be this color.
    vec4 window_background_color; // Unused window framebuffer space is this color, e.g. the space not in the fixed aspect-ratio subrectangle.
    int window_width;
    int window_height;

    //////////////////////////////////////////////////////////////////////////////////
    // dummy functions until painting module is updated
    inline void begin_camera_rendering(Aspect<Camera> &camera, bool clear = false) {};
    inline void end_camera_rendering(Aspect<Camera> &camera) {};

    Framebuffer screen_buffer;
    int framebuffer_res_x;
    int framebuffer_res_y; // minimum framebuffer size needed to account for all cameras being rendered to.

    void compile_shaders();
private:
    // Shaders
    GLuint postprocessing_quad_vao;
    Resource<GLShaderProgram> tone_map_gamma_correction_program;

    World &world;
};

#endif // WORLD_GRAPHICS_H
