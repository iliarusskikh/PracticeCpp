//Find duplicates in O(n) time and O(n) extra space

//Given an array arr[] of n elements that contains elements from 0 to n-1, with any of these numbers appearing any number of times. The task is to find the repeating numbers.


//Input: n = 7, arr[] = [1, 2, 3, 6, 3, 6, 1]
//Output: 1, 3, 6
//Explanation: The numbers 1 , 3 and 6 appears more than once in the array.
//
//Input : n = 5, arr[] = [1, 2, 3, 4 ,3]
//Output: 3
//Explanation: The number 3 appears more than once in the array.


// C++ code to find duplicates in an array
// using hashmap

#include <bits/stdc++.h>
using namespace std;

vector<int> findDuplicates(vector<int> &arr) {

    // Step 1: Create an empty unordered map to store
    // element frequencies
    int n = arr.size();
    unordered_map<int, int> freqMap;
    vector<int> result;

    // Step 2: Iterate through the array and count
    // element frequencies
    for (int i = 0; i < n; i++) {
        freqMap[arr[i]]++;
    }

    // Step 3: Iterate through the hashmap to find duplicates
    for (auto &entry : freqMap) {
        if (entry.second > 1) {
            result.push_back(entry.first);
        }
    }

    // Step 4: If no duplicates found, add -1 to the result
    if (result.empty()) {
        result.push_back(-1);
    }

    // Step 6: Return the result vector containing
    // duplicate elements or -1
    return result;
}

int main() {
    vector<int> arr = {1, 6, 5, 2, 3, 3, 2};

    vector<int> duplicates = findDuplicates(arr);

    for (int element : duplicates) {
        cout << element << " ";
    }

    return 0;
}
