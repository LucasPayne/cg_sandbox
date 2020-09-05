#ifndef PAINTING_H
#define PAINTING_H
#include "core.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "mathematics/mathematics.h"
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
    std::vector<vec3> sphere_positions;
    std::vector<float> sphere_radii;
    std::vector<vec4> sphere_colors;

    Resource<GLShaderProgram> spheres_shader_program;

    Graphics &graphics;
    World &world;
};


#endif // PAINTING_H
