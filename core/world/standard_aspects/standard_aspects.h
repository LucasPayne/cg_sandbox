#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "interactive_graphics_context/input.h"
#include "mathematics/mathematics.h"

#include "world/world.h"



/*--------------------------------------------------------------------------------
Transform aspect
--------------------------------------------------------------------------------*/
struct Transform : public IAspectType {
    vec3 position;
    Quaternion rotation;
    float scale;

    Transform() :
        position{vec3::zero()}, rotation{Quaternion::identity()}, scale{1.f}
    {}

    void init(float x, float y, float z);
    void init(vec3 _position);
    void init(vec3 _position, Quaternion _rotation);
    void init_lookat(vec3 position, vec3 target);
    void lookat(vec3 target);

    mat4x4 matrix() const;
    mat4x4 inverse_matrix() const;
};
REFLECT_STRUCT(Transform);


/*--------------------------------------------------------------------------------
Camera aspect
--------------------------------------------------------------------------------*/
struct Camera : public IAspectType {
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    mat4x4 projection_matrix;

    // Initialize this to a projective camera, with the default full viewport.
    Camera(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio);
    Camera() {}
};
REFLECT_STRUCT(Camera);


/*--------------------------------------------------------------------------------
Drawable aspect
--------------------------------------------------------------------------------*/
struct Drawable : public IAspectType {
    GeometricMaterialInstance geometric_material;
    MaterialInstance material;

    Drawable(const GeometricMaterialInstance &gmi, const MaterialInstance &mi) :
        geometric_material{gmi}, material{mi}
    {}
    Drawable() {}
};
REFLECT_STRUCT(Drawable);



#endif // STANDARD_ASPECTS_H
