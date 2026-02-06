//runtime polymorphism
//dynamic binding or late binding
//without virtual functions a base class function would have been called
#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun() { cout << "A" << endl; }
    virtual ~A() {} // Added virtual destructor - mandatory to call children destructors
    
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
    A *a = new C; //Base class pointer to derived class
    A *b = new B;
    a->A::fun(); // Explicitly call A's fun()
    b->A::fun(); // Explicitly call A's fun()
    delete a;    // Clean up
    delete b;    // Clean up
    
    
    
    A* ptr1 = new C;
    A* ptr2 = new B;
    A* ptr3 = new A;

    ptr1->fun();   // prints C
    ptr2->fun();   // prints B
    ptr3->fun();   // prints A

    delete ptr1;
    delete ptr2;
    delete ptr3;
    
    //using smart pointers + containers
    vector<unique_ptr<A>> objects;
    
    objects.push_back(make_unique<A>());
    objects.push_back(make_unique<B>());
    objects.push_back(make_unique<C>());

    for (const auto& obj : objects) {
        obj->fun();
    }

    // no manual delete needed — RAII
    
    
    return 0;
}


//abstract classes
//a pure virtual function is declared with =0
//abstract classes cannot be instantiated
//derived class must implement all pure virtual functions






// compile time polymorphism achieved through function overloading or templates
//function binding at compile time

void print(int x){}
void print(double x){}

template<typename T>
void print(T value){}
