#include <iostream>

int i;

void f(int x) {
    std::cout << x << i;
}

int main() {
    i = 3;
    f(i++);
}
// Output:34
//Hence, in the expression f(i++), f is called with a parameter of the original value of i, but i is incremented before entering the body of f.



