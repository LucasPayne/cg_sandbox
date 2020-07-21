#ifndef STANDARD_ASPECTS_H
#define STANDARD_ASPECTS_H
#include "core.h"
#include "entity_model/entity_model.h"

struct Transform : public IAspectType<Transform> {

    float position[3];
    float rotation[3];
    uint32_t flags;

    // mat4x4 model_matrix() const {
    //     //construct it
    // }
};

struct Camera : public IAspectType<Transform> {

    // Viewport extents (in terms of the application subrectangle).
    float bottom_left[2];
    float top_right[2];
    float projection_matrix[16];

    // mat4x4 vp_matrix() const {
    //     Transform *t = entity_model.get_aspect<Transform>(entity);
    //     return projection_matrix * t->model_matrix.inverse();
    // }
};

#endif // STANDARD_ASPECTS_H
