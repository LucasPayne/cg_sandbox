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

    // When rendering into a camera (whether it attached to a framebuffer or a texture),
    // use these draw calls at the start and end.
    void begin_camera_rendering(Aspect<Camera> &camera);
    void end_camera_rendering(Aspect<Camera> &camera);

    // Draw a vertex array (in the geometric material) using a GeometricMaterial+Material+ShadingModel triple.
    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);

    // Clear to the default screen.
    void clear();
    // Render the Drawables into each camera.
    void render_drawables(); 


    // All raw OpenGL shader objects should be stored in this cache.
    //    note: Currently shading-system shaders are not, since they are generated.
    struct ShaderCache : public ResourceCache<GLShader> {
        ShaderCache(World &_world) : ResourceCache<GLShader>(_world) {};
        Resource<GLShader> compile(const std::string &path);
    };
    ShaderCache shaders;

    // "Shading" is the term for the model-shading system with geometric materials, materials, and shading models.
    ShadingAssets shading;
    // Immediate-mode drawing of vector graphics in 3D.
    Painting paint;

private:
    World &world;
};



#endif // GRAPHICS_H
