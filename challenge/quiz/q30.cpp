#include <iostream>
struct X {
  X() { std::cout << "X"; }
};

int main() { X x(); }

// Output: This program has no output.

//X x(); is a function prototype, not a variable definition.
// Remove the parentheses, and the program will output X.
