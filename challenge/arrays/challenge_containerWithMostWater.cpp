//Container with Most Water

//Given an array arr[] of non-negative integers, where each element arr[i] represents the height of the vertical lines, find the maximum amount of water that can be contained between any two lines, together with the x-axis.

//Input: arr[] = [1, 5, 4, 3]
//Output: 6
//Explanation: 5 and 3 are 2 distance apart. So the size of the base = 2. Height of container = min(5, 3) = 3. So total area = 3 * 2 = 6.


//[Expected Approach] Using Two Pointers - O(n) Time and O(1) Space

//The idea is to maintain two pointers: left pointer at the beginning of the array and right pointer at the end of the array. These pointers act as the container's sides so we can calculate the amount of water stored between them using the formula: min(arr[left], arr[right]) * (right - left).
//
//After calculating the amount of water for the given sides, we can have three cases:
//
//arr[left] < arr[right]: This means that we have calculated the water stored for the container of height arr[left], so increment left by 1.
//arr[left] >= arr[right]: This means that we have calculated the water stored for the container of height arr[right], so decrement right by 1.
//Repeat the above process till left is less than right keeping track of the maximum water stored as the result.

#include <vector>
#include <iostream>
using namespace std;

int maxWater(vector<int> &arr) {
    int left = 0, right = arr.size() - 1;
    int res = 0;
    while(left < right) {
        
        // find the water stored in the container between
        // arr[left] and arr[right]
        int water = min(arr[left], arr[right]) * (right - left);
        res = max(res, water);
      
        if(arr[left] < arr[right])
            left += 1;
        else
            right -= 1;
    }
  
    return res;
}

int main() {
    vector<int> arr = {2, 1, 8, 6, 4, 6, 5, 5};
    cout << maxWater(arr);
}
