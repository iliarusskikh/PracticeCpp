//Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
//Output: 5
//Explanation: arr[5] = 8 is a peak element because arr[4] < arr[5] > arr[6].

//[Naive Approach] Using Linear Search - O(n) Time and O(1) Space
/*
#include <iostream>
#include <vector>
using namespace std;

int peakElement(vector<int> &arr) {
    int n = arr.size();
  
    for(int i = 0; i < n; i++) {
        bool left = true;
        bool right = true;
      
        // Check for element to the left
        if(i > 0 && arr[i] <= arr[i - 1])
            left = false;
      
        // Check for element to the right
        if(i < n - 1 && arr[i] <= arr[i + 1])
            right = false;
      
        // If arr[i] is greater than its left as well as
        // its right element, return its index
        if(left && right) {
            return i;
        }
    }
    return 0;
}

int main() {
    vector<int> arr = {1, 2, 4, 5, 7, 8, 3};
    cout << peakElement(arr);
    return 0;
}
*/


//[Expected Approach] Using Binary Search - O(log n) Time and O(1) Space

#include <iostream>
#include <vector>
using namespace std;

int peakElement(vector<int> &arr) {
    int n = arr.size();
  
    // If there is only one element, then it's a peak
    if (n == 1)
        return 0;
        
    // Check if the first element is a peak
    if (arr[0] > arr[1])
        return 0;
        
    // Check if the last element is a peak
    if (arr[n - 1] > arr[n - 2])
        return n - 1;
    
    // Search Space for binary Search
    int lo = 1, hi = n - 2;
    
    while(lo <= hi) {
        int mid = lo + (hi - lo)/2;
        
        // If the element at mid is a
        // peak element return  mid
        if(arr[mid] > arr[mid - 1]
                       && arr[mid] > arr[mid + 1])
            return mid;
        
        // If next neighbor is greater, then peak
        // element will exist in the right subarray
        if(arr[mid] < arr[mid + 1])
            lo = mid + 1;
            
        // Otherwise, it will exist in left subarray
        else
            hi = mid - 1;
    }
    
    return 0;
}

int main() {
    vector<int> arr = {1, 2, 4, 5, 7, 8, 3};
    cout << peakElement(arr);
    return 0;
}
