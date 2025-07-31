// C++ program to show the different operator functions on
// bitset
#include <bitset>
#include <iostream>

using namespace std;

int main()
{

    bitset<4> bitset1("1001"), bitset2("1010");
    bitset<4> result;

    cout << "Bitset1: " << bitset1
         << "\nBitset2: " << bitset2 << endl;

    cout << "Accessing bit value at index 1 of bitset1: "
         << bitset1[1] << endl;

    // bitwise AND
    cout << "Bitwise AND using &: "
         << (result = bitset1 & bitset2) << endl;
    cout << "Bitwise AND using &=: " << (bitset1 &= bitset2)
         << endl;

    // bitwise OR
    bitset1 = 9; // 9 = 1001
    cout << "Bitwise OR using |: "
         << (result = bitset1 | bitset2) << endl;
    cout << "Bitwise OR using |=: " << (bitset1 |= bitset2)
         << endl;

    // bitwise NOT
    cout << "Bitwise NOT: " << (result = ~bitset1) << endl;

    // bitwise XOR
    bitset1 = 9;
    cout << "Bitwise XOR: " << (bitset1 ^= bitset2) << endl;

    bitset1 = 9;
    cout << "Binary leftshift on bitwise1: "
         << (bitset1 <<= 1) << endl;
    bitset1 = 9;
    cout << "Binary rightshift on bitwise1: "
         << (bitset1 >>= 1) << endl;

    // declaring index variable
    int index = 0;

    // declaring few bitset objects
    bitset<4> allSet("1111"), allUnset;

    cout << "any() value: " << boolalpha << allSet.any()
         << endl;

    cout << "all() value: " << allSet.all() << endl;

    cout << "none() value: " << allSet.none() << endl;

    cout << "test() at index 0: " << noboolalpha
         << allSet.test(index) << endl;

    cout << "size() value: " << allSet.size() << endl;

    cout << "Value of allUnset on before using set(): "
         << allUnset << endl;
    allUnset.set(index);
    cout << "Value of allUnset on after using set(): "
         << allUnset << endl;

    cout << "Value of allSet on before using reset(): "
         << allSet << endl;
    allSet.reset(index);
    cout << "Value of allSet on after using reset(): "
         << allSet << endl;

    // declaring an empty string
    string bitString;
    // using to_string() method to assign value to empty
    // string
    bitString = allSet.to_string();
    cout << "bitString: " << bitString << endl;

    cout << "Unsigned Long value: " << allSet.to_ulong();
    
    
    return 0;
}

