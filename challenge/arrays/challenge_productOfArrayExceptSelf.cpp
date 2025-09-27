//Product of Array Except Self

//[Efficient Approach] Using Product Array - O(n) Time and O(1) Space

//The idea is to handle two special cases of the input array: when it contains zero(s) and when it doesn't.

//If the array has no zeros, product of array at any index (excluding itself) can be calculated by dividing the total product of all elements by the current element.
//
//However, division by zero is undefined, so if there are zeros in the array, the logic changes. If there is exactly one zero, the product for that index will be the product of all other non-zero elements, while the elements in rest of the indices will be zero.
//If there are more than one zero, the product for all indices will be zero, since multiplying by zero results in zero.

#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the product of all elements
// except the current element
vector<int> productExceptSelf(vector<int> &arr) {
    int zeros = 0, idx = -1;
    int prod = 1;

    // Count zeros and track the index of the zero
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == 0) {
            zeros++;
            idx = i;
        } else {
            prod *= arr[i];
        }
    }

    vector<int> res(arr.size(), 0);

    // If no zeros, calculate the product for all elements
    if (zeros == 0) {
        for (int i = 0; i < arr.size(); i++)
            res[i] = prod / arr[i];
    }
    // If one zero, set product only at the zero's index
    else if (zeros == 1)
        res[idx] = prod;

    return res;
}

int main() {
    vector<int> arr = {10, 3, 5, 6, 2};
    vector<int> res = productExceptSelf(arr);

    for (int val : res)
        cout << val << " ";
}
