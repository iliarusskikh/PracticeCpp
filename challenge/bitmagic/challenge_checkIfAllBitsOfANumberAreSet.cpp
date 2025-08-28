//Method 2: If n = 0, then answer is 'No'. Else add 1 to n. Let it be num = n + 1. If num & (num - 1) == 0, then all bits are set, else all bits are not set.

// C++ implementation to check whether every
// digit in the binary representation of the
// given number is set or not
#include <bits/stdc++.h>
using namespace std;

// function to check if all the bits are set
// or not in the binary representation of 'n'
string areAllBitsSet(int n)
{
    // all bits are not set
    if (n == 0)
        return "No";

    // if true, then all bits are set
    if (((n + 1) & n) == 0)
        return "Yes";

    // else all bits are not set
    return "No";
}

// Driver program to test above
int main()
{
    int n = 7;
    cout << areAllBitsSet(n);
    return 0;
}
