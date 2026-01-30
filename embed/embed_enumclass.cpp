//Enum classes are scoped, strongly typed, and can specify an underlying type (e.g., uint32_t) for better control and safety.
#include <iostream>
#include <cstdint>  // for uint32_t

// Traditional enum (unscoped, implicit int conversion)
typedef enum {
    OFF,  // 0
    ON    // 1
} State_t;

// Enum class (scoped, strongly typed, underlying type)
enum class ModernState_t : uint32_t {
    off,  // 0
    on    // 1
};

int main() {
    // Traditional enum usage
    State_t state = OFF;
    std::cout << "Traditional: " << state << " (implicit int: " << (state + 1) << ")\n";

    // Enum class usage (needs scope, no implicit int conversion)
    ModernState_t modern_state = ModernState_t::off;
    std::cout << "Enum class: " << static_cast<uint32_t>(modern_state) << "\n";

    return 0;
}
