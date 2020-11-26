#include <time.h>
#include <assert.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/cameraman.cpp"
#include "world/graphics/image.h"

void fill_sinogram(Image<float> &image, Image<float> &sinogram);
Image<float> create_sinogram(Image<float> &image, int num_parallel_rays, int num_directions);


struct LinePoint {
    int x;
    int y;
    float weight;
    LinePoint(int _x, int _y, float _weight) :
        x{_x}, y{_y}, weight{_weight}
    {}
};


void trace_line(Image<float> &image, float theta, float s, std::function<void(LinePoint)> function)
{
    trace_line(image, cos(theta), sin(theta), function);
}
void trace_line(Image<float> &image,
                float cos_theta, float sin_theta,
                float s,
                std::function<void(LinePoint)> function)
{
    int n = image.width();
    vec2 p(s * cos_theta, s * sin_theta);

    float height = sqrt(fabs(1 - s*s));
    vec2 from = 0.5*(p + height*vec2(-sin_theta, cos_theta) + vec2(1,1));
    vec2 to = 0.5*(p - height*vec2(-sin_theta, cos_theta) + vec2(1,1));

    int a_x = floor(from.x() * n);
    int a_y = floor(from.y() * n);
    int b_x = floor(to.x() * n);
    int b_y = floor(to.y() * n);

    // Special case: The whole line segment is in one pixel.
    if (a_x == b_x && a_y == b_y) {
        float weight = 2*height;
        if (isnan(weight)) {
            fprintf(stderr, "trace_line: NaN weight in one pixel\n");
            exit(EXIT_FAILURE);
        }
        function(LinePoint(a_x, a_y, weight));
        return;
    }

    // Bresenham's line algorithm.
    int x_dir = to.x() > from.x() ? 1 : -1;
    int y_dir = to.y() > from.y() ? 1 : -1;
    float dx = fabs(1.f/(n*(to.x() - from.x())));
    float dy = fabs(1.f/(n*(to.y() - from.y())));
    float grid_aligned_when_at_least = 10000;
    float next_x;
    if (dx >= grid_aligned_when_at_least) {
        next_x = INFINITY;
    } else {
        next_x = x_dir > 0 ? (1 - (n*from.x() - floor(n*from.x())))*dx
                           : (n*from.x() - floor(n*from.x()))*dx;
    }
    float next_y;
    if (dy >= grid_aligned_when_at_least) {
        next_y = INFINITY;
    } else {
        next_y = y_dir > 0 ? (1 - (n*from.y() - floor(n*from.y())))*dy
                           : (n*from.y() - floor(n*from.y()))*dy;
    }
    int cell_x = a_x;
    int cell_y = a_y;
    float t = 0;
    float integral = 0.f;
    while (x_dir*cell_x <= x_dir*b_x && y_dir*cell_y <= y_dir*b_y && cell_x >= 0 && cell_x < n && cell_y >= 0 && cell_y < n) {
        float next_t;
        if (next_x < next_y) {
            cell_x += x_dir;
            next_t = next_x;
            next_x += dx;
        } else {
            cell_y += y_dir;
            next_t = next_y;
            next_y += dy;
        }
        float weight = (next_t - t) * height;
        if (isnan(weight)) {
            fprintf(stderr, "trace_line: NaN weight\n");
            printf("height: %.6f\n", height);
            printf("dx: %.6f\n", dx);
            printf("dy: %.6f\n", dy);
            printf("next_x: %.6f\n", next_x);
            printf("next_y: %.6f\n", next_y);
            printf("t: %.6f\n", t);
            printf("next_t: %.6f\n", next_t);
            exit(EXIT_FAILURE);
        }
        function(LinePoint(cell_x, cell_y, weight));
        t = next_t;
    }
}



float line_integral(Image<float> &image, float cos_theta, float sin_theta, float s)
{
    float integral = 0.f;
    trace_line(image, cos_theta, sin_theta, s, [&](LinePoint p) {
        integral += p.weight * image(p.y, p.x);
    });
    return integral;
}

void fill_sinogram(Image<float> &image, Image<float> &sinogram)
{
    int num_parallel_rays = sinogram.height();
    int num_directions = sinogram.width();
    float inv_num_directions = 1.0 / num_directions;
    float inv_num_parallel_rays_minus_one = 1.0 / (num_parallel_rays - 1);
    float w = (num_parallel_rays - 2.f) / num_parallel_rays; //weights the computed s so that no rays are tangent to the circle.
    for (int i = 0; i < num_directions; i++) {
        float theta = M_PI * i * inv_num_directions;
        float cos_theta = cos(theta);
        float sin_theta = sin(theta);
        for (int j = 0; j < num_parallel_rays; j++) {
            float s = (-1 + 2*j*inv_num_parallel_rays_minus_one)*w;
            float integral = line_integral(image, cos_theta, sin_theta, s);
            sinogram(j, i) = integral;
        }
    }
}
Image<float> create_sinogram(Image<float> &image, int num_parallel_rays, int num_directions)
{
    assert(image.width() == image.height());
    Image<float> sinogram(num_parallel_rays, num_directions);
    fill_sinogram(image, sinogram);
    return sinogram;
}



struct Reconstructor {
    int num_parallel_rays;
    int num_directions;
    Image<float> sinogram;
    int n;
    Image<float> reconstruction;
    Reconstructor(Image<float> _sinogram, int _n) :
        num_parallel_rays{_sinogram.height()},
        num_directions{_sinogram.width()},
        sinogram{_sinogram},
        n{_n},
        reconstruction(_n, _n)
    {
        reconstruction.clear(0);
        cyclic_counter_s = 0;
        cyclic_counter_theta = 0;
        inv_num_directions = 1.f / num_directions;
        inv_num_parallel_rays_minus_one = 1.f / (num_parallel_rays - 1);

        theta = 0;
        cos_theta = 1;
        sin_theta = 0;

        w = (num_parallel_rays - 2.f) / num_parallel_rays; //weights the computed s so that no rays are tangent to the circle.
    }
    Reconstructor() {}

    int cyclic_counter_s;
    int cyclic_counter_theta;
    float inv_num_directions;
    float inv_num_parallel_rays_minus_one;
    float theta;
    float cos_theta;
    float sin_theta;
    float w;

    void iterate();
};

void Reconstructor::iterate()
{
    // cyclic_counter_s = rand() % num_parallel_rays;
    // cyclic_counter_theta = rand() % num_directions;
    // theta = M_PI*cyclic_counter_theta*inv_num_directions_minus_one;
    // cos_theta = cos(theta);
    // sin_theta = sin(theta);

    float val = sinogram(cyclic_counter_s, cyclic_counter_theta);
    float s = (-1 + 2*cyclic_counter_s*inv_num_parallel_rays_minus_one)*w;
    // Compute the approximate line integral of the current guess through this line, corresponding to the point in the sinogram.
    float integral = line_integral(reconstruction, cos_theta, sin_theta, s);
    float residual = val - integral;

    float square_row_length = 0.f;
    float total_weight = 0.f;
    trace_line(reconstruction, cos_theta, sin_theta, s, [&](LinePoint p) {
        square_row_length += p.weight * p.weight;
        total_weight += p.weight;
    });
    // printf("total_weight: %.8f\n", total_weight);
    // printf("square_row_length: %.8f\n", square_row_length);getchar();
    float lambda = 1.f; // relaxation coefficient.
    float weighted_residual = lambda * (residual / square_row_length);
    
    trace_line(reconstruction, cos_theta, sin_theta, s, [&](LinePoint p) {
        reconstruction(p.y, p.x) += weighted_residual * p.weight;
    });

    cyclic_counter_s += 1;
    if (cyclic_counter_s == num_parallel_rays) {
        cyclic_counter_s = 0;
        #if 1
            cyclic_counter_theta = (cyclic_counter_theta+1) % num_directions;
        #else
            cyclic_counter_theta = rand() % num_directions;
        #endif
        theta = M_PI*cyclic_counter_theta*inv_num_directions;
        cos_theta = cos(theta);
        sin_theta = sin(theta);
    }
}






Aspect<Camera> main_camera;


struct Test : public IBehaviour {
    Image<float> image;
    Image<float> sinogram;
    Image<float> reconstruction_sinogram;
    Reconstructor reconstructor;

    int img_size;
    int num_parallel_rays;
    int num_directions;

    void refresh() {
        image.clear(0);
        for (int i = 0; i < 20; i++) draw_circle(image, vec2(0.5+0.3*(frand()-0.5), 0.5+0.3*(frand()-0.5)), 0.1+frand()*0.2, 0.5+0.5*frand());
        fill_sinogram(image, sinogram);
        reconstructor = Reconstructor(sinogram, img_size);
        reconstruction_sinogram = Image<float>(sinogram.width(), sinogram.height());
    }

    Test(int n, int _num_parallel_rays, int _num_directions) :
        image(n, n), sinogram(_num_parallel_rays, _num_directions),
        img_size{n}, num_parallel_rays{_num_parallel_rays}, num_directions{_num_directions}
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
                for (int i = 0; i < 28; i++) reconstructor.iterate();
            }
            if (e.key.code == KEY_I) {
                reconstruction_sinogram = create_sinogram(reconstructor.reconstruction, sinogram.width(), sinogram.height());
            }
        }
    }

    void update() {
        vec4 border_color = vec4(1,1,1,1);
        world->graphics.paint.bordered_depth_sprite(main_camera, image.texture(), vec2(0.1,0.1), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, sinogram.texture(), vec2(0.1,0.5), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, reconstructor.reconstruction.texture(), vec2(0.5,0.1), 0.4,0.4, 3, border_color);
        world->graphics.paint.bordered_depth_sprite(main_camera, reconstruction_sinogram.texture(), vec2(0.5,0.5), 0.4,0.4, 3, border_color);

	    for (int i = 0; i < 10*28; i++) reconstructor.iterate();
	    fill_sinogram(reconstructor.reconstruction, reconstruction_sinogram);
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
    world.add<Test>(test, 512, 256, 256);

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
