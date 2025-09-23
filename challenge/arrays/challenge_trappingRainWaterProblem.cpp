//Trapping Rain Water Problem

//Given an array arr[] of size n consisting of non-negative integers, where each element represents the height of a bar in an elevation map and the width of each bar is 1, determine the total amount of water that can be trapped between the bars after it rains.


//Input: arr[] = [3, 0, 2, 0, 4]
//Output: 7
//Explanation: We trap 0 + 3 + 1 + 3 + 0 = 7 units.



//[Expected Approach] Using Two Pointers - O(n) Time and O(1) Space

//The approach is mainly based on the following facts:
//
//If we consider a subarray arr[left...right], we can decide the amount of water either for arr[left] or arr[right] if we know the left max (max element in arr[0...left-1]) and right max (max element in arr[right+1...n-1].
//If left max is less than the right max, then we can decide for arr[left]. Else we can decide for arr[right]
//If we decide for arr[left], then the amount of water would be left max - arr[left] and if we decide for arr[right], then the amount of water would be right max - arr[right].


#include <iostream>
#include <vector>
using namespace std;

int maxWater(vector<int> &arr) {
    int left = 1; // set it as second element from each edge
    int right = arr.size() - 2; // set it as second element from each edge

    // lMax : Maximum in subarray arr[0..left-1]
    // rMax : Maximum in subarray arr[right+1..n-1]
    int lMax = arr[left - 1];
    int rMax = arr[right + 1]; //default val

    int res = 0;
    while (left <= right) {
      
        // If rMax is smaller, then we can calc the amount of water for arr[right]
        if (rMax <= lMax) {
            res += max(0, rMax - arr[right]);// Add the water for arr[right]
            rMax = max(rMax, arr[right]); // Update right max
            right -= 1; // Update right pointer as we have eval the amount of water for this
        } else {
            res += max(0, lMax - arr[left]);// Add the water for arr[left]
            lMax = max(lMax, arr[left]);// Update left max

            left += 1;// Update left pointer as we have decided water for this
        }
    }
    return res;
}

/*

     *
     *       *
     * *     *
 *   * *     *
 * * * * * _ *

 diagram
 
 */

int main() {
    vector<int> arr = {2, 1, 5, 3, 1, 0, 4};
    cout << maxWater(arr) << endl;
    return 0;
}
