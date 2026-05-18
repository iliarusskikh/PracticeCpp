#include <iostream>
#include <vector>

int f() { std::cout << "f"; return 0;}
int g() { std::cout << "g"; return 0;}

void h(std::vector<int> v) {}

int main() {
    h({f(), g()});
}

// Output: fg
//The goal of this question is to demonstrate that the evaluation order of elements in an initializer list is specified (as opposed to the arguments to a function call).

//If h took two ints instead of a vector<int>, and was called like this:

//h(f(), g());
//the program would be unspecified, and could either print fg or gf.
