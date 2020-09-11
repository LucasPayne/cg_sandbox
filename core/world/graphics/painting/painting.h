#ifndef PAINTING_H
#define PAINTING_H
#include "core.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "mathematics/mathematics.h"
#include "mesh_processing/mesh_processing.h"
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

struct PaintingLine {
    vec3 a;
    vec3 b;
    float width;
    vec4 color;
    PaintingLine(vec3 _a, vec3 _b, float _width, vec4 _color) :
        a{_a},
        b{_b},
        width{_width},
        color{_color}
    {}
};

struct WireframeRenderData {
    GLuint vao;
    GLuint vertex_attribute_buffer;
    GLuint triangle_index_buffer;
    uint32_t num_indices;
    uint32_t num_vertices;
    mat4x4 model_matrix;
    float width;
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
    void line(vec3 a, vec3 b, float width, vec4 color);

    void wireframe(SurfaceGeometry &geom, mat4x4 model_matrix, float width);

private:
    std::vector<PaintingSphere> spheres;
    std::vector<PaintingLine> lines;
    std::vector<WireframeRenderData> wireframe_render_data;

    Resource<GLShaderProgram> spheres_shader_program;
    Resource<GLShaderProgram> lines_shader_program;
    Resource<GLShaderProgram> wireframe_shader_program;

    void render_spheres();
    void render_lines();
    void render_wireframes();

    Graphics &graphics;
    World &world;
};


#endif // PAINTING_H
