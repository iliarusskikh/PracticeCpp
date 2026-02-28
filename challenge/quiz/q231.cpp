#include <iostream>

struct override {};//Type name (user-defined struct)

struct Base {
virtual override f() = 0;
};

struct Derived : Base {
virtual auto f() -> override override{
    std::cout << "1";
    return override();  // Construct and return object of type 'override'
}
    
    
/*
 
 virtual override f() override {
 //          │         │
 //          │         └── keyword: overrides base class function
 //          └───────────── return type: struct override
 
     std::cout << "1";
     return override();  // Construct type 'override'
 }
 */
};

int main() {
Derived().f();
}
// 1

//[override and final] have a special meaning when appearing in a certain context. (...) Unless otherwise specified, any ambiguity as to whether a given identifier has a special meaning is resolved to interpret the token as a regular identifier.
/*
 
 
 If we replace the type name override with type, the definition of Derived::f becomes easier to read:

 virtual auto f() -> type override{
     std::cout << "1";
     return type();
 }
 
 
 
 auto f() -> int;      // Same as: int f();

 */
