/*
 Dynamic programming patters
 - Memoization
 - Tabulation
 - Constant Transition
 - Grid
 - Two Sequences
 - nterval DP
 - Non-Constant Transition
 - Knapsack-like
 */

//# Number of palindromic substrings

#include <string>

int countSubstrings(std::string s) {
    int n = s.length();
    int total_palindromes = 0;

    // Iterate through all possible centers
    for (int i = 0; i < n; ++i) {
        // Case 1: Odd length palindromes (center is a single character like "a")
        int left1 = i, right1 = i;
        while (left1 >= 0 && right1 < n && s[left1] == s[right1]) {
            total_palindromes++;
            left1--;
            right1++;
        }

        // Case 2: Even length palindromes (center is between two characters like "aa")
        int left2 = i, right2 = i + 1;
        while (left2 >= 0 && right2 < n && s[left2] == s[right2]) {
            total_palindromes++;
            left2--;
            right2++;
        }
    }

    return total_palindromes;
}

