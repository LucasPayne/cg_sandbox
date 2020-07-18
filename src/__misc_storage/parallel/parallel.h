#ifndef PARALLEL_H
#define PARALLEL_H
#include <core.h>
#include <thread>
// #include <mutex>
// #include <condition_variable>
namespace Parallel {

int num_system_cores();

class ThreadingContext {
private:
    std::vector<std::thread> worker_threads;
public:
    ThreadingContext();
    ~ThreadingContext();
};


} // namespace Parallel
#endif // PARALLEL_H


