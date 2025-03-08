virtual function

A virtual function in C++ is a member function in a base class that you can override in a derived class while ensuring dynamic (runtime) polymorphism.




✔ Runtime Polymorphism – Allows derived classes to modify base class behavior dynamically.
✔ Extensibility – New classes can override base behavior without modifying existing code.
✔ Encapsulation – Hides implementation details in a base class, exposing only an interface.

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { // Virtual function
        cout << "Base class show()" << endl;
    }
};

class Derived : public Base {
public:
    void show() override { // Overriding the virtual function
        cout << "Derived class show()" << endl;
    }
};

int main() {
    Base* ptr;
    Derived d;
    ptr = &d;

    ptr->show(); // Calls Derived::show() due to virtual function
    return 0;
}

