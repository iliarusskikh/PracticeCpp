/*
//[Naive Approach] Sorting - O(n × log(n)) Time and O(1) Space
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sort012(vector<int> &arr) {
    
    // standard sorting function
    sort(arr.begin(), arr.end());
}

int main() {
    vector<int> arr = {0, 1, 2, 0, 1, 2};
    
    sort012(arr);

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    return 0;
}
*/

/*
//[Better Approach] Counting 0s, 1s and 2s. Time Complexity: O(2 × n),Auxiliary Space: O(1)
#include <iostream>
#include <vector>
using namespace std;

void sort012(vector<int> &arr) {
    int n = arr.size();
    int c0 = 0, c1 = 0, c2 = 0;

    // count 0s, 1s and 2s
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0)
            c0 += 1;
        else if (arr[i] == 1)
            c1 += 1;
        else
            c2 += 1;
    }

    int idx = 0;
    
    // place all the 0s
    for (int i = 0; i < c0; i++)
        arr[idx++] = 0;

    // place all the 1s
    for (int i = 0; i < c1; i++)
        arr[idx++] = 1;

    // place all the 2s
    for (int i = 0; i < c2; i++)
        arr[idx++] = 2;
}

int main() {
    vector<int> arr = { 0, 1, 2, 0, 1, 2 };
    sort012(arr);

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    return 0;
}
*/


//[Expected Approach] Dutch National Flag Algorithm - One Pass - O(n) Time and O(1) Space

#include <iostream>
#include <vector>

using namespace std;

void sort012(vector<int>&arr, int n)
{
    int lo = 0;//0s
    int mid = 0;//move it
    int hi = n-1; //2s
    
    while(mid <= hi)
    {
        if (arr[mid] == 0)
        {
            swap(arr[lo++], arr[mid++]);
        } else if(arr[mid] == 1)
        {
            mid++;
        } else
        {
            swap(arr[mid], arr[hi-1]);
        }
    }
}

int main() {
    vector<int> arr = { 0, 1, 2, 0, 1, 2 };
    int n = arr.size();
    
    // sort the array in-place
    sort012(arr, n);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    
    return 0;
}
