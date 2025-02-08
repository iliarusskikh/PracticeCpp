//virtual functions
//A virtual function (also known as virtual methods) is a member function that is declared within a base class and is re-defined (overridden) by a derived class.
//slower!
// A program with virtual destructor

//vs interface -> An interface does not have an implementation of any of its methods, it can be considered as a collection of method declarations.

#include <iostream>

using namespace std;

class base {
public:
    base()
    { cout << "Constructing base\n"; }
    virtual ~base() //making base destructor virtual would also delete all derived
    { cout << "Destructing base\n"; }
};

class derived : public base {
public:
    derived()
    { cout << "Constructing derived\n"; }
    ~derived()
    { cout << "Destructing derived\n"; }
};

int main()
{
    derived *d = new derived();
    base *b = d;
    delete b;
    getchar();
    return 0;
}
