//If the compiler had optimized away certain memory accesses assuming the object was still of type Base, std::launder forces it to reconsider the object's actual type.

#include <iostream>
#include <new>

struct Base
{
    virtual void show() {std::cout << "Base\n";}
};

struct Derived : Base {
    void show() override {
        std::cout<< "Derived" << std::endl;
    };
};

int main()
{
    alignas(Derived) char buffer[sizeof(Derived)]; //create non objective buffer
    Base* obj = new (buffer) Derived(); //buffer preallocated on stack. not heap
    obj->show();
    obj->~Base();//base destroyed
    auto* recovered = std::launder(reinterpret_cast<Derived*>(buffer));//prevents unknown behaviour, gives access to objects after changing their type
    //If the compiler had optimized away certain memory accesses assuming the object was still of type Base, std::launder forces it to reconsider the object's actual type.
    recovered->show(); //shows Derived
    recovered->~Derived();
    
    return 0;
}
