#include <iostream>
#include <string>

class Animal {
public:
    void eat() {
        std::cout << "This animal eats food." << std::endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "The dog barks: Woof!" << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat();  // Inherited from Animal
    myDog.bark(); // Specific to Dog
    return 0;
}
