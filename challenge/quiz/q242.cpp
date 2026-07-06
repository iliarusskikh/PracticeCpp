#include <iostream>
#include <type_traits>
#include <utility>

void g(int&) { std::cout << 'L'; }
void g(int&&) { std::cout << 'R'; }

template<typename T>
void f(T&& t) {
    if (std::is_same_v<T, int>) { std::cout << 1; }
    if (std::is_same_v<T, int&>) { std::cout << 2; }
    if (std::is_same_v<T, int&&>) { std::cout << 3; }
    g(std::forward<T>(t));
}

int main() {
    f(42);
    int i = 0;
    f(i);
}

// Output:1R2L
//Type Deduction: The argument 42 is an rvalue (int prvalue). When passed to a universal reference T&&, T is deduced as int.
// casts the parameter t to an rvalue reference int&&.

//Type Deduction: The argument i is an lvalue (int). When passed to a universal reference T&&, T is deduced as an lvalue reference, int&.
//Reference Collapsing: The parameter type becomes T&& → int& &&, which collapses to int&.
