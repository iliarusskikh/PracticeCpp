//Here’s a practical checklist for cache-friendly C++ code.

#include <iostream>

// driver code
int main()
{

    //1. Remember what the cache actually does
    //The CPU loads memory in cache lines (typically 64 bytes).
    struct Data {
        int a;   // 4 bytes
        int b;   // 4 bytes
        int c;   // 4 bytes
        int d;   // 4 bytes
        // total 16 bytes
    };
    
//    Accessing a pulls the whole cache line.
//    Unused data still costs bandwidth.
    
    Data arr[10000];
    int sum = 0;
    for (int i = 0; i < 10000; ++i) {
        sum += arr[i].a;           // ← only reading 4 bytes at a time
    }
    //Even though your code only reads 4 bytes at a time (arr[i].a), the CPU actually loads 64 bytes at a time (on almost all modern desktop/server/mobile CPUs in 2025–2026).


    
    
    
    
    
    
    
//  2 Contiguous memory benefits from spatial locality.
//  Linked structures often cause cache misses.
    
    std::vector<int> v(n);          // contiguous block of memory
    // internally: basically int* data = new int[n];  (plus size/capacity)

    for (int x : v) {
        sum += x;
    }
    
    std::list<int> l;               // doubly-linked list
    // each node is typically something like:
    // struct Node {
    //     int value;
    //     Node* next;
    //     Node* prev;   // ~24 bytes on 64-bit system (8+8+4 + padding/alignment)
    // };

    for (int x : l) {
        sum += x;
    }
    
    
    
    
    
    
    
//3 Think SoA (Structure of Arrays) vs AoS (Array of Structures)
//  Rule of thumb: AoS for clarity, SoA for hot loops and bulk processing.
    
    //AoS (Array of Structures) — the classic, intuitive way
    struct Particle {
        float x, y, z;     // position     12 bytes
        float vx, vy, vz;  // velocity     12 bytes
        // often padded to 16/32 bytes for alignment
    };

    std::vector<Particle> particles(N);
    
    //SoA (Structure of Arrays) — cache + vectorization + GPU friendly
    struct Particles {
        std::vector<float> x, y, z;
        std::vector<float> vx, vy, vz;
        // all same size N
    };
    
//    Rule of thumb (the checklist point)
//
//    Use AoS when:
//    Code clarity/readability is priority
//    You usually access all/most fields of one entity together (e.g., rendering a single sprite: pos + color + scale)
//    N is small (< few thousand — fits in L1/L2 cache anyway)
//    Object-oriented style feels natural
//
//Cache line: [x0 y0 z0 vx0 vy0 vz0 | x1 y1 z1 vx1 ...]  ← mixed, partial use
    
    
    
//    Use SoA (or hybrid) when:
//    Hot loops process one or few fields across many entities
//    Bulk / data-parallel processing (simulations, ML inference, compute shaders)
//    You want easy SIMD vectorization or GPU transfer
//    N is large (tens of thousands → millions)
//
//Cache line x: [x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12 x13 x14 x15]  ← all useful!
//    Many real engines use hybrids:
//
//    Unity DOTS / ECS → pure SoA-style
//    Game engines → AoS for small components, SoA for particle systems / vertex data
//    AoSoA (Array of hybrid chunks) — small blocks of AoS inside SoA for best of both
    
    
    
    
    
    
    
    

//    4. Access memory sequentially
//    Same complexity, very different performance.
//    Inner loops should walk memory linearly.
    //a[i][j], first through i, then through j
    
    //Elements of the same row are stored contiguously in memory.
//    The rightmost index (column) varies fastest.
    
    //The good (cache-friendly) way — sequential access

    double sum = 0.0;
    for (int i = 0; i < rows; ++i) {          // outer: rows
        for (int j = 0; j < cols; ++j) {      // inner: columns
            sum += m[i][j];
        }
    }
    
    
    
    
    
    
    
    
    
//    5. Minimize pointer indirection
    //Each next may point to a different cache line.
    
    //Most harmful version — classic linked list (heavy pointer chasing)
    struct Node {
        Node* next;       // ← 8 bytes on 64-bit system
        int value;        // 4 bytes
        // usually 24 bytes total because of alignment/padding
    };

    Node* head = ...;
    //traversal
    int sum = 0;
    for (Node* n = head; n != nullptr; n = n->next) {
        sum += n->value;
    }
    
    
    //Much better version — use indices instead of pointers
    struct Node {
        int next;       // ← index into vector/array (usually 4 bytes)
        int value;      // 4 bytes
        // total 8 bytes — very dense!
    };

    std::vector<Node> nodes;
    int head = first_valid_index;   // usually 0 or some other start index
    
    //traversal
    int sum = 0;
    for (int idx = head; idx != -1 /* or some invalid value */; idx = nodes[idx].next) {
        sum += nodes[idx].value;
    }
    
    
    
    
    
    
//    6. Keep hot data small
    //Hot loops should touch as few cache lines as possible.

    //The problem with the mixed “hot + cold” struct (AoS style)
    struct Object {
        int id;                // 4 bytes  ─┐ hot: accessed every frame/iteration
        float value;           // 4 bytes  ─┘
        std::string name;      // ~24–32 bytes (small string optimization + heap pointer)
        std::vector<int> log;  // ~24–32 bytes (capacity, size, pointer to heap)
        // total: usually 56–96 bytes per object (with padding + alignment)
    };

    std::vector<Object> objects(N);
    
    //Typical hot loop (e.g. game update, physics tick, simulation step, ML forward pass):
    for (auto& obj : objects) {
        obj.value += some_acceleration * dt;
        // maybe also use obj.id for lookup or conditional
    }
    
    
    //The solution: split hot vs cold data (SoA-style separation)
    // Hot data — keep small, dense, frequently accessed
    struct Hot {
        int   id;     // 4 B
        float value;  // 4 B
        // total 8 bytes → 8 objects fit in one 64-byte cache line
        // (with alignment padding → still ~8 per line)
    };

    // Cold data — large, infrequently accessed, or setup/teardown only
    struct Cold {
        std::string          name;
        std::vector<int>     log;
        // whatever else: texture ID, mesh handle, debug info, history, etc.
    };

    // In practice: parallel arrays / separate containers
    std::vector<Hot>  hot_data(N);
    std::vector<Cold> cold_data(N);   // or use indices if you want tighter coupling
    
    for (size_t i = 0; i < N; ++i) {
        hot_data[i].value += acceleration[i] * dt;
        // occasionally need cold data? → explicit access cold_data[i].name etc.
    }
    
    
    
    
    
    
//    7. Use blocking for large datasets
    for (int ii = 0; ii < N; ii += B)
      for (int jj = 0; jj < N; jj += B)
        for (int kk = 0; kk < N; kk += B)
          for (int i = ii; i < ii+B; ++i)
            for (int j = jj; j < jj+B; ++j)
              for (int k = kk; k < kk+B; ++k)
                C[i][j] += A[i][k] * B[k][j];
//example
    const int TILE_SIZE = 32;   // Tune this: 16, 32, 64... try what fits best in L1

    double sum = 0.0;

    for (int ii = 0; ii < ROWS; ii += TILE_SIZE) {//step of  32
        for (int jj = 0; jj < COLS; jj += TILE_SIZE) {

            // Now process one small tile (32×32 block)
            for (int i = ii; i < ii + TILE_SIZE && i < ROWS; ++i) {//processing each of 32 elements
                for (int j = jj; j < jj + TILE_SIZE && j < COLS; ++j) {
                    sum += matrix[i][j];
                }
            }
        }
    }
    
    
    
    
//    Blocking keeps working sets in cache.
//
//    For large N (e.g., thousands), this is cache-hostile in most loop orders because:
//
//    The inner loop reuses one row of A and one column of B — but columns of B are not contiguous (stride = N×sizeof(float)).
//    Data is reloaded from memory repeatedly → poor temporal reuse (same elements fetched many times across distant loop iterations).
//    Working set (active parts of A, B, C) is huge → doesn't fit in L1/L2 cache → lots of expensive L3/main-memory accesses.
    
    
    
    
    
//    8. Avoid branches in hot loops
    // Branch-heavy
    if (x > 0)
        sum += x;

    // More predictable
    sum += x &-(x >0);

    //Small changes matter in tight loops.
    
    
    
    
    
//    9. Be deliberate about alignment and false sharing
//False sharing happens when two or more threads read/write different variables that happen to live on the same cache line (usually 64 bytes).
    
    struct alignas(64) Counter {
        std::atomic<int> value;
    };
    
    struct Counters {
        std::atomic<int> a;   // Thread 1 increments this
        std::atomic<int> b;   // Thread 2 increments this
        // total ~8–16 bytes → almost always on same 64-byte line
    };

    Counters global_counters;
    //Even with std::atomic, you get false sharing thrashing — not data race, just terrible performance.

//    Shared cache lines hurt multithreaded performance; padding helps.
    
//    Because cache coherence protocols (MESI/MOESI etc.) work at cache-line granularity:
//
//    Thread A writes to counterA.value → invalidates the entire cache line in all other cores
//    Thread B (on another core) wants to write to counterB.value (same line) → must wait for the line to be re-acquired → ping-pong between cores
//    Result: massive contention, even though logically the variables are independent → performance drops to single-thread speed or worse in contended cases
    
    
    
    //Mitigation: Pad to separate cache lines (destructive interference)
//    Use std::hardware_constructive_interference_size instead of hard-coding 64 for portability.

    //std::hardware_constructive_interference_size is the maximum size you can use for objects that you want to share on the same cache line (true sharing, for read-mostly or producer-consumer patterns).
    
    struct alignas(std::hardware_constructive_interference_size) SharedReadMostly {
        int version;               // written rarely
        std::atomic<int> refcount; // read often by many threads
        // Keep total ≤ constructive size so they stay together → fewer lines to load
    };
    
//    Use when you want locality (e.g., read-hot data + version check).
//    Rarely needed — most performance work focuses on avoiding destructive interference.
    
    
//    10. Compile with realistic optimizations
    //g++ -O3 -march=native -mtune=native -flto -DNDEBUG -o app main.cpp
//    
//    -march=native enables all CPU-specific instructions (AVX2/AVX-512, etc.)
//    -O3 enables aggressive optimizations (including loop unrolling, vectorization)
//    Avoid -O0 or debug builds for perf measurements — they hide real bottlenecks
    //perf stat -e instructions,cycles,cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses ./app
    //perf stat ./app
    
    //Tools evolve, but in 2026 the combo of perf stat, perf record/report, perf c2c, and Cachegrind remains the gold standard on Linux for cache/memory performance work.
    
    
    
    
    //11. padding
    //Most C++ implementations apply one more rule:
    //The size of the struct must be a multiple of the largest alignment requirement of any of its members.
    //1. Forcing no padding — use __attribute__((packed)) or #pragma pack
    
    // Before: normal struct with automatic padding
    struct Normal {
        uint8_t  a;     // 1 byte even
        // ← compiler adds 1 byte padding here (to align uint16_t on 2-byte boundary)
        uint8_t  b;     // 1 byte
        uint16_t c;     // 2 bytes uint16_t → usually must start at an even address (2-byte alignment)
    };  // Total size: 6 bytes (on most platforms)

//    Largest alignment here = 2 bytes (uint16_t)
//    So sizeof must be a multiple of 2 (i.e. even)
    //If the last member has alignment 2, compilers usually pad to next multiple of 2 that is ≥ current offset + size of last member — but they round up aggressively.
    
    // After: packed — no automatic padding
    struct Packed {
        uint8_t  a;     // 1 byte
        uint8_t  b;     // 1 byte
        uint16_t c;     // 2 bytes
    } __attribute__((packed));  // Total size: 4 bytes

    // Alternative syntax (GCC/Clang/MSVC compatible)
    #pragma pack(push, 1)
    struct Packed2 {
        uint8_t  a;
        uint8_t  b;
        uint16_t c;
    };
    #pragma pack(pop)
    
    
    // Good compromise for status register
    union StatusRegister {
        uint8_t raw;                     // for direct hardware write/read

        struct {
            uint8_t enabled    : 1;
            uint8_t overflow   : 1;
            uint8_t timeout    : 1;
            uint8_t reserved   : 5;
        } bits __attribute__((packed));

    } status;
    
    
    
    
    return EXIT_SUCCESS;
}
