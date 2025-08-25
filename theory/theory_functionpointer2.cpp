#include <bits/stdc++.h>
using namespace std;

// Normal pointer to a function
int (*func_ptr1)(int, int);

// Using typedef with pointer
// to a function
typedef int (*func_ptr2)(int, int);

// Function to multiply two numbers
int product(int u, int v) { return u * v; }

int main(void) {
    
    func_ptr1 = &product;

    // Using typedefed function
    // pointer for creating new
    // function pointer "new_func"
    func_ptr2 new_func_ptr = &product;

    // Using normal pointer to a function
    int x2 = (*func_ptr1)(3, 2);

    // Using the new function pointer
    int x1 = (*new_func_ptr)(2, 4);

    cout << x1 << endl;
    cout << x2;
}
