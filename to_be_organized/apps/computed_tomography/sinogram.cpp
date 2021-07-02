

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
