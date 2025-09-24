//Counting Bits
//Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

#include <vector>
using namespace std;

vector<int> countBits(int n) {
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++) {
        ans[i] = __builtin_popcount(i);
    }
    return ans;
}


