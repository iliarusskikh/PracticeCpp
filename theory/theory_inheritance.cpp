#include <iostream>
#include <string>

//protected members are accessible inside the class where they are defined and inside the derived class


class Animal {
private:
    int a{10};
public:
    void eat() {
        std::cout << "This animal eats food." << std::endl;
    }
protected:
    int c{20};//accessible in derived and inherited classes
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "Protected "  <<c<<"\n"; //way to access protected
        std::cout << "The dog barks: Woof!" << std::endl;
    }
};

class Monster : protected Animal { //private members not accessible, public protected - accessible
public:
    void bark() {
        std::cout << "Protected "  <<c<<"\n"; //way to access protected
        std::cout << "The dog barks: Woof!" << std::endl;
    }
};


class Monster2 : protected Animal { //private members not accessible, public protected - accessible
public:
    void bark() {
        std::cout << "Protected "  <<c<<"\n"; //way to access protected
        std::cout << "The dog barks: Woof!" << std::endl;
    }
};


int main() {
    Dog myDog;
    myDog.eat();  // Inherited from Animal
    myDog.bark(); // Specific to Dog
    
    //std::cout << "Protected "  <<myDog.c<<"\n"; //this is error! cannot be accessed in main function

    //protected member can only be accessed inside classes
    return 0;
}
