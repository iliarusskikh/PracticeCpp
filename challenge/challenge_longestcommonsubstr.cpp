#include <bits/stdc++.h>
using namespace std;

// Returns length of the longest common substring 
// ending with the last characters. We mainly find
// Longest common suffix.
int LCSuf(const string& s1, const string& s2, int m, int n) {
    if (m == 0 || n == 0 || s1[m - 1] != s2[n - 1])
        return 0;
    return 1 + LCSuf(s1, s2, m - 1, n - 1);
}

int maxCommStr(const string& s1, const string& s2) {
    int res = 0;
    
    // Find the longest common substring ending
    // at every pair of characters and take the 
    // maximum of all.
    for (int i = 1; i <= s1.size(); i++) {
        for (int j = 1; j <= s2.size(); j++) {
            res = max(res, LCSuf(s1, s2, i, j));
        }
    }
    return res;
}

int main() {
    string s1 = "geeksforgeeks";
    string s2 = "practicewritegeekscourses";
    cout << maxCommStr(s1, s2) << endl;
    return 0;
}

