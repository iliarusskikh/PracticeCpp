#include <iostream>
#include <vector>
#include <numeric>      // for std::iota
#include <bitset>       // for std::bitset
#include <climits>      // for INT_MAX
#include <cstdlib>      // for std::abs (though __builtin_abs is compiler builtin)

//C++ 20
//#include <bit>          // for std::popcount, std::countl_zero, etc.
#include <version>      // for __cplusplus check (optional)


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== GCC/Clang Builtin Functions Demo ===\n\n";

    // ============================================
    // 1. BIT MANIPULATION (Most Common)
    // ============================================
    std::cout << "1. BIT MANIPULATION\n";
    std::cout << "-------------------\n";

    unsigned int x = 0b00000000000000000000000000001101; // 13 in binary
    unsigned long long big = 0xFFFFFFFFFFFFFFFFULL;      // 64 bits all set

    std::cout << "Number: " << x << " (binary: 1101)\n";
    std::cout << "  popcount(x):      " << __builtin_popcount(x) << " (count of 1s)\n";
    std::cout << "  popcountll(big):  " << __builtin_popcountll(big) << " (64-bit version)\n";
    std::cout << "  clz(x):           " << __builtin_clz(x) << " (leading zeros in 32-bit)\n";
    std::cout << "  ctz(x):           " << __builtin_ctz(x) << " (trailing zeros)\n";
    std::cout << "  ffs(x):           " << __builtin_ffs(x) << " (1-based position of first 1)\n";
    std::cout << "  parity(x):        " << __builtin_parity(x) << " (1 if odd number of 1s)\n\n";

    // Edge cases
    std::cout << "Edge cases:\n";
    std::cout << "  ctz(8):           " << __builtin_ctz(8) << " (1000 has 3 trailing zeros)\n";
    std::cout << "  clz(1):           " << __builtin_clz(1) << " (only LSB set)\n\n";

    // ============================================
    // 2. FINDING SET BITS (Common CP Pattern)
    // ============================================
    std::cout << "2. ITERATING SET BITS\n";
    std::cout << "---------------------\n";
    
    unsigned int mask = 0b10110; // 22
    std::cout << "Mask: " << mask << " (binary: 10110)\n";
    std::cout << "Set bit positions: ";

    while (mask) {
        int bit = __builtin_ctz(mask);  // Get position of lowest set bit
        std::cout << bit << " ";
        mask &= mask - 1;               // Clear lowest set bit
    }
    std::cout << "\n\n";

    // ============================================
    // 3. ARITHMETIC BUILTINS
    // ============================================
    std::cout << "3. ARITHMETIC OPERATIONS\n";
    std::cout << "------------------------\n";

    int a = -42;
    std::cout << "abs(-42):           " << __builtin_abs(a) << "\n";

    // Overflow detection
    int res;
    int big_num = INT_MAX;
    
    bool overflow = __builtin_add_overflow(big_num, 1, &res);
    std::cout << "add_overflow check: " << (overflow ? "YES" : "NO")
         << " (INT_MAX + 1)\n";
    
    overflow = __builtin_mul_overflow(100000, 100000, &res);
    std::cout << "mul_overflow check: " << (overflow ? "YES" : "NO")
         << " (100000 * 100000)\n\n";

    // ============================================
    // 4. BRANCH PREDICTION HINTS
    // ============================================
    std::cout << "4. BRANCH PREDICTION\n";
    std::cout << "--------------------\n";
    
    auto processPositive = [](int num) {
        // Tell compiler: num > 0 is LIKELY true
        if (__builtin_expect(num > 0, 1)) {
            return num * 2;
        }
        return 0;
    };
    
    std::cout << "processPositive(10): " << processPositive(10) << "\n";
    std::cout << "processPositive(-5): " << processPositive(-5) << "\n";
    std::cout << "(Hints help CPU pipeline, no visible output change)\n\n";

    // ============================================
    // 5. PREFETCHING (Cache Optimization)
    // ============================================
    std::cout << "5. CACHE PREFETCHING\n";
    std::cout << "--------------------\n";
    
    vector<int> arr(1000);
    iota(arr.begin(), arr.end(), 0);
    
    long long sum = 0;
    for (int i = 0; i < 900; i++) {
        // Prefetch data we'll need soon (3 iterations ahead)
        __builtin_prefetch(&arr[i + 100], 0, 3);  // 0=read, 3=high locality
        
        sum += arr[i];
    }
    std::cout << "Sum with prefetching: " << sum << "\n";
    std::cout << "(Prefetch reduces cache misses in large arrays)\n\n";

    // ============================================
    // 6. PRACTICAL CP EXAMPLES
    // ============================================
    std::cout << "6. COMPETITIVE PROGRAMMING TRICKS\n";
    std::cout << "---------------------------------\n";

    // Check if power of 2
    auto isPowerOf2 = [](unsigned int n) {
        return n > 0 && __builtin_popcount(n) == 1;
    };
    std::cout << "isPowerOf2(16):     " << (isPowerOf2(16) ? "YES" : "NO") << "\n";
    std::cout << "isPowerOf2(18):     " << (isPowerOf2(18) ? "YES" : "NO") << "\n";

    // Get highest power of 2 <= n
    auto highestPowerOf2 = [](unsigned int n) {
        return 1U << (31 - __builtin_clz(n));
    };
    //31 - __builtin_clz(n) -> 1U << position shifts left
    std::cout << "highestPowerOf2(50):" << highestPowerOf2(50) << "\n";

    // Count total set bits from 1 to n
    auto countTotalSetBits = [](int n) {
        int count = 0;
        for (int i = 1; i <= n; i++) {
            count += __builtin_popcount(i);
        }
        return count;
    };
    std::cout << "Total set bits 1-10:" << countTotalSetBits(10) << "\n";

    // Next permutation using builtins (alternative to std::next_permutation)
    std::cout << "\nNext higher number with same popcount:\n";
    unsigned int num = 0b00101100; // 44
    unsigned int next = ((num | (num - 1)) + 1) | (((~num & (num - 1)) - 1) >> (__builtin_ctz(num) + 1));
    std::cout << "  Current: " << num << " (" << std::bitset<8>(num) << ")\n";
    std::cout << "  Next:    " << next << " (" << std::bitset<8>(next) << ")\n\n";

    
    // ============================================
    // 7. C++20 STANDARD ALTERNATIVES (<bit>)
    // ============================================
    std::cout << "7. C++20 STANDARD EQUIVALENTS (<bit>)\n";
    std::cout << "-------------------------------------\n";
    #if __cplusplus >= 202002L
    #include <bit>
    std::cout << "std::popcount(13):  " << std::popcount(13u) << "\n";
    std::cout << "std::countl_zero(8):" << std::countl_zero(8u) << "\n";
    std::cout << "std::countr_zero(8):" << std::countr_zero(8u) << "\n";
    #else
    std::cout << "Compile with -std=c++20 to see std::bit functions\n";
    #endif

    return EXIT_SUCCESS;
}


/*
 Output:
 === GCC/Clang Builtin Functions Demo ===

 1. BIT MANIPULATION
 -------------------
 Number: 13 (binary: 1101)
   popcount(x):      3 (count of 1s)
   popcountll(big):  64 (64-bit version)
   clz(x):           28 (leading zeros in 32-bit)
   ctz(x):           0 (trailing zeros)
   ffs(x):           1 (1-based position of first 1)
   parity(x):        1 (1 if odd number of 1s)

 2. ITERATING SET BITS
 ---------------------
 Mask: 22 (binary: 10110)
 Set bit positions: 1 2 4

 3. ARITHMETIC OPERATIONS
 ------------------------
 add_overflow check: YES (INT_MAX + 1)
 mul_overflow check: YES (100000 * 100000)

 6. COMPETITIVE PROGRAMMING TRICKS
 ---------------------------------
 isPowerOf2(16):     YES
 isPowerOf2(18):     NO
 highestPowerOf2(50):32
 Total set bits 1-10:17
 
 
 */
