#include <iostream>
#include <utility>

struct A {
    A() = default;
    A(const A&)  { std::cout << '1'; }
    A(A&&)       { std::cout << '2'; }
};

A a;

int main() {
    [a = std::move(a)]() {
        [a = std::move(a)]() {
        }();
    }();
}
// Output: 21

//The outer lambda captures a with a = std::move(a), which direct-initializes its closure member from the global a. Thanks to std::move turning this into an rvalue, the move constructor A(A&&) is selected, which prints 2.

//The lambda's operator() is const by default
//The function call operator (...) is declared const if and only if the lambda-expression's parameter-declaration-clause is not followed by mutable


//The second std::move yields const A&&
//The copy constructor is selected instead
//With the move constructor not viable for const A&&, overload resolution selects the copy constructor A(const A&) instead, printing 1 .
