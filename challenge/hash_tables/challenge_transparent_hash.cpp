#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <string_view>    // required for std::string_view

// ────────────────────────────────────────────────
// Transparent hasher for string-like keys
// ────────────────────────────────────────────────
struct string_hash
{
    using is_transparent = void;   // This enables heterogeneous lookup

    // Hash std::string_view (covers string literals, string_view, char*, etc.)
    std::size_t operator()(std::string_view sv) const noexcept
    {
        // Very simple FNV-1a style hash — good enough for most uses
        // In production many people use xxHash, murmur, or std::hash<std::string_view>
        std::size_t h = 14695981039346656037ULL;           // FNV offset basis
        for (char c : sv)
        {
            h ^= static_cast<std::size_t>(static_cast<unsigned char>(c));
            h *= 1099511628211ULL;                         // FNV prime
        }
        return h;
    }


    // Optional: also support std::string directly (not strictly required)
    std::size_t operator()(const std::string& s) const noexcept
    {
        return (*this)(std::string_view(s));
    }
};

int main()
{
    // Map with transparent hasher + transparent equal (std::equal_to<> is already transparent)
    std::unordered_map<std::string, int, string_hash, std::equal_to<>> m;

    // Insert some values (normal std::string keys)
    m["AAPL"] = 150;
    m["MSFT"] = 320;
    m["GOOGL"] = 2800;
    m.emplace("TSLA", 700);

    std::cout << "Map size: " << m.size() << "\n\n";

    // ────────────────────────────────────────────────
    // Lookups without creating any temporary std::string
    // ────────────────────────────────────────────────

    // 1. string literal → implicitly std::string_view
    if (auto it = m.find("AAPL"); it != m.end())
    {
        std::cout << "AAPL: " << it->second << "\n";
    }

    // 2. explicit string_view
    std::string_view sv = "MSFT";
    std::cout << "MSFT via string_view: " << m.at(sv) << "\n";

    // 3. count() also works transparently
    std::cout << "GOOGL exists? " << (m.count("GOOGL") ? "yes" : "no") << "\n";
    std::cout << "IBM exists?   " << (m.count("IBM")    ? "yes" : "no") << "\n";

    // 4. operator[] also works (but still creates entry if missing — be careful!)
    std::cout << "NVDA (new):   " << m["NVDA"] << "\n";           // inserts 0
    std::cout << "Map size now: " << m.size() << "\n";

    return EXIT_SUCCESS;
}

// hashing - Any operation that needs to locate / check existence / insert / erase a key will call the hash function at least once.

