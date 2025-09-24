//Add two numbers without using arithmetic operators

//Given two integers a and b, the task is to find the sum of a and b without using + or - operators.


//If we want to calculate the sum of a and b such that a and b has no common set bit, then a ^ b is same as a + b. So, we can say that a + b without carry = a ^ b.
//
//How to handle the case when we have carry, that is a and b has common set bits?
//
//To calculate the carry, we know that carry will only have the common set bits of a and b, shifted 1 place to the left. So, we can say that carry = (a & b) << 1.


// C++ Program to add two numbers without using arithmetic operators

#include <bits/stdc++.h>
using namespace std;

// function to add two numbers without using arithmetic operators
int sum(int a, int b) {
    
    // Iterate till there is no carry
    while (b != 0) {
        
        // carry contains common set bits of a and b, left shifted by 1
        int carry = (a & b) << 1;

        // Update a with (a + b without carry)
        a = a ^ b;
      
        // Update b with carry
        b = carry;
    }
    return a;
}

int main() {
    int a = -1, b = 2;
  
    cout << sum(a, b);
    return 0;
}
