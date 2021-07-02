#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"
#include "world/graphics/image.h"

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
                }
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

    void post_render_update()
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
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

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
}


void App::close()
{
}

void App::loop()
{
}

void App::window_handler(WindowEvent e)
{
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
    World world(context);
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
