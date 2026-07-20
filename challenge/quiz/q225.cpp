#include <iostream>

struct X {
    X() { std::cout << "1"; }
    X(const X &) { std::cout << "3"; }
    ~X() { std::cout << "2"; }

    void f() { std::cout << "4"; }

} object;

int main() {
    X(object); //it would have been copy constructor if (X(object)) - extra parantheses were added
    object.f();
}
// Output: 11422
