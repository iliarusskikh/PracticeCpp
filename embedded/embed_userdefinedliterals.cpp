//Custom operators for literals allow domain-specific syntax, like converting "5.0_km" to meters at compile-time if constexpr.
#include <iostream>

// User-defined literal for kilometers to meters
constexpr long double operator"" _km(long double x_km) {
    return x_km * 1000.0;  // Convert km to meters
}

int main() {
    long double distance = 5.0_km;  // Calls operator"" _km(5.0)
    std::cout << "5 km in meters: " << distance << "\n";

    // Works with integers too (implicit conversion)
    long double another = 2_km;  // 2.0_km
    std::cout << "2 km in meters: " << another << "\n";

    return 0;
}
