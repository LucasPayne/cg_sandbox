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
    context.add_callbacks(&world);
    context.add_callbacks(&world.input);

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    context.enable_raw_mouse();

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
