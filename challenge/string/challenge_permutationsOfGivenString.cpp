//Permutations of given String
//Given a string s, the task is to return all permutations of a given string in lexicographically sorted order.
//Duplicate arrangement can exist
//Input:  s = "ABC"
//Output: "ABC", "ACB", "BAC", "BCA", "CAB", "CBA"
//
//Input: s = "XY"
//Output: "XY", "YX"
//
//Input: s = "AAA"
//Output: "AAA", "AAA", "AAA", "AAA", "AAA", "AAA"


//Time Complexity: O(n * n!)
//Auxiliary Space: O(n!)

// C++ Program to generate all unique
// permutations of a string
#include <bits/stdc++.h>
using namespace std;

// Recursive function to generate
// all permutations of string s
void recurPermute(int index, string &s, vector<string> &ans) {

    // Base Case - end of string
    if (index == s.size()) {
        ans.push_back(s);
        return;
    }

    // Swap the current index with all possible indices and recur
    for (int i = index; i < s.size(); i++) {
        swap(s[index], s[i]);
        recurPermute(index + 1, s, ans);
        swap(s[index], s[i]);
    }
}

// Function to find all unique permutations
vector<string> findPermutation(string &s) {

    vector<string> ans;    // Stores the final answer
    //unordered_set<char> use it for unique permutations
    recurPermute(0, s, ans);

    sort(ans.begin(), ans.end());    // sort the resultant vector
    return ans;
}

int main() {
    string s = "ABC";
    vector<string> res = findPermutation(s);
    for(auto x: res) {
        cout << x << " ";
    }
    return 0;
}


/*-------------------------------------------------------*/
#include <cctype>   // for std::tolower

sort(ans.begin(), ans.end(), [](const string& a, const string& b) {
    return lexicographical_compare(
        a.begin(), a.end(),
        b.begin(), b.end(),
        [](char c1, char c2) { return tolower(c1) < tolower(c2); }
    );
});

//length then alpha
sort(ans.begin(), ans.end(), [](const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    }
    return a < b;
});

//sort(ans.begin(), ans.end(), greater<string>());
