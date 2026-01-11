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
    virtual void fun() override{ cout << "B" << endl; } //since base class is virtual, B and C virual by default
};//override added for clarity

class C : public B
{
public:
    virtual void fun() override { cout << "C" << endl; }
};//override added for clarity

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
