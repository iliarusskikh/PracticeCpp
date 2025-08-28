//[Alternate Approach - 2] - Using Inbuilt Functions - O(log n) Time and O(1) Space

#include <bits/stdc++.h>
using namespace std;

// Function for finding first and last occurrence of x
vector<int> find(vector<int> arr, int x) {
    int n = arr.size();

    // return index of first number
    // greater than or equal to x
    int first = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

    // return index of first number
    // greater than x
    int last = upper_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;

    // If x is not present
    if (first == n || arr[first] != x) {
        first = -1;
        last = -1;
    }
    vector<int> res = {first, last};
    return res;
}

int main() {
    vector<int> arr = {1, 3, 5, 5, 5, 5, 67, 123, 125};
    int x = 5;
    vector<int> res = find(arr, x);
    cout << res[0] << " " << res[1];
    return 0;
}
