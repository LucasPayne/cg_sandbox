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
    mat4x4 projection_matrix;

    bool rendering_to_framebuffer; //note: Currently this is always true, but later cameras could be able to render to textures.

    vec4 background_color;

    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
        // If cameras rendering to the framebuffer have different layers, then the one with the lowest layer has priority for,
        // e.g., ray picking.
    int layer;
        // When the camera is rendering to a framebuffer, this returns whether or not the given screen position is in the camera's rectangle.
    bool in_viewport(float screen_x, float screen_y);
        // Transform screen coordinates to the coordinates of the camera's viewport (a rectangular affine transformation).
    void to_viewport(float screen_x, float screen_y, float *camera_x, float *camera_y);


    // Create a ray that points toward 
    Ray ray(float camera_x, float camera_y);


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
