#include <iostream>

struct Quiz {};

void f(Quiz) { std::cout << "f1"; }
void f(Quiz &) { std::cout << "f2"; }

int main() {
    f(Quiz());
}
// Output: f1

//the expression Quiz() is a prvalue (a kind of rvalue).

//For the first overload, taking a Quiz by value, it is simple. The parameter is initialized directly from the prvalue Quiz().
//Since the first overload is allowed, but the second is not, the first overload is chosen and f1 is printed.


