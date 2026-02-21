//Binary literals start with 0b for easy bit representation. Digit separators (') improve readability in large numbers (works for decimal, hex, binary).
#include <iostream>
#include <cstdint>  // for uint32_t

int main() {
    // Binary literal with digit separators for readability
    uint32_t v = 0b0000'0000'0000'0000'1111'0000'1111'0000;  // Binary: groups of 4 bits
    std::cout << "Binary value (decimal): " << v << "\n";  // 0b... → 0xF0F0 = 61680

    // Also works for decimal
    long long big_decimal = 1'000'000'000'000LL;
    std::cout << "Big decimal: " << big_decimal << "\n";

    return 0;
}
