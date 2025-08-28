//Input: a[] = [-5, 3, 6, 12, 15], b[] = [-12, -10, -6, -3, 4, 10]
//Output: 3
//Explanation: The merged array is [-12, -10, -6, -5 , -3, 3, 4, 6, 10, 12, 15]. So the median of the merged array is 3.


//[Naive Approach] Using Sorting - O((n + m) × log (n + m)) Time and O(n + m) Space
//
//a[] = [ -5, 3, 6, 12, 15 ], b[] = [ -12, -10, -6, -3, 4, 10 ]
//
//After concatenating them in a third array: c[] = [ -5, 3, 6, 12, 15, -12, -10, -6, -3, 4, 10]
//Sort c[] = [ -12, -10, -6, -5, -3, 3, 4, 6, 10, 12, 15 ]
//As the length of c[] is odd, so the median is the middle element = 3

/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double medianOf2(vector<int>& a, vector<int>& b) {
  
    // merge both the arrays
    vector<int> c(a.begin(), a.end());
    c.insert(c.end(), b.begin(), b.end());

    // sort the concatenated array
    sort(c.begin(), c.end());
    
    int len = c.size();
      
      // if length of array is even
    if (len % 2 == 0)
        return (c[len / 2] + c[len / 2 - 1]) / 2.0;
  
      // if length of array is odd
      else
        return c[len / 2];
}

int main() {
    vector<int> a = { -5, 3, 6, 12, 15 };
    vector<int> b = { -12, -10, -6, -3, 4, 10 };

    cout << medianOf2(a, b) << endl;
    return 0;
}
*/

//[Expected Approach] Using Binary Search - O(log min(n, m)) Time and O(1) Space
//The approach is similar to the Binary Search approach of Median of two sorted arrays of same size with the only difference that here we apply binary search on the smaller array instead of a[].

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

double medianOf2(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();
    
      // if a[] has more elements, then call medianOf2
      // with reversed parameters
    if (n > m)
        return medianOf2(b, a);
  
    int lo = 0, hi = n;
    while (lo <= hi) {
        int mid1 = (lo + hi) / 2;
        int mid2 = (n + m + 1) / 2 - mid1;

        // find elements to the left and right of
        // partition in a[]
        int l1 = (mid1 == 0 ? INT_MIN : a[mid1 - 1]);
        int r1 = (mid1 == n ? INT_MAX : a[mid1]);

        // find elements to the left and right of
        // partition in b[]
        int l2 = (mid2 == 0 ? INT_MIN : b[mid2 - 1]);
        int r2 = (mid2 == m ? INT_MAX : b[mid2]);

        // if it is a valid partition
        if (l1 <= r2 && l2 <= r1) {
          
              // if the total elements are even, then median is
              // the average of two middle elements
            if ((n + m) % 2 == 0)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
          
              // if the total elements are odd, then median is
             // the middle element
            else
                return max(l1, l2);
        }

        // check if we need to take lesser elements from a[]
        if (l1 > r2){
            hi = mid1 - 1;
        }
        // check if we need to take more elements from a[]
        else{
            lo = mid1 + 1;
        }
    }
    return 0;
}

int main() {
    
    vector<int> a = { -5, 3, 6, 12, 15 };
    vector<int> b = { -12, -10, -6, -3, 4, 10 };
    cout << medianOf2(a, b);
    
    return 0;
}
