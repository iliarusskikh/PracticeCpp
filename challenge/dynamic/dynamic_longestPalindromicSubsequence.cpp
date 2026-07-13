//# Interval DP
//# Longest Palindromic Subsequence

#include <string>
#include <vector>
#include <algorithm>

int longestPalindromeSubseq(std::string s) {
    int n = s.size();
    if (n == 0) return 0;

    // dp[j] will store the LPS length for the substring s[i...j]
    // next_dp will store the values for the current 'i' iteration
    std::vector<int> dp(n, 0);
    std::vector<int> next_dp(n, 0);

    // Loop backwards for the starting index 'i' (Interval left boundary)
    for (int i = n - 1; i >= 0; --i) {
        next_dp[i] = 1; // Base case: A single character is a palindrome of length 1
        
        // Loop forwards for the ending index 'j' (Interval right boundary)
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                // Outer characters match: add 2 to the inner substring result s[i+1...j-1]
                // dp[j-1] holds the old value of s[i+1...j-1] from the previous 'i' loop
                next_dp[j] = dp[j - 1] + 2;
            } else {
                // Characters mismatch: take the max of shrinking from the left or right
                // dp[j] is s[i+1...j], next_dp[j-1] is s[i...j-1]
                next_dp[j] = std::max(dp[j], next_dp[j - 1]);
            }
        }
        // Move current state to the DP table for the next outer iteration
        dp = next_dp;
    }

    // The full interval s[0...n-1] contains the global answer
    return dp[n - 1];
}


