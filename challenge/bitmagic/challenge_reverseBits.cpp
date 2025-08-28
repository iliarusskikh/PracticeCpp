// C++ program to reverse actual bits of a given number
#include <iostream>
using namespace std;

int reverseBits(unsigned int n) {
    int ans = 0;

    // traversing bits of 'n' from the right
    while (n > 0) {
        
        // bitwise left shift
        // 'ans' by 1
        ans <<= 1; //create a bit slot

        // if current bit is '1'
        if (n & 1 == 1)
            ans |= 1;

        // bitwise right shift
        // 'n' by 1
        n >>= 1;

    }

    // required number
    return ans;
}

int main() {
    int n = 11;
    cout << reverseBits(n);
    return 0;
}
