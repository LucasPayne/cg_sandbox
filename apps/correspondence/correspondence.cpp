#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"
#include "world/graphics/image.h"
#include <Eigen/Dense>

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


struct Correspondence : public IBehaviour {
    std::vector<vec2> A;
    std::vector<vec2> B;
    size_t n;
    Correspondence(std::vector<vec2> &_A, std::vector<vec2> &_B) :
        A{_A}, B{_B}, n{A.size()}
    {
        assert(A.size() == B.size());
    }

    inline Eigen::MatrixXf J(vec2 v) {
        Eigen::MatrixXf m = Eigen::MatrixXf::Zero(2, 6);
        m(0,0) = 1;
        m(1,1) = 1;
        m(0,2) = v.x();
        m(0,3) = v.y();
        m(1,4) = v.x();
        m(1,5) = v.y();
        return m;
    }

    Eigen::MatrixXf correspondence() {
        Eigen::MatrixXf M = Eigen::MatrixXf::Zero(6, 6);
        Eigen::VectorXf rhs = Eigen::VectorXf::Zero(6);
        for (int i = 0; i < n; i++) {
            auto Ja = J(A[i]);
            M += Ja.transpose() * Ja;
            Eigen::Vector2f pa(A[i].x(), A[i].y());
            Eigen::Vector2f pb(B[i].x(), B[i].y());
            // std::cout << M << "\n";
            // std::cout << rhs << "\n";
            // std::cout << pb - pa << "\n";
            rhs += Ja.transpose() * (pb - pa);
        }
        Eigen::VectorXf p = M.ldlt().solve(rhs);
        // p = [tx, ty, a00, a01, a10, a11]

        Eigen::MatrixXf transform(2, 3);
        transform << 1 + p[2], p[3], p[0],
                     p[4], 1 + p[5], p[1];
        std::cout << transform << "\n";
        return transform;
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_R || e.key.code == KEY_E) {
                vec2 p = vec2::random(-0.1, 0.1);
                float theta = 2*M_PI*frand();
                for (int i = 0; i < n; i++) {
                    A[i] = vec2::random(0.3, 0.7);
                    if (e.key.code == KEY_E) {
                        B[i] = (A[i] - vec2(0.5,0.5)).rotate(theta) + vec2(0.5,0.5) + p;
                    } else {
                        B[i] = A[i];
                    }
                }
            }
        }
    }


    void update() {
        int dx = 0;
        int dy = 0;
        if (world->input.keyboard.down(KEY_LEFT_ARROW)) {
            dx --;
        }
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) {
            dx ++;
        }
        if (world->input.keyboard.down(KEY_DOWN_ARROW)) {
            dy --;
        }
        if (world->input.keyboard.down(KEY_UP_ARROW)) {
            dy ++;
        }
        for (int i = 0; i < n; i++) B[i] += 0.1 * dt * vec2(dx, dy);
    }
    void post_render_update() {
        auto &paint = world->graphics.paint;
        paint.circles(main_camera, A, 0.01, vec4(1,0,0,1));
        paint.circles(main_camera, B, 0.01, vec4(0,1,0,1));

        auto paint_connection = [&](std::vector<vec2> &v1, std::vector<vec2> &v2, vec4 color) {
            for (int i = 0; i < n; i++) {
                std::vector<vec2> ps = {v1[i], v2[i]};
                paint.chain_2D(ps, 0.5, color);
            }
        };
        paint_connection(A, B, vec4(0,0,0,1));

        auto transform = correspondence();
        auto Ap = std::vector<vec2>(n);
        for (int i = 0; i < n; i++) {
            Eigen::Vector3f av(A[i].x(), A[i].y(), 1);
            auto p = transform * av;
            Ap[i] = vec2(p[0], p[1]);
        }
        paint.circles(main_camera, Ap, 0.005, vec4(0,1,1,1));
        paint_connection(A, Ap, vec4(0,0,1,1));
    }
};


App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    int n = 10;
    vec2 p = vec2::random(-0.1, 0.1);
    float theta = 2*M_PI*frand();
    auto A = std::vector<vec2>(n);
    auto B = std::vector<vec2>(n);
    for (int i = 0; i < n; i++) {
        A[i] = vec2::random(0.3, 0.7);
        B[i] = (A[i] - vec2(0.5,0.5)).rotate(theta) + vec2(0.5,0.5) + p;
        B[i] += vec2::random(-0.05,0.05);
    }
    auto cor_e = world.entities.add();
    auto cor = world.add<Correspondence>(cor_e, A, B);
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
