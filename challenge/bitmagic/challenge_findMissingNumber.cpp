//
//Input: arr[] = [8, 2, 4, 5, 3, 7, 1]
//Output: 6
//Explanation: All the numbers from 1 to 8 are present except 6.


//[Naive Approach] Linear Search for Missing Number - O(n^2) Time and O(1) Space
/*#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int>& arr) {
    int n = arr.size() + 1;

    // Iterate from 1 to n and check
    // if the current number is present
    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] == i) {
                found = true;
                break;
            }
        }

        // If the current number is not present
        if (!found)
            return i;
    }
    return -1;
}

int main() {
    vector<int> arr = {8, 2, 4, 5, 3, 7, 1};
    cout << missingNum(arr) << endl;
    return 0;
}*/


//[Better Approach] Using Hashing - O(n) Time and O(n) Space
/*
#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int> &arr) {

    int n = arr.size() + 1;

    // Create hash array of size n+1
    vector<int> hash(n + 1, 0);

    // Store frequencies of elements
    for (int i = 0; i < n - 1; i++) {
        hash[arr[i]]++;
    }

    // Find the missing number
    for (int i = 1; i <= n; i++) {
        if (hash[i] == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> arr = {8, 2, 4, 5, 3, 7, 1};
    int res = missingNum(arr);
    cout << res << endl;
    return 0;
}
*/



//[Expected Approach 2] Using XOR Operation - O(n) Time and O(1) Space
// XOR of a number with itself is 0 i.e. x ^ x = 0 and the given array arr[] has numbers in range [1, n]. This means that the result of XOR of first n natural numbers with the XOR of all the array elements will be the missing number. To do so, calculate XOR of first n natural numbers and XOR of all the array arr[] elements, and then our result will be the XOR of both the resultant values.
#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int>& arr) {
    int n = arr.size() + 1;
    int xor1 = 0, xor2 = 0;

    // XOR all array elements
    for (int i = 0; i < n - 1; i++) {
        xor2 ^= arr[i];
    }

    // XOR all numbers from 1 to n
    for (int i = 1; i <= n; i++) {
        xor1 ^= i;
    }

    // Missing number is the XOR of xor1 and xor2
    return xor1 ^ xor2;
}

int main() {
    vector<int> arr = {8, 2, 4, 5, 3, 7, 1};
    int res = missingNum(arr);
    cout << res << endl;
    return 0;
}
