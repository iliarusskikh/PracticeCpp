#include <iostream>

int main() {
    char* str = "X";
    std::cout << str;
}
// Output: Compiler error
//an ordinary string literal has type “array of n const char”.

//The array of n const char decays to a pointer to const char. That pointer to const char does not implicitly convert to a pointer to non-const char.


//Note: While most compilers still allow char const[] to char* conversion with just a warning, this is not a legal conversion since C++11.


