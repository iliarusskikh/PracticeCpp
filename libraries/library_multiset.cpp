#include <iostream>
#include <set>
#include <string>

//sorts elements
//duplicate elements


/*
 std::multiset<int> ms;

 // Insert (allows duplicates)
 ms.insert(42);
 ms.emplace(42);           // constructs in place

 // Count occurrences
 size_t cnt = ms.count(42);           // how many times 42 appears

 // Find range of equal elements
 auto [beginIt, endIt] = ms.equal_range(42);
 for (auto it = beginIt; it != endIt; ++it) { ... }

 // Erase one occurrence
 ms.erase(ms.find(42));               // erases only one 42

 // Erase ALL occurrences
 ms.erase(42);                        // erases every 42

 // Lower/upper bound (useful for range queries)
 auto it = ms.lower_bound(10);        // first >= 10
 auto it2 = ms.upper_bound(20);       // first > 20
 */


struct DescendingOrder{
    bool operator()(int a, int b) const{
        return a>b;
    }
};

int main()
{
    //std::multiset<int, DescendingOrder> num;

    std::multiset<int> numbers;

    // Insert duplicates — multiset allows them
    numbers.insert(5);
    numbers.insert(2);
    numbers.insert(8);
    numbers.insert(5);
    numbers.insert(2);
    numbers.insert(5);

    std::cout << "Content (sorted): ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    // Output: 2 2 5 5 5 8

    std::cout << "Size: " << numbers.size() << "\n";           // 6
    std::cout << "Count of 5: " << numbers.count(5) << "\n";   // 3
    std::cout << "Count of 7: " << numbers.count(7) << "\n";   // 0

    // Range of equal elements
    auto [first5, after5] = numbers.equal_range(5);
    std::cout << "All 5s: ";
    
    for (auto it = first5; it != after5; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    
    //.equal_range(2); find range of all 2s - pair of iterators for range of equal elements
    return 0;
}



/*
 
 #include <iostream>
 #include <set>
 #include <string>

 struct Task {
     int priority;
     std::string description;

     // We need operator< for default ordering
     bool operator<(const Task& other) const {
         return priority < other.priority;   // lower number = higher priority
     }
 };

 int main()
 {
     // Default ordering: by priority ascending (smaller = comes first)
     std::multiset<Task> tasks;

     tasks.insert({3, "Fix login bug"});
     tasks.insert({1, "Deploy to production"});
     tasks.insert({3, "Update README"});
     tasks.insert({2, "Review PR #45"});
     tasks.insert({1, "Security patch"});

     std::cout << "Tasks by priority (lowest number = highest priority):\n";
     for (const auto& t : tasks) {
         std::cout << "[" << t.priority << "] " << t.description << "\n";
     }
     // Output:
     // [1] Deploy to production
     // [1] Security patch
     // [2] Review PR #45
     // [3] Fix login bug
     // [3] Update README

     return 0;
 }
 */
