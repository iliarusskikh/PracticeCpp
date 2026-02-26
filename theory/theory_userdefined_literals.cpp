#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>      // uint64_t
#include <cmath>        // std::pow

// ────────────────────────────────────────────────
// 1. Distance literals
// ────────────────────────────────────────────────
constexpr long double operator"" _km(long double km) {
    return km * 1000.0L;           // to meters
}

constexpr long double operator"" _m(long double m) {
    return m;                      // identity (for symmetry)
}

constexpr long double operator"" _cm(long double cm) {
    return cm * 0.01L;             // to meters
}

// ────────────────────────────────────────────────
// 2. Money / finance – simple big numbers
// ────────────────────────────────────────────────
constexpr uint64_t operator"" _million(unsigned long long n) {
    return n * 1'000'000ULL;
}

constexpr uint64_t operator"" _billion(unsigned long long n) {
    return n * 1'000'000'000ULL;
}

// ────────────────────────────────────────────────
// 3. Binary / hex style – readable large constants
// ────────────────────────────────────────────────
constexpr uint64_t operator"" _KiB(unsigned long long bytes) {
    return bytes * 1024ULL;
}

constexpr uint64_t operator"" _MiB(unsigned long long bytes) {
    return bytes * 1024ULL * 1024ULL;
}

// ────────────────────────────────────────────────
// 4. String literal – quoted string with prefix
// ────────────────────────────────────────────────
struct Quoted {
    std::string value;
    Quoted(const char* s, std::size_t len)
        : value(s, len) {}
};

Quoted operator"" _q(const char* str, std::size_t len) {
    return Quoted(str, len);
}

// ────────────────────────────────────────────────
// 5. Very simple temperature example (Celsius → Kelvin)
// ────────────────────────────────────────────────
constexpr double operator"" _C(long double celsius) {
    return celsius + 273.15L;
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    // Distance
    long double earth_radius   = 6371.0_km;
    long double room_height    = 280.0_cm;
    long double cable_length   = 42.195_km;     // marathon

    std::cout << "Earth radius   : " << earth_radius   << " meters\n";
    std::cout << "Room height    : " << room_height    << " meters\n";
    std::cout << "Marathon       : " << cable_length   << " meters\n\n";

    // Money / scale
    uint64_t budget = 2_billion + 450_million;
    uint64_t cache  = 64_MiB;

    std::cout << "Budget         : " << budget << " USD\n";
    std::cout << "Cache size     : " << cache  << " bytes\n\n";

    // String literal
    auto message = "Server error 503 - Service Unavailable"_q;
    std::cout << "Quoted string  : " << message.value << "\n\n";

    // Temperature
    double boiling = 100.0_C;
    double freezing = 0.0_C;

    std::cout << "Water boils at  : " << boiling   << " K\n";
    std::cout << "Water freezes at: " << freezing  << " K\n";

    return EXIT_SUCCESS;
}
