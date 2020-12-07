#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "interactive_graphics_context/input.h"
#include "mathematics/mathematics.h"
#include "world/entities/entities.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
class World;


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

    Transform(float x, float y, float z);
    Transform(vec3 _position);
    Transform(vec3 _position, Quaternion _rotation);
    vec3 forward();
    vec3 up();
    vec3 right();
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

    // Currently, cameras are all projective, and these parameters make sense.
    float near_plane_distance;
    float far_plane_distance;
    float near_half_width;
    float m_aspect_ratio; // Aspect ratio here is height over width.

    bool rendering_to_screen; // If rendering to the screen, the framebuffer will automatically be updated to be the screen framebuffer.
    // Viewport extents. (0,0) is the bottom-left of the framebuffer.
    vec2 bottom_left;
    vec2 top_right;
    Framebuffer framebuffer;
    inline Viewport viewport() {
        int x, y, w, h;
        x = floor(framebuffer.resolution_x * bottom_left.x());
        y = floor(framebuffer.resolution_y * bottom_left.y());
        w = ceil(framebuffer.resolution_x *  top_right.x()) - x;
        h = ceil(framebuffer.resolution_y *  top_right.y()) - y;
        return Viewport(framebuffer, x, y, w, h);
    }

    vec2 depth_of_field; // The range where the captured image is considered to be in-focus (depth x to y from the camera).

    // Temporal anti-aliasing data.
    Framebuffer taa_buffer;
    bool has_taa_buffer;

    vec4 background_color;

        // If cameras rendering to the screen have different layers, then the one with the lowest layer has priority for,
        // e.g., ray picking.
    int layer;
        // When the camera is rendering to the screen, this returns whether or not the given screen position is in the camera's rectangle.
    bool in_viewport(float screen_x, float screen_y);
        // Transform screen coordinates to the coordinates of the camera's subrectangle (a rectangular affine transformation).
    void to_viewport(float screen_x, float screen_y, float *camera_x, float *camera_y);

    float aspect_ratio() const;

    // Create a ray with origin at the position at this camera that points toward the point on the near plane in camera-screen coordinates.
    Ray ray(float camera_x, float camera_y);

    // Transform from "frustum coordinates" to world space.
    // In frustum coordinates, x and y are (-1,-1) at the bottom left point on the rectangle at depth z through the frustum.
    // z is 0 at the near plane, 1 at the far plane.
    // This is useful, for example, to compute the points on a section of the frustum, for cascaded shadow mapping.
    vec3 frustum_point(float x, float y, float z);

    mat4x4 view_matrix();
    mat4x4 view_projection_matrix();

    bool has_prev_view_projection_matrix;
    mat4x4 prev_view_projection_matrix;

    // Initialize this to a projective camera rendering to the full screen.
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
       
    
    vec3 center; // The drawable can be recentered. This just changes the effective position of vertices generated by the geometric_material.
    mat4x4 model_matrix(); // Renderers must use this, since it takes into account the drawable's center.
    mat4x4 normal_matrix(); // For transforming normals into world-space when shading.
    Sphere bounding_sphere();

    // Store the previous model matrix, e.g. for rendering the velocity buffer.
    mat4x4 prev_model_matrix;
    bool has_prev_model_matrix;

    Drawable(const GeometricMaterialInstance &gmi, const MaterialInstance &mi) :
        geometric_material{gmi}, material{mi}, center{vec3::zero()}, shadow_caster{true}
    {
    }
    Drawable() {}

    bool shadow_caster;

    Sphere raw_bounding_sphere; // This bounding sphere is for the untransformed geometric data.
                                // It does not take into account the world-space transform and recentering.
};
REFLECT_STRUCT(Drawable);


/*--------------------------------------------------------------------------------
Behaviour aspect
--------------------------------------------------------------------------------*/
struct Behaviour;
// Specific Behaviours must be defined in a class which derives from IBehaviour.
struct IBehaviour {
public:
    World *world;
    Entity entity;
        // Each Behaviour attached to an entity is given a reference to the entity.

private:
    virtual void update() {
        //no-op
    }
    virtual void post_render_update() {
        //no-op
    }
    virtual void mouse_handler(MouseEvent e) {
        //no-op
    }
    virtual void keyboard_handler(KeyboardEvent e) {
        //no-op
    }
    // Behaviour routes calls to the IBehaviour's virtual functions, so needs access to private methods.
    friend class Behaviour;
};
REFLECT_STRUCT(IBehaviour);

struct Behaviour : public IAspectType {
    // note: Reflection removed for now.
    // IBehaviour *object() {
    //     return data.as<IBehaviour>();
    // }
    // // Interpet as known IBehaviour-deriving type.
    // template <typename T>
    // T *object_as() {
    //     return reinterpret_cast<T *>(data.as<IBehaviour>());
    // }

    template <typename T>
    T *object_as() {
        return reinterpret_cast<T *>(data);
    }
    IBehaviour *object() {
        return data;
    }

    // GenericOwned data;
    IBehaviour *data;
    bool enabled;

    void update();
    void post_render_update();
    void mouse_handler(MouseEvent e);
    void keyboard_handler(KeyboardEvent e);
    
};
REFLECT_STRUCT(Behaviour);

/*--------------------------------------------------------------------------------
DirectionalLight aspect
--------------------------------------------------------------------------------*/
struct DirectionalLight : public IAspectType {
    vec3 direction;
    vec3 color;
    float width; // Influences soft shadows.

    DirectionalLight() {}
    DirectionalLight(vec3 _direction, vec3 _color, float _width) :
        direction{_direction}, color{_color}, width{_width}
    {}
};
REFLECT_STRUCT(DirectionalLight);


/*--------------------------------------------------------------------------------
PointLight aspect
--------------------------------------------------------------------------------*/
struct PointLight : public IAspectType {
    vec3 color;
    float radius; // Soft-shadowing approximates this light as a sphere with this radius.

    PointLight() {}
    PointLight(vec3 _color, float _radius) :
        color{_color}, radius{_radius}
    {}
};
REFLECT_STRUCT(PointLight);



#endif // STANDARD_ASPECTS_H
