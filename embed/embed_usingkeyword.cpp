//The using keyword creates type aliases for readability. It can alias simple types, function pointers, or even templates (e.g., for generic pointers).
//during compile time
#include <iostream>
#include <cstdint>  // for uint32_t

// Simple type alias
using UL = unsigned long;

// Function pointer alias: points to a function taking uint32_t and returning uint32_t
using Func = uint32_t(*)(uint32_t);

// Alias template: generic pointer to any type T
template<typename T>
using Ptr = T*;

// Example function for pointer
uint32_t set_bit(uint32_t val) {
    return val | 1;  // Set lowest bit
}

int main() {
    // Simple alias
    UL big_num = 123456789UL;
    std::cout << "UL: " << big_num << "\n";

    // Function pointer
    Func fptr = &set_bit;
    std::cout << "Function ptr: " << fptr(0) << "\n";  // Calls set_bit(0) → 1

    // Alias template
    int a = 42;
    Ptr<int> iptr = &a;
    std::cout << "Ptr<int>: " << *iptr << "\n";

    return 0;
}
