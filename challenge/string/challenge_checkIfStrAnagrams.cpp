//Check if two Strings are Anagrams of each other
//Given two non-empty strings s1 and s2 of lowercase letters, determine if they are anagrams — i.e., if they contain the same characters with the same frequencies.


//Input: s1 = “geeks”  s2 = “kseeg”
//Output: true
//Explanation: Both the string have same characters with same frequency. So, they are anagrams.


//[Expected Approach 1] Using Hash Map or Dictionary - O(n + m) Time and O(1) Space

//The idea is to use a hash map or dictionary count the frequency of each character in both the input strings. If the frequency of every character matches in both strings, then the strings are anagrams.

//    vector<int> freq(26, 0);


#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool areAnagrams(string &s1, string &s2) {
    
    if(s1.size() != s2.size()){
        return false;
    }
    
    // create a hashmap to store character frequencies
    unordered_map<char, int> charCount;
    
    // count frequency of each character in string s1
    for(char ch: s1)
        charCount[ch] += 1;
  
    // Count frequency of each character in string s2
    for(char ch: s2)
        charCount[ch] -= 1;
  
    // check if all frequencies are zero
    for (auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    
    string s1 = "geeks";
    string s2 = "kseeg";
    
    if(areAnagrams(s1, s2)){
        cout << "true";
    }
    else{
        cout << "false";
    }
    
    return 0;
}
