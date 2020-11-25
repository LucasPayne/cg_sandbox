#ifndef PAINTING_H
#define PAINTING_H
#include "core.h"
#include "world/resources/resources.h"
#include "world/graphics/drawing.h"
#include "mathematics/mathematics.h"
#include "mesh_processing/mesh_processing.h"
#include "world/standard_aspects/standard_aspects.h"
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

struct PaintingLines {
    std::vector<vec3> points;
    float width;
    vec4 color;
    PaintingLines(std::vector<vec3> _points, float _width, vec4 _color) :
        points{_points},
        width{_width},
        color{_color}
    {}
};

struct PaintingLines2D {
    std::vector<vec2> points;
    float width;
    vec4 color;
    Aspect<Camera> camera;
    PaintingLines2D(Aspect<Camera> _camera, std::vector<vec2> _points, float _width, vec4 _color) :
        points{_points},
        width{_width},
        color{_color},
        camera{_camera}
    {}
};


struct PaintingCircles {
    // Header struct.
    Aspect<Camera> camera;
    int n;
    float radius;
    vec4 color;
    float outline_width;
    vec4 outline_color;
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


struct SpriteRenderData {
    Aspect<Camera> camera;
    GLuint texture;
    vec2 bottom_left;
    float width;
    float height;
    bool is_depth;
    SpriteRenderData(Aspect<Camera> _camera, GLuint _texture, vec2 _bottom_left, float _width, float _height, bool _is_depth) :
        camera{_camera}, texture{_texture}, bottom_left{_bottom_left}, width{_width}, height{_height}, is_depth{_is_depth}
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

    // 3D painting commands.
    void sphere(vec3 position, float radius, vec4 color);
    void line(vec3 a, vec3 b, float width, vec4 color);
    void wireframe(SurfaceGeometry &geom, mat4x4 model_matrix, float width);
    void chain(std::vector<vec3> &points, float width, vec4 color);

    // 2D painting commands.
    void bspline(Aspect<Camera> camera, int degree, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color);
    void quadratic_bspline(Aspect<Camera> camera, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color);
    void circles(Aspect<Camera> camera, std::vector<vec2> &positions, float radius, vec4 color, float outline_width = 0.f, vec4 outline_color = vec4::zero());
    void chain_2D(Aspect<Camera> camera, std::vector<vec2> &points, float width, vec4 color);
    void sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height);
    void depth_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height);
    void bordered_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color);
    void bordered_depth_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color);

private:
    // 3D painting buffers.
    std::vector<PaintingSphere> spheres;
    std::vector<PaintingLines> lines;
    std::vector<WireframeRenderData> wireframe_render_data;

    // 2D painting buffers.
    std::vector<PaintingCircles> circle_buffer;
    std::vector<vec2> circle_positions;
    std::vector<PaintingLines2D> lines_2D;
    std::vector<SpriteRenderData> sprites;

    // 3D painting programs.
    Resource<GLShaderProgram> spheres_shader_program;
    Resource<GLShaderProgram> lines_shader_program;
    Resource<GLShaderProgram> wireframe_shader_program;

    // 2D painting programs.
    static const int max_bspline_degree;
    std::vector<Resource<GLShaderProgram>> bspline_2D_shader_programs; // The program for degree i+1 is at index i.
    std::vector<Resource<GLShaderProgram>> bspline_2D_fillets_shader_programs;
    Resource<GLShaderProgram> primitive_lines_2D_shader_program;
    Resource<GLShaderProgram> circles_2D_shader_program;
    Resource<GLShaderProgram> sprite_shader_program;
    Resource<GLShaderProgram> depth_sprite_shader_program;

    void render_spheres();
    void render_lines();
    void render_wireframes();
    void render_circles();
    void render_lines_2D();
    void render_sprites();

    Graphics &graphics;
    World &world;
};


#endif // PAINTING_H
