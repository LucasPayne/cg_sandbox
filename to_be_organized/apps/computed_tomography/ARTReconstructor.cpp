
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
