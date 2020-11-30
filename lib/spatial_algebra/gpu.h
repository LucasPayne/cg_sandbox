#ifndef SPATIAL_ALGEBRA_GPU_H
#define SPATIAL_ALGEBRA_GPU_H

#ifdef __CUDACC__
#define HD __host__ __device__
#else
#define HD
#endif

#endif // SPATIAL_ALGEBRA_GPU_H

