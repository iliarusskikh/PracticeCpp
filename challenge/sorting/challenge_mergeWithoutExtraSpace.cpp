//Input: a[] = [2, 4, 7, 10], b[] = [2, 3]
//Output: a[] = [2, 2, 3, 4], b[] = [7, 10]
//Explanation: Combined sorted array = [2, 2, 3, 4, 7, 10], array a[] contains smallest 4 elements: 2, 2, 3 and 4, and array b[] contains remaining 2 elements: 7, 10.

//[Naive Approach] Using Insert of Insertion Sort | Time Complexity: O(m * n)
/*#include <iostream>
#include <vector>
using namespace std;

void mergeArrays(vector<int>& a, vector<int>& b) {
      
      // Traverse b[] starting from the last element
    for (int i = b.size() - 1; i >= 0; i--) {
          
        // If b[i] is smaller than the largest element of a[]
        if (a.back() > b[i]) {
          
              // Place b[i] in the correct position in a[],
            // and move last element of a[] to b[]
            int last = a.back();
            int j = a.size() - 2;
            while (j >= 0 && a[j] > b[i]) {
                a[j + 1] = a[j];
                j--;
            }
          
            a[j + 1] = b[i];
            b[i] = last;
        }
    }
}

int main() {
    vector<int> a = {1, 5, 9, 10, 15, 20};
    vector<int> b = {2, 3, 8, 13};
    mergeArrays(a, b);

    for (int ele: a)
        cout << ele << " ";
    cout << "\n";
    for (int ele: b)
        cout << ele << " ";
    return 0;
}
*/

//[Better Approach 2] By Swap and Sort Time Complexity: O((m+n) + m*log(m) + n*log(n))
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mergeArrays(vector<int>& a, vector<int>& b) {
    int i = a.size() - 1, j = 0;

      // swap smaller elements from b[]
      // with larger elements from a[]
    while (i >= 0 && j < b.size() && a[i] > b[j]) {
          swap(a[i--], b[j++]);
    }

    // Sort both arrays
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
}

int main() {
    vector<int> a = {1, 5, 9, 10, 15, 20};
    vector<int> b = {2, 3, 8, 13};
    mergeArrays(a, b);

    for (int ele: a)
        cout << ele << " ";
    cout << "\n";
    for (int ele: b)
        cout << ele << " ";
    return 0;
}
