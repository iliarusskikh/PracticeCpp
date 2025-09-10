//Longest Repeating Subsequence

//Given a string s, the task is to find the length of the longest repeating subsequence, such that the two subsequences don't have the same string character at the same position, i.e. any ith character in the two subsequences shouldn't have the same index in the original string.

//
//Input: s= "abc"
//Output: 0
//Explanation: There is no repeating subsequence
//
//Input: s= "aab"
//Output: 1
//Explanation: The two subsequence are 'a'(0th index) and 'a'(1th index). Note that 'b' cannot be considered as part of subsequence as it would be at same index in both.


//Using Recursion - O(2^n) time and O(n) space

// C++ program to find longest
// repeating subsequence using recursion

#include <bits/stdc++.h>
using namespace std;

int findLongestRepeatingSubsequence(int i, int j, string &s) {

    // base case
    if (i == 0 || j == 0)
        return 0;

    // If characters match and their
    // indices are different
    if (s[i - 1] == s[j - 1] && i != j) {
        return 1 + findLongestRepeatingSubsequence(i - 1, j - 1, s);
    }

    // Else make two recursive calls. Check from different parts of the code
    return max(findLongestRepeatingSubsequence(i - 1, j, s),
               findLongestRepeatingSubsequence(i, j - 1, s));
}

int longestRepeatingSubsequence(string s) {
  
    int n = s.length();
    return findLongestRepeatingSubsequence(n, n, s);
}

int main() {
  
    string s = "AABEBCDD";
    int res = longestRepeatingSubsequence(s);
    cout << res;

    return 0;
}
