#include <iostream>
using namespace std;


// Function to check if x is power of 2
bool isPowerOfTwo(int x)
{
    // First x in the below expression is
    // for the case when x is 0
    return x && (!(x & (x - 1)));
}


bool at_position(int num, int pos)
{
    bool bit = num & (1 << pos);
    return bit;
}



void toggle(int& num, int pos)
{
    num ^= (1 << pos);
}



// First step is to get a number that  has all 1's except
// the given position.
void unset(int& num, int pos)
{
    // Second step is to bitwise and this  number with given
    // number
    num &= (~(1 << pos));
}


// num is the number and pos is the position
// at which we want to set the bit.
void set(int& num, int pos)
{
    // First step is shift '1', second
    // step is bitwise OR
    num |= (1 << pos);
}
int main()
{
    int num = 4, pos = 1;
    set(num, pos);
    cout << (int)(num) << endl;
    return 0;
}
