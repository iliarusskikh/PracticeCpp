#include <iostream>

extern "C" int x; //declaration
extern "C" { int y; } //definition

int main() {
    std::cout << x << y;
}
// Output: undefined
//The result: x is never defined but it is optional for the compiler to print an error. The behaviour of this program is undefined.
