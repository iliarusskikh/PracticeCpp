//2 Sum - Count pairs with given sum

//Given an array arr[] of n integers and a target value, find the number of pairs of integers in the array whose sum is equal to target.

//Input: arr[] = [1, 5, 7, -1, 5], target = 6
//Output:  3
//Explanation: Pairs with sum 6 are (1, 5), (7, -1) & (1, 5).

//[Better Approach] Using Two Pointers Technique - O(nlogn) Time and O(1) Space

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countPairs(vector<int> &arr, int target) {
    int res = 0;
    int n = arr.size();
    int left = 0, right = n - 1;
    
    // Sort the array before applying
    // two-pointer technique
    sort(arr.begin(), arr.end());
    while (left < right) {
      
        // If sum is greater
        if (arr[left] + arr[right] < target)
            left++;

        // If sum is lesser
        else if (arr[left] + arr[right] > target)
            right--;

        // If sum is equal
        else {
          
            int cnt1 = 0, cnt2 = 0;
            int ele1 = arr[left], ele2 = arr[right];
          
            // Count frequency of first element of the pair
            while (left <= right and arr[left] == ele1) {
                left++;
                cnt1++;
            }
          
            // Count frequency of second element of the pair
            while(left <= right and arr[right] == ele2) {
                right--;
                cnt2++;
            }
           
            // If both the elements are same, then count of
            // pairs = the number of ways to choose 2
            // elements among cnt1 elements
            if(ele1 == ele2)
                res += (cnt1 * (cnt1 - 1))/2;
          
            // If the elements are different, then count of
            // pairs = product of the count of both elements
            else
                res += (cnt1 * cnt2);
        }
    }
    return res;
}

int main() {
    vector<int> arr = {1, 5, 7, -1, 5};
    int target = 6;

    cout << countPairs(arr, target);

    return 0;
}
