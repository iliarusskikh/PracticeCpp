//Permutations of given String
//Given a string s, the task is to return all permutations of a given string in lexicographically sorted order.
//
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

    // Base Case
    if (index == s.size()) {
        ans.push_back(s);
        return;
    }

    // Swap the current index with all
    // possible indices and recur
    for (int i = index; i < s.size(); i++) {
        swap(s[index], s[i]);
        recurPermute(index + 1, s, ans);
        swap(s[index], s[i]);
    }
}

// Function to find all unique permutations
vector<string> findPermutation(string &s) {

    // Stores the final answer
    vector<string> ans;
    //unordered_set<char> use it for unique permutations
    recurPermute(0, s, ans);

    // sort the resultant vector
    sort(ans.begin(), ans.end());

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
