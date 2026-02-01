#include <iostream>
#include <memory>

class Animal {
public:
    virtual ~Animal() = default;           // polymorphic base class
    virtual void makeSound() const = 0;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof!\n";
    }
    void fetchBall() {
        std::cout << "Fetching ball... happy!\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow!\n";
    }
    void ignoreYou() {
        std::cout << "I'm ignoring you...\n";
    }
};

int main()
{

    //implicit
    double value = 5.24;
    int a = value;
    
    //explicit
    int b = (int)value; //c style casting
    
    //c++ casting
    double s = static_cast<int>(value)+5.3;
    
    
    
    //dynamic cast
    //more on dynamic casting - only in c++, it does the validation
    //evaluates at runtime
    //used across inheritance
    //could we promote child to parent?
    Animal* animal = new Dog();

    // Safe downcast with dynamic_cast
    if (Dog* dog = dynamic_cast<Dog*>(animal)) {
        dog->fetchBall();           // now we can safely call Dog-specific method
    }
    else if (Cat* cat = dynamic_cast<Cat*>(animal)) {
        cat->ignoreYou();
    }
    else {
        std::cout << "Unknown animal type\n";
    }

    delete animal;
    
    //const task
    
    
    //static_cast = compile-time type checking
    //dynamic_cast = for polymorphic types
    //const_cast = add/remove const qualifier
    //reinterpret_cast = low-level reinterpreting of bits (no checks)
    int num =43;
    int* ptr = #;
    //converts pointer to integer
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    

    
    int *i = new int(44);
    float *f = reinterpret_cast<float *>(i);
    std::cout << *f<<"\n";//undefined behaviour when accessing
    
    
    
    
    
    return EXIT_SUCCESS;
}

