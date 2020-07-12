#include "parallel/parallel.h"
namespace Parallel {

int num_system_cores()
{
    // hardware_concurrency() gives a hint only.
    int n = std::thread::hardware_concurrency();
    if (n == 0) return 1;
    return n;
}

} // namespace Parallel
