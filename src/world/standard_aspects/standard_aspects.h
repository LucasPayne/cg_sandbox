#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "mathematics/mathematics.h"
#include "resource_model/resource_model.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"

struct Transform : public IAspectType<Transform> {
    vec3 position;
    vec3 rotation;

    void init(float x, float y, float z);
    void init(vec3 _position);
    void init(float x, float y, float z, float theta_x, float theta_y, float theta_z);
    void init(vec3 _position, vec3 _rotation);

    inline mat4x4 matrix() const {
        // note: mat4x4 constructor parameter order is column-major.
        return mat4x4(1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      position.x(),position.y(),position.z(),1);
    }
    inline mat4x4 inverse_matrix() const {
        return mat4x4(1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      -position.x(),-position.y(),-position.z(),1);
    }
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

// Specific Logic must be defined in a class which derives from ILogic, or a class which derives from ILogic.
struct ILogic {
    bool has_update;
    virtual void update() {
        // After one call, signify that this virtual function has not been overridden,
        // and that it is a no-op.
        has_update = false;
    }
};
struct Logic : public IAspectType<Logic> {
    size_t data_size;
    ILogic *data;
    template <typename L>
    L *init() {
        if (data != nullptr) {
            fprintf(stderr, "ERROR: Cannot reinitialize Logic aspect.\n");
            exit(EXIT_FAILURE);
        }
        data_size = sizeof(L);
        data = new L();
        data->has_update = true; // The default functions will set this to false after one call.
        return reinterpret_cast<L *>(data);
    }
};

#endif // STANDARD_ASPECTS_H
