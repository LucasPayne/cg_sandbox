
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
