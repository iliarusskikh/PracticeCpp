// C++ program to find the k largest elements in the
// array using min heap

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Function to find the k largest elements in the array
vector<int> kLargest(vector<int> &arr, int k)
{
    // Min Priority Queue (Min-Heap) with first k
    // elements of the array
    priority_queue<int, vector<int>, greater<int>> minH(arr.begin(), arr.begin() + k);

    // Travers n - k elements
    for (int i = k; i < arr.size(); i++) {

          
          // If the top of heap is less than the arr[i]
          // then remove top element and insert arr[i]
          if(minH.top() < arr[i]) {
             minH.pop();
              minH.push(arr[i]);
        }
    }

    vector<int> res;
  
      // Min heap will contain only k
      // largest element
    while (!minH.empty()) {
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

