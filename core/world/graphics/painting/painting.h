#ifndef PAINTING_H
#define PAINTING_H
#include "core.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "mathematics/mathematics.h"


// struct PaintingSphere {
//     vec3 position;
//     float radius;
//     vec4 color;
//     PaintingSphere(vec3 _position, float _radius, vec4 _color) :
//         position{_position}, radius{_radius}, color{_color}
//     {}
// };


class Graphics;
class World;
class Painting {
public:
    Painting(Graphics &_graphics, World &_world) :
        graphics{_graphics}, world{_world}
    {}

    void init();

    void render();
    void clear();
    void sphere(vec3 position, float radius, vec4 color);

private:
    // std::vector<PaintingSphere> spheres;
    std::vector<vec3> sphere_positions;
    std::vector<float> sphere_radii;
    std::vector<vec4> sphere_colors;

    Resource<GeometricMaterial> spheres_gmat;
    Resource<Material> spheres_mat;
    Resource<ShadingModel> spheres_sm;

    Graphics &graphics;
    World &world;
};


#endif // PAINTING_H
