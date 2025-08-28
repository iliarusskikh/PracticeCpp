//[Approach 1] Recursive approach - O(n) Time and O(n) Space
/*
#include <iostream>
#include <vector>
using namespace std;

// Helper function that takes array and size, used for recursion
bool isSortedHelper(vector<int>& arr, int n) {
    if (n == 0 || n == 1)
        return true;
    return arr[n - 1] >= arr[n - 2] && isSortedHelper(arr, n - 1);
}

// Main function to check if array is sorted, only takes array as input
bool isSorted(vector<int>& arr) {
    return isSortedHelper(arr, arr.size());
}

int main() {
    vector<int> arr = { 10, 20, 30, 40, 50 };
    cout << (isSorted(arr) ? "true\n" : "false\n");
    return 0;
}
*/


//[Approach 2] Using Built-in Methods (Applicable for C++ and Python Only) - O(n) Time and O(1) Space
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool isSorted(vector<int> &arr){
    
    // is_sorted() is a built-in method
    if(is_sorted(arr.begin(), arr.end()))
    return true;
    
    return false;
}

int main() {
    
    vector<int> arr = { 10, 20, 30, 40, 50 };
    if(isSorted(arr))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    return 0;
}

/*
 //[Approach 2] Iterative approach - O(n) Time and O(1) Space
 #include <iostream>
 #include <vector>
 using namespace std;

 bool isSorted(vector<int>& arr) {
     
     // Iterate over the array and check if
     // every element is greater than or
     // equal to previous element.
     for (int i = 1; i < arr.size(); i++)
         if (arr[i - 1] > arr[i])
             return false;

     return true;
 }

 int main() {
     vector<int> arr = { 10, 20, 30, 40, 50 };
     cout << (isSorted(arr) ? "true\n" : "false\n");
     return 0;
 }
 */
