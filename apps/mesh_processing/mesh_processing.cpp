#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/object_viewer_cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"


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
    {
        Entity obj = create_mesh_object(world, "resources/models/large/buddha.obj", "resources/model_test/model_test.mat");
        obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Entity cameraman = create_object_viewer_cameraman(world, obj);
        cameraman.get<Transform>()->position = vec3(0,0,2);
    }

    // mesh_processing testing.
    auto geom = SurfaceGeometry();

    auto v1 = geom.add_vertex(0,0,0);
    auto v2 = geom.add_vertex(1,0,0);
    auto v3 = geom.add_vertex(0,1,0);
    auto triangle = geom.add_triangle(v1, v2, v3);

    int n = 5;
    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vertices.push_back(geom.add_vertex(1+0.1*i, 1+0.1*j, 0));
        }
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            geom.add_triangle(vertices[n*i + j], vertices[n*(i+1) +j], vertices[n*i + j+1]);
            geom.add_triangle(vertices[n*i + j+1], vertices[n*(i+1) + j], vertices[n*(i+1) + j+1]);
        }
    }

    // geom.printout();

    // for (auto vertex : geom.vertices()) {
    //     // Since the outgoing halfedge is arbitrary, the face circled is arbitrary.
    //     std::cout << "Circling " << geom.vertex_positions[vertex] << "\n";
    //     auto start = vertex.halfedge();
    //     auto he = start;
    //     do {
    //         std::cout << geom.vertex_positions[he.vertex()] << "\n";
    //         he = he.next();
    //     } while (he != start);
    // }


    {
    std::ofstream file("tmp/test.off");
    geom.write_OFF(file);
    file.close();
    Entity obj = create_mesh_object(world, "tmp/test.off", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }

    {
    auto model = MLModel::load("resources/models/dragon.off");
    auto model_geom = SurfaceGeometry();
    model_geom.add_model(model);

    std::ofstream file("tmp/dragon_test.off");
    model_geom.write_OFF(file);
    file.close();
    Entity obj = create_mesh_object(world, "tmp/dragon_test.off", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }


    
}


void App::close()
{
}
void App::loop()
{
    for (int i = 0; i < 40; i++) {
        float y = -0.5 + 1.0/40.0 * i;
        float x = 0.2*cos(0.6*total_time + 6*y);
        float z = 0.2*sin(0.6*total_time + 6*y);
        float r = 0.03;
        world.graphics.paint.sphere(vec3(x,y,z), r, vec4(i%2,0.1 + (i%3)*0.2,(i+1)%2,1));
    }
    for (int i = 0; i < 40; i++) {
        float y = -0.5 + 1.0/40.0 * i;
        float x = 0.2*cos(-0.6*total_time - 6*y + M_PI/2);
        float z = 0.2*sin(-0.6*total_time - 6*y + M_PI/2);
        float r = 0.03;
        world.graphics.paint.sphere(vec3(x,y,z), r, vec4(i%2,0.1 + (i%3)*0.2,(i+1)%2,1));
    }
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
