#include <iostream>
#include <utility>

struct A {
  A() = default;
  A(const A &a) { std::cout << '1'; }
  A(A &&a) { std::cout << '2'; }
};

A a;

int main() {
  [a = std::move(a)]() {
    [a = std::move(a)]() {};
  }();
}
// Output: 21

//The outer lambda captures the a from the global scope. The global a is non-const, so when we do std::move(a), the result is a non-const rvalue reference. When initializing the capturing member of the closure type, the move constructor of A is used and 2 is printed.

//The inner lambda captures the a from the outer lambda, not the a from the global scope. This happens inside the function call operator of the outer closure type. That function call operator is const, so the access to the a member is treated as const. When we do std::move(a), the result is a const rvalue reference. When initializing the capturing member of the inner closure type, the non-const rvalue reference in A's move constructor is not viable, and instead the copy constructor is used, causing 1 to be printed.
