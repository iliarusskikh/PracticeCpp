#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <string>
#include <cstdint>     // uint64_t

// ────────────────────────────────────────────────
// Composite key: symbol + venue ID (common pattern)
// ────────────────────────────────────────────────
struct SymbolVenue {
    std::string symbol;
    uint32_t    venue_id;   // e.g. exchange/venue identifier

    // For nice printing
    friend std::ostream& operator<<(std::ostream& os, const SymbolVenue& k) {
        os << k.symbol << "@" << k.venue_id;
        return os;
    }
};

// ────────────────────────────────────────────────
// Equality: exact match (no float tolerance needed here)
// ────────────────────────────────────────────────
struct SymbolVenueEqual {
    bool operator()(const SymbolVenue& a, const SymbolVenue& b) const {
        return a.symbol == b.symbol && a.venue_id == b.venue_id;
    }
};

// ────────────────────────────────────────────────
// Hash: good mixing with golden-ratio style
// ────────────────────────────────────────────────
struct SymbolVenueHash {
    std::size_t operator()(const SymbolVenue& k) const noexcept {
        std::size_t h = std::hash<std::string>{}(k.symbol);

        // Mix in the venue_id (small integer)
        h ^= std::hash<uint32_t>{}(k.venue_id)
             + 0x9e3779b9ULL + (h << 6) + (h >> 2);

        return h;
    }
};

int main()
{
    // ────────────────────────────────────────────────
    // unordered_set with custom key/hash/equal
    // ────────────────────────────────────────────────
    std::unordered_set<SymbolVenue, SymbolVenueHash, SymbolVenueEqual> unique_trades;

    unique_trades.reserve(64);  // good habit

    // Insert some example executions / quotes
    unique_trades.insert({"AAPL", 1});   // NYSE
    unique_trades.insert({"AAPL", 2});   // Nasdaq
    unique_trades.insert({"MSFT", 1});
    unique_trades.insert({"TSLA", 3});   // some dark pool / ATS
    unique_trades.insert({"GOOGL", 1});
    unique_trades.insert({"AAPL", 1});   // duplicate → ignored

    // ────────────────────────────────────────────────
    // Basic queries
    // ────────────────────────────────────────────────
    SymbolVenue query{"AAPL", 2};
    std::cout << query << " exists? "
              << (unique_trades.contains(query) ? "YES" : "NO") << "\n";

    // ────────────────────────────────────────────────
    // Bucket statistics
    // ────────────────────────────────────────────────
    auto& s = unique_trades;

    std::size_t total_buckets    = s.bucket_count();
    std::size_t occupied         = 0;
    std::size_t max_length       = 0;

    for (std::size_t i = 0; i < total_buckets; ++i) {
        auto len = s.bucket_size(i);
        if (len > 0) {
            occupied++;
            if (len > max_length) max_length = len;
        }
    }

    std::cout << "\nunordered_set statistics:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Elements (size)       : " << s.size() << "\n";
    std::cout << "Bucket count          : " << total_buckets << "\n";
    std::cout << "Occupied buckets      : " << occupied
              << " (" << std::fixed << std::setprecision(1)
              << (100.0 * occupied / total_buckets) << "%)\n";
    std::cout << "Max chain length      : " << max_length << "\n";
    std::cout << "Load factor           : " << s.load_factor()
              << "  (max = " << s.max_load_factor() << ")\n\n";

    // Optional: show content of longest buckets
    std::cout << "Buckets with >1 element:\n";
    for (std::size_t i = 0; i < total_buckets; ++i) {
        auto len = s.bucket_size(i);
        if (len > 1) {
            std::cout << "  bucket[" << i << "]: " << len << " elements\n";
            for (auto it = s.begin(i); it != s.end(i); ++it) {
                std::cout << "    " << *it << "\n";
            }
        }
    }

    return EXIT_SUCCESS;
}
