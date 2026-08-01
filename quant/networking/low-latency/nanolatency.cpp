//clang++ -std=c++20 -O2 -march=native -o program program.cpp
//The -march=native flag is itself a low-latency technique — it enables CPU-specific SIMD optimisations


#include <chrono>
#include <iostream>

// The right way to measure latency in C++
struct LatencyProbe {
    using Clock = std::chrono::high_resolution_clock;
    using NS    = std::chrono::nanoseconds;

    Clock::time_point start_;

    void start() { start_ = Clock::now(); }

    long stop_ns() {
        return std::chrono::duration_cast<NS>(
            Clock::now() - start_).count();
    }
};

int main() {
    LatencyProbe p;
    SPSCRing<int, 1024> ring;

    p.start();
    ring.push(42);
    auto val = ring.pop();
    long ns = p.stop_ns();

    std::cout << "Ring push/pop latency: " << ns << " ns\n";
}
