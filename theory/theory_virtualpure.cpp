#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun() = 0; //  pure virtual
    virtual ~A() {} // Virtual destructor
};

// Provide implementation for pure virtual function
//void A::fun() {
//    cout << "A" << endl;
//}

class B : public A
{
public:
    virtual void fun() override { cout << "B" << endl; } // Override required since A::fun is pure virtual
};

class C : public B
{
public:
    virtual void fun() override { cout << "C" << endl; }
};

int main()
{
    // A* abstractA = new A; // Error: Cannot instantiate abstract class A
    A *a = new C;
    A *b = new B;
    a->A::fun(); // Explicitly call A's fun() implementation
    b->A::fun(); // Explicitly call A's fun() implementation
    delete a;    // Clean up
    delete b;    // Clean up
    return 0;
}
