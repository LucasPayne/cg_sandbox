#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "resource_model/resource_model.h"
#include "entity_model/entity_model.h"
#include "rendering/rendering.h"

struct Transform : public IAspectType<Transform> {
    float position[3];
    float rotation[3];
    uint32_t flags;

    // mat4x4 model_matrix() const {
    //     //construct it
    // }
};

struct Camera : public IAspectType<Camera> {
    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    float projection_matrix[16];

    // mat4x4 vp_matrix() const {
    //     Transform *t = entity_model.get_aspect<Transform>(entity);
    //     return projection_matrix * t->model_matrix.inverse();
    // }
};

struct Drawable : public IAspectType<Drawable> {
    GeometricMaterialInstance geometric_material;
    MaterialInstance material;
};

#endif // STANDARD_ASPECTS_H
