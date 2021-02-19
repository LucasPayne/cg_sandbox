/*--------------------------------------------------------------------------------
Some differential geometry of surfaces.
--------------------------------------------------------------------------------*/
#include <time.h>
#include <functional>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"
#include "world/graphics/image.h"

#include "automatic_differentiation.h"


Aspect<Camera> main_camera;


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


struct ParametricSurface : public IBehaviour {
    std::function<vec3(float, float)> f;
    std::function<vec3(float, float)> dfu;
    std::function<vec3(float, float)> dfv; // Jacobian
    std::function<vec3(float, float)> ddfuu;
    std::function<vec3(float, float)> ddfuv;
    std::function<vec3(float, float)> ddfvv; // Hessian

    vec2 param;

    int tes_h;
    int tes_w;
    float step_h;
    float step_w;

    Resource<GLShaderProgram> curvature_shader;

    bool visualize_mean_or_gaussian;

    ParametricSurface(std::function<vec3(float, float)> _f,
                      std::function<vec3(float, float)> _dfu,
                      std::function<vec3(float, float)> _dfv,
                      std::function<vec3(float, float)> _ddfuu,
                      std::function<vec3(float, float)> _ddfuv,
                      std::function<vec3(float, float)> _ddfvv)
    : f{_f}, dfu{_dfu}, dfv{_dfv},
      ddfuu{_ddfuu},
      ddfuv{_ddfuv},
      ddfvv{_ddfvv},
      param(0.5, 0.5)
    {}

    void init() {
        curvature_shader = world->resources.add<GLShaderProgram>();
        curvature_shader->add_shader(GLShader(VertexShader, "apps/surfaces/curvature.vert"));
        curvature_shader->add_shader(GLShader(FragmentShader, "apps/surfaces/curvature.frag"));
        curvature_shader->link();

        tes_h = 20;
        tes_w = 20;
        step_h = 1.f / (tes_h - 1);
        step_w = 1.f / (tes_w - 1);

        visualize_mean_or_gaussian = 1; // gaussian
    }


    mat2x2 first_fundamental_form(float u, float v) const {
        vec3 deru = dfu(u, v);
        vec3 derv = dfv(u, v);
        // Calculate the first fundamental form.
        // E,F,G
        float E = vec3::dot(deru, deru);
        float F = vec3::dot(deru, derv);
        float G = vec3::dot(derv, derv);
        mat2x2 I = mat2x2(
            E, F,
            F, G
        );
        return I;
    }

    float surface_area(int tes = 40, bool gaussian_quadrature = true) const {
        const int tes_h = tes;
        const int tes_w = tes;
        const float step_h = 1.f/tes_h;
        const float step_w = 1.f/tes_w;

        if (gaussian_quadrature) {
	    float left_node_shift = 0.5f - 0.5f/sqrt(3);
	    float right_node_shift = 0.5f + 0.5f/sqrt(3);
            float measured = 0.f;
	    for (int i = 0; i < tes_h; i++) {
                for (int j = 0; j < tes_w; j++) {
                    float u = step_h * i;
                    float v = step_w * j;
                    float bl = sqrt(first_fundamental_form(u + step_h*left_node_shift, v  + step_w*left_node_shift).determinant());
                    float br = sqrt(first_fundamental_form(u + step_h*left_node_shift, v  + step_w*right_node_shift).determinant());
                    float tl = sqrt(first_fundamental_form(u + step_h*right_node_shift, v + step_w*left_node_shift).determinant());
                    float tr = sqrt(first_fundamental_form(u + step_h*right_node_shift, v + step_w*right_node_shift).determinant());
                    measured += ((bl + br + tl + tr)*0.25) * step_w * step_h;
                }
            }
            return measured;
        } else {
            float measured = 0.f;
	    for (int i = 0; i < tes_h; i++) {
                for (int j = 0; j < tes_w; j++) {
                    float u = step_h * i;
                    float v = step_w * j;
                    float bl = sqrt(first_fundamental_form(u + step_h, v  + step_w).determinant());
                    float br = sqrt(first_fundamental_form(u + step_h, v  + step_w).determinant());
                    float tl = sqrt(first_fundamental_form(u + step_h, v + step_w).determinant());
                    float tr = sqrt(first_fundamental_form(u + step_h, v + step_w).determinant());
                    measured += ((bl + br + tl + tr)*0.25) * step_w * step_h;
                }
            }
            return measured;
        }
    };
    

    vec3 surface_normal(float u, float v) const {
        return -vec3::cross(dfu(u, v), dfv(u, v)).normalized();
    }

    mat2x2 shape_operator(float u, float v) const {
        vec3 point = f(u, v);
        vec3 deru = dfu(u, v);
        vec3 derv = dfv(u, v);
        vec3 normal = surface_normal(u, v);
        vec3 deruu = ddfuu(u, v);
        vec3 deruv = ddfuv(u, v);
        vec3 dervv = ddfvv(u, v);

        // Calculate the first fundamental form.
        // E,F,G
        float E = vec3::dot(deru, deru);
        float F = vec3::dot(deru, derv);
        float G = vec3::dot(derv, derv);
        mat2x2 I = mat2x2(
            E, F,
            F, G
        );

        // Calculate the second fundamental form.
        float e = vec3::dot(normal, deruu);
        float f = vec3::dot(normal, deruv);
        float g = vec3::dot(normal, dervv);
        mat2x2 II = mat2x2(
            e, f,
            f, g
        );

        // inv(I) * II was derived from minimizing/maximizing t^T II t w/r/t t such that t^T I t = 1 (min/maximizing a quadratic form over an ellipse).
        // This appears to be in line with the definition of the shape operator. https://en.wikipedia.org/wiki/Differential_geometry_of_surfaces#Shape_operator
        return I.inverse() * II;
    }
    std::pair<float, float> curvatures(float u, float v) const {
        mat2x2 P = shape_operator(u, v);
        return std::pair<float, float>(P.determinant(), P.trace()/2);
    }

    void update() {
        const vec4 color = vec4(0.2*vec3(1,1,1),1);
        const float line_width = 3;

        auto transform = entity.get<Transform>();
        auto p = transform->position;

        for (int i = 0; i < tes_h-1; i++) {
	    float y = i * step_h;
            for (int j = 0; j < tes_w-1; j++) {
                float x = j * step_w;
                vec3 a = f(x, y);
                vec3 b = f(x + step_w, y);
                vec3 c = f(x + step_w, y + step_h);
                vec3 d = f(x, y + step_h);
                world->graphics.paint.line(p + a, p + b, line_width, color);
                world->graphics.paint.line(p + a, p + d, line_width, color);
                if (i == tes_h-2) world->graphics.paint.line(p + d, p + c, line_width, color);
                if (j == tes_w-2) world->graphics.paint.line(p + b, p + c, line_width, color);
            }
        }
        const vec4 sphere_color = vec4(1,0,0,1);
        const float sphere_size = 0.05;
        vec3 point = f(param.x(), param.y());
        vec3 normal = surface_normal(param.x(), param.y());
        world->graphics.paint.sphere(point, sphere_size, sphere_color);
        vec3 deru = dfu(param.x(), param.y());
        vec3 derv = dfv(param.x(), param.y());
        world->graphics.paint.line(point, point + 0.4*deru.normalized(), line_width * 2, vec4(1,0,0,1));
        world->graphics.paint.line(point, point + 0.4*derv.normalized(), line_width * 2, vec4(0,1,0,1));
        world->graphics.paint.line(point, point + 0.4 * normal, line_width * 2, vec4(0,0,1,1));

        // Calculate the first fundamental form.
        // E,F,G
        float E = vec3::dot(deru, deru);
        float F = vec3::dot(deru, derv);
        float G = vec3::dot(derv, derv);
        mat2x2 I = mat2x2(
            E, F,
            F, G
        );
        std::cout << I << "\n";

        // Calculate the second fundamental form.
        vec3 deruu = ddfuu(param.x(), param.y());
        vec3 deruv = ddfuv(param.x(), param.y());
        vec3 dervv = ddfvv(param.x(), param.y());
        float e = vec3::dot(normal, deruu);
        float f = vec3::dot(normal, deruv);
        float g = vec3::dot(normal, dervv);
        mat2x2 II = mat2x2(
            e, f,
            f, g
        );
        std::cout << II << "\n";

        // inv(I) * II was derived from minimizing/maximizing t^T II t w/r/t t such that t^T I t = 1 (min/maximizing a quadratic form over an ellipse).
        // This appears to be in line with the definition of the shape operator. https://en.wikipedia.org/wiki/Differential_geometry_of_surfaces#Shape_operator
        mat2x2 M = I.inverse() * II;
        std::cout << M << "\n";
        mat2x2 V,D;
        std::tie(V,D) = M.diagonalize();
        std::cout << V << "\n";
        std::cout << D << "\n";

        vec2 e1 = V.column(0);
        vec2 e2 = V.column(1);
        vec3 e1p = deru*e1.x() + derv*e1.y();
        vec3 e2p = deru*e2.x() + derv*e2.y();

        float l1 = D.entry(0,0);
        float l2 = D.entry(1,1);
        float gaussian_curvature = l1 * l2;
        float mean_curvature = 0.5 * (l1 + l2);
        printf("%.5f, %.5f\n", M.determinant(), M.trace()/2); // This should give the same values.
        printf("curvatures:\n    Gaussian curvature: %.5f\n    Mean curvature:     %.5f\n", gaussian_curvature, mean_curvature);

        world->graphics.paint.line(point, point + 0.4*e1p.normalized(), line_width * 2.5, vec4(1,0,1,1));
        world->graphics.paint.line(point, point + 0.4*e2p.normalized(), line_width * 2.5, vec4(1,0,1,1));

        // Compare quadrature rules for integrating surface area.
        printf("surface area:\n");
        printf("gaussian quadrature:\n");
        for (int i = 1; i <= 10; i++) {
            printf("    %dx%d: %.7f\n", i, i, surface_area(i, true));
        }
        printf("    ...x...: %.7f\n", surface_area(100, true));
        printf("trapezium rule:\n");
        for (int i = 1; i <= 10; i++) {
            printf("    %dx%d: %.7f\n", i, i, surface_area(i, false));
        }
        printf("    ...x...: %.7f\n", surface_area(100, false));
    }

    void post_render_update() {
        auto transform = entity.get<Transform>();

        std::vector<vec3> positions(tes_h * tes_w);
        std::vector<vec2> curvatures_array(tes_h * tes_w);
        for (int i = 0; i < tes_h; i++) {
	    float y = i * step_h;
            for (int j = 0; j < tes_w; j++) {
                float x = j * step_w;
                float g,m;
                std::tie(g, m) = curvatures(x, y);
                curvatures_array[tes_w*i + j] = vec2(g, m);
                positions[tes_w*i + j] = f(x, y);
            }
        }
        vec2 max_abs_curvatures = vec2(0,0);
        for (vec2 c : curvatures_array) {
            max_abs_curvatures = vec2::max(max_abs_curvatures, c.abs());
        }

        mat4x4 mvp_matrix = main_camera->view_projection_matrix() * transform->matrix();
        curvature_shader->bind();
        glUniformMatrix4fv(curvature_shader->uniform_location("mvp_matrix"), 1, GL_FALSE, (const GLfloat *) &mvp_matrix);
        glUniform2fv(curvature_shader->uniform_location("max_abs_curvatures"), 1, (const GLfloat *) &max_abs_curvatures);
        glUniform1i(curvature_shader->uniform_location("mode"), visualize_mean_or_gaussian);

        GLuint vao;
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint position_buffer;
        glGenBuffers(1, &position_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * tes_h * tes_w, (const void *) &positions[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
        glEnableVertexAttribArray(0);
        GLuint curvature_buffer;
        glGenBuffers(1, &curvature_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, curvature_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * tes_h * tes_w, (const void *) &curvatures_array[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
        glEnableVertexAttribArray(1);

        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        int num_indices = 3*2*(tes_w-1)*(tes_h-1);
        auto indices = std::vector<uint16_t>(3*2*(tes_w-1)*(tes_h-1));
        int index_pos = 0;
        for (int i = 0; i < tes_h-1; i++) {
            for (int j = 0; j < tes_w-1; j++) {
                indices[index_pos] = tes_w*i + j;
                indices[index_pos+1] = tes_w*i + j+1;
                indices[index_pos+2] = tes_w*(i+1) + j+1;

                indices[index_pos+3] = tes_w*i + j;
                indices[index_pos+4] = tes_w*(i+1) + j+1;
                indices[index_pos+5] = tes_w*(i+1) + j;
                index_pos += 6;
            }
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * num_indices, (const void *) &indices[0], GL_DYNAMIC_DRAW);
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, (const void *) 0);
        curvature_shader->unbind();
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_G) visualize_mean_or_gaussian = (visualize_mean_or_gaussian + 1) % 2;
        }
    }
};

struct Test1 : public IBehaviour {
    ParametricSurface *surface;
    Test1(ParametricSurface *_surface) : surface{_surface}
    {}

    void update() {
        surface->param = vec2(0.5 + 0.45 * cos(total_time), 0.5 + 0.45 * sin(total_time));
    }
};





App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity e = world.entities.add();
    e.add<Transform>(0,0,0);
    world.add<Test1>(e, world.add<ParametricSurface>(e,
        [](float u, float v) { // f
            return vec3(3*u, 4*u*u*v - 2*v*v, 4*v);
        },
        [](float u, float v) { // dfu
            return vec3(3, 8*u*v, 0);
        },
        [](float u, float v) { // dfv
            return vec3(0, 4*u*u - 4*v, 4);
        },
        [](float u, float v) { // ddfuu
            return vec3(0, 8*v, 0);
        },
        [](float u, float v) { // ddfuv
            return vec3(0, 8*u, 0);
        },
        [](float u, float v) { // ddfvv
            return vec3(0, -4, 0);
        }

        // [](float u, float v) { // f
        //     return vec3(u, u*u - 2*u*v + v*v, v);
        // },
        // [](float u, float v) { // dfu
        //     return vec3(1, 2*u - 2*v, 0);
        // },
        // [](float u, float v) { // dfv
        //     return vec3(0, 2*v - 2*u, 1);
        // },
        // [](float u, float v) { // ddfuu
        //     return vec3(0, 2, 0);
        // },
        // [](float u, float v) { // ddfuv
        //     return vec3(0, -2, 0);
        // },
        // [](float u, float v) { // ddfvv
        //     return vec3(0, 2, 0);
        // }

        // [](float u, float v) { // f
        //     return vec3(3*u, 0, 2*v);
        // },
        // [](float u, float v) { // dfu
        //     return vec3(3, 0, 0);
        // },
        // [](float u, float v) { // dfv
        //     return vec3(0, 0, 2);
        // },
        // [](float u, float v) { // ddfuu
        //     return vec3(0, 0, 0);
        // },
        // [](float u, float v) { // ddfuv
        //     return vec3(0, 0, 0);
        // },
        // [](float u, float v) { // ddfvv
        //     return vec3(0, 0, 0);
        // }
    ));
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

    if (e.action == KEYBOARD_PRESS) {
        // if (e.key.code == KEY_R) world.graphics.compile_shaders();
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
    World world(context);
    printf("[main] Adding world callbacks...\n");

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
