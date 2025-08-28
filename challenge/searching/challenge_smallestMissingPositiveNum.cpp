//Given an unsorted array arr[] with both positive and negative elements, find the smallest positive number missing from the array.
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int missingNumber(vector<int> &arr) {
    
    sort(arr.begin(), arr.end());
    int res = 1;
    for (int i = 0; i < arr.size(); i++) {

        // If we have found 'res' in the array,
        // 'res' is no longer missing, so increment it
        if (arr[i] == res)
            res++;

        // If the current element is larger than 'res',
        // 'res' cannot be found in the array,
        // so it is our final answer
        else if (arr[i] > res)
            break;
    }
    return res;
}

int main() {
    vector<int> arr = {2, -3, 4, 1, 1, 7};

    cout << missingNumber(arr);
    return 0;
}
*/


//[Better approach] Using Visited Array - O(n) Time and O(n) Space
/*#include <iostream>
#include <vector>
using namespace std;

int missingNumber(vector<int> &arr) {
    int n = arr.size();

    // To mark the occurrence of elements
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {

        // if element is in range from 1 to n
        // then mark it as visited
        if (arr[i] > 0 && arr[i] <= n)
            vis[arr[i] - 1] = true;
    }

    // Find the first element which is unvisited
    // in the original array
    for (int i = 1; i <= n; i++) {
        if (!vis[i - 1]) {
            return i;
        }
    }

    // if all elements from 1 to n are visited
    // then n + 1 will be first positive missing number
    return n + 1;
}

int main() {

    vector<int> arr = {2, -3, 4, 1, 1, 7};
    cout << missingNumber(arr);
}

*/
