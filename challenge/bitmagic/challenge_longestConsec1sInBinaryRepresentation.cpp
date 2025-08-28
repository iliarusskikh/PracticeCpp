//Length of the Longest Consecutive 1s in Binary Representation
//
//Input: N = 14
//Output: 3
//Explanation: The binary representation of 14 is 1110.

//The idea is based on the concept that the AND of bit sequence with a left shifted by 1 version of itself effectively removes the trailing 1 from every sequence of consecutive 1s.

//11101111   (x)
//
//& 11011110   (x << 1)
//---------------------------
//11001110   (x & (x << 1))

//Time Complexity: O(X), Here X is the length of binary representation of N.
/*
#include<bits/stdc++.h>
using namespace std;

int maxConsecutiveOnes(int x)
{
    // Initialize result
    int count = 0;

    // Count the number of iterations to
    // reach x = 0.
    while (x!=0)
    {
        // This operation reduces length
        // of every sequence of 1s by one.
        x = (x & (x << 1));

        count++;
    }

    return count;
}

// Driver code
int main()
{
    // Function Call
    cout << maxConsecutiveOnes(14) << endl;
    cout << maxConsecutiveOnes(222) << endl;
    return 0;
}
*/




//Time Complexity: O(log X), Here X is the length of binary representation of N


#include <iostream>
#include <bitset>
#include <string>
using namespace std;

int main() {
    int num = 222;

    // Convert the integer to its binary representation as a string
    string binary = bitset<32>(num).to_string();
    int count = 0;
    int maxCount = 0;

    // Loop through the binary string to find the longest consecutive 1s
    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == '1') {
            count++;
            if (count > maxCount) {
                maxCount = count;
            }
        } else {
            count = 0;
        }
    }

    // Print the result
    cout << "The length of the longest consecutive 1s in the binary representation is: " << maxCount << endl;

    return 0;
}
