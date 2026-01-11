#include <iostream>
#include <array>    // For std::array
#include <vector>   // For std::vector
#include <string>   // For std::string

int main() {
    // =====================================
    // 1. Built-in Static Arrays (C-style)
    // =====================================
    // These are fixed-size, allocated on stack (or globally), size must be compile-time constant.
    // Pros: Simple, fast. Cons: No bounds checking, decays to pointers, no size info.
    
    const int staticSize = 5;  // Compile-time constant
    int staticArr[staticSize] = {1, 2, 3, 4, 5};  // Declaration and initialization
    
    // Accessing elements (no bounds checking - can cause undefined behavior if out-of-range)
    std::cout << "Static array element at index 0: " << staticArr[0] << std::endl;
    
    // Size: Must use sizeof (bytes) / sizeof(element), no built-in size()
    size_t staticLen = sizeof(staticArr) / sizeof(staticArr[0]);
    std::cout << "Static array size: " << staticLen << std::endl;
    
    // Looping (manual or range-based for C++11+)
    for (int i = 0; i < staticLen; ++i) {
        std::cout << staticArr[i] << " ";
    }
    std::cout << std::endl;
    
    // Multidimensional static array
    int multiStatic[2][3] = {{1, 2, 3}, {4, 5, 6}};
    std::cout << "Multi-static [1][2]: " << multiStatic[1][2] << std::endl;  // 6
    
    // Passing to functions: Decays to pointer, loses size info
    // void printStatic(int arr[], size_t size);  // Need to pass size separately

    // =====================================
    // 2. std::array (Fixed-Size, Static-Sized STL Array)
    // =====================================
    // From <array>. Fixed size at compile-time, like static arrays, but with STL features.
    // Pros: Bounds checking (at()), iterators, size(), doesn't decay to pointer.
    // Cons: Size fixed, no resizing (use std::vector for dynamic).
    
    // Declaration: Template params are type and size (size must be compile-time constant)
    std::array<int, 5> stdArr = {1, 2, 3, 4, 5};  // Initialization (C++11 uniform init)
    
    // Or explicit:
    // std::array<int, 5> stdArrExplicit;
    // stdArrExplicit[0] = 1;  // etc.
    
    // Accessing elements
    std::cout << "std::array element at index 0: " << stdArr[0] << std::endl;  // [] no check
    std::cout << "With bounds check: " << stdArr.at(1) << std::endl;  // at() throws std::out_of_range if invalid
    
    // Size: Built-in size() method (constexpr, compile-time)
    std::cout << "std::array size: " << stdArr.size() << std::endl;  // 5
    std::cout << "Empty? " << stdArr.empty() << std::endl;  // 0 (false)
    
    // Front/back access
    std::cout << "Front: " << stdArr.front() << ", Back: " << stdArr.back() << std::endl;  // 1, 5
    
    // Iterators (STL-compatible: begin(), end(), rbegin(), etc.)
    std::cout << "Iterating std::array: ";
    for (auto it = stdArr.begin(); it != stdArr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop (C++11+)
    std::cout << "Range-based: ";
    for (int& elem : stdArr) {  // & for reference, to modify if needed
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Filling
    stdArr.fill(10);  // Set all elements to 10
    std::cout << "After fill: " << stdArr[0] << std::endl;  // 10
    
    // Swapping with another array (same type/size)
    std::array<int, 5> swapArr = {6, 7, 8, 9, 10};
    stdArr.swap(swapArr);
    std::cout << "After swap: " << stdArr[0] << std::endl;  // 6
    
    // Data pointer: raw access if needed (like C array)
    int* rawPtr = stdArr.data();
    std::cout << "Raw data[0]: " << rawPtr[0] << std::endl;
    
    // Multidimensional std::array (nested)
    std::array<std::array<int, 3>, 2> multiStd = {{{1, 2, 3}, {4, 5, 6}}};
    std::cout << "Multi-std [1][2]: " << multiStd[1][2] << std::endl;  // 6
    
    // Passing to functions: Passed by value (copy) or reference, size preserved
    // void printStd(const std::array<int, 5>& arr);  // Recommended: const ref to avoid copy
    
    // Comparison operators: ==, !=, <, etc. (lexicographical)
    if (stdArr == swapArr) {
        std::cout << "Arrays equal" << std::endl;
    } else {
        std::cout << "Arrays not equal" << std::endl;  // This will print
    }
    
    // Tuple interface (std::get, std::tuple_size, etc. for structured bindings in C++17+)
    // auto [a, b, c, d, e] = stdArr;  // C++17

    //creating arrays in the heap - dynamic allocation - specific size
    int* another = new int[5]; //cannot applly size calc, as it would measure pointer size
    delete[] another;
    
    // =====================================
    // 3. Dynamic Arrays (std::vector)
    // =====================================
    // For comparison: Resizable, dynamic allocation.
    // Use when size isn't known at compile-time or needs to change.
    
    std::vector<int> dynVec = {1, 2, 3};  // Initial size 3
    std::cout << "Dynamic vector size: " << dynVec.size() << std::endl;
    
    // Resizing/growing
    dynVec.push_back(4);  // Add element, may reallocate
    dynVec.resize(5);     // Resize to 5, default-construct new elements
    dynVec.shrink_to_fit();  // Optional: Reduce capacity to size
    
    // Capacity vs. size
    std::cout << "Size: " << dynVec.size() << ", Capacity: " << dynVec.capacity() << std::endl;
    
    // Insert/erase
    dynVec.insert(dynVec.begin() + 1, 10);  // Insert 10 at index 1
    dynVec.erase(dynVec.begin()+3);           // Remove first element
    
    // Similar access: [], at(), front(), back(), iterators, etc.
    std::cout << "Dynamic [0]: " << dynVec[0] << std::endl;
    
    // Multidimensional: std::vector<std::vector<int>>
    std::vector<std::vector<int>> multiDyn = {{1, 2}, {3, 4, 5}};  // Jagged (uneven rows ok)
    
    // Emplace for efficiency (construct in place)
    dynVec.emplace_back(6);  // No temporary - not a single copy constructor!!!
    
    // Reserve to avoid reallocations
    dynVec.reserve(10);  // Pre-allocate space to avoid additional copies
    //use empalceback instead of push_back

    dynVec.clear();//entire array
    // =====================================
    // Key Differences Summary (in comments)
    // =====================================
    // - Static built-in: Simplest, but unsafe, no STL.
    // - std::array: Fixed-size like static, but safe, STL-compatible, no overhead.
    // - std::vector: Dynamic size, resizable, some overhead for growth.
    // Use std::array when size is fixed and known; vector otherwise.
    // For very large fixed arrays, std::array or static to avoid heap.
    
    return 0;
}
