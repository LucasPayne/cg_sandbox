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

struct TrianglePatch : public IBehaviour {
    vec3 points[6];
    SurfaceGeometry geom;
    bool active;
    bool subdiv_central;

    vec3 point(int i, int j, int k) {
        assert(i + j + k == 2);
        if (i == 2) return points[0];
        if (j == 2) return points[1];
        if (k == 2) return points[2];
        if (k == 0) return points[3];
        if (i == 0) return points[4];
        if (j == 0) return points[5];
        assert(0);
    }
    // cycle = 0,1,2
    // This version cycles the indices i,j,k so that it is easy to do something symmetrically for each vertex of the triangle.
    vec3 point(int i, int j, int k, int cycle) {
        switch (cycle) {
            case 0: return point(i,j,k);
            case 1: return point(j,k,i);
            case 2: return point(k,i,j);
        }
        assert(0);
    }

    TrianglePatch() {}
    TrianglePatch(std::vector<vec3> &_points, bool _subdiv_central = true) : active{true}, subdiv_central{_subdiv_central} {
        assert(_points.size() == 6);
        Vertex vertices[6];
        for (int i = 0; i < 6; i++) {
            points[i] = _points[i];
            vertices[i] = geom.add_vertex(_points[i]);
        }
        geom.add_triangle(vertices[0], vertices[3], vertices[5]);
        geom.add_triangle(vertices[1], vertices[4], vertices[3]);
        geom.add_triangle(vertices[2], vertices[5], vertices[4]);
        geom.add_triangle(vertices[3], vertices[4], vertices[5]);
    }

    void update() {
        if (active) world->graphics.paint.wireframe(geom, mat4x4::identity(), 0.001);
    }

    void keyboard_handler(KeyboardEvent e) {
        if (active && e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) subdivide();
        }
    }

    void subdivide() {
        if (subdiv_central) {
            for (int cyc = 0; cyc <= 2; cyc++) {
                std::vector<vec3> ps = {
                    point(2,0,0,cyc),
                    0.5*(point(1,1,0,cyc) + 0.5*(point(2,0,0,cyc) + point(0,2,0,cyc))),
                    0.5*(point(1,0,1,cyc) + 0.5*(point(2,0,0,cyc) + point(0,0,2,cyc))),
                    0.5*(point(2,0,0,cyc) + point(1,1,0,cyc)),
                    0.25*(point(2,0,0,cyc) + point(1,1,0,cyc) + point(1,0,1,cyc) + point(0,1,1,cyc)),
                    0.5*(point(2,0,0,cyc) + point(1,0,1,cyc))
                };
                world->add<TrianglePatch>(entity, ps);
            }
            std::vector<vec3> ps;
	    for (int cyc = 0; cyc <= 2; cyc++)
                ps.push_back(0.5*(point(1,1,0,cyc) + 0.5*(point(2,0,0,cyc) + point(0,2,0,cyc))));
	    for (int cyc = 0; cyc <= 2; cyc++) 
	        ps.push_back(0.25*(point(2,0,0,cyc) + point(1,1,0,cyc) + point(1,0,1,cyc) + point(0,1,1,cyc)));
            world->add<TrianglePatch>(entity, ps);
        } else {
            std::vector<vec3> ps = {
	        point(2,0,0),
	        0.5*(point(1,1,0) + 0.5*(point(2,0,0) + point(0,2,0))),
                0.5*(point(1,0,1) + 0.5*(point(2,0,0) + point(0,0,2))),
                0.5*(point(2,0,0) + point(1,1,0)),
                0.25*(point(2,0,0) + point(1,1,0) + point(1,0,1) + point(0,1,1)),
                0.5*(point(2,0,0) + point(1,0,1))
            };
            world->add<TrianglePatch>(entity, ps);

            ps = {
                0.25*point(0,2,0) + 0.5*point(1,1,0) + 0.25*point(2,0,0),
            
                point(0,0,2),

                0.25*point(0,0,2) + 0.5*point(1,0,1) + 0.25*point(2,0,0),

                0.5*point(0,1,1) + 0.5*point(1,0,1),

                0.5*point(0,0,2) + 0.5*point(1,0,1),

                0.25*(point(0,1,1) + point(1,0,1) + point(1,1,0) + point(2,0,0)),
            };
            world->add<TrianglePatch>(entity, ps);

            ps = {
                0.25*point(0,2,0) + 0.5*point(1,1,0) + 0.25*point(2,0,0),
                point(0,2,0),
                point(0,0,2),
                0.5*(point(0,2,0) + point(1,1,0)),
                point(0,1,1),
                0.5*(point(0,1,1) + point(1,0,1)),
            };
            world->add<TrianglePatch>(entity, ps);
        }

        active = false;
    }
};



struct SubdivisionCurve : public IBehaviour {
    std::vector<std::vector<vec3>> components;

    SubdivisionCurve() {}
    SubdivisionCurve(std::vector<vec3> _points) {
        components.push_back(_points);
    }

    void update() {
        static vec4 colors[4] = {vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1), vec4(0,0,0,1)};

        int c = 0;
        for (auto points : components) {
            for (int i = 0; i < points.size()-1; i++) {
                world->graphics.paint.line(points[i], points[i+1], 10, colors[c%4]);
            }
            c += 1;
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) {
                subdivide();
            }
        }
    }

    void subdivide() {
        std::vector<std::vector<vec3>> new_components;
        for (auto points : components) {
            for (int segment = 0; segment <= 1; segment++) {
                auto point = [&](int index) {
                    if (segment == 0) return points[index];
                    return points[5-1-index];
                };
                auto comp = std::vector<vec3>();
                comp.push_back(point(0));
                comp.push_back(0.5*point(0) + 0.5*point(1));
                comp.push_back(0.25*point(0) + 0.5*point(1) + 0.25*point(2));
                comp.push_back((1.f/8)*point(0) + (3.f/8)*point(1) + (3.f/8)*point(2) + (1.f/8)*point(3));
                comp.push_back(1.f/16 * point(0) + 4.f/16 * point(1) + 6.f/16 * point(2) + 4.f/16 * point(3) + 1.f/16 * point(4));
                new_components.push_back(comp);
            }
        }
        components = new_components;
    }
};



int factorial(int n)
{
    if (n <= 1) return 1;
    int f = n;
    for (int i = 1; i < n-1; i++) {
        f *= n-i;
    }
    return f;
}
int binomial_coefficient(int n, int k)
{
    if (k == 0) {
        return 1;
    }
    int c = n;
    for (int i = 1; i < k; i++) {
        c *= n-i;
    }
    return c / factorial(k);
}


struct SplineCurve : public IBehaviour {

    std::vector<vec3> points;

    SplineCurve() {}
    SplineCurve(std::vector<vec3> _points) {
        points = _points;
        show_de_boor = true;
        show_bezier = true;
    }

    bool show_de_boor;
    bool show_bezier;

    void render_bezier_curve(int degree, vec3 *ps, float width, vec4 color, int tess=10) {
        float w = 1.f / tess;
        std::vector<vec3> chain(tess+1);
        for (int i = 0; i <= tess; i++) {
            float t = i*w;
            vec3 p = vec3::zero();
            for (int j = 0; j <= degree; j++) {
                float coeff = 1;
                for (int k = 0; k < j; k++) {
                    coeff *= 1-t;
                }
                for (int k = 0; k < degree-j; k++) {
                    coeff *= t;
                }
                coeff *= binomial_coefficient(degree, j);
                p += coeff * ps[j];
            }
            chain[i] = p;
        }
        world->graphics.paint.chain(chain, width, color);
    }

    void update() {
        static vec4 colors[4] = {vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1)};
        if (show_de_boor) {
            for (int i = 0; i <= points.size()-2; i++) {
	        world->graphics.paint.line(points[i], points[i+1], 3, vec4(0,0,0,1));
            }
        }

        #define DEBOOR_WIDTH 5
        for (int i = 0; i <= points.size()-DEBOOR_WIDTH; i++) {
            vec3 deboor[DEBOOR_WIDTH];
            for (int j = 0; j < DEBOOR_WIDTH; j++) deboor[j] = points[i+j];

            // ------------------------
            // 1/6,   2/3,   1/6,   0
            // 0,     2/3,   1/3,   0
            // 0,     1/3,   2/3,   0
            // 0,     1/6,   2/3,   1/6
            // ------------------------


            // 0,      1/24,    11/24,   11/24,   1/24
            // 0,      1/12,    7/12,    1/3,     0
            // 0,      1/6,     2/3,     1/6,     0
            // 0,      1/3,     7/12,    1/12,    0
            // 1/24,   11/24,   11/24,   1/24,    0


            float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
                // 0.5, 0.5, 0,
                // 0, 1, 0,
                // 0, 0.5, 0.5

                // 1.f/6,   2.f/3,   1.f/6,   0,
                // 0,       2.f/3,   1.f/3,   0,
                // 0,       1.f/3,   2.f/3,   0,
                // 0,       1.f/6,   2.f/3,   1.f/6,

                0,      1.f/24,    11.f/24,   11.f/24,   1.f/24,
                0,      1.f/12,    7.f/12,    1.f/3,     0,
                0,      1.f/6,     2.f/3,     1.f/6,     0,
                0,      1.f/3,     7.f/12,    1.f/12,    0,
                1.f/24,   11.f/24,   11.f/24,   1.f/24,    0,
            };
            vec3 bezier[DEBOOR_WIDTH];
            for (int j = 0; j < DEBOOR_WIDTH; j++) bezier[j] = vec3::zero();
            
            for (int b = 0; b < DEBOOR_WIDTH; b++) {
                for (int bb = 0; bb <= DEBOOR_WIDTH; bb++) {
                    bezier[b] += weights[DEBOOR_WIDTH*b + bb] * deboor[bb];
                }
            }
            if (show_bezier) {
                for (int j = 0; j < DEBOOR_WIDTH-1; j++) {
                    world->graphics.paint.line(bezier[j], bezier[j+1], 1.5, colors[i%4]);
                }
            }
            render_bezier_curve(DEBOOR_WIDTH-1, bezier, 5, colors[i%4]);
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) show_de_boor = !show_de_boor;
            if (e.key.code == KEY_Y) show_bezier = !show_bezier;
        }
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
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    if (0) {
        // Triangle subdiv testing
        Entity e = world.entities.add();
        vec3 a = vec3(2,0,0);
        vec3 b = vec3(0,2,0);
        vec3 c = vec3(0,0,2);
        vec3 ab = 0.5*(a + b) + vec3::random(-2,2);
        vec3 bc = 0.5*(b + c) + vec3::random(-2,2);
        vec3 ca = 0.5*(c + a) + vec3::random(-2,2);
        // vec3 a = vec3(-2,0,0);
        // vec3 b = vec3(2,0,0);
        // vec3 c = vec3(0,2,0);
        // vec3 ab = 0.5*(a + b);
        // vec3 bc = 0.5*(b + c);
        // vec3 ca = 0.5*(c + a);
        std::vector<vec3> points = {
            a, b, c, ab, bc, ca
        };
        world.add<TrianglePatch>(e, points, false);
    }

    if (0) {
        // Curve subdiv testing
        Entity e = world.entities.add();
        auto points = std::vector<vec3>(5);
        for (int i = 0; i < points.size(); i++) {
            points[i] = vec3::random(-1,1);
        }
        world.add<SubdivisionCurve>(e, points);
    }

    
    if (1) {
        // Spline curve testing
        Entity e = world.entities.add();
        auto points = std::vector<vec3>(20);
        points[0] = vec3::zero();
        for (int i = 1; i < points.size(); i++) {
            points[i] = points[i-1] + vec3::random(-1,1);
        }
        world.add<SplineCurve>(e, points);
    }
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

    context.enable_raw_mouse();

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
