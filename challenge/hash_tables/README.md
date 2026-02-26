# C++ Hash Tables – Practical Examples


## Core Concepts – Quick Reference

### Hash Table Basics

- Separate chaining (linked lists per bucket) – standard-mandated
- Average O(1) lookup/insert/erase when load factor controlled & hash good
- Worst case O(n) when all keys collide → one giant linked list

### Important Member Functions

```cpp
m.reserve(n);               // best practice – pre-allocate for ~n elements
m.rehash(n);                // force at least n buckets (rarely needed)
m.bucket_count();           // current number of buckets
m.load_factor();            // size() / bucket_count()
m.max_load_factor(0.7f);    // tune – lower = fewer collisions, more memory
m.bucket(key);              // which bucket this key would go to
m.bucket_size(b);           // how many elements in bucket b

```


### Iterator Invalidation Rules 

- Rehash (automatic or reserve/rehash call) → all iterators invalidated
- erase(iterator) → only that iterator invalidated
- Never store raw iterators across operations that may cause rehash

#### Custom Hash + Equal – Golden Rules

- Hash must be noexcept, deterministic in one run
- Equal keys → must produce same hash
- Good distribution → minimize long chains

Common combine pattern (used in Boost/Abseil/etc.):

size_t h = std::hash<T1>{}(v1);
h ^= std::hash<T2>{}(v2) + 0x9e3779b9 + (h << 6) + (h >> 2);


When to prefer alternatives

Scenario Recommended choice Reason
Need ordering / range queriesstd::map / std::setlog n guaranteed
Very hot path, millions of ops/secabsl::flat_hash_map or ska::flat_hash_mapOpen addressing, better cache
Known small & fixed key setPerfect hash / array + enumZero collisions, compile-time
Symbol lookups (strings)std::unordered_map <std::string, T, ...> with transparent hasherAvoid string copies with string_view


### Memory 

std::unordered_map itself stores almost everything on the heap.

The map object (the small control structure with pointers to buckets, size counters, load factor etc.) lives where you declare it — usually on the stack if it's a local variable, or inside another object if it's a member.
But all the actual data (buckets array + all nodes with keys and values) lives on the heap.

- Allocation cost
Every insert / emplace → at least one heap allocation (new node)
Expensive when inserting millions one-by-one without reserve()

- Cache performance
Nodes are scattered on heap → poor locality (pointer chasing)
Main reason flat/open-addressing maps (absl, ska) are often 20–100% faster

- Memory usage
High overhead: ~24–64 bytes per element (node + pointers + padding) + buckets
Much higher than std::vector or dense arrays

- Rehash
Allocates new bigger bucket array + new nodes → many allocations at once
That's why reserve() before bulk insert is critical

- Lifetime
Data lives as long as the map object — map destruction frees all heap nodes
No manual delete needed (RAII)


### FAQ 

- “Does unordered_map store data on heap or stack?”
→ “The control structure is small and can be on stack, but buckets and all key-value nodes are dynamically allocated on the heap.”
- “Why does it matter in performance?”
→ “Heap allocations are slow, scattered nodes hurt cache locality — that's why pre-reserving capacity and using flat hash maps can give big speedups in hot paths.”
- “Any way to avoid heap?”
→ “For very small fixed-size cases you could use a sorted array or perfect hash, but for dynamic data (order books, risk maps) heap is unavoidable with unordered_map.”



### Implications
- Deletion is expensive in open addressing → tombstones hurt probe chains → many fast maps discourage erase or use lazy deletion

- String keys — transparent hashing + string_view still saves huge memory/cycles

- Very small maps (< 64 elements) → often std::vector + linear search or sorted vector faster

- Very large keys (big structs) → node-based (chaining) better than flat (less movement during Robin Hood swaps)

- SIMD metadata lookup (SwissTable style) → wins big on modern CPUs (AVX2/AVX-512)

- Hash DoS is still real → never use hash of untrusted input without per-process seed (most std libs now do this automatically)




# QUICK LEARN

## 1. Core Container: std::unordered_map / unordered_set
- Implementation — separate chaining (array of buckets, each bucket is a forward-linked list of nodes)
- Average complexity — O(1) for lookup / insert / erase / count (amortized)
- Worst case — O(n) when many keys collide → degenerate to linked list
- Order — unordered (arbitrary iteration order, changes on rehash)
- Iterator invalidation — rehash invalidates all iterators; single-element erase invalidates only iterators to that element

## 2. Template Parameters

template<
    class Key,
    class T,                            // for map; ignored in set
    class Hash      = std::hash<Key>,
    class KeyEqual  = std::equal_to<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> class unordered_map;

Most common customizations:
Provide custom Hash + KeyEqual for user-defined types
Rarely change allocator (polymorphic / arena / pmr in C++17+)

## 3. std::hash<Key> Requirements (Named Requirement: Hash)
Must satisfy:
- Function object: size_t operator()(const Key&) const
- Deterministic within one program run
- Equal keys must produce equal hash values (very important!)
- Should be noexcept (strongly recommended since C++11)
- Good avalanche / uniformity → minimize collisions

Standard provides specializations for:
- All integer types (int, long, uint64_t, …)
- float, double, long double
- std::string, std::string_view (C++17+)
- std::nullptr_t, pointers, enums, std::optional, std::variant, std::bitset, chrono types, etc.

### No built-in for: std::pair, std::tuple, arrays, custom structs → you must implement!

## 4. Custom Hash – Most Common Patterns
### Style 1 – separate hasher + equal (cleanest)

```
struct MyKey {
 uint64_t a; 
 int b; 
 std::string s; 
};


struct MyHash {
    size_t operator()(const MyKey& k) const noexcept {
        size_t h = std::hash<uint64_t>{}(k.a);
        h ^= std::hash<int>{}(k.b) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<std::string>{}(k.s) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

struct MyEqual {
    bool operator()(const MyKey& x, const MyKey& y) const {
        return x.a == y.a && x.b == y.b && x.s == y.s;
    }
};

std::unordered_map<MyKey, Value, MyHash, MyEqual> m;

```

### Style 2 – specialize std::hash in namespace std (requires operator==)
```
namespace std {
    template<> struct hash<MyKey> {
        size_t operator()(const MyKey& k) const noexcept 
        { /* ... */ }
    };
}

```

Golden-ratio mixer (0x9e3779b9) is still very common in 2026 (from Boost).

- Modern alternatives (better quality / faster):

absl::Hash<T> (Abseil) — very high quality
xxh3 / wyhash / t1ha — extremely fast non-cryptographic hashes
SplitMix64 + per-run seed (anti-hash-flooding)


## 5. Load Factor & Rehashing

max_load_factor() default = 1.0
load_factor() = size() / bucket_count()
When size() > bucket_count() × max_load_factor() → automatic rehash (~2× buckets)
reserve(n) — best practice before bulk insert

m.reserve(1'000'000);   // ensures ~no rehash for next 1M inserts
reserve(n) ≈ rehash(ceil(n / max_load_factor()))


## 6. Bucket API
```
size_t bc = m.bucket_count();
size_t b  = m.bucket(key);
size_t len = m.bucket_size(b);          // elements in this bucket
for (auto it = m.begin(b); it != m.end(b); ++it) { /* local iteration */ }
```

Average chain length ≈ load factor → aim for 0.7–1.3

## 7. Floating-point & String Gotchas

double hashing — bit representation (NaN issues, +0 vs -0)
Equality for floats — use epsilon in custom KeyEqual
const char* — hashes pointer, not content → dangerous
Prefer std::string_view + transparent hasher (C++20 is_transparent)

C++
```
struct str_hash {
    using is_transparent = void;
    size_t operator()(std::string_view sv) const noexcept { /* ... */ }
};

std::unordered_map<std::string, T, str_hash, std::equal_to<>> m;
```

8. vs std::map / std::set


Need                    Prefer unordered_map/set    Prefer map/set  
Fastest average lookup              Yes (O(1))          No (O(log n))
No order needed                     Yes                 Waste
Range queries / lower_bound         No                  Yes
Predictable worst-case              No                  Yes
Memory overhead                 Usually lower           Higher (tree nodes)

## 9. Modern Alternatives

Popular high-speed implementations (often 1.5–4× faster than std::unordered_map):
- absl::flat_hash_map (SwissTable)
Open addressing + SIMD
8-bit hash fingerprints + group loading (SIMD)
2–3.5×
General purpose, Google's production

- martinus::unordered_dense
Robin Hood + separate value array
8-bit hash bits, index indirection
2–4×
Often fastest in 2024–2025 benches

- martinus/robin_hood::unordered_flat_map
Robin Hood hashing
Linear probing with displacement stealing
1.8–3×
Classic fast & simple Robin Hood

- ska::flat_hash_map / bytell_hash_map
Robin Hood / linear
Byte-wise metadata
1.5–3×
Extremely cache-friendly


## Why binary trees (std::map, std::set) have high overhead

Node-based structure
Every element lives in its own heap-allocated node.
Three pointers per node (red-black tree)
left child
right child
parent (almost all implementations use parent pointers)
→ 24 bytes just for pointers (64-bit)

Color bit (red/black) → usually 1 byte + padding → often 8 bytes more
Per-element allocation overhead
malloc/free metadata (~16–32 bytes per allocation on many allocators)
Alignment/padding to satisfy alignof(pair<const K,V>)

No bulk allocation
Unlike vector, tree nodes are scattered → terrible cache locality + fragmentation

### Result: even for tiny key+value (e.g. int→int = 8 bytes), you easily pay 5–8× more memory.

In contrast - std::vector<pair<K,V>> would use one single contiguous block
