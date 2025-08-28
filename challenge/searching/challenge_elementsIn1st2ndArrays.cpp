//For each in 1st array count less than or equal to it in 2nd array

//Given two unsorted arrays a[] and b[]. Both arrays may contain duplicate elements. For each element in a[], find the count of elements in b[] are less than or equal to that element.

//Input: a[] = [1, 2, 3, 4, 7, 9], b[] = [0, 1, 2, 1, 1, 4]
//Output: [4, 5, 5, 6, 6, 6]
//Explanation:
//For a[0] = 1, there are 4 elements in b (0, 1, 1, 1) that are ≤ 1.
//For a[1] = 2, there are 5 elements in b (0, 1, 1, 1, 2) that are ≤ 2.
//For a[2] = 3, there are 5 elements in b that are ≤ 3.
//Similarly, for a[3] = 4, there are 6 elements in b that are ≤ 4, and for a[4] = 7 and a[5] = 9, there are also 6 elements in b that are ≤ 7 and ≤ 9, respectively.

//[Naive Approach] Using Nested Loops - O(n * m) Time and O(n) Space
/*
#include <iostream>
#include <vector>
using namespace std;

vector<int> countLessEq(vector<int>& a, vector<int>& b) {
    
    int n = a.size(), m = b.size();

    // to store the result
    vector<int> res(n);

    // outer loop for each element of a[]
    for (int i = 0; i < n; i++) {
        int count = 0;

        // inner loop for each element of b[]
        for (int j = 0; j < m; j++)
            if (b[j] <= a[i])
                count++;

        res[i] = count;
    }

    return res;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 7, 9};
    vector<int> b = {0, 1, 2, 1, 1, 4};
    vector<int> result = countLessEq(a, b);
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}

*/


//[Better Approach - 1] Using Sorting - O((n + m) * log m) Time and O(n) Space

//The idea is to sort the elements of array b[], then perform a modified binary search on array b[]. For each element x of array a[], find the last index of the largest element smaller than or equal to x in sorted array b[]. The index of the largest element will give the count of elements.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// to perform the binary search
int binarySearch(vector<int> &arr, int x) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

vector<int> countLessEq(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();

    // to store the result
    vector<int> res(n);

    // sort the array b[]
    sort(b.begin(), b.end());

    // outer loop for each element of a[]
    for (int i = 0; i < n; i++) {
        res[i] = binarySearch(b, a[i]);
    }

    return res;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 7, 9};
    vector<int> b = {0, 1, 2, 1, 1, 4};
    vector<int> result = countLessEq(a, b);
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}



//OR

vector<int> countLessEq(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();

    // to store the result
    vector<int> res(n);

    // sort the array b[]
    sort(b.begin(), b.end());

    // outer loop for each element of a[]
    for (int i = 0; i < n; i++) {
        res[i] = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    return res;
}
