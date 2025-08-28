// C++ Code to find Median of two Sorted Arrays of
// Same Size using Sorting
/*
#include <bits/stdc++.h>
using namespace std;

// Function to find the median of two sorted arrays of equal size
double getMedian(vector<int>& a, vector<int>& b) {
  
    // Concatenate
    vector<int> c(a.begin(), a.end());
    c.insert(c.end(), b.begin(), b.end());

    // Sort the concatenated array
    sort(c.begin(), c.end());
    
    // Calculate and return the median
    int n = c.size();
      
    int mid1 = n / 2;
    int mid2 = mid1 - 1;
    return (c[mid1] + c[mid2]) / 2.0;
}

int main() {
    vector<int> a = { 1, 12, 15, 26, 38 };
    vector<int> b = { 2, 13, 17, 30, 45 };

    cout << getMedian(a, b) << endl;
    return 0;
}*/




// C++ Program to find the median of merged sorted
// array using Binary Search

#include <bits/stdc++.h>
using namespace std;

// function to find median of merged sorted array
double getMedian(vector<int> &a, vector<int> &b) {
        
      int n = a.size();
      
      // We can take [0...n] number of elements from a[]
      int low = 0, high = n;
  
      while(low <= high) {
        
          // Take mid1 elements from a
          int mid1 = (low + high) / 2;
          
          // Take mid2 elements from b
          int mid2 = n - mid1;
      
          // Find elements to the left and right of partition in a
          int l1 = (mid1 == 0 ? INT_MIN : a[mid1 - 1]);
          int r1 = (mid1 == n ? INT_MAX : a[mid1]);
      
          // Find elements to the left and right of partition in b
          int l2 = (mid2 == 0 ? INT_MIN : b[mid2 - 1]);
          int r2 = (mid2 == n ? INT_MAX : b[mid2]);
      
          // If it is a valid partition
          if(l1 <= r2 && l2 <= r1)
            return (max(l1, l2) + min(r1, r2)) / 2.0;
          
          // If we need to take lesser elements from a
          if(l1 > r2)
              high = mid1 - 1;
      
          // If we need to take more elements from a
          else
              low = mid1 + 1;
    }
      return 0;
}

int main() {
    vector<int> a = { 1, 12, 15, 26, 38 };
    vector<int> b = { 2, 13, 17, 30, 45 };

    cout << getMedian(a, b) << endl;

    return 0;
}
