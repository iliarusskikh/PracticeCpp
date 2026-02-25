// Virtual base class to resolve the diamond problem
#include <iostream>

/*
class A {
public:
    A() {
        std::cout << "A Constructor\n";
    }
    void display(){
        std::cout <<"I am A\n";
    }
};

class B: public A {
public:
    B() {
        std::cout << "B Constructor\n";
    }
};

class C: public A {
public:
    C() {
        std::cout << "C Constructor\n";
    }
};

class D: public B, public C {
public:
    C() {
        std::cout << "D Constructor\n";
    }
};
*/

//one copy of display function per classes B or C.
class A {
public:
    A() {
        std::cout << "A Constructor\n";
    }
    void display(){
        std::cout <<"I am A\n";
    }
};

class B: virtual public A {
public:
    B() {
        std::cout << "B Constructor\n";
    }
};

class C: virtual public A {
public:
    C() {
        std::cout << "C Constructor\n";
    }
};

class D: public B, public C {
public:
    D() {
        std::cout << "D Constructor\n";
    }
};


int main()
{
    
    
    D obj;
    //output
    //A Constructor
    //B Constructor
    //A Constructor
    //C Constructor
    //D Constructor

    
    //compiler error when obj.display() since it does not know if display function of class B or C
    //once virtual base class declared through B and C for class A
    //A Constructor - called only one
    //B Constructor
    //C Constructor
    //D Constructor
    //I am A


    
    
    return EXIT_SUCCESS;
}
