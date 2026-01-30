//std::iota fills a range (e.g., array, vector) with consecutive values starting from a given number. Requires <numeric> and <iterator>
#include <iostream>
#include <numeric>    // for std::iota
#include <vector>     // for std::vector
#include <iterator>   // for std::ostream_iterator

int main() {
    std::vector<int> arr(5);  // Size 5

    // Fill with 10, 11, 12, 13, 14
    std::iota(arr.begin(), arr.end(), 10);

    std::cout << "Filled array: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}
