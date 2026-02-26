#include <functional>      // for std::hash
#include <cstdint>         // for uint64_t
#include <iostream>

int main()
{
    auto hasher = std::hash<std::uint64_t>{};

    std::uint64_t val1 = 0x0000000000000000ULL;
    std::uint64_t val2 = 0x0000000000000001ULL;

    std::uint64_t h1 = hasher(val1);
    std::uint64_t h2 = hasher(val2);

    int diff_bits = __builtin_popcountll(h1 ^ h2);

    std::cout << "Different bits: " << diff_bits << " (ideal ~32)\n";
    
    
    std::uint64_t h1 = std::hash<std::uint64_t>{}(0x0000000000000000ULL);
    std::uint64_t h2 = std::hash<std::uint64_t>{}(0x0000000000000001ULL);
    int diff_bits2 = __builtin_popcountll(h3 ^ h4);

    std::cout << "Different bits: " << diff_bits2 << " (ideal ~32)\n";
    
    
    std::cout << "Number of 1s in binary: " << __builtin_popcount(1234) << " in total\n";

    
}
//Different bits: 1 (ideal ~32)
//Different bits: 1 (ideal ~32)
//Ones: 5 ones

//if your keys have low entropy or structured patterns (e.g., sequential counters, bit-masked IDs, clustered values), you can get many collisions → long chains → O(n) slowdown.

