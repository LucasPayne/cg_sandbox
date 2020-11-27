
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

