//inversion if arr[i] > arr[j] and i < j.
// If the array is already sorted, then the inversion count is 0, but if the array is sorted in reverse order, the inversion count is maximum.

//[Naive Approach] Using Two Nested Loops - O(n^2) Time and O(1) Space
/*
#include <iostream>
#include <vector>
using namespace std;

int inversionCount(vector<int> &arr) {

    int n = arr.size();
    int invCount = 0;
  
    // Loop through the array
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            
            // If the current element is greater
            // than the next, increment the count
            if (arr[i] > arr[j])
                invCount++;
        }
    }
    
    return invCount;
}

int main() {
    vector<int> arr = {4, 3, 2, 1};
    cout << inversionCount(arr) << endl;
    return 0;
}
*/



//[Expected Approach] Using Merge Step of Merge Sort - O(n*log n) Time and O(n) Space
#include <iostream>
#include <vector>
using namespace std;

// This function merges two sorted subarrays arr[l..m] and arr[m+1..r]
// and also counts inversions in the whole subarray arr[l..r]
int countAndMerge(vector<int>& arr, int l, int m, int r) {
  
    // Counts in two subarrays
    int n1 = m - l + 1, n2 = r - m;

    // Set up two vectors for left and right halves
//    vector<int> left(n1), right(n2);
//    for (int i = 0; i < n1; i++)
//        left[i] = arr[i + l];
//    for (int j = 0; j < n2; j++)
//        right[j] = arr[m + 1 + j];

    vector<int> left(arr.begin(), arr.begin() + n1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + m + 1 + n2);

    // Initialize inversion count (or result) and merge two halves
    int res = 0;
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {

        // No increment in inversion count if left[] has a
        // smaller or equal element
        if (left[i] <= right[j])
            arr[k++] = left[i++];
      
        // If right is smaller, then it is smaller than n1-i
          // elements because left[] is sorted
        else {
            arr[k++] = right[j++];
            res += (n1 - i);
        }
    }

    // Merge remaining elements
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];

    return res;
}

// Function to count inversions in the array
int countInv(vector<int>& arr, int l, int r){
    int res = 0;
    if (l < r) {
        int m = (r + l) / 2;

        // Recursively count inversions in the left and
        // right halves
        res += countInv(arr, l, m);
        res += countInv(arr, m + 1, r);

        // Count inversions such that greater element is in the left half and smaller in the right half
        res += countAndMerge(arr, l, m, r);
    }
    return res;
}

int inversionCount(vector<int> &arr) {
      int n = arr.size();
      return countInv(arr, 0, n-1);
}

int main(){
    vector<int> arr = {4, 3, 2, 1};
    
    cout << inversionCount(arr);
    return 0;
}


