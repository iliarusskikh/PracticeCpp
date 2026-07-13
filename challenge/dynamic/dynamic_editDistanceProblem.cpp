//# Edit Distance Problem
// Given two strings, find the minimum operations to convert one into the other.
// you can insert a character, delete a character, replace a character

// word1 = "horse"
// word2 = "ros"
//Answer: 3 operations
//horse -> rorse (replace)
//rorse -> rose (delete)
//rose -> ros (delete


#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

int minDistance(std::string word1, std::string word2) {
    int m = word1.size();
    int n = word2.size();
    
    // Track the previous and current rows
    std::vector<int> prev(n + 1);
    std::vector<int> curr(n + 1);
    
    // Base Case: Convert an empty word1 to word2 requires 'j' insertions
    std::iota(prev.begin(), prev.end(), 0);
    
    for (int i = 1; i <= m; ++i) {
        // Base Case: Convert word1 of length 'i' to empty word2 requires 'i' deletions
        curr[0] = i;
        
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                // Characters match, no operation needed (take diagonal value)
                curr[j] = prev[j - 1];
            } else {
                // Characters mismatch, choose the minimum of three operations:
                // 1. prev[j]   -> Delete operation from word1
                // 2. curr[j-1] -> Insert operation into word1
                // 3. prev[j-1] -> Replace operation
                curr[j] = 1 + std::min({prev[j], curr[j - 1], prev[j - 1]});
            }
        }
        // Move current row data to previous row for the next iteration
        prev = curr;
    }
    
    return prev[n];
}



