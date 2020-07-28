#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "mathematics/mathematics.h"
#include "resource_model/resource_model.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"

struct Transform : public IAspectType<Transform> {
    vec3 position;
    Quaternion rotation;

    void init(float x, float y, float z);
    void init(vec3 _position);
    void init(vec3 _position, Quaternion _rotation);
    void init_lookat(vec3 position, vec3 target);
    void lookat(vec3 target);

    mat4x4 matrix() const;
    mat4x4 inverse_matrix() const;
};

struct Camera : public IAspectType<Camera> {
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    mat4x4 projection_matrix;

    // Initialize this to a projective camera, with the default full viewport.
    void init_projective(float near_plane_distance, float far_plane_distance, float near_half_width, float aspect_ratio);
};

struct Drawable : public IAspectType<Drawable> {
    GeometricMaterialInstance geometric_material;
    MaterialInstance material;
};

// Specific Behaviours must be defined in a class which derives from IBehaviour.
struct World;
struct IBehaviour {
    World *world;
    Entity entity; // Each Behaviour attached to an entity is given a reference to the entity.
    bool updating;
    virtual void update() {
        // After one call, signify that this virtual function has not been overridden,
        // and that it is a no-op.
        updating = false;
    }
    bool handling_mouse;
    virtual void mouse_handler(MouseEvent e) {
        handling_mouse = false;
    }
    bool handling_keyboard;
    virtual void keyboard_handler(KeyboardEvent e) {
        handling_keyboard = false;
    }
};
struct Behaviour : public IAspectType<Behaviour> {
    size_t object_size;
    IBehaviour *object;
};

#endif // STANDARD_ASPECTS_H
