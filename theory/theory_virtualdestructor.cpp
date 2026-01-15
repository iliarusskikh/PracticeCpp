#include <iostream>
using namespace std;

class Base
{
public:
    Base(){std::cout << "Base Constructor\n";}
    virtual ~Base(){std::cout << "Base Destructor\n";}//added virtual
};

class Derived : public Base
{
public:
    Derived(){std::cout << "Derived Constructor\n";}
    ~Derived(){std::cout << "Derived Destructor\n";}
};


int main()
{
    Base* base = new Base(); //Base Constructor
    delete base;//Base Destructor
    Derived* derived = new Derived();//Base Constructor Derived Constructor
    delete derived;//Derived Destructor Base Destructor
    
    Base* poly = new Derived(); //polymorphism // Base Constructor Derived Constructor
    delete poly; //Base Destructor only.. hence Base destructor needs to be virtual to hint that there is a sub class to find destructor
    
    //whenever there is a subclass, always set destructor as virtual!
    
    
    return EXIT_SUCCESS;
}
