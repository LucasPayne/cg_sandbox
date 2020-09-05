#ifndef PAINTING_H
#define PAINTING_H
#include "core.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "mathematics/mathematics.h"
class Graphics;
class World;


struct PaintingSphere {
    vec3 position;
    float radius;
    vec4 color;
    PaintingSphere(vec3 _position, float _radius, vec4 _color) :
        position{_position},
        radius{_radius},
        color{_color}
    {}
};


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
    std::vector<PaintingSphere> spheres;

    Resource<GLShaderProgram> spheres_shader_program;

    Graphics &graphics;
    World &world;
};


#endif // PAINTING_H
