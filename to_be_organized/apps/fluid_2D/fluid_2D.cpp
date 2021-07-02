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

// Utility class for 2D indexing with () notation.
template <typename T>
class Array2D {
private:
    std::vector<T> _data;
    int m;
    int n;
public:
    Array2D(int _m, int _n) : m{_m}, n{_n}
    {
        _data = std::vector<T>(m * n);
    }
    Array2D() {}
    inline T operator()(int i, int j) const {
        return _data[n*i + j];
    }
    inline T &operator()(int i, int j) {
        return _data[n*i + j];
    }
};

// Staggered array with LEFT and BELOW arrays, for use in a MAC grid.
template <typename T>
class StaggeredArray2D {
private:
    int m;
    int n;
    Array2D<vec2> axes[2];  // m x (n+1) LEFT array
                            // (m+1) x n BELOW array
public:
    StaggeredArray2D(int _m, int _n) : m{_m}, n{_n}
    {
        axes[0] = Array2D<vec2>(m, n+1);
        axes[1] = Array2D<vec2>(m+1, n);
    }
    StaggeredArray2D() {}
    inline T operator()(int axis, int i, int j) const {
        return axes[axis](i, j);
    }
    inline T &operator()(int axis, int i, int j) {
        return axes[axis](i, j);
    }
};



struct FluidDemo : public IBehaviour {
    int m;
    int n;

    vec2 bl;
    vec2 tr;
    vec2 cell_dim;
    vec2 box_dim;

    // MAC (markers-and-cells) grid data.
    /*
        -------   -------
        |     |   |     |
        o left|   |below|
        |     |   |     |
        -------   ---o---
    */
    
    // Ping-pong staggered velocity array.
    int _velocity_swap_flag;
    StaggeredArray2D<vec2> _velocity_swap_buffers[2];
    inline vec2 &velocity(int axis, int i, int j) const {
        return _velocity_swap_buffers[_velocity_swap_flag](axis, i, j);
    }
    inline vec2 &velocity(int axis, int i, int j) {
        return _velocity_swap_buffers[_velocity_swap_flag](axis, i, j);
    }
    inline vec2 &tmp_velocity(int axis, int i, int j) const {
        return _velocity_swap_buffers[(_velocity_swap_flag+1)%2](axis, i, j);
    }
    inline vec2 &tmp_velocity(int axis, int i, int j) {
        return _velocity_swap_buffers[(_velocity_swap_flag+1)%2](axis, i, j);
    }
    inline void swap_velocity_buffers() { _velocity_swap_flag = (_velocity_swap_flag + 1) % 2; }
    //todo: Nicer swap buffer data structure.


    FluidDemo(int _m, int _n) : m{_m}, n{_n},
    {
        bl = vec2(0.2, 0.2);
        tr = vec2(0.8, 0.8);
        cell_dim = vec2(1.f/n, 1.f/m) * (tr - bl);
        box_dim = tr - bl;

        _velocity_swap_flag = 0;
        _velocity_swap_buffers[0](_m, _n);
        _velocity_swap_buffers[1](_m, _n);
    }
    // Convert indices into corresponding physical positions.
    vec2 corner_pos(int i, int j) {
        return vec2(bl.x() + (tr.x()-bl.x())*j/n,
                    bl.y() + (tr.y()-bl.y())*i/m);
    }
    vec2 center_pos(int i, int j) {
        return corner_pos(i, j) + 0.5*cell_dim;
    }
    vec2 left_face_pos(int i, int j) {
        return corner_pos(i, j) + vec2(0, 0.5*cell_dim.y());
    }
    vec2 below_face_pos(int i, int j) {
        return corner_pos(i, j) + vec2(0.5*cell_dim.x(), 0);
    }
    vec2 face_pos(int axis, int i, int j) { // for iteration
        return axis == 0 ? left_face_pos(i, j) : below_face_pos(i, j);
    }

    
    // Set the velocity field to samples of a given function.
    void initialize_velocity_field(std::function<vec2(vec2)> F)
    {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i < m) {
                    velocity(0, i, j) = F(left_face_pos(i, j));
                }
                if (j < n) {
                    velocity(1, i, j) = F(below_face_pos(i, j));
                }
            }
        }
    }

    // Simulation
    //------------------------------------------------------------
    // Simulation scratch data
    StaggeredArray2D<vec2> advected_velocity;


    struct CellPosition {
        int i;
        int j;
        vec2 internal;
    };
    // Convert a physical position into (i,j, vec2(x, y)) where x and y are the internal cell-coordinates in [0,1]^2.
    CellPosition point_to_cell(vec2 p) const {
        vec2 resized = (p - bl) * box_dim;
        int i = floor(resized.x());
        int j = floor(resized.y());
        vec2 pos_in_cell = resized - vec2(i, j);
        return {i, j, pos_in_cell};
    }


    void step(float timestep);
    void advect(float timestep);
    void apply_body_forces(float timestep);
    void project(float timestep);
    vec2 interpolate_velocity(vec2 from, vec2 p);

    void update();
    
    void post_render_update() {
        auto &paint = world->graphics.paint;
        vec4 grid_color = vec4(1,0,0,1);
        for (int i = 0; i <= m; i++) {
            std::vector<vec2> points = { corner_pos(i, 0), corner_pos(i, n) };
	    paint.chain_2D(points, 0.5, grid_color);
        }
        for (int i = 0; i <= n; i++) {
            std::vector<vec2> points = { corner_pos(0, i), corner_pos(m, i) };
	    paint.chain_2D(points, 0.5, grid_color);
        }

        // std::vector<vec2> positions;
        // for (int i = 0; i < m; i++) {
        //     for (int j = 0; j < n; j++) {
        //         positions.push_back(below_face_pos(i, j));
        //         positions.push_back(left_face_pos(i, j));
        //     }
        // }
        // paint.circles(main_camera, positions, 0.001, vec4(1,0,0,1));

        for (int axis = 0; axis <= 1; axis ++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    vec2 a = face_pos(axis, i, j);
                    vec2 b = a + velocity(axis, i, j);
                    std::vector<vec2> line = {a, b};
	            paint.chain_2D(line, 0.5, vec4(0,0,0,1));
                }
            }
        }
    }
};


// Interpolation for semi-Lagrangian advection.
vec2 FluidDemo::interpolate_velocity(vec2 from, vec2 p)
{
    auto p_cell = point_to_cell(p);

    if (p_cell.i < 0 || p_cell.j < 0 || p_cell.i > m-1 || p_cell.j > n-1) {
        // Outside the solid box.
        // Instead assume that the fluid came from the closest point on the wall on the trajectory.

        float T = INFINITY;
        vec2 intersection;
        for (int axis = 0; axis <= 1; axis++) {
            bool did_intersect = false;
            vec2 corner = from[axis] > p[axis] ? bl : tr;
	    float t = (corner[axis] - from[axis])/(p[axis] - from[axis]);
	    if (0 <= t && t <= 1) {
                did_intersect = true;
                if (t < T) {
                    intersection = from + t*(p - from);
                    T = t;
                }
            }
        }
        if (T < INFINITY) {
            p = intersection; // Update p
            p_cell = point_to_cell(intersection);
        }
    }

    return vec2(0,0);
}


void FluidDemo::step(float timestep)
{
    advect(timestep);
    apply_body_forces(timestep);
    project(timestep);
}
void FluidDemo::advect(float timestep)
{
    /*
        Du/Dt = 0,
        du/dt = -u.grad(u)
    */

    // Advect the velocity into a separate buffer.
    for (int axis = 0; axis <= 1; axis++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vec2 p = face_pos(axis, i, j);
                // RK2 as in FSfCG p29
                vec2 pmid = p - 0.5*timestep * velocity(axis, i, j);
                vec2 pp = p - timestep * interpolate_velocity(p, pmid);
                advected_velocity(axis, i, j) = interpolate_velocity(p, pp);

                // std::vector<vec2> drawps = {p, pp};
	        // world->graphics.paint.chain_2D(drawps, 10, vec4(0,1,0,1));
            }
        }
    }
    // Update the velocity to this advected velocity.
    
}
void FluidDemo::apply_body_forces(float timestep)
{

}
void FluidDemo::project(float timestep)
{

}

void FluidDemo::update()
{
    step(dt);
}


App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    Entity fluid_e = world.entities.add();
    auto fluid = world.add<FluidDemo>(fluid_e, 20, 20);
    fluid->initialize_velocity_field([](vec2 v)->vec2 {
        return vec2(0.01 * v.x()*v.x(), 0.01);
    });
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
