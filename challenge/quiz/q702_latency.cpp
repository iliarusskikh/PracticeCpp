#include <iostream>
#include <vector>
#include <chrono>
#include <new>      // NOTE: required for std::hardware_destructive_interference_size —
                     // not guaranteed to be pulled in transitively by <vector>/<chrono>

// Estimates the average latency (in ns) of a "cold" read that must be
// re-filled into L1 (i.e. the data was just evicted from L1, so this is
// effectively an L1-miss / fill-latency measurement, not a warm L1-hit).
auto MeasureL1CacheLatency() {

    // Smallest size guaranteed by the implementation such that two objects
    // placed CacheLineSize apart won't share (and false-share) a cache line.
    // In practice this equals the L1 cache line size (usually 64 bytes,
    // 128 on some Apple Silicon / ARM parts).
    constexpr auto CacheLineSize = std::hardware_destructive_interference_size; // C++17+

    // Size of the buffer we "flood" the cache with to evict everything
    // currently resident in L1 (and possibly L2, depending on its size).
    // 2<<12 == 8192, so this is CacheLineSize * 8192 ≈ 512 KB —
    // comfortably bigger than a typical 32–48 KB L1 data cache.
    constexpr auto EvictBufferSize = CacheLineSize * (2 << 12);

    // Number of repeated measurements to average over (reduces noise/variance
    // from a single tiny, sub-clock-resolution measurement).
    constexpr auto Trials = 20'000;

    // CacheLineData: the single 64-byte line whose "cold read" latency we
    // actually want to measure (only index [0] is ever touched).
    // CacheLineEvictData: the large scratch buffer used purely to evict L1.
    std::vector<uint8_t> CacheLineData(CacheLineSize), CacheLineEvictData(EvictBufferSize);

    // `volatile` sink forces the compiler to actually perform every read
    // below rather than proving the loops are dead code and deleting them.
    volatile uint64_t sink = 0;

    using namespace std::chrono;
    auto floodTime = 0.0; // running total of time spent purely in the flood loops (ns)

    const auto startTrialing = steady_clock::now();

    for (auto trials{0uz}; trials < Trials; trials++) {

        // --- Eviction phase (timed separately) ---
        auto floodStart = steady_clock::now();
        for (auto i{0uz}; i < CacheLineEvictData.size(); i += CacheLineSize) {
            sink += CacheLineEvictData[i]; // touch exactly one byte per cache line
                                            // -> pulls every line of the flood buffer
                                            // into cache, evicting CacheLineData in the process
        }
        auto floodEnd = steady_clock::now();

        const auto iterationFloodTime = duration_cast<nanoseconds>(floodEnd - floodStart).count();
        floodTime += static_cast<double>(iterationFloodTime);

        // --- The actual event of interest: reading the now-evicted line ---
        // This happens AFTER floodEnd was captured, so its cost is NOT inside
        // iterationFloodTime — it only shows up in the *outer* (startTrialing/
        // endTrialing) timer. That's the whole trick: subtract flood time from
        // total time to isolate this read (plus fixed per-iteration overhead).
        sink += CacheLineData[0];
    }

    const auto endTrialing = steady_clock::now();
    const auto totalTrialTime =
        static_cast<double>(duration_cast<nanoseconds>(endTrialing - startTrialing).count());

    // "Everything that happened in the loop that wasn't the flood work itself":
    // 2x steady_clock::now() call overhead, duration_cast/accumulate cost,
    // outer-loop bookkeeping, and — dominantly, if all goes well — the cold read.
    const auto totalReadLatency = totalTrialTime - floodTime;

    return totalReadLatency / Trials; // average ns per cold read (with caveats below)
}

int main() {
    auto latency = MeasureL1CacheLatency();
    std::cout << "Estimated cold-read latency: " << latency << " ns\n"; // was missing!
    return 0;
}


// steady_clock
// guaranteed never to go backwards
// it's designed for measuring intervals, not wall-clock time

