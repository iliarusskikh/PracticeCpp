#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>

// ────────────────────────────────────────────────
// Custom key type — typical in trading/quant code
// ────────────────────────────────────────────────
struct TradeKey {
    std::string  symbol;
    int          side;       // e.g. 1 = buy, -1 = sell
    double       price;      // limit price

    
    // For debugging / printing
    friend std::ostream& operator<<(std::ostream& os, const TradeKey& k) {
        os << k.symbol << " "
           << (k.side > 0 ? "BUY" : "SELL") << " @ "
           << std::fixed << std::setprecision(2) << k.price;
        return os;
    }
};

// ────────────────────────────────────────────────
// Custom equality comparator (with floating-point tolerance)
// ────────────────────────────────────────────────
struct TradeKeyEqual {
    bool operator()(const TradeKey& a, const TradeKey& b) const {
        constexpr double EPS = 1e-6;
        return a.symbol == b.symbol &&
               a.side   == b.side   &&
               std::abs(a.price - b.price) < EPS;
    }
};

// ────────────────────────────────────────────────
// Custom hash
// Using the classic boost-style golden ratio combine
// ────────────────────────────────────────────────
struct TradeKeyHash {
    std::size_t operator()(const TradeKey& k) const noexcept {
        std::size_t h = std::hash<std::string>{}(k.symbol);

        // Combine side (small integer)
        h ^= std::hash<int>{}(k.side) + 0x9e3779b9 + (h << 6) + (h >> 2);

        // Combine price (double → bit pattern)
        // Important: we hash the bit representation, not the value
        std::uint64_t price_bits = 0;
        std::memcpy(&price_bits, &k.price, sizeof(double));
        h ^= std::hash<std::uint64_t>{}(price_bits) + 0x9e3779b9 + (h << 6) + (h >> 2);

        return h;
    }
};


int main()
{
    // ────────────────────────────────────────────────
    // Create the map with custom key + hash + equal
    // ────────────────────────────────────────────────
    std::unordered_map<
        TradeKey,
        int,                        // just a counter / volume for example
        TradeKeyHash,
        TradeKeyEqual
    > book;

    // Reserve space → helps avoid many early rehashes
    book.reserve(32);

    // ────────────────────────────────────────────────
    // Insert some example orders
    // ────────────────────────────────────────────────
    book[{ "AAPL",  1, 195.20 }] = 100;
    book[{ "AAPL", -1, 195.25 }] =  80;
    book[{ "MSFT",  1, 420.50 }] =  50;
    book[{ "TSLA",  1, 248.75 }] = 120;
    book[{ "AAPL",  1, 195.20 }] = 220;   // same key → updates
    book[{ "NVDA", -1, 890.10 }] =  30;
    book[{ "GOOGL", 1, 175.40 }] =  60;

    // ────────────────────────────────────────────────
    // Collect bucket statistics
    // ────────────────────────────────────────────────
    std::size_t total_buckets      = book.bucket_count();
    std::size_t occupied_buckets   = 0;
    std::size_t max_chain_length   = 0;

    for (std::size_t i = 0; i < total_buckets; ++i) {
        std::size_t len = book.bucket_size(i);
        if (len > 0) {
            occupied_buckets++;
            max_chain_length = std::max(max_chain_length, len);
        }
    }

    // ────────────────────────────────────────────────
    // Print report
    // ────────────────────────────────────────────────
    std::cout << "\nunordered_map<TradeKey, int> statistics\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Elements (size)         : " << book.size() << "\n";
    std::cout << "Bucket count            : " << total_buckets << "\n";
    std::cout << "Occupied buckets        : " << occupied_buckets
              << " (" << (100.0 * occupied_buckets / total_buckets) << "%)\n";
    std::cout << "Max chain length        : " << max_chain_length << "\n";
    std::cout << "Load factor             : " << std::fixed << std::setprecision(3)
              << book.load_factor() << "  (max = " << book.max_load_factor() << ")\n\n";

    // Optional: show which buckets have content
    std::cout << "Buckets with content:\n\n";
    for (std::size_t i = 0; i < total_buckets; ++i) {
        std::size_t len = book.bucket_size(i);
        if (len > 0) {
            std::cout << "  bucket[" << std::setw(3) << i << "] : "
                      << len << " element(s)\n";
        }
    }

    

    size_t b = book.bucket(TradeKey{ "AAPL",  1, 195.20 });
    
    for (auto it = book.begin(b); it != book.end(b); ++it) {
        std::cout << "  " << it->first << " → " << it->second << "\n";
    }




    std::unordered_map<
        TradeKey,
        int,                        // just a counter / volume for example
        TradeKeyHash,
        TradeKeyEqual
    > book2;
    // extract a node → move it to another container without rehashing / copying key
    auto node = book.extract(key);           // removes from m, returns node_handle
    book2.insert(std::move(node));    // inserts into another map, reuses the node

    
    return EXIT_SUCCESS;
}


/*
 
 unordered_map<TradeKey, int> statistics
 ----------------------------------------
 Elements (size)         : 6
 Bucket count            : 11
 Occupied buckets        : 6 (54.545%)
 Max chain length        : 2
 Load factor             : 0.545  (max = 1)

 Buckets with content:
   bucket[  0] : 1 element(s)
   bucket[  2] : 2 element(s)
   bucket[  4] : 1 element(s)
   bucket[  5] : 1 element(s)
   bucket[  7] : 1 element(s)
 
 */



/*
 
 
 struct string_hash {
     using is_transparent = void;           // this enables heterogeneous lookup
     size_t operator()(std::string_view sv) const noexcept { … }
 };

 std::unordered_map<std::string, int, string_hash, std::equal_to<>> m;

 // now you can do lookups without creating std::string
 m.find("AAPL");                    // string literal → string_view
 m.count(std::string_view("MSFT"));
 
 
 */
