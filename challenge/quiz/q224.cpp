#include <iostream>

struct Base {
    virtual int f() = 0;
};

int Base::f() { return 1; }

struct Derived : Base {
    int f() override;
};

int Derived::f() { return 2; }

int main() {
    Derived object;
    std::cout << object.f();
    std::cout << ((Base&)object).f();
}

// Output: 22

//((Base&)object).f() casts object to a Base& before calling f(), but since f() is a virtual function, Derived::f() is still called, returning 2.


