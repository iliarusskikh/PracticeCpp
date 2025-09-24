//Maximum Product Subarray

//Given an array arr[] consisting of positive, negative, and zero values, find the maximum product that can be obtained from any contiguous subarray of arr[].

//Input: arr[] = [-2, 6, -3, -10, 0, 2]
//Output: 180
//Explanation: The subarray with maximum product is [6, -3, -10] with product = 6 * (-3) * (-10) = 180.


//Step By Step Approach:
//
//Initialize three variables: currMax, currMin, and maxProd with the first element of the array.
//Loop through the array from index 1 to end to evaluate every position’s contribution.
//For each index, calculate the temporary maximum using max of current value, current × currMax, and current × currMin.
//Update currMin using min of current value, current × currMax, and current × currMin.
//Assign currMax to the previously computed temporary maximum value.
//Update maxProd by comparing it with the updated currMax value.
//Finally, return maxProd which stores the maximum product of any subarray.



#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxProduct(vector<int> &arr) {

      int n = arr.size();
      
    // max product ending at the current index
    int currMax = arr[0];

    // min product ending at the current index
    int currMin = arr[0];

    // Initialize overall max product
    int maxProd = arr[0];
  
    // Iterate through the array
    for (int i = 1; i < n; i++) {
          
          // Temporary variable to store the maximum product ending
          // at the current index
        int temp = max({ arr[i], arr[i] * currMax,
                                            arr[i] * currMin });
        
          // Update the minimum product ending at the current index
          currMin = min({ arr[i], arr[i] * currMax,
                                            arr[i] * currMin });
      
          // Update the maximum product ending at the current index
        currMax = temp;
      
          // Update the overall maximum product
        maxProd = max(maxProd, currMax);
    }
    return maxProd;
}

int main() {
    vector<int> arr = { -2, 6, -3, -10, 0, 2 };
    cout << maxProduct(arr);
    return 0;
}
