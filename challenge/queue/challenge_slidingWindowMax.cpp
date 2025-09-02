//Sliding Window Maximum (Maximum of all subarrays of size K)

//Given an array arr[] of integers and an integer k, your task is to find the maximum value for each contiguous subarray of size k. The output should be an array of maximum values corresponding to each contiguous subarray.
//Input: arr[] = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
//Output: [3, 3, 4, 5, 5, 5, 6]
//Explanation:
//1st contiguous subarray = [1 2 3] max = 3
//2nd contiguous subarray = [2 3 1] max = 3


/*
//[Naive Approach] - Using Nested Loops - O(n * k) Time and O(1) Space
#include <iostream>
#include <vector>
using namespace std;

// Method to find the maximum for each
// and every contiguous subarray of size k.
vector<int> maxOfSubarrays(vector<int>& arr, int k) {
    int n = arr.size();

    // to store the results
    vector<int> res;
  
    for (int i = 0; i <= n - k; i++) {
      
        // Find maximum of subarray beginning
        // with arr[i]
        int max = arr[i];
        for (int j = 1; j < k; j++) {
            if (arr[i + j] > max)
                max = arr[i + j];
        }
        res.push_back(max);
    }
  
    return res;
}

int main() {
    vector<int> arr = { 1, 2, 3, 1, 4, 5, 2, 3, 6 };
    int k = 3;
    vector<int> res = maxOfSubarrays(arr, k);
    for (int maxVal : res) {
        cout << maxVal << " ";
    }
    return 0;
}
*/



//[Expected Approach] - Using Deque - O(n) Time and O(k) Space

#include <bits/stdc++.h>
using namespace std;

// Method to find the maximum for each
// and every contiguous subarray of size k.
vector<int> maxOfSubarrays(vector<int>& arr, int k) {

    vector<int> res;    // to store the results
    deque<int> dq(k);    // create deque to store max values

    // Process first k (or first window) elements of array
    for (int i = 0; i < k; ++i) {
      
        // For every element, the previous smaller elements are useless so remove them from dq
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();            // Remove from rear
        }

        dq.push_back(i);        // Add new element at rear of queue
    }

    // Process rest of the elements, i.e., from arr[k] to arr[n-1]
    for (int i = k; i < arr.size(); ++i) {
      
        // The element at the front of the queue is the largest
        // element of previous window, so store it
        res.push_back(arr[dq.front()]);

        // Remove the elements which are out of this window
        while (!dq.empty() && dq.front() <= i - k) {
          
            // Remove from front of queue
            dq.pop_front();
        }

        // Remove all elements smaller than the currently being
        // added element (remove useless elements)
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }

        // Add current element at the rear of dq
        dq.push_back(i);
    }

    // store the maximum element of last window
    res.push_back(arr[dq.front()]);

    return res;
}

int main() {
    vector<int> arr = {1, 3, 2, 1, 7, 3};
    int k = 3;
    vector<int> res = maxOfSubarrays(arr, k);
    for (int maxVal : res) {
        cout << maxVal << " ";
    }
    return 0;
}



/*
 #include <bits/stdc++.h>
 using namespace std;

 // Method to find the maximum for each
 // and every contiguous subarray of size k.
 vector<int> maxOfSubarrays(const vector<int>& arr, int k) {
     int n = arr.size();

     // to store the results
     vector<int> res;

     // to store the max value
     priority_queue<pair<int, int> > heap;

     // Initialize the heap with the first k elements
     for (int i = 0; i < k; i++)
         heap.push({ arr[i], i });

     // The maximum element in the first window
     res.push_back(heap.top().first);

     // Process the remaining elements
     for (int i = k; i < arr.size(); i++) {

         // Add the current element to the heap
         heap.push({ arr[i], i });

         // Remove elements that are outside the current
         // window
         while (heap.top().second <= i - k)
             heap.pop();

         // The maximum element in the current window
         res.push_back(heap.top().first);
     }

     return res;
 }

 int main() {
     vector<int> arr = { 1, 2, 3, 1, 4, 5, 2, 3, 6 };
     int k = 3;
     vector<int> res = maxOfSubarrays(arr, k);
     for (int maxVal : res) {
         cout << maxVal << " ";
     }
     return 0;
 }
 */
