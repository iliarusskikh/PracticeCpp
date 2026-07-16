#include <new>
#include <atomic>
#include <cstdlib>


static std::atomic<size_t> s_AllocCount{0};

void* operator new(size_t size) {
    
    if (size == 0) size = 1;              // Edge case: zero-size returns valid ptr
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();       // Edge case: out of memory
    
    s_AllocCount++;                       // Track allocation
    return p;
}

void* operator new[](size_t size) {
    // Delegate to scalar version
    return operator new(size);
}
