#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "interactive_graphics_context/input.h"
#include "mathematics/mathematics.h"

#include "world/world.h"


/*--------------------------------------------------------------------------------
Transform aspect
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct Transform : public AspectBase {
    /*ENTRY*/ vec3 position;
    /*ENTRY*/ Quaternion rotation;

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
/*REFLECTED*/ struct Camera : public AspectBase {
    // Viewport extents (in terms of the application subrectangle).
    /*ENTRY*/ float bottom_left[2];
    /*ENTRY*/ float top_right[2];
    /*ENTRY*/ mat4x4 projection_matrix;

    // Initialize this to a projective camera, with the default full viewport.
    void init_projective(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio);
};


/*--------------------------------------------------------------------------------
Drawable aspect
--------------------------------------------------------------------------------*/
/*REFLECTED*/ struct Drawable : public AspectBase {
    /*ENTRY*/ GeometricMaterialInstance geometric_material;
    /*ENTRY*/ MaterialInstance material;
};


#endif // STANDARD_ASPECTS_H
