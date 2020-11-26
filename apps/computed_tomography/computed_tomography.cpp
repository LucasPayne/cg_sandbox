#include <time.h>
#include <assert.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/cameraman.cpp"
#include "world/graphics/image.h"


Image<float> create_sinogram(Image<float> image, int num_parallel_rays, int num_directions)
{
    assert(image.width() == image.height());
    int n = image.width();
    Image<float> sinogram(num_parallel_rays, num_directions);

    float inv_num_directions = 1.0 / num_directions;
    float inv_num_parallel_rays_minus_one = 1.0 / (num_parallel_rays - 1);
    for (int i = 0; i < num_directions; i++) {
        float theta = M_PI * i * inv_num_directions;
        float sin_theta = sin(theta);
        float cos_theta = cos(theta);
        for (int j = 0; j < num_parallel_rays; j++) {
            float s = -1 + 2*j*inv_num_parallel_rays_minus_one;
            vec2 p(s * cos_theta, s * sin_theta);
            
            float height = sqrt(1 - fabs(s)*fabs(s));
            vec2 from = 0.5*(p + height*vec2(-sin_theta, cos_theta) + vec2(1,1));
            vec2 to = 0.5*(p - height*vec2(-sin_theta, cos_theta) + vec2(1,1));
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
                integral += (next_t - t) * image(cell_y, cell_x);
                t = next_t;
            }
            sinogram(j, i) = integral;
        }
    }
    return sinogram;
}





Aspect<Camera> main_camera;


struct Test : public IBehaviour {
    Image<float> image;
    Image<float> sinogram;
    Test(int n) : image(n, n)
    {
        image.clear(0);
        for (int i = 0; i < 5; i++) draw_circle(image, vec2(0.5+0.3*(frand()-0.5), 0.5+0.3*(frand()-0.5)), 0.1+frand()*0.2, 0.5+0.5*frand());
        sinogram = create_sinogram(image, 128, 128);
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
                image.clear(0);
	        for (int i = 0; i < 5; i++) draw_circle(image, vec2(0.5+0.3*(frand()-0.5), 0.5+0.3*(frand()-0.5)), 0.1+frand()*0.2, 0.5+0.5*frand());
                sinogram = create_sinogram(image, 128, 128);
            }
        }
    }

    void update() {
        world->graphics.paint.bordered_depth_sprite(main_camera, image.texture(), vec2(0.1,0.1), 0.4,0.4, 3, vec4(0.5,0.5,0.5,1));
        world->graphics.paint.bordered_depth_sprite(main_camera, sinogram.texture(), vec2(0.1,0.5), 0.4,0.4, 3, vec4(0.5,0.5,0.5,1));
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
    world.add<Test>(test, 128);
}


void App::close()
{
}
void App::loop()
{
    // std::vector<vec2> points = {vec2(0.2,0.2)};
    // world.graphics.paint.circles(main_camera, points, 0.2, vec4(0,0,1,1), 0.03, vec4(1,0,0,1));

/*
    struct ellipse {
        vec2 origin;
        float theta;
        float a;
        float b;
        float density;
    };
    std::vector<ellipse> ellipses;
    ellipse e;
    e.origin = vec2(0.5,0.5);
    e.theta = 0;
    e.a = 0.1;
    e.b = 0.1;
    ellipses.push_back(e);

    vec2 c(0.5, 0.5);
    float r = 0.1;
    int s_n = 10;
    int theta_n = 10;
    for (int i = 0; i < theta_n; i++) {
        float theta = 2*M_PI*i*(1.0/theta_n);
        for (int j = 0; j < s_n; j++) {
            float s = -r + 2*r*j*(1.0/s_n);
            vec2 d1 = c + s*vec2(cos(theta), sin(theta)/0.566) + r*vec2(sin(theta), -cos(theta)/0.566);
            vec2 d2 = c + s*vec2(cos(theta), sin(theta)/0.566) - r*vec2(sin(theta), -cos(theta)/0.566);
            std::vector<vec2> points = {d1, d2};
            world.graphics.paint.chain_2D(main_camera, points, 1, vec4(0,0,1,1));

            vec2 origin = d1;
            vec2 dir = (d2 - d1).normalized();

            for (auto &el : ellipses) {
                float inv_a_squared = 1.0 / (el.a * el.a);
                float inv_b_squared = 1.0 / (el.b * el.b);

                std::cout << origin << "\n";
                vec2 origin_p = origin.inverse_transform(el.origin, el.theta);
                std::cout << "---> " << origin_p << "\n";
                vec2 dir_p = dir.rotate(el.theta);
                float A = dir_p.x()*dir_p.x() * inv_a_squared + dir_p.y()*dir_p.y() * inv_b_squared;
                float B = 2*origin_p.x()*dir_p.x() * inv_a_squared + 2*origin_p.y()*dir_p.y() * inv_b_squared;
                float C = origin_p.x()*origin_p.x() * inv_a_squared + origin_p.y()*origin_p.y() * inv_b_squared - 1;
                float discrim = B*B - 4*A*C;
                if (discrim >= 0) {
                    float sqrt_discrim = sqrt(discrim);
                    float inv_2A = 1.0 / 2*A;
                    float t1 = (B + sqrt_discrim)*inv_2A;
                    float t2 = (B - sqrt_discrim)*inv_2A;
                    vec2 p1 = origin + dir*t1;
                    vec2 p2 = origin + dir*t2;
                    std::vector<vec2> points = {p1, p2};
                    world.graphics.paint.circles(main_camera, points, 0.01, vec4(0,0,1,1), 0.01, vec4(1,0,0,1));
                }
            }
        }
    }
*/
/*
    int num_parallel_rays = 50;
    int num_directions = 50;
    float inv_num_directions = 1.0 / num_directions;
    float inv_num_parallel_rays_minus_one = 1.0 / (num_parallel_rays - 1);
    for (int i = 0; i < num_directions; i++) {
        float theta = M_PI * i * inv_num_directions;
        float sin_theta = sin(theta);
        float cos_theta = cos(theta);
        for (int j = 0; j < num_parallel_rays; j++) {
            float s = -1 + 2*j*inv_num_parallel_rays_minus_one;
            vec2 p(s * cos_theta, s * sin_theta);
            
            float height = sqrt(1 - fabs(s)*fabs(s));
            vec2 from = p + height*vec2(-sin_theta, cos_theta);
            vec2 to = p - height*vec2(-sin_theta, cos_theta);

	    std::vector<vec2> points = {0.5*(from + vec2(1,1)), 0.5*(to + vec2(1,1))};
            world.graphics.paint.chain_2D(main_camera, points, 1, vec4(0,0,1,1));
        }
    }
*/
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
