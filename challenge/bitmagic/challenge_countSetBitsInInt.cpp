//Input : n = 13
//Output : 3
//Binary representation of 13 is 1101 and has 3 set bits

//Time Complexity: O(logn)
// C++ program to demonstrate __builtin_popcount()
#include <iostream>
using namespace std;

int main()
{
    cout << __builtin_popcount(4) << endl;
    cout << __builtin_popcount(15);

    return 0;
}
