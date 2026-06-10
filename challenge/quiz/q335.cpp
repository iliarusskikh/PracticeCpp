#include <cstddef>
#include <iostream>

void f(void*) {
    std::cout << 1;
}

void f(std::nullptr_t) {
    std::cout << 2;
}

int main() {
    int* a{};

    f(a);
    f(nullptr);
    f(NULL);
}

// Output: unspecified implementation
//The macro NULL is an implementation-defined null pointer constant.

//In most implementations, NULL will be an integer literal and the program will not compile due to ambiguous call f(NULL). However, the C++ standard allows NULL to be a prvalue of std::nullptr_t in which case the program would output 122.


