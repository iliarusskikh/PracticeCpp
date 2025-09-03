//Count number of binary strings without consecutive 1's

//Given a positive integer n, the task is to count all possible distinct binary strings of length n such that there are no consecutive 1's.

//Input: n = 3
//Output: 5
//Explanation: 5 strings are ("000", "001", "010", "100", "101").
//
//Input: n = 2
//Output: 3
//Explanation: 3 strings are ("00", "01", "10").



//Using Recursion - O(2^n) Time and O(n) Space
//
//The idea is to explore two possible choices at each step of building the binary string. When constructing a string of length n, at each index, we have two choices: either place a 0 or place a 1. If we choose to place a 0, we can proceed to the next index. However, if we choose to place a 1, we must ensure that the next index does not contain a 1, so we skip the next index.
//
//Mathematically the recurrence relation will look like the following:
//
//countStrings(i) = countStrings(i+1) + countStrings(i+2)
//
//Base Case:
//
//countStrings(i) = 1, if i >= n.


// C++ program to count number of binary
// strings without consecutive 1's using recursion
#include <bits/stdc++.h>
using namespace std;

int countRecur(int i, int n) {
    
    // Base case
    if (i >= n) return 1;
    
    // If we take 1 at ith index,
    // we cannot have 1 at (i-1)
    int take = countRecur(i+2, n);
    
    // If we skip 1, we can consider
    // 1 at i-1.
    int noTake = countRecur(i+1, n);
    
    return take + noTake;
}

int countStrings(int n) {
    return countRecur(0, n);
}

int main() {
    int n = 3;
    cout << countStrings(n);

    return 0;
}

/*// C++ program to count number of binary
 // strings without consecutive 1's using memoization
 #include <bits/stdc++.h>
 using namespace std;

 int countRecur(int i, int n, vector<int> &memo) {
     
     // Base case
     if (i >= n) return 1;
     
     // If value is memoized
     if (memo[i]!=-1) return memo[i];
     
     // If we take 1 at ith index,
     // we cannot have 1 at (i-1)
     int take = countRecur(i+2, n, memo);
     
     // If we skip 1, we can consider
     // 1 at i-1.
     int noTake = countRecur(i+1, n, memo);
     
     return memo[i] = take + noTake;
 }

 int countStrings(int n) {
     
     vector<int> memo(n, -1);
     return countRecur(0, n, memo);
 }

 int main() {
     int n = 3;
     cout << countStrings(n);

     return 0;
 }*/
