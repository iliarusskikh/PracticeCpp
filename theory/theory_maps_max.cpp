#include <iostream>
#include <map>
#include <algorithm>

int main() {
    // Example map with int keys and int values
    std::map<int, int> m = {{1, 10}, {2, 30}, {3, 20}, {4, 50}, {5, 40}};

    // Find the key-value pair with the maximum value
    auto max_pair = *std::max_element(m.begin(), m.end(),
                                      [](const std::pair<const int, int>& i,
                                         const std::pair<const int, int>& j) {
                                          return i.second < j.second;
                                      });

    // Print the result
    std::cout << "Key-value pair with maximum value: {"
              << max_pair.first << ", " << max_pair.second << "}\n";

    // Print all pairs for reference
    std::cout << "All pairs:\n";
    for (const auto& pair : m) {
        std::cout << "{" << pair.first << ", " << pair.second << "}\n";
    }

    return 0;
}


/*
 #include <iostream>
 #include <map>
 #include <algorithm>

 int main() {
     // Example map with int keys and int values
     std::map<int, int> m = {{1, 10}, {2, 30}, {3, 20}, {4, 50}, {5, 40}};

     // Find the key-value pair with the maximum value using auto
     auto max_pair = *std::max_element(m.begin(), m.end(),
                                       [](const auto& i, const auto& j) {
                                           return i.second < j.second;
                                       });

     // Print the result
     std::cout << "Key-value pair with maximum value: {"
               << max_pair.first << ", " << max_pair.second << "}\n";

     // Print all pairs for reference
     std::cout << "All pairs:\n";
     for (const auto& pair : m) {
         std::cout << "{" << pair.first << ", " << pair.second << "}\n";
     }

     return 0;
 }
 */
