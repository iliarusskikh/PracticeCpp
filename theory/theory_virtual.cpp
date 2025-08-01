#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun() { cout << "A" << endl; }
    virtual ~A() {} // Added virtual destructor
};

class B : public A
{
public:
    virtual void fun() { cout << "B" << endl; } //since base class is virtual, B and C virual by default
};

class C : public B
{
public:
    virtual void fun() { cout << "C" << endl; }
};

int main()
{
    A *a = new C;
    A *b = new B;
    a->A::fun(); // Explicitly call A's fun()
    b->A::fun(); // Explicitly call A's fun()
    delete a;    // Clean up
    delete b;    // Clean up
    return 0;
}
