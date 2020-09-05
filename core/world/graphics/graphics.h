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
#include "world/standard_aspects/standard_aspects.h"


// Shading programs, compiled from a GeometricMaterial+Material+ShadingModel, are cached.
struct ShadingProgramKey {
    TableElementID gmat_id;
    TableElementID mat_id;
    TableElementID sm_id;
    ShadingProgramKey(const Resource<GeometricMaterial> &gmat, const Resource<Material> &mat, const Resource<ShadingModel> &sm) :
        gmat_id{gmat.ID()}, mat_id{mat.ID()}, sm_id{sm.ID()}
    {}
    bool operator==(const ShadingProgramKey &other) const {
        return (gmat_id == other.gmat_id) && (mat_id == other.mat_id) && (sm_id == other.sm_id);
    }
};
struct ShadingProgramHasher {
    size_t operator()(const ShadingProgramKey &key) const {
        //--todo: Choose a good hash function for u32,u32,u32 -> u64
        return 310921*key.gmat_id + 313101*key.mat_id + 233011*key.sm_id;
    }
};
typedef std::unordered_map<ShadingProgramKey, Resource<ShadingProgram>, ShadingProgramHasher> ShadingProgramCache;


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

    ShadingProgram *get_shading_program(Resource<GeometricMaterial> gmat, Resource<Material> mat, Resource<ShadingModel> sm);

    // When rendering into a camera (whether it attached to a framebuffer or a texture),
    // use these draw calls at the start and end.
    void begin_camera_rendering(Aspect<Camera> &camera);
    void end_camera_rendering(Aspect<Camera> &camera);

    void draw(GeometricMaterialInstance &gmat_instance,
              MaterialInstance &mat_instance,
              ShadingModelInstance &sm_instance);

    // Clear to the default screen.
    void clear();
    // Render the Drawables into each camera.
    void render_drawables();

    // Immediate-mode drawing of vector graphics in 3D.
    Painting paint;



private:
    World &world;
    ShadingProgramCache shading_program_cache;
};



#endif // GRAPHICS_H
