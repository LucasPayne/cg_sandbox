#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "interactive_graphics_context/input.h"
#include "mathematics/mathematics.h"

#include "world/world.h"


/*--------------------------------------------------------------------------------
Transform aspect
--------------------------------------------------------------------------------*/
struct Transform : public AspectBase {
    vec3 position;
    Quaternion rotation;
    float scale;

    void init(float x, float y, float z);
    void init(vec3 _position);
    void init(vec3 _position, Quaternion _rotation);
    void init_lookat(vec3 position, vec3 target);
    void lookat(vec3 target);

    mat4x4 matrix() const;
    mat4x4 inverse_matrix() const;
};


/*--------------------------------------------------------------------------------
Camera aspect
--------------------------------------------------------------------------------*/
struct Camera : public AspectBase {
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    mat4x4 projection_matrix;

    // Initialize this to a projective camera, with the default full viewport.
    void init_projective(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio);
};


/*--------------------------------------------------------------------------------
Drawable aspect
--------------------------------------------------------------------------------*/
struct Drawable : public AspectBase {
    GeometricMaterialInstance geometric_material;
    MaterialInstance material;
};


#endif // STANDARD_ASPECTS_H
