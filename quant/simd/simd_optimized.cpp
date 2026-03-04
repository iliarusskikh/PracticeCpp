// vector_add_benchmark.cpp
// Compile examples:
//   g++ -std=c++17 -O3 -march=native -o vecadd vecadd.cpp          (auto-detects best)
//   clang++ -std=c++17 -O3 -march=native -o vecadd vecadd.cpp
//
//   For explicit AVX2:   -mavx2
//   For explicit NEON:   -march=armv8-a+simd (usually enabled by default on aarch64)

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstddef>      // size_t

#if defined(__AVX2__)
    #include <immintrin.h>
    #define USE_AVX2 1
#elif defined(__ARM_NEON) || defined(__ARM_NEON__)
    #include <arm_neon.h>
    #define USE_NEON 1
#else
    #warning "No SIMD support detected – using scalar fallback only"
#endif

void run_benchmark()
{
    constexpr size_t size = 10'000'000;   // large enough to see difference
    constexpr float   init_a = 1.234f;
    constexpr float   init_b = 2.567f;

    std::vector<float> a(size, init_a);
    std::vector<float> b(size, init_b);
    std::vector<float> result(size, 0.0f);

    // ────────────────────────────────────────────────
    // 1. Scalar version
    // ────────────────────────────────────────────────
    auto t1_start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }

    auto t1_end = std::chrono::high_resolution_clock::now();
    auto scalar_us = std::chrono::duration_cast<std::chrono::microseconds>(t1_end - t1_start).count();

    // Reset result for fair comparison
    std::fill(result.begin(), result.end(), 0.0f);

    // ────────────────────────────────────────────────
    // 2. SIMD version
    // ────────────────────────────────────────────────
    auto t2_start = std::chrono::high_resolution_clock::now();

    
#if defined(USE_AVX2) // AMD
    // ─── AVX2 (8 floats per vector) ────────────────────────────────
    constexpr size_t step = 8;
    size_t i = 0;
    for (; i + step <= size; i += step) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&result[i], vr);
    }
    // remainder
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }

    
#elif defined(USE_NEON) // ARM
    // ─── NEON (4 floats per vector) ────────────────────────────────
    constexpr size_t step = 4;
    size_t i = 0;
    for (; i + step <= size; i += step) {
        float32x4_t va = vld1q_f32(&a[i]);
        float32x4_t vb = vld1q_f32(&b[i]);
        float32x4_t vr = vaddq_f32(va, vb);
        vst1q_f32(&result[i], vr);
    }
    // remainder
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }

#else
    // Fallback – same as scalar
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
#endif

    auto t2_end = std::chrono::high_resolution_clock::now();
    auto simd_us = std::chrono::duration_cast<std::chrono::microseconds>(t2_end - t2_start).count();

    // ────────────────────────────────────────────────
    // Results
    // ────────────────────────────────────────────────
    std::cout << "\nVector size: " << size << " floats ("
              << size * sizeof(float) / 1024.0 / 1024.0 << " MiB)\n\n";

    std::cout << "Scalar loop:   "
              << std::fixed << std::setprecision(0)
              << scalar_us << " μs\n";

    std::cout << "SIMD version:  "
              << simd_us << " μs\n";

    if (scalar_us > 0) {
        double speedup = static_cast<double>(scalar_us) / simd_us;
        std::cout << "Speedup:       " << std::setprecision(2)
                  << speedup << "×\n";
    }

#ifdef USE_AVX2
    std::cout << "Used: AVX2 (256-bit / 8 floats per iteration)\n";
#elif defined(USE_NEON)
    std::cout << "Used: NEON (128-bit / 4 floats per iteration)\n";
#else
    std::cout << "Used: scalar only (no SIMD detected)\n";
#endif

    // Optional: verify correctness (last few elements)
    std::cout << "\nLast few results (should be ≈ "
              << init_a + init_b << "):\n";
    for (size_t k = size - 8; k < size; ++k) {
        std::cout << result[k] << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "Vector addition benchmark\n";
    std::cout << "Compiler: " << __cplusplus << " / "
#ifdef __clang__
              << "Clang " << __clang_major__ << "." << __clang_minor__
#elif defined(__GNUC__)
              << "GCC " << __GNUC__ << "." << __GNUC_MINOR__
#endif
              << "\n";

    run_benchmark();
    return EXIT_SUCCESS;
}
