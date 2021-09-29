#include "cg_sandbox.h"
#include "mesh_processing/mesh_processing.h"
#include "mesh_processing/extensions/assimp_convert.h"
#include "CameraController.cpp"


struct DrawableMesh : public IBehaviour {
    SurfaceGeometry *geom;
    DrawableMesh()
    {
        // geom = assimp_to_surface_geometry(PATH "bunny_head.stl");
        // geom = assimp_to_surface_geometry(PATH "bunny_head.stl");
        // for (int i = 0; i < 600; i++) {
        //     for (auto face : geom->mesh.faces()) {
        //         geom->mesh.remove_face(face);
        //         break;
        //     }
        // }
        //
        #if 0
        geom = assimp_to_surface_geometry(PATH "bunny_head.stl");
        #else
        geom = assimp_to_surface_geometry(PATH "Tangram-6.stl");
        for (auto v : geom->mesh.vertices()) {
            geom->position[v] *= 3;
            geom->position[v] += vec_t(1, 0, 0);
        }
        #endif
        geom->mesh.lock();

       
        // geom = new SurfaceGeometry();
        // auto v1 = geom->add_vertex(0,0,0);
        // auto v2 = geom->add_vertex(1,0,0);
        // auto v3 = geom->add_vertex(1,1,0);
        // auto v4 = geom->add_vertex(0,1,0);
        // auto t1 = geom->mesh.add_triangle(v1, v2, v3);
        // auto t2 = geom->mesh.add_triangle(v1, v3, v4);
        // geom->mesh.remove_face(t2);
        // geom->mesh.remove_vertex(v4);

        // std::cout << geom->mesh.num_halfedges() << "\n";
        // geom->mesh.lock();
        // std::cout << geom->mesh.num_halfedges() << "\n";
        // geom->mesh.unlock();
        // std::cout << geom->mesh.num_halfedges() << "\n";
        // getchar();
    
        // geom->mesh.remove_face(t2);
        // geom->mesh.remove_vertex(v4);
        
        // geom = Enmesh::grid_geom(10, 10, 0,0, 1,1);

        // for (auto face : geom->mesh.faces()) {
        //     if (frand() > 0.9) {
        //         geom->mesh.remove_face(face);
        //     }
        // }
        // geom->mesh.lock();
    }
    void post_render_update()
    {
        world->graphics.paint.wireframe(*geom, mat4x4::identity(), 0.01);
        // for (auto start : geom->mesh.boundary_loops()) {
        //     auto he = start;
        //     auto loop = std::vector<vec3>();
        //     do {
        //         vec_t pos = geom->position[he.vertex()];
        //         loop.push_back(vec3(pos.x(), pos.y(), pos.z()));
        //     } while ((he = he.next()) != start);
        //     loop.push_back(loop[0]);
        //     world->graphics.paint.chain(loop, 4, vec4(1,0,0,1));
        // }
    }

    void keyboard_handler(KeyboardEvent e)
    {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_P) {
                // Barycentric subdivision.
                auto subdiv = new Subdivision::Triangular(geom->mesh);
                geom = Subdivision::barycentric(*subdiv, *geom);
            }
            if (e.key.code == KEY_O) {
                // Loop subdivision.
                auto subdiv = new Subdivision::Triangular(geom->mesh);
                geom = Subdivision::loop(*subdiv, *geom);
            }
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
    auto cameraman = world.entities.add();
    auto camera = cameraman.add<Camera>(0.1, 300, 0.1, 0.566);
    cameraman.add<Transform>(0,0,2);
    world.add<CameraController>(cameraman);

    auto mesh_entity = world.entities.add();
    world.add<DrawableMesh>(mesh_entity);
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
    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_Q) {
            exit(EXIT_SUCCESS);
        }
    }
}

void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    printf("[main] Creating context...\n");
    IGC::Context context("A world");
    printf("[main] Creating world...\n");
    World world(context);

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
