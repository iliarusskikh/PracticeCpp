//First negative integer in every window of size k

//Given an array and a positive integer k, find the first negative integer for each window(contiguous subarray) of size k. If a window does not contain a negative integer, then print 0 for that window.


//[Better Approach] Sliding Window with Deque technique - O(n) time and O(k) space

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// Function to find the first negative integer
// in every window of size k
vector<int> firstNegInt(vector<int>& arr, int k) {
    deque<int> dq;
    vector<int> res;
    int n = arr.size();

    // Process the first window of size k
    for (int i = 0; i < k; i++) {
        if (arr[i] < 0) {
            dq.push_back(i);
        }
    }

    // Process the rest of the elements
    for (int i = k; i < n; i++) {
        
        // If there is any negative number in the window, add it to the result
        if (!dq.empty()) {
            res.push_back(arr[dq.front()]);
        } else {
            res.push_back(0);
        }

        // Remove elements which are out of this window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Add the current element if it is negative
        if (arr[i] < 0) {
            dq.push_back(i);
        }
    }

    // For the last window, process it separately
    if (!dq.empty()) {
        res.push_back(arr[dq.front()]);
    } else {
        res.push_back(0);
    }

    return res;
}

int main() {
    vector<int> arr = {12, -1, -7, 8, -15, 30, 16, 28};
    int k = 3;

    // Get the result from the function
    vector<int> result = firstNegInt(arr, k);

    // Print the result in the required format
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
