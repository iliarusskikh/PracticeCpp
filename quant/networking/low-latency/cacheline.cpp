//Cache Line Awareness
//False sharing is one of the biggest performance killers in low-latency systems. You can demonstrate you understand it:

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// BAD: two counters share a cache line — cores fight over it
struct BadCounters {
    std::atomic<long> a{0};  // } same 64-byte
    std::atomic<long> b{0};  // } cache line!
};

// GOOD: each counter on its own cache line
struct GoodCounters {
    alignas(64) std::atomic<long> a{0};
    alignas(64) std::atomic<long> b{0};
};

template<typename T>
long benchmark(T& counters) {
    auto t0 = std::chrono::high_resolution_clock::now();

    std::thread t1([&]{ for(int i=0;i<1e7;i++) counters.a++; });
    std::thread t2([&]{ for(int i=0;i<1e7;i++) counters.b++; });
    t1.join(); t2.join();

    auto t1_ = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1_-t0).count();
}

int main() {
    BadCounters  bad;
    GoodCounters good;
    std::cout << "Bad  (false sharing): " << benchmark(bad)  << "ms\n";
    std::cout << "Good (cache-aligned): " << benchmark(good) << "ms\n";
}
