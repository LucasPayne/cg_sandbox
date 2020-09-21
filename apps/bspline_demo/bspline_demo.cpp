#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/object_viewer_cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"


class DrawableNURBS : public IBehaviour {
public:
    DrawableNURBS(int _degree, int _m, int _n, std::vector<vec3> &_control_grid) :
        degree{_degree},
        m{_m}, n{_n},
        num_vertical_knots{_m + _degree + 1},
        num_horizontal_knots{_n + _degree + 1}
    {
        assert(m > degree && n > degree);

        for (auto v : _control_grid) control_grid.push_back(v);

        weights.insert(weights.end(), control_grid.size(), 1.f);
        for (int i = 0; i < m; i++) {
            knots.push_back(i);
        }
        for (int i = 0; i < n; i++) {
            knots.push_back(i);
        }
        initialize_on_GPU();

        //----------
        // note: This really should not be here.
        nurbs_program.add_shader(GLShader(VertexShader, "shaders/NURBS/quadratic_NURBS.vert"));
        nurbs_program.add_shader(GLShader(TessControlShader, "shaders/NURBS/quadratic_NURBS.tcs"));
        nurbs_program.add_shader(GLShader(TessEvaluationShader, "shaders/NURBS/quadratic_NURBS.tes"));
        nurbs_program.add_shader(GLShader(FragmentShader, "shaders/NURBS/quadratic_NURBS.frag"));
        nurbs_program.link();
    }

private:
    void initialize_on_GPU()
    {
        int num_control_points = m*n;

        // Create index windows.
        int index_bytes;
        GLenum index_type;
        if (num_control_points-1 <= 0xFF) {
            index_bytes = 1;
            index_type = GL_UNSIGNED_BYTE;
        } else if (num_control_points-1 <= 0xFFFF) {
            index_bytes = 2;
            index_bytes = GL_UNSIGNED_SHORT;
        } else {
            // It is assumed that 32 bits will be sufficient, so no check is made.
            index_bytes = 4;
            index_bytes = GL_UNSIGNED_INT;
        }

        int num_horizontal_patches = n - degree;
        int num_vertical_patches = m - degree;
        int num_patches = num_horizontal_patches * num_vertical_patches;
        std::vector<uint8_t> index_array_bytes((degree + 1)*(degree + 1) * index_bytes * num_patches);
        int pos = 0;
        for (uint32_t i = 0; i < num_vertical_patches; i++) {
            for (uint32_t j = 0; j < num_horizontal_patches; j++) {
                for (uint32_t ii = 0; ii <= degree; ii++) {
                    for (uint32_t jj = 0; jj <= degree; jj++) {
                        uint32_t index = (i + ii)*n + j + jj;
                        if (index_bytes == 1) {
                            index_array_bytes[pos] = index;
                        } else if (index_bytes == 2) {
                            *((uint16_t *) &index_array_bytes[pos]) = index;
                        } else {
                            *((uint32_t *) &index_array_bytes[pos]) = index;
                        }
                        pos ++;
                    }
                }
            }
        }

        // GPU data upload.
        //------------------------------------------------------------
        // Upload vertex data.
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * num_control_points, (const void *) &control_grid[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Upload index buffer.
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array_bytes.size(), (const void *) &index_array_bytes[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Upload 1D texture of knots.
        glGenBuffers(1, &knot_texture_buffer);
        glBindBuffer(GL_TEXTURE_BUFFER, knot_texture_buffer);
        glBufferData(GL_TEXTURE_BUFFER, knots.size(), (const void *) &knots[0], GL_STATIC_DRAW);
        glGenTextures(1, &knot_texture);
        glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, knot_texture_buffer);
        glBindTexture(GL_TEXTURE_BUFFER, 0);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }

    void update()
    {
        mat4x4 matrix = entity.get<Transform>()->matrix();

        nurbs_program.bind();
        glPatchParameteri(GL_PATCH_VERTICES, 9);
        for (auto camera : world->entities.aspects<Camera>()) {
            mat4x4 mvp_matrix = 

            world->graphics.begin_camera_rendering(camera);

            
            
            glBindVertexArray(vao);
            glDrawElements

            world->graphics.end_camera_rendering(camera);
        }
        nurbs_program.unbind();
    }

    int degree;
    int m;
    int n;
    int num_vertical_knots;
    int num_horizontal_knots;
    std::vector<vec3> control_grid;
    std::vector<float> weights;
    std::vector<float> knots;

    GLuint vao;
    GLuint vertex_buffer;
    GLuint knot_texture;
    GLuint knot_texture_buffer;
    GLuint index_buffer;


    // shaders
    GLShaderProgram nurbs_program;
};


struct BSplineDemo : public IBehaviour {
    Aspect<Camera> main_camera;
    std::vector<vec2> positions;
    std::vector<float> knots;
    float width;
    vec4 color;
    
    float point_radius;
    bool dragging_point;
    int dragging_point_index;

    BSplineDemo(Aspect<Camera> _main_camera, int n) :
        dragging_point{false}
    {
        main_camera = _main_camera;
        color = vec4(1,0.4,0.4,1);
        width = 0.008;
        point_radius = 0.005;
        positions = std::vector<vec2>(n);
        knots = std::vector<float>(n + 3);
        for (int i = 0; i < n; i++) {
            positions[i] = vec2::random(0.1, 0.9);
        }
        for (int i = 0; i < n+3; i++) {
            knots[i] = i;
        }
    }

    void update() {
        world->graphics.paint.quadratic_bspline(main_camera, positions, knots, width, color);
        world->graphics.paint.circles(main_camera, positions, point_radius, vec4(1,1,1,1), 0.333, vec4(0,0,0,1));
        // world->graphics.paint.lines(main_camera, positions, 0.001, vec4(0,0,0,1));
    }

    void mouse_handler(MouseEvent e) {
        if (e.action == MOUSE_BUTTON_PRESS) {
            for (int i = 0; i < positions.size(); i++) {
                if (vec2::dot(vec2(e.cursor.x, e.cursor.y) - positions[i],
                              vec2(e.cursor.x, e.cursor.y) - positions[i]) <= point_radius * point_radius) {
                    dragging_point = true;
                    dragging_point_index = i;
                }
            }
        } else if (e.action == MOUSE_BUTTON_RELEASE) {
            dragging_point = false;
        } else if (e.action == MOUSE_MOVE) {
            if (dragging_point) {
                positions[dragging_point_index] = vec2(e.cursor.x, e.cursor.y);
            }
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_I) {
                for (int i = 0; i < knots.size(); i++) {
                    knots[i] += (2*((i+1)%2)-1)*0.1;
                }
            }
            if (e.key.code == KEY_O) {
                for (int i = 0; i < knots.size(); i++) {
                    knots[i] -= (2*((i+1)%2)-1)*0.1;
                }
            }
            if (e.key.code == KEY_P) {
                for (int i = 0; i < positions.size(); i++) {
                    positions[i] = vec2::random(0.1, 0.9);
                }
            }
            float width_grow_factor = 1.25;
            if (e.key.code == KEY_Y) {
                width /= width_grow_factor;
            }
            if (e.key.code == KEY_U) {
                width *= width_grow_factor;
            }
        }
    }
};



struct WireframeDemo : public IBehaviour {
    SurfaceGeometry geom;

    WireframeDemo(const std::string &model_path, float scale = 1.f) {
        auto model = MLModel::load(model_path);
        geom.add_model(model);
        for (auto v : geom.vertices()) {
            geom.vertex_positions[v] *= scale;
        }
    }

    void update() {
        auto t = entity.get<Transform>();
        t->rotation = Quaternion::from_axis_angle(vec3(0,1,0), 0.2*total_time);
        world->graphics.paint.wireframe(geom, t->matrix(), 0.001);
    }
};




class App : public IGC::Callbacks {
public:
    World &world;
    App(World &world);

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);
};
App::App(World &_world) : world{_world}
{
    auto obj = create_mesh_object(world, "resources/models/large/buddha.obj", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    Entity cameraman = create_object_viewer_cameraman(world, obj);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    
    auto demo = world.entities.add();
    world.add<BSplineDemo>(demo, cameraman.get<Camera>(), 9);

    auto dragon = world.entities.add();
    dragon.add<Transform>(vec3(1,0,0));
    world.add<WireframeDemo>(dragon, "resources/models/dragon.off");

    auto nurbs_entity = world.entities.add();
    nurbs_entity.add<Transform>();
    int m = 6;
    int n = 5;
    std::vector<vec3> positions(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            positions.push_back(vec3(0.2*i, 0, 0.2*j));
        }
    }
    world.add<DrawableNURBS>(nurbs_entity, 2, m, n, positions);
}


void App::close()
{
}
void App::loop()
{
}

void App::window_handler(WindowEvent e)
{
    force_aspect_ratio(e);
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    srand(time(0));

    printf("[main] Creating context...\n");
    IGC::Context context("A world");
    printf("[main] Creating world...\n");
    World world;
    printf("[main] Adding world callbacks...\n");
    context.add_callbacks(&world);
    context.add_callbacks(&world.input);

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
