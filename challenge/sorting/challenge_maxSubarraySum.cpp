//Maximum Subarray Sum - Kadane's Algorithm
//
//Input: arr[] = [2, 3, -8, 7, -1, 2, 3]
//Output: 11
//Explanation: The subarray [7, -1, 2, 3] has the largest sum 11.

//[Naive Approach] By iterating over all subarrays - O(n^2) Time and O(1) Space
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySum(vector<int> &arr) {
    int res = arr[0];
  
    // Outer loop for starting point of subarray
      for(int i = 0; i < arr.size(); i++) {
        int currSum = 0;
      
        // Inner loop for ending point of subarray
        for(int j = i; j < arr.size(); j++) {
            currSum = currSum + arr[j];
          
            // Update res if currSum is greater than res
            res = max(res, currSum);
        }
    }
    return res;
}

int main() {
    vector<int> arr = {2, 3, -8, 7, -1, 2, 3};
    cout << maxSubarraySum(arr);
    return 0;
}
*/


//[Expected Approach] Using Kadane's Algorithm - O(n) Time and O(1) Space
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
        
        // Either extend the previous subarray or start new from current element
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
