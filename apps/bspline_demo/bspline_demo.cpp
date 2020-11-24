#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"

Aspect<Camera> main_camera;


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
        for (int i = 0; i < num_vertical_knots; i++) {
            knots.push_back(i);
        }
        for (int i = 0; i < num_horizontal_knots; i++) {
            knots.push_back(i);
        }

        // // test: shift the knots.
        // for (int i = 0; i < num_vertical_knots; i++) {
        //     knots[i] += (2*((i+1)%2)-1)*0.25;
        // }

        initialize_on_GPU();

        //----------
        // note: This really should not be here.
        nurbs_program.add_shader(GLShader(VertexShader, "shaders/NURBS/quadratic_NURBS.vert"));
        nurbs_program.add_shader(GLShader(TessControlShader, "shaders/NURBS/quadratic_NURBS.tcs"));
        nurbs_program.add_shader(GLShader(TessEvaluationShader, "shaders/NURBS/quadratic_NURBS.tes"));
        nurbs_program.add_shader(GLShader(GeometryShader, "shaders/NURBS/quadratic_NURBS.geom"));
        nurbs_program.add_shader(GLShader(FragmentShader, "shaders/NURBS/quadratic_NURBS.frag"));
        nurbs_program.link();
    }

private:
    void initialize_on_GPU()
    {
        int num_control_points = m*n;

        // Create index windows.
        int index_bytes;
        if (num_control_points-1 <= 0xFF) {
            index_bytes = 1;
            index_type = GL_UNSIGNED_BYTE;
        } else if (num_control_points-1 <= 0xFFFF) {
            index_bytes = 2;
            index_type = GL_UNSIGNED_SHORT;
        } else {
            // It is assumed that 32 bits will be sufficient, so no check is made.
            index_bytes = 4;
            index_type = GL_UNSIGNED_INT;
        }

        num_vertical_patches = m - degree;
        num_horizontal_patches = n - degree;
        int num_patches = num_horizontal_patches * num_vertical_patches;
        num_indices = (degree + 1) * (degree + 1) * num_patches;
        std::vector<uint8_t> index_array_bytes(index_bytes * num_indices);
        int pos = 0;
        for (uint32_t i = 0; i < num_vertical_patches; i++) {
            for (uint32_t j = 0; j < num_horizontal_patches; j++) {
                for (uint32_t ii = 0; ii <= degree; ii++) {
                    for (uint32_t jj = 0; jj <= degree; jj++) {
                        uint32_t index = (i + ii)*n + j + jj;
                        if (index_bytes == 1) {
                            index_array_bytes[pos] = index;
                        } else if (index_bytes == 2) {
                            ((uint16_t *) &index_array_bytes[0])[pos] = index;
                        } else {
                            ((uint32_t *) &index_array_bytes[0])[pos] = index;
                        }
                        pos ++;
                    }
                    printf("\n");
                }
                printf("===\n");
            }
        }
        // getchar();

        // GPU data upload.
        //------------------------------------------------------------

        // Upload vertex data.
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * control_grid.size(), (const void *) &control_grid[0], GL_STATIC_DRAW);
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
        glBufferData(GL_TEXTURE_BUFFER, sizeof(float)*knots.size(), (const void *) &knots[0], GL_STATIC_DRAW);
        glGenTextures(1, &knot_texture);
        glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, knot_texture_buffer);
        // glBindTexture(GL_TEXTURE_BUFFER, 0);
        // glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }

    void sync_with_GPU()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * control_grid.size(), (const void *) &control_grid[0]);

        glBindBuffer(GL_TEXTURE_BUFFER, knot_texture_buffer);
        glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(float)*knots.size(), (const void *) &knots[0]);
    }

    void update()
    {
        for (int i = 0; i < control_grid.size(); i++) {
            control_grid[i].y() += 0.5*dt*sin(3*total_time + 10*control_grid[i].x()*control_grid[i].z())*cos(2*total_time + control_grid[i].x()*control_grid[i].x());
        }
        for (int i = 0; i < num_vertical_knots; i++) {
            knots[i] += 0.4*dt*sin(5*total_time) * (2*((i+1)%2)-1);
        }
        for (int i = 0; i < num_horizontal_knots; i++) {
            knots[num_horizontal_knots+i] += 0.4*dt*cos(5*total_time + i*0.2) * (2*((i+1)%2)-1);
        }

        sync_with_GPU();
        mat4x4 matrix = entity.get<Transform>()->matrix();
        nurbs_program.bind();
        glPatchParameteri(GL_PATCH_VERTICES, 9);
        glBindVertexArray(vao);

        glUniform1i(nurbs_program.uniform_location("num_vertical_knots"), num_vertical_knots);
        glUniform1i(nurbs_program.uniform_location("num_vertical_patches"), num_vertical_patches);
        glUniform1i(nurbs_program.uniform_location("num_horizontal_patches"), num_horizontal_patches);
        glUniform1i(nurbs_program.uniform_location("knots"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer); //-----probably don't need this.


        for (auto camera : world->entities.aspects<Camera>()) {
            world->graphics.begin_camera_rendering(camera);
            mat4x4 mvp_matrix = camera->view_projection_matrix() * matrix;

            glUniformMatrix4fv(nurbs_program.uniform_location("mvp_matrix"), 1, GL_FALSE, (const GLfloat *) &mvp_matrix);


            glPointSize(10);
            glLineWidth(1);
            glDrawElements(GL_PATCHES, num_indices, index_type, (const void *) 0);
            // glDrawArrays(GL_POINTS, 0, control_grid.size());

            world->graphics.end_camera_rendering(camera);
        }
        nurbs_program.unbind();

        for (auto v : control_grid) world->graphics.paint.sphere((matrix * vec4(v, 1)).xyz(), 0.006, vec4(1,1,1,1));
    }

    int degree;
    int m;
    int n;
    int num_vertical_knots;
    int num_horizontal_knots;
    int num_vertical_patches;
    int num_horizontal_patches;
    GLenum index_type;
    int num_indices; // Number of indices in the list of index windows.
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


std::vector<vec3> points;
float omega = 0.25;

App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    
    Entity obj = create_mesh_object(world, "resources/models/large/buddha.obj", "shaders/uniform_color.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

    
#if 1
    auto demo = world.entities.add();
    world.add<BSplineDemo>(demo, cameraman.get<Camera>(), 9);
#endif

#if 1
    auto dragon = world.entities.add();
    dragon.add<Transform>(vec3(1,0,0));
    world.add<WireframeDemo>(dragon, "resources/models/dragon.off");
#endif

#if 1
    auto nurbs_entity = world.entities.add();
    nurbs_entity.add<Transform>();
    int m = 30;
    int n = 30;
    std::vector<vec3> positions;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // positions.push_back(vec3(0.2*i - 0.32, 0.2*j - 0.32, sin(i*0.08)));

            positions.push_back(vec3(0.2*j, -2, -0.2*i));
        }
    }
    world.add<DrawableNURBS>(nurbs_entity, 2, m, n, positions);

    points = std::vector<vec3>(10);
    for (int i = 0; i < 10; i++) {
        points[i] = vec3::random(-1,1);
    }

#endif
}


void App::close()
{
}
void App::loop()
{
    world.graphics.paint.chain(points, points.size(), vec4(0,0,0,1));
    world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_textures["position"], vec2(0.06,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
    world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_textures["normal"], vec2(0.36,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
    world.graphics.paint.bordered_sprite(main_camera, world.graphics.gbuffer_textures["albedo"], vec2(0.66,0.09), 0.28,0.28, 3, vec4(0,0,0,1));
}

void App::window_handler(WindowEvent e)
{
    force_aspect_ratio(e);
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_C) {
            std::vector<vec3> new_points;
            new_points.clear();
            for (int j = 0; j < points.size()-1; j++) {
                new_points.push_back(vec3::lerp(points[j], points[j+1], omega));
                new_points.push_back(vec3::lerp(points[j], points[j+1], 1-omega));
            }
            points.clear();
            for (auto p : new_points) points.push_back(p);
        }
        if (e.key.code == KEY_V) {
            points.clear();
            for (int i = 0; i < 10; i++) points.push_back(vec3::random(-1,1));
        }
        if (e.key.code == KEY_X) {
            omega += 0.01;
        }
        if (e.key.code == KEY_Z) {
            omega -= 0.01;
        }
    }
    
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
