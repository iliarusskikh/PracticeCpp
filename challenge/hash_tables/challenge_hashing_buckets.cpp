#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
#include <iomanip>

struct Position {
    double px;
    int qty;
    std::string sym;
};



//A valid hash function must:
//
//Be a function object (has operator()(const Key& k) const).
//Return size_t.
//Be noexcept (strongly recommended — otherwise the container may be slower or throw).
//Always return the same value for the same key within one execution of the program.
//If two keys are equal according to KeyEqual, they must produce the exact same hash.
//Produce a good distribution (different keys should collide as rarely as possible).
struct PosHash {
    size_t operator()(const Position& p) const noexcept {
        
        size_t h1 = std::hash<std::string>{}(p.sym);
        //{}Creates a temporary object of that type (default-constructed)
        //(p.sym)Calls operator() on that temporary object, passing p.sym
        size_t h2 = std::hash<double>{}(p.px);
        size_t h3 = std::hash<int>{}(p.qty);
        
        // Excellent mixing function (boost::hash_combine style)
        h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        h1 ^= h3 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        
        return h1;
    }
};

struct PosEqual {
    bool operator()(const Position& a, const Position& b) const {
        return a.sym == b.sym &&
               std::abs(a.px - b.px) < 1e-9 &&   // floating-point safe
               a.qty == b.qty;
    }
};
// When PosEqual is called?
//book.find(key) — for every element in the bucket until match or end
//book[key] (operator[]) — to decide “insert new” or “return existing"
//book.at(key) — same as find, throws if not found
//book.count(key) / contains(key) (C++20)
//book.insert(...) / emplace(...) / try_emplace(...) - checks if key already exists before inserting
//book.erase(key) (the key version)Yesbook.erase(it) (iterator version)

// Default would be std::equal_to<Position>
// which does member-wise exact comparison:
//return a.px == b.px && a.qty == b.qty && a.sym == b.sym;

//But double exact == is dangerous in production code (floating-point rounding, 100.50 vs 100.499999999).
//Our version uses std::abs(a.px - b.px) < 1e-9 → tolerant to tiny price differences.


int main() {
//    std::unordered_map<Position, double, PosHash> book; //only with hash function

    std::unordered_map<Position, double, PosHash, PosEqual> book;
//    Keys are of type Position
//    Values are double
//    Use our custom hash function PosHash instead of the default std::hash<Position>
//    Use our custom equality check PosEqual instead of the default operator== or std::equal_to<Position>
    
    // Best practice: reserve before bulk inserts
    book.reserve(10);

    // Insert
    book[{100.50, 100, "AAPL"}] = 10'250.75;
    //struct Position {
    //    double px;       // ← 100.50
    //    int    qty;      // ← 100
    //    std::string sym; // ← "AAPL"  (const char* → std::string)
    //};

    book.emplace(Position{150.25, 50, "TSLA"}, 7'500.0);
    book[{99.99, 200, "NVDA"}] = 25'000.0;

    // Lookup
    Position lookup{100.50, 100, "AAPL"};
    auto it = book.find(lookup);
    if (it != book.end()) {
        std::cout << "Found AAPL position value: $"
                  << std::fixed << std::setprecision(2) << it->second << '\n';
    }



    std::cout << "AAPL bucket = " << book.bucket(Position{100.50, 100, "AAPL"}) << '\n';
    std::cout << "TSLA bucket = " << book.bucket(Position{150.25, 50, "TSLA"}) << '\n';
    std::cout << "NVDA bucket = " << book.bucket(Position{99.99, 200, "NVDA"}) << '\n';
    std::cout << "\n";


    // Stats
    std::cout << "Size          : " << book.size() << '\n'; //Number of key-value pairs stored
    std::cout << "Bucket count  : " << book.bucket_count() << '\n';
    //Size of the internal array of buckets total size before re-allocation
    //After reserve(10) the implementation chosenthe next suitable size.
    //Most standard libraries (GCC, Clang) use small prime numbers (11 is the smallest prime ≥ 10).
    
    std::cout << "Load factor   : " << book.load_factor() << '\n';
    //size() / bucket_count() = 3 / 11
    //Very low → excellent performance (far below the 1.0 trigger for rehash)

    std::cout << "Max load factor: " << book.max_load_factor() << '\n';

    // Show bucket distribution
    for (size_t i = 0; i < book.bucket_count(); ++i) {
        if (book.bucket_size(i) > 0) {
            std::cout << "Bucket " << i << " has " << book.bucket_size(i) << " elements\n";
        }
    }
    //Two of Position keys landed in bucket 0 after hash % 11
    //Collision happened

    size_t b = book.bucket(Position{100.50, 100, "AAPL"});

    for (auto it = book.begin(b); it != book.end(b); ++it) {
        // sequential access — in the order they are chained
        std::cout << it->first.sym << " : " << it->second << '\n';
    }


    //max chain length
    size_t max_chain = 0;
    size_t buckets_with_elements = 0;

    for (size_t i = 0; i < book.bucket_count(); ++i) {
        size_t len = book.bucket_size(i);
        if (len > 0) {
            buckets_with_elements++;
            max_chain = std::max(max_chain, len);
            if (len >= 5) {
                std::cout << "Bucket " << i << " has " << len << " elements\n";
            }
        }
    }

    std::cout << "Max chain length: " << max_chain << "\n";
    std::cout << "Buckets with content: " << buckets_with_elements << " / " << book.bucket_count() << "\n";





    return EXIT_SUCCESS;
}

//Found AAPL position value: $10250.75
//Size          : 3
//Bucket count  : 11
//Load factor   : 0.27
//Max load factor: 1.00
//Bucket 0 has 2 elements
//Bucket 7 has 1 elements



//the final hash % 11 can still be the same for different keys when the table is tiny (only 11 buckets).
//This is normal and expected.
//buckets array (size 11):
//
//[0]  →  Position{AAPL, 100.50, 100}  +  10250.75
//     →  Position{TSLA, 150.25, 50}   +   7500.00     ← collision chain
//
//[1]  empty
//[2]  empty
//...
//[7]  →  Position{NVDA, 99.99, 200}   +  25000.00     ← single element
//...
//[10] empty




