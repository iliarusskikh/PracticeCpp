//Program to find whether a given number is power of 2

//Approach 1: Using Log - O(1) time and O(1) space
/*
#include <iostream>
#include <cmath>
using namespace std;

bool isPowerofTwo(int n) {
    if (n <= 0)
        return false;
    
    // Calculate log base 2 of n
    int logValue = log2(n);
    
    // Check if log2(n) is an integer
    // and 2^(logn) = n
    return pow(2, logValue) == n;
}

int main() {
    int n = 16;
    if (isPowerofTwo(n)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}
*/



//Approach 3: Using Count of Set Bits - O(log n) time and O(1) space

#include <iostream>
using namespace std;

bool isPowerofTwo(int n) {
    if (n <= 0)
        return false;
    
    // Count set bits
    int count = 0;
    while (n > 0) {
        if (n & 1)
            count++;
        n = n >> 1;
    }
    
    // If count of set bits is 1,
    // then n is a power of 2
    return (count == 1);
}

bool isPowerofTwo2(int n) {
    
    // Check if n is positive and n & (n-1) is 0
    return (n > 0) && ((n & (n-1)) == 0); // 0b10000 & 0b01111
}

int main() {
    int n = 16;
    if (isPowerofTwo(n)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}
