#include <iostream>

struct A {
    virtual void foo (int a = 1) {
        std::cout << "A" << a;
    }
};

struct B : A {
    virtual void foo (int a = 2) {
        std::cout << "B" << a;
    }
};

int main () {
    A *b = new B;
    b->foo();
}

// Output: B1

//On the next line, we call b->foo(), where b has the static type A, and the dynamic type B. Since foo() is virtual, the dynamic type of b is used to ensure B::foo() gets called rather than A::foo().


