//static_assert checks conditions at compile-time. If false, compilation fails with a message. Great for type/size checks
#include <iostream>
#include <cstdint>  // for uint32_t

// Example: Assert size of type
static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes!");

// Template example
template<typename T>
void check_type() {
    static_assert(std::is_integral_v<T>, "T must be an integer type!");
}

int main() {
    check_type<int>();  // OK
    // check_type<double>();  // Would fail compilation

    std::cout << "All assertions passed!\n";
    return 0;
}
