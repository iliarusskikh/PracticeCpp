//Lock-Free Ring Buffer
//This is the heart of DPDK, ef_vi, and every kernel-bypass system. Packets are passed between threads/cores via ring buffers without locks.

// spsc_ring.hpp — Single Producer Single Consumer Ring Buffer
#include <atomic>
#include <array>
#include <optional>

template<typename T, size_t N>
class SPSCRing {
    // Cache-line aligned to avoid false sharing between cores
    // This is a key pattern in ALL low-latency systems
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};
    std::array<T, N> buf_;

public:
    bool push(const T& val) {
        const size_t h = head_.load(std::memory_order_relaxed);
        const size_t next = (h + 1) % N;
        if (next == tail_.load(std::memory_order_acquire))
            return false; // full
        buf_[h] = val;
        head_.store(next, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {
        const size_t t = tail_.load(std::memory_order_relaxed);
        if (t == head_.load(std::memory_order_acquire))
            return std::nullopt; // empty
        T val = buf_[t];
        tail_.store((t + 1) % N, std::memory_order_release);
        return val;
    }
};


//DPDK's rte_ring, Solarflare's packet queues — all built on this exact pattern.
