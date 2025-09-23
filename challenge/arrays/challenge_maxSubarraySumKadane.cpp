//Maximum Subarray Sum - Kadane's Algorithm

//Given an integer array arr[], find the subarray (containing at least one element) which has the maximum possible sum, and return that sum.
//Note: A subarray is a continuous part of an array.


//Input: arr[] = [2, 3, -8, 7, -1, 2, 3]
//Output: 11
//Explanation: The subarray [7, -1, 2, 3] has the largest sum 11.


//[Expected Approach] Using Kadane's Algorithm - O(n) Time and O(1) Space

//The idea of Kadane's algorithm is to traverse over the array from left to right and for each element, find the maximum sum among all subarrays ending at that element. The result will be the maximum of all these values.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySum(vector<int> &arr) {
    
    // Stores the result (maximum sum found so far)
    int res = arr[0];
    
    // Maximum sum of subarray ending at current position
    int maxEnding = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        
        // Either extend the previous subarray or start
        // new from current element
        maxEnding = max(arr[i], maxEnding + arr[i]);

        // Update result if the new subarray sum is larger
        res = max(res, maxEnding);
    }
    return res;
}

int main() {
    vector<int> arr = {2, 3, -8, 7, -1, 2, 3};
    cout << maxSubarraySum(arr);
    return 0;
}
