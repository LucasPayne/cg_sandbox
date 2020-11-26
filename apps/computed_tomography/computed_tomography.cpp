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
    float grid_aligned_when_at_least = 10000; // Used to detect when a line is well-approximated as vertical or horizontal.
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



enum ReconstructorTypes {
    CT_ART,
    CT_SART,
    NUM_RECONSTRUCTOR_TYPES
};
struct Reconstructor
{
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
    }
    Reconstructor() {}

    virtual void iterate() = 0;
};




// ART: Algebraic Reconstruction Technique
struct ARTReconstructor : public Reconstructor
{
    int cyclic_counter_s;
    int cyclic_counter_theta;
    float inv_num_directions;
    float inv_num_parallel_rays_minus_one;
    float theta;
    float cos_theta;
    float sin_theta;
    float w;

    ARTReconstructor(Image<float> _sinogram, int _n) : Reconstructor(_sinogram, _n) {
        cyclic_counter_s = 0;
        cyclic_counter_theta = 0;
        inv_num_directions = 1.f / num_directions;
        inv_num_parallel_rays_minus_one = 1.f / (num_parallel_rays - 1);

        theta = 0;
        cos_theta = 1;
        sin_theta = 0;

        w = (num_parallel_rays - 2.f) / num_parallel_rays; //weights the computed s so that no rays are tangent to the circle.
    }
    ARTReconstructor() {}

    void iterate();
};


void ARTReconstructor::iterate()
{
    for (int i = 0; i < num_parallel_rays; i++) {
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
}


// SART: Simultaneous Algebraic Reconstruction Technique
struct SARTReconstructor : public Reconstructor
{
    Image<float> weighted_residual;
    Image<float> reconstruction_sinogram;

    Image<float> reconstruction_total_weights;

    SARTReconstructor(Image<float> _sinogram, int _n) :
        Reconstructor(_sinogram, _n),
        weighted_residual(_sinogram.width(), _sinogram.height()),
        reconstruction_sinogram(_sinogram.width(), _sinogram.height()),
        reconstruction_total_weights(_n, _n)
    {
    }
    SARTReconstructor() {}

    void iterate();
};

void SARTReconstructor::iterate()
{
    reconstruction_total_weights.clear(0);
    fill_sinogram(reconstruction, reconstruction_sinogram);
    for (int i = 0; i < weighted_residual.height(); i++) {
        float s = (-1 + 2*i*(1.f / (num_parallel_rays - 1)))*((num_parallel_rays - 2.f)/num_parallel_rays);
        for (int j = 0; j < weighted_residual.width(); j++) {
            float theta = M_PI * j / (1.f * num_directions);
            float cos_theta = cos(theta);
            float sin_theta = sin(theta);
            float total_weight = 0.f;
            trace_line(reconstruction, cos_theta, sin_theta, s, [&](LinePoint p) {
                total_weight += p.weight;
                // For each pixel in the reconstruction image, compute the sum of the weights of the lines through that pixel.
                reconstruction_total_weights(p.y, p.x) += p.weight;
            });
            weighted_residual(i, j) = total_weight * (sinogram(i, j) - reconstruction_sinogram(i, j));
        }
    }

    const float lambda = 1.f; // relaxation coefficient
    // // Update the reconstruction image.
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         reconstruction(i, j) += lambda * reconstruction_total_weights
    //     }
    // }

    // Update the reconstruction image.
    for (int i = 0; i < weighted_residual.height(); i++) {
        float s = (-1 + 2*i*(1.f / (num_parallel_rays - 1)))*((num_parallel_rays - 2.f)/num_parallel_rays);
        for (int j = 0; j < weighted_residual.width(); j++) {
            float theta = M_PI * j / (1.f * num_directions);
            float cos_theta = cos(theta);
            float sin_theta = sin(theta);
            float total_weight = 0.f;
            trace_line(reconstruction, cos_theta, sin_theta, s, [&](LinePoint p) {
                reconstruction(p.y, p.x) += p.weight * weighted_residual(i, j) / reconstruction_total_weights(p.y, p.x);
            });
        }
    }

}





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
