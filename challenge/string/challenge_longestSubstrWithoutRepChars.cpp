//Longest Substring Without Repeating Characters

//Given a string s having lowercase characters, find the length of the longest substring without repeating characters.


//The idea is to maintain a window of distinct characters. The window is initialized as single character. We keep extending the window on the right side till we see distinct characters. When we see a repeating character, we remove characters from the left side of the window. We keep track of the maximum length window.


//Initialize two pointers left and right with 0, which define the current window being considered.
//The right pointer moves from left to right, extending the current window.
//If the character at right pointer is not visited, it's marked as visited.
//If the character at right pointer is visited, it means there is a repeating character. The left pointer moves to the right while marking visited characters as false until the repeating character is no longer part of the current window.
//The length of the current window (right - left + 1) is calculated and answer is updated accordingly.

//[Expected Approach 1] Using Sliding Window - O(n) Time and O(1) Space


#include <iostream>
#include <vector>
using namespace std;


int longestUniqueSubstr(string& s) {
    if (s.length() == 0 || s.length() == 1)
        return s.length();

    int res = 0;
    vector<bool>vis(26, false);

    // left and right pointer of sliding window
    int left = 0, right = 0;
    while (right < s.length()) {

        // If character is repeated, move left pointer marking
          // visited characters as false until the repeating
          // character is no longer part of the current window
        while (vis[s[right] - 'a'] == true) {

                vis[s[left] - 'a'] = false;
                left++;
           }

        vis[s[right] - 'a'] = true;

        // The length of the current window (right - left + 1)
        // is calculated and answer is updated accordingly.
        res = max(res, (right - left + 1));
        right++;
    }
    return res;
}

int main() {
    string s = "geeksforgeeks";
    cout << longestUniqueSubstr(s);
    return 0;
}
