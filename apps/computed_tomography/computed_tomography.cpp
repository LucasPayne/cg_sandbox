#include <time.h>
#include <assert.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/cameraman.cpp"
#include "world/graphics/image.h"

#include "computed_tomography.h"
#include "ARTReconstructor.cpp"
#include "SARTReconstructor.cpp"
#include "sinogram.cpp"
#include "ray_tracing.cpp"


Aspect<Camera> main_camera;


struct ReconstructionTest : public IBehaviour {
    Image<float> image;
    Image<float> sinogram;
    Image<float> reconstruction_sinogram;
    Reconstructor *reconstructor;

    int img_size;
    int num_parallel_rays;
    int num_directions;

    int reconstructor_type;

    void refresh() {
        image.clear(0);
        for (int i = 0; i < 20; i++) draw_circle(image, vec2(0.5+0.3*(frand()-0.5), 0.5+0.3*(frand()-0.5)), 0.1+frand()*0.2, 0.5+0.5*frand());
        fill_sinogram(image, sinogram);

        if (reconstructor != nullptr) delete reconstructor;
        if (reconstructor_type == CT_ART) {
            reconstructor = new ARTReconstructor(sinogram, img_size);
        } else if (reconstructor_type == CT_SART) {
            reconstructor = new SARTReconstructor(sinogram, img_size);
        }
        reconstruction_sinogram = Image<float>(sinogram.width(), sinogram.height());
    }

    ReconstructionTest(int n, int _num_parallel_rays, int _num_directions, int _reconstructor_type) :
        image(n, n), sinogram(_num_parallel_rays, _num_directions), reconstructor{nullptr},
        img_size{n}, num_parallel_rays{_num_parallel_rays}, num_directions{_num_directions},
        reconstructor_type{_reconstructor_type}
    {
        refresh();
    }

    void draw_line(vec2 from, vec2 to) {
        int n = image.width();
        int a_x = floor(from.x() * n);
        int a_y = floor(from.y() * n);
        int b_x = floor(to.x() * n);
        int b_y = floor(to.y() * n);
        // Bresenham's line algorithm.
        int x_dir = to.x() > from.x() ? 1 : -1;
        int y_dir = to.y() > from.y() ? 1 : -1;
        float dx = fabs(1.f/(n*(to.x() - from.x())));
        float dy = fabs(1.f/(n*(to.y() - from.y())));
        float next_x = x_dir > 0 ? (1 - (n*from.x() - floor(n*from.x())))*dx
                                 : (n*from.x() - floor(n*from.x()))*dx;
        float next_y = y_dir > 0 ? (1 - (n*from.y() - floor(n*from.y())))*dy
                                 : (n*from.y() - floor(n*from.y()))*dy;
        int cell_x = a_x;
        int cell_y = a_y;
        while (x_dir*cell_x <= x_dir*b_x && y_dir*cell_y <= y_dir*b_y && cell_x >= 0 && cell_x < n && cell_y >= 0 && cell_y < n) {
            if (next_x < next_y) {
                cell_x += x_dir;
                next_x += dx;
            } else {
                cell_y += y_dir;
                next_y += dy;
            }
            image(cell_y, cell_x) = 0.8;
        }
    }

    void draw_circle(Image<float> &img, vec2 center, float radius, float intensity) {
        center *= img.width();
        radius *= img.width();
        for (int i = 0; i < img.width(); i++) {
            for (int j = 0; j < img.width(); j++) {
                if ((i - center.y())*(i - center.y()) + (j - center.x())*(j - center.x()) <= radius*radius) {
                    img(i, j) = intensity;
                }
            }
        }
    }


    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_O) {
                refresh();
            }
            if (e.key.code == KEY_P) {
                reconstructor->iterate();
            }
            if (e.key.code == KEY_I) {
                reconstruction_sinogram = create_sinogram(reconstructor->reconstruction, sinogram.width(), sinogram.height());
            }
            if (e.key.code == KEY_M) {
                reconstructor_type = (reconstructor_type + 1) % NUM_RECONSTRUCTOR_TYPES;
                refresh();
            }
        }
    }

    void update() {
        vec4 border_color = vec4(1,1,1,1);
        world->graphics.paint.bordered_depth_sprite(main_camera, image.texture(), vec2(0.1,0.1), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, sinogram.texture(), vec2(0.1,0.5), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, reconstructor->reconstruction.texture(), vec2(0.5,0.1), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, reconstruction_sinogram.texture(), vec2(0.5,0.5), 0.4,0.4, 3, border_color);

	    reconstructor->iterate();
	    fill_sinogram(reconstructor->reconstruction, reconstruction_sinogram);
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

    Entity test = world.entities.add();
    world.add<ReconstructionTest>(test, 128, 128, 128, CT_ART);

    main_camera->background_color = vec4(0,0,0,1);
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
    IGC::Context context("computed_tomography");
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
