#include "core.h"
#include "data_structures/table.h"
#include "entity_model/entity_model.h"


struct Transform : public AspectBase {
    static TableCollectionType type_id;

    float position[3];
    float rotation[3];
};
TableCollectionType Transform::type_id = -1;

struct Camera : public AspectBase {
    static TableCollectionType type_id;

    float projection_matrix[16];
};
TableCollectionType Camera::type_id = -1;


int main(void)
{
    EntityModel em;
    em.register_aspect_type<Transform>("Transform");
    em.register_aspect_type<Camera>("Camera");

    for (int i = 0; i < 15; i++) {
        Entity e = em.new_entity();
        if (frand() > 0.5) {
            Aspect<Transform> t = em.add_aspect<Transform>(e);
        }
        if (frand() > 0.3) {
            Aspect<Camera> c = em.add_aspect<Camera>(e);
            if (frand() > 0.5) {
                em.destroy_aspect<Camera>(c);
            }
        }
    }
}
