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
#include <numeric>

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
    enum Modes {
        AFFINE,
        TRANSLATION,
        TRANSLATION_AND_SCALE,
        TRANSLATION_AND_ROTATION, // requires non-linear least squares
        NUM_MODES
    };
    struct ModeData {
        size_t rows;
        size_t cols;
        bool linear;
    } mode_data[NUM_MODES] = { // mode-specific data such as the size of the Jacobian
        {2, 6, true},
        {2, 2, true},
        {2, 3, true},
        {2, 3, false},
    };
    
    std::vector<vec2> A;
    std::vector<vec2> B;
    size_t n;
    int mode;
    Correspondence(std::vector<vec2> &_A, std::vector<vec2> &_B) :
        A{_A}, B{_B}, n{A.size()}
    {
        assert(A.size() == B.size());
        mode = TRANSLATION_AND_ROTATION;
    }

    inline Eigen::MatrixXf J(vec2 v, Eigen::VectorXf motion_parameters) {
        auto &p = motion_parameters;
        Eigen::MatrixXf m = Eigen::MatrixXf::Zero(mode_data[mode].rows, mode_data[mode].cols);
        switch (mode) {
        case AFFINE:
            // p = [tx, ty, a00, a01, a10, a11]
            m(0,0) = 1;
            m(1,1) = 1;
            m(0,2) = v.x();
            m(0,3) = v.y();
            m(1,4) = v.x();
            m(1,5) = v.y();
            return m;
        case TRANSLATION:
            // p = [tx, ty]
            m << 1,0,
                 0,1;
            return m;
        case TRANSLATION_AND_SCALE:
            // p = [tx, ty, a]
            m << 1,0, v.x(),
                 0,1, v.y();
            return m;
        case TRANSLATION_AND_ROTATION:
            // p = [tx, ty, theta]
            m << 1,0, -sin(p[2])*v.x() - cos(p[2])*v.y(),
                 0,1, cos(p[2])*v.x() - sin(p[2])*v.y();
            return m;
        }
        assert(0);
    }
    std::function<vec2(vec2)> construct_transform(Eigen::VectorXf p) {
        Eigen::MatrixXf transform(2, 3);
        switch (mode) {
        case AFFINE:
            transform << 1 + p[2], p[3], p[0],
                         p[4], 1 + p[5], p[1];
            break;
        case TRANSLATION:
            transform << 1, 0, p[0],
                         0, 1, p[1];
            break;
        case TRANSLATION_AND_SCALE:
            transform << 1 + p[2], 0, p[0],
                         0, 1 + p[2], p[1];
            break;
        case TRANSLATION_AND_ROTATION:
            transform << cos(p[2]), -sin(p[2]), p[0],
                         sin(p[2]), cos(p[2]), p[1];
            break;
        }
        // Return a callable which transforms points as vec2s.
        return [transform](vec2 point)->vec2 {
            Eigen::Vector3f point_h = Eigen::Vector3f(point.x(), point.y(), 1);
            Eigen::Vector2f transformed = transform * point_h;
            return vec2(transformed[0], transformed[1]);
        };
    }

    auto correspondence() {
        // Initialize motion parameters to zero.
        Eigen::VectorXf motion_parameters = Eigen::VectorXf::Zero(mode_data[mode].cols);
        
        // Transformed points (initial transform is the identity).
        std::vector<vec2> Ap = A;

        for (int N = 0; N < 10; N++) {
            Eigen::MatrixXf M = Eigen::MatrixXf::Zero(mode_data[mode].cols, mode_data[mode].cols);
            Eigen::VectorXf rhs = Eigen::VectorXf::Zero(mode_data[mode].cols);
            for (int i = 0; i < n; i++) {
                auto Ja = J(A[i], motion_parameters);
                M += Ja.transpose() * Ja;
                Eigen::Vector2f target_point(B[i].x(), B[i].y());
                Eigen::Vector2f image_point(Ap[i].x(), Ap[i].y());
                rhs += Ja.transpose() * (target_point - image_point);
            }
	    motion_parameters += M.ldlt().solve(rhs);
            if (mode_data[mode].linear) break; // No iteration if using linear least squares.

            auto transform = construct_transform(motion_parameters);
            for (int i = 0; i < n; i++) Ap[i] = transform(A[i]);
        }
        return construct_transform(motion_parameters);
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
            if (e.key.code == KEY_M) mode = (mode + 1) % NUM_MODES;
        }
    }


    void update() {
        // shift the points with arrow keys
        vec2 dkey = world->arrow_key_vector();
        for (int i = 0; i < n; i++) B[i] += 0.1 * dt * dkey;

        // Compute centroid of B points.
        vec2 centroid = vec2::zero();
        for (int i = 0; i < n; i++) centroid += B[i];
        centroid /= n; 

        if (world->input.keyboard.down(KEY_P)) {
            // rotate the points
            for (int i = 0; i < n; i++) B[i] = centroid + (B[i] - centroid).rotate(dt);
        }
        if (world->input.keyboard.down(KEY_I)) {
            // shrink the points to the centroid
            for (int i = 0; i < n; i++) B[i] = centroid + (1 - 0.25*dt) * (B[i] - centroid);
        }
        if (world->input.keyboard.down(KEY_O)) {
            for (int i = 0; i < n; i++) B[i] += vec2::random(-0.05, 0.05) * dt;
        }
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
        for (int i = 0; i < n; i++) Ap[i] = transform(A[i]);
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
