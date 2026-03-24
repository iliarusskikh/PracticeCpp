#include <iostream>

int main() {
    int a = '0';
    char const &b = a;
    std::cout << b;
    a++;
    std::cout << b;
}
//0 0
//'0' is a character literal, with type char. (The value of '0' is actually implementation defined, but will typically be 48.) This value is then promoted to an int, and stored in a.

//We then take a reference b to a. But b is a char reference, not an int reference, so it can not bind directly to the int.

//A pointer to int can not be converted to a pointer to char const via any standard conversion hence
//So the initializer expression a is converted to a temporary char const, which b refers to.

//We then print b, which refers to our temporary char '0'.

//We then increment the original a, which importantly does not modify the temporary that b refers to.

//We finally print b again, which still prints 0.
