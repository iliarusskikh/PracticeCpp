// C++ program to find the k largest elements in the
// array using min heap
/*
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Function to find the k largest elements in the array
vector<int> kLargest(vector<int> &arr, int k)
{
    // Min Priority Queue (Min-Heap) with first elements of the array
    priority_queue<int, vector<int>, greater<int> > minH(arr.begin(), arr.begin() + k);

    // Travers n - k elements
    for (int i = k; i < arr.size(); i++)
    {
      // If the top of heap is less than the arr[i]
      // then remove top element and insert arr[i]
      if(minH.top() < arr[i])
      {
        minH.pop();
        minH.push(arr[i]);
      }
    }

    vector<int> res;
  
      // Min heap will contain only k
      // largest element
    while (!minH.empty())
    {
        res.push_back(minH.top());
        minH.pop();
    }
      
      // Reverse the result array, so that all
      // elements are in decreasing order
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    vector<int> arr = {1, 23, 12, 9, 30, 2, 50};
    int k = 3;
  
      vector<int> res = kLargest(arr, k);
      for(int ele : res)
          cout << ele << " ";
      
      return 0;
}
*/




/*
// C++ program to find k largest elements in an
// array using sorting Time Complexity: O(n * log k)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> kLargest(vector<int> &arr, int k) {
  
    // sort the given array in descending order
    sort(arr.begin(), arr.end(), greater<int>());
    
      // store the first k element in result array
    vector<int> res(arr.begin(), arr.begin() + k);
      return res;
}

int main() {
    vector<int>arr = {1, 23, 12, 9, 30, 2, 50};
    int k = 3;
 
    vector<int> res = kLargest(arr, k);
      for(int ele : res)
          cout << ele << " ";
  
      return 0;
}
*/



// C++ program to find the k largest elements in the array
// using partitioning step of quick sort

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to partition the array around a pivot
int partition(vector<int> &arr, int left, int right) {
    
    // Last element is chosen as a pivot.
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
      
          // Elements greater than or equal to pivot
          // are placed in the left side of pivot
        if (arr[j] >= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    
    swap(arr[i], arr[right]);
    
    // The correct sorted position of the pivot
    return i;
}

void quickSelect(vector<int> &arr, int left, int right, int k) {
    if (left <= right) {
        int pivotIdx = partition(arr, left, right);
        
        // Count of all elements in the left part
        int leftCnt = pivotIdx - left + 1;
      
          // If leftCnt is equal to k, then we have
          // found the k largest element
        if (leftCnt == k)
            return;
        
        // Search in the left subarray
        if (leftCnt > k)
            quickSelect(arr, left, pivotIdx - 1, k);
            
        // Reduce the k by number of elements already covered
        // and search in the right subarray
        else
            quickSelect(arr, pivotIdx + 1, right, k - leftCnt);
    }
}

vector<int> kLargest(vector<int> &arr, int k) {
    int n = arr.size();
    quickSelect(arr, 0, n - 1, k);
    
    // First k elements of the array will be the largest
    vector<int> res(arr.begin(), arr.begin() + k);
  
      // Sort the result in descending order
      sort(res.begin(), res.end(), greater<int>());
    return res;
}

int main() {
    vector<int> arr = {1, 23, 12, 9, 30, 2, 50};
    int k = 3;

    vector<int> res = kLargest(arr, k);
    for (int ele : res)
        cout << ele << " ";
    
    return 0;
}
