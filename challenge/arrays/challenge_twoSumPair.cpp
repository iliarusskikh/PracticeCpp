//Two Sum - Pair with given Sum

//Given an array arr[] of n integers and a target value, check if there exists a pair whose sum equals the target. This is a variation of the 2-Sum problem.

//[Better Approach 2] Sorting and Two-Pointer Technique - O(n × log(n)) time and O(1) space
//
//If the sum equals the target, we’ve found the pair.
//If the sum is less than the target, move the left pointer to the right to increase the sum.
//If the sum is greater than the target, move the right pointer to the left to decrease the sum.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool twoSum(vector<int> &arr, int target){
  
    sort(arr.begin(), arr.end());

    int left = 0, right = arr.size() - 1;

    // Iterate while left pointer
    // is less than right
    while (left < right){
        int sum = arr[left] + arr[right];

        // Check if the sum matches the target
        if (sum == target)
            return true;
        else if (sum < target)
        
        // Move left pointer to the right
            left++;
        else
        
        // Move right pointer to the left
            right--;
    }
    // If no pair is found
    return false;
}

int main(){
    vector<int> arr = {0, -1, 2, -3, 1};
    int target = -2;

    if (twoSum(arr, target))
        cout << "true";
    else
        cout << "false";

    return 0;
}


/*
 
 
 Step By Step Implementations:

 Create an empty Hash Set or Unordered Set
 Iterate through the array and for each number in the array:
 => Calculate the complement (target - current number).
 => Check if the complement exists in the set:
 - If it is, then pair found.
 - If it isn’t, add the current number to the set.
 If the loop completes without finding a pair, return that no pair exists.
 
 
 #include <iostream>
 #include <vector>
 #include <unordered_set>
 using namespace std;

 bool twoSum(vector<int> &arr, int target){
   
     // Create an unordered_set to store the elements
     unordered_set<int> s;

     for (int i = 0; i < arr.size(); i++){

         // Calculate the complement that added to
         // arr[i], equals the target
         int complement = target - arr[i];

         // Check if the complement exists in the set
         if (s.find(complement) != s.end())
             return true;

         // Add the current element to the set
         s.insert(arr[i]);
     }
   
     // If no pair is found
     return false;
 }

 int main(){
     vector<int> arr = {0, -1, 2, -3, 1};
     int target = -2;

     if (twoSum(arr, target))
         cout << "true";
     else
         cout << "false";

     return 0;
 }
 */
