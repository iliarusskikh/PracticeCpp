# C++ Hash Tables – Complete Cheat Sheet
---
## What is hashing?
- A hash function is a pure function that takes a key (any type) and returns a fixed-size integer (in C++ usually size_t = 64-bit on modern machines).

## 1. Core Concept & Why So Efficient

- **Hash table** = array of **buckets** + **hash function** that maps `key → bucket index` (`hash(key) % bucket_count()`).
- **Average O(1)** insert / lookup / erase because:
  - Hash computation is O(1) (or O(length) for strings).
  - Bucket lookup is O(1).
  - Collision chains are kept **short** (good hash → uniform distribution → average chain length ≈ load factor).
- **Amortized** guarantee: rehash cost is spread over many insertions.
- **Worst case O(n)** only with pathological hash (all keys collide) or adversarial input.

**C++ STL implementation (`std::unordered_map` / `std::unordered_set`)**  
- **Separate chaining** (mandated by the standard).  
- Internal: array of buckets, each bucket is a singly-linked list of nodes.  
- Collisions resolved by: same-hash → same bucket → linear search with `key_equal`.

---

## 2. `std::unordered_map` vs `std::unordered_set`

| Feature              | `unordered_map<Key, T>`                  | `unordered_set<Key>`                  |
|----------------------|------------------------------------------|---------------------------------------|
| Stores               | `pair<const Key, T>`                     | Key only                              |
| `operator[]` / `at`  | Yes                                      | No                                    |
| Typical use          | Symbol → price/volume, ID → order        | Unique IDs, visited nodes             |

Both share identical hash/bucket/re-hash mechanics.

---

## 3. Performance Guarantees (C++ Standard)

| Operation                          | Average | Worst  | Notes                              |
|------------------------------------|---------|--------|------------------------------------|
| `insert`/`emplace` / `try_emplace` | O(1)    | O(n)   | Amortized                          |
| `erase` /`find`/`count`/`contains` |C++20 O(1)| O(n) | —                           |
| `operator[]`                       | O(1)    | O(n)   | Inserts default if missing         |
| `rehash` / `reserve`               | O(n)    | O(n)   | Full rebuild                       |
| Iteration                          | O(n)    | O(n)   | Arbitrary order, changes on rehash |

**Iterator invalidation rules** (critical):  
- Rehash (`reserve`, `rehash`, insert that triggers growth) → **all iterators invalidated**.  
- Single `erase(it)` → only that iterator invalidated.

---

## 4. Load Factor & Rehashing (The Magic Behind Amortized O(1))

- `load_factor() = size() / bucket_count()` (O(1))
- `max_load_factor()` default = **1.0**
- When `size() > bucket_count() * max_load_factor()` → automatic rehash to ~2× buckets
- `reserve(n)` → **best practice** before bulk insert (ensures no rehash for next `n` elements)

> “`m.reserve(1e6)` before inserting 1M elements turns worst-case O(n log n) into guaranteed amortized O(n)”  

---

## 5. Bucket Interface (Shows You Understand Internals)

```cpp
size_t bc = m.bucket_count();
size_t b  = m.bucket(key);                    // which bucket this key lands in
size_t bs = m.bucket_size(b);                 // elements in that bucket
for (auto it = m.begin(b); it != m.end(b); ++it) { ... }  // local iterators
```

---

## 6. `std::hash` Requirements & Built-ins

- Must be `noexcept`, deterministic within one run.
- Provided for: all arithmetic, enums, pointers, `std::string`, `string_view`, `chrono::*`, smart pointers, etc.
- **NOT** provided for: `pair`, `tuple`, user structs, `const char*` (hashes pointer!).

---

## 7. Custom Hash + Equality for User Types (Classic)

### Option A – Template params (cleanest)
```cpp
struct Position { double px; int qty; std::string sym; };

struct PosHash {
    size_t operator()(const Position& p) const noexcept {
        size_t h1 = std::hash<std::string>{}(p.sym);
        size_t h2 = std::hash<double>{}(p.px);
        size_t h3 = std::hash<int>{}(p.qty);
        h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        h1 ^= h3 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        return h1;
    }
};

struct PosEqual {
    bool operator()(const Position& a, const Position& b) const {
        return a.sym == b.sym && std::abs(a.px - b.px) < 1e-9 && a.qty == b.qty;
    }
};

std::unordered_map<Position, double, PosHash, PosEqual> book;
```

### Option B – Specialize `std::hash` (requires `operator==`)
```cpp
template<> struct std::hash<Position> { /* ... */ };
```

**Floating-point gotcha**: Use epsilon in equality.  
**Anti-DoS safe hash**: Use SplitMix64 + random seed (widely used in competitive code).

**Pair / Tuple example**:
```cpp
template<class T1, class T2>
struct std::hash<std::pair<T1,T2>> {
    size_t operator()(const std::pair<T1,T2>& p) const {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};
```

---

## 8. C++ Version Highlights

- **C++11**: 
- **C++17**: `try_emplace`, `insert_or_assign`, node extract/merge
- **C++20**: `contains()`, `erase_if()`
- **C++23/26**: `insert_range`, `constexpr` containers

---

## 9. `unordered_` vs `map` / `set` (Decision Table)

| Need                        | Choose `unordered_` | Choose ordered (`map`/`set`) |
|-----------------------------|---------------------|------------------------------|
| Fastest lookups             | Yes                 | No (`log n`)                 |
| No order required           | Yes                 | Waste                        |
| Range queries / `lower_bound` | No                | Yes                          |
| Predictable worst-case      | No                  | Yes                          |
| Memory / cache              | Usually better      | Tree nodes overhead          |

---

## 10. Common Questions & Answers

1. **“How does rehash work?”**  
   → Allocates new larger bucket array → re-computes hash for every element → O(current size).

2. **“Why is it amortized O(1)?”**  
   → Each rehash doubles buckets → each element is rehashed O(log n) times in its lifetime.

3. **“What happens with bad hash?”**  
   → All elements in one bucket → O(n). Mention DoS attacks and safe hashes.

4. **“How to pre-size?”**  
   → `m.reserve(expected_size);`

5. **“Can I modify key while in map?”**  
   → No → UB (keys are `const`).

---

## 11. Best Practices

- Always `reserve()` when you know size.
- Prefer `emplace` / `try_emplace`.

- For symbols → `std::string_view` with transparent hash/equal.
- std::string as key → copies the string data into the map node.
- std::string_view → stores only pointer + length → no copy, lower memory, faster.

- In hot paths → consider `absl::flat_hash_map` or `ska::flat_hash_map` (open addressing, faster) but know they are non-standard.
- Profile hot buckets: `for(size_t i=0; i<m.bucket_count(); ++i) if(m.bucket_size(i)>10) ...`

---

**One-liner **:
> `unordered_map` = O(1) average via hashing + chaining + controlled load factor. Master `reserve`, custom `std::hash`, and rehash semantics → instant senior quant credibility.

---
