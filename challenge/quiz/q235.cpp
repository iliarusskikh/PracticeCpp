
#include <initializer_list>
#include <iostream>

class C {
public:
    C() = default;
    C(const C&) { std::cout << 1; }
};

void f(std::initializer_list<C> i) {}

int main() {
    C c;
    std::initializer_list<C> i{c};
    f(i);
    f(i);
}
//Output: 1

//So when we construct the initializer list i, we can imagine a temporary array of one C being created, where the element is copy-initialized. Since c is an lvalue, a copy is made (not for instance a move), and 1 is printed.


//in f cases , the initializer_list only refers to that array, it doesn't have a copy of it.
