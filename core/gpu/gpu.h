#ifndef GPU_H
#define GPU_H
#include <stdlib.h>
#include <unordered_map>
#include <type_index>


void _cuda_check(cudaError_t result, char const *const func, const char *const file, int const line)
{
    if (result != 0) {
        std::cerr << "CUDA error (" << result << ") at " << file << ":" << line << " '" << func << "'\n";
        cudaDeviceReset();
        exit(EXIT_FAILURE);
    }
}
#define cuda_check(RESULT) _cuda_check(( RESULT ), #RESULT, __FILE__, __LINE__)


// Use CUDA API function to determine the block size giving the maximum possible occupancy.
// It is assumed that this is the best choice.
template <typename K>
int get_block_size(const char *description, K kernel) {
    // It is assumed that the API function does non-trivial work, so its result is cached.
    static std::unordered_map<std::type_index, int> block_size_cache;

    std::type_index t_index(typeid(K));
    auto found = std::find(block_size_cache.begin(), block_size_cache.end(), t_index);
    if (found != block_size_cache.end()) {
        // Found in the cache.
        return found->second;
    }
    // Not found in the cache, call the API function to compute the block size for maximum occupancy.
    int min_grid_size, block_size;
    cudaOccupancyMaxPotentialBlockSize(&min_grid_size, &block_size, kernel, 0, 0);
    block_size_cache[t_index] = block_size;
    return block_size;
}


template <typename F>
__global__ void Kernel(F func, int n)
{
    int index = blockDim.x*blockIdx.x + threadIdx.x;
    if (index >= n) return;
    func(index);
}


template <typename F>
void GPU_for(const char *description, int n, F func)
{
    auto kernel = &Kernel<F>;
    int block_size = get_block_size(description, kernel);
    int grid_size = (n-1)/block_size + 1;
    kernel<<<grid_size, block_size>>>(func, n);
}


#endif // GPU_H
