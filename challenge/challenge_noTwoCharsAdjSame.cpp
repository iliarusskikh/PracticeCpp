//Rearrange characters in a String such that no two adjacent characters are same

//Given a string s with lowercase repeated characters, the task is to rearrange characters in a string so that no two adjacent characters are the same. If it is not possible to do so, then print empty string ("").

//[Approach 2] Using Greedy - O(n) Time and O(n) Space

//The idea is to fill all the even positions of the result string first, with the highest frequency character. If there are still some even positions remaining, fill them first. Once even positions are done, then fill the odd positions. This way, it can be ensured that no two adjacent characters are the same.


//Follow the given steps to solve the problem:
//
//Calculate the frequencies of every character in the input string.
//If a character with a maximum frequency has a frequency greater than (n + 1) / 2, then return an empty string, as it is not possible to construct the required string.
//Now fill the even index positions with the maximum frequency character, if some even positions are remaining then first fill them with remaining characters.
//Then fill odd index positions with the remaining characters.
//Return the constructed string.


// C++ program to rearrange characters in a string
// so that no two adjacent characters are same.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to rearrange character of a string
// so that no two adjacent characters are same
string rearrangeString(string &s) {
    int n = s.length();
    int mxCnt = 0;
    char ch = '#';

    // Store frequencies of all characters in string
    unordered_map<char, int> freq;
    for (int i = 0; i < n; i++) {
        freq[s[i]]++;
        
        if (freq[s[i]] > mxCnt) {
            mxCnt = freq[s[i]];
            ch = s[i];
        }
    }
    
    // Check if the result is possible or not
    if (mxCnt > ((n+1)/2))
        return "";
    
    // Filling the most frequently occurring char at
    // even indices
    int ind = 0;
    while (mxCnt > 0) {
        s[ind] = ch;
        ind = ind + 2;
        mxCnt--;
    }
    freq[ch] = 0;

    // Filling rest of the characters first at even positions,
    // then odd positions.
    for (char ch = 'a'; ch <= 'z'; ch++) {

        while (freq[ch] > 0) {
            
            // Switch to odd, when all even positions were filled
            ind = (ind >= n) ? 1 : ind;
            s[ind] = ch;
            ind += 2;
            freq[ch]--;
        }
    }
    
    return s;
}

int main() {
    string s = "aaabc";
    cout << rearrangeString(s);
    return 0;
}
