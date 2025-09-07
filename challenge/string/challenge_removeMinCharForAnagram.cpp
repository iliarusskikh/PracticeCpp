//Remove minimum characters so that two strings become anagram


//Approach - Using 2 Frequency Arrays - O(n + m) time and O(1) space

// C++ program to find minimum number of characters
// to be removed to make two strings anagram.
#include<bits/stdc++.h>
using namespace std;

// function to calculate minimum numbers of characters
// to be removed to make two strings anagram
int remAnagram(string& s1, string& s2) {
    
    vector<int> cnt(26, 0);

    // increment frequency of each character in first string
    for (char ch: s1) {
        cnt[ch-'a']++;
    }

    // decrement frequency of each character in second string
    for (char ch: s2) {
        cnt[ch-'a']--;
    }

    // traverse count array to find number of characters
    // to be removed
    int ans = 0;
    
    for (int i=0; i<26; i++)
        ans += abs(cnt[i]);
        
    return ans;
}

int main() {
    string str1 = "bcadeh", str2 = "hea";
    cout << remAnagram(str1, str2);
    return 0;
}


/*
 
 // C++ program to find minimum number of characters
 // to be removed to make two strings anagram.
 #include<bits/stdc++.h>
 using namespace std;

 // function to calculate minimum numbers of characters
 // to be removed to make two strings anagram
 int remAnagram(string& s1, string& s2) {
     
     unordered_map<char, int> map;

     // increment frequency of each character in first string
     for (char ch: s1) {
         map[ch]++;
     }

     // decrement frequency of each character in second string
     for (char ch: s2) {
         map[ch]--;
     }

     // traverse count array to find number of characters
     // to be removed
     int ans = 0;
     
     for (auto p: map)
         ans += abs(p.second);
         
     return ans;
 }

 int main() {
     string str1 = "bcadeh", str2 = "hea";
     cout << remAnagram(str1, str2);
     return 0;
 }
 */
