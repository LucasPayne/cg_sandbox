#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/object_viewer_cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"

SurfaceGeometry *model_geom;
SurfaceGeometry *test_geom;


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
    {
        auto mesh = SurfaceMesh();
        auto v1 = mesh.add_vertex();
        auto v2 = mesh.add_vertex();
        auto v3 = mesh.add_vertex();
        auto v4 = mesh.add_vertex();
        mesh.add_triangle(v1, v3, v4);
        mesh.add_triangle(v1, v4, v2);
        getchar();
    }
    {
        auto mesh = SurfaceMesh();
        Vertex vertices[9];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                vertices[3*i + j] = mesh.add_vertex();
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                printf("Square %d %d\n", i, j);
                int a = 3*i + j;
                int b = 3*(i+1) + j;
                int c = 3*i + j+1;
                int d = 3*(i+1) + j+1;
                printf("Triangle %d %d %d\n", a, b, d);
                mesh.add_triangle(vertices[a], vertices[b], vertices[d]);
                printf("Triangle %d %d %d\n", a, d, c);
                mesh.add_triangle(vertices[a], vertices[d], vertices[c]);
            }
        }
	getchar();
    }



    // mesh_processing testing.
    test_geom = new SurfaceGeometry();

    auto v1 = test_geom->add_vertex(0,0,0);
    auto v2 = test_geom->add_vertex(1,0,0);
    auto v3 = test_geom->add_vertex(0,1,0);
    auto triangle = test_geom->add_triangle(v1, v2, v3);

    int n = 5;
    std::vector<Vertex> vertices;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vertices.push_back(test_geom->add_vertex(1+0.1*i, 1+0.1*j, 0));
        }
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            test_geom->add_triangle(vertices[n*i + j], vertices[n*(i+1) +j], vertices[n*i + j+1]);
            test_geom->add_triangle(vertices[n*i + j+1], vertices[n*(i+1) + j], vertices[n*(i+1) + j+1]);
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
    test_geom->write_OFF(file);
    file.close();
    Entity obj = create_mesh_object(world, "tmp/test.off", "resources/model_test/model_test.mat");
    obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    obj.get<Transform>()->position.z() -= 0.05;
    }

    {
    // Load the dragon model, create a SurfaceGeometry from it, write the surface geometry out to an OFF file,
    // then load that OFF file and create an object from it.
    // auto model = MLModel::load("resources/models/dragon.off");
    auto model = MLModel::load("resources/models/large/bunny_head.stl");
    model_geom = new SurfaceGeometry(); //global
    model_geom->add_model(model);

    std::ofstream file("tmp/dragon_test.off");
    model_geom->write_OFF(file);
    file.close();
    // Entity obj = create_mesh_object(world, "tmp/dragon_test.off", "resources/model_test/model_test.mat");
    // obj.get<Drawable>()->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
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

    world.graphics.paint.wireframe(*model_geom, mat4x4::identity(), 0.001);
    world.graphics.paint.wireframe(*test_geom, mat4x4::identity(), 0.001);
    
    // VertexAttachment<vec3> neighbour_averages(model_geom->mesh);
    // for (auto vertex : model_geom->vertices()) {
    //     neighbour_averages[vertex] = vec3(0,0,0);
    // }
    // for (auto vertex : model_geom->vertices()) {
    //     auto start = vertex.halfedge();
    //     auto he = start;
    //     int n = 0;
    //     while (!he.null()) {
    //         auto ring_vertex = he.tip();
    //         neighbour_averages[vertex] += model_geom->vertex_positions[ring_vertex];
    //         he = he.flip().next();
    //         n ++;
    //         if (he == start) break;
    //     }
    //     if (n > 0) neighbour_averages[vertex] *= 1.0 / n;
    // }
    // for (auto vertex : model_geom->vertices()) {
    //     model_geom->vertex_positions[vertex] = vec3::lerp(model_geom->vertex_positions[vertex], neighbour_averages[vertex], dt);
    // }
    // for (auto vertex : model_geom->vertices()) {
    //     model_geom->vertex_positions[vertex] += 0.1 * dt * vec3(frand()-0.5,frand()-0.5,frand()-0.5);
    // }


    // static Halfedge test_he;
    // static bool set_test_v = false;
    // if (!set_test_v) {
    //     test_he = (*model_geom->vertices().begin()).halfedge();
    //     set_test_v = true;
    // }
    // world.graphics.paint.sphere(model_geom->vertex_positions[test_he.tip()], 0.007, vec4(1,0,0,1));
    // printf("%u to ", test_he.index());
    // test_he = test_he.flip().next();
    // printf("%u\n", test_he.index());
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
