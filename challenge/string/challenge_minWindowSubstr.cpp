//Smallest window in a String containing all characters of other String

//Given two strings s and p, the task is to find the smallest substring in s that contains all characters of p, including duplicates. If no such substring exists, return "". If multiple substrings of the same length are found, return the one with the smallest starting index.


//Input: s = "timetopractice", p = "toc"
//Output: toprac
//Explanation: "toprac" is the smallest substring in which "toc" can be found.


//[Expected Approach] Using Window Sliding - O(n) Time and O(1) Space:



#include <iostream>
#include <string>
#include <vector>
using namespace std;

string smallestWindow(string s, string p) {
    // If s is shorter than p, no solution possible
    if (s.length() < p.length()) return "";
    
    // Arrays to store character counts (ASCII size 256)
    vector<int> pCount(256, 0), sCount(256, 0);
    
    // Count characters in pattern p
    for (char c : p) pCount[c]++;
    
    int start = 0, matched = 0, minLen = INT_MAX, startIdx = -1;
    
    // Slide window over s
    for (int end = 0; end < s.length(); end++) {
        // Add character at end of window
        sCount[s[end]]++;
        
        // If current char is in p and count is sufficient, increment matched
        if (pCount[s[end]] > 0 && sCount[s[end]] <= pCount[s[end]]) matched++;
        
        // If all characters of p are matched
        if (matched == p.length()) {
            // Shrink window from start while valid
            while (sCount[s[start]] > pCount[s[start]] || pCount[s[start]] == 0) {
                sCount[s[start]]--;
                start++;
            }
            
            // Update smallest window if current is smaller
            int currLen = end - start + 1;
            if (currLen < minLen) {
                minLen = currLen;
                startIdx = start;
            }
        }
    }
    
    // Return empty string if no valid window found
    return startIdx == -1 ? "" : s.substr(startIdx, minLen);
}

int main() {
    string s = "timetopractice", p = "toc";
    cout << smallestWindow(s, p) << endl; // Output: toprac
    return 0;
}
